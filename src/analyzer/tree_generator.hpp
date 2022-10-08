#ifndef ANALYZER_TREE_GENERATOR_HPP
#define ANALYZER_TREE_GENERATOR_HPP

#include <deque>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include <utility>
#include <functional>

#include "common/token.hpp"
#include "common/scope.hpp"

namespace ANALYZER
{

class TreeGenerator
{
private:
    static const std::unordered_map<std::string, TOKEN::Keyword::Tag> KEYWORD_MAP;
    static const std::deque<TOKEN::PreprocessingToken*> TEMPORARY_OBJECT;

public:
    using Sequence = std::deque<TOKEN::PreprocessingToken*>;

    TreeGenerator();
    ~TreeGenerator();
    TreeGenerator(const TreeGenerator&) = delete;
    TreeGenerator(TreeGenerator&&) = delete;

    bool execute(const std::string &filename
        , const Sequence &sequence);
    
    // if this function is called, mTranslationUnit's value is nullptr.
    auto moveTranslationUnit()
        {return std::exchange(mTranslationUnit, nullptr);}

private:
    // this class is used to mCacheMap's value_type.
    class MapElement;

    // member functions
    TOKEN::TranslationUnit *tokTranslationUnit();
    TOKEN::ExternalDeclaration *tokExternalDeclaration();
    TOKEN::FunctionDefinition *tokFunctionDefinition();
    TOKEN::Declaration *tokDeclaration();
    TOKEN::DeclarationSpecifiers *tokDeclarationSpecifiers();
    TOKEN::InitDeclaratorList *tokInitDeclaratorList();
    TOKEN::StaticAssertDeclaration *tokStaticAssertDeclaration();
    TOKEN::ConstantExpression *tokConstantExpression();
    TOKEN::StringLiteral *tokStringLiteral();
    TOKEN::Declarator *tokDeclarator();
    TOKEN::DeclarationList *tokDeclarationList();
    TOKEN::CompoundStatement *tokCompoundStatement();
    TOKEN::StorageClassSpecifier *tokStorageClassSpecifier();
    TOKEN::TypeSpecifier *tokTypeSpecifier();
    TOKEN::TypeQualifier *tokTypeQualifier();
    TOKEN::FunctionSpecifier *tokFunctionSpecifier();
    TOKEN::AlignmentSpecifier *tokAlignmentSpecifier();
    TOKEN::InitDeclarator *tokInitDeclarator();
    TOKEN::ConditionalExpression *tokConditionalExpression();
    TOKEN::Pointer *tokPointer();
    TOKEN::DirectDeclarator *tokDirectDeclarator();
    TOKEN::BlockItemList *tokBlockItemList();
    TOKEN::AtomicTypeSpecifier *tokAtomicTypeSpecifier();
    TOKEN::StructOrUnionSpecifier *tokStructOrUnionSpecifier();
    TOKEN::EnumSpecifier *tokEnumSpecifier();
    TOKEN::TypedefName *tokTypedefName();
    TOKEN::TypeName *tokTypeName();
    TOKEN::Initializer *tokInitializer();
    TOKEN::LogicalORExpression *tokLogicalORExpression();
    TOKEN::Expression *tokExpression();
    TOKEN::TypeQualifierList *tokTypeQualifierList();
    TOKEN::AssignmentExpression *tokAssignmentExpression();
    TOKEN::ParameterTypeList *tokParameterTypeList();
    TOKEN::IdentifierList *tokIdentifierList();
    TOKEN::Identifier *tokIdentifier();
    TOKEN::BlockItem *tokBlockItem();
    TOKEN::StructOrUnion *tokStructOrUnion();
    TOKEN::StructDeclarationList *tokStructDeclarationList();
    TOKEN::EnumeratorList *tokEnumeratorList();
    TOKEN::SpecifierQualifierList *tokSpecifierQualifierList();
    TOKEN::AbstractDeclarator *tokAbstractDeclarator();
    TOKEN::InitializerList *tokInitializerList();
    TOKEN::LogicalANDExpression *tokLogicalANDExpression();
    TOKEN::UnaryExpression *tokUnaryExpression();
    TOKEN::AssignmentOperator *tokAssignmentOperator();
    TOKEN::ParameterList *tokParameterList();
    TOKEN::Statement *tokStatement();
    TOKEN::StructDeclaration *tokStructDeclaration();
    TOKEN::Enumerator *tokEnumerator();
    TOKEN::DirectAbstractDeclarator *tokDirectAbstractDeclarator();
    TOKEN::Designation *tokDesignation();
    TOKEN::InclusiveORExpression *tokInclusiveORExpression();
    TOKEN::PostfixExpression *tokPostfixExpression();
    TOKEN::CastExpression *tokCastExpression();
    TOKEN::UnaryOperator *tokUnaryOperator();
    TOKEN::ParameterDeclaration *tokParameterDeclaration();
    TOKEN::LabeledStatement *tokLabeledStatement();
    TOKEN::ExpressionStatement *tokExpressionStatement();
    TOKEN::SelectionStatement *tokSelectionStatement();
    TOKEN::IterationStatement *tokIterationStatement();
    TOKEN::JumpStatement *tokJumpStatement();
    TOKEN::StructDeclaratorList *tokStructDeclaratorList();
    TOKEN::EnumerationConstant *tokEnumerationConstant();
    TOKEN::DesignatorList *tokDesignatorList();
    TOKEN::ExclusiveORExpression *tokExclusiveORExpression();
    TOKEN::PrimaryExpression *tokPrimaryExpression();
    TOKEN::ArgumentExpressionList *tokArgumentExpressionList();
    TOKEN::StructDeclarator *tokStructDeclarator();
    TOKEN::Designator *tokDesignator();
    TOKEN::ANDExpression *tokANDExpression();
    TOKEN::Constant *tokConstant();
    TOKEN::GenericSelection *tokGenericSelection();
    TOKEN::EqualityExpression *tokEqualityExpression();
    TOKEN::GenericAssocList *tokGenericAssocList();
    TOKEN::RelationalExpression *tokRelationalExpression();
    TOKEN::GenericAssociation *tokGenericAssociation();
    TOKEN::ShiftExpression *tokShiftExpression();
    TOKEN::AdditiveExpression *tokAdditiveExpression();
    TOKEN::MultiplicativeExpression *tokMultiplicativeExpression();

    TOKEN::AttributeSpecifier *tokAttributeSpecifier();
    TOKEN::AttributeSpecifierList *tokAttributeSpecifierList();
    TOKEN::AttributeStatement *tokAttributeStatement();

    TOKEN::AsmQualifiers *tokAsmQualifiers();
    TOKEN::BasicAsm *tokBasicAsm();
    TOKEN::ExtendedAsm *tokExtendedAsm();
    TOKEN::AsmStatement *tokAsmStatement();

    TOKEN::IncludingFile *tokIncludingFile();

    TOKEN::IntegerConstant *convIntegerConstant();
    TOKEN::FloatingConstant *convFloatingConstant();
    TOKEN::EnumerationConstant *convEnumerationConstant();
    TOKEN::CharacterConstant *convCharacterConstant();
    TOKEN::Token *convToken();

    // if token is matching, idx is increment
    bool isMatch(TOKEN::Keyword::Tag);
    bool isMatch(TOKEN::Punctuator::Tag);

    // copy token from cache.
    // this function reference mIdx.
    // if copy is successful, mIdx is updated.
    // otherwise, this returns nullptr
    template<class Token>
    Token *createFromCache();
    // register token to cache.
    // this function references mIdx to determine MapElement::mEnd.
    // this function returns argument's value.
    template<class Token>
    Token *registerToCache(Token*
        , std::size_t beginIdx); 

    // error
    bool noEvaluatedError() const;

    // member variables
    std::string mFile;
    std::reference_wrapper<const Sequence> mSeq;
    std::size_t mIdx;
    TOKEN::TranslationUnit *mTranslationUnit;
    std::unordered_multimap<std::size_t, MapElement*> mCacheMap;
};

// this class has token's beginning position, end position and Token itself.
class TreeGenerator::MapElement
{
public:
    // this variant class is able to contain any tokens.
    using Var = std::variant<TOKEN::Token*
        , TOKEN::Keyword*
        , TOKEN::Identifier*
        , TOKEN::Constant*
        , TOKEN::StringLiteral*
        , TOKEN::Punctuator*
        , TOKEN::IdentifierNondigit*
        , TOKEN::Digit*
        , TOKEN::IntegerConstant*
        , TOKEN::FloatingConstant*
        , TOKEN::EnumerationConstant*
        , TOKEN::CharacterConstant*
        , TOKEN::EncodingPrefix*
        , TOKEN::SCharSequence*
        , TOKEN::Nondigit*
        , TOKEN::UniversalCharacterName*
        , TOKEN::DecimalConstant*
        , TOKEN::IntegerSuffix*
        , TOKEN::OctalConstant*
        , TOKEN::HexadecimalConstant*
        , TOKEN::DecimalFloatingConstant*
        , TOKEN::HexadecimalFloatingConstant*
        , TOKEN::CCharSequence*
        , TOKEN::SChar*
        , TOKEN::HexQuad*
        , TOKEN::NonzeroDigit*
        , TOKEN::OctalDigit*
        , TOKEN::HexadecimalPrefix*
        , TOKEN::HexadecimalDigit*
        , TOKEN::FractionalConstant*
        , TOKEN::ExponentPart*
        , TOKEN::FloatingSuffix*
        , TOKEN::DigitSequence*
        , TOKEN::HexadecimalFractionalConstant*
        , TOKEN::BinaryExponentPart*
        , TOKEN::HexadecimalDigitSequence*
        , TOKEN::Sign*
        , TOKEN::CChar*
        , TOKEN::EscapeSequence*
        , TOKEN::SimpleEscapeSequence*
        , TOKEN::OctalEscapeSequence*
        , TOKEN::HexadecimalEscapeSequence*
        , TOKEN::PreprocessingToken*
        , TOKEN::PPNumber*
        , TOKEN::UnsignedSuffix*
        , TOKEN::LongSuffix*
        , TOKEN::LongLongSuffix*
        , TOKEN::TranslationUnit*
        , TOKEN::ExternalDeclaration*
        , TOKEN::FunctionDefinition*
        , TOKEN::Declaration*
        , TOKEN::DeclarationSpecifiers*
        , TOKEN::Declarator*
        , TOKEN::DeclarationList*
        , TOKEN::CompoundStatement*
        , TOKEN::InitDeclaratorList*
        , TOKEN::StaticAssertDeclaration*
        , TOKEN::StorageClassSpecifier*
        , TOKEN::TypeSpecifier*
        , TOKEN::TypeQualifier*
        , TOKEN::FunctionSpecifier*
        , TOKEN::AlignmentSpecifier*
        , TOKEN::Pointer*
        , TOKEN::DirectDeclarator*
        , TOKEN::BlockItemList*
        , TOKEN::InitDeclarator*
        , TOKEN::ConstantExpression*
        , TOKEN::AtomicTypeSpecifier*
        , TOKEN::StructOrUnionSpecifier*
        , TOKEN::EnumSpecifier*
        , TOKEN::TypedefName*
        , TOKEN::TypeName*
        , TOKEN::TypeQualifierList*
        , TOKEN::AssignmentExpression*
        , TOKEN::ParameterTypeList*
        , TOKEN::IdentifierList*
        , TOKEN::BlockItem*
        , TOKEN::Initializer*
        , TOKEN::ConditionalExpression*
        , TOKEN::StructOrUnion*
        , TOKEN::StructDeclarationList*
        , TOKEN::EnumeratorList*
        , TOKEN::SpecifierQualifierList*
        , TOKEN::AbstractDeclarator*
        , TOKEN::UnaryExpression*
        , TOKEN::AssignmentOperator*
        , TOKEN::ParameterList*
        , TOKEN::Statement*
        , TOKEN::InitializerList*
        , TOKEN::LogicalORExpression*
        , TOKEN::Expression*
        , TOKEN::StructDeclaration*
        , TOKEN::Enumerator*
        , TOKEN::DirectAbstractDeclarator*
        , TOKEN::PostfixExpression*
        , TOKEN::UnaryOperator*
        , TOKEN::CastExpression*
        , TOKEN::ParameterDeclaration*
        , TOKEN::LabeledStatement*
        , TOKEN::ExpressionStatement*
        , TOKEN::SelectionStatement*
        , TOKEN::IterationStatement*
        , TOKEN::JumpStatement*
        , TOKEN::Designation*
        , TOKEN::LogicalANDExpression*
        , TOKEN::StructDeclaratorList*
        , TOKEN::PrimaryExpression*
        , TOKEN::ArgumentExpressionList*
        , TOKEN::DesignatorList*
        , TOKEN::InclusiveORExpression*
        , TOKEN::StructDeclarator*
        , TOKEN::GenericSelection*
        , TOKEN::Designator*
        , TOKEN::ExclusiveORExpression*
        , TOKEN::GenericAssocList*
        , TOKEN::ANDExpression*
        , TOKEN::GenericAssociation*
        , TOKEN::EqualityExpression*
        , TOKEN::RelationalExpression*
        , TOKEN::ShiftExpression*
        , TOKEN::AdditiveExpression*
        , TOKEN::MultiplicativeExpression*
        , TOKEN::AttributeSpecifier*
        , TOKEN::AttributeSpecifierList*
        , TOKEN::AttributeStatement*
        , TOKEN::BasicAsm*
        , TOKEN::ExtendedAsm*
        , TOKEN::AsmQualifiers*
        , TOKEN::AsmStatement*
        , TOKEN::IncludingFile*>;

    std::size_t mBegin{0ull};
    std::size_t mEnd{0ull};
    Var mToken{std::in_place_type<TOKEN::Token*>, nullptr};
};

template<class Token>
Token *TreeGenerator::createFromCache()
{
    for(auto &&[iter, last]{mCacheMap.equal_range(mIdx)}; iter != last; iter++)
    {
        if(std::holds_alternative<Token*>(iter->second->mToken))
        {
            mIdx = iter->second->mEnd;
            return std::get<Token*>(iter->second->mToken)->copy();
        }
    }

    return nullptr;
}

template<class Token>
Token *TreeGenerator::registerToCache(Token *token
    , std::size_t beginIdx)
{
    auto &&element{new MapElement{beginIdx, mIdx, token->copy()}};
    mCacheMap.emplace(beginIdx, element);
    return token;
}

}

#endif