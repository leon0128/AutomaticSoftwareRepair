#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <variant>
#include <vector>
#include <utility>

class Token;

class Keyword;
class Identifier;
class Constant;
class StringLiteral;
class Punctuator;

class IdentifierNondigit;
class Digit;

class IntegerConstant;
class FloatingConstant;
class EnumerationConstant;
class CharacterConstant;

class EncodingPrefix;
class SCharSequence;

struct Token
{
    using Variant = std::variant<std::nullptr_t
        , Keyword*
        , Identifier*
        , Constant*
        , StringLiteral*
        , Punctuator*>;

    Variant var;

    template<class... Args>
    Token(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~Token();
};

struct Keyword
{
    enum class Tag : signed char
    {
        NONE
        , AUTO, BREAK, CASE, CHAR
        , CONST, CONTINUE, DEFAULT, DO
        , DOUBLE, ELSE, ENUM, EXTERN
        , FLOAT, FOR, GOTO, IF
        , INLINE, INT, LONG, REGISTER
        , RESTRICT, RETURN, SHORT, SIGNED
        , SIZEOF, STATIC, STRUCT, SWITCH
        , TYPEDEF, UNION, UNSIGNED, VOID
        , VOLATILE, WHILE, ALIGNAS, ALIGNOF
        , ATOMIC, BOOL, COMPLEX, GENERIC
        , IMAGINARY, NORETURN, STATIC_ASSERT, THREAD_LOCAL
    };

    Tag tag;

    constexpr Keyword(Tag inTag = Tag::NONE) noexcept
        : tag(inTag){}
    ~Keyword() = default;
};

struct Identifier
{
    using Variant = std::variant<std::nullptr_t
        , IdentifierNondigit*
        , Digit*>;
    
    std::vector<Variant> seq;

    template<class... Args>
    Identifier(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~Identifier();
};

struct Constant
{
    using Variant = std::variant<std::nullptr_t
        , IntegerConstant*
        , FloatingConstant*
        , EnumerationConstant*
        , CharacterConstant*>;
    
    Variant var;

    template<class... Args>
    Constant(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~Constant();
};

struct StringLiteral
{
    EncodingPrefix *ep;
    SCharSequence *scs;
    
    constexpr StringLiteral(EncodingPrefix *inep = nullptr
        , SCharSequence *inscs = nullptr) noexcept
        : ep(inep)
        , scs(inscs){}
    ~StringLiteral();
};

struct Punctuator
{
    enum Tag : signed char
    {
        NONE
        , L_SQUARE_BRACKET, R_SQUARE_BRACKET, L_PARENTHESIS, R_PARENTHESIS
        , L_CURLY_BRACKET, R_CURLY_BRACKET, PERIOD, ARROW
        , INCREMENT, DECREMENT, BITAND, ASTERISK
        , PLUS, MINUS, COMPL, NOT
        , SLASH, PERCENT, L_SHIFT, R_SHIFT
        , LESS, GREATER, LESS_EQUAL, GREATER_EQUAL
        , EQUAL, NOT_EQUAL, XOR, BITOR
        , AND, OR, QUESTION, COLON
        , SEMICOLON, TRIPLE_PERIOD, ASSIGNMENT, ASTERISK_ASSIGNMENT
        , SLASH_ASSIGNMENT, PERCENT_ASSIGNMENT, PLUS_ASSIGNMENT, MINUS_ASSIGNMENT
        , L_SHIFT_ASSIGNMENT, R_SHIFT_ASSIGNMENT, AND_ASSIGNMENT, XOR_ASSIGNMENT
        , BITOR_ASSIGNMENT, COMMA, HASH, DOUBLE_HASH
    };

    Tag tag;

    constexpr Punctuator(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~Punctuator() = default;
};

#endif