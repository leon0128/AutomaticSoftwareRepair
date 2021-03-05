#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <set>

#include "identifier.hpp"
#include "token.hpp"
#include "type.hpp"

namespace SCOPE{class Scope;}

class Analyzer
{
public:
    Analyzer(const std::string&
        , TOKEN::TranslationUnit*);
    ~Analyzer();

    bool execute();

private:
    std::string mFilename;
    TOKEN::TranslationUnit *mTranslationUnit;

    std::unordered_map<std::size_t, TYPE::IdInfo*> mIdMap;
    std::size_t mNextId;
    SCOPE::Scope *mScope;

    bool analyze(TOKEN::TranslationUnit*);
    bool analyze(TOKEN::Declaration*){return false;}
    bool analyze(TOKEN::FunctionDefinition*){return false;}

    std::tuple<IDENTIFIER::Storage
        , TYPE::Type*
        , IDENTIFIER::FunctionSpecifier
        , IDENTIFIER::Alignment*> deduceAttributes(const TOKEN::DeclarationSpecifiers*
        , bool isEnd);
    TYPE::Type *deduceType(const std::vector<TOKEN::TypeQualifier*>&
        , const std::vector<TOKEN::TypeSpecifier*>&
        , bool isEnd);
    TYPE::Type *deduceType(const std::vector<TOKEN::TypeSpecifier::Tag>&);
    TYPE::Type *deduceType(const TOKEN::AtomicTypeSpecifier*);
    TYPE::Type *deduceType(const TOKEN::StructOrUnionSpecifier*
        , bool isEnd);
    TYPE::Type *deduceType(const TOKEN::EnumSpecifier*);
    TYPE::Type *deduceType(const TOKEN::TypedefName*);
    TYPE::Type *deduceType(const TOKEN::TypeName*);
    TYPE::Type *deduceType(const TOKEN::SpecifierQualifierList*
        , bool isEnd);
    TYPE::Type *deduceType(const TOKEN::ParameterDeclaration*);
    TYPE::Type *deduceType(TYPE::Type *base
        , const TOKEN::Pointer*);
    TYPE::Qualifier deduceQualifiers(const std::vector<TOKEN::TypeQualifier*>&);
    IDENTIFIER::Storage deduceStorage(const std::vector<TOKEN::StorageClassSpecifier*>&);
    IDENTIFIER::FunctionSpecifier deduceFunctionSpecifier(const std::vector<TOKEN::FunctionSpecifier*>&);
    IDENTIFIER::Alignment *deduceAlignment(const std::vector<TOKEN::AlignmentSpecifier*>&);
    bool addArguments(const TOKEN::IdentifierList*);
    bool addQualifier(TYPE::Type*
        , const TYPE::Qualifier&) const;
    bool addMemberInfo(std::size_t id
        , const TOKEN::StructDeclarationList*);
    bool addMemberInfo(std::size_t id
        , TYPE::Type*
        , const TOKEN::StructDeclarator*);
    TYPE::Type *deduceType(TYPE::Type *base
        , const TOKEN::AbstractDeclarator*);
    TYPE::Type *deduceType(TYPE::Type *base
        , const TOKEN::DirectAbstractDeclarator*);
    std::pair<TYPE::Type*, std::string> deduceTypeAndIdentifier(TYPE::Type *base
        , const TOKEN::Declarator*
        , bool isPrototype);
    std::pair<TYPE::Type*, std::string> deduceTypeAndIdentifier(TYPE::Type *base
        , const TOKEN::DirectDeclarator*
        , bool isPrototype);

    SCOPE::Scope *removeScope();

    static const std::unordered_map<TYPE::Base::Tag, std::vector<std::multiset<TOKEN::TypeSpecifier::Tag>>> TYPE_MAP;
};

#endif