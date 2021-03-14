#include <iostream>

#include "scope.hpp"

namespace SCOPE
{

Scope::Scope(Scope *parent
    , ScopeTag tag)
    : mParent{parent}
    , mChildren{}
    , mScopeTag{tag}
    , mArr{Set{}, Set{}, Set{}, Set{}}
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

Scope *Scope::getParent() const noexcept
{
    return mParent;
}

bool Scope::addIdentifier(const Identifier &id
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

    auto &&[iter, isSuccessful]{scope->set(nTag).emplace(id)};
    if(!isSuccessful)
    {
        std::cerr << "Scope error:\n"
            "    what: fail to add identifier.\n"
            "    key: " << id.key() << "\n"
            "    id: " << id.id()
            << std::endl;
    }

    return isSuccessful;
}

bool Scope::addIdentifier(const Identifier &id
    , NamespaceTag nTag)
{
    return addIdentifier(id, nTag, scopeTag());
}

}