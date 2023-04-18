#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <vector>

#include <map>
#include <functional>
#include <tuple>

#include "utility/output.hpp"
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

    test(pool);

    // finalize
    finalize();

    if(Configure::SHOULD_OUTPUT_SIMILARITY_LOG)
        outputSimilarityLog(target, pool);

    outputSpecifiedLog();

    return false;
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

    std::vector<double> thresholds;
    std::vector<double> maps;
    std::vector<double> errors;
    thresholds.reserve(101ull);
    maps.reserve(101ull);
    errors.reserve(101ull);

    for(int i{0}; i <= 100; i++)
    {
        Configure::SIM_CAPACITY = static_cast<double>(i) / 100.0;

        std::deque<std::deque<double>> similarity;
        for(auto &&element : reps)
            similarity.push_back(Calculator::calculateSimilarity(element));

        std::map<std::string, std::size_t> contestCountMap;
        std::vector<std::vector<std::pair<std::size_t, double>>> rankedContests(reps.size()
            , std::vector<std::pair<std::size_t, double>>(reps.size()));

        for(std::size_t i{0ull}; i < similarity.size(); i++)
        {
            if(!similarity[i].empty()
                && similarity[i].front() > -0.5)
            {
                std::string contestName{reps.at(i)->mFilename.substr(5ull, 6ull)};
                if(contestCountMap.contains(contestName))
                    contestCountMap.at(contestName)++;
                else
                    contestCountMap.emplace(contestName, 1ull);
            }

            for(std::size_t j{0ull}; j < similarity.size(); j++)
                rankedContests[i][j] = std::make_pair(j, similarity[i][j]);

            std::sort(rankedContests[i].begin()
                , rankedContests[i].end()
                , [](const auto &lhs, const auto &rhs){return lhs.second > rhs.second;});
        }

        double map{0.0};
        std::size_t errorCount{0ull};
        for(std::size_t rowIdx{0ull}; rowIdx < rankedContests.size(); rowIdx++)
        {
            if(!rankedContests[rowIdx].empty()
                && rankedContests[rowIdx].front().second < -0.5)
            {
                errorCount++;
                continue;
            }

            std::string contestName{reps.at(rowIdx)->mFilename.substr(5ull, 6ull)};

            double sumPrecision{0.0};
            double tpCount{0.0};
            std::size_t sameContestCount{contestCountMap.at(contestName)};

            for(std::size_t columnIdx{0ull}; columnIdx < sameContestCount; columnIdx++)
            {
                if(contestName == reps.at(rankedContests[rowIdx][columnIdx].first)->mFilename.substr(5ull, 6ull))
                    tpCount += 1.0;

                sumPrecision += tpCount / (static_cast<double>(columnIdx) + 1.0);
            }

            double averagePrecision{sumPrecision / static_cast<double>(sameContestCount)};
            map += averagePrecision;
        }

        if(errorCount != rankedContests.size())
            map /= static_cast<double>(rankedContests.size() - errorCount);

        thresholds.push_back(Configure::SIM_CAPACITY);
        maps.push_back(map);
        errors.push_back(static_cast<double>(errorCount) / static_cast<double>(similarity.size()));
    }

    std::cout << "threshold";
    for(auto &&d : thresholds)
        std::cout << "," << std::fixed << std::setprecision(2) << d;
    std::cout << "\nMAP";
    for(auto &&d : maps)
        std::cout << "," << std::fixed << std::setprecision(4) << d;
    std::cout << "\nerror";
    for(auto &&d : errors)
        std::cout << "," << std::fixed << std::setprecision(4) << d;
    std::cout << std::endl;

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