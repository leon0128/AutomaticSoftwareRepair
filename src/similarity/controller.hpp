#ifndef SIMILARITY_CONTROLLER_HPP
#define SIMILARITY_CONTROLLER_HPP

#include <deque>
#include <utility>
#include <string>

namespace TOKEN
{
    class TranslationUnit;
};

namespace SIM
{

class Controller
{
public:
    Controller();
    ~Controller();

    bool execute(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>>&);

private:

};

}

#endif