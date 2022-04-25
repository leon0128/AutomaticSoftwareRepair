#ifndef SIMILARITY_STRUCTURE_TOKEN_METRICS_HPP
#define SIMILARITY_STRUCTURE_TOKEN_METRICS_HPP

#include <string>
#include <valarray>

namespace SIM
{

template<class T>
class StructureTokenMetrics
{
public:
    using ValueType = T;

    enum Tag : std::size_t
    {
        // keywords
        AUTO, BREAK, CASE, CHAR
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
        , ATTRIBUTE
        // punctuators
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
        // identifier
        , IDENTIFIER

        // number of enum
        , NUM_OF_ENUM
    };

    StructureTokenMetrics(const std::string &inFilename = std::string{}
        , const std::string &inFunctionName = std::string{})
        : mFilename{inFilename}
        , mFunctionName{inFunctionName}
        , mArray(static_cast<ValueType>(0), Tag::NUM_OF_ENUM){}

    constexpr auto &filename() noexcept
        {return mFilename;}
    constexpr const auto &filename() const noexcept
        {return mFilename;}
    constexpr auto &functionName() noexcept
        {return mFunctionName;}
    constexpr const auto &functionName() const noexcept
        {return mFunctionName;}
    constexpr auto &array() noexcept
        {return mArray;}
    constexpr const auto &array() const noexcept
        {return mArray;}

private:
    std::string mFilename;
    std::string mFunctionName;
    std::valarray<ValueType> mArray;
};

}

#endif