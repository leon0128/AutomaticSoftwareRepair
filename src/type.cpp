#include "type.hpp"

namespace TYPE
{

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