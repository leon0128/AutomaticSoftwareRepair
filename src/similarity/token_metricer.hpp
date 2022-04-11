#ifndef SIMILARITY_TOKEN_METRICER_HPP
#define SIMILARITY_TOKEN_METRICER_HPP

#include <deque>
#include <memory>
#include <string>

namespace TOKEN
{
    class TranslationUnit;
    class ExternalDeclaration;
    class FunctionDefinition;
    class Declaration;
    class InitDeclaratorList;
    class InitDeclarator;
    class Identifier;
    class Statement;
    class ExpressionStatement;
    class JumpStatement;
    class LabeledStatement;
    class CompoundStatement;
    class BlockItemList;
    class BlockItem;
    class SelectionStatement;
    class IterationStatement;
    class Expression;
    class AssignmentExpression;
    class AssignmentOperator;
    class ConditionalExpression;
    class LogicalORExpression;
    class LogicalANDExpression;
    class InclusiveORExpression;
    class ExclusiveORExpression;
    class ANDExpression;
    class EqualityExpression;
    class RelationalExpression;
    class ShiftExpression;
    class AdditiveExpression;
    class MultiplicativeExpression;
    class CastExpression;
    class UnaryExpression;
    class UnaryOperator;
    class PostfixExpression;
    class PrimaryExpression;
    class Constant;
    class GenericSelection;
    class GenericAssocList;
    class GenericAssociation;
    class EnumerationConstant;
    class ConstantExpression;
    class StaticAssertDeclaration;
    class DeclarationList;

    class ArgumentExpressionList;
    class InitializerList;
    class Designation;
    class DesignatorList;
    class Designator;
    class Initializer;
    class TypeName;
    class SpecifierQualifierList;
    class TypeSpecifier;
    class AtomicTypeSpecifier;
    class StructOrUnionSpecifier;
    class StructOrUnion;
    class StructDeclarationList;
    class StructDeclaration;
    class StructDeclaratorList;
    class StructDeclarator;
    class Declarator;
    class DirectDeclarator;
    class IdentifierList;
    class ParameterTypeList;
    class ParameterList;
    class ParameterDeclaration;
    class DeclarationSpecifiers;
    class StorageClassSpecifier;
    class FunctionSpecifier;
    class AlignmentSpecifier;
    class EnumSpecifier;
    class EnumeratorList;
    class Enumerator;
    class TypedefName;
    class TypeQualifier;
    class TypeQualifierList;
    class AbstractDeclarator;
    class Pointer;
    class DirectAbstractDeclarator;
}

namespace SIM
{

template<class>
class StructureTokenMetrics;

class TokenMetricer
{
public:
    TokenMetricer();

    bool execute(const std::string &filename
        , const TOKEN::TranslationUnit*);

    const auto &stms() const noexcept
        {return mSTMs;}

private:
    bool process(const TOKEN::Identifier*);
    bool process(const TOKEN::TranslationUnit*);
    bool process(const TOKEN::ExternalDeclaration*);
    bool process(const TOKEN::FunctionDefinition*);
    bool process(const TOKEN::Declaration*);
    bool process(const TOKEN::InitDeclaratorList*);
    bool process(const TOKEN::InitDeclarator*);
    bool process(const TOKEN::Statement*);
    bool process(const TOKEN::JumpStatement*);
    bool process(const TOKEN::ExpressionStatement*);
    bool process(const TOKEN::LabeledStatement*);
    bool process(const TOKEN::CompoundStatement*);
    bool process(const TOKEN::BlockItemList*);
    bool process(const TOKEN::BlockItem*);
    bool process(const TOKEN::SelectionStatement*);
    bool process(const TOKEN::IterationStatement*);
    bool process(const TOKEN::Expression*);
    bool process(const TOKEN::AssignmentExpression*);
    bool process(const TOKEN::AssignmentOperator*);
    bool process(const TOKEN::ConditionalExpression*);
    bool process(const TOKEN::LogicalORExpression*);
    bool process(const TOKEN::LogicalANDExpression*);
    bool process(const TOKEN::InclusiveORExpression*);
    bool process(const TOKEN::ExclusiveORExpression*);
    bool process(const TOKEN::ANDExpression*);
    bool process(const TOKEN::EqualityExpression*);
    bool process(const TOKEN::RelationalExpression*);
    bool process(const TOKEN::ShiftExpression*);
    bool process(const TOKEN::AdditiveExpression*);
    bool process(const TOKEN::MultiplicativeExpression*);
    bool process(const TOKEN::CastExpression*);
    bool process(const TOKEN::UnaryExpression*);
    bool process(const TOKEN::UnaryOperator*);
    bool process(const TOKEN::PostfixExpression*);
    bool process(const TOKEN::PrimaryExpression*);
    bool process(const TOKEN::Constant*);
    bool process(const TOKEN::GenericSelection*);
    bool process(const TOKEN::GenericAssocList*);
    bool process(const TOKEN::GenericAssociation*);
    bool process(const TOKEN::EnumerationConstant*);
    bool process(const TOKEN::ConstantExpression*);
    bool process(const TOKEN::StaticAssertDeclaration*);
    bool process(const TOKEN::DeclarationList*);

    bool process(const TOKEN::ArgumentExpressionList*);
    bool process(const TOKEN::InitializerList*);
    bool process(const TOKEN::Designation*);
    bool process(const TOKEN::DesignatorList*);
    bool process(const TOKEN::Designator*);
    bool process(const TOKEN::Initializer*);
    
    bool process(const TOKEN::TypeName*);
    bool process(const TOKEN::SpecifierQualifierList*);
    bool process(const TOKEN::TypeSpecifier*);
    bool process(const TOKEN::TypeQualifier*);
    bool process(const TOKEN::AtomicTypeSpecifier*);
    bool process(const TOKEN::StructOrUnionSpecifier*);
    bool process(const TOKEN::StructOrUnion*);
    bool process(const TOKEN::StructDeclarationList*);
    bool process(const TOKEN::StructDeclaration*);
    bool process(const TOKEN::StructDeclaratorList*);
    bool process(const TOKEN::StructDeclarator*);
    bool process(const TOKEN::Declarator*);
    bool process(const TOKEN::DirectDeclarator*);
    bool process(const TOKEN::IdentifierList*);
    bool process(const TOKEN::TypeQualifierList*);
    bool process(const TOKEN::ParameterTypeList*);
    bool process(const TOKEN::ParameterList*);
    bool process(const TOKEN::ParameterDeclaration*);
    bool process(const TOKEN::DeclarationSpecifiers*);
    bool process(const TOKEN::StorageClassSpecifier*);
    bool process(const TOKEN::FunctionSpecifier*);
    bool process(const TOKEN::AlignmentSpecifier*);
    bool process(const TOKEN::EnumSpecifier*);
    bool process(const TOKEN::EnumeratorList*);
    bool process(const TOKEN::Enumerator*);
    bool process(const TOKEN::TypedefName*);
    bool process(const TOKEN::AbstractDeclarator*);
    bool process(const TOKEN::Pointer*);
    bool process(const TOKEN::DirectAbstractDeclarator*);

    std::string getIdentifier(const TOKEN::Declarator*) const;

    bool invalidStatementError() const;
    bool noSupportError(const std::string&) const;
    bool invalidVariantError(const std::string &className) const;

    std::string mCurrentFilename;
    std::shared_ptr<StructureTokenMetrics<std::size_t>> mCurrentSTM;
    std::deque<std::shared_ptr<StructureTokenMetrics<std::size_t>>> mSTMs;
};

}

#endif