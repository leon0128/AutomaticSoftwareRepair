#ifndef SIMILARITY_REPRESENTATION_CREATOR_HPP
#define SIMILARITY_REPRESENTATION_CREATOR_HPP

#include <deque>
#include <string>
#include <utility>

#include "common/token.hpp"

namespace SIM
{

// base class
class RepresentationCreator;
// derived class
class OriginalRepresentationCreator;
class Type1RepresentationCreator;
class Type2RepresentationCreator;
class Type3RepresentationCreator;

// same implementation as original
class RepresentationCreator
{
public:
    // public static member functions
    // create representataion
    // empty if error has occured.
    static std::deque<Representation::Element*> create(const std::string &filename
        , const TOKEN::TranslationUnit*);
    
    // create representations and register it at Representation::reps
    static bool createAndRegister(const std::string &filename
        , const TOKEN::TranslationUnit*);

    // public member functions
    RepresentationCreator(std::size_t gramSize);
    virtual ~RepresentationCreator() = 0;

    // move only
    RepresentationCreator(const RepresentationCreator&) = delete;
    RepresentationCreator(RepresentationCreator&&) = default;

    bool execute(const TOKEN::TranslationUnit*);

    std::size_t gramSize() const noexcept
        {return mGramSize;}
    auto &&functionTokens() const noexcept
        {return mFunctionTokens;}
    auto &&functionTokens() noexcept
        {return mFunctionTokens;}

protected:
    enum class TypeTag : unsigned char;

    static const std::unordered_map<TypeTag, std::string> mTypeTagMap;

    // example of effect:
    //  gram size: 2
    //  tokens:
    //      before: {"int", "main", "(", ")"}
    //      after: {"intmain", "main(", "()"}
    bool concatenateTokens();

    // protected member functions
    virtual bool process(const TOKEN::TranslationUnit*);
    virtual bool process(const TOKEN::FunctionDefinition*);
    virtual bool process(const TOKEN::DeclarationSpecifiers*);
    virtual bool process(const TOKEN::Declarator*);
    virtual bool process(const TOKEN::DeclarationList*);
    virtual bool process(const TOKEN::CompoundStatement*);
    virtual bool process(const TOKEN::StorageClassSpecifier*);
    virtual bool process(const TOKEN::TypeSpecifier*);
    virtual bool process(const TOKEN::FunctionSpecifier*);
    virtual bool process(const TOKEN::AlignmentSpecifier*);
    virtual bool process(const TOKEN::Pointer*);
    virtual bool process(const TOKEN::DirectDeclarator*);
    virtual bool process(const TOKEN::Declaration*);
    virtual bool process(const TOKEN::BlockItemList*);
    virtual bool process(const TOKEN::TypeQualifierList*);
    virtual bool process(const TOKEN::Identifier*);
    virtual bool process(const TOKEN::AssignmentExpression*);
    virtual bool process(const TOKEN::ParameterTypeList*);
    virtual bool process(const TOKEN::IdentifierList*);
    virtual bool process(const TOKEN::InitDeclaratorList*);
    virtual bool process(const TOKEN::StaticAssertDeclaration*);
    virtual bool process(const TOKEN::BlockItem*);
    virtual bool process(const TOKEN::TypeQualifier*);
    virtual bool process(const TOKEN::ConditionalExpression*);
    virtual bool process(const TOKEN::UnaryExpression*);
    virtual bool process(const TOKEN::AssignmentOperator*);
    virtual bool process(const TOKEN::ParameterList*);
    virtual bool process(const TOKEN::InitDeclarator*);
    virtual bool process(const TOKEN::ConstantExpression*);
    virtual bool process(const TOKEN::StringLiteral*);
    virtual bool process(const TOKEN::Statement*);
    virtual bool process(const TOKEN::LogicalORExpression*);
    virtual bool process(const TOKEN::Expression*);
    virtual bool process(const TOKEN::PostfixExpression*);
    virtual bool process(const TOKEN::UnaryOperator*);
    virtual bool process(const TOKEN::CastExpression*);
    virtual bool process(const TOKEN::TypeName*);
    virtual bool process(const TOKEN::ParameterDeclaration*);
    virtual bool process(const TOKEN::Initializer*);
    virtual bool process(const TOKEN::EncodingPrefix*);
    virtual bool process(const TOKEN::LabeledStatement*);
    virtual bool process(const TOKEN::ExpressionStatement*);
    virtual bool process(const TOKEN::SelectionStatement*);
    virtual bool process(const TOKEN::IterationStatement*);
    virtual bool process(const TOKEN::JumpStatement*);
    virtual bool process(const TOKEN::SCharSequence*);
    virtual bool process(const TOKEN::LogicalANDExpression*);
    virtual bool process(const TOKEN::PrimaryExpression*);
    virtual bool process(const TOKEN::ArgumentExpressionList*);
    virtual bool process(const TOKEN::InitializerList*);
    virtual bool process(const TOKEN::SpecifierQualifierList*);
    virtual bool process(const TOKEN::AbstractDeclarator*);
    virtual bool process(const TOKEN::InclusiveORExpression*);
    virtual bool process(const TOKEN::Constant*);
    virtual bool process(const TOKEN::GenericSelection*);
    virtual bool process(const TOKEN::Designation*);
    virtual bool process(const TOKEN::AtomicTypeSpecifier*);
    virtual bool process(const TOKEN::StructOrUnionSpecifier*);
    virtual bool process(const TOKEN::EnumSpecifier*);
    virtual bool process(const TOKEN::TypedefName*);
    virtual bool process(const TOKEN::DirectAbstractDeclarator*);
    virtual bool process(const TOKEN::ExclusiveORExpression*);
    virtual bool process(const TOKEN::IntegerConstant*);
    virtual bool process(const TOKEN::FloatingConstant*);
    virtual bool process(const TOKEN::EnumerationConstant*);
    virtual bool process(const TOKEN::CharacterConstant*);
    virtual bool process(const TOKEN::GenericAssocList*);
    virtual bool process(const TOKEN::DesignatorList*);
    virtual bool process(const TOKEN::StructOrUnion*);
    virtual bool process(const TOKEN::StructDeclarationList*);
    virtual bool process(const TOKEN::EnumeratorList*);
    virtual bool process(const TOKEN::ANDExpression*);
    virtual bool process(const TOKEN::GenericAssociation*);
    virtual bool process(const TOKEN::Designator*);
    virtual bool process(const TOKEN::StructDeclaration*);
    virtual bool process(const TOKEN::Enumerator*);
    virtual bool process(const TOKEN::EqualityExpression*);
    virtual bool process(const TOKEN::StructDeclaratorList*);
    virtual bool process(const TOKEN::RelationalExpression*);
    virtual bool process(const TOKEN::StructDeclarator*);
    virtual bool process(const TOKEN::ShiftExpression*);
    virtual bool process(const TOKEN::AdditiveExpression*);
    virtual bool process(const TOKEN::MultiplicativeExpression*);

    virtual bool process(const TOKEN::Token*);
    virtual bool process(const TOKEN::Keyword*);
    virtual bool process(const TOKEN::Punctuator*);

    virtual bool process(const TOKEN::AttributeSpecifier*);
    virtual bool process(const TOKEN::AttributeSpecifierList*);
    virtual bool process(const TOKEN::AttributeStatement*);

    virtual bool process(const TOKEN::BasicAsm*);
    virtual bool process(const TOKEN::ExtendedAsm*);
    virtual bool process(const TOKEN::AsmQualifiers*);
    virtual bool process(const TOKEN::AsmStatement*);

    // effects:
    //  mFunctionTokens.push_back();
    //  mFunctionTokens.back().first = [function-name];
    bool setFunctionName(const TOKEN::Declarator*);
    // effects:
    //  mFunctionTokens.back().second.emplace_back(token);
    template<class Str>
    void addToken(Str &&token)
        {mFunctionTokens.back().second.emplace_back(std::forward<Str>(token));}

    // process against sequence
    // just call process for each element
    template<class Seq>
    bool processAgainstSequence(const Seq &seq);
    // process against sequence
    // call process for each element and add puctuator
    template<class Seq>
    bool processAgainstSequence(const Seq &seq
        , const std::string &punctuator);

    bool variantError(const std::string &className) const;
    bool tokenSizeError(const std::string &functionName) const;

    // protected member variables
    std::size_t mGramSize;
    // first: function names
    // second: tokens
    std::deque<std::pair<std::string, std::deque<std::string>>> mFunctionTokens;
};

enum class RepresentationCreator::TypeTag : unsigned char
{
    DATA_TYPE
    , CLASS_TYPE
    , KEYWORD
    , OPERATOR
    , STRING_LITERAL
    , NUMBER
    , IDENTIFIER
};

template<class Seq>
bool RepresentationCreator::processAgainstSequence(const Seq &seq)
{
    for(auto &&e : seq)
    {
        if(!process(e))
            return false;
    }

    return true;
}

template<class Seq>
bool RepresentationCreator::processAgainstSequence(const Seq &seq
    , const std::string &punctuator)
{
    for(std::size_t i{0ull}; i < seq.size(); i++)
    {
        if(!process(seq[i]))
            return false;

        if(i + 1ull != seq.size())
            addToken(punctuator);
    }

    return true;
}

class OriginalRepresentationCreator : public RepresentationCreator
{
public:
    OriginalRepresentationCreator(std::size_t gramSize)
        : RepresentationCreator{gramSize}{}
    ~OriginalRepresentationCreator() = default;
};

class Type1RepresentationCreator : public RepresentationCreator
{
public:
    Type1RepresentationCreator(std::size_t gramSize)
        : RepresentationCreator{gramSize}{}
    ~Type1RepresentationCreator() = default;
};

class Type2RepresentationCreator : public RepresentationCreator
{
public:
    Type2RepresentationCreator(std::size_t gramSize)
        : RepresentationCreator{gramSize}{}
    ~Type2RepresentationCreator() = default;

protected:
    virtual bool process(const TOKEN::TypeSpecifier*) override;
    virtual bool process(const TOKEN::Identifier*) override;
    virtual bool process(const TOKEN::StringLiteral*) override;
    virtual bool process(const TOKEN::StructOrUnionSpecifier*) override;
    virtual bool process(const TOKEN::EnumSpecifier*) override;
    virtual bool process(const TOKEN::TypedefName*) override;
    virtual bool process(const TOKEN::IntegerConstant*) override;
    virtual bool process(const TOKEN::FloatingConstant*) override;
    virtual bool process(const TOKEN::CharacterConstant*) override;
    
};

class Type3RepresentationCreator : public Type2RepresentationCreator
{
public:
    Type3RepresentationCreator(std::size_t gramSize)
        : Type2RepresentationCreator{gramSize}{}
    ~Type3RepresentationCreator() = default;

protected:
    virtual bool process(const TOKEN::StorageClassSpecifier*) override;
    virtual bool process(const TOKEN::FunctionSpecifier*) override;
    virtual bool process(const TOKEN::AlignmentSpecifier*) override;
    virtual bool process(const TOKEN::Pointer*) override;
    virtual bool process(const TOKEN::DirectDeclarator*) override;
    virtual bool process(const TOKEN::ParameterTypeList*) override;
    virtual bool process(const TOKEN::StaticAssertDeclaration*) override;
    virtual bool process(const TOKEN::TypeQualifier*) override;
    virtual bool process(const TOKEN::ConditionalExpression*) override;
    virtual bool process(const TOKEN::UnaryExpression*) override;
    virtual bool process(const TOKEN::AssignmentOperator*) override;
    virtual bool process(const TOKEN::InitDeclarator*) override;
    virtual bool process(const TOKEN::LogicalORExpression*) override;
    virtual bool process(const TOKEN::PostfixExpression*) override;
    virtual bool process(const TOKEN::UnaryOperator*) override;
    virtual bool process(const TOKEN::LabeledStatement*) override;
    virtual bool process(const TOKEN::SelectionStatement*) override;
    virtual bool process(const TOKEN::IterationStatement*) override;
    virtual bool process(const TOKEN::JumpStatement*) override;
    virtual bool process(const TOKEN::LogicalANDExpression*) override;
    virtual bool process(const TOKEN::InclusiveORExpression*) override;
    virtual bool process(const TOKEN::GenericSelection*) override;
    virtual bool process(const TOKEN::Designation*) override;
    virtual bool process(const TOKEN::AtomicTypeSpecifier*) override;
    virtual bool process(const TOKEN::EnumSpecifier*) override;
    virtual bool process(const TOKEN::DirectAbstractDeclarator*) override;
    virtual bool process(const TOKEN::ExclusiveORExpression*) override;
    virtual bool process(const TOKEN::StructOrUnion*) override;
    virtual bool process(const TOKEN::ANDExpression*) override;
    virtual bool process(const TOKEN::GenericAssociation*) override;
    virtual bool process(const TOKEN::Enumerator*) override;
    virtual bool process(const TOKEN::EqualityExpression*) override;
    virtual bool process(const TOKEN::RelationalExpression*) override;
    virtual bool process(const TOKEN::ShiftExpression*) override;
    virtual bool process(const TOKEN::AdditiveExpression*) override;
    virtual bool process(const TOKEN::MultiplicativeExpression*) override;

    virtual bool process(const TOKEN::Keyword*) override;
    virtual bool process(const TOKEN::Punctuator*) override;

    virtual bool process(const TOKEN::AttributeSpecifier*) override;

    virtual bool process(const TOKEN::BasicAsm*) override;
    virtual bool process(const TOKEN::ExtendedAsm*) override;
    virtual bool process(const TOKEN::AsmQualifiers*) override;
};

}

#endif