#ifndef REPAIR_REPRESENTATION_HPP
#define REPAIR_REPRESENTATION_HPP

#include <deque>
#include <vector>
#include <functional>
#include <string>
#include <memory>

namespace REPAIR
{

namespace BLOCK
{
    class Block;
}

namespace OPERATION
{
    class Operation;
}

namespace REPRESENTATION
{
    class Representation;
}

namespace REPRESENTATION
{

class Representation
{
private:
    inline static const std::deque<std::shared_ptr<BLOCK::Block>> TEMPORALY_POOL{};
    inline static std::reference_wrapper<const std::deque<std::shared_ptr<BLOCK::Block>>> POOL{TEMPORALY_POOL};
    inline static const std::shared_ptr<BLOCK::Block> TEMPORARY_BLOCK{};
    inline static std::reference_wrapper<const std::shared_ptr<BLOCK::Block>> INIT_BLOCK{TEMPORARY_BLOCK};

public:
    static bool initialize(const std::shared_ptr<BLOCK::Block> &target
        , const std::deque<std::shared_ptr<BLOCK::Block>> &pool);

private:
    BLOCK::Block *mBlock;
    std::deque<const OPERATION::Operation*> mOps;

public:
    Representation();
    ~Representation();

    bool addOperation();

    Representation *copy() const;

    const BLOCK::Block *block() const noexcept
        {return mBlock;}

private:
    Representation(const BLOCK::Block*
        , const std::deque<const OPERATION::Operation*>&);

    // update block, apply mOps.back()
    bool updateBlock();

    bool creationError(const std::string &what) const;
};

}

}

#endif