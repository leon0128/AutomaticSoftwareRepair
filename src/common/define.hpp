#ifndef COMMON_DEFINE_HPP
#define COMMON_DEFINE_HPP

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <mutex>

#include "configure.hpp"

inline namespace COMMON
{

namespace SCOPE
{
    class Scope;
}

namespace TOKEN
{
    class TranslationUnit;
}

struct CodeInformation
{
    std::string mFilename;
    std::shared_ptr<TOKEN::TranslationUnit> mTranslationUnit;
    std::shared_ptr<SCOPE::Scope> mScope;
};

inline extern std::stringstream sstream;
std::stringstream sstream{};

inline extern std::mutex stdioMutex;
std::mutex stdioMutex{};

inline extern void controlOutputLog(std::string &command)
{
    if(!Configure::SHOULD_OUTPUT_SUBPROCESS_LOG)
    {
        command += " > ";
        command += Configure::NULL_FILENAME;
        command += " 2>&1";
    }

    if(Configure::SHOULD_OUTPUT_COMMAND_LOG)
        std::cout << "command-log: " << command << std::endl;
}

inline extern void controlOutputLog(std::string &command
    , std::mutex &mutex)
{
    if(!Configure::getSafelySHOULD_OUTPUT_SUBPROCESS_LOG())
    {
        command += " > ";
        command += Configure::getSafelyNULL_FILENAME();
        command += " 2>&1";
    }

    if(Configure::getSafelySHOULD_OUTPUT_COMMAND_LOG())
    {
        std::lock_guard lock{mutex};
        std::cout << "command-log: " << command << std::endl;
    }
}

}

#endif