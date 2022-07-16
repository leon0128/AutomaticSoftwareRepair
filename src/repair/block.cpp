#include <iostream>
#include <limits>
#include <utility>

#include "../analyzer.hpp"
#include "block.hpp"

namespace REPAIR::BLOCK
{

Block::Block()
    : mScopeId{std::numeric_limits<std::size_t>::max()}
    , mDecls{}
    , mStats{}
{
}

Block::~Block()
{
    for(auto &&statPair : mStats)
        delete statPair.second;
}

Block::Block(const TOKEN::TranslationUnit *tu
    , std::size_t scopeId)
    : mScopeId{scopeId}
    , mDecls{}
    , mStats{}
{
    using namespace TOKEN;

    for(const auto *ed : tu->seq)
    {
        if(std::holds_alternative<Declaration*>(ed->var))
            mDecls.push_back(std::get<Declaration*>(ed->var)->statementId);
        else if(std::holds_alternative<FunctionDefinition*>(ed->var))
        {
            const auto *fd{std::get<FunctionDefinition*>(ed->var)};
            mStats.emplace_back(fd->statementId
                , new Block(fd->cs
                    , fd->scopeId));
        }
        else
            variantError("ExternalDeclaration");
    }
}

bool Block::isIfBlock() const
{
    return !mStats.empty()
        && mStats.front().first == std::numeric_limits<std::size_t>::max();
}

bool Block::add(const std::vector<std::size_t> &pos
    , std::size_t statId)
{
    using namespace TOKEN;

    Block *block{getBlock(pos)};

    block->mStats.insert(block->mStats.begin() + pos.back()
        , createStatPair(std::get<std::shared_ptr<Statement>>(Analyzer::statementMap().at(statId)).get()
            , block->scopeId()));

    return true;
}

bool Block::subtract(const std::vector<std::size_t> &pos)
{
    Block *block{getBlock(pos)};

    delete block->mStats.at(pos.back()).second;
    block->mStats.erase(block->mStats.begin() + pos.back());

    return true;
}

bool Block::replace(const std::vector<std::size_t> &pos
    , std::size_t statId)
{
    using namespace TOKEN;

    Block *block{getBlock(pos)};

    delete block->mStats.at(pos.back()).second;
    block->mStats.at(pos.back()) = createStatPair(std::get<std::shared_ptr<Statement>>(Analyzer::statementMap().at(statId)).get()
        , block->scopeId());

    return true;
}

TOKEN::TranslationUnit *Block::createTranslationUnit() const
{
    using namespace TOKEN;

    auto *tu{new TranslationUnit{decltype(TranslationUnit::seq){}}};

    for(const auto &id : mDecls)
        tu->seq.push_back(new ExternalDeclaration{std::get<std::shared_ptr<Declaration>>(Analyzer::statementMap().at(id))->copy()});

    for(const auto &pair : mStats)
    {
        auto &&oldfd{std::get<std::shared_ptr<FunctionDefinition>>(Analyzer::statementMap().at(pair.first))};
        auto *fd{new FunctionDefinition{oldfd->ds->copy()
            , oldfd->d->copy()
            , oldfd->dl
                ? oldfd->dl->copy()
                : nullptr
            , pair.second->createCompoundStatement()}};
        fd->scopeId = oldfd->scopeId;
        fd->statementId = oldfd->statementId;
    
        tu->seq.push_back(new ExternalDeclaration{fd});
    }

    return tu;
}

Block *Block::copy() const
{
    Block *block{new Block{}};
    block->mScopeId = mScopeId;
    block->mDecls = mDecls;

    for(const auto &pair : mStats)
    {
        block->mStats.emplace_back(pair.first
            , pair.second
                ? pair.second->copy()
                : nullptr);
    }

    return block;
}

Block::Block(const TOKEN::CompoundStatement *cs
    , std::size_t scopeId)
    : mScopeId{scopeId}
    , mDecls{}
    , mStats{}
{
    using namespace TOKEN;

    if(cs->bil != nullptr)
    {
        for(const auto *bi : cs->bil->seq)
        {
            if(std::holds_alternative<Declaration*>(bi->var))
                mDecls.push_back(std::get<Declaration*>(bi->var)->statementId);
            else if(std::holds_alternative<Statement*>(bi->var))
                mStats.push_back(createStatPair(std::get<Statement*>(bi->var)));
            else
                variantError("BlockItem");
        }
    }
}

Block::Block(const TOKEN::LabeledStatement *ls)
    : mScopeId{std::numeric_limits<std::size_t>::max()}
    , mDecls{}
    , mStats{}
{
    using namespace TOKEN;
    using LS = LabeledStatement;

    const Statement *subStat{nullptr};
    if(std::holds_alternative<LS::Si_s>(ls->var))
        subStat = std::get<LS::Si_s>(ls->var).s;
    else if(std::holds_alternative<LS::Sce_s>(ls->var))
        subStat = std::get<LS::Sce_s>(ls->var).s;
    else if(std::holds_alternative<LS::Ss>(ls->var))
        subStat = std::get<LS::Ss>(ls->var).s;
    else
        variantError("LabeledStatement");

    move(Block{subStat});
}

Block::Block(const TOKEN::SelectionStatement *ss
    , std::size_t scopeId)
    : mScopeId{scopeId}
    , mDecls{}
    , mStats{}
{
    using namespace TOKEN;
    using SS = SelectionStatement;

    if(std::holds_alternative<SS::Si_e_s>(ss->var)
        || std::holds_alternative<SS::Si_e_s_s>(ss->var))
    {
        const Statement *ifStat{nullptr};
        const Statement *elseStat{nullptr};

        if(std::holds_alternative<SS::Si_e_s>(ss->var))
            ifStat = std::get<SS::Si_e_s>(ss->var).s;
        else
        {
            ifStat = std::get<SS::Si_e_s_s>(ss->var).s0;
            elseStat = std::get<SS::Si_e_s_s>(ss->var).s1;
        }

        mStats.push_back(ifStat
            ? std::make_pair(std::numeric_limits<std::size_t>::max()
                , new Block{ifStat})
            : std::make_pair(std::numeric_limits<std::size_t>::max()
                , new Block{scopeId}));
        mStats.push_back(elseStat
            ? std::make_pair(std::numeric_limits<std::size_t>::max()
                , new Block{elseStat})
            : std::make_pair(std::numeric_limits<std::size_t>::max()
                , new Block{scopeId}));
    }
    else if(std::holds_alternative<SS::Ss_e_s>(ss->var))
        move(Block{std::get<SS::Ss_e_s>(ss->var).s});
    else
        variantError("SelectionStatement");
}

Block::Block(const TOKEN::IterationStatement *is)
    : mScopeId{std::numeric_limits<std::size_t>::max()}
    , mDecls{}
    , mStats{}
{
    using namespace TOKEN;
    using IS = IterationStatement;

    const Statement *subStat{nullptr};

    if(std::holds_alternative<IS::Sw_e_s>(is->var))
        subStat = std::get<IS::Sw_e_s>(is->var).s;
    else if(std::holds_alternative<IS::Sd_s_e>(is->var))
        subStat = std::get<IS::Sd_s_e>(is->var).s;
    else if(std::holds_alternative<IS::Sf_e_e_e_s>(is->var))
        subStat = std::get<IS::Sf_e_e_e_s>(is->var).s;
    else if(std::holds_alternative<IS::Sf_d_e_e_s>(is->var))
        subStat = std::get<IS::Sf_d_e_e_s>(is->var).s;
    else
        variantError("IterationStatement");

    move(Block{subStat});
}

Block::Block(const TOKEN::Statement *statement)
    : mScopeId{statement->scopeId}
    , mDecls{}
    , mStats{}
{
    using namespace TOKEN;

    if(!statement)
        nullptrError("Statement");
    else
    {
        if(std::holds_alternative<CompoundStatement*>(statement->var))
            move(Block{std::get<CompoundStatement*>(statement->var)
                , statement->scopeId});
        else
            mStats.push_back(createStatPair(statement));
    }
}

Block::Block(std::size_t scopeId)
    : mScopeId{scopeId}
    , mDecls{}
    , mStats{}
{
}

Block *Block::getBlock(const std::vector<std::size_t> &pos)
{
    Block *block{this};
    for(std::size_t i{0ull};
        i + 1ull < pos.size();
        i++)
        block = block->mStats.at(pos[i]).second;
    
    return block;
}

StatPair Block::createStatPair(const TOKEN::Statement *statement)
{
    using namespace TOKEN;

    StatPair statPair{statement->statementId
        , nullptr};
    
    if(std::holds_alternative<LabeledStatement*>(statement->var))
        statPair.second = new Block{std::get<LabeledStatement*>(statement->var)};
    else if(std::holds_alternative<CompoundStatement*>(statement->var))
        statPair.second = new Block{std::get<CompoundStatement*>(statement->var)
            , statement->scopeId};
    else if(std::holds_alternative<SelectionStatement*>(statement->var))
        statPair.second = new Block{std::get<SelectionStatement*>(statement->var)
            , statement->scopeId};
    else if(std::holds_alternative<IterationStatement*>(statement->var))
        statPair.second = new Block{std::get<IterationStatement*>(statement->var)};
    else if(std::holds_alternative<ExpressionStatement*>(statement->var)
        || std::holds_alternative<JumpStatement*>(statement->var)
        || std::holds_alternative<AttributeStatement*>(statement->var)
        || std::holds_alternative<AsmStatement*>(statement->var))
        ;
    else
        variantError("Statement");
    
    return statPair;
}

StatPair Block::createStatPair(const TOKEN::Statement *statement
    , std::size_t scopeId)
{
    auto &&statPair{createStatPair(statement)};
    if(statPair.second != nullptr)
        statPair.second->changeScopeId(scopeId);
    
    return statPair;
}

void Block::changeScopeId(std::size_t scopeId)
{
    mScopeId = scopeId;

    for(auto &&pair : mStats)
    {
        if(pair.second != nullptr)
            pair.second->changeScopeId(scopeId);
    }
}

TOKEN::CompoundStatement *Block::createCompoundStatement() const
{
    using namespace TOKEN;

    auto *cs{new CompoundStatement{new BlockItemList{decltype(BlockItemList::seq){}}}};
    for(const auto &id : mDecls)
        cs->bil->seq.push_back(new BlockItem{std::get<std::shared_ptr<Declaration>>(Analyzer::statementMap().at(id))->copy()});

    for(const auto &pair : mStats)
        cs->bil->seq.push_back(new BlockItem{createStatement(pair)});

    return cs;
}

TOKEN::Statement *Block::createStatement(const StatPair &pair) const
{
    using namespace TOKEN;
    using LS = LabeledStatement;
    using CS = CompoundStatement;
    using ES = ExpressionStatement;
    using SS = SelectionStatement;
    using IS = IterationStatement;
    using JS = JumpStatement;
    using AS = AttributeStatement;
    using AsmS = AsmStatement;

    const auto &oldPtr{std::get<std::shared_ptr<Statement>>(Analyzer::statementMap().at(pair.first))};
    Statement *newStatement{nullptr};

    newStatement = new Statement{std::monostate{}};
    newStatement->scopeId = oldPtr->scopeId;
    newStatement->statementId = oldPtr->statementId;
    
    if(std::holds_alternative<LS*>(oldPtr->var))
    {
        const auto *oldLs{std::get<LS*>(oldPtr->var)};
        if(std::holds_alternative<LS::Si_s>(oldLs->var))
        {
            const auto &s{std::get<LS::Si_s>(oldLs->var)};
            newStatement->var.emplace<LS*>(new LS{LS::Si_s{s.i->copy()
                , s.asl->copy()
                , pair.second->createStatement()}});
        }
        else if(std::holds_alternative<LS::Sce_s>(oldLs->var))
        {
            const auto &s{std::get<LS::Sce_s>(oldLs->var)};
            newStatement->var.emplace<LS*>(new LS{LS::Sce_s{s.ce->copy()
                , pair.second->createStatement()}});
        }
        else if(std::holds_alternative<LS::Ss>(oldLs->var))
            newStatement->var.emplace<LS*>(new LS{LS::Ss{pair.second->createStatement()}});
    }
    else if(std::holds_alternative<CS*>(oldPtr->var))
        newStatement->var.emplace<CS*>(pair.second->createCompoundStatement());
    else if(std::holds_alternative<ES*>(oldPtr->var))
        newStatement->var.emplace<ES*>(std::get<ES*>(oldPtr->var)->copy());
    else if(std::holds_alternative<SS*>(oldPtr->var))
    {
        const auto *oldSs{std::get<SS*>(oldPtr->var)};
        if(std::holds_alternative<SS::Si_e_s>(oldSs->var))
        {
            const auto &s{std::get<SS::Si_e_s>(oldSs->var)};
            newStatement->var.emplace<SS*>(new SS{SS::Si_e_s_s{s.e->copy()
                , pair.second->mStats.front().second->createStatement()
                , pair.second->mStats.back().second->createStatement()}});
        }
        else if(std::holds_alternative<SS::Si_e_s_s>(oldSs->var))
        {
            const auto &s{std::get<SS::Si_e_s_s>(oldSs->var)};
            newStatement->var.emplace<SS*>(new SS{SS::Si_e_s_s{s.e->copy()
                , pair.second->mStats.front().second->createStatement()
                , pair.second->mStats.back().second->createStatement()}});
        }
        else if(std::holds_alternative<SS::Ss_e_s>(oldSs->var))
        {
            const auto &s{std::get<SS::Ss_e_s>(oldSs->var)};
            newStatement->var.emplace<SS*>(new SS{SS::Ss_e_s{s.e->copy()
                , pair.second->createStatement()}});
        }
    }
    else if(std::holds_alternative<IS*>(oldPtr->var))
    {
        const auto *oldIs{std::get<IS*>(oldPtr->var)};
        if(std::holds_alternative<IS::Sw_e_s>(oldIs->var))
        {
            const auto &s{std::get<IS::Sw_e_s>(oldIs->var)};
            newStatement->var.emplace<IS*>(new IS{IS::Sw_e_s{s.e->copy()
                , pair.second->createStatement()}});
        }
        else if(std::holds_alternative<IS::Sd_s_e>(oldIs->var))
        {
            const auto &s{std::get<IS::Sd_s_e>(oldIs->var)};
            newStatement->var.emplace<IS*>(new IS{IS::Sd_s_e{pair.second->createStatement()
                , s.e->copy()}});
        }
        else if(std::holds_alternative<IS::Sf_e_e_e_s>(oldIs->var))
        {
            const auto &s{std::get<IS::Sf_e_e_e_s>(oldIs->var)};
            newStatement->var.emplace<IS*>(new IS{IS::Sf_e_e_e_s{s.e0 ? s.e0->copy() : nullptr
                , s.e1 ? s.e1->copy() : nullptr
                , s.e2 ? s.e2->copy() : nullptr
                , pair.second->createStatement()}});
        }
        else if(std::holds_alternative<IS::Sf_d_e_e_s>(oldIs->var))
        {
            const auto &s{std::get<IS::Sf_d_e_e_s>(oldIs->var)};
            newStatement->var.emplace<IS*>(new IS{IS::Sf_d_e_e_s{s.d->copy()
                , s.e0 ? s.e0->copy() : nullptr
                , s.e1 ? s.e1->copy() : nullptr
                , pair.second->createStatement()}});
        }
    }
    else if(std::holds_alternative<JS*>(oldPtr->var))
        newStatement->var.emplace<JS*>(std::get<JS*>(oldPtr->var)->copy());
    else if(std::holds_alternative<AS*>(oldPtr->var))
        newStatement->var.emplace<AS*>(std::get<AS*>(oldPtr->var)->copy());
    else if(std::holds_alternative<AsmS*>(oldPtr->var))
        newStatement->var.emplace<AsmS*>(std::get<AsmS*>(oldPtr->var)->copy());

    return newStatement;
}

TOKEN::Statement *Block::createStatement() const
{
    using namespace TOKEN;

    Statement *statement{nullptr};

    if(mDecls.empty() && mStats.empty())
        statement = new Statement{new ExpressionStatement{}};
    else if(mDecls.empty() && mStats.size() == 1)
        statement = createStatement(mStats.front());
    else
        statement = new Statement{createCompoundStatement()};
    
    return statement;
}

void Block::move(Block &&other)
{
    mScopeId = other.mScopeId;
    mDecls = std::move(other.mDecls);
    mStats = std::move(other.mStats);
}

bool Block::variantError(const std::string &className) const
{
    std::cerr << "Block::variantError()\n"
        "    className: " << className
        << std::endl;
    return false;
}

bool Block::nullptrError(const std::string &className) const
{
    std::cerr << "Block::nullptrError()\n"
        "    className: " << className
        << std::endl;
    return false;
}

}