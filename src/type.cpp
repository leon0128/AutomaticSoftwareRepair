#include <iostream>

#include "type.hpp"

namespace TYPE
{

bool equalTo(const Type &lhs
    , const Type &rhs)
{
    if(lhs.var.index() != rhs.var.index())
        return false;
    
    if(std::holds_alternative<std::monostate>(lhs.var))
        return false;
    
    if(std::holds_alternative<Base>(lhs.var))
        return equalTo(std::get<Base>(lhs.var)
            , std::get<Base>(rhs.var));
    else if(std::holds_alternative<Function>(lhs.var))
        return equalTo(std::get<Function>(lhs.var)
            , std::get<Function>(rhs.var));
    else if(std::holds_alternative<Array>(lhs.var))
        return equalTo(std::get<Array>(lhs.var)
            , std::get<Array>(rhs.var));
    else if(std::holds_alternative<Pointer>(lhs.var))
        return equalTo(std::get<Pointer>(lhs.var)
            , std::get<Pointer>(rhs.var));
    else if(std::holds_alternative<Enum>(lhs.var))
        return equalTo(std::get<Enum>(lhs.var)
            , std::get<Enum>(rhs.var));
    else if(std::holds_alternative<Struct>(lhs.var))
        return equalTo(std::get<Struct>(lhs.var)
            , std::get<Struct>(rhs.var));
    else if(std::holds_alternative<Bitfield>(lhs.var))
        return equalTo(std::get<Bitfield>(lhs.var)
            , std::get<Bitfield>(rhs.var));
    else if(std::holds_alternative<Typedef>(lhs.var))
        return equalTo(std::get<Typedef>(lhs.var)
            , std::get<Typedef>(rhs.var));
    else if(std::holds_alternative<Lvalue>(lhs.var))
        return equalTo(std::get<Lvalue>(lhs.var)
            , std::get<Lvalue>(rhs.var));
    else if(std::holds_alternative<Initializer>(lhs.var))
        return equalTo(std::get<Initializer>(lhs.var)
            , std::get<Initializer>(rhs.var));
    else
        return notSupportedError("");

    return true;
}

bool equalTo(const Base &lhs
    , const Base &rhs)
{
    return lhs.tag == rhs.tag
        && lhs.quals.flags == rhs.quals.flags;
}

bool equalTo(const Function &lhs
    , const Function &rhs)
{
    if(!equalTo(std::any_cast<Type>(lhs.retType)
        , std::any_cast<Type>(rhs.retType)))
        return false;
    
    if(lhs.paramTypes.size() != rhs.paramTypes.size())
        return false;
    for(std::size_t i{0ull};
        i < lhs.paramTypes.size();
        i++)
    {
        if(!equalTo(lhs.paramTypes[i]
            , rhs.paramTypes[i]))
            return false;
    }

    if(lhs.isVariable != rhs.isVariable)
        return false;
    
    return true;
}

bool equalTo(const Array &lhs
    , const Array &rhs)
{
    if(!equalTo(std::any_cast<Type>(lhs.eleType)
        , std::any_cast<Type>(rhs.eleType)))
        return false;
    
    if(lhs.quals.flags != rhs.quals.flags)
        return false;
    
    return true;
}

bool equalTo(const Pointer &lhs
    , const Pointer &rhs)
{
    if(!equalTo(std::any_cast<Type>(lhs.refType)
        , std::any_cast<Type>(rhs.refType)))
        return false;
    
    if(lhs.quals.flags == rhs.quals.flags)
        return false;
    
    return true;
}

bool equalTo(const Enum &lhs
    , const Enum &rhs)
{
    if(lhs.id != rhs.id)
        return false;
    
    if(lhs.quals.flags != rhs.quals.flags)
        return false;
    
    return true;
}

bool equalTo(const Struct &lhs
    , const Struct &rhs)
{
    if(lhs.id != rhs.id)
        return false;
    
    if(lhs.quals.flags != rhs.quals.flags)
        return false;
    
    return true;
}

bool equalTo(const Bitfield &lhs
    , const Bitfield &rhs)
{
    if(equalTo(std::any_cast<Type>(lhs.refType)
        , std::any_cast<Type>(rhs.refType)))
        return false;
    
    return true;
}

bool equalTo(const Typedef &lhs
    , const Typedef &rhs)
{
    if(equalTo(std::any_cast<Type>(lhs.refType)
        , std::any_cast<Type>(rhs.refType)))
        return false;

    if(lhs.quals.flags != rhs.quals.flags)
        return false;

    return true;
}

bool equalTo(const Lvalue &lhs
    , const Lvalue &rhs)
{
    if(equalTo(std::any_cast<Type>(lhs.refType)
        , std::any_cast<Type>(rhs.refType)))
        return false;
    
    return true;
}

bool equalTo(const Initializer &lhs
    , const Initializer &rhs)
{
    return notSupportedError("TYPE::equalTo(Initializer)");
}

bool notSupportedError(const std::string &msg)
{
    std::cerr << "Type error:\n"
        "    what: not supported.\n"
        "    ---: " << msg
        << std::endl;
    return false;
}

IdInfo::IdInfo(DerivedTag dTag
    , const std::string &tag)
    : mDerivedTag{dTag}
    , mId{NEXT_ID++}
    , mTag{tag}
    , mIsDefined{false}
{
}

IdInfo::~IdInfo()
{
}

StructInfo::StructInfo(const std::string &tag
    , bool b)
    : IdInfo{IdInfo::DerivedTag::STRUCT
        , tag}
    , members{}
    , isUnion{b}
{
}

EnumInfo::EnumInfo(const std::string &tag)
    : IdInfo{IdInfo::DerivedTag::ENUM
        , tag}
    , members{}
{
}

}