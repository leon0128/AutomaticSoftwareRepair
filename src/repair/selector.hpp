#ifndef REPAIR_SELECTOR_HPP
#define REPAIR_SELECTOR_HPP

#include <functional>
#include <string>
#include <memory>
#include <deque>

#include "common/token.hpp"

namespace IDENTIFIER
{
    class Identifier;
}

namespace REPAIR
{

class Selector
{
private:
    enum class Tag
    {
        
    };

    inline static std::deque<std::size_t> INIT_VALUE{};
    inline static std::deque<std::deque<std::size_t>> CANDIDATE_INIT_VALUE{};

public:
    Selector();
    ~Selector();

    Selector(const Selector&) = delete;
    Selector(Selector&&) = delete;

    // remove previous value
    bool execute(std::size_t scopeId
        , const TOKEN::Statement*
        , std::deque<std::size_t>&);
    // get candidate identifiers.
    bool execute(std::size_t scopeId
        , const TOKEN::Statement*
        , std::deque<std::deque<std::size_t>>&);
    // convert iddentifier-id to idList
    bool execute(const std::deque<std::size_t>&
        , const TOKEN::Statement*);

    // if statement fits to scope, this return true.
    // otherwise, this return false.
    // if statement has attribute-specifier,
    // return value is false.
    bool isFittable(std::size_t scopeId
        , const TOKEN::Statement*);

private:
    bool clear();

    // insert visible identifier-id to argument.
    bool getVisibleIdentifierList(const std::shared_ptr<IDENTIFIER::Identifier>&
        , std::deque<std::size_t>&);
    // remove different type to identifier from vector for argument.
    bool getSameTypeIdentifier(const std::shared_ptr<IDENTIFIER::Identifier>&
        , std::deque<std::size_t>&);
    // select one from vector for argument.
    // result: size of vector == 1
    bool selectOne(const std::deque<std::size_t>&
        , std::size_t&);

    bool convert(TOKEN::Identifier*);

    bool select(TOKEN::Identifier*);

    bool select(const TOKEN::Statement*);
    bool select(const TOKEN::JumpStatement*);
    bool select(const TOKEN::ExpressionStatement*);
    bool select(const TOKEN::LabeledStatement*);
    bool select(const TOKEN::CompoundStatement*);
    bool select(const TOKEN::SelectionStatement*);
    bool select(const TOKEN::IterationStatement*);
    bool select(const TOKEN::Expression*);
    bool select(const TOKEN::AssignmentExpression*);
    bool select(const TOKEN::ConditionalExpression*);
    bool select(const TOKEN::LogicalORExpression*);
    bool select(const TOKEN::LogicalANDExpression*);
    bool select(const TOKEN::InclusiveORExpression*);
    bool select(const TOKEN::ExclusiveORExpression*);
    bool select(const TOKEN::ANDExpression*);
    bool select(const TOKEN::EqualityExpression*);
    bool select(const TOKEN::RelationalExpression*);
    bool select(const TOKEN::ShiftExpression*);
    bool select(const TOKEN::AdditiveExpression*);
    bool select(const TOKEN::MultiplicativeExpression*);
    bool select(const TOKEN::CastExpression*);
    bool select(const TOKEN::UnaryExpression*);
    bool select(const TOKEN::PostfixExpression*);
    bool select(const TOKEN::PrimaryExpression*);
    bool select(const TOKEN::Constant*);
    bool select(const TOKEN::GenericSelection*);
    bool select(const TOKEN::GenericAssocList*);
    bool select(const TOKEN::GenericAssociation*);
    bool select(const TOKEN::EnumerationConstant*);
    bool select(const TOKEN::ConstantExpression*);
    bool select(const TOKEN::StaticAssertDeclaration*);

    bool select(const TOKEN::ArgumentExpressionList*);
    bool select(const TOKEN::InitializerList*);
    bool select(const TOKEN::Designation*);
    bool select(const TOKEN::DesignatorList*);
    bool select(const TOKEN::Designator*);
    bool select(const TOKEN::Initializer*);
    
    bool select(const TOKEN::TypeName*);
    bool select(const TOKEN::SpecifierQualifierList*);
    bool select(const TOKEN::TypeSpecifier*);
    bool select(const TOKEN::AtomicTypeSpecifier*);
    bool select(const TOKEN::StructOrUnionSpecifier*);
    bool select(const TOKEN::StructDeclarationList*);
    bool select(const TOKEN::StructDeclaration*);
    bool select(const TOKEN::StructDeclaratorList*);
    bool select(const TOKEN::StructDeclarator*);
    bool select(const TOKEN::Declarator*);
    bool select(const TOKEN::DirectDeclarator*);
    bool select(const TOKEN::ParameterTypeList*);
    bool select(const TOKEN::ParameterList*);
    bool select(const TOKEN::ParameterDeclaration*);
    bool select(const TOKEN::DeclarationSpecifiers*);
    bool select(const TOKEN::AlignmentSpecifier*);
    bool select(const TOKEN::EnumSpecifier*);
    bool select(const TOKEN::EnumeratorList*);
    bool select(const TOKEN::Enumerator*);
    bool select(const TOKEN::TypedefName*);
    bool select(const TOKEN::AbstractDeclarator*);
    bool select(const TOKEN::Pointer*);
    bool select(const TOKEN::DirectAbstractDeclarator*);

    bool select(const TOKEN::AttributeSpecifierList*);
    bool select(const TOKEN::AttributeSpecifier*);
    bool select(const TOKEN::AttributeStatement*);

    bool select(const TOKEN::AsmQualifiers*);
    bool select(const TOKEN::BasicAsm*);
    bool select(const TOKEN::ExtendedAsm*);
    bool select(const TOKEN::AsmStatement*);

    bool invalidVariantError(const std::string &className) const;
    bool candidateError() const;
    bool supportError(const std::string&) const;
    bool lackIdError() const;
    bool unusedIdError() const;

    bool mIsSelection;
    bool mIsCandidate;
    bool mIsFittable;

    std::size_t mScopeId;
    std::reference_wrapper<std::deque<std::size_t>> mIds;
    std::reference_wrapper<std::deque<std::deque<std::size_t>>> mCandidateIds;

    std::size_t mIdx;
    std::reference_wrapper<const std::deque<std::size_t>> mCIds;

    std::vector<bool> mIsFittables;
};

}

#endif