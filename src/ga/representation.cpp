#include <iostream>
#include <utility>

#include "../configure.hpp"
#include "block.hpp"
#include "operation.hpp"
#include "representation.hpp"

namespace GA::REPRESENTATION
{

bool Representation::initialize(const Pool &pool
    , const BLOCK::Block *block)
{
    POOL = pool;
    INIT_BLOCK = block;

    return true;
}

Representation::Representation()
    : mBlock{INIT_BLOCK->copy()}
    , mOps{}
{
}

Representation::~Representation()
{
    delete mBlock;
    for(auto *op : mOps)
        delete op;
}

bool Representation::addOperation()
{
    OPERATION::Operation op{POOL
        , mBlock};

    if(op.tag() != OPERATION::Tag::NONE)
        mOps.emplace_back(new OPERATION::Operation{std::move(op)});
    else
        return false;

    if(!updateBlock())
        return false;

    return true;
}

Representation *Representation::copy() const
{
    return new Representation{mBlock
        , mOps};
}

Representation::Representation(const BLOCK::Block *block
    , const std::vector<const OPERATION::Operation*> &ops)
    : mBlock{block->copy()}
    , mOps{}
{
    for(const auto *op : ops)
        mOps.push_back(new OPERATION::Operation{*op});
}

bool Representation::updateBlock()
{
    using namespace OPERATION;

    const auto *op{mOps.back()};

    switch(op->tag())
    {
        case(Tag::ADD):
            if(!mBlock->add(op->dst()
                , op->statId()))
                return false;
            break;
        case(Tag::DEL):
            if(!mBlock->subtract(op->dst()))
                return false;
            break;
        case(Tag::REP):
            if(!mBlock->replace(op->dst()
                , op->statId()))
                return false;
            break;
        
        default:;
    }

    return true;
}

bool Representation::creationError(const std::string &what) const
{
    std::cerr << "Representation::creationError()\n"
        "    what: " << what
        << std::endl;
    return false;
}

}