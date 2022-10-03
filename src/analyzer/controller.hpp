#ifndef ANALYZER_CONTROLLER_HPP
#define ANALYZER_CONTROLLER_HPP

#include <deque>
#include <string>

#include "common/token.hpp"

namespace ANALYZER
{

class Controller
{
public:
    Controller();
    ~Controller();

    bool execute();

private:

};

}

#endif