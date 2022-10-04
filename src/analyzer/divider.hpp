#ifndef ANALYZER_DIVIDER_HPP
#define ANALYZER_DIVIDER_HPP

#include <vector>
#include <string>

#include "common/token.hpp"

namespace ANALYZER
{

class Divider
{
public:

    static bool execute(TOKEN::TranslationUnit*);

private:
    static bool divide(TOKEN::TranslationUnit*);
    static bool divide(TOKEN::CompoundStatement*);
    static bool divide(TOKEN::Statement*);
    static bool divide(TOKEN::LabeledStatement*);
    static bool divide(TOKEN::ExpressionStatement*);
    static bool divide(TOKEN::SelectionStatement*);
    static bool divide(TOKEN::IterationStatement*);
    static bool divide(TOKEN::JumpStatement*);
    static bool divide(TOKEN::AttributeStatement*);
    static bool divide(TOKEN::AsmStatement*);
    
    static bool divide(TOKEN::BlockItemList*
        , std::size_t pos
        , TOKEN::Declaration*);

    // create Statement and remove Initializer.
    // InitDeclarator should have InitDeclarator::Sd_i.
    static TOKEN::Statement *createStatement(TOKEN::InitDeclarator*);

    static bool unsupportedError(const std::string &what);

public:
    Divider() = delete;
};

}

#endif