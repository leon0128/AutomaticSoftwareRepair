#ifndef SIMILARITY_CALCULATOR_HPP
#define SIMILARITY_CALCULATOR_HPP

#include <deque>
#include <memory>
#include <cmath>
#include <valarray>

#include "structure_token_metrics.hpp"

namespace SIM
{

template<class>
class StructureTokenMetrics;

class Calculator
{
private:
    template<class ValueType>
    using STM = StructureTokenMetrics<ValueType>;
    template<class ValueType>
    using STMs = std::deque<std::shared_ptr<STM<ValueType>>>;

public:
    Calculator();

    bool execute(const STMs<std::size_t>&);

    const auto &functionNames() const noexcept
        {return mFunctionNames;}
    const auto &result() const noexcept
        {return mResult;}

private:
    std::shared_ptr<STM<double>> calculateTF(const std::shared_ptr<STM<std::size_t>>&) const;
    std::shared_ptr<STM<double>> calculateIDF(const STMs<std::size_t>&) const;
    std::size_t calculateDL(const std::shared_ptr<STM<std::size_t>>&) const;
    STMs<double> calculateOkapiBM25(const STMs<std::size_t>&) const;
    // result: [0, 1]
    template<class BaseType, class ResultType = double>
    ResultType calculateCosineSimilarity(const std::shared_ptr<STM<BaseType>> &lhs
        , const std::shared_ptr<STM<BaseType>> &rhs) const;

    bool emptyError(const std::string &what) const;

    std::deque<std::string> mFunctionNames;
    std::valarray<std::valarray<double>> mResult;
};

template<class BaseType, class ResultType>
ResultType Calculator::calculateCosineSimilarity(const std::shared_ptr<STM<BaseType>> &lhs
    , const std::shared_ptr<STM<BaseType>> &rhs) const
{
    ResultType numerator{static_cast<ResultType>(0)};
    ResultType denominator{static_cast<ResultType>(0)};

    ResultType lden{static_cast<ResultType>(0)};
    ResultType rden{static_cast<ResultType>(0)};

    for(std::size_t i{0ull};
        i < STM<BaseType>::NUM_OF_ENUM;
        i++)
    {
        numerator
            += static_cast<ResultType>(lhs->array()[i])
                * static_cast<ResultType>(rhs->array()[i]);
        lden += std::pow(static_cast<ResultType>(lhs->array()[i])
            , static_cast<ResultType>(2));
        rden += std::pow(static_cast<ResultType>(rhs->array()[i])
            , static_cast<ResultType>(2));
    }
    denominator = static_cast<ResultType>(std::sqrt(lden) * std::sqrt(rden));

    // result: [-1, 1]
    ResultType result = numerator / denominator;
    // result: [0, 1]
    result = (result + static_cast<ResultType>(1)) / static_cast<ResultType>(2);

    return result;
}

}

#endif