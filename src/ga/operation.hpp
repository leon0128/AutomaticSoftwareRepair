#ifndef GA_OPERATION_HPP
#define GA_OPERATION_HPP

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

namespace GA
{

namespace BLOCK
{
    class Block;
}

using StatPair = std::pair<std::size_t, BLOCK::Block*>;
using CStatPair = std::pair<std::size_t, const BLOCK::Block*>;
using Pool = std::vector<const BLOCK::Block*>;

namespace OPERATION
{

enum class Tag : unsigned char;
class Operation;

Tag selectTag();

enum class Tag : unsigned char
{
    NONE
    , ADD
    , DEL
    , REP
};

class Operation
{
private:
    static std::vector<
        std::pair<
            std::size_t
                , std::vector<
                    std::size_t>>> SELECTABLE_SOURCE_POOL_AND_FUNCTION_INDICES;
    static std::vector<std::size_t> SELECTABLE_DESTINATION_INDICES;

    // key: scope-id
    // value: array of selectable statement-id
    static std::unordered_map<std::size_t
        , std::vector<std::size_t>> SELECTABLE_STATEMENT_MAP;

public:
    static bool initialize(const Pool &pool
        , const BLOCK::Block*);

private:
    static bool initializeSelectableStatement(const Pool &pool
        , const BLOCK::Block*);
    static void insertScopeId(const BLOCK::Block*);
    static bool insertStatementId(std::size_t scopeId
        , const BLOCK::Block*);

private:
    Tag mTag;
    std::vector<std::size_t> mSrc; // for addition and replacement
    std::vector<std::size_t> mDst; // for addition, deletion and replacement
    std::vector<std::size_t> mIds; // for addition and replacement
    std::size_t mSrcId; // source statement id, for addition and replacement
    std::size_t mStatId; // alternative statement id, for addition and replacement

public:
    Operation();
    Operation(const Pool &pool
        , const BLOCK::Block *srcBlock);
    Operation(const Pool &pool
        , const BLOCK::Block *srcBlock
        , Tag);

    Tag tag() const noexcept
        {return mTag;}
    const std::vector<std::size_t> &src() const noexcept
        {return mSrc;}
    const std::vector<std::size_t> &dst() const noexcept
        {return mDst;}
    const std::vector<std::size_t> &ids() const noexcept
        {return mIds;}
    std::size_t srcId() const noexcept
        {return mSrcId;}
    std::size_t statId() const noexcept
        {return mStatId;}

private:
    bool selectAdditionalPosition(const Pool &pool
        , const BLOCK::Block*);
    bool selectSubtractionalPosition(const BLOCK::Block*);
    bool selectReplacingPosition(const Pool &pool
        , const BLOCK::Block*);
    
    // mSrc[0] and mSrc[1].
    bool selectSourcePoolAndFunction();
    // mSrc[2] ... .
    bool selectSourceStatement(const Pool&);
    // mDst[0].
    bool selectDestinationFunction();
    // mDst[1] ... .
    bool selectDestinationStatement(const BLOCK::Block*
        , bool isAddition);
    // mStatId and mIds[0] ... .
    bool selectAlternativeIdentifier(const Pool&
        , const BLOCK::Block*);
    // mSrcId
    bool selectSourceStatement(const BLOCK::Block*);
    // mStatId and mIds[0] ...
    bool selectAlternativeIdentifier(const BLOCK::Block*);

    void clear();

    CStatPair getStatPair(const Pool&) const; // use mSrc
    CStatPair getStatPair(const BLOCK::Block*) const; // use mDst
    std::size_t getScopeId(const BLOCK::Block*) const; // use mDst (no use mDst.back)
    std::size_t getStatementId(const Pool&) const; // use mSrc

    bool candidateError(const std::string &functionName) const;
    bool selectionError(const std::string &what) const;
};

}

}

#endif