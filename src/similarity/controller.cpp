#include "../token.hpp"
#include "representation.hpp"
#include "controller.hpp"

namespace SIM
{

Controller::Controller()
{
}

Controller::~Controller()
{
}

bool Controller::execute(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>> &tus)
{
    

    Representation::deleteReps();
    return true;
}

}