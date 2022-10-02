#ifndef REPAIR_CONTROLLER_HPP
#define REPAIR_CONTROLLER_HPP

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <utility>
#include <deque>

class Analyzer;

namespace REPAIR
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
public:
    // public member function
    Controller();
    ~Controller();

    // use similarity
    bool execute(std::shared_ptr<Analyzer> src
        , const std::vector<std::shared_ptr<Analyzer>> &pool
        , const std::deque<std::deque<double>> &similarity);

    // no use similarity
    bool execute(std::shared_ptr<Analyzer> src
        , const std::vector<std::shared_ptr<Analyzer>> &pool);


private:
    // private member functions
    bool initialize(std::shared_ptr<Analyzer> src
        , const std::vector<std::shared_ptr<Analyzer>> &pool);
    
    std::shared_ptr<REPRESENTATION::Representation> geneticAlgorithm();
    int fitness(const REPRESENTATION::Representation*);
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

    // private member variables
    BLOCK::Block *mBlock;
    Pool mPool;

    std::size_t mNumCreatedFile;
    std::size_t mNumCompilationSucceededFile;
    bool mIsAbleToRepair;
};

}

#endif