#ifndef GA_CONTROLLER_HPP
#define GA_CONTROLLER_HPP

#include <functional>
#include <vector>

class Analyzer;

namespace GA
{

class Block;

class Controller
{
private:
    static const Analyzer INIT_VALUE;
    static const std::vector<Analyzer> INIT_VALUES;

public:
    Controller();
    ~Controller();

    bool execute(const Analyzer &src
        , const std::vector<Analyzer> &pool);

private:
    bool initialize();

    std::reference_wrapper<const Analyzer> mSrcAnalyzer;
    std::reference_wrapper<const std::vector<Analyzer>> mAnalyzerPool;

    const Block *mSrcBlock;
    std::vector<const Block*> mBlockPool;
};

}

#endif