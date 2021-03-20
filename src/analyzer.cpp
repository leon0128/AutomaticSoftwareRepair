#include <iostream>

#include "identifier.hpp"
#include "type.hpp"
#include "scope.hpp"
#include "analyzer.hpp"

Analyzer::Analyzer()
    : mFlags{}
    , mScope{nullptr}
{
}

Analyzer::~Analyzer()
{
}

bool Analyzer::execute(const TOKEN::TranslationUnit *tu)
{
    if(!tu)
        return true;

    if(!analyze(tu))
        return false;
    
    return true;
}

bool Analyzer::analyze(const TOKEN::TranslationUnit *tu)
{
    mScope = new SCOPE::Scope(mScope
        , SCOPE::Scope::ScopeTag::FILE);

    for(const auto &ed : tu->seq)
    {
        if(std::holds_alternative<TOKEN::FunctionDefinition*>(ed->var))
        {
            if(!analyze(std::get<TOKEN::FunctionDefinition*>(ed->var)))
                return false;
        }
        else if(std::holds_alternative<TOKEN::Declaration*>(ed->var))
        {
            if(!analyze(std::get<TOKEN::Declaration*>(ed->var)))
                return false;
        }
        else
            variantError("ExternalDeclaration");
    }

    return true;
}