#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

#include "../system.hpp"
#include "../random.hpp"
#include "../token.hpp"
#include "configure.hpp"
#include "representation.hpp"
#include "controller.hpp"

namespace GA
{

Controller::Controller(const TOKEN::TranslationUnit *tu)
    : mSrc(tu)
    , mSrcBlock(nullptr)
    , mGen()
    , mResult()
{
}

Controller::~Controller()
{
    delete mSrcBlock;
}

bool Controller::execute()
{
    static auto sortComp = [](const std::pair<int, std::size_t> &lhs
        , const std::pair<int, std::size_t> &rhs)
            {return lhs.first > rhs.first;};

    if(!initialize())
        return false;
    
    for(std::size_t gen = 0; gen < Configure::MAX_GEN; gen++)
    {
        std::vector<Representation> nextGen;
        std::vector<std::pair<int, std::size_t>> scores;
        
        for(std::size_t i = 0; i < mGen.size(); i++)
            scores.emplace_back(fitness(mGen[i]), i);

        std::sort(scores.begin()
            , scores.end()
            , sortComp);

        mResult = mGen[scores.front().second];
        if(scores.front().first >= Configure::GOAL_SCORE)
            break;

        for(std::size_t i = 0; i < Configure::NUM_ELITE; i++)
            nextGen.push_back(mGen[scores[i].second]);

        for(std::size_t i = Configure::NUM_ELITE; i < Configure::POP_SIZE; i++)
            nextGen.push_back(manipulate(scores));
    
        mGen.swap(nextGen);
    }

    return true;
}

bool Controller::initialize()
{
    if(Configure::MAX_GEN <= 0
        || Configure::POP_SIZE <= 0
        || Configure::POP_SIZE < Configure::NUM_ELITE
        || (Configure::TOURNAMENT_SIZE <= 0 || Configure::TOURNAMENT_SIZE > Configure::POP_SIZE))
    {
        std::cerr << "GA::Controller error:\n"
            "    what: MAX_GEN or POP_SIZE should have value greater than 0.\n"
            "          NUM_ELITE should have value less than POP_SIZE.\n"
            "          TOURNAMENT_SIZE should have value greater than 0 and less than POP_SIZE.\n"
            "    MAX_GEN: " << Configure::MAX_GEN << "\n"
            "    POP_SIZE: " << Configure::POP_SIZE << "\n"
            "    NUM_ELITE: " << Configure::NUM_ELITE << "\n"
            "    TOURNAMENT_SIZE: " << Configure::TOURNAMENT_SIZE
            << std::endl;
        return false;
    }

    mSrcBlock = createBlock(mSrc);   

    for(std::size_t i = 0; i < Configure::POP_SIZE; i++)
        mGen.push_back(createRandomRep(mSrcBlock));

    return true;
}

int Controller::fitness(const Representation &rep) const
{
    Block *block = createBlock(rep);
    TOKEN::TranslationUnit *tu = createTranslationUnit(block);

    std::string filename = Configure::TEST_NAME;
    filename += ".c";

    std::fstream fstr(filename, std::ios::out);
    if(fstr.is_open())
        fstr << TOKEN::str(tu) << std::endl;
    else
    {
        std::cerr << "GA::Controller warning:\n"
            "    what: failed to open file.\n"
            "    file: " << filename
            << std::endl;
        return std::numeric_limits<decltype(Configure::GOAL_SCORE)>::min();
    }

    if(SYSTEM::system(Configure::COMPILER, filename, "-o", Configure::TEST_NAME) != 0)
    {
        std::cerr << "GA::Controller warning:\n"
            "    what: failed to compile test code.\n"
            << std::flush;
        return std::numeric_limits<decltype(Configure::GOAL_SCORE)>::min();
    }

    int score = 0;
    for(int i = 0; i < Configure::NUM_POSITIVE; i++)
    {
        if(SYSTEM::system("sh"
            , Configure::TEST_SCRIPT
            , std::string("./") + Configure::TEST_NAME
            , Configure::POSITIVE_TEST_PREFIX + std::to_string(i)) == 0)
            score += Configure::POSITIVE_WEIGHT;
    }
    for(int i = 0; i < Configure::NUM_NEGATIVE; i++)
    {
        if(SYSTEM::system("sh"
            , Configure::TEST_SCRIPT
            , std::string("./") + Configure::TEST_NAME
            , Configure::NEGATIVE_TEST_PREFIX + std::to_string(i)) == 0)
            score += Configure::NEGATIVE_WEIGHT;
    }

    delete block;
    delete tu;

    return score;
}

Representation Controller::manipulate(const std::vector<std::pair<int, std::size_t>> &scores) const
{
    Representation ret;

    if(Configure::NEW_OPERATION_PROBABILITY >= RAND.floating())
    {
        ret = mGen[select(scores)];
        ret.append(createRandomRep(ret.block, 1));
    }
    else
    {
        ret = mGen[select(scores)];
        ret.append(mGen[select(scores)]);
    }

    return ret;
}

std::size_t Controller::select(const std::vector<std::pair<int, std::size_t>> &scores) const
{
    std::vector<std::pair<int, std::size_t>> sample;
    std::sample(scores.begin()
        , scores.end()
        , std::back_inserter(sample)
        , Configure::TOURNAMENT_SIZE
        , RAND.engine());
    return std::max_element(sample.begin()
        , sample.end()
        , [](auto &&l, auto &&r){return l.first > r.first;})->second;
}

}