#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <unordered_map>
#include <array>
#include <string>
#include <vector>

namespace IDENTIFIER{class Identifier;}

namespace SCOPE
{

class Scope
{
public:
    enum class ScopeTag : signed char;
    enum class NamespaceTag : signed char;

    Scope(Scope*, ScopeTag);
    ~Scope();
    Scope(const Scope&) = delete;
    Scope(Scope&&) = delete;

    Scope *addChild(ScopeTag);
    Scope *getParent() const;

    bool addIdentifier(ScopeTag, NamespaceTag, const std::string&, IDENTIFIER::Identifier*);
    IDENTIFIER::Identifier *getIdentifier(NamespaceTag, const std::string&);

private:
    Scope *mParent;
    std::vector<Scope*> mChildren;
    ScopeTag mScopeTag;
    std::array<std::unordered_map<std::string, IDENTIFIER::Identifier*>, 4> mMap;
};

enum class Scope::ScopeTag : signed char
{
    FILE
    , FUNCTION
    , BLOCK
    , FUNCTION_PROTOTYPE
};

enum class Scope::NamespaceTag : signed char
{
    LABEL = 0
    , TAG = 1
    , MEMBER = 2
    , OTHER = 3
};

}

#endif