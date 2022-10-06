#include "configure.hpp"
#include "repairer.hpp"
#include "controller.hpp"

namespace REPAIR
{

Controller::Controller()
{
}

Controller::~Controller()
{
}

bool Controller::execute(const CodeInformation &target
    , const std::deque<CodeInformation> &pool
    , const std::optional<std::deque<std::deque<double>>> &similarity)
{
    Repairer repairer;
    if(!repairer.execute(target, pool, similarity))
        return false;

    if(!repairer.outputResult(Configure::RESULT_FILENAME))
        return false;

    return true;
}

}