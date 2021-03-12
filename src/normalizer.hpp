#ifndef NORMALIZER_HPP
#define NORMALIZER_HPP

#include <bitset>

namespace TOKEN
{
    class TranslationUnit;
}

class Normalizer
{
private:
    enum class IdentifierTag : std::size_t
    {
        OBJECT
        , FUNCTION
        , TAG
        , MEMBER
        , ENUMERATION
        , TYPEDEF
        , LABEL
    };
    inline static constexpr const std::size_t NUM_IDENTIFIER_TAG = 7;
    inline static constexpr const std::bitset<NUM_IDENTIFIER_TAG> NORMALIZATION_FLAGS{0b1111111ull};
    inline static bool IS_NORMALIZED(IdentifierTag tag)
        {return NORMALIZATION_FLAGS.test(static_cast<std::size_t>(tag));}

public:
    Normalizer(const TOKEN::TranslationUnit*);
    ~Normalizer();
    Normalizer(const Normalizer&) = delete;
    Normalizer(Normalizer&&) = delete;

    bool execute();

    TOKEN::TranslationUnit *translationUnit() const noexcept
        {return mTranslationUnit;}

private:

    TOKEN::TranslationUnit *mTranslationUnit;
};

#endif