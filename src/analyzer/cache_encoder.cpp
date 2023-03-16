#include <filesystem>
#include <fstream>

#include "cache_encoder.hpp"

namespace ANALYZER
{

CacheEncoder::CacheEncoder()
    : mFilename{}
    , mStream{std::ios_base::binary}
{
}

bool CacheEncoder::execute(const std::string &filename
    , const TOKEN::TranslationUnit *tu)
{
    mFilename = filename;

    if(!encode(tu))
        return false;

    if(!output(filename))
        return false;

    return true;
}

bool CacheEncoder::output(const std::string &filename) const
{
    std::filesystem::path cacheFilePath{outputFilename(filename)};
    std::filesystem::create_directories(cacheFilePath.parent_path());

    std::ofstream fileStream{cacheFilePath, std::ios_base::out | std::ios_base::binary};
    if(!fileStream.is_open())
        return false;

    fileStream << mStream.str();

    fileStream.close();

    return true;
}

}