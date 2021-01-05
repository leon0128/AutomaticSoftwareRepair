#ifndef IDENTIIFER_HPP
#define IDENTIFIER_HPP

#include <string>
#include <variant>
#include <utility>

namespace TOKEN{class ConstantExpression;}
namespace TYPE{class Type;}

namespace IDENTIFIER
{

enum class Storage : signed char;

class Identifier;
class Object;
class Function;
class Tag;
class Member;
class Enumeration;
class Typedef;
class Label;

enum class Storage : signed char
{
    NONE
    , EXTERN
    , STATIC
    , THREAD_LOCAL_EXTERN
    , THREAD_LOCAL_STATIC
    , AUTO
    , REGISTER
};

struct Identifier
{
    using Var = std::variant<Object*
        , Function*
        , Tag*
        , Member*
        , Enumeration*
        , Typedef*
        , Label*>;
    
    std::string name;
    Var var;
    
    template<class Str, class ...Args>
    Identifier(Str &&str, Args &&...args)
        : name(std::forward<Str>(str))
        , var(std::forward<Args>(args)...){}
    ~Identifier();
};

struct Object
{
    TYPE::Type *type;
    Storage storage;
    bool isDefined;

    constexpr Object(TYPE::Type *t
        , Storage s
        , bool d) noexcept
        : type(t)
        , storage(s)
        , isDefined(d){}
    ~Object();
};

struct Function
{
    TYPE::Type *type;
    Storage storage;
    bool isDefined;

    constexpr Function(TYPE::Type *t
        , Storage s
        , bool d) noexcept
        : type(t)
        , storage(s)
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