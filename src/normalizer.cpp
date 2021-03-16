#include <iostream>

#include "token.hpp"
#include "scope.hpp"
#include "normalizer.hpp"

Normalizer::Normalizer(const TOKEN::TranslationUnit *tu)
    : mTranslationUnit{tu != nullptr ? tu->copy() : nullptr}
    , mScope{new SCOPE::Scope{nullptr, SCOPE::Scope::ScopeTag::FILE}}
{
}

Normalizer::~Normalizer()
{
    delete mTranslationUnit;
    delete mScope;
}

bool Normalizer::execute()
{
    if(mTranslationUnit == nullptr)
    {
        std::cerr << "Normalizer error:\n"
            "    what: translation-unit is null.\n"
            << std::flush;
        return false;
    }

    

    return true;
}