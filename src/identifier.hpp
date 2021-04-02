#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <string>
#include <bitset>
#include <variant>
#include <iostream>
#include <memory>

#include "type.hpp"

namespace TOKEN
{
    class ConstantExpression;
}

namespace IDENTIFIER
{

class StorageClass;
class Alignment;
class FunctionSpecifiers;

class Identifier;

class Object;
class Function;
class Tag;
class Member;
class Enum;
class Typedef;
class Label;

template<class DerivedType, class BaseTypePtr>
std::shared_ptr<DerivedType> dynamicPointerCast(BaseTypePtr&&);

class StorageClass
{
private:
    inline static constexpr const std::size_t NUM_TAG{6ull};

public:
    enum class Tag : unsigned char;

    std::bitset<NUM_TAG> flags{0b000000ull};
};

enum class StorageClass::Tag : unsigned char
{
    TYPEDEF
    , EXTERN
    , STATIC
    , THREAD_LOCAL
    , AUTO
    , REGISTER
};

class Alignment
{
public:
    using Var = std::variant<std::monostate
        , TYPE::Type
        , std::shared_ptr<TOKEN::ConstantExpression>>;
    
    Var var;
};

class FunctionSpecifiers
{
private:
    inline static constexpr const std::size_t NUM_TAG{2ull};

public:
    enum class Tag : unsigned char;

    std::bitset<NUM_TAG> flags{0b00ull};
};

enum class FunctionSpecifiers::Tag : unsigned char
{
    INLINE
    , NORETURN
};

class Identifier
{
private:
    inline static std::size_t NEXT_ID{0ull};

public:
    enum class DerivedTag : unsigned char;

    Identifier(DerivedTag
        , const std::string&);

    virtual const std::string &key() const
        {return mStr;}

    DerivedTag derivedTag() const noexcept
        {return mTag;}
    const std::string &str() const noexcept
        {return mStr;}
    std::size_t id() const noexcept
        {return mId;}

private:
    DerivedTag mTag;
    std::string mStr;
    std::size_t mId;
};

enum class Identifier::DerivedTag : unsigned char
{
    OBJECT
    , FUNCTION
    , TAG
    , MEMBER
    , ENUM
    , TYPEDEF
    , LABEL
};

class Object : public Identifier
{
public:
    Object(const std::string&
        , const TYPE::Type&
        , const StorageClass&
        , const Alignment&
        , bool);

    const TYPE::Type &type() const noexcept
        {return mType;}
    const StorageClass &storageClass() const noexcept
        {return mStorage;}
    void storageClass(const StorageClass &sc) noexcept
        {mStorage.flags |= sc.flags;}
    const Alignment &alignment() const noexcept
        {return mAlignment;}
    
    bool isDefined() const noexcept
        {return mIsDefined;}
    void isDefined(bool b) noexcept
        {mIsDefined = b;}

private:
    TYPE::Type mType;
    StorageClass mStorage;
    Alignment mAlignment;
    bool mIsDefined;
};

class Function : public Identifier
{
public:
    Function(const std::string&
        , const TYPE::Type&
        , const StorageClass&
        , const FunctionSpecifiers&
        , bool);
    
    const TYPE::Type &type() const noexcept
        {return mType;}
    const StorageClass &storageClass() const noexcept
        {return mStorage;}
    void storageClass(const StorageClass &sc) noexcept
        {mStorage.flags |= sc.flags;}
    const FunctionSpecifiers &functionSpecifiers() const noexcept
        {return mSpecifiers;}
    void functionSpecifiers(const FunctionSpecifiers &fs) noexcept
        {mSpecifiers.flags |= fs.flags;}
    
    bool isDefined() const noexcept
        {return mIsDefined;}
    void isDefined(bool b) noexcept
        {mIsDefined = b;}

private:
    TYPE::Type mType;
    StorageClass mStorage;
    FunctionSpecifiers mSpecifiers;
    bool mIsDefined;
};

class Tag : public Identifier
{
public:
    enum class T : unsigned char;

    Tag(const std::string&
        , std::size_t
        , T);

    std::size_t typeId() const noexcept
        {return mTypeId;}
    T tag() const noexcept
        {return mTag;}

private:
    std::size_t mTypeId;
    T mTag;
};

enum class Tag::T : unsigned char
{
    STRUCT
    , UNION
    , ENUM
};

class Member : public Identifier
{
public:
    Member(const std::string&
        , std::size_t);

    const std::string &key() const noexcept override
        {return std::to_string(typeId()) + '.' + str();}

    std::size_t typeId() const noexcept
        {return mTypeId;}

private:
    std::size_t mTypeId;
};

class Enum : public Identifier
{
public:

    Enum(const std::string&
        , std::size_t);

    std::size_t typeId() const noexcept
        {return mTypeId;}

private:
    std::size_t mTypeId;
};

class Typedef : public Identifier
{
public:
    Typedef(const std::string&
        , const TYPE::Type&);

    const TYPE::Type &type() const noexcept
        {return mType;}

private:
    TYPE::Type mType;
};

class Label : public Identifier
{
public:
    Label(const std::string&
        , bool);

    bool isDefined() const noexcept
        {return mIsDefined;}
    void isDefined(bool b) noexcept
        {mIsDefined = b;}

private:
    bool mIsDefined;
};

}

#endif