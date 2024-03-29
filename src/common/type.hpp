#ifndef COMMON_TYPE_HPP
#define COMMON_TYPE_HPP

#include <vector>
#include <string>
#include <utility>
#include <any>
#include <variant>
#include <bitset>
#include <memory>
#include <set>
#include <unordered_map>
#include <optional>
#include <set>
#include <deque>
#include <mutex>

#include "token.hpp"

inline namespace COMMON
{

namespace TYPE
{

class Qualifiers;

class Base;
class Function;
class Array;
class Pointer;
class Enum;
class Struct;
class Bitfield;
class Typedef;
class Lvalue;
class Initializer;
class Type;

class IdInfo;
class StructInfo;
class EnumInfo;

inline extern std::unordered_map<std::size_t, std::shared_ptr<IdInfo>> TYPE_MAP;
inline decltype(TYPE_MAP) TYPE_MAP{};
inline extern std::recursive_mutex typeMapMutex;
inline decltype(typeMapMutex) typeMapMutex{};

extern const std::unordered_map<TOKEN::Keyword::Tag, TOKEN::TypeSpecifier::Tag> KEYWORD_TYPE_MAP;

// wrapper
template<class ...Args>
extern std::pair<decltype(TYPE_MAP)::iterator, bool> emplaceSafely(Args &&...args);
extern decltype(TYPE_MAP)::mapped_type atSafely(const decltype(TYPE_MAP)::key_type &key);

std::optional<Type> extractType(const Typedef&);
std::optional<Type> addQualifiers(const Type&
    , const Qualifiers&);
bool equalTo(const Type&
    , const Type&
    , std::size_t rec = 0ull);
bool equalTo(const Base&
    , const Base&
    , std::size_t rec = 0ull);
bool equalTo(const Function&
    , const Function&
    , std::size_t rec = 0ull);
bool equalTo(const Array&
    , const Array&
    , std::size_t rec = 0ull);
bool equalTo(const Pointer&
    , const Pointer&
    , std::size_t rec = 0ull);
bool equalTo(const Enum&
    , const Enum&
    , std::size_t rec = 0ull);
bool equalTo(const Struct&
    , const Struct&
    , std::size_t rec = 0ull);
bool equalTo(const Bitfield&
    , const Bitfield&
    , std::size_t rec = 0ull);
bool equalTo(std::size_t
    , std::size_t
    , std::size_t rec = 0ull);

bool notSupportedError(const std::string&);
bool notDefinedError(const std::string&);
// this function return true.
bool passingMaxRecursionWarning();

class Qualifiers
{
private:
    inline static constexpr const std::size_t NUM_TAG{4ull};

public:
    enum class Tag : unsigned char;

    static const std::unordered_map<Tag, std::string> nameMap;

    std::bitset<NUM_TAG> flags{0b0000ull};

    std::string name() const;
};

class Base
{
public:
    enum class Tag : unsigned char;

    static const std::unordered_map<Tag, std::string> nameMap;
    static const std::unordered_map<Tag, std::deque<std::multiset<TOKEN::TypeSpecifier::Tag>>> typeMap;

    Tag tag{0};
    Qualifiers quals;

    std::string name() const;
};

class Function
{
public:
    std::any retType;
    std::vector<Type> paramTypes;
    bool isVariable{false};

    std::string name() const;
};

class Array
{
public:
    std::any eleType;
    Qualifiers quals;
    std::shared_ptr<TOKEN::AssignmentExpression> exp;
    bool hasStatic{false};
    bool isVariable{false};

    std::string name() const;
};

class Pointer
{
public:
    std::any refType;
    Qualifiers quals;

    std::string name() const;
};

class Enum
{
public:
    std::size_t id{0ull};
    Qualifiers quals;

    std::string name() const;
};

class Struct
{
public:
    std::size_t id{0ull};
    Qualifiers quals;

    std::string name() const;
};

class Bitfield
{
public:
    std::any refType;
    std::shared_ptr<TOKEN::ConstantExpression> exp;

    std::string name() const;
};

class Typedef
{
public:
    std::any refType;
    Qualifiers quals;

    std::string name() const;
};

class Lvalue
{
public:
    std::any refType;

    std::string name() const;
};

class Initializer
{
public:
    using Designator = std::variant<std::monostate
        , std::shared_ptr<TOKEN::ConstantExpression>
        , std::string>;
    class Element;

    std::vector<Element> elems;

    std::string name() const;
};

class Type
{
public:
    using Var = std::variant<std::monostate
        , Base
        , Function
        , Array
        , Pointer
        , Enum
        , Struct
        , Bitfield
        , Typedef
        , Lvalue
        , Initializer>;
    
    Var var;

    std::string name() const;
};

enum class Qualifiers::Tag : unsigned char
{
    CONST
    , RESTRICT
    , VOLATILE
    , ATOMIC
};

enum class Base::Tag : unsigned char
{
    VOID, CHAR, S_CHAR, U_CHAR
    , S_SHORT, U_SHORT, S_INT, U_INT
    , S_LONG, U_LONG, S_LONG_LONG, U_LONG_LONG
    , FLOAT, DOUBLE, LONG_DOUBLE, BOOL
    , FLOAT_COMPLEX, DOUBLE_COMPLEX, LONG_DOUBLE_COMPLEX
    , FLOAT128, FLOAT128_COMPLEX
    , BUILTIN_VA_LIST
};

class Initializer::Element
{
public:
    Designator designator;
    std::any type;
};

class IdInfo
{
private:
    inline static std::size_t NEXT_ID{0ull};
    // return next-id then next-id is incremented
    static std::size_t nextId();

public:
    enum class DerivedTag : unsigned char;

    IdInfo(DerivedTag
        , const std::string&);
    virtual ~IdInfo() = 0;

    DerivedTag derivedTag() const noexcept
        {return mDerivedTag;}
    std::size_t id() const noexcept
        {return mId;}
    const std::string &tag() const noexcept
        {return mTag;}
    bool isDefined() const noexcept
        {return mIsDefined;}
    void isDefined(bool b) noexcept
        {mIsDefined = b;}

private:
    DerivedTag mDerivedTag;
    std::size_t mId;
    std::string mTag;
    bool mIsDefined;
};

enum class IdInfo::DerivedTag : unsigned char
{
    STRUCT
    , ENUM
};

class StructInfo : public IdInfo
{
public:
    using ElemT = std::pair<Type
        , std::string>;
    
    std::vector<ElemT> members;
    bool isUnion;

    StructInfo(const std::string&
        , bool);
};

class EnumInfo : public IdInfo
{
public:
    using ElemT = std::pair<std::string
        , std::shared_ptr<TOKEN::ConstantExpression>>;

    std::vector<ElemT> members;

    EnumInfo(const std::string&);
};

template<class ...Args>
std::pair<decltype(TYPE_MAP)::iterator, bool> emplaceSafely(Args &&...args)
{
    std::unique_lock lock{typeMapMutex};
    return TYPE_MAP.emplace(std::forward<Args>(args)...);
}

}

}

#endif