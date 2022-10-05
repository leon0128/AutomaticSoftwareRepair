#include <chrono>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <condition_variable>
#include <future>
#include <mutex>
#include <numeric>
#include <limits>

#include "utility/random.hpp"
#include "configure.hpp"
#include "common/scope.hpp"
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
    if(!initialize(target, pool, similarity))
        return false;
    
    if(!repair())
        return false;

    return true;
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

    return true;
}

bool Repairer::repair()
{
    using namespace REPRESENTATION;

    // rep and score
    Reps prevReps, currentReps;

    for(std::size_t gen{0ull}; gen < Configure::MAX_GEN; gen++)
    {
        currentReps.swap(prevReps);
        currentReps.clear();

        if(!createReps(currentReps, prevReps))
            return false;

        if(!test(currentReps))
            return false;

        if(mIsRepaired)
            break;
    }

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
            currentReps.at(indexOfReps).second = score;
            availableIndices.push_back(indexOfFutures);
            cv.notify_all();
        
            return {indexOfReps, score};
        }};

    for(std::size_t i{0ull}; i < currentReps.size(); i++)
    {
        std::unique_lock lock{mutex};

        if(!availableIndices.empty())
        {
            std::size_t indexOfFutures{availableIndices.front()};
            availableIndices.pop_front();
            
            if(futures.at(indexOfFutures).valid())
            {
                auto &&[indexOfReps, score]{futures.at(indexOfFutures).get()};
                currentReps.at(indexOfReps).second = score;
                if(score >= Configure::GOAL_SCORE)
                    break;
            }

            futures.at(indexOfFutures)
                = std::async(std::launch::async
                    , evaluateWrapper
                    , i
                    , indexOfFutures
                    , currentReps.at(i).first);
        }
        else
            cv.wait(lock, [&]{return !availableIndices.empty();});
    }

    for(auto &&future : futures)
    {
        if(future.valid())
        {
            auto &&[index, score]{future.get()};
            currentReps.at(index).second = score;
        }
    }


    std::sort(currentReps.begin()
        , currentReps.end()
        , [](auto &&lhs, auto &&rhs){return lhs.second > rhs.second;});

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

bool Repairer::repCreationError(const std::string &what) const
{
    std::cerr << "REPAIR::Repairer::repCreationError():\n"
        "    what: " << what
        << std::endl;
    return false;
}

}