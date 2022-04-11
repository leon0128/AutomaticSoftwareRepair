#include <iostream>

#include "../analyzer.hpp"
#include "register.hpp"

namespace GA
{

std::optional<std::size_t> Register::execute(TOKEN::Statement *statement)
{
    return registerStatement(statement);
}

std::optional<std::size_t> Register::registerStatement(TOKEN::Statement *statement)
{
    using namespace TOKEN;

    using LS = LabeledStatement;
    using CS = CompoundStatement;
    using SS = SelectionStatement;
    using IS = IterationStatement;


    std::optional<std::size_t> subId;
    if(std::holds_alternative<LS*>(statement->var))
    {
        auto *ls{std::get<LS*>(statement->var)};

        if(std::holds_alternative<LS::Si_s>(ls->var))
            subId = registerStatement(std::get<LS::Si_s>(ls->var).s);
        else if(std::holds_alternative<LS::Sce_s>(ls->var))
            subId = registerStatement(std::get<LS::Sce_s>(ls->var).s);
        else if(std::holds_alternative<LS::Ss>(ls->var))
            subId = registerStatement(std::get<LS::Ss>(ls->var).s);
        else
        {
            variantError("LabeledStatement");
            return {std::nullopt}; 
        }

        if(!subId)
            return {std::nullopt};
    }
    else if(std::holds_alternative<CS*>(statement->var))
    {
        auto *cs{std::get<CS*>(statement->var)};

        if(bool{cs->bil})
        {
            for(auto *bi : cs->bil->seq)
            {
                if(std::holds_alternative<Declaration*>(bi->var))
                    subId = registerDeclaration(std::get<Declaration*>(bi->var));
                else if(std::holds_alternative<Statement*>(bi->var))
                    subId = registerStatement(std::get<Statement*>(bi->var));
                else
                {
                    variantError("BlockItem");
                    return {std::nullopt};
                }
            
                if(!subId)
                    return {std::nullopt};
            }
        }
    }
    else if(std::holds_alternative<SS*>(statement->var))
    {
        auto *ss{std::get<SS*>(statement->var)};
        if(std::holds_alternative<SS::Si_e_s>(ss->var))
            subId = registerStatement(std::get<SS::Si_e_s>(ss->var).s);
        else if(std::holds_alternative<SS::Si_e_s_s>(ss->var))
        {
            if(!registerStatement(std::get<SS::Si_e_s_s>(ss->var).s0))
                return {std::nullopt};
            subId = registerStatement(std::get<SS::Si_e_s_s>(ss->var).s1);
        }
        else if(std::holds_alternative<SS::Ss_e_s>(ss->var))
            subId = registerStatement(std::get<SS::Ss_e_s>(ss->var).s);
        else
        {
            variantError("SelectionStatement");
            return {std::nullopt};
        }

        if(!subId)
            return {std::nullopt};
    }
    else if(std::holds_alternative<IS*>(statement->var))
    {
        auto *is{std::get<IS*>(statement->var)};
        if(std::holds_alternative<IS::Sw_e_s>(is->var))
            subId = registerStatement(std::get<IS::Sw_e_s>(is->var).s);
        else if(std::holds_alternative<IS::Sd_s_e>(is->var))
            subId = registerStatement(std::get<IS::Sd_s_e>(is->var).s);
        else if(std::holds_alternative<IS::Sf_e_e_e_s>(is->var))
            subId = registerStatement(std::get<IS::Sf_e_e_e_s>(is->var).s);
        else if(std::holds_alternative<IS::Sf_d_e_e_s>(is->var))
            subId = registerStatement(std::get<IS::Sf_d_e_e_s>(is->var).s);
        else
        {
            variantError("IterationStatement");
            return {std::nullopt};
        }

        if(!subId)
            return {std::nullopt};
    }
    
    statement->statementId = Analyzer::addStatement(std::shared_ptr<Statement>(statement->copy()));
    return {statement->statementId};
}

std::optional<std::size_t> Register::registerDeclaration(TOKEN::Declaration *declaration)
{
    using namespace TOKEN;

    declaration->statementId = Analyzer::addStatement(std::shared_ptr<Declaration>(declaration->copy()));
    return {declaration->statementId};
}

bool Register::variantError(const std::string &className)
{
    std::cerr << "Register::variantError():\n"
        "    class name: " << className
        << std::endl;
    return false;
}

}