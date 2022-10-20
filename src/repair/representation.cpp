#include <iostream>
#include <utility>

#include "configure.hpp"
#include "utility/output.hpp"
#include "block.hpp"
#include "operation.hpp"
#include "representation.hpp"

namespace REPAIR::REPRESENTATION
{

bool Representation::initialize(const std::shared_ptr<BLOCK::Block> &target
    , const std::deque<std::shared_ptr<BLOCK::Block>> &pool)
{
    POOL = pool;
    INIT_BLOCK = target;

    return true;
}

Representation::Representation()
    : mBlock{INIT_BLOCK.get()->copy()}
    , mOps{}
{
}

Representation::~Representation()
{
    delete mBlock;
}

bool Representation::addOperation()
{
    std::shared_ptr<OPERATION::Operation> op{new OPERATION::Operation{mBlock, POOL}};

    if(op->tag() == OPERATION::Tag::NONE)
        return false;

    if(!Configure::SHOULD_CREATE_SAME_OP
        && mOps.empty())
    {
        for(auto &&[iter, endIter]{OPERATION::Operation::firstOperationMap.equal_range(op->srcId())};
            iter != endIter;
            iter++)
        {
            if(*(iter->second) == *op)
                return false;
        }
        
        OPERATION::Operation::firstOperationMap.emplace(op->srcId(), op);
    }

    mOps.emplace_back(op);

    if(!updateBlock())
    {
        mOps.pop_back();
        return false;
    }

    return true;
}

Representation *Representation::copy() const
{
    return new Representation{mBlock, mOps};
}

Representation::Representation(const BLOCK::Block *block
    , const std::deque<std::shared_ptr<OPERATION::Operation>> &ops)
    : mBlock{block->copy()}
    , mOps{}
{
    for(auto &&op : ops)
        mOps.push_back(op);
}

bool Representation::updateBlock()
{
    using namespace OPERATION;

    auto &&op{mOps.back()};

    switch(op->tag())
    {
        case(Tag::ADD):
            if(!mBlock->add(op->targetPos()
                , op->statId()))
                return false;
            break;
        case(Tag::DEL):
            if(!mBlock->subtract(op->targetPos()))
                return false;
            break;
        case(Tag::REP):
            if(!mBlock->replace(op->targetPos()
                , op->statId()))
                return false;
            break;
        
        default:;
    }

    return true;
}

bool Representation::creationError(const std::string &what) const
{
    std::cerr << OUTPUT::charRedCode
        << "Representation::creationError()\n"
        << OUTPUT::resetCode
        << "    what: " << what
        << std::endl;
    return false;
}

}