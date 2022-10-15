#ifndef ANALYZER_CONTROLLER_HPP
#define ANALYZER_CONTROLLER_HPP

#include <deque>
#include <string>
#include <memory>
#include <utility>
#include <optional>
#include <mutex>

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
    
    // this function is used for target file.
    bool analyze(const std::string &filename);
    // this function is used for pool files.
    bool analyze(const std::deque<std::string> &filenames);

    // this function analyze file.
    // if analyzing is successed, return CodeInformation,
    // othewise return std::nullopt.
    // this function is thread safe.
    static std::optional<CodeInformation> analyzeSafely(const std::string &filename);

    bool poolIgnoringWarning(const std::string &filename) const;

    void outputAnalyzingLog() const;
    void outputAnalyzingLog(const std::string &filename
        , std::size_t poolSize);
    void setSpecifiedLog() const;

    CodeInformation mTarget;
    std::deque<CodeInformation> mPool;

    std::mutex mMemberMutex;
    std::size_t mTotalPoolCount;
    std::size_t mSuccessedPoolCount;
};

}

#endif