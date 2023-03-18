#ifndef ANALYZER_CACHE_ENCODER_HPP
#define ANALYZER_CACHE_ENCODER_HPP

#include <string>
#include <sstream>
#include <type_traits>

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
    // if T has only member var(std::variant),
    //  this function should be used to encode.
    // this function executes encode function to element that var has.
    template<class T>
    auto encode(const T *t)
        -> decltype(t->var, bool{});
    // if T has only member seq(std::vector),
    //  this function should be used to encode.
    // this function executes encode function to elements that seq has.
    template<class T>
    auto encode(const T *t)
        -> decltype(t->seq, bool{});

    template<class Integral>
    auto encode(Integral)
        -> std::enable_if<std::is_integral_v<Integral>, bool>::type;
    
    template<class Enum>
    auto encode(Enum)
        -> std::enable_if<std::is_enum_v<Enum>, bool>::type;

    // add padding (max: 255)
    // it's should be called before arithmetic element is written.
    bool align(std::stringstream::pos_type alignmentSize);

    bool output(const std::string &filename) const;

    std::stringstream mStream;
};

template<class T>
auto CacheEncoder::encode(const T *t)
    -> decltype(t->var, bool{})
{
    mStream.write()

    return std::visit([](auto &&arg){return });
}

}

#endif