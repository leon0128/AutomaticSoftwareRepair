#include <iostream>

#include "../analyzer.hpp"
#include "representation.hpp"
#include "controller.hpp"

namespace GA
{

Controller::Controller()
    : mSrcBlock{nullptr}
    , mBlockPool{nullptr}
{
}

Controller::~Controller()
{
    delete mSrcBlock;
    for(auto &&b : mBlockPool)
        delete b;
}

bool Controller::execute(const Analyzer &source
    , const std::vector<Analyzer> &pool)
{
    
}

}