#ifndef NORMALIZER_HPP
#define NORMALIZER_HPP

#include <bitset>

namespace TOKEN
{
    class TranslationUnit;
}

namespace SCOPE
{
    class Scope;
}

class Normalizer
{
private:
    enum class IdentifierTag : unsigned char;
    enum class ScopeTag : unsigned char;
    enum class NamespaceTag : unsigned char;

    inline static constexpr const std::size_t NUM_IDENTIFIER_TAG{7};
    inline static constexpr const std::bitset<NUM_IDENTIFIER_TAG> IDENTIFIER_NORMALIZATION_FLAGS{0b1111111ull};
    inline static constexpr bool isNormalized(IdentifierTag tag)
        {return IDENTIFIER_NORMALIZATION_FLAGS[static_cast<std::size_t>(tag)];}
    inline static constexpr const std::size_t NUM_SCOPE_TAG{4};
    inline static constexpr const std::bitset<NUM_SCOPE_TAG> SCOPE_NORMALIZATION_FLAGS{0b1111ull};
    inline static constexpr bool isNormalized(ScopeTag tag)
        {return SCOPE_NORMALIZATION_FLAGS[static_cast<std::size_t>(tag)];}
    inline static constexpr const std::size_t NUM_NAMESPACE_TAG{4};
    inline static constexpr const std::bitset<NUM_NAMESPACE_TAG> NAMESPACE_NORMALIZATION_FLAGS{0b1111ull};
    inline static constexpr bool isNormalized(NamespaceTag tag)
        {return NAMESPACE_NORMALIZATION_FLAGS[static_cast<std::size_t>(tag)];}

public:
    Normalizer(const TOKEN::TranslationUnit*);
    ~Normalizer();
    Normalizer(const Normalizer&) = delete;
    Normalizer(Normalizer&&) = delete;

    bool execute();

    TOKEN::TranslationUnit *translationUnit() const noexcept
        {return mTranslationUnit;}
    SCOPE::Scope *scope() const noexcept
        {return mScope;}

private:
    TOKEN::TranslationUnit *mTranslationUnit;
    SCOPE::Scope *mScope;
};

enum class Normalizer::IdentifierTag : unsigned char
{
    OBJECT
    , FUNCTION
    , TAG
    , MEMBER
    , ENUMERATION
    , TYPEDEF
    , LABEL
};

enum class Normalizer::ScopeTag : unsigned char
{
    FILE
    , FUNCTION
    , BLOCK
    , FUNCTION_PROTOTYPE
};

enum class Normalizer::NamespaceTag : unsigned char
{
    LABEL
    , TAG
    , MEMBER
    , OTHER
};

#endif