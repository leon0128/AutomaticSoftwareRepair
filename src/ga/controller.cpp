#include <iostream>

#include "../analyzer.hpp"
#include "../scope.hpp"
#include "block.hpp"
#include "controller.hpp"

namespace GA
{

const Analyzer Controller::INIT_VALUE{};
const std::vector<Analyzer> Controller::INIT_VALUES{};

Controller::Controller()
    : mSrcAnalyzer{INIT_VALUE}
    , mAnalyzerPool{INIT_VALUES}
    , mSrcBlock{nullptr}
    , mBlockPool{nullptr}
{
}

Controller::~Controller()
{
}

bool Controller::execute(const Analyzer &src
    , const std::vector<Analyzer> &pool)
{
    mSrcAnalyzer = std::cref(src);
    mAnalyzerPool = std::cref(pool);

    if(initialize())
        return false;

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

    return true;
}

}