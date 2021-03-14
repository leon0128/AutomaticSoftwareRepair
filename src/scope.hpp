#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <unordered_set>
#include <functional>
#include <array>
#include <any>

#include "identifier.hpp"

namespace SCOPE
{

class Scope
{
public:
    using Set = std::unordered_set<Identifier>;

    inline static constexpr const std::size_t NUM_NAMESPACE{4ull};
    enum class ScopeTag : unsigned char;
    enum class NamespaceTag : unsigned char;

    Scope(Scope*
        , ScopeTag);
    ~Scope();
    Scope(const Scope&) = delete;
    Scope(Scope&&) = delete;

    Scope *addChild(ScopeTag);
    Scope *getParent() const noexcept;
    bool addIdentifier(const Identifier&
        , NamespaceTag
        , ScopeTag);
    bool addIdentifier(const Identifier&
        , NamespaceTag);

    ScopeTag scopeTag() const noexcept
        {return mScopeTag;}

private:
    Set &set(NamespaceTag tag)
        {return mArr[static_cast<std::size_t>(tag)];}

    Scope *mParent;
    std::vector<Scope*> mChildren;
    ScopeTag mScopeTag;
    std::array<Set, NUM_NAMESPACE> mArr;
};

enum class Scope::ScopeTag : unsigned char
{
    FILE
    , FUNCTION
    , BLOCK
    , FUNCTION_PROTOTYPE
};

enum class Scope::NamespaceTag : unsigned char
{
    LABEL
    , TAG
    , MEMBER
    , OTHER
};

}

#endif