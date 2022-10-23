#include <chrono>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <condition_variable>
#include <future>
#include <numeric>
#include <limits>
#include <mutex>

#include "configure.hpp"
#include "utility/random.hpp"
#include "utility/file.hpp"
#include "utility/system.hpp"
#include "utility/output.hpp"
#include "common/scope.hpp"
#include "common/token.hpp"
#include "common/define.hpp"
#include "common/time_measurer.hpp"
#include "block.hpp"
#include "representation.hpp"
#include "operation.hpp"
#include "repairer.hpp"

namespace REPAIR
{

Repairer::Repairer()
    : mTarget{}
    , mPool{}
    , mIsRepaired{false}
    , mResult{nullptr}
    , mTotalGen{0ull}
    , mTotalRep{0ull}
{
}

Repairer::~Repairer()
{
    delete mResult;
}

bool Repairer::execute(const CodeInformation &target
    , const std::deque<CodeInformation> &pool
    , const std::optional<std::deque<std::deque<double>>> &similarity)
{
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::RepairTag::INITIALIZING};
        if(!initialize(target, pool, similarity))
            return false;
    }

    if(Configure::SHOULD_USE_BRUTE_FORCE)
    {
        if(!repairUsingBruteForce())
            return false;
    }
    else
    {
        if(!repair())
            return false;
    }

    if(Configure::SHOULD_OUTPUT_REPAIR_LOG)
        outputResultLog();

    if(Configure::SHOULD_OUTPUT_SPECIFIED_LOG)
        outputSpecifiedLog();

    return true;
}

bool Repairer::outputResult(const std::string &filename) const
{
    if(!mResult)
        return false;
    
    // remove extension
    std::string baseFilename{filename};
    if(std::filesystem::path{filename}.extension() == ".c")
    {
        baseFilename.pop_back();
        baseFilename.pop_back();
    };

    return outputToFile(baseFilename
        , std::shared_ptr<REPRESENTATION::Representation>{mResult->copy()});
}

bool Repairer::initialize(const CodeInformation &target
    , const std::deque<CodeInformation> &pool
    , const std::optional<std::deque<std::deque<double>>> &similarity)
{
    mTarget
        = std::make_shared<BLOCK::Block>(target.mTranslationUnit.get()
            , target.mScope->id());
    for(auto &&ci : pool)
    {
        mPool.emplace_back(std::make_shared<BLOCK::Block>(ci.mTranslationUnit.get()
            , ci.mScope->id()));
    }

    if(!REPRESENTATION::Representation::initialize(mTarget, mPool))
        return false;
    
    if(similarity.has_value())
    {
        if(!OPERATION::Operation::initialize(mTarget, mPool, similarity.value()))
            return false;
    }
    else
    {
        if(!OPERATION::Operation::initialize(mTarget, mPool))
            return false;
    }

    if(!Configure::SHOULD_CREATE_SAME_OP
        && !OPERATION::Operation::initializeFirstOperations(mTarget))
        return false;

    return true;
}

bool Repairer::repair()
{
    using namespace REPRESENTATION;

    // rep and score
    Reps prevReps, currentReps;

    for(std::size_t gen{0ull}; gen < Configure::MAX_GEN; gen++)
    {
        mTotalGen++;

        currentReps.swap(prevReps);
        currentReps.clear();

        {
            TimeMeasurer::Wrapper wrapper{TimeMeasurer::RepairTag::REP_GENERATION};
            if(!createReps(currentReps, prevReps))
                return false;
        }

        {
            TimeMeasurer::Wrapper wrapper{TimeMeasurer::RepairTag::EVALUATION};
            if(!test(currentReps))
                return false;
        }

        if(mIsRepaired)
            break;
    }

    return true;
}

bool Repairer::repairUsingBruteForce()
{
    using namespace REPRESENTATION;
    
    TimeMeasurer::Wrapper wrapper{TimeMeasurer::RepairTag::EVALUATION};

    // this mutex is used for futures and availableIndices.
    std::mutex mutex;
    std::condition_variable cv;

    std::deque<std::future<std::pair<std::shared_ptr<Representation>, int>>> futures(Configure::NUM_CONCURRENCY);
    // availableIndices is used to notify finished future object to main thread.
    std::deque<std::size_t> availableIndices(futures.size());
    std::iota(availableIndices.begin()
        , availableIndices.end()
        , 0ull);

    std::size_t firstOpSize{OPERATION::Operation::firstOperations.size()};
    int maxScore{std::numeric_limits<int>::min()};

    // this function is used for std::async function.
    // future object has this function.
    auto &&evaluateWrapper{[&](std::size_t indexOfFutures
        , std::shared_ptr<Representation> rep)
        -> std::pair<std::shared_ptr<Representation>, int>
        {
            int score{evaluateRep(rep)};

            std::unique_lock lock{mutex};
            mTotalRep++;
            availableIndices.push_back(indexOfFutures);

            cv.notify_all();
            return {rep, score};
        }};

    auto &&evaluateWrapperWithOutput{[&](std::size_t indexOfFutures
        , std::shared_ptr<Representation> rep)
        -> std::pair<std::shared_ptr<Representation>, int>
        {
            auto &&result{evaluateWrapper(indexOfFutures, rep)};

            std::unique_lock ioLock{stdioMutex};
            std::cout << "repair-log: evaluation is end.("
                << mTotalRep
                << "/" << firstOpSize
                << ")"
                << std::endl;
            return result;
        }};

    // function that is passed to future.
    std::function<std::pair<std::shared_ptr<Representation>, int>(std::size_t, std::shared_ptr<Representation>)> evaluateFunc;
    if(Configure::SHOULD_OUTPUT_REPAIR_LOG)
        evaluateFunc = evaluateWrapperWithOutput;
    else
        evaluateFunc = evaluateWrapper;

    // execute all evaluation.
    for(std::size_t i{0ull}; i < firstOpSize;)
    {
        std::unique_lock lock{mutex};

        // if available future object exists,
        // result of previous future object is assigned currentReps
        // and new future object is set to futures.
        if(!availableIndices.empty())
        {
            std::size_t indexOfFutures{availableIndices.front()};
            availableIndices.pop_front();
            
            if(futures.at(indexOfFutures).valid())
            {
                auto &&[rep, score]{futures.at(indexOfFutures).get()};
                if(score >= maxScore)
                {
                    maxScore = score;
                    mResult = rep->copy();
                }
                if(score >= Configure::getSafelyGOAL_SCORE())
                    break;
            }

            std::shared_ptr<Representation> rep{new Representation{}};
            rep->addOperation(OPERATION::Operation::firstOperations.at(i).second);
            futures.at(indexOfFutures)
                = std::async(std::launch::async
                    , evaluateFunc
                    , indexOfFutures
                    , rep);
            i++;
        }
        else
            cv.wait(lock, [&]{return !availableIndices.empty();});
    }

    // wait until execution of future objects is end.
    for(auto &&future : futures)
    {
        if(future.valid())
        {
            auto &&[rep, score]{future.get()};
            if(score >= maxScore)
            {
                maxScore = score;
                mResult = rep->copy();
            }
        }
    }

    // set results to member variables.
    mIsRepaired = maxScore >= Configure::GOAL_SCORE;

    return true;
}

bool Repairer::createReps(Reps &currentReps
    , const Reps &prevReps) const
{
    static std::shared_ptr<REPRESENTATION::Representation> clearBase{new REPRESENTATION::Representation{}};

    double newCreationProb{1.0};
    
    if(!prevReps.empty())
    {
        newCreationProb = Configure::NEW_CREATION_PROB;
    
        std::copy(prevReps.begin()
            , prevReps.begin() + Configure::NUM_ELITE
            , std::back_inserter(currentReps));
    }

    for(std::size_t i{currentReps.size()}; i < Configure::POP_SIZE; i++)
    {
        std::shared_ptr<REPRESENTATION::Representation> derived;
        if(RANDOM::RAND.floating<double>() <= newCreationProb)
            derived = createRep(clearBase);
        else
            derived = createRep(selectRep(prevReps));
        
        if(!derived)
            return false;

        currentReps.emplace_back(derived, std::numeric_limits<int>::min());
    }

    return true;
}

bool Repairer::test(Reps &currentReps)
{
    using namespace REPRESENTATION;

    // this mutex is used for currentReps, futures and availableIndices.
    std::mutex mutex;
    std::condition_variable cv;

    std::deque<std::future<std::pair<std::size_t,int>>> futures(Configure::NUM_CONCURRENCY);
    // availableIndices is used to notify finished future object to main thread.
    std::deque<std::size_t> availableIndices(futures.size());
    std::iota(availableIndices.begin()
        , availableIndices.end()
        , 0ull);

    // this function is used for std::async function.
    // future object has this function.
    auto &&evaluateWrapper{[&](std::size_t indexOfReps
        , std::size_t indexOfFutures
        , std::shared_ptr<Representation> rep)
        -> std::pair<std::size_t, int>
        {
            int score{evaluateRep(rep)};

            std::unique_lock lock{mutex};
            mTotalRep++;
            currentReps.at(indexOfReps).second = score;
            availableIndices.push_back(indexOfFutures);

            cv.notify_all();
            return {indexOfReps, score};
        }};

    auto &&evaluateWrapperWithOutput{[&](std::size_t indexOfReps
        , std::size_t indexOfFutures
        , std::shared_ptr<Representation> rep)
        -> std::pair<std::size_t, int>
        {
            auto &&result{evaluateWrapper(indexOfReps
                , indexOfFutures
                , rep)};

            std::unique_lock ioLock{stdioMutex};
            std::cout << "repair-log: evaluation is end.("
                << (mTotalRep - 1ull) % Configure::getSafelyPOP_SIZE() + 1ull
                << "/" << Configure::getSafelyPOP_SIZE()
                << ")(gen:" << mTotalGen << ")"
                << std::endl;
            return result;
        }};

    // function that is passed to future.
    std::function<std::pair<std::size_t, int>(std::size_t, std::size_t, std::shared_ptr<Representation>)> evaluateFunc;
    if(Configure::SHOULD_OUTPUT_REPAIR_LOG)
        evaluateFunc = evaluateWrapperWithOutput;
    else
        evaluateFunc = evaluateWrapper;

    // execute all evaluation.
    for(std::size_t indexOfReps{0ull}, size{currentReps.size()}; indexOfReps < size;)
    {
        std::unique_lock lock{mutex};

        // if available future object exists,
        // result of previous future object is assigned currentReps
        // and new future object is set to futures.
        if(!availableIndices.empty())
        {
            std::size_t indexOfFutures{availableIndices.front()};
            availableIndices.pop_front();
            
            if(futures.at(indexOfFutures).valid())
            {
                auto &&[index, score]{futures.at(indexOfFutures).get()};
                if(currentReps.at(index).second >= Configure::getSafelyGOAL_SCORE())
                    break;
            }

            futures.at(indexOfFutures)
                = std::async(std::launch::async
                    , evaluateFunc
                    , indexOfReps
                    , indexOfFutures
                    , currentReps.at(indexOfReps).first);
            indexOfReps++;
        }
        else
            cv.wait(lock, [&]{return !availableIndices.empty();});
    }

    // wait until execution of future objects is end.
    for(auto &&future : futures)
    {
        if(future.valid())
            future.get();
    }

    // results is sorted by score.
    std::sort(currentReps.begin()
        , currentReps.end()
        , [](auto &&lhs, auto &&rhs){return lhs.second > rhs.second;});

    // set results to member variables.
    mResult = currentReps.front().first->copy();
    mIsRepaired = currentReps.front().second >= Configure::GOAL_SCORE;

    return true;
}

std::shared_ptr<REPRESENTATION::Representation> Repairer::createRep(const std::shared_ptr<REPRESENTATION::Representation> &base) const
{
    std::shared_ptr<REPRESENTATION::Representation> rep{base->copy()};

    bool isCreated{false};
    for(std::size_t i{0ull}; i < Configure::FAILURE_LIMIT; i++)
    {
        if((isCreated = rep->addOperation()))
            break;
    }

    if(!isCreated)
    {
        repCreationError("failure limit is reached.");
        return {};
    }
    
    return rep;
}

std::shared_ptr<REPRESENTATION::Representation> Repairer::selectRep(const Reps &reps) const
{
    Reps sample;
    std::sample(reps.begin()
        , reps.end()
        , std::back_inserter(sample)
        , Configure::TOURNAMENT_SIZE
        , RANDOM::RAND.engine());

    return std::max_element(sample.begin()
        , sample.end()
        , [](auto &&lhs, auto &&rhs){return lhs.second > rhs.second;})
        ->first; 
}

int Repairer::evaluateRep(const std::shared_ptr<REPRESENTATION::Representation> &rep)
{
    int score{std::numeric_limits<int>::min()};

    std::string baseFilename{PATH::getTempFilename()};

    // if any function return false, remained function is not called and score is set min.
    outputToFile(baseFilename, rep)
        && compile(baseFilename)
        && execute(baseFilename, score);

    // removes created files.
    std::string cFilename{baseFilename + ".c"};
    std::string execFilename{baseFilename + Configure::getSafelyEXEC_EXTENSION()};
    std::remove(cFilename.c_str());
    std::remove(execFilename.c_str());

    return score;
}

bool Repairer::outputToFile(const std::string &baseFilename
    , const std::shared_ptr<REPRESENTATION::Representation> &rep)
{
    std::shared_ptr<TOKEN::TranslationUnit> translationUnit{rep->block()->createTranslationUnit()};

    if(!PATH::write(baseFilename + ".c", translationUnit->str(rep->block()->scopeId())))
        return outputError(baseFilename + ".c");

    return true;
}

bool Repairer::compile(const std::string &baseFilename)
{
    std::string command{SYSTEM::command(Configure::getSafelyCOMPILER()
        , baseFilename + ".c"
        , "-o"
        , baseFilename + Configure::getSafelyEXEC_EXTENSION())};

    controlOutputLog(command, stdioMutex);

    if(SYSTEM::system(command) != 0)
        return compilingError(baseFilename + ".c");

    return true;
}

bool Repairer::execute(const std::string &baseFilename
    , int &score)
{
    auto &&exec{[&](const std::string &prefix
        , std::size_t size
        , int weight)
        -> bool
        {
            for(std::size_t i{0ull}; i < size; i++)
            {
                std::string tempFilename{PATH::getTempFilename()};
                std::string command{SYSTEM::command("bash"
                    , Configure::getSafelyTEST_SCRIPT()
                    , prefix + std::to_string(i)
                    , baseFilename + Configure::getSafelyEXEC_EXTENSION()
                    , tempFilename)};

                controlOutputLog(command, stdioMutex);

                if(SYSTEM::system(command) == 0)
                    score += weight;

                PATH::remove(tempFilename);
            }

            return true;
        }};

    score = 0;
    return exec(Configure::getSafelyPOSITIVE_TEST_PREFIX()
        , Configure::getSafelyNUM_POSITIVE_TEST()
        , Configure::getSafelyPOSITIVE_TEST_WEIGHT())
        && exec(Configure::getSafelyNEGATIVE_TEST_PREFIX()
            , Configure::getSafelyNUM_NEGATIVE_TEST()
            , Configure::getSafelyNEGATIVE_TEST_WEIGHT());
}

void Repairer::outputResultLog() const
{
    std::cout << "repair-log:\n"
        "    repair is " << (mIsRepaired ? "SUCCEEDED" : "FAILED")
        << ".\n    Generation: " << mTotalGen
        << "\n    Representation: " << mTotalRep
        << std::endl;
}

bool Repairer::repCreationError(const std::string &what) const
{
    std::cerr << OUTPUT::charRedCode
        << "REPAIR::Repairer::repCreationError():\n"
        << OUTPUT::resetCode
        << "    what: " << what
        << std::endl;
    return false;
}

bool Repairer::outputError(const std::string &filename)
{
    std::unique_lock lock{stdioMutex};
    std::cerr << OUTPUT::charRedCode
        << "REPAIR::Repairer::outputError():\n"
        << OUTPUT::resetCode
        << "    what: failed to output to file.\n"
        "    filename: " << filename
        << std::endl;
    return false;
}

bool Repairer::compilingError(const std::string &filename)
{
    std::unique_lock lock{stdioMutex};
    std::cerr << OUTPUT::charRedCode
        << "REPAIR::Repairer::compilingError():\n"
        << OUTPUT::resetCode
        << "    filename" << filename
        << std::endl;
    return false;
}

void Repairer::outputSpecifiedLog() const
{
    sstream << std::boolalpha
        << mIsRepaired
        << ","
        << mTotalRep
        << ",";
}

}