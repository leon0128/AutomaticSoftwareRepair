#ifndef COMMON_SCOPE_HPP
#define COMMON_SCOPE_HPP

#include <unordered_map>
#include <functional>
#include <optional>
#include <utility>
#include <array>
#include <any>
#include <memory>
#include <vector>
#include <deque>
#include <mutex>
#include <utility>

inline namespace COMMON
{

namespace IDENTIFIER
{
    class Identifier;
}

namespace SCOPE
{

class Scope;

class Scope
{
private:
    inline static std::size_t NEXT_ID{0ull};
    inline static std::unordered_map<std::size_t
        , Scope*> SCOPE_MAP{};
    inline static std::recursive_mutex mScopeMapMutex{};

    // first: scope-id that indicates translation-unit.
    // second: deque of included file. ex. {"<stdio.h>, "\"header.h\"", ...}
    inline static std::unordered_map<std::size_t
        , std::deque<std::string>> INCLUDING_FILE_MAP{};
    inline static std::recursive_mutex mIncludingFileMapMutex{};

    static std::size_t nextIdSafely();

public:
    using PairType = std::pair<std::shared_ptr<IDENTIFIER::Identifier>
        , std::size_t>;
    using ReturnType = std::optional<PairType>;

    enum class ScopeTag : unsigned char;
    enum class NamespaceTag : unsigned char;

    inline static constexpr const std::size_t NUM_NAMESPACE{4ull};

    using Map = std::unordered_map<std::string
        , std::shared_ptr<IDENTIFIER::Identifier>>;
    using Array = std::array<Map
        , NUM_NAMESPACE>;

    inline static auto &&scopeMap()
        {return SCOPE_MAP;}
    inline static auto &&includingFileMap()
        {return INCLUDING_FILE_MAP;}
    inline static auto &&includingFileMapMutex()
        {return mIncludingFileMapMutex;}

    Scope(Scope*
        , ScopeTag);
    ~Scope();
    Scope(const Scope&) = delete;
    Scope(Scope&&) = delete;

    Scope *addChild(ScopeTag);
    Scope *getParent() const noexcept
        {return mParent;}
    
    ReturnType addIdentifier(const std::shared_ptr<IDENTIFIER::Identifier>&
                , NamespaceTag
                , ScopeTag);
    ReturnType addIdentifier(const std::shared_ptr<IDENTIFIER::Identifier>&
                , NamespaceTag);
    ReturnType getIdentifier(const std::string&
                , NamespaceTag
                , bool isCurrent);

    std::size_t id() const noexcept
        {return mId;}
    ScopeTag scopeTag() const noexcept
        {return mScopeTag;}
    Map &map(NamespaceTag tag)
        {return mArr[static_cast<std::size_t>(tag)];}
    const Map &map(NamespaceTag tag) const noexcept
        {return mArr[static_cast<std::size_t>(tag)];}

    void outputData(std::size_t numIndent = 0ull) const;

private:
    std::size_t mId;
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

}

#endif