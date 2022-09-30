#include <iostream>
#include <algorithm>
#include <iterator>

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

    test(tus);

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

void Controller::test(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>> &tus)
{
    using Rep = Representation;
    using RC = RepresentationCreator;

    std::deque<Rep::Element*> reps;
    for(auto &&[filename, tu] : tus)
    {
        auto &&tempReps{RC::create(filename, tu)};
        std::move(tempReps.begin()
            , tempReps.end()
            , std::back_inserter(reps));
    }

    std::deque<std::deque<double>> similarity;

    for(auto &&element : reps)
    {
        similarity.push_back(Calculator::calculateSimilarity(element));
        Calculator::normalize(similarity.back());
    }

    for(auto &&row : similarity)
    {
        for(auto &&column : row)
            std::cout << column << ",";
        std::cout << std::endl;
    }

    for(auto &&element : reps)
        delete element;
}

}