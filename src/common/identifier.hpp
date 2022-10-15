#ifndef COMMON_IDENTIFIER_HPP
#define COMMON_IDENTIFIER_HPP

#include <string>
#include <bitset>
#include <variant>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <utility>

#include "type.hpp"

inline namespace COMMON
{

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

inline extern std::unordered_map<std::size_t, std::shared_ptr<Identifier>> IDENTIFIER_MAP;
inline decltype(IDENTIFIER_MAP) IDENTIFIER_MAP{};
inline extern std::recursive_mutex identifierMapMutex;
inline decltype(identifierMapMutex) identifierMapMutex{};

// wrapper
template<class ...Args>
extern std::pair<decltype(IDENTIFIER_MAP)::iterator, bool> emplaceSafely(Args &&...args);
extern decltype(IDENTIFIER_MAP)::mapped_type atSafely(const decltype(IDENTIFIER_MAP)::key_type &key);

bool notSupportedError(const std::string&);

template<class DerivedType, class BaseTypePtr>
std::shared_ptr<DerivedType> dynamicPointerCast(BaseTypePtr&&);

bool isSameType(const std::shared_ptr<Identifier>&
    , const std::shared_ptr<Identifier>&);

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
    inline static std::mutex mMutex{};

    static std::size_t nextId();

public:
    enum class DerivedTag : unsigned char;

    Identifier(DerivedTag
        , const std::string&);
    virtual ~Identifier() = default;

    virtual std::string key() const
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

    std::string key() const override
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

template<class ...Args>
std::pair<decltype(IDENTIFIER_MAP)::iterator, bool> emplaceSafely(Args &&...args)
{
    std::unique_lock lock{identifierMapMutex};
    return IDENTIFIER_MAP.emplace(std::forward<Args>(args)...);
}

}

}

#endif