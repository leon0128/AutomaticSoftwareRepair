#include "../token.hpp"
#include "representation.hpp"
#include "representation_creator.hpp"
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
    if(!createAndRegisterReps(tus))
        return false;

    Representation::deleteReps();
    return true;
}

bool Controller::createAndRegisterReps(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>> &tus)
{
    for(auto &&[filename, tu] : tus)
    {
        if(!RepresentationCreator::createAndRegister(filename, tu))
            return false;
    }

    return true;
}

}