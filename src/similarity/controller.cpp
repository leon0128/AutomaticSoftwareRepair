#include "../token.hpp"
#include "representation.hpp"
#include "representation_creator.hpp"
#include "calculator.hpp"
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
    // initialize and 
    bool isSucceessfull{initialize(tus)};



    // finalize
    finalize();

    return isSucceessfull;
}

bool Controller::initialize(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>> &tus)
{
    // priority:
    //  RepCreator > Calculator

    // create and register Rep
    for(auto &&[filename, tu] : tus)
    {
        if(!RepresentationCreator::createAndRegister(filename, tu))
            return false;
    }

    // initialize Calculator
    if(!Calculator::initialize())
        return false;

    return true;
}

void Controller::finalize()
{
    Representation::deleteReps();
    Calculator::finalize();
}

}