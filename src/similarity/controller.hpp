#ifndef SIMILARITY_CONTROLLER_HPP
#define SIMILARITY_CONTROLLER_HPP

#include <deque>
#include <utility>
#include <string>
#include <memory>

#include "common/token.hpp"
#include "common/define.hpp"

namespace SIM
{

class Controller
{
public:
    Controller();
    ~Controller();

    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;

    bool execute(const CodeInformation &target
        , const std::deque<CodeInformation> &pool);
    
    // if this function is called,
    // Controller::mResults is undefined.
    auto &&moveResults() noexcept
        {return std::move(mResults);}

private:
    bool initialize(const std::deque<CodeInformation> &pool);
    bool calculate(const CodeInformation &target);
    void finalize();
    
    void test(const std::deque<CodeInformation> &pool);

    std::deque<std::deque<double>> mResults;
};

}

#endif