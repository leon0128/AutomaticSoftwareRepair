#include <iostream>
#include <algorithm>
#include <iterator>

#include "configure.hpp"
#include "representation.hpp"
#include "representation_creator.hpp"
#include "calculator.hpp"
#include "controller.hpp"

namespace SIM
{

Controller::Controller()
    : mResults{}
{
}

Controller::~Controller()
{
}

bool Controller::execute(const CodeInformation &target
    , const std::deque<CodeInformation> &pool)
{
    // initialize and 
    bool isSucceessfull{initialize(pool)
        && calculate(target)};

    // test(pool);

    // finalize
    finalize();

    if(Configure::SHOULD_OUTPUT_SIMILARITY_LOG)
        outputSimilarityLog(target, pool);

    outputSpecifiedLog();

    return isSucceessfull;
}

bool Controller::initialize(const std::deque<CodeInformation> &pool)
{
    // priority:
    //  RepCreator > Calculator

    // create and register Rep
    for(auto &&ci : pool)
    {
        if(!RepresentationCreator::createAndRegister(ci.mFilename, ci.mTranslationUnit.get()))
            return false;
    }

    // initialize Calculator
    if(!Calculator::initialize())
        return false;

    return true;
}

bool Controller::calculate(const CodeInformation &target)
{
    using Rep = Representation;
    using RC = RepresentationCreator;

    std::deque<Rep::Element*> reps{RC::create(target.mFilename, target.mTranslationUnit.get())};

    for(auto &&element : reps)
    {
        mResults.push_back(Calculator::calculateSimilarity(element));
        // Calculator::normalize(similarity.back());
    }

    for(auto &&element : reps)
        delete element;

    return true;
}

void Controller::finalize()
{
    Representation::deleteReps();
    Calculator::finalize();
}

void Controller::test(const std::deque<CodeInformation> &pool)
{
    using Rep = Representation;
    using RC = RepresentationCreator;

    std::deque<Rep::Element*> reps;
    for(auto &&ci : pool)
    {
        auto &&tempReps{RC::create(ci.mFilename, ci.mTranslationUnit.get())};
        std::move(tempReps.begin()
            , tempReps.end()
            , std::back_inserter(reps));
    }

    std::deque<std::deque<double>> similarity;

    std::cout << ",";
    for(auto &&element : reps)
    {
        std::cout << element->mFilename << "::" << element->mFunctionName << ",";
        similarity.push_back(Calculator::calculateSimilarity(element));
        Calculator::normalize(similarity.back());
    }
    std::cout << std::endl;

    for(std::size_t i{0ull}; i < similarity.size(); i++)
    {
        std::cout << reps.at(i)->mFilename << "::" << reps.at(i)->mFunctionName << ",";
        auto &&row{similarity.at(i)};

        for(auto &&column : row)
            std::cout << column << ",";
        std::cout << std::endl;
    }

    for(auto &&element : reps)
        delete element;
}

void Controller::outputSimilarityLog(const CodeInformation &target
    , const std::deque<CodeInformation> &pool) const
{
    using RC = RepresentationCreator;

    auto &&targetReps{RC::create(target.mFilename, target.mTranslationUnit.get())};

    std::cout << "similarity-log:\n"
        "    target";
    for(auto &&rep : targetReps)
        std::cout << "," << rep->mFilename << "::" << rep->mFunctionName;
    std::cout << std::endl;

    for(std::size_t i{0ull}; i < mResults.size(); i++)
    {
        auto &&row{mResults.at(i)};
        std::cout << "    "
            << targetReps.at(i)->mFilename
            << "::"
            << targetReps.at(i)->mFunctionName;
    
        for(auto &&column : row)
            std::cout << "," << column;
        std::cout << std::endl;
    }

    for(auto &&rep : targetReps)
        delete rep;
}

void Controller::outputSpecifiedLog() const
{
    
}

}