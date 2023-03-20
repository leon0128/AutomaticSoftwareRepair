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
    // if T has only member tag(T::Tag),
    //  this function should be used to encode.
    // this function executes encode function to tag.
    template<class T>
    auto encode(const T *t)
        -> decltype(t->tag, bool{});

    // this function is used to encode integral value.
    template<class Integral>
    auto encode(Integral)
        -> std::enable_if<std::is_integral_v<Integral>, bool>::type;
    
    // this function is used to encode enum value.
    template<class Enum>
    auto encode(Enum)
        -> std::enable_if<std::is_enum_v<Enum>, bool>::type;

    // other tokens
    bool encode(std::monostate);
    bool encode(const std::string&);
    bool encode(const TOKEN::Identifier::Seq&);
    bool encode(const TOKEN::Identifier::Element&);
    bool encode(const TOKEN::Identifier::Id&);
    bool encode(const TOKEN::StringLiteral*);
    bool encode(const TOKEN::Digit*);
    bool encode(const TOKEN::IntegerConstant::Sdc_is&);
    bool encode(const TOKEN::IntegerConstant::Soc_is&);
    bool encode(const TOKEN::IntegerConstant::Shc_is&);
    bool encode(const TOKEN::EnumerationConstant*);
    bool encode(const TOKEN::CharacterConstant*);
    bool encode(const TOKEN::Nondigit*);
    bool encode(const TOKEN::UniversalCharacterName::Su_hq&);
    bool encode(const TOKEN::UniversalCharacterName::SU_hq_hq&);
    bool encode(const TOKEN::DecimalConstant*);
    bool encode(const TOKEN::HexadecimalConstant*);
    bool encode(const TOKEN::DecimalFloatingConstant::Sfc_ep_fs&);
    bool encode(const TOKEN::DecimalFloatingConstant::Sds_ep_fs&);
    bool encode(const TOKEN::HexadecimalFloatingConstant::Shp_hfc_bep_fs&);
    bool encode(const TOKEN::HexadecimalFloatingConstant::Shp_hds_bep_fs&);
    bool encode(const TOKEN::HexQuad*);
    bool encode(const TOKEN::NonzeroDigit*);
    bool encode(const TOKEN::OctalDigit*);
    bool encode(const TOKEN::HexadecimalDigit*);
    bool encode(const TOKEN::FractionalConstant::Sds_ds&);
    bool encode(const TOKEN::FractionalConstant::Sds&);
    bool encode(const TOKEN::ExponentPart*);
    bool encode(const TOKEN::HexadecimalFractionalConstant::Shds_hds&);
    bool encode(const TOKEN::HexadecimalFractionalConstant::Shds&);
    bool encode(const TOKEN::BinaryExponentPart*);
    bool encode(const TOKEN::SimpleEscapeSequence*);
    bool encode(const TOKEN::IntegerSuffix::Sus_ls&);
    bool encode(const TOKEN::IntegerSuffix::Sus_lls&);
    bool encode(const TOKEN::IntegerSuffix::Sls_us&);
    bool encode(const TOKEN::IntegerSuffix::Slls_us&);
    bool encode(const TOKEN::FunctionDefinition*);
    bool encode(const TOKEN::Declaration*);
    bool encode(const TOKEN::Declaration::Sds_idl&);
    bool encode(const TOKEN::Declaration::Ssad&);

    // add padding (max: 255)
    // it's should be called before arithmetic element is written.
    bool align(std::stringstream::pos_type alignmentSize);

    // add pointer status to mStream.
    // if pointer has value(i.e. not nullptr), add '\x1' to mStream and return true.
    // otherwise(i.e. nullptr), add '\x0' to mStream and return false.
    template<class T>
    bool addStatus(const T*);

    bool output(const std::string &filename) const;

    std::stringstream mStream;
};

template<class T>
auto CacheEncoder::encode(const T *t)
    -> decltype(t->var, bool{})
{
    if(!addStatus(t))
        return true;

    return encode(t->var.index())
        && std::visit([&](auto &&arg){return encode(arg);}, t->var);
}

template<class T>
auto CacheEncoder::encode(const T *t)
    -> decltype(t->seq, bool{})
{
    if(!addStatus(t))
        return true;

    if(!encode(t->seq.size()))
        return false;

    for(auto &&e : t->seq)
    {
        if(!encode(e))
            return false;
    }

    return true;
}

template<class T>
auto CacheEncoder::encode(const T *t)
    -> decltype(t->tag, bool{})
{
    if(!addStatus(t))
        return true;

    return encode(t->tag);
}

template<class Integral>
auto CacheEncoder::encode(Integral i)
    -> std::enable_if<std::is_integral_v<Integral>, bool>::type
{
    if(!align(std::alignment_of_v<Integral>))
        return false;

    mStream.write(reinterpret_cast<const char*>(&i)
        , sizeof(i));

    return true;
}

template<class Enum>
auto CacheEncoder::encode(Enum e)
    -> std::enable_if<std::is_enum_v<Enum>, bool>::type
{
    return encode(static_cast<std::underlying_type_t<Enum>>(e));
}

template<class T>
bool CacheEncoder::addStatus(const T *t)
{
    if(t != nullptr)
    {
        encode('\x1');
        return true;
    }
    else
    {
        encode('\x0');
        return false;
    }
}

}

#endif