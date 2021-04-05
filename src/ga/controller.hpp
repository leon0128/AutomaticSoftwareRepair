#ifndef GA_CONTROLLER_HPP
#define GA_CONTROLLER_HPP

#include <vector>

class Analyzer;

namespace GA
{

class Block;

class Controller
{
public:
    Controller();
    ~Controller();

    bool execute(const Analyzer &source
        , const std::vector<Analyzer> &pool);

private:
    Block *mSrcBlock;
    std::vector<Block*> mBlockPool;
};

}



#endif