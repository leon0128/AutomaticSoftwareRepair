#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include "token.hpp"

class Scope;

class Analyzer
{
private:
    static const std::unordered_map<std::string, TOKEN::Keyword::Tag> KEYWORD_MAP;

public:
    using Sequence = std::vector<TOKEN::PreprocessingToken*>;

    Analyzer(const std::string &file
        , const Sequence &seq);
    ~Analyzer();
    Analyzer(const Analyzer&) = delete;
    Analyzer(Analyzer&&) = delete;

    bool execute();
    TOKEN::TranslationUnit *translationUnit() const noexcept
        {return mTranslationUnit;}

private:
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

    TOKEN::IntegerConstant *convIntegerConstant();
    TOKEN::FloatingConstant *convFloatingConstant();
    TOKEN::EnumerationConstant *convEnumerationConstant();
    TOKEN::CharacterConstant *convCharacterConstant();

    // if token is matching, idx is increment
    bool isMatch(TOKEN::Keyword::Tag);
    bool isMatch(TOKEN::Punctuator::Tag);

    std::string mFile;
    const Sequence &mSeq;
    std::size_t mIdx;
    Scope *mScope;
    TOKEN::TranslationUnit *mTranslationUnit;
};

#endif