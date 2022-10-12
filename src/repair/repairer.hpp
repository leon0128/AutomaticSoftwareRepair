#ifndef REPAIR_REPAIRER_HPP
#define REPAIR_REPAIRER_HPP

#include <deque>
#include <optional>
#include <memory>
#include <functional>
#include <string>
#include <utility>
#include <mutex>

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
    bool outputResult(const std::string &filename) const;

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
    static bool outputToFile(const std::string &baseFilename
        , const std::shared_ptr<REPRESENTATION::Representation> &rep);
    static bool compile(const std::string &baseFilename);
    static bool execute(const std::string &baseFilename
        , int &score);

    void outputResultLog() const;

    bool repCreationError(const std::string &what) const;

    static bool outputError(const std::string &filename);
    static bool compilingError(const std::string &filename);

    void outputSpecifiedLog() const;

    std::shared_ptr<BLOCK::Block> mTarget;
    std::deque<std::shared_ptr<BLOCK::Block>> mPool;

    bool mIsRepaired;
    REPRESENTATION::Representation *mResult;

    // these variable is used for log.
    std::size_t mTotalGen;
    std::size_t mTotalRep;

    inline static std::mutex mIOMutex{};
};

}

#endif