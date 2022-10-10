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
    static bool divide(TOKEN::ExpressionStatement*);
    static bool divide(TOKEN::JumpStatement*);
    static bool divide(TOKEN::AttributeStatement*);
    static bool divide(TOKEN::AsmStatement*);
    static bool divide(TOKEN::Statement*);
    static bool divide(TOKEN::LabeledStatement*);
    static bool divide(TOKEN::SelectionStatement*);
    static bool divide(TOKEN::IterationStatement*);

    static bool divide(TOKEN::BlockItemList*
        , std::size_t pos
        , TOKEN::Declaration*);

    static bool divide(TOKEN::Statement*
        , TOKEN::IterationStatement*);
    static bool divide(TOKEN::Statement*
        , TOKEN::IterationStatement*
        , TOKEN::IterationStatement::Sf_d_e_e_s&);

    // create Statement and remove Initializer.
    // InitDeclarator should have InitDeclarator::Sd_i.
    static TOKEN::Statement *createStatement(TOKEN::InitDeclarator*);

    static bool unsupportedWarning(const std::string &className);

public:
    Divider() = delete;
};

}

#endif