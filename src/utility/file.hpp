#ifndef UTILITY_FILE_HPP
#define UTILITY_FILE_HPP

#include <filesystem>
#include <string>

namespace PATH
{

/* type == file_type::redular
// if type is file_type::redular and path.parent() is not exist,
// path.parent() is created. if file is able to create in path,
// this function return true, otherwise function return false.
*/
/* type == file_type::directory
// if type is file_type::directory and path is not exist,
// path is created. if path was created or path is already created,
// function return true. otherwise function return false.
*/
/* otherwise
// function always return false.
*/
bool isValid(const std::filesystem::path &path
    , std::filesystem::file_type type);

bool isExist(const std::filesystem::path &path
    , std::filesystem::file_type type);

bool read(const std::filesystem::path &path
    , std::string &str);
bool write(const std::filesystem::path &path
    , const std::string &str
    , bool isOverwitten = true);

std::string getTempFilename();

}

#endif