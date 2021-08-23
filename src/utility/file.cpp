#include <fstream>
#include <sstream>
#include <string>

#include "file.hpp"

namespace PATH
{

bool isValid(const std::filesystem::path &path
    , std::filesystem::file_type type)
{
    if(type == std::filesystem::file_type::regular)
    {
        if(isValid(path.parent_path(), std::filesystem::file_type::directory)
            && !isExist(path, std::filesystem::file_type::directory))
            return true;
        else
            return false;
    }
    else if(type == std::filesystem::file_type::directory)
    {
        if(isExist(path, std::filesystem::file_type::directory))
            return true;
        else
            return std::filesystem::create_directories(path);
    }
    else
        return false;
}

bool isExist(const std::filesystem::path &path
    , std::filesystem::file_type type)
{
    return type == std::filesystem::status(path).type();
}

bool read(const std::filesystem::path &path
    , std::string &str)
{
    std::ifstream fstr{path};
    if(!fstr.is_open())
        return false;

    std::stringstream sstr;
    sstr << fstr.rdbuf();
    str += sstr.str();
    return true;
}

bool write(const std::filesystem::path &path
    , const std::string &str
    , bool isOverwritten)
{
    std::fstream fstr;

    if(isOverwritten
        && isExist(path, std::filesystem::file_type::regular))
        fstr.open(path, std::ios_base::out);
    else
    {
        if(!isValid(path, std::filesystem::file_type::regular))
            return false;
        fstr.open(path, std::ios_base::out);
    }

    if(!fstr.is_open())
        return false;

    fstr << str;

    return true;
}

}