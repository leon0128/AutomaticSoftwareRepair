#include <cmath>
#include <limits>
#include <iostream>
#include <algorithm>

#include "configure.hpp"
#include "utility/output.hpp"
#include "calculator.hpp"

namespace SIM
{

bool Calculator::initialize()
{
    if(!calculateAndRegisterInfo())
        return false;

    return true;
}

void Calculator::finalize()
{
    deleteInfo();
}

std::deque<double> Calculator::calculateSimilarity(const Representation::Element *repE)
{
    using Rep = Representation;

    // return value (use copy elision)
    std::deque<double> similarity(Rep::reps().size(), 0.0);

    // query reduction
    std::array<std::deque<std::size_t>, Rep::castTag(Rep::Tag::SIZE_OF_TAG)> indicesToUse
        {calculateIndicesToUse(Rep::Tag::ORIGINAL, repE->mReps.at(Rep::castTag(Rep::Tag::ORIGINAL)).tokens())
            , calculateIndicesToUse(Rep::Tag::TYPE1, repE->mReps.at(Rep::castTag(Rep::Tag::TYPE1)).tokens())
            , calculateIndicesToUse(Rep::Tag::TYPE2, repE->mReps.at(Rep::castTag(Rep::Tag::TYPE2)).tokens())
            , calculateIndicesToUse(Rep::Tag::TYPE3, repE->mReps.at(Rep::castTag(Rep::Tag::TYPE3)).tokens())};
    // test
    for(auto &&deque : indicesToUse)
    {
        if(deque.empty())
            return std::deque<double>(Rep::reps().size(), -1.0);
    }

    // score calculation
    for(std::size_t docIdx{0ull}; docIdx < Rep::reps().size(); docIdx++)
    {
        similarity.at(docIdx)
            = calculateScoreSiamese(repE
                , indicesToUse
                , docIdx);
    }

    return similarity;
}

bool Calculator::normalize(std::deque<double> &scores)
{
    double maxScore{*std::max_element(scores.begin(), scores.end())};

    if(std::fabs(maxScore - 0.0) < std::numeric_limits<double>::epsilon())
        return normalizationError("max score is 0.");

    for(auto &&score : scores)
        score = score / maxScore;

    return true;
}

bool Calculator::calculateAndRegisterInfo()
{
    // priority:
    //  tf > df > idf > boost
    if(!calculateAndRegisterTF()
        || !calculateAndRegisterDF()
        || !calculateAndRegisterIDF()
        || !calculateAndRegisterBoost())
        return false;

    return true;
}

bool Calculator::calculateAndRegisterTF()
{
    for(std::size_t docIdx{0ull}; docIdx < Representation::reps().size(); docIdx++)
    {
        for(std::size_t repIdx{0ull}; repIdx < Representation::castTag(Representation::Tag::SIZE_OF_TAG); repIdx++)
        {
            auto &&termMap{mInfo.at(repIdx)};

            // calculate number of term
            for(auto &&term : Representation::reps().at(docIdx)->mReps.at(repIdx).tokens())
            {
                // if no map contains term,
                // add Element and create term-freq(Element::mTF) array. 
                if(!termMap.contains(term))
                    termMap.emplace(term, new Element{std::deque<double>(Representation::reps().size(), 0.0)});

                termMap.at(term)->mTF.at(docIdx) += 1.0;
            }

            // calculate term-freq value from number of term.
            for(auto &&[term, termElement] : termMap)
                termElement->mTF.at(docIdx) = std::sqrt(termElement->mTF.at(docIdx));
        }
    }

    return true;
}

bool Calculator::calculateAndRegisterDF()
{
    for(auto &&map : mInfo)
    {
        for(auto &&[term, element] : map)
        {
            for(auto &&tf : element->mTF)
            {
                if(std::fabs(tf - 0.0) >= std::numeric_limits<double>::epsilon())
                    element->mDF++;
            }
        }
    }

    return true;
}

bool Calculator::calculateAndRegisterIDF()
{
    double docSize{static_cast<double>(Representation::reps().size())};

    for(auto &&map : mInfo)
    {
        // calculate invert-doc-freq from doc-freq
        for(auto &&[term, element] : map)
            element->mIDF = 1.0 + std::log(docSize / (static_cast<double>(element->mDF) + 1.0));
    }

    return true;
}

bool Calculator::calculateAndRegisterBoost()
{
    for(std::size_t repIdx{0ull}; repIdx < Representation::castTag(Representation::Tag::SIZE_OF_TAG); repIdx++)
    {
        // calculate boost value.
        double boost{0.0};
        switch(repIdx)
        {
            case(Representation::castTag(Representation::Tag::ORIGINAL)):
                boost = static_cast<double>(Configure::SIM_ORIGINAL);
                break;
            case(Representation::castTag(Representation::Tag::TYPE1)):
                boost = static_cast<double>(Configure::SIM_TYPE1);
                break;
            case(Representation::castTag(Representation::Tag::TYPE2)):
                boost = static_cast<double>(Configure::SIM_TYPE2);
                break;
            case(Representation::castTag(Representation::Tag::TYPE3)):
                boost = static_cast<double>(Configure::SIM_TYPE3);
                break;
 
            default:;
        }

        // assign boost value to Element
        for(auto &&[term, element] : mInfo.at(repIdx))
            element->mBoost = boost;
    }

    return true;
}

std::deque<std::size_t> Calculator::calculateIndicesToUse(Representation::Tag typeTag
    , const std::deque<std::string> &tokens)
{
    // return value (use copy elision)
    std::deque<std::size_t> idxToUse;

    auto &&termMap{mInfo.at(Representation::castTag(typeTag))};
    
    // threshold: = capacity * number of documents
    double threshold{Configure::SIM_CAPACITY * static_cast<double>(Representation::reps().size())};

    for(std::size_t idx{0ull}; idx < tokens.size(); idx++)
    {
        if(!termMap.contains(tokens[idx]))
            continue;
        
        if(static_cast<double>(termMap.at(tokens[idx])->mDF) <= threshold)
            idxToUse.push_back(idx);
    }

    if(idxToUse.empty())
        reductionWarning();

    return idxToUse;
}

double Calculator::calculateScoreSiamese(const Representation::Element *queries
    , const std::array<std::deque<std::size_t>, Representation::castTag(Representation::Tag::SIZE_OF_TAG)> &idxToUseArray
    , std::size_t docIdx)
{
    using Rep = Representation;

    double score{0.0};
    for(std::size_t tag{0ull}; tag < Rep::castTag(Rep::Tag::SIZE_OF_TAG); tag++)
    {
        score
            += calculateScore(Rep::Tag{tag}
                , queries->mReps.at(tag).tokens()
                , idxToUseArray.at(tag)
                , docIdx);
    }

    return score;
}

double Calculator::calculateScore(Representation::Tag tag
    , const std::deque<std::string> &query
    , const std::deque<std::size_t> &idxToUse
    , std::size_t docIdx)
{
    double score{0.0};

    for(auto &&termIdx : idxToUse)
    {
        score
            += calculateTF(tag, query.at(termIdx), docIdx)
                * calculateIDF(tag, query.at(termIdx))
                * calculateBoost(tag, query.at(termIdx));
    }

    score
        *= calculateNorm(tag, docIdx)
            * calculateQueryNorm(tag, query, idxToUse)
            * calculateCoord(tag, query, idxToUse, docIdx);

    return score;
}

double Calculator::calculateTF(Representation::Tag tag
    , const std::string &term
    , std::size_t docIdx)
{
    using Rep = Representation;

    double score{0.0};

    auto &&map{mInfo.at(Rep::castTag(tag))};
    if(map.contains(term))
        score = map.at(term)->mTF.at(docIdx);
    else
        score = 0.0;

    return score;
}

double Calculator::calculateIDF(Representation::Tag tag
    , const std::string &term)
{
    using Rep = Representation;

    double score{0.0};

    auto &&map{mInfo.at(Rep::castTag(tag))};
    if(map.contains(term))
        score = map.at(term)->mIDF;
    else
        score = 0.0;

    return score;
}

double Calculator::calculateBoost(Representation::Tag tag
    , const std::string &term)
{
    using Rep = Representation;

    double score{0.0};

    auto &&map{mInfo.at(Rep::castTag(tag))};
    if(map.contains(term))
        score = map.at(term)->mBoost;
    else
        score = 0.0;

    return score;
}

double Calculator::calculateNorm(Representation::Tag tag
    , std::size_t docIdx)
{
    using Rep = Representation;

    return static_cast<double>(Rep::reps().at(docIdx)->mReps.at(Rep::castTag(tag)).tokens().size());
}

double Calculator::calculateQueryNorm(Representation::Tag tag
    , const std::deque<std::string> &query
    , const std::deque<std::size_t> &idxToUse)
{
    double sumWeight{0.0};
    for(auto &&idx : idxToUse)
        sumWeight += std::pow(calculateIDF(tag, query[idx]), 2.0);

    if(std::fabs(sumWeight - 0.0) >= std::numeric_limits<double>::epsilon())
        return 1.0 / std::sqrt(sumWeight);
    else
        return 0.0;
}

double Calculator::calculateCoord(Representation::Tag tag
    , const std::deque<std::string> &query
    , const std::deque<std::size_t> &idxToUse
    , std::size_t docIdx)
{
    double querySize{static_cast<double>(idxToUse.size())};
    double numContainedTerm{0.0};

    for(auto &&termIdx : idxToUse)
    {
        if(std::fabs(calculateTF(tag, query[termIdx], docIdx) - 0.0) >= std::numeric_limits<double>::epsilon())
            numContainedTerm += 1.0;
    }

    return numContainedTerm / querySize;
}

void Calculator::deleteInfo()
{
    for(auto &&map : mInfo)
    {
        for(auto &&[term, element] : map)
            delete element;
    
        map.clear();
    }
}

bool Calculator::reductionWarning()
{
    std::cerr << OUTPUT::charYellowCode
        << "SIM::Calculator::reductionWarning():\n"
        << OUTPUT::resetCode
        << "    what: indices to use is empty.\n"
        << "        reduction threshold should be changed.\n"
        << std::flush;
    
    return false;
}

bool Calculator::normalizationError(const std::string &what)
{
    std::cerr << OUTPUT::charRedCode
        << "SIM::Calculator::normalizationError():\n"
        << OUTPUT::resetCode
        << "    what: " << what
        << std::endl;
    
    return false;
}

}