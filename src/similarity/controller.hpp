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

    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;

    bool execute(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>>&);

private:
    bool createAndRegisterReps(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>>&);
};

}

#endif