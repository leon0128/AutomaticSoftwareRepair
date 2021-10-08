#ifndef GA_REPRESENTATION_HPP
#define GA_REPRESENTATION_HPP

#include <vector>
#include <functional>
#include <string>

namespace GA
{

namespace BLOCK
{
    class Block;
}

using Pool = std::vector<const BLOCK::Block*>;

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
    inline static const Pool TEMPORALY_POOL{};
    inline static std::reference_wrapper<const Pool> POOL{TEMPORALY_POOL};
    inline static const BLOCK::Block *INIT_BLOCK{nullptr};

public:
    static bool initialize(const Pool&
        , const BLOCK::Block*);

private:
    BLOCK::Block *mBlock;
    std::vector<const OPERATION::Operation*> mOps;

public:
    Representation();
    ~Representation();

    bool addOperation();

    Representation *copy() const;

    const BLOCK::Block *block() const noexcept
        {return mBlock;}

private:
    Representation(const BLOCK::Block*
        , const std::vector<const OPERATION::Operation*>&);

    // update block, apply mOps.back()
    bool updateBlock();

    bool creationError(const std::string &what) const;
};

}

}

#endif