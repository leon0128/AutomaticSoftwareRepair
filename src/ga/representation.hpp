#ifndef GA_REPRESENTATION_HPP
#define GA_REPRESENTATION_HPP

#include <vector>

namespace GA
{

class Operation;
class Representation;

class Operation
{
public:
    enum class Tag : unsigned char;

    Tag tag{0u};
    std::vector<std::size_t> src;
    std::vector<std::size_t> dst;
    std::vector<std::size_t> ids;
};

enum class Operation::Tag : unsigned char
{
    ADD
    , SUB
    , SWAP
};

class Representation
{
public:
    std::vector<Operation> ops;
};

}

#endif