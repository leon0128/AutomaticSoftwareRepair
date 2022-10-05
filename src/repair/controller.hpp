#ifndef REPAIR_CONTROLLER_HPP
#define REPAIR_CONTROLLER_HPP

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <utility>
#include <deque>
#include <optional>

#include "common/define.hpp"
#include "common/token.hpp"

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

    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;

    // if similarity is std::nullopt, similarity is not used.
    bool execute(const CodeInformation &target
        , const std::deque<CodeInformation> &pool
        , const std::optional<std::deque<std::deque<double>>> &similarity);

private:
};

}

#endif