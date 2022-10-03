#include <iostream>
#include <algorithm>
#include <numeric>
#include <limits>
#include <map>

#include "../utility/output.hpp"
#include "../utility/random.hpp"
#include "../configure.hpp"
#include "../analyzer.hpp"
#include "register.hpp"
#include "selector.hpp"
#include "block.hpp"
#include "operation.hpp"

namespace REPAIR::OPERATION
{

decltype(Operation::SELECTABLE_DESTINATION_INDICES) Operation::SELECTABLE_DESTINATION_INDICES{};
decltype(Operation::SELECTABLE_STATEMENT_MAP) Operation::SELECTABLE_STATEMENT_MAP{};
decltype(Operation::SIMILARITY) Operation::SIMILARITY{};
decltype(Operation::SCOPE_BELONGED_SCOPE_MAP) Operation::SCOPE_BELONGED_SCOPE_MAP{};
decltype(Operation::SCOPE_ROW_MAP) Operation::SCOPE_ROW_MAP{};
decltype(Operation::STAT_BELONGED_SCOPE_MAP) Operation::STAT_BELONGED_SCOPE_MAP{};
decltype(Operation::SCOPE_COLUMN_MAP) Operation::SCOPE_COLUMN_MAP{};

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

    if(!initializeSelectableStatement(pool
        , block))
        return false;

    if(!initializeMap(pool, block))
        return false;

    return true;
}

bool Operation::initialize(const Pool &pool
    , const BLOCK::Block *target
    , const std::deque<std::deque<double>> &similarity)
{
    if(!initialize(pool, target))
        return false;

    if(!initializeSimilarity(pool, target, similarity))
        return false;
    
    if(!discard())
        return false;

    if(!setProbability())
        return false;

    return true;
}

bool Operation::initializeSelectableStatement(const Pool &pool
    , const BLOCK::Block *block)
{
    for(auto &&[statId, subBlock] : block->stats())
    {
        if(subBlock != nullptr)
            insertScopeId(subBlock);
    }

    for(const auto &pair : SELECTABLE_STATEMENT_MAP)
    {
        for(const auto *b : pool)
        {
            if(!insertStatementId(pair.first
                , b))
                return false;
        }
    }
        
    return true;
}

void Operation::insertScopeId(const BLOCK::Block *block)
{
    if(SELECTABLE_STATEMENT_MAP.find(block->scopeId()) == SELECTABLE_STATEMENT_MAP.end())
        SELECTABLE_STATEMENT_MAP.emplace(block->scopeId()
            , decltype(SELECTABLE_STATEMENT_MAP)::mapped_type{});

    for(const auto &pair : block->stats())
    {
        if(pair.second != nullptr)
            insertScopeId(pair.second);
    }
}

bool Operation::insertStatementId(std::size_t scopeId
    , const BLOCK::Block *block)
{
    Selector selector;

    for(const auto &pair : block->stats())
    {
        if(pair.first != std::numeric_limits<decltype(pair.first)>::max())
        {
            auto &&var{Analyzer::statementMap().at(pair.first)};
            if(std::holds_alternative<std::shared_ptr<TOKEN::Statement>>(var))
            {
                auto &&statement{std::get<std::shared_ptr<TOKEN::Statement>>(var)};
                if(selector.isFittable(scopeId
                    , statement.get()))
                {
                    SELECTABLE_STATEMENT_MAP
                        .at(scopeId)
                            .emplace_back(0.0
                                , statement->statementId);
                }
            }
        }

        if(pair.second != nullptr)
            insertStatementId(scopeId
                , pair.second);
    }

    // set probabirity that is average value.
    if(!SELECTABLE_STATEMENT_MAP.at(scopeId).empty())
    {
        double averageProp{1.0 / static_cast<double>(SELECTABLE_STATEMENT_MAP.at(scopeId).size())};
        for(auto &&[prob, statId] : SELECTABLE_STATEMENT_MAP.at(scopeId))
            prob = averageProp;
    }

    return true;
}

bool Operation::initializeMap(const Pool &pool
    , const BLOCK::Block *target)
{
    // set scope-belonged-scope-map and stat-belonged-scope-map.
    // rec: set a this function.
    auto &&insert{[](auto &&rec
        , ScopeId funcId
        , const BLOCK::Block *block)
        -> void
        {
            SCOPE_BELONGED_SCOPE_MAP[block->scopeId()] = funcId;
            for(auto &&[statId, subBlock] : block->stats())
            {
                if(!block->isIfBlock())
                    STAT_BELONGED_SCOPE_MAP[statId] = block->scopeId();
                if(subBlock != nullptr)
                    rec(rec, funcId, subBlock);
            }
        }};

    // set a scope-row-map.
    for(auto &&[statId, block] : target->stats())
    {
        if(!block)
            continue;

        SCOPE_ROW_MAP[block->scopeId()] = SCOPE_ROW_MAP.size();
        insert(insert, block->scopeId(), block);
    }

    // set a scope-column-map.
    for(auto &&block : pool)
    {
        for(auto &&[statId, subBlock] : block->stats())
        {
            if(!subBlock)
                continue;

            SCOPE_COLUMN_MAP[subBlock->scopeId()] = SCOPE_COLUMN_MAP.size();
            insert(insert, subBlock->scopeId(), subBlock);
        }
    }

    return true;
}

bool Operation::initializeSimilarity(const Pool &pool
    , const BLOCK::Block *target
    , const std::deque<std::deque<double>> &similarity)
{
    // key
    for(std::size_t row{0ull};
        auto &&[statId, targetBlock] : target->stats())
    {
        if(!targetBlock)
            continue;

        auto &&mappedValue{SIMILARITY[targetBlock->scopeId()] = decltype(SIMILARITY)::mapped_type{}};
    
        // value
        for(std::size_t column{0ull};
            auto &&poolBlock : pool)
        {
            for(auto &&[statId, subBlock] : poolBlock->stats())
            {
                if(!subBlock)
                    continue;
            
                mappedValue.emplace_back(subBlock->scopeId()
                    , similarity.at(row).at(column));
                
                column++;
            }
        }

        std::sort(mappedValue.begin()
            , mappedValue.end()
            , [](auto &&lhs, auto &&rhs){return lhs.second > rhs.second;});

        row++;
    }

    return true;
}

bool Operation::discard()
{
    auto &&isSimilar{[](ScopeId scopeId
        , std::size_t statId)
        -> bool
        {
            auto &&destScopeId{SCOPE_BELONGED_SCOPE_MAP.at(scopeId)};
            auto &&srcScopeId{SCOPE_BELONGED_SCOPE_MAP.at(STAT_BELONGED_SCOPE_MAP.at(statId))};

            auto &&iter{std::find_if(SIMILARITY.at(destScopeId).begin()
                , SIMILARITY.at(destScopeId).end()
                , [&](auto &&pair){return pair.first == srcScopeId;})};

            if(iter == SIMILARITY.at(destScopeId).end())
                return false;

            return iter - SIMILARITY.at(destScopeId).begin() < static_cast<long int>(Configure::SIM_NUMBER_OF_USE);
        }};

    for(auto &&[scopeId, statIds] : SELECTABLE_STATEMENT_MAP)
    {
        std::erase_if(statIds
            , [&](auto &&pair){return !isSimilar(scopeId, pair.second);});
    }

    return true;
}

bool Operation::setProbability()
{
    for(auto &&[scopeId, statIds] : SELECTABLE_STATEMENT_MAP)
    {
        if(statIds.empty())
            continue;

        double sum{0.0};
        for(auto &&[prob, statId] : statIds)
        {
            prob = Configure::SHOULD_CHANGE_PROB
                    ? getSimilarity(scopeId, statId)
                    : 1.0;
            sum += prob;
        }

        if(sum - 0.0 <= std::numeric_limits<double>::epsilon())
        {
            for(auto &&[prob, statId] : statIds)
                prob = 1.0 / static_cast<double>(statIds.size());
        }
        else
        {
            for(auto &&[prob, statId] : statIds)
                prob = prob / sum;
        }
    }

    return true;
}

double Operation::getSimilarity(ScopeId scopeId
    , std::size_t statId)
{
    auto &&destScopeId{SCOPE_BELONGED_SCOPE_MAP.at(scopeId)};
    auto &&srcScopeId{SCOPE_BELONGED_SCOPE_MAP.at(STAT_BELONGED_SCOPE_MAP.at(statId))};

    auto &&mappedValue{SIMILARITY.at(destScopeId)};
    auto &&iter{std::find_if(mappedValue.begin()
        , mappedValue.end()
        , [&](auto &&pair){return pair.first == srcScopeId;})};

    if(iter == mappedValue.end())
    {
        initializationError("related similarity is not found.");
        return 0.0;
    }

    return iter->second;
}

bool Operation::initializationError(const std::string &what)
{
    std::cerr << "Operation::initializationError():\n"
        "    what: " << what
        << std::endl;
    return false;
}

Operation::Operation()
    : mTag{Tag::NONE}
    , mSrc{}
    , mDst{}
    , mIds{}
    , mSrcId{std::numeric_limits<std::size_t>::max()}
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
    , mSrcId{std::numeric_limits<std::size_t>::max()}
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
    if(!selectDestinationFunction()
        || !selectDestinationStatement(srcBlock
            , true)
        || !selectSourceStatement(srcBlock)
        || !selectAlternativeIdentifier(srcBlock))
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
    if(!selectDestinationFunction()
        || !selectDestinationStatement(srcBlock
            , false)
        || !selectSourceStatement(srcBlock)
        || !selectAlternativeIdentifier(srcBlock))
    {
        clear();
        return false;
    }
    
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
    while((block = block->stats().at(mDst.back()).second));

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

bool Operation::selectSourceStatement(const BLOCK::Block *block)
{
    auto &&scopeId{getScopeId(block)};
    auto &&ids{SELECTABLE_STATEMENT_MAP.at(scopeId)};

    if(ids.empty())
        return selectionError("no have statement that is addable to destination position.");

    for(double prob{RANDOM::RAND.floating<double>()}
            , sum{0.0};
        auto &&[p, statId] : ids)
    {
        if((sum += p) >= prob)
        {
            mSrcId = statId;
            break;
        }
    }
    
    return true;
}

bool Operation::selectAlternativeIdentifier(const BLOCK::Block *block)
{
    auto &&scopeId{getScopeId(block)};

    std::shared_ptr<TOKEN::Statement> statement{std::get<std::shared_ptr<TOKEN::Statement>>(Analyzer::statementMap().at(mSrcId))->copy()};

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