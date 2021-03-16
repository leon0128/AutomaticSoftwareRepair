#include "identifier.hpp"

namespace IDENTIFIER
{

Identifier::Identifier(const std::string &str)
    : mStr{str}
    , mId{NEXT_ID++}
{
}

const std::string &Identifier::key() const
{
    return mStr;
}

Object::Object(const std::string &s
    , const TYPE::Type &t
    , const StorageClass &sc
    , const Alignment &a
    , bool b)
    : Identifier{s}
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
    : Identifier{s}
    , mType{t}
    , mStorage{sc}
    , mSpecifiers{f}
    , mIsDefined{b}
{
}

Tag::Tag(const std::string &s
    , std::size_t i
    , T t)
    : Identifier{s}
    , mTypeId{i}
    , mTag{t}
{
}

Member::Member(const std::string &s
    , std::size_t i
    , const std::string &n)
    : Identifier{s}
    , mTypeId{i}
    , mName{n}
{
}

Enum::Enum(const std::string &s
    , std::size_t i)
    : Identifier{s}
    , mTypeId{i}
{
}

Typedef::Typedef(const std::string &s
    , const TYPE::Type &t)
    : Identifier{s}
    , mType{t}
{
}

Label::Label(const std::string &s
    , bool b)
    : Identifier{s}
    , mIsDefined{b}
{
}

}