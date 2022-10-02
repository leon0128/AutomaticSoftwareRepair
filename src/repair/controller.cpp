#include <limits>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <iomanip>

#include "../utility/file.hpp"
#include "../utility/system.hpp"
#include "../utility/random.hpp"
#include "../configure.hpp"
#include "../analyzer.hpp"
#include "../scope.hpp"
#include "../time_measurer.hpp"
#include "block.hpp"
#include "representation.hpp"
#include "operation.hpp"
#include "controller.hpp"

namespace REPAIR
{

Controller::Controller()
    : mBlock{nullptr}
    , mPool{}
    , mNumCreatedFile{0ull}
    , mNumCompilationSucceededFile{0ull}
    , mIsAbleToRepair{false}
{
}

Controller::~Controller()
{
    delete mBlock;
    for(auto *block : mPool)
        delete block;
}

bool Controller::execute(std::shared_ptr<Analyzer> srcAnalyzer
    , const std::vector<std::shared_ptr<Analyzer>> &analyzerPool
    , const std::optional<std::deque<std::deque<double>>> &similarity)
{
    if(!initialize(srcAnalyzer
        , analyzerPool
        , similarity))
        return false;

    std::shared_ptr<REPRESENTATION::Representation> result{geneticAlgorithm()};
    if(!result)
        return false;

    outputToFile(Configure::RESULT_FILENAME
        , result.get());

    if(Configure::SHOULD_OUTPUT_REPAIR_LOG)
    {
        std::cout << "repair:\n"
            << "    repair is " << (mIsAbleToRepair ? "SUCCEEDED" : "FAILED")
            << ".\n    compile success late: "
            << std::fixed << std::setprecision(3)
            << static_cast<double>(mNumCompilationSucceededFile) / static_cast<double>(mNumCreatedFile) * 100.0
            << "%(" << mNumCompilationSucceededFile << '/' << mNumCreatedFile << ')'
            << std::endl;
    }

    return true;
}

bool Controller::initialize(std::shared_ptr<Analyzer> src
    , const std::vector<std::shared_ptr<Analyzer>> &pool
    , const std::optional<std::deque<std::deque<double>>> &similarity)
{
    TimeMeasurer::Wrapper wrapper{TimeMeasurer::RepairTag::INITIALIZING};

    mBlock = new BLOCK::Block{src->translationUnit()
        , src->scope()->id()};
    for(const auto &analyzer : pool)
    {
        mPool.push_back(new BLOCK::Block{analyzer->translationUnit()
            , analyzer->scope()->id()});
    }
    
    if(!REPRESENTATION::Representation::initialize(mPool, mBlock))
        return false;
    
    if(similarity.has_value())
    {
        if(!OPERATION::Operation::initialize(mPool, mBlock, similarity.value()))
            return false;
    }
    else
    {
        if(!OPERATION::Operation::initialize(mPool, mBlock))
            return false;
    }

    return true;
}

std::shared_ptr<REPRESENTATION::Representation> Controller::geneticAlgorithm()
{
    using namespace REPRESENTATION;

    std::vector<std::shared_ptr<Representation>> reps;
    std::vector<std::shared_ptr<Representation>> nextReps;
    std::vector<std::pair<int, std::size_t>> scores;

    for(std::size_t i{0ull};
        i < Configure::POP_SIZE;
        i++)
    {
        reps.emplace_back(new Representation{});
        for(std::size_t j{0ull};
            j < Configure::FAILURE_LIMIT;
            j++)
        {
            if(reps.back()->addOperation())
                break;            
            else if(j + 1ull == Configure::FAILURE_LIMIT)
            {
                geneticAlgorithmError("failed to create representation");
                return std::shared_ptr<Representation>{};
            }
        }
    }

    std::shared_ptr<Representation> result;
    for(std::size_t gen{0ull};
        gen < Configure::MAX_GEN;
        gen++)
    {
        for(std::size_t i{0ull};
            i < reps.size();
            i++)
        {
            scores.emplace_back(fitness(reps[i].get())
                , i);
            if(scores.back().first >= Configure::GOAL_SCORE)
            {
                mIsAbleToRepair = true;
                result = reps[i];
                break;
            }
        }

        if(mIsAbleToRepair)
            break;

        std::sort(scores.begin()
            , scores.end()
            , [](const auto &lhs
                , const auto &rhs)
                {return lhs.first > rhs.first;});
        
        if(gen + 1ull == Configure::MAX_GEN)
        {
            result = reps[scores.front().second];
            break;
        }
        
        for(std::size_t i{Configure::NUM_ELITE};
            i < Configure::POP_SIZE;
            i++)
        {
            if(auto &&rep{manipulate(reps
                , scores)};
                bool{rep})
                nextReps.push_back(std::move(rep));
            else
                return std::shared_ptr<REPRESENTATION::Representation>{};
        }

        reps.swap(nextReps);
        nextReps.clear();
        scores.clear();
    }

    return result;
}

int Controller::fitness(const REPRESENTATION::Representation *rep)
{
    auto &&evaluate{[](const std::string &prefix
        , std::size_t size
        , int weight)
        -> int
        {
            int score{0};
            for(std::size_t i{0ull};
                i < size;
                i++)
            {
                std::string command{SYSTEM::command("bash"
                    , Configure::TEST_SCRIPT
                    , Configure::EXECUTION_NAME
                    , prefix + std::to_string(i)
                    , ">"
                    , SYSTEM::NULLFILE
                    , "2>&1")};

                if(SYSTEM::system(command) == 0)
                    score += weight;
            }

            return score;
        }};

    if(!outputToFile(Configure::TEST_FILENAME
        , rep))
        return std::numeric_limits<int>::min();
    else
        mNumCreatedFile++;

    if(!compile(Configure::TEST_FILENAME))
        return std::numeric_limits<int>::min();
    else
        mNumCompilationSucceededFile++;

    int score{0};
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::RepairTag::EVALUATION};
        score += evaluate(Configure::POSITIVE_TEST_PREFIX
            , Configure::NUM_POSITIVE_TEST
            , Configure::POSITIVE_TEST_WEIGHT);
        score += evaluate(Configure::NEGATIVE_TEST_PREFIX
            , Configure::NUM_NEGATIVE_TEST
            , Configure::NEGATIVE_TEST_WEIGHT);
    }

    return score;
}

bool Controller::outputToFile(const std::string &filename
    , const REPRESENTATION::Representation *rep) const
{
    TimeMeasurer::Wrapper wrapper{TimeMeasurer::RepairTag::FILE_CREATION};

    std::shared_ptr<TOKEN::TranslationUnit> tu{rep->block()->createTranslationUnit()};
    
    if(!PATH::write(filename
        , TOKEN::str(tu.get())))
        return outputError(filename);

    return true;
}

bool Controller::compile(const std::string &filename) const
{
    TimeMeasurer::Wrapper wrapper{TimeMeasurer::RepairTag::COMPILATION};

    std::string command{SYSTEM::command(Configure::COMPILER
        , filename
        , "-o"
        , Configure::EXECUTION_NAME
        , ">"
        , SYSTEM::NULLFILE
        , "2>&1")};
    
    if(SYSTEM::system(command) != 0)
        return compilingError(filename);

    return true;
}

std::shared_ptr<REPRESENTATION::Representation> Controller::manipulate(const std::vector<std::shared_ptr<REPRESENTATION::Representation>> &reps
    , const std::vector<std::pair<int, std::size_t>> &scores) const
{
    using namespace REPRESENTATION;

    TimeMeasurer::Wrapper wrapper{TimeMeasurer::RepairTag::MANIPLATION};

    std::shared_ptr<Representation> rep;

    bool isCreated{false};
    for(std::size_t i{0ull};
        i < Configure::FAILURE_LIMIT + 1ull;
        i++)
    {
        rep.reset(reps[select(scores)]->copy());

        if(rep->addOperation())
        {
            isCreated = true;
            break;
        }
    }

    if(!isCreated)
    {
        manipulationError("reached failure limits");
        return {};
    }

    return rep;
}

std::size_t Controller::select(const std::vector<std::pair<int, std::size_t>> &scores) const
{
    std::vector<std::pair<int, std::size_t>> sample;
    std::sample(scores.begin()
        , scores.end()
        , std::back_inserter(sample)
        , Configure::TOURNAMENT_SIZE
        , RANDOM::RAND.engine());

    return std::max_element(sample.begin()
        , sample.end()
        , [](const auto &lhs
            , const auto &rhs)
            {return lhs.first > rhs.first;})->second;
}

bool Controller::compilingError(const std::string &filename) const
{
    std::cerr << "GA::Controller compilingError()\n"
        "    filename: " << filename
        << std::endl;
    return false;
}

bool Controller::manipulationError(const std::string &what) const
{
    std::cerr << "GA::Controller manipulationError()\n"
        "    what: " << what
        << std::endl;
    return false;
}

bool Controller::geneticAlgorithmError(const std::string &what) const
{
    std::cerr << "GA::Controller geneticAlgorithmError()\n"
        << "    what: " << what
        << std::endl;
    return false;
}

bool Controller::outputError(const std::string &filename) const
{
    std::cerr << "GA::Controller outputError()\n"
        "    filename: " << filename
        << std::endl;
    return false;
}

}