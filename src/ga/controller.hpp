#ifndef GA_CONTROLLER_HPP
#define GA_CONTROLLER_HPP

#include <functional>
#include <vector>
#include <utility>
#include <optional>
#include <string>

class Analyzer;

namespace GA
{

class Block;
class Representation;

class Controller
{
private:
    using Scores = std::vector<std::pair<int, std::size_t>>;

    static const Analyzer INIT_VALUE;
    static const std::vector<Analyzer> INIT_VALUES;

public:
    Controller();
    ~Controller();

    bool execute(const Analyzer &src
        , const std::vector<Analyzer> &pool);

private:
    bool initialize();
    // return.first : genetic algorithm is successed.
    // return.second : result is found.
    std::pair<bool, bool> geneticAlgorithm(Representation &result);
    int fitness(const Representation&) const;
    bool outputToFile(const std::string &filename
        , const Representation&) const;
    bool compile(const std::string &filename) const;
    int evaluate(const std::string &prefix
        , std::size_t number
        , int weight) const;

    std::optional<Representation> manipulate(const std::vector<Representation>&
        , const Scores&) const;
    std::size_t select(const Scores&) const;

    bool compileError(const std::string &filename) const;

    static bool debugInfo();

    std::reference_wrapper<const Analyzer> mSrcAnalyzer;
    std::reference_wrapper<const std::vector<Analyzer>> mAnalyzerPool;

    const Block *mSrcBlock;
    std::vector<const Block*> mBlockPool;
};

}

#endif