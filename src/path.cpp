#include <fstream>
#include <sstream>

#include "path.hpp"

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

std::string read(const std::filesystem::path &file)
{
    std::ifstream fstr(file);
    if(!fstr.is_open())
        return std::string();

    std::stringstream sstr;
    sstr << fstr.rdbuf();
    return sstr.str();
}

}