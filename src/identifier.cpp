#include "identifier.hpp"

namespace IDENTIFIER
{

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
    , std::size_t i
    , const std::string &n)
    : Identifier{DerivedTag::MEMBER
        , s}
    , mTypeId{i}
    , mName{n}
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