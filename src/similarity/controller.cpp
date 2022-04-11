#include <memory>
#include <iostream>
#include <utility>

#include "../utility/output.hpp"
#include "structure_token_metrics.hpp"
#include "calculator.hpp"
#include "token_metricer.hpp"
#include "controller.hpp"

namespace SIM
{

Controller::Controller()
{
}

bool Controller::execute(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>> &tus)
{
    TokenMetricer tm;

    for(const auto &tu : tus)
    {
        if(!tm.execute(tu.first, tu.second))
            return false;
    }

    Calculator calculator;
    if(!calculator.execute(tm.stms()))
        return false;

    if(!outputCSV(calculator.functionNames(), calculator.result()))
        return false;

    return true;
}

bool Controller::outputCSV(const std::deque<std::string> &functionNames
    , const std::valarray<std::valarray<double>> &result) const
{
    std::ostream &stream{std::cout};

    for(const auto &s : functionNames)
        stream << ',' << s;
    stream << '\n';

    for(std::size_t i{0ull}; i < functionNames.size(); i++)
    {
        stream << functionNames[i];
        for(const auto &d : result[i])
            stream << ',' << d;
        stream << '\n';
    }

    return true;
}

}