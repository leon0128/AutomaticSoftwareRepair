#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>

#include "../system.hpp"
#include "../random.hpp"
#include "../analyzer.hpp"
#include "../configure.hpp"
#include "representation.hpp"
#include "controller.hpp"

namespace GA
{

const Analyzer Controller::INIT_VALUE{};
const std::vector<Analyzer> Controller::INIT_VALUES{};

Controller::Controller()
    : mSrcAnalyzer{std::cref(INIT_VALUE)}
    , mAnalyzerPool{std::cref(INIT_VALUES)}
    , mSrcBlock{nullptr}
    , mBlockPool{}
{
}

Controller::~Controller()
{
    delete mSrcBlock;
    for(auto &&block : mBlockPool)
        delete block;
}

bool Controller::execute(const Analyzer &source
    , const std::vector<Analyzer> &pool)
{
    mSrcAnalyzer = std::cref(source);
    mAnalyzerPool = std::cref(pool);

    if(!initialize())
        return false;

    Representation result;
    if(!geneticAlgorithm(result))
        return false;

    result.print();

    return true;
}

bool Controller::initialize()
{
    if(!(mSrcBlock = createBlock(mSrcAnalyzer.get().translationUnit())))
        return false;
    
    for(const auto &analyzer : mAnalyzerPool.get())
    {
        if(!mBlockPool.emplace_back(createBlock(analyzer.translationUnit())))
            return false;
    }
    
    return true;
}

bool Controller::geneticAlgorithm(Representation &rep)
{
    std::vector<Representation> reps;
    for(std::size_t i{0};
        i < Configure::POP_SIZE;
        i++)
        reps.push_back(createRandomRep(mSrcBlock));
    
    for(std::size_t gen{0};
        gen < Configure::MAX_GEN;
        gen++)
    {
        std::vector<Representation> nextReps;
        Scores scores;

        for(std::size_t i{0};
            i < reps.size();
            i++)
        {
            auto &&pair{scores.emplace_back(fitness(reps[i]), i)};
        }

        std::sort(scores.begin()
            , scores.end()
            , [](const auto &lhs
                , const auto &rhs)
                {return lhs.first > rhs.first;});
        
        rep = reps[scores.front().second];
        if(scores.front().first >= Configure::GOAL_SCORE)
            break;
        
        for(std::size_t i{0};
            i < Configure::NUM_ELITE;
            i++)
            nextReps.push_back(reps[scores[i].second]);
        
        for(std::size_t i{Configure::NUM_ELITE};
            i < Configure::POP_SIZE;
            i++)
        {
            nextReps.emplace_back();
            if(!manipulate(reps
                , scores
                , nextReps.back()))
                return false;
        }

        reps.swap(nextReps);
    }

    return true;
}

int Controller::fitness(const Representation &rep) const
{
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
    std::shared_ptr<Block> block{createBlock(rep)};
    if(!block)
        return false;

    std::shared_ptr<TOKEN::TranslationUnit> translationUnit{createTranslationUnit(block.get())};
    if(!translationUnit)
        return false;
    
    std::fstream fstr{filename
        , std::ios::out};
    if(!fstr.is_open())
        return openError(filename);
    
    fstr << TOKEN::str(translationUnit.get())
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

int Controller::evaluate(const std::string &prefix
    , std::size_t num
    , int weight) const
{
    int score{0};
    for(std::size_t i{0ull};
        i < num;
        i++)
    {
        if(SYSTEM::system("sh"
            , Configure::TEST_SCRIPT
            , std::string{"./"} + Configure::EXECUTION_NAME
            , prefix + std::to_string(i)) == 0)
            score += weight;
    }

    return score;
}

bool Controller::manipulate(const std::vector<Representation> &reps
    , const Scores &scores
    , Representation &rep)
{
    rep = reps[select(scores)];

    if(Configure::ADDING_NEW_OPERATION_PROBABILITY >= RAND.floating())
        rep.append(createRandomRep(rep.block));
    else
        rep.append(reps[select(scores)]);
    
    return true;
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

bool Controller::openError(const std::string &filename) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: failed to open file.\n"
        "    file: " << filename
        << std::endl;
    return false;
}

bool Controller::compileError(const std::string &filename) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: failed to compile.\n"
        "    file: " << filename
        << std::endl;
    return false;
}

}