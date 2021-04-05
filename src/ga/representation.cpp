#include <iostream>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <functional>

#include "../random.hpp"
#include "../token.hpp"
#include "../configure.hpp"
#include "representation.hpp"

namespace GA
{

Representation &Representation::append(const Representation &rhs)
{
    if(block != rhs.block)
        throw std::runtime_error("lhs.block != rhs.block");
    
    ops.insert(ops.end()
        , rhs.ops.begin()
        , rhs.ops.end());
    
    return *this;
}

void Representation::print() const
{
    auto printContainer = [](const auto &container)
        {
            std::cout << '{';
            if(!container.empty())
            {
                auto iter = container.begin();
                std::cout << *iter;
                for(iter++; iter != container.end(); iter++)
                    std::cout << ',' << *iter;
            }
            std::cout << '}';
        };

    std::cout << "Rep:\n";
    for(auto &&op : ops)
    {
        std::cout << "    ";
        switch(op.tag)
        {
            case(OpTag::ADD):
                std::cout << "add : ";
                break;
            case(OpTag::SUB):
                std::cout << "sub : ";
                break;
            case(OpTag::SWAP):
                std::cout << "swap: ";
                break;
            default:;
        }
        printContainer(op.src);
        printContainer(op.dst);
        std::cout << '\n';
    }
    std::cout << std::flush;
}

Block *createBlock(const TOKEN::TranslationUnit *tu)
{
    std::vector<TOKEN::Declaration*> decls;
    std::vector<Block::Element> elems;

    for(auto &&ed : tu->seq)
    {
        if(std::holds_alternative<TOKEN::Declaration*>(ed->var))
            decls.push_back(std::get<TOKEN::Declaration*>(ed->var)->copy());
        else if(std::holds_alternative<TOKEN::FunctionDefinition*>(ed->var))
            elems.emplace_back(std::get<TOKEN::FunctionDefinition*>(ed->var)->copy(), createBlock(std::get<TOKEN::FunctionDefinition*>(ed->var)->cs));
    }

    return new Block(std::move(decls), std::move(elems));
}

Block *createBlock(const TOKEN::CompoundStatement *cs)
{
    std::vector<TOKEN::Declaration*> decls;
    std::vector<Block::Element> elems;

    if(cs->bil != nullptr)
    {
        for(auto &&bi : cs->bil->seq)
        {
            if(std::holds_alternative<TOKEN::Declaration*>(bi->var))
                decls.push_back(std::get<TOKEN::Declaration*>(bi->var)->copy());
            else if(std::holds_alternative<TOKEN::Statement*>(bi->var))
                elems.emplace_back(createElement(std::get<TOKEN::Statement*>(bi->var)));
        }
    }

    return new Block(std::move(decls), std::move(elems));
}

Block *createBlock(const TOKEN::LabeledStatement *ls)
{
    std::vector<Block::Element> elems;
    
    TOKEN::Statement *s = nullptr;
    if(std::holds_alternative<TOKEN::LabeledStatement::Si_s>(ls->var))
        s = std::get<TOKEN::LabeledStatement::Si_s>(ls->var).s;
    else if(std::holds_alternative<TOKEN::LabeledStatement::Sce_s>(ls->var))
        s = std::get<TOKEN::LabeledStatement::Sce_s>(ls->var).s;
    else if(std::holds_alternative<TOKEN::LabeledStatement::Ss>(ls->var))
        s = std::get<TOKEN::LabeledStatement::Ss>(ls->var).s;

    if(s != nullptr)
        elems.emplace_back(createElement(s));
    
    return new Block(std::vector<TOKEN::Declaration*>(), std::move(elems));
}

Block *createBlock(const TOKEN::SelectionStatement *ss)
{
    Block *block = new Block(std::vector<TOKEN::Declaration*>(), std::vector<Block::Element>());

    if(std::holds_alternative<TOKEN::SelectionStatement::Si_e_s>(ss->var))
    {
        auto &&s = std::get<TOKEN::SelectionStatement::Si_e_s>(ss->var);
        Block *b = nullptr;
        if(std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            b = createBlock(std::get<TOKEN::CompoundStatement*>(s.s->var));
        else
        {
            b = new Block(std::vector<TOKEN::Declaration*>(), std::vector<Block::Element>());
            b->elems.emplace_back(createElement(s.s));
        }
        block->elems.emplace_back(static_cast<TOKEN::Statement*>(nullptr), b);
        block->elems.emplace_back(static_cast<TOKEN::Statement*>(nullptr), new Block(std::vector<TOKEN::Declaration*>(), std::vector<Block::Element>()));
    }
    else if(std::holds_alternative<TOKEN::SelectionStatement::Si_e_s_s>(ss->var))
    {
        auto &&s = std::get<TOKEN::SelectionStatement::Si_e_s_s>(ss->var);
        Block *ifb = nullptr, *elseb = nullptr;
        if(std::holds_alternative<TOKEN::CompoundStatement*>(s.s0->var))
            ifb = createBlock(std::get<TOKEN::CompoundStatement*>(s.s0->var));
        else
        {
            ifb = new Block(std::vector<TOKEN::Declaration*>(), std::vector<Block::Element>());
            ifb->elems.emplace_back(createElement(std::get<TOKEN::SelectionStatement::Si_e_s_s>(ss->var).s0));
        }
        if(std::holds_alternative<TOKEN::CompoundStatement*>(s.s1->var))
            elseb = createBlock(std::get<TOKEN::CompoundStatement*>(s.s1->var));
        else
        {
            elseb = new Block(std::vector<TOKEN::Declaration*>(), std::vector<Block::Element>());
            elseb->elems.emplace_back(createElement(std::get<TOKEN::SelectionStatement::Si_e_s_s>(ss->var).s1));
        }
        block->elems.emplace_back(static_cast<TOKEN::Statement*>(nullptr), ifb);
        block->elems.emplace_back(static_cast<TOKEN::Statement*>(nullptr), elseb);
    }
    else if(std::holds_alternative<TOKEN::SelectionStatement::Ss_e_s>(ss->var))
    {
        auto &&s = std::get<TOKEN::SelectionStatement::Ss_e_s>(ss->var);
        if(std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
        {
            delete block;
            block = createBlock(std::get<TOKEN::CompoundStatement*>(s.s->var));
        }
        else
            block->elems.emplace_back(createElement(s.s));
    }

    return block;
}

Block *createBlock(const TOKEN::IterationStatement *is)
{
    Block *block = new Block(std::vector<TOKEN::Declaration*>(), std::vector<Block::Element>());

    if(std::holds_alternative<TOKEN::IterationStatement::Sw_e_s>(is->var))
    {
        auto &&s = std::get<TOKEN::IterationStatement::Sw_e_s>(is->var);
        if(std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
        {
            delete block;
            block = createBlock(std::get<TOKEN::CompoundStatement*>(s.s->var));
        }
        else
            block->elems.emplace_back(createElement(s.s));
    }
    else if(std::holds_alternative<TOKEN::IterationStatement::Sd_s_e>(is->var))
    {
        auto &&s = std::get<TOKEN::IterationStatement::Sd_s_e>(is->var);
        if(std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
        {
            delete block;
            block = createBlock(std::get<TOKEN::CompoundStatement*>(s.s->var));
        }
        else
            block->elems.emplace_back(createElement(s.s));

    }
    else if(std::holds_alternative<TOKEN::IterationStatement::Sf_e_e_e_s>(is->var))
    {
        auto &&s = std::get<TOKEN::IterationStatement::Sf_e_e_e_s>(is->var);
        if(std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
        {
            delete block;
            block = createBlock(std::get<TOKEN::CompoundStatement*>(s.s->var));
        }
        else
            block->elems.emplace_back(createElement(s.s));
    }
    else if(std::holds_alternative<TOKEN::IterationStatement::Sf_d_e_e_s>(is->var))
    {
        auto &&s = std::get<TOKEN::IterationStatement::Sf_d_e_e_s>(is->var);
        if(std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
        {
            delete block;
            block = createBlock(std::get<TOKEN::CompoundStatement*>(s.s->var));
        }
        else
            block->elems.emplace_back(createElement(s.s));
    }

    return block;
}

Block::Element createElement(const TOKEN::Statement *s)
{
    Block::Element ret = {s->copy(), nullptr};

    if(std::holds_alternative<TOKEN::LabeledStatement*>(s->var))
        ret.second = createBlock(std::get<TOKEN::LabeledStatement*>(s->var));
    else if(std::holds_alternative<TOKEN::CompoundStatement*>(s->var))
        ret.second = createBlock(std::get<TOKEN::CompoundStatement*>(s->var));
    else if(std::holds_alternative<TOKEN::ExpressionStatement*>(s->var))
        ;
    else if(std::holds_alternative<TOKEN::SelectionStatement*>(s->var))
        ret.second = createBlock(std::get<TOKEN::SelectionStatement*>(s->var));
    else if(std::holds_alternative<TOKEN::IterationStatement*>(s->var))
        ret.second = createBlock(std::get<TOKEN::IterationStatement*>(s->var));
    else if(std::holds_alternative<TOKEN::JumpStatement*>(s->var))
        ;
    
    return ret;
}

Block *createBlock(const Representation &rep)
{
    Block *ret = rep.block->copy();

    for(auto &&op : rep.ops)
    {
        switch(op.tag)
        {
            case(OpTag::ADD):
                manipulateAdd(rep.block
                    , ret
                    , op.src
                    , op.dst);
                break;
            case(OpTag::SUB):
                manipulateSub(ret
                    , op.dst);
                break;
            case(OpTag::SWAP):
                manipulateSwap(ret
                    , op.src
                    , op.dst);
                break;
            
            default:;
        }
    }

    return ret;
}

bool manipulateAdd(const Block *srcBlock
    , Block *dstBlock
    , const std::vector<std::size_t> &srcPos
    , const std::vector<std::size_t> &dstPos)
{
    Block::FunctionOrStatement fors{static_cast<TOKEN::FunctionDefinition*>(nullptr)};

    for(auto &&pos : srcPos)
    {
        if(srcBlock == nullptr
            || srcBlock->elems.size() <= pos)
        {
            std::cerr << "Representation warning:\n"
                "    what: selected statement is not exists.\n"
                << std::flush;
            return false;
        }

        fors = srcBlock->elems[pos].first;
        srcBlock = srcBlock->elems[pos].second;
    }

    for(std::size_t i = 0; i < dstPos.size(); i++)
    {
        std::size_t pos = dstPos[i];

        if(dstBlock == nullptr
            || dstBlock->elems.size() <= pos)
        {
            std::cerr << "Representation warning:\n"
                "    what: selected statement is not exists.\n"
                << std::flush;
            return false;
        }

        if(i + 1 == dstPos.size())
        {
            auto &&iter = std::next(dstBlock->elems.begin(), pos);
            dstBlock->elems.emplace(iter
                , std::visit([](auto &&p){return static_cast<Block::FunctionOrStatement>(p != nullptr ? p->copy() : nullptr);}
                    , fors)
                , dstBlock != nullptr ? dstBlock->copy() : nullptr);
        }
        else
            dstBlock = dstBlock->elems[pos].second;
    }

    return true;
}

bool manipulateSub(Block *dstBlock
    , const std::vector<std::size_t> &dstPos)
{
    for(std::size_t i = 0; i < dstPos.size(); i++)
    {
        auto &&pos = dstPos[i];

        if(dstBlock == nullptr
            || dstBlock->elems.size() <= pos)
        {
            std::cerr << "Representation warning:\n"
                "    what: selected statement is not exists.\n"
                << std::flush;
            return false;
        }

        if(i + 1 == dstPos.size())
        {
            auto &&iter = std::next(dstBlock->elems.begin(), pos);
            std::visit([](auto &&p){delete p;}, iter->first);
            delete iter->second;
            dstBlock->elems.erase(iter);
        }
        else
            dstBlock = dstBlock->elems[pos].second;
    }

    return true;
}

bool manipulateSwap(Block *dstBlock
    , const std::vector<std::size_t> &lhsPos
    , const std::vector<std::size_t> &rhsPos)
{
    Block::Element tmp{static_cast<TOKEN::FunctionDefinition*>(nullptr), nullptr};

    auto selectElement = [&tmp](Block *block
        , const std::vector<std::size_t> &pos)
            -> std::pair<Block::Element&, bool>
        {
            std::reference_wrapper<Block::Element> ret = std::ref(tmp);

            Block *currentBlock = block;
            for(auto &&p : pos)
            {
                if(currentBlock == nullptr
                    || currentBlock->elems.size() <= p)
                {
                    std::cerr << "Representation warning:\n"
                        "    what: selected statement is not exists.\n"
                        << std::flush;
                    return {tmp, false};
                }
                else if(currentBlock->elems.size() == p)
                    return {ret.get(), true};

                ret = std::ref(currentBlock->elems[p]);
                currentBlock = currentBlock->elems[p].second;
            }

            return {ret.get(), true};
        };

    auto &&[lhs, isFoundLhs] = selectElement(dstBlock, lhsPos);
    auto &&[rhs, isFoundRhs] = selectElement(dstBlock, rhsPos);

    if(isFoundLhs && isFoundRhs)
    {
        std::swap(lhs, rhs);
        return true;
    }
    else
        return false;
}

Block::~Block()
{
    for(auto &&d : decls)
        delete d;
    for(auto &&e : elems)
    {
        std::visit([](auto &&p){delete p;}, e.first);
        delete e.second;
    }
}

Block *Block::copy() const
{
    Block *ret = new Block(std::vector<TOKEN::Declaration*>()
        , std::vector<Element>());

    for(auto &&d : decls)
        ret->decls.push_back(d->copy());

    for(auto &&e : elems)
        ret->elems.emplace_back(std::visit([](auto &&p){return FunctionOrStatement(p != nullptr ? p->copy() : nullptr);}, e.first)
            , e.second != nullptr ? e.second->copy() : nullptr);
    
    return ret;
}

Representation createRandomRep(const Block *block
    , std::size_t num)
{
    static auto selectStat = [&](std::vector<std::size_t> &q, const Block *b)
    {
        while(b != nullptr)
        {
            if(b->elems.empty())
                break;
            else
            {
                std::size_t idx = RAND.random<std::size_t>(b->elems.size());
                if(idx != b->elems.size())
                {
                    q.push_back(idx);
                    b = b->elems[idx].second;
                }
                else
                    break;
            }
        }
    };

    Representation rep;
    rep.block = block;

    for(std::size_t i = 0; i < num; i++)
    {   
        Operation op;
        op.tag = selectOpTag();

        switch(op.tag)
        {
            case(OpTag::ADD):
            case(OpTag::SWAP):
                selectStat(op.src, block);
                selectStat(op.dst, block);
                break;
            case(OpTag::SUB):
                selectStat(op.dst, block);
                break;
            
            default:;
        }
        
        rep.ops.push_back(std::move(op));
    }

    return rep;
}

OpTag selectOpTag(OpTag def)
{
    OpTag ret = def;
    double prob = RAND.floating();
    double sum = 0.0;

    if((sum += Configure::ADDING_PROBABILITY) >= prob)
        ret = OpTag::ADD;
    else if((sum += Configure::SUBTRACTING_PROBABILITY) >= prob)
        ret = OpTag::SUB;
    else if((sum += Configure::SWAPPING_PROBABILITY) >= prob)
        ret = OpTag::SWAP;
    
    return ret;
}

TOKEN::TranslationUnit *createTranslationUnit(const Block *block)
{
    std::vector<TOKEN::ExternalDeclaration*> edvec;

    for(auto &&d : block->decls)
        edvec.push_back(new TOKEN::ExternalDeclaration(d->copy()));
    
    for(auto &&e : block->elems)
    {
        if(std::holds_alternative<TOKEN::FunctionDefinition*>(e.first))
        {
            TOKEN::FunctionDefinition *oldFd = std::get<TOKEN::FunctionDefinition*>(e.first);
            TOKEN::FunctionDefinition *newFd = new TOKEN::FunctionDefinition();
            newFd->ds = oldFd->ds->copy();
            newFd->d = oldFd->d->copy();
            newFd->dl = oldFd->dl != nullptr ? oldFd->dl->copy() : nullptr;
            newFd->cs = createCompoundStatement(e.second);

            edvec.push_back(new TOKEN::ExternalDeclaration(newFd));
        }
        else
        {
            std::cerr << "Representation warning:\n"
                "    what: block of Translation-Unit should not include statement."
                "ignored this statement.\n"
                << std::flush;
        }
    }

    return new TOKEN::TranslationUnit(std::move(edvec));
}

TOKEN::CompoundStatement *createCompoundStatement(const Block *block)
{
    std::vector<TOKEN::BlockItem*> biseq;

    for(auto &&d : block->decls)
        biseq.push_back(new TOKEN::BlockItem(d->copy()));
    
    for(auto &&e : block->elems)
    {
        if(std::holds_alternative<TOKEN::Statement*>(e.first))
        {
            TOKEN::Statement *oldS = std::get<TOKEN::Statement*>(e.first);
            if(oldS != nullptr)
                biseq.push_back(new TOKEN::BlockItem(createStatement(e)));
        }
        else
        {
            std::cerr << "Representation warning:\n"
                "    what: block of Translation-Unit should not include statement."
                "ignored this statement.\n"
                << std::flush;
        }
    }

    return new TOKEN::CompoundStatement(new TOKEN::BlockItemList(std::move(biseq)));
}

TOKEN::Statement *createStatement(const Block::Element &element)
{
    TOKEN::Statement *oldS = std::get<TOKEN::Statement*>(element.first);
    TOKEN::Statement *newS = new TOKEN::Statement(std::monostate());

    if(std::holds_alternative<TOKEN::LabeledStatement*>(oldS->var))
    {
        TOKEN::LabeledStatement *oldLs = std::get<TOKEN::LabeledStatement*>(oldS->var);
        if(std::holds_alternative<TOKEN::LabeledStatement::Si_s>(oldLs->var))
        {
            auto &&s = std::get<TOKEN::LabeledStatement::Si_s>(oldLs->var);
            TOKEN::LabeledStatement::Si_s tmp;
            tmp.i = s.i->copy();
            tmp.s = createStatement(element.second);
            newS->var.emplace<TOKEN::LabeledStatement*>(new TOKEN::LabeledStatement(tmp));
        }
        else if(std::holds_alternative<TOKEN::LabeledStatement::Sce_s>(oldLs->var))
        {
            auto &&s = std::get<TOKEN::LabeledStatement::Sce_s>(oldLs->var);
            TOKEN::LabeledStatement::Sce_s tmp;
            tmp.ce = s.ce->copy();
            tmp.s = createStatement(element.second);
            newS->var.emplace<TOKEN::LabeledStatement*>(new TOKEN::LabeledStatement(tmp));
        }
        else if(std::holds_alternative<TOKEN::LabeledStatement::Ss>(oldLs->var))
        {
            auto &&s = std::get<TOKEN::LabeledStatement::Ss>(oldLs->var);
            TOKEN::LabeledStatement::Ss tmp;
            tmp.s = createStatement(element.second);
            newS->var.emplace<TOKEN::LabeledStatement*>(new TOKEN::LabeledStatement(tmp));
        }
    }
    else if(std::holds_alternative<TOKEN::CompoundStatement*>(oldS->var))
        newS->var.emplace<TOKEN::CompoundStatement*>(createCompoundStatement(element.second));
    else if(std::holds_alternative<TOKEN::ExpressionStatement*>(oldS->var))
        newS->var.emplace<TOKEN::ExpressionStatement*>(std::get<TOKEN::ExpressionStatement*>(oldS->var)->copy());
    else if(std::holds_alternative<TOKEN::SelectionStatement*>(oldS->var))
    {
        TOKEN::SelectionStatement *oldSs = std::get<TOKEN::SelectionStatement*>(oldS->var);
        if(std::holds_alternative<TOKEN::SelectionStatement::Si_e_s>(oldSs->var))
        {
            auto &&s = std::get<TOKEN::SelectionStatement::Si_e_s>(oldSs->var);
            TOKEN::SelectionStatement::Si_e_s_s tmp;
            tmp.e = s.e->copy();
            tmp.s0
                = element.second->elems.size() >= 1
                    ? new TOKEN::Statement(createCompoundStatement(element.second->elems[0].second))
                    : new TOKEN::Statement(new TOKEN::CompoundStatement());
            tmp.s1
                = element.second->elems.size() >= 2
                    ? new TOKEN::Statement(createCompoundStatement(element.second->elems[1].second))
                    : new TOKEN::Statement(new TOKEN::CompoundStatement());
            newS->var.emplace<TOKEN::SelectionStatement*>(new TOKEN::SelectionStatement(tmp));
        }
        else if(std::holds_alternative<TOKEN::SelectionStatement::Si_e_s_s>(oldSs->var))
        {
            auto &&s = std::get<TOKEN::SelectionStatement::Si_e_s_s>(oldSs->var);
            TOKEN::SelectionStatement::Si_e_s_s tmp;
            tmp.e = s.e->copy();
            tmp.s0
                = element.second->elems.size() >= 1
                    ? new TOKEN::Statement(createCompoundStatement(element.second->elems[0].second))
                    : new TOKEN::Statement(new TOKEN::CompoundStatement());
            tmp.s1
                = element.second->elems.size() >= 2
                    ? new TOKEN::Statement(createCompoundStatement(element.second->elems[1].second))
                    : new TOKEN::Statement(new TOKEN::CompoundStatement());
            newS->var.emplace<TOKEN::SelectionStatement*>(new TOKEN::SelectionStatement(tmp));
        }
        else if(std::holds_alternative<TOKEN::SelectionStatement::Ss_e_s>(oldSs->var))
        {
            auto &&s = std::get<TOKEN::SelectionStatement::Ss_e_s>(oldSs->var);
            TOKEN::SelectionStatement::Ss_e_s tmp;
            tmp.e = s.e->copy();
            tmp.s = new TOKEN::Statement(createCompoundStatement(element.second));
            newS->var.emplace<TOKEN::SelectionStatement*>(new TOKEN::SelectionStatement(tmp));
        }
    }
    else if(std::holds_alternative<TOKEN::IterationStatement*>(oldS->var))
    {
        auto &&oldIs = std::get<TOKEN::IterationStatement*>(oldS->var);
        if(std::holds_alternative<TOKEN::IterationStatement::Sw_e_s>(oldIs->var))
        {
            auto &&s = std::get<TOKEN::IterationStatement::Sw_e_s>(oldIs->var);
            TOKEN::IterationStatement::Sw_e_s tmp;
            tmp.e = s.e->copy();
            tmp.s = new TOKEN::Statement(createCompoundStatement(element.second));
            newS->var.emplace<TOKEN::IterationStatement*>(new TOKEN::IterationStatement(tmp));
        }
        else if(std::holds_alternative<TOKEN::IterationStatement::Sd_s_e>(oldIs->var))
        {
            auto &&s = std::get<TOKEN::IterationStatement::Sd_s_e>(oldIs->var);
            TOKEN::IterationStatement::Sd_s_e tmp;
            tmp.e = s.e->copy();
            tmp.s = new TOKEN::Statement(createCompoundStatement(element.second));
            newS->var.emplace<TOKEN::IterationStatement*>(new TOKEN::IterationStatement(tmp));
        }
        else if(std::holds_alternative<TOKEN::IterationStatement::Sf_e_e_e_s>(oldIs->var))
        {
            auto &&s = std::get<TOKEN::IterationStatement::Sf_e_e_e_s>(oldIs->var);
            TOKEN::IterationStatement::Sf_e_e_e_s tmp;
            tmp.e0 = s.e0 != nullptr ? s.e0->copy() : nullptr;
            tmp.e1 = s.e1 != nullptr ? s.e1->copy() : nullptr;
            tmp.e2 = s.e2 != nullptr ? s.e2->copy() : nullptr;
            tmp.s = new TOKEN::Statement(createCompoundStatement(element.second));
            newS->var.emplace<TOKEN::IterationStatement*>(new TOKEN::IterationStatement(tmp));
        }
        else if(std::holds_alternative<TOKEN::IterationStatement::Sf_d_e_e_s>(oldIs->var))
        {
            auto &&s = std::get<TOKEN::IterationStatement::Sf_d_e_e_s>(oldIs->var);
            TOKEN::IterationStatement::Sf_d_e_e_s tmp;
            tmp.d = s.d->copy();
            tmp.e0 = s.e0 != nullptr ? s.e0->copy() : nullptr;
            tmp.e1 = s.e1 != nullptr ? s.e1->copy() : nullptr;
            tmp.s = new TOKEN::Statement(createCompoundStatement(element.second));
            newS->var.emplace<TOKEN::IterationStatement*>(new TOKEN::IterationStatement(tmp));
        }
    }
    else if(std::holds_alternative<TOKEN::JumpStatement*>(oldS->var))
    {
        auto &&oldJs = std::get<TOKEN::JumpStatement*>(oldS->var);
        if(std::holds_alternative<TOKEN::JumpStatement::Sg_i>(oldJs->var))
        {
            delete newS;
            newS = oldS->copy();
        }
        else if(std::holds_alternative<TOKEN::JumpStatement::Sc>(oldJs->var))
        {
            delete newS;
            newS = oldS->copy();
        }
        else if(std::holds_alternative<TOKEN::JumpStatement::Sb>(oldJs->var))
        {
            delete newS;
            newS = oldS->copy();
        }
        else if(std::holds_alternative<TOKEN::JumpStatement::Sr_e>(oldJs->var))
        {
            delete newS;
            newS = oldS->copy();
        }
    }

    return newS;
}

TOKEN::Statement *createStatement(const Block *block)
{
    TOKEN::Statement *newS = nullptr;

    if(block->elems.empty())
        newS = new TOKEN::Statement(new TOKEN::ExpressionStatement());
    else if(block->elems.size() == 1)
        newS = createStatement(block->elems.front());
    else
    {
        newS = createStatement(block->elems.front());
        std::cerr << "Representation warning:\n"
            "    what: labeled-statement should not have element more than one.\n"
            << std::flush;
    }

    return newS;
}

}