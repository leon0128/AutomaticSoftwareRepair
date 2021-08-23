#include <iostream>
#include <algorithm>
#include <numeric>

#include "../utility/random.hpp"
#include "../configure.hpp"
#include "../analyzer.hpp"
#include "register.hpp"
#include "selector.hpp"
#include "block.hpp"
#include "operation.hpp"

namespace GA::OPERATION
{

std::vector<
    std::pair<
        std::size_t
            , std::vector<
                std::size_t>>> Operation::SELECTABLE_SOURCE_POOL_AND_FUNCTION_INDICES{};

std::vector<std::size_t> Operation::SELECTABLE_DESTINATION_INDICES{};

Tag selectTag()
{
    double random{RANDOM::RAND.floating()};
    double sum{0.0};

    Tag tag{Tag::NONE};

    if((sum += Configure::ADDING_PROBABILITY) >= random)
        tag = Tag::ADD;
    else if((sum += Configure::SUBTRACTING_PROBABILITY) >= random)
        tag = Tag::DEL;
    else if((sum += Configure::SWAPPING_PROBABILITY) >= random)
        tag = Tag::REP;
    
    return tag;
}

bool Operation::initialize(const Pool &pool
    , const BLOCK::Block *block)
{
    using namespace TOKEN;
    using DD = DirectDeclarator;

    auto &&getFunctionName{[](const Declarator *declarator)
        -> std::string
    {
        while(1)
        {
            if(std::holds_alternative<DD::Si>(declarator->dd->seq.front()))
                return TOKEN::str(std::get<DD::Si>(declarator->dd->seq.front()).i);
            else if(std::holds_alternative<DD::Sd>(declarator->dd->seq.front()))
                declarator = std::get<DD::Sd>(declarator->dd->seq.front()).d;
            else
                return std::string{};
        }
    }};

    for(std::size_t i{0ull};
        i < block->stats().size();
        i++)
    {
        const auto &fd{std::get<std::shared_ptr<FunctionDefinition>>(Analyzer::statementMap().at(block->stats().at(i).first))};
        if(std::find(Configure::TARGET_FUNCTION_NAMES.begin()
            , Configure::TARGET_FUNCTION_NAMES.end()
            , getFunctionName(fd->d))
            != Configure::TARGET_FUNCTION_NAMES.end())
            SELECTABLE_DESTINATION_INDICES.push_back(i);
    }
    if(SELECTABLE_DESTINATION_INDICES.empty())
    {
        SELECTABLE_DESTINATION_INDICES.resize(block->stats().size());
        std::iota(SELECTABLE_DESTINATION_INDICES.begin()
            , SELECTABLE_DESTINATION_INDICES.end()
            , 0ull);
    }

    for(std::size_t i{0ull};
        i < pool.size();
        i++)
    {
        SELECTABLE_SOURCE_POOL_AND_FUNCTION_INDICES.emplace_back(i, std::vector<std::size_t>{});
        for(std::size_t j{0ull};
            j < pool[i]->stats().size();
            j++)
        {
            if(!pool[i]->stats()[j].second->stats().empty())
                SELECTABLE_SOURCE_POOL_AND_FUNCTION_INDICES.back().second.push_back(j);
        }
        if(SELECTABLE_SOURCE_POOL_AND_FUNCTION_INDICES.back().second.empty())
            SELECTABLE_SOURCE_POOL_AND_FUNCTION_INDICES.pop_back();
    }

    return true;
}

Operation::Operation()
    : mTag{Tag::NONE}
    , mSrc{}
    , mDst{}
    , mIds{}
    , mStatId{std::numeric_limits<std::size_t>::max()}
{
}

Operation::Operation(const Pool &pool
    , const BLOCK::Block *srcBlock)
    : Operation{pool
        , srcBlock
        , selectTag()}
{
}

Operation::Operation(const Pool &pool
    , const BLOCK::Block *srcBlock
    , Tag tag)
    : mTag{tag}
    , mSrc{}
    , mDst{}
    , mIds{}
    , mStatId{std::numeric_limits<std::size_t>::max()}
{
    switch(tag)
    {
        case(Tag::ADD):
            if(!selectAdditionalPosition(pool
                , srcBlock))
                mTag = Tag::NONE;
            break;
        case(Tag::DEL):
            if(!selectSubtractionalPosition(srcBlock))
                mTag = Tag::NONE;
            break;
        case(Tag::REP):
            if(!selectReplacingPosition(pool
                , srcBlock))
                mTag = Tag::NONE;
            break;

        default:;
    }

    if(tag == Tag::NONE)
        clear();
}

bool Operation::selectAdditionalPosition(const Pool &pool
    , const BLOCK::Block *srcBlock)
{
    if(!selectSourcePoolAndFunction()
        || !selectSourceStatement(pool)
        || !selectDestinationFunction()
        || !selectDestinationStatement(srcBlock
            , true)
        || !selectAlternativeIdentifier(pool
            , srcBlock))
    {
        clear();
        return false;
    }

    return true;
}

bool Operation::selectSubtractionalPosition(const BLOCK::Block *srcBlock)
{
    if(!selectDestinationFunction()
        || !selectDestinationStatement(srcBlock
            , false))
    {
        clear();
        return false;
    }
    
    return true;
}

bool Operation::selectReplacingPosition(const Pool &pool
    , const BLOCK::Block *srcBlock)
{
    if(!selectSourcePoolAndFunction()
        || !selectSourceStatement(pool)
        || !selectDestinationFunction()
        || !selectDestinationStatement(srcBlock
            , false)
        || !selectAlternativeIdentifier(pool
            , srcBlock))
    {
        clear();
        return false;
    }
    
    return true;
}

bool Operation::selectSourcePoolAndFunction()
{
    if(SELECTABLE_SOURCE_POOL_AND_FUNCTION_INDICES.empty())
        return candidateError("selectSourcePoolAndFunction()");

    const auto &pair{SELECTABLE_SOURCE_POOL_AND_FUNCTION_INDICES[RANDOM::RAND(SELECTABLE_SOURCE_POOL_AND_FUNCTION_INDICES.size())]};
    
    mSrc.push_back(pair.first);
    mSrc.push_back(pair.second[RANDOM::RAND(pair.second.size())]);

    return true;
}

bool Operation::selectSourceStatement(const Pool &pool)
{
    const auto *block{getStatPair(pool).second};

    bool wasIfBlock{false};
    do
    {        
        std::size_t idx{std::numeric_limits<std::size_t>::max()};
        if(block->isIfBlock())
        {
            idx = RANDOM::RAND(block->stats().size() + 1ull);
            if(idx >= block->stats().size())
                break;
            else
                mSrc.push_back(idx);
        }
        else if(wasIfBlock)
        {
            idx = RANDOM::RAND(block->stats().size() + 1ull);
            if(idx < block->stats().size())
                mSrc.push_back(idx);
            else
            {
                mSrc.pop_back();
                break;
            }
        }
        else if(mSrc.size() == 2ull)
        {
            idx = RANDOM::RAND(block->stats().size());
            mSrc.push_back(idx);
        }
        else
        {
            idx = RANDOM::RAND(block->stats().size() + 1ull);
            if(idx >= block->stats().size())
                break;
            else
                mSrc.push_back(idx);
        }

        wasIfBlock = block->isIfBlock();
    }
    while(block = block->stats().at(mSrc.back()).second);

    return true;
}

bool Operation::selectDestinationFunction()
{
    if(SELECTABLE_DESTINATION_INDICES.empty())
        return candidateError("selectDestinationFunction()");
    
    mDst.push_back(SELECTABLE_DESTINATION_INDICES[RANDOM::RAND(SELECTABLE_DESTINATION_INDICES.size())]);

    return true;
}

bool Operation::selectDestinationStatement(const BLOCK::Block *block
    , bool isAddition)
{
    block = getStatPair(block).second;

    bool wasIfBlock{false};
    do
    {
        std::size_t idx{std::numeric_limits<std::size_t>::max()};
        if(block->isIfBlock())
        {
            idx = RANDOM::RAND(block->stats().size() + 1ull);
            if(idx >= block->stats().size())
                break;
            else
                mDst.push_back(idx);
        }
        else if(wasIfBlock)
        {
            if(isAddition)
            {
                idx = RANDOM::RAND(block->stats().size() + 1ull);
                
                if(idx <= block->stats().size())
                    mDst.push_back(idx);
                if(idx >= block->stats().size())
                    break;
            }
            else
            {
                idx = RANDOM::RAND(block->stats().size() + 1ull);
                if(idx < block->stats().size())
                    mDst.push_back(idx);
                else
                {
                    mDst.pop_back();
                    break;
                }
            }
        }
        else if(mDst.size() == 1ull)
        {
            if(isAddition)
            {
                idx = RANDOM::RAND(block->stats().size() + 1ull);
                mDst.push_back(idx);
                if(idx >= block->stats().size())
                    break;
            }
            else
            {
                if(block->stats().empty())
                    return selectionError("function has no statement");
                idx = RANDOM::RAND(block->stats().size());
                mDst.push_back(idx);
            }
        }
        else
        {
            if(isAddition)
            {
                idx = RANDOM::RAND(block->stats().size() + 2ull);
                
                if(idx <= block->stats().size())
                    mDst.push_back(idx);
                if(idx >= block->stats().size())
                    break;
            }
            else
            {
                idx = RANDOM::RAND(block->stats().size() + 1ull);
                if(idx >= block->stats().size())
                    break;
                else
                    mDst.push_back(idx);
            }
        }

        wasIfBlock = block->isIfBlock();
    }
    while(block = block->stats().at(mDst.back()).second);

    return true;
}

bool Operation::selectAlternativeIdentifier(const Pool &pool
    , const BLOCK::Block *block)
{
    std::size_t scopeId{getScopeId(block)};
    std::size_t statementId{getStatementId(pool)};

    std::shared_ptr<TOKEN::Statement> statement{std::get<std::shared_ptr<TOKEN::Statement>>(Analyzer::statementMap().at(statementId))->copy()};
    
    Selector selector;
    if(!selector.execute(scopeId
        , statement.get()
        , mIds))
        return false;
    if(!selector.execute(mIds
        , statement.get()))
        return false;

    std::optional<std::size_t> statId;
    if(!(statId = Register::execute(statement.get())))
        return false;

    mStatId = statId.value();
    return true;
}

void Operation::clear()
{
    mTag = Tag::NONE;
    mSrc.clear();
    mDst.clear();
    mIds.clear();
    mStatId = std::numeric_limits<std::size_t>::max();
}

CStatPair Operation::getStatPair(const Pool &pool) const
{
    CStatPair statPair{0ull, pool.at(mSrc.front())};

    for(std::size_t i{1ull};
        i < mSrc.size();
        i++)
        statPair = statPair.second->stats().at(mSrc[i]);
    
    return statPair;
}

CStatPair Operation::getStatPair(const BLOCK::Block *block) const
{
    CStatPair statPair{0ull, block};

    for(const auto &idx : mDst)
        statPair = statPair.second->stats().at(idx);

    return statPair;
}

std::size_t Operation::getScopeId(const BLOCK::Block *block) const
{
    for(std::size_t i{0ull};
        i + 1ull < mDst.size();
        i++)
        block = block->stats().at(mDst[i]).second;
    
    return block->scopeId();
}

std::size_t Operation::getStatementId(const Pool &pool) const
{
    const auto *block{pool.at(mSrc.front())};

    for(std::size_t i{1ull};
        i + 1ull < mSrc.size();
        i++)
        block = block->stats().at(mSrc[i]).second;
    
    return block->stats().at(mSrc.back()).first;
}

bool Operation::candidateError(const std::string &functionName) const
{
    std::cerr << "Operation::candidateError()\n"
        "    functionName: " << functionName
        << std::endl;
    return false;
}

bool Operation::selectionError(const std::string &what) const
{
    std::cerr << "Operation::selectionError()\n"
        "    what: " << what
        << std::endl;
    return false;
}

}