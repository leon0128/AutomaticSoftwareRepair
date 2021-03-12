#include <iostream>

#include "token.hpp"
#include "normalizer.hpp"

Normalizer::Normalizer(const TOKEN::TranslationUnit *tu)
    : mTranslationUnit{tu != nullptr ? tu->copy() : nullptr}
{
}

Normalizer::~Normalizer()
{
    delete mTranslationUnit;
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