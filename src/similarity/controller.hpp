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

    bool execute(const std::pair<std::string, const TOKEN::TranslationUnit*> &target
        , const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>> &pool);
    
    // if this function is called,
    // Controller::mResults is undefined.
    auto &&getResults() noexcept
        {return std::move(mResults);}

private:
    bool initialize(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>>&);
    bool calculate(const std::pair<std::string, const TOKEN::TranslationUnit*> &target);
    void finalize();
    
    void test(const std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>>&);

    std::deque<std::deque<double>> mResults;
};

}

#endif