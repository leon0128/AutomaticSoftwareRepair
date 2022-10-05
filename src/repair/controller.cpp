#include <limits>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <iomanip>

#include "utility/file.hpp"
#include "utility/system.hpp"
#include "utility/random.hpp"
#include "configure.hpp"
#include "analyzer/analyzer.hpp"
#include "common//scope.hpp"
#include "common/time_measurer.hpp"
#include "block.hpp"
#include "representation.hpp"
#include "operation.hpp"
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
    return true;
}

}