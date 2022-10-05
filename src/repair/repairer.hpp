#ifndef REPAIR_REPAIRER_HPP
#define REPAIR_REPAIRER_HPP

#include <deque>
#include <optional>
#include <memory>
#include <functional>
#include <string>
#include <utility>

#include "common/define.hpp"

namespace REPAIR
{

namespace BLOCK
{
    class Block;
}

namespace REPRESENTATION
{
    class Representation;
}

class Repairer
{
private:
    using Reps = std::deque<std::pair<std::shared_ptr<REPRESENTATION::Representation>, int>>;

public:
    Repairer();
    ~Repairer();

    Repairer(const Repairer&) = delete;
    Repairer(Repairer&&) = delete;

    bool execute(const CodeInformation &target
        , const std::deque<CodeInformation> &pool
        , const std::optional<std::deque<std::deque<double>>> &similarity);

    auto moveResult()
        {return std::exchange(mResult, nullptr);}

private:
    bool initialize(const CodeInformation &target
        , const std::deque<CodeInformation> &pool
        , const std::optional<std::deque<std::deque<double>>> &similarity);

    bool repair();
    // this function adds new Representation to currentReps.
    // if prevReps is empty, all of Representations are created newly.
    // otherwise, Representations are created derived or newly. 
    bool createReps(Reps &currentReps
        , const Reps &prevReps) const;
    // this fuction set a score to currentReps.
    // if repair is successful before all reps is test, remained reps is not evaluated. 
    // if repair is successful, this function sets mIsRepaired and mResult.
    bool test(Reps &currentReps);

    // this function adds Operation to base's copy and return new representation that is added Operation.
    std::shared_ptr<REPRESENTATION::Representation> createRep(const std::shared_ptr<REPRESENTATION::Representation> &base) const;
    // this function selects a base Representation.
    // no create new Representation.
    std::shared_ptr<REPRESENTATION::Representation> selectRep(const Reps &reps) const;

    // these fuctions are static member for multithread execution.
    static int evaluateRep(const std::shared_ptr<REPRESENTATION::Representation> &rep);

    bool repCreationError(const std::string &what) const;

    std::shared_ptr<BLOCK::Block> mTarget;
    std::deque<std::shared_ptr<BLOCK::Block>> mPool;

    bool mIsRepaired;
    REPRESENTATION::Representation *mResult;
};

}

#endif