#include <iostream>
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

    std::deque<std::deque<double>> similarity;
    for(auto &&element : reps)
        similarity.push_back(Calculator::calculateSimilarity(element));

    std::map<std::string, std::size_t> contestCountMap;
    std::vector<std::vector<std::pair<std::size_t, double>>> rankedContests(reps.size()
        , std::vector<std::pair<std::size_t, double>>(reps.size()));

    for(std::size_t i{0ull}; i < similarity.size(); i++)
    {
        std::string contestName{reps.at(i)->mFilename.substr(5ull, 6ull)};
        if(contestCountMap.contains(contestName))
            contestCountMap.at(contestName)++;
        else
            contestCountMap.emplace(contestName, 1ull);

        for(std::size_t j{0ull}; j < similarity.size(); j++)
            rankedContests[i][j] = std::make_pair(j, similarity[i][j]);

        std::sort(rankedContests[i].begin()
            , rankedContests[i].end()
            , [](const auto &lhs, const auto &rhs){return lhs.second > rhs.second;});
    }

    double map{0.0};
    std::map<std::string, double> mapMap;
    for(std::size_t rowIdx{0ull}; rowIdx < rankedContests.size(); rowIdx++)
    {
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

        mapMap.at(contestName) += averagePrecision;
            
    }
    map /= static_cast<double>(rankedContests.size());

    double mmr{0.0};
    for(std::size_t rowIdx{0ull}; rowIdx < rankedContests.size(); rowIdx++)
    {
        std::string contestName{reps[rowIdx]->mFilename.substr(5ull, 6ull)};
        std::size_t rank{0ull};
        while(contestName != reps[rankedContests[rowIdx][rank].first]->mFilename.substr(5ull, 6ull))
            rank++;
        mmr += 1.0 / (static_cast<double>(rank) + 1.0);
    }
    mmr /= static_cast<double>(rankedContests.size());

    std::cout << "MAP: " << map << std::endl;
    std::cout << "MMR: " << mmr << std::endl;

    // for(std::size_t rowIndex{0ull}; rowIndex < similarity.size(); rowIndex++)
    // {
    //     auto &&row{similarity.at(rowIndex)};
    //     rankedDeque.emplace_back(reps.at(rowIndex)->mFilename + "::" + reps.at(rowIndex)->mFunctionName
    //         , std::deque<std::tuple<double, std::string, std::string>>());
    //     for(std::size_t columnIndex{0ull}; columnIndex < row.size(); columnIndex++)
    //     {
    //         rankedDeque.back().second.emplace_back(std::make_tuple(row.at(columnIndex)
    //             , reps.at(columnIndex)->mFilename.substr(5ull, 6ull)
    //             , reps.at(columnIndex)->mFilename + "::" + reps.at(columnIndex)->mFunctionName));
    //     }

    //     std::sort(rankedDeque.back().second.begin()
    //         , rankedDeque.back().second.end()
    //         , [](auto &&lhs, auto &&rhs){return std::get<0>(lhs) > std::get<0>(rhs);});
    // }

    // std::deque<std::pair<std::string, std::deque<double>>> averages;
    // for(auto &&[functionName, deque] : rankedDeque)
    // {
    //     std::map<std::string, std::size_t> rankSumMap;
    //     for(std::size_t i{0ull}; i < deque.size(); i++)
    //     {
    //         auto &&[sim, contest, function]{deque.at(i)};
    //         if(!rankSumMap.contains(contest))
    //             rankSumMap.emplace(contest, 0ull);
    //         rankSumMap.at(contest) += i + 1ull;
    //     }
    //     averages.emplace_back(functionName, std::deque<double>());
    //     for(auto &&[contest, rankSum] : rankSumMap)
    //         averages.back().second.emplace_back(static_cast<double>(rankSum) / static_cast<double>(contestCountMap.at(contest)));
    // }

    // std::cout << "target";
    // for(auto &&[contest, count] : contestCountMap)
    //     std::cout << "," << contest;
    // std::cout << std::endl;
    // for(auto &&[function, average] : averages)
    // {
    //     std::cout << function;
    //     for(auto &&avg : average)
    //         std::cout << "," << avg;
    //     std::cout << std::endl;
    // }

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