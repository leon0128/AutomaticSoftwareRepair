#include <iostream>
#include <unordered_map>

#include "utility/output.hpp"
#include "identifier.hpp"
#include "scope.hpp"

inline namespace COMMON
{

namespace SCOPE
{

Scope::Scope(Scope *parent
    , ScopeTag tag)
    : mId{NEXT_ID++}
    , mParent{parent}
    , mChildren{}
    , mScopeTag{tag}
    , mArr{Map{}, Map{}, Map{}, Map{}}
{
    SCOPE_MAP.emplace(mId
        , this);
}

Scope::~Scope()
{
    for(auto &&s : mChildren)
    {
        SCOPE_MAP.erase(s->id());
        delete s;
    }
}

Scope *Scope::addChild(ScopeTag tag)
{
    Scope *child{new Scope{this, tag}};
    mChildren.push_back(child);
    return child;
}

Scope::ReturnType Scope::addIdentifier(const std::shared_ptr<IDENTIFIER::Identifier> &id
    , NamespaceTag nTag
    , ScopeTag sTag)
{
    Scope *scope{this};
    for(;
        scope != nullptr
            ? scope->scopeTag() != sTag
            : false;
        scope = scope->getParent())
        ;
    
    if(scope == nullptr)
    {
        std::cerr << "Scope error:\n"
            "    what: fail to find scope.\n"
            "    tag: " << static_cast<std::size_t>(sTag)
            << std::endl;
        return {std::nullopt};
    }

    auto &&[iter, isSuccessful]{scope->map(nTag).emplace(id->key(), id)};
    if(!isSuccessful)
    {
        std::cerr << "Scope error:\n"
            "    what: fail to add identifier.\n"
            "    key: " << id->key() << "\n"
            "    id: " << id->id()
            << std::endl;
        return {std::nullopt};
    }

    IDENTIFIER_MAP.emplace(id->id()
        , id);

    return {PairType{iter->second, scope->id()}};
}

Scope::ReturnType Scope::addIdentifier(const std::shared_ptr<IDENTIFIER::Identifier> &id
    , NamespaceTag nTag)
{
    return addIdentifier(id, nTag, scopeTag());
}

Scope::ReturnType Scope::getIdentifier(const std::string &str
    , NamespaceTag tag
    , bool isCurrent)
{
    if(isCurrent)
    {
        if(auto &&iter{map(tag).find(str)};
            iter != map(tag).end())
            return {PairType{iter->second, id()}};
    }
    else
    {
        for(auto &&scope{this};
            scope != nullptr;
            scope = scope->getParent())
        {
            if(auto &&iter{scope->map(tag).find(str)};
                iter != scope->map(tag).end())
                return {PairType{iter->second, scope->id()}};
        }
    }

    return {std::nullopt};
}

void Scope::outputData(std::size_t numIndent) const
{
    static const std::unordered_map<ScopeTag, std::string> scopeNameMap
        {{ScopeTag::FILE, "FILE"}
            , {ScopeTag::FUNCTION, "FUNCTION"}
            , {ScopeTag::BLOCK, "BLOCK"}
            , {ScopeTag::FUNCTION_PROTOTYPE, "FUNCTION_PROTOTYPE"}};
    static const std::unordered_map<NamespaceTag, std::string> namespaceNameMap
        {{NamespaceTag::LABEL, "LABEL"}
            , {NamespaceTag::TAG, "TAG"}
            , {NamespaceTag::MEMBER, "MEMBER"}
            , {NamespaceTag::OTHER, "OTHER"}};

    auto &&indentedCout{[&](std::size_t num)
        -> std::ostream&
    {
        return std::cout << std::string(4ull * num, ' ');
    }};

    indentedCout(numIndent) << "=== scope-info ===" << std::endl;

    indentedCout(numIndent) << "scope-id: " << id() << std::endl;
    indentedCout(numIndent) << "parent-id: ";
    if(mParent != nullptr)
        std::cout << mParent->id() << std::endl;
    else
        std::cout << "NONE" << std::endl;
    indentedCout(numIndent) << "scope-tag: " << scopeNameMap.at(scopeTag()) << std::endl;

    indentedCout(numIndent) << "namespace:" << std::endl;
    for(auto &&[tag, tagName]: namespaceNameMap)
    {
        indentedCout(numIndent + 1ull) << tagName << std::endl;
        for(auto &&[str, identifier] : map(tag))
            indentedCout(numIndent + 2ull) << str << std::endl;
    }

    indentedCout(numIndent) << "children:" << std::endl;
    for(auto &&child : mChildren)
        child->outputData(numIndent + 1ull);

    indentedCout(numIndent) << "=== ========= ===" << std::endl;
}

}

}