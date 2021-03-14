#ifndef TYPE_HPP
#define TYPE_HPP

#include <vector>
#include <string>
#include <utility>
#include <any>
#include <variant>
#include <bitset>
#include <memory>

namespace TOKEN
{
    class AssignmentExpression;
    class ConstantExpression;
}

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

class StructInfo;
class EnumInfo;
class IdInfo;

class Qualifiers
{
private:
    inline static constexpr const std::size_t NUM_TAG{4ull};

public:
    enum class Tag : unsigned char;

    std::bitset<NUM_TAG> flags{0b0000ull};
};

class Base
{
public:
    enum class Tag : unsigned char;

    Tag tag{0};
    Qualifiers quals;
};

class Function
{
public:
    std::any retType;
    std::vector<Type> paramTypes;
    bool isVariable{false};
};

class Array
{
public:
    std::any eleType;
    Qualifiers quals;
    std::shared_ptr<TOKEN::AssignmentExpression> exp;
    bool hasStatic{false};
};

class Pointer
{
public:
    std::any refType;
    Qualifiers quals;
};

class Enum
{
public:
    std::size_t id{0ull};
    Qualifiers quals;
};

class Struct
{
public:
    std::size_t id{0ull};
    Qualifiers quals;
};

class Bitfield
{
public:
    std::any refType;
    std::shared_ptr<TOKEN::ConstantExpression> exp;
};

class Typedef
{
public:
    std::any refType;
    Qualifiers quals;
};

class Lvalue
{
public:
    std::any refType;
};

class Initializer
{
public:
    using Designator = std::variant<std::monostate
        , std::shared_ptr<TOKEN::ConstantExpression>
        , std::string>;
    class Element;

    std::vector<Element> elems;
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
};

class Initializer::Element
{
public:
    Designator designator;
    std::any type;
};

class StructInfo
{
public:
    using ElemT = std::pair<Type
        , std::string>;

    std::vector<ElemT> members;
    bool isUnion{false};
};

class EnumInfo
{
public:
    using ElemT = std::pair<std::string
        , std::shared_ptr<TOKEN::ConstantExpression>>;

    std::vector<ElemT> members;
};

class IdInfo
{
public:
    using Var = std::variant<std::monostate
        , StructInfo
        , EnumInfo>;

    std::size_t id{0ull};
    std::string tag;
    bool isDefined{false};
    Var var;
};

}

#endif