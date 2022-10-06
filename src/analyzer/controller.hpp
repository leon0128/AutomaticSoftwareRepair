#ifndef ANALYZER_CONTROLLER_HPP
#define ANALYZER_CONTROLLER_HPP

#include <deque>
#include <string>
#include <memory>
#include <utility>

#include "common/define.hpp"

namespace ANALYZER
{

class Controller
{
public:
    Controller();
    ~Controller();

    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;

    bool execute();

    // if this function is called, mTarget's value is undefined.
    auto &&moveTarget() noexcept
        {return std::move(mTarget);}
    // if this function is called, mPool's value is undefined.
    auto &&movePool() noexcept
        {return std::move(mPool);}

private:
    std::deque<std::string> getFiles(const std::string &pathname) const;
    
    // if isTarget is true, function's results is stored to mTarget.
    // if isTarget is false, function's results is stored to mPool.
    bool analyze(const std::string &filename
        , bool isTarget);

    CodeInformation mTarget;
    std::deque<CodeInformation> mPool;
};

}

#endif