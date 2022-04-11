#include <cmath>
#include <iostream>
#include <deque>
#include <utility>

#include "structure_token_metrics.hpp"
#include "calculator.hpp"

namespace SIM
{

Calculator::Calculator()
    : mFunctionNames{}
    , mResult{}
{
}

bool Calculator::execute(const STMs<std::size_t> &stms)
{
    auto okapi{calculateOkapiBM25(stms)};

    mResult = std::valarray<std::valarray<double>>(std::valarray<double>(0.0, okapi.size()), okapi.size());
    mFunctionNames = std::deque<std::string>(stms.size());

    for(std::size_t i{0ull}; i < stms.size(); i++)
        mFunctionNames[i] = stms[i]->filename() + "::" + stms[i]->functionName();

    for(std::size_t i{0ull}; i < mResult.size(); i++)
    {
        for(std::size_t j{0ull}; j < mResult[i].size(); j++)
            mResult[i][j] = calculateCosineSimilarity(okapi[i], okapi[j]);
    }

    return true;
}

std::shared_ptr<Calculator::STM<double>> Calculator::calculateTF(const std::shared_ptr<STM<std::size_t>> &src) const
{
    std::shared_ptr<STM<double>> result{new STM<double>{src->filename()
        , src->functionName()}};

    double sum{static_cast<double>(src->array().sum())};

    if(sum == 0ull)
    {
        emptyError("sum of STM is 0. all elements set to 0.\n");
        return result;
    }

    for(std::size_t i{0ull};
        i < src->array().size();
        i++)
        result->array()[i] = static_cast<double>(src->array()[i]) / sum;

    return result;
}

std::shared_ptr<Calculator::STM<double>> Calculator::calculateIDF(const STMs<std::size_t> &stms) const
{
    auto &&numAppearance{[&](std::size_t idx)
        -> double
        {
            std::size_t num{0ull};
            for(const auto &stm : stms)
            {
                if(stm->array()[idx])
                    num++;
            }

            return static_cast<double>(num);
        }};

    std::shared_ptr<STM<double>> result{new STM<double>{}};

    double numFunction{static_cast<double>(stms.size())};

    for(std::size_t i{0ull};
        i < STM<std::size_t>::NUM_OF_ENUM;
        i++)
    {
        double numApp{numAppearance(i)};
        result->array()[i]
            = log((numFunction - numApp + 0.5)
                / (numApp + 0.5));
    }

    return result;
}

std::size_t Calculator::calculateDL(const std::shared_ptr<STM<std::size_t>> &stm) const
{
    return stm->array().sum();
}

Calculator::STMs<double> Calculator::calculateOkapiBM25(const STMs<std::size_t> &stms) const
{
    STMs<double> result;
    for(std::size_t i{0ull};
        i < stms.size();
        i++)
    {
        result.emplace_back(new STM<double>{stms[i]->filename()
            , stms[i]->functionName()});
    }

    std::deque<std::shared_ptr<STM<double>>> tfs;
    for(auto &&stm : stms)
        tfs.push_back(calculateTF(stm));
    
    auto &&idf{calculateIDF(stms)};

    std::valarray<double> dls(0.0, stms.size());
    for(std::size_t i{0ull};
        i < stms.size();
        i++)
        dls[i] = static_cast<double>(calculateDL(stms[i]));
    
    double avgDL{dls.sum() / dls.size()};

    double k{2.0};
    double b{0.75};

    for(std::size_t funcIdx{0ull};
        funcIdx < result.size();
        funcIdx++)
    {
        for(std::size_t tokenIdx{0ull};
            tokenIdx < result[funcIdx]->array().size();
            tokenIdx++)
        {
            result[funcIdx]->array()[tokenIdx]
                = idf->array()[tokenIdx]
                    * (tfs[funcIdx]->array()[tokenIdx] * (k + 1.0))
                    / (tfs[funcIdx]->array()[tokenIdx] + 1.0 * (1.0 - b + b * dls[funcIdx] / avgDL));
        }
    }

    return result;
}

bool Calculator::emptyError(const std::string &what) const
{
    std::cerr << "SIM::Calculator::emptyError()\n"
        << "    what: " << what
        << std::endl;
    
    return false;
}

}