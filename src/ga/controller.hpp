#ifndef GA_CONTROLLER_HPP
#define GA_CONTROLLER_HPP

#include <vector>
#include <functional>
#include <utility>
#include <string>

class Analyzer;

namespace GA
{

class Block;
class Representation;

class Controller
{
private:
    using Scores = std::vector<std::pair<int
        , std::size_t>>;

    static const Analyzer INIT_VALUE;
    static const std::vector<Analyzer> INIT_VALUES;

public:
    Controller();
    ~Controller();

    bool execute(const Analyzer &source
        , const std::vector<Analyzer> &pool);

private:
    bool initialize();
    bool geneticAlgorithm(Representation&);
    int fitness(const Representation&) const;
    bool outputToFile(const std::string&
        , const Representation&) const;
    bool compile(const std::string&) const;
    int evaluate(const std::string &prefix
        , std::size_t num
        , int weight) const;

    bool manipulate(const std::vector<Representation>&
        , const Scores&
        , Representation&);
    std::size_t select(const Scores&) const;

    bool openError(const std::string&) const;
    bool compileError(const std::string&) const;

    std::reference_wrapper<const Analyzer> mSrcAnalyzer;
    std::reference_wrapper<const std::vector<Analyzer>> mAnalyzerPool;

    const Block *mSrcBlock;
    std::vector<const Block*> mBlockPool;
};

}



#endif