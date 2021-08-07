#include <utility>
#include <iostream>
#include <limits>
#include <memory>
#include <functional>
#include <algorithm>

#include "../utility/output.hpp"
#include "../token.hpp"
#include "../analyzer.hpp"
#include "representation.hpp"
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

bool Block::deleteInvalidOp(const Block *block
    , Representation &rep)
{
    std::shared_ptr<Block> tmpBlock{block->copy()};
    auto &&idxOpt{Index::createIndex(tmpBlock.get())};
    if(!idxOpt)
        return false;

    for(std::size_t i{0ull};
        i < rep.ops.size();
        i++)
    {
        decltype(operateAdd) *operateFunc{nullptr};

        switch(rep.ops[i].tag)
        {
            case(Operation::Tag::ADD):
                operateFunc = &operateAdd;
                break;
            case(Operation::Tag::SUB):
                operateFunc = &operateSub;
                break;
            case(Operation::Tag::REP):
                operateFunc = &operateRep;
                break;
        }

        if(!operateFunc(rep.ops[i]
            , tmpBlock.get()
            , idxOpt.value()))
        {
            deleteWarning(rep.ops[i]);

            rep.ops.erase(rep.ops.begin() + i);
            i--;
        }
    }

    return true;
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

    return createBlock(statement);
}

Block *Block::createBlock(const TOKEN::SelectionStatement *ss
    , std::size_t scopeId)
{
    using namespace TOKEN;
    using SS = SelectionStatement;

    Block *block{nullptr};

    if(std::holds_alternative<SS::Si_e_s>(ss->var)
        || std::holds_alternative<SS::Si_e_s_s>(ss->var))
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

bool Block::deleteWarning(const Operation &op)
{
    std::cerr << "GA::Block warning:\n"
        "    what: delete GA::Operation from GA::Representation.\n"
        "    op: ";
    op.print();
    std::cout << std::endl;

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

TOKEN::TranslationUnit *Block::createTranslationUnit() const
{
    using namespace TOKEN;

    auto *tu{new TranslationUnit{decltype(TranslationUnit::seq){}}};

    for(auto &&id : decls)
    {
        auto &&ptr{std::get<std::shared_ptr<Declaration>>(Analyzer::statementMap().at(id))};
        tu->seq.push_back(new ExternalDeclaration{ptr->copy()});
    }

    for(auto &&pair : stats)
    {
        auto &&ptr{std::get<std::shared_ptr<FunctionDefinition>>(Analyzer::statementMap().at(pair.first))};
        auto *fd{new FunctionDefinition{ptr->ds->copy()
            , ptr->d->copy()
            , ptr->dl
                ? ptr->dl->copy()
                : nullptr
            , pair.second->createCompoundStatement()}};
        fd->scopeId = ptr->scopeId;
        fd->statementId = ptr->statementId;

        tu->seq.push_back(new ExternalDeclaration{fd});
    }

    return tu;
}

std::shared_ptr<Block> Block::createBlock(const Representation &rep) const
{
    std::shared_ptr<Block> newBlock{copy()};
    auto &&idxOpt{Index::createIndex(newBlock.get())};
    if(!idxOpt)
        return {nullptr};

    for(const auto &op : rep.ops)
    {
        switch(op.tag)
        {
            case(Operation::Tag::ADD):
                operateAdd(op
                    , newBlock.get()
                    , idxOpt.value());
                break;
            case(Operation::Tag::SUB):
                operateSub(op
                    , newBlock.get()
                    , idxOpt.value());
                break;
            case(Operation::Tag::REP):
                operateRep(op
                    , newBlock.get()
                    , idxOpt.value());
                break;
        }
    }

    return std::move(newBlock);
}

void Block::print() const
{
    auto &&printElement{[](const std::pair<std::size_t, Block*> &pair)
        -> void
        {
            std::cout << '{'
                << pair.first;
            if(bool{pair.second})
            {
                std::cout << ',';
                pair.second->print();
            }
            std::cout << '}';
        }};

    std::cout << "{scopeId:"
        << scopeId
        << ",decls:"
        << decls
        << ",stats:{";
    
    if(!stats.empty())
    {
        for(std::size_t i{0ull};
            i + 1ull < stats.size();
            i++)
        {
            printElement(stats[i]);
            std::cout << ',';
        }

        printElement(stats.back());
    }
    
    std::cout << "}}"
        << std::flush;
}

bool Block::operateAdd(const Operation &op
    , Block *block
    , Block::Index &index)
{
    std::reference_wrapper<Index> idxRef{index};
    if(!selectBlockAndIndex(op
        , block
        , idxRef))
        return false;

    auto &&iter{idxRef.get().indices.begin()};
    for(;
        iter != idxRef.get().indices.end();
        iter++)
    {
        if(iter->first.second >= op.dst.back())
            break;
    }
    
    auto &&idOpt{Operation::getStatementId(op)};
    if(!idOpt)
        return notFoundStatementError(op);

    if(iter != idxRef.get().indices.end())
        block->stats.insert(block->stats.begin()
            + iter->first.second
            , std::make_pair(idOpt.value()
                , static_cast<Block*>(nullptr)));
    else
        block->stats.emplace_back(idOpt.value()
            , nullptr);

    for(;
        iter != idxRef.get().indices.end();
        iter++)
        iter->first.second++;
    
    return true;
}

bool Block::operateSub(const Operation &op
    , Block *block
    , Block::Index &index)
{
    std::reference_wrapper<Index> idxRef{index};
    if(!selectBlockAndIndex(op
        , block
        , idxRef))
        return false;

    auto &&iter{idxRef.get().find(op.dst.back())};
    if(iter == idxRef.get().indices.end())
        return notFoundStatementError(op);
    
    delete block->stats[iter->first.second].second;
    block->stats.erase(block->stats.begin() + iter->first.second);

    for(;
        iter != idxRef.get().indices.end();
        iter++)
        iter->first.second--;
    
    idxRef.get().indices.erase(iter);

    return true;
}

bool Block::operateRep(const Operation &op
    , Block *block
    , Block::Index &index)
{
    return operateSub(op
        , block
        , index)
        | operateAdd(op
            , block
            , index);
}

bool Block::selectBlockAndIndex(const Operation &op
    , Block *&block
    , std::reference_wrapper<Block::Index> &idxRef)
{
    if(op.dst.empty())
        return noHasDstError();

    for(std::size_t i{0ull};
        i + 1ull < op.dst.size();
        i++)
    {
        auto &&iter{idxRef.get().find(op.dst[i])};
        if(iter == idxRef.get().indices.end())
            return notFoundStatementError(op);
    
        block = block->stats[iter->first.second].second;
        idxRef = std::ref(iter->second.value());
    }

    return true;
}

bool Block::notFoundStatementError(const Operation &op)
{
    std::cerr << "GA::Block error:\n"
        "    what: failed to find statement to operate.\n"
        "    op: ";
    op.print();
    std::cout << std::endl;
    return false;
}

bool Block::noHasDstError()
{
    std::cerr << "GA::Block error:\n"
        "    what: Operation::dst shall have destination position.\n"
        << std::flush;
    return false;
}

TOKEN::CompoundStatement *Block::createCompoundStatement() const
{
    using namespace TOKEN;

    auto *cs{new CompoundStatement{new BlockItemList{decltype(BlockItemList::seq){}}}};

    for(auto &&id : decls)
    {
        auto &&ptr{std::get<std::shared_ptr<Declaration>>(Analyzer::statementMap().at(id))};
        cs->bil->seq.push_back(new BlockItem{ptr->copy()});
    }

    for(auto &&pair : stats)
        cs->bil->seq.push_back(new BlockItem{createStatement(pair)});

    return cs;
}

TOKEN::Statement *Block::createStatement(const std::pair<std::size_t, Block*> &pair) const
{
    using namespace TOKEN;
    using LS = LabeledStatement;
    using CS = CompoundStatement;
    using ES = ExpressionStatement;
    using SS = SelectionStatement;
    using IS = IterationStatement;
    using JS = JumpStatement;

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
                , pair.second->stats.front().second->createStatement()
                , pair.second->stats.back().second->createStatement()}});
        }
        else if(std::holds_alternative<SS::Si_e_s_s>(oldSs->var))
        {
            const auto &s{std::get<SS::Si_e_s_s>(oldSs->var)};
            newStatement->var.emplace<SS*>(new SS{SS::Si_e_s_s{s.e->copy()
                , pair.second->stats.front().second->createStatement()
                , pair.second->stats.back().second->createStatement()}});
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
            newStatement->var.emplace<IS*>(new IS{IS::Sf_e_e_e_s{s.e0->copy()
                , s.e1->copy()
                , s.e2->copy()
                , pair.second->createStatement()}});
        }
        else if(std::holds_alternative<IS::Sf_d_e_e_s>(oldIs->var))
        {
            const auto &s{std::get<IS::Sf_d_e_e_s>(oldIs->var)};
            newStatement->var.emplace<IS*>(new IS{IS::Sf_d_e_e_s{s.d->copy()
                , s.e0->copy()
                , s.e1->copy()
                , pair.second->createStatement()}});
        }
    }
    else if(std::holds_alternative<JS*>(oldPtr->var))
        newStatement->var.emplace<JS*>(std::get<JS*>(oldPtr->var)->copy());

    return newStatement;
}

TOKEN::Statement *Block::createStatement() const
{
    using namespace TOKEN;

    Statement *statement{nullptr};

    if(decls.empty() && stats.empty())
        statement = new Statement{new ExpressionStatement{}};
    else if(decls.empty() && stats.size() == 1)
        statement = createStatement(stats.front());
    else
        statement = new Statement{createCompoundStatement()};
    
    return statement;
}

decltype(Block::Index::indices)::iterator Block::Index::find(std::size_t idx)
{
    auto &&iter{indices.begin()};
    for(;
        iter != indices.end();
        iter++)
    {
        if(iter->first.first == idx)
            break;
    }

    return iter;
}

std::optional<Block::Index> Block::Index::createIndex(const Block *block)
{
    Index index;

    for(std::size_t i{0ull};
        i < block->stats.size();
        i++)
    {
        index.indices.emplace_back(std::make_pair(i, i)
            , block->stats[i].second
                ? createIndex(block->stats[i].second)
                : std::nullopt);
    }

    return {std::move(index)};
}

}