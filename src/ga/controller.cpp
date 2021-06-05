#include <iostream>
#include <algorithm>
#include <limits>
#include <iterator>
#include <fstream>

#include "../analyzer.hpp"
#include "../scope.hpp"
#include "../configure.hpp"
#include "../system.hpp"
#include "../random.hpp"
#include "block.hpp"
#include "representation.hpp"
#include "controller.hpp"

namespace GA
{

const Analyzer Controller::INIT_VALUE{};
const std::vector<Analyzer> Controller::INIT_VALUES{};

Controller::Controller()
    : mSrcAnalyzer{INIT_VALUE}
    , mAnalyzerPool{INIT_VALUES}
    , mSrcBlock{nullptr}
    , mBlockPool{}
{
}

Controller::~Controller()
{
    delete mSrcBlock;
    for(auto *block : mBlockPool)
        delete block;
}

bool Controller::execute(const Analyzer &src
    , const std::vector<Analyzer> &pool)
{
    mSrcAnalyzer = std::cref(src);
    mAnalyzerPool = std::cref(pool);

    if(!initialize())
        return false;

    Representation result;
    if(!geneticAlgorithm(result))
        return false;
    
    std::cout << "Result:\n"
        "    ";
    result.print();
    outputToFile(Configure::RESULT_FILENAME
        , result);

    debugInfo();

    return true;
}

bool Controller::initialize()
{
    if(!(mSrcBlock = Block::createBlock(mSrcAnalyzer.get().translationUnit()
        , mSrcAnalyzer.get().scope()->id())))
        return false;
    
    for(const auto &analyzer : mAnalyzerPool.get())
    {
        if(!mBlockPool.emplace_back(Block::createBlock(analyzer.translationUnit()
            , analyzer.scope()->id())))
            return false;
    }

    if(!Operation::initialize(mSrcAnalyzer.get().translationUnit()))
        return false;

    return true;
}

bool Controller::geneticAlgorithm(Representation &result)
{
    std::vector<Representation> reps;
    for(std::size_t i{0ull};
        i < Configure::POP_SIZE;
        i++)
    {
        if(auto &&opt{Representation::createRandomRep(mSrcBlock
            , mBlockPool)};
            bool(opt))
            reps.push_back(std::move(opt.value()));
        else
            return false;
    }

    for(std::size_t gen{0ull};
        gen < Configure::MAX_GEN;
        gen++)
    {
        std::vector<Representation> nextReps;
        Scores scores;

        for(std::size_t i{0ull};
            i < reps.size();
            i++)
            scores.emplace_back(fitness(reps[i])
                , i);
        
        std::sort(scores.begin()
            , scores.end()
            , [](const auto &lhs
                , const auto &rhs)
                {return lhs.first > rhs.first;});
        
        result = reps[scores.front().second];
        if(scores.front().first >= Configure::GOAL_SCORE)
            break;
        
        for(std::size_t i{0ull};
            i < Configure::NUM_ELITE;
            i++)
            nextReps.push_back(reps[scores[i].second]);
        
        for(std::size_t i{Configure::NUM_ELITE};
            i < Configure::POP_SIZE;
            i++)
        {
            if(auto &&opt{manipulate(reps
                , scores)};
                bool(opt))
                nextReps.push_back(std::move(opt.value()));
            else
                return false;
        }

        reps.swap(nextReps);
    }

    return true;
}

int Controller::fitness(const Representation &rep) const
{
    rep.print();

    if(!outputToFile(Configure::TEST_FILENAME
        , rep))
        return std::numeric_limits<int>::min();
    
    if(!compile(Configure::TEST_FILENAME))
        return std::numeric_limits<int>::min();
    
    int score{0};
    score += evaluate(Configure::POSITIVE_TEST_PREFIX
        , Configure::NUM_POSITIVE_TEST
        , Configure::POSITIVE_TEST_WEIGHT);
    score += evaluate(Configure::NEGATIVE_TEST_PREFIX
        , Configure::NUM_NEGATIVE_TEST
        , Configure::NEGATIVE_TEST_WEIGHT);

    return score;
}

bool Controller::outputToFile(const std::string &filename
    , const Representation &rep) const
{
    std::shared_ptr<Block> block{mSrcBlock->createBlock(rep)};
    std::shared_ptr<TOKEN::TranslationUnit> tu{block->createTranslationUnit()};

    std::ofstream fstr{filename};
    fstr << TOKEN::str(tu.get())
        << std::endl;
    fstr.close();

    return true;
}

bool Controller::compile(const std::string &filename) const
{
    if(SYSTEM::system(Configure::COMPILER
        , filename
        , "-o"
        , Configure::EXECUTION_NAME
        , "> /dev/null 2>&1")
        != 0)
        return compileError(filename);
    
    return true;
}

bool Controller::evaluate(const std::string &prefix
    , std::size_t number
    , int weight) const
{
    int score{0};
    for(std::size_t i{0ull};
        i < number;
        i++)
    {
        if(SYSTEM::system("sh"
            , Configure::TEST_SCRIPT
            , std::string{"./"} + Configure::EXECUTION_NAME
            , prefix + std::to_string(i))
            == 0)
            score += weight;
    }

    return score;
}

std::optional<Representation> Controller::manipulate(const std::vector<Representation> &reps
    , const Scores &scores) const
{
    Representation rep{reps[select(scores)]};

    if(Configure::ADDING_NEW_OPERATION_PROBABILITY >= RAND.floating())
    {
        auto &&opt{Representation::createRandomRep(mSrcBlock
            , mBlockPool)};
        if(!opt)
            return {std::nullopt};

        if(!rep.merge(mSrcBlock
            , opt.value()))
            return {std::nullopt};
    }
    else
    {
        if(!rep.merge(mSrcBlock
            , reps[select(scores)]))
            return {std::nullopt};
    }

    return rep;
}

std::size_t Controller::select(const Scores &scores) const
{
    Scores sample;
    std::sample(scores.begin()
        , scores.end()
        , std::back_inserter(sample)
        , Configure::TOURNAMENT_SIZE
        , RAND.engine());

    return std::max_element(sample.begin()
        , sample.end()
        , [](const auto &lhs
            , const auto &rhs)
            {return lhs.first > rhs.first;})->second;
}

bool Controller::compileError(const std::string &filename) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: failed to compile.\n"
        "    file: " << filename
        << std::endl;
    
    return false;
}

bool Controller::debugInfo()
{
    std::cout << "=== Identifier list ===\n";
    for(const auto &pair : Analyzer::idMap())
    {
        std::cout << "    {" << pair.first
            << ", "
            << pair.second->key()
            << "},\n";
    }
    
    std::cout << "=== src and ids and statement-id list ===\n";
    for(const auto &pair : Operation::newStatementIds())
    {
        std::cout << "    {src:{";
        for(const auto &i : pair.first.first)
        {
            std::cout << i
                << ", ";
        }
        std::cout << "}, ids:{";
        for(const auto &i : pair.first.second)
        {
            std::cout << i
                << ", ";
        }
        std::cout << "}, id: ";
        std::cout << pair.second
            << "},\n";
    }
    
    std::cout << "=== statement list ===\n";
    for(const auto &pair : Analyzer::statementMap())
    {
        std::cout << "{id: "
            << pair.first
            << ", stat:\n"
            "-------------------\n"
            << std::visit([](const auto &p){return TOKEN::str(p.get());}
                , pair.second)
            << "\n-------------------},\n";
    }

    std::cout << std::flush;
}

}