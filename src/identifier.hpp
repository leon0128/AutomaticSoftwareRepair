#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <string>
#include <bitset>
#include <variant>
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

class StorageClass
{
private:
    inline static constexpr const std::size_t NUM_TAG{4ull};

public:
    enum class Tag : unsigned char;

    std::bitset<NUM_TAG> flags{0b0000ull};
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
        , std::shared_ptr<TOKEN::ConstantExpression*>>;
    
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
    Identifier(const std::string&);

    virtual const std::string &key() const = 0;

    const std::string &str() const noexcept
        {return mStr;}
    std::size_t id() const noexcept
        {return mId;}

private:
    std::string mStr;
    std::size_t mId;
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
    const FunctionSpecifiers &functionSpecifiers() const noexcept
        {return mSpecifiers;}
    
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
        , std::size_t
        , const std::string&);

    const std::string &key() const noexcept override
        {return std::to_string(typeId()) + '.' + mName;}

    std::size_t typeId() const noexcept
        {return mTypeId;}
    const std::string &name() const noexcept
        {return mName;}

private:
    std::size_t mTypeId;
    std::string mName;
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