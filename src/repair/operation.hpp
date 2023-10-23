#ifndef REPAIR_OPERATION_HPP
#define REPAIR_OPERATION_HPP

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <deque>
#include <memory>
#include <tuple>

inline namespace COMMON
{
namespace TOKEN
{
    class Statement;
}
}

namespace REPAIR
{

namespace BLOCK
{
    class Block;
}

using StatPair = std::pair<std::size_t, BLOCK::Block*>;
using CStatPair = std::pair<std::size_t, const BLOCK::Block*>;

namespace OPERATION
{

enum class Tag : unsigned char;
class Operation;
class OperationHash;

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
    using ScopeId = std::size_t;
    using StatId = std::size_t;
    using Prob = double;

    static std::vector<std::size_t> SELECTABLE_DESTINATION_INDICES;

    // key: scope-id
    // value: array of probabirity and selectable statement-id
    static std::unordered_map<ScopeId
        , std::deque<std::pair<Prob, StatId>>> SELECTABLE_STATEMENT_MAP;

    // key: destination function's scope-id.
    // value:
    //  key: source function's scope-id.
    //  value: probability.
    static std::unordered_map<ScopeId, std::deque<std::pair<ScopeId, double>>> SIMILARITY;

    // key: scope-id that is belonged to value.
    // value: function's scope-id.
    static std::unordered_map<ScopeId, ScopeId> SCOPE_BELONGED_SCOPE_MAP;
    // key: function's scope-id.
    // value: similarity's row index that indicates key's function.
    static std::unordered_map<ScopeId, std::size_t> SCOPE_ROW_MAP;
    // key: stat-id that is belonged to value.
    // value: scope-id (not function's id)
    static std::unordered_map<std::size_t, ScopeId> STAT_BELONGED_SCOPE_MAP;
    // key: function's scope-id.
    // value: similarity's column index that indicates key's function.
    static std::unordered_map<ScopeId, std::size_t> SCOPE_COLUMN_MAP;

public:
    // this object contains operation that is created.
    //  first: srcId (if operation::tag is sub, srcId's value is max).
    inline static std::unordered_multimap<std::size_t, std::shared_ptr<Operation>> createdOperations{};
    // this object indicates count of same op created.
    inline static std::size_t createdSameOpCount{0ull};

    inline static const auto &similarity()
        {return SIMILARITY;}
    inline static const auto &scopeBelongedScopeMap()
        {return SCOPE_BELONGED_SCOPE_MAP;}

    static bool initialize(const std::shared_ptr<BLOCK::Block> &target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool);
    static bool initialize(const std::shared_ptr<BLOCK::Block> &target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool
        , const std::deque<std::deque<double>> &similarity);

private:
    static bool initializeSelectableStatement(const std::shared_ptr<BLOCK::Block> &target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool);
    static void insertScopeId(const BLOCK::Block*);
    static bool insertStatementId(std::size_t scopeId
        , const BLOCK::Block*);

    // initialize
    //  scope-belonged-scope-map
    //  , scope-row-map
    //  , stat-belonged-scope-map
    //  , scope-column-map
    static bool initializeMap(const std::shared_ptr<BLOCK::Block> &target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool);

    // initialize SIMILARITY    
    static bool initializeSimilarity(const std::shared_ptr<BLOCK::Block> &target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool
        , const std::deque<std::deque<double>> &similarity);

    // discard selectable statemnt that has low similarity.
    static bool discard();

    static bool setProbability();
    static Prob getSimilarity(ScopeId destScopeId
        , std::size_t srcStatId);
    static std::size_t getRank(ScopeId destScopeId
        , std::size_t srcStatId);

    static bool initializationError(const std::string &what);

private:
    Tag mTag;
    std::deque<std::size_t> mTargetPos; // for addition, deletion and replacement
    std::size_t mSrcId; // source statement id, for addition and replacement
    std::size_t mStatId; // alternative statement id, for addition and replacement
    std::deque<std::size_t> mAltIds;

public:
    Operation();
    Operation(const BLOCK::Block *target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool);
    Operation(const BLOCK::Block *target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool
        , Tag);

    Tag tag() const noexcept
        {return mTag;}
    auto &&targetPos() const noexcept
        {return mTargetPos;}
    std::size_t srcId() const noexcept
        {return mSrcId;}
    std::size_t statId() const noexcept
        {return mStatId;}
    auto &&altIds() const noexcept
        {return mAltIds;}

private:
    bool selectAdditionalPosition(const BLOCK::Block *target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool);
    bool selectSubtractionalPosition(const BLOCK::Block *target);
    bool selectReplacingPosition(const BLOCK::Block *target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool);
    
    // mDst[0].
    bool selectDestinationFunction();
    // mDst[1] ... .
    bool selectDestinationStatement(const BLOCK::Block*
        , bool isAddition);
    // mSrcId
    bool selectSourceStatement(const BLOCK::Block *target);
    // mStatId
    bool selectAlternativeIdentifier(const BLOCK::Block *target);

    void clear();

    CStatPair getStatPair(const BLOCK::Block *target) const; // use mDst
    std::size_t getScopeId(const BLOCK::Block *target) const; // use mDst (no use mDst.back)

    bool candidateError(const std::string &functionName) const;
    bool selectionError(const std::string &what) const;
};

extern bool operator==(const Operation &lhs
    , const Operation &rhs);
extern bool operator!=(const Operation &lhs
    , const Operation &rhs);

}

}

#endif