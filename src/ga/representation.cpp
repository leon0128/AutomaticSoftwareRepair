#include <iostream>
#include <limits>
#include <algorithm>

#include "../identifier.hpp"
#include "../token.hpp"
#include "../random.hpp"
#include "../configure.hpp"
#include "../analyzer.hpp"
#include "selector.hpp"
#include "block.hpp"
#include "representation.hpp"

namespace GA
{

void Operation::print() const
{
    auto &&printVec{[](const std::vector<std::size_t> &vec)
        -> void
        {
            std::cout << "{";
            if(!vec.empty())
            {
                for(std::size_t i{0ull};
                    i + 1 < vec.size();
                    i++)
                    std::cout << vec[i]
                        << ",";
                
                std::cout << vec.back();
            }

            std::cout << "}";
        }};

    std::cout << "{tag:";
    switch(tag)
    {
        case(Operation::Tag::ADD):
            std::cout << "ADD,"
                "src:";
            printVec(src);
            std::cout << ",dst:";
            printVec(dst);
            std::cout << ",ids:";
            printVec(ids);
            break;
        case(Operation::Tag::SUB):
            std::cout << "SUB,"
                "dst:";
            printVec(dst);
            break;
        case(Operation::Tag::REP):
            std::cout << "REP,"
                "src:";
            printVec(src);
            std::cout << ",dst:";
            printVec(dst);
            std::cout << ",ids:";
            printVec(ids);
            break;
    }
    std::cout << "}"
        << std::flush;
}

bool Operation::initialize(const TOKEN::TranslationUnit *tu)
{
    using namespace TOKEN;

    std::vector<std::string> functionNames;
    for(const auto *ed : tu->seq)
    {
        if(std::holds_alternative<FunctionDefinition*>(ed->var))
        {
            const auto *fd{std::get<FunctionDefinition*>(ed->var)};
            functionNames.push_back(Analyzer::idMap().at(getFunctionName(fd->d))->str());
        }
    }

    for(const auto &target : Configure::TARGET_FUNCTION_NAMES)
    {
        std::size_t i{0ull};
        for(;
            i < functionNames.size();
            i++)
        {
            if(functionNames[i] == target)
                break;
        }

        if(i != functionNames.size())
            SELECTABLE_FUNCTION_IDS.push_back(i);
        else
            return notFoundTargetFunction(target);
    }

    return true;
}

std::optional<Operation> Operation::createRandomOp(const Block *srcBlock
    , const std::vector<const Block*> &blockPool)
{
    double prob{RAND.floating()};
    double sum{0.0};

    Operation op;

    if((sum += Configure::ADDING_PROBABILITY) >= prob)
        op.tag = Tag::ADD;
    else if((sum += Configure::SUBTRACTING_PROBABILITY) >= prob)
        op.tag = Tag::SUB;
    else if((sum += Configure::SWAPPING_PROBABILITY) >= prob)
        op.tag = Tag::REP;
    else
    {
        tagError();
        return {std::nullopt};
    }

    bool isSuccessfull{false};
    std::size_t failureCount{0ull};

    do
    {
        op.src.clear();
        op.dst.clear();
        op.ids.clear();

        switch(op.tag)
        {
            case(Tag::ADD):
            {
                if(!selectAddSrcPos(blockPool
                    , op.src)
                    || !selectAddDstPos(srcBlock
                        , op.dst)
                    || !selectAlternativeIds(blockPool
                        , srcBlock
                        , op))
                    break;
                
                isSuccessfull = true;
                break;
            }
            case(Tag::SUB):
            {
                if(!selectSubDstPos(srcBlock
                    , op.dst))
                    break;

                isSuccessfull = true;
                break;
            }
            case(Tag::REP):
            {
                if(!selectRepSrcPos(blockPool
                    , op.src)
                    || !selectRepDstPos(srcBlock
                        , op.dst)
                    || !selectAlternativeIds(blockPool
                        , srcBlock
                        , op))
                    break;
                
                isSuccessfull = true;
                break;
            }
        }

        failureCount++;
    }
    while(!isSuccessfull
        && failureCount < Configure::FAILURE_LIMIT);
    
    if(!isSuccessfull)
    {
        notCreatedOperationError();
        return {std::nullopt};
    }
    
    return {std::move(op)};
}

bool Operation::selectSubDstPos(const Block *block
    , std::vector<std::size_t> &pos)
{
    if(auto &&idOpt{selectFunctionPos(block)};
        bool(idOpt))
        pos.push_back(idOpt.value());
    else
        return false;

    bool isIfStatement{false};
    while(block = block->stats[pos.back()].second)
    {   
        if(!block->stats.empty()
            && block->stats.front().first == std::numeric_limits<std::size_t>::max())
        {
            isIfStatement = true;
            std::size_t idx{RAND.random(block->stats.size()) + 1ull};
            if(idx >= block->stats.size())
                break;
            else
                pos.push_back(idx);
        }
        else
        {
            if(!isIfStatement && pos.size() != 1ull)
            {
                std::size_t idx{RAND.random(block->stats.size()) + 1ull};
                if(idx >= block->stats.size())
                    break;
                else
                    pos.push_back(idx);
            }
            else
            {
                if(block->stats.empty())
                    return noHasStatement("selectSubDstPos()");
                
                pos.push_back(RAND.random(block->stats.size()));
            }

            isIfStatement = false;
        }
    }

    return true;
}

bool Operation::selectAddDstPos(const Block *block
    , std::vector<std::size_t> &pos)
{
    if(auto &&idOpt{selectFunctionPos(block)};
        bool(idOpt))
        pos.push_back(idOpt.value());
    else
        return false;

    bool isIfStatement{false};
    while(block = block->stats[pos.back()].second)
    {
        if(!block->stats.empty()
            && block->stats.front().first == std::numeric_limits<std::size_t>::max())
        {
            isIfStatement = true;
            std::size_t idx{RAND.random(block->stats.size() + 1ull)};
            if(idx >= block->stats.size())
                break;
            else
                pos.push_back(idx);
        }
        else
        {
            std::size_t idx{0ull};
            if(isIfStatement || pos.size() == 1ull)
                idx = RAND.random(block->stats.size() + 1ull);
            else
                idx = RAND.random(block->stats.size() + 2ull);

            if(idx <= block->stats.size())
                pos.push_back(idx);
            
            if(idx >= block->stats.size())
                break;

            isIfStatement = false;
        }
    }

    return true;
}

bool Operation::selectAddSrcPos(const std::vector<const Block*> &pool
    , std::vector<std::size_t> &pos)
{
    pos.push_back(RAND.random(pool.size()));

    const Block *block{pool[pos.back()]};
    
    if(block->stats.empty())
        return noHasFunctionError();
    
    pos.push_back(RAND.random(block->stats.size()));
    block = block->stats[pos.back()].second;
    if(block->stats.empty())
        return noHasStatement("selectAddSrcPos()");
    pos.push_back(RAND.random(block->stats.size()));

    bool isIfStatement{false};
    while(block = block->stats[pos.back()].second)
    {
        if(!isIfStatement)
        {
            if(!block->stats.empty()
                && block->stats.front().first == std::numeric_limits<std::size_t>::max())
                isIfStatement = true;

            std::size_t idx{RAND.random(block->stats.size() + 1ull)};
            if(idx >= block->stats.size())
                break;
            else
                pos.push_back(idx);
        }
        else
        {
            isIfStatement = false;

            if(block->stats.empty())
            {
                pos.pop_back();
                break;
            }
            else
                pos.push_back(RAND.random(block->stats.size()));
        }
    }

    return true;
}

bool Operation::selectRepDstPos(const Block *block
    , std::vector<std::size_t> &pos)
{
    if(auto &&idOpt{selectFunctionPos(block)};
        bool(idOpt))
        pos.push_back(idOpt.value());
    else
        return false;

    block = block->stats[pos.back()].second;
    if(block->stats.empty())
        return noHasStatement("selectRepDstPos");
    pos.push_back(RAND.random(block->stats.size()));

    bool isIfStatement{false};
    while(block = block->stats[pos.back()].second)
    {
        if(!block->stats.empty()
            && block->stats.front().first == std::numeric_limits<std::size_t>::max())
        {
            isIfStatement = true;

            std::size_t idx{RAND.random(block->stats.size() + 1ull)};
            if(idx >= block->stats.size())
                break;
            else
                pos.push_back(idx);
        }
        else
        {
            if(isIfStatement
                && block->stats.empty())
            {
                pos.pop_back();
                break;
            }
            else
            {
                std::size_t idx{RAND.random(block->stats.size()
                    + (isIfStatement
                        ? 0ull
                        : 1ull))};
                if(idx >= block->stats.size())
                    break;
                else
                    pos.push_back(idx);
                
                isIfStatement = true;
            }
        }
    }

    return true;
}

bool Operation::selectRepSrcPos(const std::vector<const Block*> &pool
    , std::vector<std::size_t> &pos)
{
    pos.push_back(RAND.random(pool.size()));

    const Block *block{pool[pos.back()]};
    
    if(block->stats.empty())
        return noHasFunctionError();
    
    pos.push_back(RAND.random(block->stats.size()));
    block = block->stats[pos.back()].second;
    if(block->stats.empty())
        return noHasStatement("selectRepSrcPos()");
    pos.push_back(RAND.random(block->stats.size()));

    bool isIfStatement{false};
    while(block = block->stats[pos.back()].second)
    {
        if(!isIfStatement)
        {
            if(!block->stats.empty()
                && block->stats.front().first == std::numeric_limits<std::size_t>::max())
                isIfStatement = true;

            std::size_t idx{RAND.random(block->stats.size() + 1ull)};
            if(idx >= block->stats.size())
                break;
            else
                pos.push_back(idx);
        }
        else
        {
            isIfStatement = false;

            if(block->stats.empty())
            {
                pos.pop_back();
                break;
            }
            else
                pos.push_back(RAND.random(block->stats.size()));
        }
    }

    return true;
}

std::optional<std::size_t> Operation::getScopeId(const Block *block
    , const std::vector<std::size_t> &pos)
{
    if(pos.empty())
    {
        positionError("position is empty.");
        return {std::nullopt};
    }

    for(std::size_t i{0ull};
        i + 1ull < pos.size();
        i++)
    {
        if(block->stats.size() <= pos[i]
            || !block->stats[pos[i]].second)
        {
            positionError("out of range or sub-block no exists.");
            return {std::nullopt};
        }

        block = block->stats[pos[i]].second;
    }

    return {block->scopeId};
}

bool Operation::selectAlternativeIds(const std::vector<const Block*> &pool
    , const Block *block
    , Operation &op)
{
    auto &&scopeId{getScopeId(block, op.dst)};
    if(!scopeId)
        return false;
    auto &&statementId{getSrcStatementId(pool, op.src)};
    if(!statementId)
        return false;
    
    auto &&statement{getStatement(statementId.value())};
    if(!statement)
        return false;

    Selector selector;
    if(!selector.execute(scopeId.value()
        , statement.get()
        , op.ids))
        return false;
    
    for(const auto &outerPair : NEW_STATEMENT_IDS)
    {
        if(outerPair.first == std::make_pair(op.src, op.ids))
            return true;
    }

    std::shared_ptr<TOKEN::Statement> newStatement{statement->copy()};
    if(!selector.execute(op.ids
        , newStatement.get()))
        return false;

    auto &&id{Analyzer::addStatement(std::move(newStatement))};
    NEW_STATEMENT_IDS.emplace_back(std::make_pair(op.src
        , op.ids)
        , id);
    CREATED_STATEMENT_IDS.emplace(id);

    return true;
}

std::optional<std::size_t> Operation::selectFunctionPos(const Block *block)
{
    if(block->stats.empty())
    {
        noHasFunctionError();
        return {std::nullopt};
    }

    if(SELECTABLE_FUNCTION_IDS.empty())
        return {RAND.random(block->stats.size())};
    else
        return {SELECTABLE_FUNCTION_IDS[RAND.random(SELECTABLE_FUNCTION_IDS.size())]};
}

std::optional<std::size_t> Operation::getSrcStatementId(const std::vector<const Block*> &pool
    , const std::vector<std::size_t> &pos)
{
    if(pos.empty())
    {
        positionError("no has source position.");
        return {std::nullopt};
    }

    const Block *block{pool[pos.front()]};

    for(std::size_t i{1ull};
        i + 1ull < pos.size();
        i++)
        block = block->stats.at(pos[i]).second;
    
    return {block->stats.at(pos.back()).first};
}

std::optional<std::size_t> Operation::getStatementId(const Operation &op)
{
    for(const auto &outerPair : NEW_STATEMENT_IDS)
    {
        if(outerPair.first == std::make_pair(op.src, op.ids))
            return outerPair.second;
    }

    notFoundStatementError("Operation::getStatementId()");
    return {std::nullopt};
}

bool Operation::isCreatedStatement(std::size_t id)
{
    return CREATED_STATEMENT_IDS.find(id) != CREATED_STATEMENT_IDS.end();
}

std::shared_ptr<TOKEN::Statement> Operation::getStatement(std::size_t id)
{
    auto &&iter{Analyzer::statementMap().find(id)};
    if(iter == Analyzer::statementMap().end())
    {
        notFoundStatementError(id);
        return {nullptr};
    }

    if(!std::holds_alternative<std::shared_ptr<TOKEN::Statement>>(iter->second))
    {
        variantError("variant shall have statement.");
        return {nullptr};
    }

    return std::get<std::shared_ptr<TOKEN::Statement>>(iter->second);
}

std::size_t Operation::getFunctionName(const TOKEN::Declarator *declarator)
{
    using namespace TOKEN;
    using DD = DirectDeclarator;

    if(std::holds_alternative<DD::Si>(declarator->dd->seq.front()))
        return std::get<Identifier::Id>(std::get<DD::Si>(declarator->dd->seq.front()).i->var).first;
    else
        return getFunctionName(std::get<DD::Sd>(declarator->dd->seq.front()).d);
}

bool Operation::tagError()
{
    std::cerr << "GA::Operation error:\n"
        "    what: Tag is not selected.\n"
        << std::flush;
    return false;
}

bool Operation::noHasFunctionError()
{
    std::cerr << "GA::Operation error:\n"
        "    what: Block has no function.\n"
        << std::flush;
    return false;
}

bool Operation::noHasStatement(const std::string &func)
{
    std::cerr << "GA::Operation error:\n"
        "    what: Block has no statement.\n"
        "    caller: " << func
        << std::endl;
    return false;
}

bool Operation::positionError(const std::string &message)
{
    std::cerr << "GA::Operation error:\n"
        "    what: position is invalid.\n"
        "    desc: " << message
        << std::endl;
    return false; 
}

bool Operation::variantError(const std::string &message)
{
    std::cerr << "GA::Operation error:\n"
        "    what: variant error.\n"
        "    desc: " << message
        << std::endl;
    return false;
}

bool Operation::notFoundStatementError(const std::size_t id)
{
    std::cerr << "GA::Operation error:\n"
        "    what: specified statement is not found.\n"
        "    statement id: " << id
        << std::endl;
    return false;
}

bool Operation::notFoundStatementError(const std::string &message)
{
    std::cerr << "GA::Operation error:\n"
        "    what: specified statement for operation is not found.\n"
        "    desc: " << message
        << std::endl;
    return false;
}

bool Operation::notCreatedOperationError()
{
    std::cerr << "GA::Operation error:\n"
        "    what: failed to create operation.\n"
        << std::flush;
    return false;
}

bool Operation::notFoundTargetFunction(const std::string &name)
{
    std::cerr << "GA::Operation error:\n"
        "    what: failed to find target function name.\n"
        "    function name: " << name
        << std::endl;
    return false;
}

bool Representation::merge(const Block *src
    , const Representation &other)
{
    ops.insert(ops.end()
        , other.ops.begin()
        , other.ops.end());

    if(!Block::deleteInvalidOp(src
        , *this))
        return false;

    return true;
}

void Representation::print() const
{
    std::cout << "Rep:{";
    if(!ops.empty())
    {
        for(std::size_t i{0ull};
            i + 1 < ops.size();
            i++)
        {
            ops[i].print();
            std::cout << ",";
        }
        ops.back().print();
    }
    std::cout << "}\n"
        << std::flush;
}

std::optional<Representation> Representation::createRandomRep(const Block *srcBlock
    , const std::vector<const Block*> &blockPool)
{
    Representation rep;

    if(auto &&opt{Operation::createRandomOp(srcBlock
        , blockPool)};
        bool(opt))
        rep.ops.push_back(std::move(opt.value()));
    else
        return {std::nullopt};

    return {std::move(rep)};
}

}