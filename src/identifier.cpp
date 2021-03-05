#include "type.hpp"
#include "token.hpp"
#include "identifier.hpp"

namespace IDENTIFIER
{

Alignment::~Alignment()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<TYPE::Type*>(var))
        delete std::get<TYPE::Type*>(var);
    else if(std::holds_alternative<TOKEN::ConstantExpression*>(var))
        delete std::get<TOKEN::ConstantExpression*>(var);
}

Alignment *Alignment::copy() const
{
    if(std::holds_alternative<std::monostate>(var))
        return new Alignment();
    else if(std::holds_alternative<TYPE::Type*>(var))
        return new Alignment(std::get<TYPE::Type*>(var)->copy());
    else if(std::holds_alternative<TOKEN::ConstantExpression*>(var))
        return new Alignment(std::get<TOKEN::ConstantExpression*>(var)->copy());
}

Identifier::~Identifier()
{
    std::visit([&](auto &&p){delete p;}, var);
}

Object::~Object()
{
    delete type;
    delete alignment;
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