#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <utility>
#include <bitset>
#include <unordered_map>
#include <memory>
#include <stdexcept>

#include "token.hpp"

namespace SCOPE
{
    class Scope;
}
namespace TYPE
{
    class IdInfo;
}
namespace IDENTIFIER
{
    class Identifier;
}

class Analyzer
{
private:
    enum class FlagTag : unsigned char;
    inline static constexpr const std::size_t NUM_FLAG_TAG{2};

    using Flags = std::bitset<NUM_FLAG_TAG>;

    using MapKey = std::size_t;
    template<class E>
    using MapElement = std::shared_ptr<E>;
    using TypeMap = std::unordered_map<MapKey, MapElement<TYPE::IdInfo>>;
    using IdMap = std::unordered_map<MapKey, MapElement<IDENTIFIER::Identifier>>;

    inline static TypeMap TYPE_MAP{};
    inline static IdMap ID_MAP{};

public:
    Analyzer();
    ~Analyzer();

    bool execute(const TOKEN::TranslationUnit*);

private:
    bool analyze(const TOKEN::TranslationUnit*);
    bool analyze(const TOKEN::ExternalDeclaration*);
    bool analyze(const TOKEN::FunctionDefinition*);
    bool analyze(const TOKEN::Declaration*);

    void flag(FlagTag tag, bool b)
        {mFlags.set(static_cast<std::size_t>(tag), b);}
    bool flag(FlagTag tag) const
        {return mFlags.test(static_cast<std::size_t>(tag));}

    void variantError(const char *className) const
        {throw std::runtime_error(className);}

    Flags mFlags;
    SCOPE::Scope *mScope;
};

enum class Analyzer::FlagTag : unsigned char
{
    // is not declaration
    IS_FUNCTION
    // does declaration form [struct-or-union identifier;]
    , IS_DECLARATION_OVER
};

#endif