#include <iostream>

#include "identifier.hpp"
#include "scope.hpp"

namespace SCOPE
{

Scope::Scope(Scope *parent
    , ScopeTag tag)
    : mParent{parent}
    , mChildren{}
    , mScopeTag{tag}
    , mArr{Map{}, Map{}, Map{}, Map{}}
{
}

Scope::~Scope()
{
    for(auto &&s : mChildren)
        delete s;
}

Scope *Scope::addChild(ScopeTag tag)
{
    Scope *child{new Scope{this, tag}};
    mChildren.push_back(child);
    return child;
}

bool Scope::addIdentifier(const std::shared_ptr<IDENTIFIER::Identifier> &id
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
        return false;
    }

    auto &&[iter, isSuccessful]{scope->map(nTag).emplace(id->key(), id)};
    if(!isSuccessful)
    {
        std::cerr << "Scope error:\n"
            "    what: fail to add identifier.\n"
            "    key: " << id->key() << "\n"
            "    id: " << id->id()
            << std::endl;
    }

    return isSuccessful;
}

bool Scope::addIdentifier(const std::shared_ptr<IDENTIFIER::Identifier> &id
    , NamespaceTag nTag)
{
    return addIdentifier(id, nTag, scopeTag());
}

std::shared_ptr<IDENTIFIER::Identifier> Scope::getIdentifier(const std::string &str
    , NamespaceTag tag
    , bool isCurrent)
{
    if(isCurrent)
    {
        if(auto &&iter{map(tag).find(str)};
            iter != map(tag).end())
            return iter->second;
    }
    else
    {
        if(auto &&iter{map(tag).find(str)};
            iter != map(tag).end())
            return iter->second;
    }

    return {};
}

}