#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <string>
#include <variant>
#include <utility>
#include <bitset>

namespace TOKEN{class ConstantExpression;}
namespace TYPE{class Type;}

namespace IDENTIFIER
{

class Storage;
class Alignment;
class FunctionSpecifier;

class Identifier;
class Object;
class Function;
class Tag;
class Member;
class Enumeration;
class Typedef;
class Label;

struct Storage
{
    enum class Tag : signed char
    {
        TYPEDEF = 0
        , EXTERN = 1
        , STATIC = 2
        , THREAD_LOCAL = 3
        , AUTO = 4
        , REGISTER = 5
    };

    std::bitset<6> flags;
    
    Storage(std::bitset<6> f)
        : flags(f){}
    ~Storage() = default;
};

struct Alignment
{
    using Var = std::variant<std::monostate
        , TYPE::Type*
        , TOKEN::ConstantExpression*>;
    
    Var var;

    template<class ...Args>
    Alignment(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~Alignment();

    Alignment *copy() const;
};

struct FunctionSpecifier
{
    enum class Tag : signed char
    {
        INLINE = 0
        , NORETURN = 1
    };

    std::bitset<2> flags;
    
    FunctionSpecifier(std::bitset<2> f)
        : flags(f){}
    ~FunctionSpecifier() = default;
    FunctionSpecifier(const FunctionSpecifier&) = default;
    FunctionSpecifier(FunctionSpecifier&&) = default;
};

struct Identifier
{
private:
    static inline std::size_t NEXT_ID = 0;
    std::size_t mId;

public:
    using Var = std::variant<Object*
        , Function*
        , Tag*
        , Member*
        , Enumeration*
        , Typedef*
        , Label*>;

    std::size_t id() const noexcept
        {return mId;}
    std::string name;
    Var var;

    template<class Str, class ...Args>
    Identifier(Str &&str, Args &&...args)
        : mId(NEXT_ID++)
        , name(std::forward<Str>(str))
        , var(std::forward<Args>(args)...){}
    ~Identifier();
};

struct Object
{
    TYPE::Type *type;
    Storage storage;
    Alignment *alignment;
    bool isDefined;

    Object(TYPE::Type *t
        , Storage s
        , Alignment *a
        , bool d)
        : type(t)
        , storage(s)
        , alignment(a)
        , isDefined(d){}
    ~Object();
};

struct Function
{
    TYPE::Type *type;
    Storage storage;
    FunctionSpecifier specifier;
    bool isDefined;

    Function(TYPE::Type *t
        , Storage s
        , bool d
        , FunctionSpecifier fs)
        : type(t)
        , storage(s)
        , specifier(fs)
        , isDefined(d){}
    ~Function();
};

struct Tag
{
    enum class T : signed char
    {
        STRUCT
        , UNION
        , ENUM
    };

    std::size_t id;
    T tag;
    bool isDefined;

    constexpr Tag(std::size_t i
        , T t
        , bool d) noexcept
        : id(i)
        , tag(t)
        , isDefined(d){}
    ~Tag() = default;
};

struct Member
{
    std::size_t id;
    std::string name;

    template<class Str>
    Member(std::size_t i
        , Str &&n)
        : id(i)
        , name(std::forward<Str>(n)){}
    ~Member() = default;
};

struct Enumeration
{
    std::size_t id;

    constexpr Enumeration(std::size_t i) noexcept
        : id(i){}
    ~Enumeration() = default;
};

struct Typedef
{
    TYPE::Type *type;
    
    constexpr Typedef(TYPE::Type *t) noexcept
        : type(t){}
    ~Typedef();
};

struct Label
{
    bool isDefined;

    constexpr Label(bool d) noexcept
        : isDefined(d){}
    ~Label() = default;
};

}

#endif