#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <utility>
#include <bitset>
#include <unordered_map>
#include <memory>
#include <string>
#include <optional>

#include "token.hpp"
#include "type.hpp"
#include "identifier.hpp"

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
    inline static constexpr const std::size_t NUM_FLAG_TAG{3};

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
    bool analyze(const TOKEN::FunctionDefinition*);
    bool analyze(const TOKEN::Declaration*);
    bool analyze(const TOKEN::CompoundStatement*);
    bool analyze(const TOKEN::Statement*);
    bool analyze(const TOKEN::LabeledStatement*);
    bool analyze(const TOKEN::ExpressionStatement*);
    bool analyze(const TOKEN::SelectionStatement*);
    bool analyze(const TOKEN::IterationStatement*);
    bool analyze(const TOKEN::JumpStatement*);

    bool analyze(const TOKEN::Initializer*);
    bool analyze(const TOKEN::ConstantExpression*);

    std::optional<std::tuple<IDENTIFIER::StorageClass
        , TYPE::Type
        , IDENTIFIER::FunctionSpecifiers
        , IDENTIFIER::Alignment>>
        analyzeAttributes(const TOKEN::DeclarationSpecifiers*);
    std::optional<std::pair<TYPE::Type
        , std::string>>
        analyzeTypeAndIdentifier(const TOKEN::Declarator*
            , const TYPE::Type&);

    bool flag(FlagTag tag, bool b);
    bool flag(FlagTag tag) const;

    void variantError(const char *className) const;
    bool differentTypeError(const std::string&) const;
    bool redefinedError(const std::string&) const;
    bool notSupportedError(const std::string&) const;

    Flags mFlags;
    SCOPE::Scope *mScope;
};

enum class Analyzer::FlagTag : unsigned char
{
    // is not declaration
    IS_FUNCTION
    // does declaration form [struct-or-union identifier;]
    , IS_DECLARATION_OVER
    // if it flag is false,
    // block scope is not created at compound-statement
    , IS_CREATING_BLOCK
};

#endif