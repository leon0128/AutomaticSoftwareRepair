#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <cstdio>

#include "file.hpp"

namespace PATH
{

bool isValid(const std::filesystem::path &path
    , std::filesystem::file_type type)
{
    if(type == std::filesystem::file_type::regular)
    {
        if(path.filename() == "")
            return false;

        if(isValid(path.parent_path(), std::filesystem::file_type::directory)
            && !isExist(path, std::filesystem::file_type::directory))
            return true;
        else
            return false;
    }
    else if(type == std::filesystem::file_type::directory)
    {
        if(path.filename() == "")
            return true;

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

std::string getTempFilename()
{
    static std::filesystem::path tempDir{std::filesystem::temp_directory_path() / "asr/"};
    static std::size_t numCreated{0};
    static bool isCreatedDirectories{false};
    static std::mutex mutex;


    std::unique_lock lock{mutex};
    if(!isCreatedDirectories)
        std::filesystem::create_directories(tempDir);
    return (tempDir / std::to_string(numCreated++)).string();
}

bool remove(const std::string &filename)
{
    return std::remove(filename.c_str()) == 0;
}

}