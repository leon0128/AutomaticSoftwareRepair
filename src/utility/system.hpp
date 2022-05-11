#ifndef UTILITY_SYSTEM_HPP
#define UTILITY_SYSTEM_HPP

#include <cstdlib>
#include <string>
#include <utility>
#include <iostream>

namespace SYSTEM
{

#if _WIN64 || _WIN32
inline extern const char * const NULLFILE{"NUL"};
#else
inline extern const char * const NULLFILE{"/dev/null"};
#endif

inline extern bool shouldOutputLog;
bool shouldOutputLog{false};

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
    if(shouldOutputLog)
        std::clog << "command: " << cmd << std::endl;

    return std::system(cmd.c_str());
}

template<class Str
    , class ...Args>
inline extern int system(Str &&str
    , Args &&...args)
{
    std::string com{command(std::forward<Str>(str)
        , std::forward<Args>(args)...)};
    
    if(shouldOutputLog)
        std::clog << "command: " << com << std::endl;

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