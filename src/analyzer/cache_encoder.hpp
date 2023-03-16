#ifndef ANALYZER_CACHE_ENCODER_HPP
#define ANALYZER_CACHE_ENCODER_HPP

#include <string>
#include <sstream>

#include "common/token.hpp"

namespace ANALYZER
{

class CacheEncoder
{
public:
    // should use only relative filename.
    static std::string outputFilename(const std::string &filename)
        {return "./cache/" + filename + ".tree";}

    CacheEncoder();
    ~CacheEncoder() = default;

    bool execute(const std::string &filename
        , const TOKEN::TranslationUnit*);

private:
    bool encode(const TOKEN::TranslationUnit*);

    bool output(const std::string &filename) const;

    std::stringstream mStream;
};

}

#endif