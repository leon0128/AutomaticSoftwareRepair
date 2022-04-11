#ifndef GA_CONTROLLER_HPP
#define GA_CONTROLLER_HPP

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <utility>

class Analyzer;

namespace GA
{

namespace BLOCK
{
    class Block;
}

using Pool = std::vector<const BLOCK::Block*>;

namespace REPRESENTATION
{
    class Representation;
}

namespace OPERATION
{
    class Operation;
}

class Controller;

class Controller
{
private:
    BLOCK::Block *mBlock;
    Pool mPool;

public:
    Controller();
    ~Controller();

    bool execute(std::shared_ptr<Analyzer> src
        , const std::vector<std::shared_ptr<Analyzer>> &pool);

private:
    bool initialize(std::shared_ptr<Analyzer> src
        , const std::vector<std::shared_ptr<Analyzer>> &pool);
    
    std::shared_ptr<REPRESENTATION::Representation> geneticAlgorithm() const;
    int fitness(const REPRESENTATION::Representation*) const;
    bool outputToFile(const std::string &filename
        , const REPRESENTATION::Representation*) const;
    bool compile(const std::string &filename) const;
    std::shared_ptr<REPRESENTATION::Representation> manipulate(const std::vector<std::shared_ptr<REPRESENTATION::Representation>>&
        , const std::vector<std::pair<int, std::size_t>> &scores) const;
    std::size_t select(const std::vector<std::pair<int, std::size_t>> &scores) const;

    bool compilingError(const std::string &filename) const;
    bool manipulationError(const std::string &what) const;
    bool geneticAlgorithmError(const std::string &what) const;
    bool outputError(const std::string &filename) const;
};

}

#endif