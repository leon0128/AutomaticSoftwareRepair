#include <iostream>
#include <utility>

#include "utility/output.hpp"
#include "divider.hpp"

namespace ANALYZER
{

bool Divider::execute(TOKEN::TranslationUnit *tu)
{
    if(!divide(tu))
        return false;

    return true;
}

bool Divider::divide(TOKEN::TranslationUnit *tu)
{
    using namespace TOKEN;

    for(auto *ed : tu->seq)
    {
        if(std::holds_alternative<FunctionDefinition*>(ed->var))
        {
            if(!divide(std::get<FunctionDefinition*>(ed->var)->cs))
                return false;
        }
    }

    return true;
}

bool Divider::divide(TOKEN::CompoundStatement *cs)
{
    using namespace TOKEN;

    if(cs->bil != nullptr)
    {
        for(std::size_t i{0ull};
            i < cs->bil->seq.size();
            i++)
        {
            std::size_t preSize{cs->bil->seq.size()};
            auto *bi{cs->bil->seq.at(i)};
            if(std::holds_alternative<Declaration*>(bi->var))
            {
                if(!divide(cs->bil
                    , i + 1ull
                    , std::get<Declaration*>(bi->var)))
                    return false;
            }
            else if(std::holds_alternative<Statement*>(bi->var))
            {
                if(!divide(std::get<Statement*>(bi->var)))
                    return false;
            }

            i += cs->bil->seq.size() - preSize;
        }
    }

    return true;
}

bool Divider::divide(TOKEN::BlockItemList *bil
    , std::size_t pos
    , TOKEN::Declaration *declaration)
{
    using namespace TOKEN;

    if(!std::holds_alternative<Declaration::Sds_idl>(declaration->var))
        return true;
    
    auto &&s{std::get<Declaration::Sds_idl>(declaration->var)};
    
    if(!s.idl)
        return true;
    
    for(auto *id : s.idl->seq)
    {
        if(std::holds_alternative<InitDeclarator::Sd_i>(id->var))
        {
            auto *statement{createStatement(id)};
            if(!statement)
                continue;
            
            bil->seq.insert(bil->seq.begin() + pos++
                , new BlockItem{statement});
        }
    }

    return true;
}

bool Divider::divide(TOKEN::Statement *statement)
{
    using namespace TOKEN;

    if(std::holds_alternative<LabeledStatement*>(statement->var))
        return divide(std::get<LabeledStatement*>(statement->var));
    else if(std::holds_alternative<CompoundStatement*>(statement->var))
        return divide(std::get<CompoundStatement*>(statement->var));
    else if(std::holds_alternative<ExpressionStatement*>(statement->var))
        return divide(std::get<ExpressionStatement*>(statement->var));
    else if(std::holds_alternative<SelectionStatement*>(statement->var))
        return divide(std::get<SelectionStatement*>(statement->var));
    else if(std::holds_alternative<IterationStatement*>(statement->var))
        return divide(std::get<IterationStatement*>(statement->var));
    else if(std::holds_alternative<JumpStatement*>(statement->var))
        return divide(std::get<JumpStatement*>(statement->var));
    else if(std::holds_alternative<AttributeStatement*>(statement->var))
        return divide(std::get<AttributeStatement*>(statement->var));
    else if(std::holds_alternative<AsmStatement*>(statement->var))
        return divide(std::get<AsmStatement*>(statement->var));

    return true;
}

bool Divider::divide(TOKEN::LabeledStatement *ls)
{
    using namespace TOKEN;
    using LS = LabeledStatement;

    Statement *statement{nullptr};

    if(std::holds_alternative<LS::Si_s>(ls->var))
        statement = std::get<LS::Si_s>(ls->var).s;
    else if(std::holds_alternative<LS::Sce_s>(ls->var))
        statement = std::get<LS::Sce_s>(ls->var).s;
    else if(std::holds_alternative<LS::Ss>(ls->var))
        statement = std::get<LS::Ss>(ls->var).s;
    
    if(statement != nullptr)
        return divide(statement);
    
    return true;
}

bool Divider::divide(TOKEN::ExpressionStatement*)
{
    return true;
}

bool Divider::divide(TOKEN::SelectionStatement *ss)
{
    using namespace TOKEN;
    using SS = SelectionStatement;

    std::pair<Statement*, Statement*> stats{nullptr, nullptr};
    if(std::holds_alternative<SS::Si_e_s>(ss->var))
        stats.first = std::get<SS::Si_e_s>(ss->var).s;
    else if(std::holds_alternative<SS::Si_e_s_s>(ss->var))
    {
        stats.first = std::get<SS::Si_e_s_s>(ss->var).s0;
        stats.second = std::get<SS::Si_e_s_s>(ss->var).s1;
    }
    else if(std::holds_alternative<SS::Ss_e_s>(ss->var))
        stats.first = std::get<SS::Ss_e_s>(ss->var).s;

    if(stats.first != nullptr)
    {
        if(!divide(stats.first))
            return false;
    }
    if(stats.second != nullptr)
    {
        if(!divide(stats.second))
            return false;
    }

    return true;
}

bool Divider::divide(TOKEN::IterationStatement *is)
{
    using namespace TOKEN;
    using IS = IterationStatement;

    Statement *statement{nullptr};
    if(std::holds_alternative<IS::Sw_e_s>(is->var))
        statement = std::get<IS::Sw_e_s>(is->var).s;
    else if(std::holds_alternative<IS::Sd_s_e>(is->var))
        statement = std::get<IS::Sd_s_e>(is->var).s;
    else if(std::holds_alternative<IS::Sf_e_e_e_s>(is->var))
        statement = std::get<IS::Sf_e_e_e_s>(is->var).s;
    else if(std::holds_alternative<IS::Sf_d_e_e_s>(is->var))
        statement = std::get<IS::Sf_d_e_e_s>(is->var).s;
    
    if(statement != nullptr)
    {
        if(!divide(statement))
            return false;
    }

    return true;
}

bool Divider::divide(TOKEN::JumpStatement*)
{
    return true;
}

bool Divider::divide(TOKEN::AttributeStatement*)
{
    return true;
}

bool Divider::divide(TOKEN::AsmStatement*)
{
    return true;
}

TOKEN::Statement *Divider::createStatement(TOKEN::InitDeclarator *id)
{
    using namespace TOKEN;
    using ID = InitDeclarator;
    using DD = DirectDeclarator;

    auto &&s{std::get<ID::Sd_i>(id->var)};

    Statement *statement{nullptr};
    if(std::holds_alternative<AssignmentExpression*>(s.i->var))
    {
        auto *assignmentExpression{std::get<AssignmentExpression*>(s.i->var)->copy()};
        auto *primaryExpression{new PrimaryExpression{std::get<DD::Si>(s.d->dd->seq.front()).i->copy()}};
        auto *postfixExpression{new PostfixExpression{decltype(PostfixExpression::seq){}}};
        postfixExpression->seq.emplace_back(PostfixExpression::Spe{primaryExpression});
        auto *unaryExpression{new UnaryExpression{UnaryExpression::Spe{postfixExpression}}};
        auto *assignmentOperator{new AssignmentOperator{AssignmentOperator::Tag::ASSIGNMENT}};
        auto *newAssignmentExpression{new AssignmentExpression{AssignmentExpression::Sue_ao_ae{unaryExpression
            , assignmentOperator
            , assignmentExpression}}};
        auto *expression{new Expression{decltype(Expression::seq){}}};
        expression->seq.push_back(newAssignmentExpression);
        auto *expressionStatement{new ExpressionStatement{expression}};
        statement = new Statement{expressionStatement};
    }
    else if(std::holds_alternative<InitializerList*>(s.i->var))
    {
        unsupportedWarning("InitializerList");
        return nullptr;
    }

    auto *asl0{s.asl0};
    auto *declarator{s.d};
    auto *asl1{s.asl1};

    delete s.i;
    
    id->var.emplace<InitDeclarator::Sd>(asl0, declarator, asl1);

    return statement;
}

bool Divider::unsupportedWarning(const std::string &className)
{
    std::cerr << OUTPUT::charYellowCode
        << "ANALYZER::Divider::unsupportedWarning():\n"
        << OUTPUT::resetCode
        << "    what: failed to support to divide class.\n"
        << "    className: " << className
        << std::endl;
    return false;
}

}