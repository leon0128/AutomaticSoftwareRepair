#include <filesystem>
#include <fstream>
#include <iostream>

#include "cache_encoder.hpp"

namespace ANALYZER
{

CacheEncoder::CacheEncoder()
    : mStream{std::ios_base::out | std::ios_base::binary}
{
}

bool CacheEncoder::execute(const std::string &filename
    , const TOKEN::TranslationUnit *tu)
{
    if(!encode(tu))
        return false;

    if(!output(filename))
        return false;

    return true;
}

bool CacheEncoder::align(std::stringstream::pos_type alignmentSize)
{
    static const char padding[0xff]{'\0'};

    auto &&paddingSize{(alignmentSize - mStream.tellp() % alignmentSize) % alignmentSize};
    mStream.write(padding, paddingSize);
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