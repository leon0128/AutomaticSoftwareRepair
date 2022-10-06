#ifndef UTILITY_SYSTEM_HPP
#define UTILITY_SYSTEM_HPP

#include <cstdlib>
#include <string>
#include <utility>
#include <iostream>

namespace SYSTEM
{

inline extern bool shouldOutputSubprocessCommand;
inline extern bool shouldOutputSubprocessLog;
inline extern std::string nullFile;
bool shouldOutputSubprocessCommand{false};
bool shouldOutputSubprocessLog{false};
std::string nullFile{"/dev/null"};

inline extern int system(const std::string &cmd);
template<class Str
    , class ...Args>
inline extern int system(Str &&str
    , Args &&...args);

template<class Str
    , class ...Args>
inline extern std::string command(Str &&str
    , Args &&...args);
inline extern std::string command();

inline extern int system(const std::string &cmd)
{
    std::string addedCmd{cmd};
    if(shouldOutputSubprocessLog)
    {
        addedCmd += " 2>&1 ";
        addedCmd += nullFile;
    }

    if(shouldOutputSubprocessCommand)
        std::clog << "command: " << addedCmd << std::endl;

    return std::system(addedCmd.c_str());
}

template<class Str
    , class ...Args>
inline extern int system(Str &&str
    , Args &&...args)
{
    std::string com{command(std::forward<Str>(str)
        , std::forward<Args>(args)...)};
    
    std::string addedCmd{com};
    if(shouldOutputSubprocessLog)
    {
        addedCmd += " 2>&1 ";
        addedCmd += nullFile;
    }

    if(shouldOutputSubprocessCommand)
        std::clog << "command: " << addedCmd << std::endl;

    return std::system(com.c_str());
}

template<class Str
    , class ...Args>
inline extern std::string command(Str &&str
    , Args &&...args)
{
    std::string cmd{str};
    cmd.push_back(' ');
    cmd += command(std::forward<Args>(args)...);
    return cmd;
}

inline extern std::string command()
{
    return {};
}

}

#endif