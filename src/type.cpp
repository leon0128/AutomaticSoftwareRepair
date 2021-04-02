#include <iostream>

#include "type.hpp"

namespace TYPE
{

bool equalTo(const TYPE::Type &lhs
    , const TYPE::Type &rhs)
{
    std::cerr << "Type error:\n"
        "    what: TYPE::equalTo() is not defined.\n"
        << std::endl;

    return true;
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