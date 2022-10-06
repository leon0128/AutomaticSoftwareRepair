#include <iostream>

#include "identifier.hpp"

inline namespace COMMON
{

namespace IDENTIFIER
{

bool notSupportedError(const std::string &msg)
{
    std::cerr << "Identifier error:\n"
        "    what: not supported.\n"
        "    ---: " << msg
        << std::endl;
    return false;
}

bool isSameType(const std::shared_ptr<Identifier> &lhs
    , const std::shared_ptr<Identifier> &rhs)
{
    using DTag = Identifier::DerivedTag;

    if(lhs->derivedTag() != rhs->derivedTag())
        return false;
    
    switch(lhs->derivedTag())
    {
        case(DTag::OBJECT):
            return TYPE::equalTo(std::dynamic_pointer_cast<Object>(lhs)->type()
                , std::dynamic_pointer_cast<Object>(rhs)->type());
        case(DTag::FUNCTION):
            return TYPE::equalTo(std::dynamic_pointer_cast<Function>(lhs)->type()
                , std::dynamic_pointer_cast<Function>(rhs)->type());
        case(DTag::TAG):
            return TYPE::equalTo(std::dynamic_pointer_cast<Tag>(lhs)->typeId()
                , std::dynamic_pointer_cast<Tag>(rhs)->typeId());
        case(DTag::MEMBER):
            return notSupportedError("Identifier::Member");
        case(DTag::ENUM):
            return TYPE::equalTo(std::dynamic_pointer_cast<Enum>(lhs)->typeId()
                , std::dynamic_pointer_cast<Enum>(rhs)->typeId());
        case(DTag::TYPEDEF):
            return TYPE::equalTo(std::dynamic_pointer_cast<Typedef>(lhs)->type()
                , std::dynamic_pointer_cast<Typedef>(rhs)->type());
        case(DTag::LABEL):
            return true;

        default:
            return notSupportedError("isSameType");
    }

    return true;
}

Identifier::Identifier(DerivedTag tag
    , const std::string &str)
    : mTag{tag}
    , mStr{str}
    , mId{NEXT_ID++}
{
}

Object::Object(const std::string &s
    , const TYPE::Type &t
    , const StorageClass &sc
    , const Alignment &a
    , bool b)
    : Identifier{DerivedTag::OBJECT
        ,s}
    , mType{t}
    , mStorage{sc}
    , mAlignment{a}
    , mIsDefined{b}
{
}

Function::Function(const std::string &s
    , const TYPE::Type &t
    , const StorageClass &sc
    , const FunctionSpecifiers &f
    , bool b)
    : Identifier{DerivedTag::FUNCTION
        ,s}
    , mType{t}
    , mStorage{sc}
    , mSpecifiers{f}
    , mIsDefined{b}
{
}

Tag::Tag(const std::string &s
    , std::size_t i
    , T t)
    : Identifier{DerivedTag::TAG
        , s}
    , mTypeId{i}
    , mTag{t}
{
}

Member::Member(const std::string &s
    , std::size_t i)
    : Identifier{DerivedTag::MEMBER
        , s}
    , mTypeId{i}
{
}

Enum::Enum(const std::string &s
    , std::size_t i)
    : Identifier{DerivedTag::ENUM
        , s}
    , mTypeId{i}
{
}

Typedef::Typedef(const std::string &s
    , const TYPE::Type &t)
    : Identifier{DerivedTag::TYPEDEF
        , s}
    , mType{t}
{
}

Label::Label(const std::string &s
    , bool b)
    : Identifier{DerivedTag::LABEL
        , s}
    , mIsDefined{b}
{
}

}

}