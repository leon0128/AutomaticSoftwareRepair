#include "token.hpp"
#include "type.hpp"

namespace TYPE
{

StructInfo::~StructInfo()
{
    for(auto &&p : members)
        delete p.first;
}

EnumInfo::~EnumInfo()
{
    for(auto &&p : members)
        delete p.second;
}

Type::~Type()
{
    std::visit([&](auto &&p){delete p;}, var);
}

Type *Type::copy() const
{
    Type *ret = nullptr;
    std::visit([&](auto &&p){ret = new Type(p->copy());}, var);
    return ret;
}

Base *Base::copy() const
{
    return new Base(tag, qualifier);
}

Function::~Function()
{
    delete returnType;
    for(auto &&t : arguments)
        delete t;
}

Function *Function::copy() const
{
    std::vector<Type*> args;
    for(auto &&t : arguments)
        args.push_back(t->copy());

    return new Function(returnType->copy(), isVariable, std::move(args));
}

Array::~Array()
{
    delete elementType;
    delete exp;
}

Array *Array::copy() const
{
    return new Array(elementType->copy()
        , exp->copy()
        , isVariable
        , hasStatic
        , qualifier);
}

Pointer::~Pointer()
{
    delete type;
}

Pointer *Pointer::copy() const
{
    return new Pointer(type->copy(), qualifier);
}

Enumeration *Enumeration::copy() const
{
    return new Enumeration(id, qualifier);
}

Struct *Struct::copy() const
{
    return new Struct(id, qualifier);
}

Bitfield::~Bitfield()
{
    delete type;
    delete exp;
}

Bitfield *Bitfield::copy() const
{
    return new Bitfield(type->copy(), exp->copy());
}

Typedef::~Typedef()
{
    delete type;
}

Typedef *Typedef::copy() const
{
    return new Typedef(type->copy(), qualifier);
}

Lvalue::~Lvalue()
{
    delete type;
}

Lvalue *Lvalue::copy() const
{
    return new Lvalue(type->copy());
}

Aggregate::~Aggregate()
{
    for(auto &&e : aggregate)
    {
        delete e.type;
        if(std::holds_alternative<TOKEN::ConstantExpression*>(e.designator))
            delete std::get<TOKEN::ConstantExpression*>(e.designator);
    }
}

Aggregate *Aggregate::copy() const
{
    std::vector<Element> agg;
    for(auto &&e : aggregate)
    {
        agg.emplace_back(e.type->copy());
        if(std::holds_alternative<std::monostate>(e.designator)
            || std::holds_alternative<std::string>(e.designator))
            agg.back().designator = e.designator;
        else if(std::holds_alternative<TOKEN::ConstantExpression*>(e.designator))
            agg.back().designator.emplace<TOKEN::ConstantExpression*>(std::get<TOKEN::ConstantExpression*>(e.designator)->copy());
    }

    return new Aggregate(std::move(agg));
}

}