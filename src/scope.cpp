#include "scope.hpp"

namespace SCOPE
{

Scope::Scope(Scope *p, ScopeTag sTag)
    : mParent(p)
    , mChildren()
    , mScopeTag(sTag)
    , mMap()
{
}

Scope::~Scope()
{
    for(auto &&m : mMap)
    {
        for(auto &&p : m)
            delete p.second;
    }
    for(auto &&s : mChildren)
        delete s;
}

Scope *Scope::addChild(ScopeTag sTag)
{
    Scope *child = new Scope(this, sTag);
    mChildren.push_back(child);
    return child;
}

Scope *Scope::getParent() const
{
    return mParent;
}

bool Scope::addIdentifier(ScopeTag sTag
    , NamespaceTag nTag
    , const std::string &str
    , IDENTIFIER::Identifier *identifier)
{
    Scope *scope = this;
    for(; scope != nullptr && scope->mScopeTag != sTag; scope = scope->mParent)
        ;

    if(scope == nullptr)
        return false;
    
    return scope->mMap[static_cast<std::size_t>(nTag)].emplace(str, identifier).second;
}

IDENTIFIER::Identifier *Scope::getIdentifier(NamespaceTag nTag
    , const std::string &str
    , bool isCurrent)
{
    if(isCurrent)
    {
        if(auto iter = mMap[static_cast<std::size_t>(nTag)].find(str);
            iter != mMap[static_cast<std::size_t>(nTag)].end())
            return iter->second;
    }
    else
    {
        for(Scope *scope = this; scope != nullptr; scope = scope->mParent)
        {
            if(auto iter = scope->mMap[static_cast<std::size_t>(nTag)].find(str);
                iter != scope->mMap[static_cast<std::size_t>(nTag)].end())
                return iter->second;
        }
    }

    return nullptr;
}

}