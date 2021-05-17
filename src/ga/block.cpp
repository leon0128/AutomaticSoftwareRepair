#include <utility>
#include <iostream>
#include <limits>

#include "../token.hpp"
#include "block.hpp"

namespace GA
{

Block *Block::createBlock(const TOKEN::TranslationUnit *tu
    , std::size_t scopeId)
{
    using namespace TOKEN;

    Block *block{new Block{scopeId}};

    for(const auto *ed : tu->seq)
    {
        if(std::holds_alternative<Declaration*>(ed->var))
            block->decls.push_back(std::get<Declaration*>(ed->var)->statementId);
        else if(std::holds_alternative<FunctionDefinition*>(ed->var))
        {
            const auto *fd{std::get<FunctionDefinition*>(ed->var)};
            block->stats.emplace_back(fd->statementId
                , createBlock(fd->cs
                    , fd->scopeId));
        }
        else
            variantError("TOKEN::ExternalDeclaration");
    }

    return block;
}

Block *Block::createBlock(const TOKEN::CompoundStatement *cs
    , std::size_t scopeId)
{
    using namespace TOKEN;

    Block *block{new Block{scopeId}};
    
    if(bool(cs->bil))
    {
        for(const auto *bi : cs->bil->seq)
        {
            if(std::holds_alternative<Declaration*>(bi->var))
                block->decls.push_back(std::get<Declaration*>(bi->var)->statementId);
            else if(std::holds_alternative<Statement*>(bi->var))
                block->stats.push_back(createPair(std::get<Statement*>(bi->var)));
            else
                variantError("TOKEN::BlockItem");
        }
    }

    return block;
}

Block *Block::createBlock(const TOKEN::LabeledStatement *ls)
{
    using namespace TOKEN;
    using LS = LabeledStatement;

    Block *block{new Block{}};

    const Statement *statement{nullptr};
    if(std::holds_alternative<LS::Si_s>(ls->var))
        statement = std::get<LS::Si_s>(ls->var).s;
    else if(std::holds_alternative<LS::Sce_s>(ls->var))
        statement = std::get<LS::Sce_s>(ls->var).s;
    else if(std::holds_alternative<LS::Ss>(ls->var))
        statement = std::get<LS::Ss>(ls->var).s;
    else
    {
        variantError("TOKEN::LabeledStatement");
        return nullptr;
    }

    block->scopeId = statement->scopeId;
    block->stats.push_back(createPair(statement));

    return block;
}

Block *Block::createBlock(const TOKEN::SelectionStatement *ss
    , std::size_t scopeId)
{
    using namespace TOKEN;
    using SS = SelectionStatement;

    Block *block{nullptr};

    if(std::holds_alternative<SS::Si_e_s>(ss->var)
        || std::holds_alternative<SS::Si_e_s>(ss->var))
    {
        block = new Block{scopeId};

        const Statement *ifStatement{nullptr};
        const Statement *elseStatement{nullptr};
        if(std::holds_alternative<SS::Si_e_s>(ss->var))
            ifStatement = std::get<SS::Si_e_s>(ss->var).s;
        else
        {
            const auto &s{std::get<SS::Si_e_s_s>(ss->var)};
            ifStatement = s.s0;
            elseStatement = s.s1;
        }

        block->stats.push_back(ifStatement
            ? std::make_pair(std::numeric_limits<std::size_t>::max()
                , createBlock(ifStatement))
            : std::make_pair(std::numeric_limits<std::size_t>::max()
                , new Block{scopeId}));
        block->stats.push_back(elseStatement
            ? std::make_pair(std::numeric_limits<std::size_t>::max()
                , createBlock(elseStatement))
            : std::make_pair(std::numeric_limits<std::size_t>::max()
                , new Block{scopeId}));
    }
    else if(std::holds_alternative<SS::Ss_e_s>(ss->var))
        block = createBlock(std::get<SS::Ss_e_s>(ss->var).s);
    else
        variantError("TOKEN::SelectionStatement");
    
    return block;
}

Block *Block::createBlock(const TOKEN::IterationStatement *is)
{
    using namespace TOKEN;
    using IS = IterationStatement;

    Block *block{nullptr};

    const Statement *statement;
    if(std::holds_alternative<IS::Sw_e_s>(is->var))
        statement = std::get<IS::Sw_e_s>(is->var).s;
    else if(std::holds_alternative<IS::Sd_s_e>(is->var))
        statement = std::get<IS::Sd_s_e>(is->var).s;
    else if(std::holds_alternative<IS::Sf_e_e_e_s>(is->var))
        statement = std::get<IS::Sf_e_e_e_s>(is->var).s;
    else if(std::holds_alternative<IS::Sf_d_e_e_s>(is->var))
        statement = std::get<IS::Sf_d_e_e_s>(is->var).s;
    else
    {
        variantError("TOKEN::IterationStatement");
        return nullptr;
    }

    block = createBlock(statement);

    return block;
}

Block *Block::createBlock(const TOKEN::Statement *statement)
{
    using namespace TOKEN;

    Block *block{nullptr};

    if(std::holds_alternative<CompoundStatement*>(statement->var))
        block = createBlock(std::get<CompoundStatement*>(statement->var)
            , statement->scopeId);
    else
    {
        block = new Block{statement->scopeId};
        block->stats.push_back(createPair(statement));
    }

    return block;
}

std::pair<std::size_t, Block*> Block::createPair(const TOKEN::Statement *statement)
{
    using namespace TOKEN;

    std::pair<std::size_t, Block*> ret{statement->statementId, nullptr};

    if(std::holds_alternative<LabeledStatement*>(statement->var))
        ret.second = createBlock(std::get<LabeledStatement*>(statement->var));
    else if(std::holds_alternative<CompoundStatement*>(statement->var))
        ret.second = createBlock(std::get<CompoundStatement*>(statement->var)
            , statement->scopeId);
    else if(std::holds_alternative<ExpressionStatement*>(statement->var))
        ;
    else if(std::holds_alternative<SelectionStatement*>(statement->var))
        ret.second = createBlock(std::get<SelectionStatement*>(statement->var)
            , statement->scopeId);
    else if(std::holds_alternative<IterationStatement*>(statement->var))
        ret.second = createBlock(std::get<IterationStatement*>(statement->var));
    else if(std::holds_alternative<JumpStatement*>(statement->var))
        ;
    else
        variantError("TOKEN::Statement");

    return ret;
}

bool Block::variantError(const std::string &className)
{
    std::cerr << "GA::Block error:\n"
        "    what: std::variant type has unexpected type.\n"
        "    class: " << className
        << std::endl;
    return false;
}

Block::~Block()
{
    for(auto &&p : stats)
        delete p.second;
}

Block *Block::copy() const
{
    std::vector<std::size_t> d{decls};
    std::vector<std::pair<std::size_t
        , Block*>> s{stats};

    for(auto &&p : s)
    {
        if(bool(p.second))
            p.second = p.second->copy();
    }
    
    return new Block{scopeId
        , std::move(d)
        , std::move(s)};
}

}