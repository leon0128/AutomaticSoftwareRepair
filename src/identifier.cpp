#include "type.hpp"
#include "token.hpp"
#include "identifier.hpp"

namespace IDENTIFIER
{

Identifier::~Identifier()
{
    std::visit([&](auto &&p){delete p;}, var);
}

Object::~Object()
{
    delete type;
}

Function::~Function()
{
    delete type;
}

Typedef::~Typedef()
{
    delete type;
}

}