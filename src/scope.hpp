#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <unordered_map>
#include <functional>
#include <array>
#include <any>
#include <memory>

namespace IDENTIFIER
{
    class Identifier;
}

namespace SCOPE
{

class Scope
{
public:
    enum class ScopeTag : unsigned char;
    enum class NamespaceTag : unsigned char;

    inline static constexpr const std::size_t NUM_NAMESPACE{4ull};

    using Map = std::unordered_map<std::string
        , std::shared_ptr<IDENTIFIER::Identifier>>;
    using Array = std::array<Map
        , NUM_NAMESPACE>;

    Scope(Scope*
        , ScopeTag);
    ~Scope();
    Scope(const Scope&) = delete;
    Scope(Scope&&) = delete;

    Scope *addChild(ScopeTag);
    Scope *getParent() const noexcept
        {return mParent;}
    bool addIdentifier(const std::shared_ptr<IDENTIFIER::Identifier>&
        , NamespaceTag
        , ScopeTag);
    bool addIdentifier(const std::shared_ptr<IDENTIFIER::Identifier>&
        , NamespaceTag);
    std::shared_ptr<IDENTIFIER::Identifier> getIdentifier(const std::string&
        , NamespaceTag
        , bool isCurrent);

    ScopeTag scopeTag() const noexcept
        {return mScopeTag;}

private:
    Map &map(NamespaceTag tag)
        {return mArr[static_cast<std::size_t>(tag)];}

    Scope *mParent;
    std::vector<Scope*> mChildren;
    ScopeTag mScopeTag;
    Array mArr;
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