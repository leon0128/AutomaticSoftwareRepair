#ifndef SIMILARITY_CONTROLLER_HPP
#define SIMILARITY_CONTROLLER_HPP

#include <valarray>
#include <deque>
#include <string>
#include <utility>

namespace TOKEN
{
    class TranslationUnit;
}

namespace SIM
{

class Controller
{
public:
    Controller();

    bool execute(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>>&);

private:
    bool outputCSV(const std::deque<std::string> &functionNames
        , const std::valarray<std::valarray<double>>&) const;
};

}

#endif