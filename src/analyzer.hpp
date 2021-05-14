#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <utility>
#include <bitset>
#include <unordered_map>
#include <vector>
#include <unordered_set>
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

    using ResultTypeTag = TYPE::Base::Tag;
    using BaseTypeTag = TOKEN::TypeSpecifier::Tag;
    using BaseTypeSet = std::multiset<BaseTypeTag>;
    using BaseTypeCandidate = std::vector<BaseTypeSet>;
    using BaseTypeMap = std::unordered_map<ResultTypeTag
        , BaseTypeCandidate>;

    static const BaseTypeMap BASE_TYPE_MAP;

public:
    Analyzer();
    ~Analyzer();

    bool execute(const std::string &filename
        , TOKEN::TranslationUnit*);
    bool finalize();

    TOKEN::TranslationUnit *translationUnit() const noexcept
        {return mTranslationUnit;}
    SCOPE::Scope *scope() const noexcept
        {return mScope;}

    inline static constexpr const TypeMap &typeMap() noexcept
        {return TYPE_MAP;}

private:
    bool analyze(const TOKEN::TranslationUnit*);
    bool analyze(TOKEN::FunctionDefinition*);
    bool analyze(const TOKEN::Declaration*);
    bool analyze(const TOKEN::CompoundStatement*
        , std::size_t &scopeId);
    bool analyze(TOKEN::Statement*);
    bool analyze(const TOKEN::LabeledStatement*);
    bool analyze(const TOKEN::ExpressionStatement*);
    bool analyze(const TOKEN::SelectionStatement*);
    bool analyze(const TOKEN::IterationStatement*);
    bool analyze(const TOKEN::JumpStatement*);

    bool analyze(const TOKEN::Initializer*);
    bool analyze(const TOKEN::InitializerList*);
    bool analyze(const TOKEN::ConstantExpression*);
    bool analyze(const TOKEN::Expression*);
    bool analyze(const TOKEN::AssignmentExpression*);
    bool analyze(const TOKEN::ConditionalExpression*);
    bool analyze(const TOKEN::LogicalORExpression*);
    bool analyze(const TOKEN::LogicalANDExpression*);
    bool analyze(const TOKEN::InclusiveORExpression*);
    bool analyze(const TOKEN::ExclusiveORExpression*);
    bool analyze(const TOKEN::ANDExpression*);
    bool analyze(const TOKEN::EqualityExpression*);
    bool analyze(const TOKEN::RelationalExpression*);
    bool analyze(const TOKEN::ShiftExpression*);
    bool analyze(const TOKEN::AdditiveExpression*);
    bool analyze(const TOKEN::MultiplicativeExpression*);
    bool analyze(const TOKEN::CastExpression*);
    bool analyze(const TOKEN::UnaryExpression*);
    bool analyze(const TOKEN::PostfixExpression*);
    bool analyze(const TOKEN::PrimaryExpression*);
    bool analyze(const TOKEN::GenericSelection*);

    std::optional<std::tuple<IDENTIFIER::StorageClass
        , TYPE::Type
        , IDENTIFIER::FunctionSpecifiers
        , IDENTIFIER::Alignment>>
        analyzeAttributes(const TOKEN::DeclarationSpecifiers*);
    std::optional<IDENTIFIER::StorageClass>
        analyzeStorageClassSpecifiers(const std::vector<const TOKEN::StorageClassSpecifier*>&);
    std::optional<TYPE::Type>
        analyzeType(const std::vector<const TOKEN::TypeSpecifier*>&
            , const std::vector<const TOKEN::TypeQualifier*>&);
    std::optional<IDENTIFIER::FunctionSpecifiers>
        analyzeFunctionSpecifiers(const std::vector<const TOKEN::FunctionSpecifier*>&);
    std::optional<IDENTIFIER::Alignment>
        analyzeAlignmentSpecifier(const std::vector<const TOKEN::AlignmentSpecifier*>&);
    std::optional<TYPE::Type>
        analyzeType(const std::vector<const TOKEN::TypeSpecifier*>&);
    std::optional<TYPE::Type>
        analyzeType(const BaseTypeSet&);
    std::optional<TYPE::Type>
        analyzeType(const std::vector<const TOKEN::AtomicTypeSpecifier*>&);
    std::optional<TYPE::Type>
        analyzeType(const std::vector<const TOKEN::StructOrUnionSpecifier*>&);
    bool analyzeMember(const TOKEN::StructDeclarationList*
        , std::size_t);
    std::optional<TYPE::Type>
        analyzeType(const TOKEN::SpecifierQualifierList*);
    std::optional<TYPE::Type>
        analyzeType(const TOKEN::ConstantExpression*
            , const TYPE::Type&);
    std::optional<TYPE::Type>
        analyzeType(const std::vector<const TOKEN::EnumSpecifier*>&);
    bool analyzeMember(const TOKEN::EnumeratorList*
        , std::size_t);
    std::optional<TYPE::Type>
        analyzeType(const std::vector<const TOKEN::TypedefName*>&);
    std::optional<TYPE::Qualifiers>
        analyzeTypeQualifiers(const std::vector<const TOKEN::TypeQualifier*>&);
    std::optional<TYPE::Type>
        analyzeType(const TYPE::Type&
            , const TYPE::Qualifiers&);
    std::optional<std::pair<TYPE::Type
        , std::string>>
        analyzeTypeAndIdentifier(const TOKEN::Declarator*
            , const TYPE::Type&);
    std::optional<TYPE::Type>
        analyzeType(const TOKEN::Pointer*
            , const TYPE::Type&);
    std::optional<TYPE::Qualifiers>
        analyzeTypeQualifiers(const TOKEN::TypeQualifierList*);
    // for array
    std::optional<TYPE::Type>
        analyzeType(const TOKEN::TypeQualifierList*
            , const TOKEN::AssignmentExpression*
            , bool hasStatic
            , bool isVariable
            , const TYPE::Type&);
    // for function
    std::optional<TYPE::Type>
        analyzeType(const TOKEN::ParameterTypeList*
            , const TYPE::Type&);
    // for function
    std::optional<TYPE::Type>
        analyzeType(const TOKEN::IdentifierList*
            , const TYPE::Type&);
    std::optional<TYPE::Type>
        analyzeType(const TOKEN::ParameterDeclaration*);
    std::optional<TYPE::Type>
        analyzeType(const TOKEN::AbstractDeclarator*
            , const TYPE::Type&);
    std::optional<TYPE::Type>
        analyzeType(const TOKEN::TypeName*);

    TOKEN::Identifier *getIdentifier(const TOKEN::Declarator*);
    void deleteIdentifierElement(TOKEN::Identifier*);

    bool flag(FlagTag tag, bool b);
    bool flag(FlagTag tag) const;

    void variantError(const std::string&) const noexcept(false); // throw error
    bool differentTypeError(const std::string&) const;
    bool redefinedError(const std::string&) const;
    bool notSupportedError(const std::string&) const;
    bool invalidAttributeError(const std::string&) const;
    bool invalidTypeError(const std::string&) const;
    bool notDeclarationError(const std::string&) const;

    std::string mFilename;
    TOKEN::TranslationUnit *mTranslationUnit;
    Flags mFlags;
    SCOPE::Scope *mScope;
};

enum class Analyzer::FlagTag : unsigned char
{
    // is not declaration
    IS_FUNCTION
    // declaration form [struct-or-union identifier;]
    , IS_DECLARATION_OVER
    // if it flag is false,
    // block scope is not created at compound-statement
    , IS_CREATING_BLOCK
};

#endif