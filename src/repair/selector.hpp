#ifndef REPAIR_SELECTOR_HPP
#define REPAIR_SELECTOR_HPP

#include <utility>
#include <vector>
#include <deque>
#include <unordered_map>
#include <optional>
#include <mutex>
#include <functional>

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
        CAN_CONVERT
        , CONVERT
        , CREATE_CACHE
    };

public:
    Selector();
    ~Selector();

    Selector(const Selector&) = delete;
    Selector(Selector&&) = delete;

    // arguments:
    //  statementId: statement id to be based
    //  scopeId: scope id to be added
    // return value:
    //  whether statement can convert
    bool canConvert(std::size_t statementId
        , std::size_t scopeId);

    // arguments:
    //  statementId: statement id to be based
    //  scopeId: scope id to be added
    //  alternativeIds: storage of used alternative ids
    // return value:
    //  first: statement id that was converted
    //  second: whether an error was occured
    std::pair<std::size_t, bool> convert(std::size_t statementId
        , std::size_t scopeId
        , std::deque<std::size_t> &alternativeIds);

private:
    // calculates candidates and creates cache
    bool calculateCandidates();

    // selects alternative ids.
    // selected ids are stored into mAlternativeIdsRef.
    bool selectAlternativeIds();

    // check validity of candidates(mCache).
    // if candidates are invalid, that candidates value is deleted
    //  and mCache stores std::nullopt instead of deleted candidates.
    // if error has occured when this function is called,
    //  false is returned.
    bool checkValidity();

    // insert visible identifier-id to argument.
    bool getVisibleIdentifierList(const std::shared_ptr<IDENTIFIER::Identifier>&
        , std::deque<std::size_t>&);
    // remove different type to identifier from vector for argument.
    bool getSameTypeIdentifier(const std::shared_ptr<IDENTIFIER::Identifier>&
        , std::deque<std::size_t>&);

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

    bool conversionError() const;
    bool invalidVariantError(const std::string &className) const;
    bool supportError(const std::string&) const;

    // key: pair of statement id(first) and scope id(second)
    // value: if statement can convert another one, object has a map
    //         otherwise, object has nullopt value. 
    //        vector: identifier ids that appear in statement.
    //        multimap's key: identifier id that indicates base identifier.
    //        multimap's value: identifier id that indicates a candidates of base identifier.
    // PairHash: PairHash class is helper of cache and calculates hash of pair(std::pair<std::size_t, std::size_t>).
    struct PairHash
    {
        std::size_t operator()(const std::pair<std::size_t, std::size_t> &pair) const noexcept
            {return (pair.first << sizeof(pair.first) * 4) + pair.second;}
    };
    static std::unordered_map<std::pair<std::size_t, std::size_t>
        , std::optional<std::pair<std::vector<std::size_t>, std::unordered_multimap<std::size_t, std::size_t>>>
        , PairHash> mCache;
    static std::mutex mCacheMutex;

    Tag mTag;
    std::size_t mStatementId; // statement id to be converted
    std::size_t mScopeId; // scope id to insert
    static std::deque<std::size_t> mAlternativeIdsInit; // initial value of mAlternativeIdsRef
    std::reference_wrapper<std::deque<std::size_t>> mAlternativeIdsRef; // reference of container of alternative ids
    std::size_t mAlternativeIdsIndex;
};

}

#endif