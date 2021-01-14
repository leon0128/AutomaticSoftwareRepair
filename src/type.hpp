#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <utility>
#include <variant>
#include <bitset>
#include <vector>

namespace TOKEN
{
    class AssignmentExpression;
    class ConstantExpression;
}

namespace TYPE
{

class IdInfo;
class StructInfo;
class EnumInfo;

class Qualifier;

class Type;
class Base;
class Function;
class Array;
class Pointer;
class Enumeration;
class Struct;
class Bitfield;
class Typedef;
class Lvalue;
class Aggregate;

struct StructInfo
{
    std::vector<std::pair<Type*, std::string>> members;

    template<class ...Args>
    StructInfo(Args &&...args)
        : members(std::forward<Args>(args)...){}
    ~StructInfo();
};

struct EnumInfo
{
    std::vector<std::pair<std::string, TOKEN::ConstantExpression*>> members;

    template<class ...Args>
    EnumInfo(Args &&...args)
        : members(std::forward<Args>(args)...){}
    ~EnumInfo();
};

struct IdInfo
{
    using Var = std::variant<std::monostate
        , StructInfo
        , EnumInfo>;
    
    std::size_t id;
    std::string tag;
    bool isDefined;
    Var var;

    template<class Str, class ...Args>
    IdInfo(std::size_t i
        , Str &&t
        , bool d
        , Args &&...args)
        : id(i)
        , tag(std::forward<Str>(t))
        , isDefined(d)
        , var(std::forward<Args>(args)...){}
    ~IdInfo() = default;
};

struct Qualifier
{
    enum class Tag : signed char
    {
        CONST = 0
        , RESTRICT = 1
        , VOLATILE = 2
        , ATOMIC = 3
    };

    std::bitset<4> flags;

    template<class ...Args>
    Qualifier(Args &&...args)
        : flags(std::forward<Args>(args)...){}
    ~Qualifier() = default;
    Qualifier(const Qualifier&) = default;
    Qualifier(Qualifier&&) = default;
};

struct Type
{
    using Var = std::variant<Base*
        , Function*
        , Array*
        , Pointer*
        , Enumeration*
        , Struct*
        , Bitfield*
        , Typedef*
        , Lvalue*
        , Aggregate*>;

    Var var;

    template<class ...Args>
    Type(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~Type();

    Type *copy() const;
};

struct Base
{
    enum class Tag : signed char
    {
        VOID, CHAR, S_CHAR, U_CHAR
        , S_SHORT, U_SHORT, S_INT, U_INT
        , S_LONG, U_LONG, S_LONG_LONG, U_LONG_LONG
        , FLOAT, DOUBLE, LONG_DOUBLE
    };

    Tag tag;
    Qualifier qualifier;

    template<class ...Args>
    Base(Tag t, Args &&...args)
        : tag(t)
        , qualifier(std::forward<Args>(args)...){}
    ~Base() = default;
    
    Base *copy() const;
};

struct Function
{
    Type *returnType;
    std::vector<Type*> arguments;
    bool isVariable;

    template<class ...Args>
    Function(Type *r, bool v, Args &&...args)
        : returnType(r)
        , arguments(std::forward<Args>(args)...)
        , isVariable(v){}
    ~Function();

    Function *copy() const;
};

struct Array
{
    Type *elementType;
    Qualifier qualifier;
    TOKEN::AssignmentExpression *exp;
    bool isVariable;
    bool hasStatic;

    template<class ...Args>
    Array(Type *element
        , TOKEN::AssignmentExpression *e
        , bool v
        , bool s
        , Args &&...args)
        : elementType(element)
        , qualifier(std::forward<Args>(args)...)
        , exp(e)
        , isVariable(v)
        , hasStatic(s){}
    ~Array();

    Array *copy() const;
};

struct Pointer
{
    Type *type;
    Qualifier qualifier;
    
    template<class ...Args>
    Pointer(Type *t, Args &&...args)
        : type(t)
        , qualifier(std::forward<Args>(args)...){}
    ~Pointer();

    Pointer *copy() const;
};

struct Enumeration
{
    std::size_t id;
    Qualifier qualifier;
    
    template<class ...Args>
    Enumeration(std::size_t i, Args &&...args)
        : id(i)
        , qualifier(std::forward<Args>(args)...){}
    ~Enumeration() = default;

    Enumeration *copy() const;
};

struct Struct
{
    std::size_t id;
    Qualifier qualifier;

    template<class ...Args>
    Struct(std::size_t i, Args &&...args)
        : id(i)
        , qualifier(std::forward<Args>(args)...){}
    ~Struct() = default;

    Struct *copy() const;
};

struct Bitfield
{
    Type *type;
    TOKEN::ConstantExpression *exp;

    constexpr Bitfield(Type *t, TOKEN::ConstantExpression *e) noexcept
        : type(t)
        , exp(e){}
    ~Bitfield();

    Bitfield *copy() const;
};

struct Typedef
{
    Type *type;
    Qualifier qualifier;
    
    template<class ...Args>
    Typedef(Type *t, Args &&...args)
        : type(t)
        , qualifier(std::forward<Args>(args)...){}
    ~Typedef();

    Typedef *copy() const;
};

struct Lvalue
{
    Type *type;

    constexpr Lvalue(Type *t) noexcept
        : type(t){}
    ~Lvalue();

    Lvalue *copy() const;
};

struct Aggregate
{
    using Designator = std::variant<std::monostate
        , TOKEN::ConstantExpression*
        , std::string>;

    struct Element
    {
        Designator designator;
        Type *type;
        
        template<class ...Args>
        Element(Type *t, Args &&...args)
            : designator(std::forward<Args>(args)...)
            , type(t){}
    };

    std::vector<Element> aggregate;

    template<class ...Args>
    Aggregate(Args &&...args)
        : aggregate(std::forward<Args>(args)...){}
    ~Aggregate();

    Aggregate *copy() const;
};

}

#endif