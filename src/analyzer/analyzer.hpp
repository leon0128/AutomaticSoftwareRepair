#ifndef ANALYZER_ANALYZER_HPP
#define ANALYZER_ANALYZER_HPP

#include <utility>
#include <bitset>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <memory>
#include <string>
#include <optional>

#include "common/token.hpp"
#include "common/type.hpp"
#include "common/identifier.hpp"
#include "common/scope.hpp"

namespace ANALYZER
{

class Analyzer
{
private:
    enum class FlagTag : unsigned char;
    inline static constexpr const std::size_t NUM_FLAG_TAG{4};

    using Flags = std::bitset<NUM_FLAG_TAG>;

public:
    Analyzer();
    ~Analyzer();

    Analyzer(const Analyzer&) = delete;
    Analyzer(Analyzer&&) = delete; 

    bool execute(const std::string &filename
        , TOKEN::TranslationUnit*);

    SCOPE::Scope *scope() const noexcept
        {return mScope;}

    // if this function is called, mScope's value is nullptr.
    auto moveScope()
        {return std::exchange(mScope, nullptr);}

private:
    bool finalize();

    // this function deletes included contents from mTranslationUnit.
    bool controlIncludingFile();
    // this function controls mIncludingFileMap.
    // second argument is indicates position of first argument in translation-unit.
    bool controlIncludingFile(const TOKEN::IncludingFile*
        , std::size_t translationUnitIndex);

    bool analyze(TOKEN::TranslationUnit*);
    bool analyze(TOKEN::FunctionDefinition*);
    bool analyze(TOKEN::Declaration*);
    bool analyze(const TOKEN::CompoundStatement*
        , std::size_t &scopeId);
    bool analyze(TOKEN::Statement*);
    bool analyze(const TOKEN::LabeledStatement*);
    bool analyze(const TOKEN::ExpressionStatement*);
    bool analyze(const TOKEN::SelectionStatement*);
    bool analyze(const TOKEN::IterationStatement*);
    bool analyze(const TOKEN::JumpStatement*);
    bool analyze(const TOKEN::AttributeStatement*);
    bool analyze(const TOKEN::AsmStatement*);

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
        analyzeType(const std::multiset<TOKEN::TypeSpecifier::Tag>&);
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
    std::string mFunctionName;
    TOKEN::TranslationUnit *mTranslationUnit;
    Flags mFlags;
    SCOPE::Scope *mScope;
    std::unordered_map<std::string, std::pair<std::size_t, std::size_t>> mIncludingFileMap;
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
    // used in function-definition or prototype-declaration
    , IS_OUTEST_PARAMETER
};

}

#endif