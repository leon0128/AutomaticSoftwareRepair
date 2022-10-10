#ifndef ANALYZER_TOKENIZER_HPP
#define ANALYZER_TOKENIZER_HPP

#include <string>
#include <unordered_map>

#include "common/token.hpp"

namespace ANALYZER
{

namespace TOKENIZER
{

    extern TOKEN::PreprocessingToken *decPreprocessingToken(const std::string &src
        , std::size_t &idx);
    extern TOKEN::Identifier *decIdentifier(const std::string &src
        , std::size_t &idx);
    extern TOKEN::PPNumber *decPPNumber(const std::string &src
        , std::size_t &idx);
    extern TOKEN::CharacterConstant *decCharacterConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::StringLiteral *decStringLiteral(const std::string &src
        , std::size_t &idx);
    extern TOKEN::Punctuator *decPunctuator(const std::string &src
        , std::size_t &idx);
    extern TOKEN::IdentifierNondigit *decIdentifierNondigit(const std::string &src
        , std::size_t &idx);
    extern TOKEN::Digit *decDigit(const std::string &src
        , std::size_t &idx);
    extern TOKEN::Sign *decSign(const std::string &src
        , std::size_t &idx);
    extern TOKEN::CCharSequence *decCCharSequence(const std::string &src
        , std::size_t &idx);
    extern TOKEN::EncodingPrefix *decEncodingPrefix(const std::string &src
        , std::size_t &idx);
    extern TOKEN::SCharSequence *decSCharSequence(const std::string &src
        , std::size_t &idx);
    extern TOKEN::Nondigit *decNondigit(const std::string &src
        , std::size_t &idx);
    extern TOKEN::UniversalCharacterName *decUniversalCharacterName(const std::string &src
        , std::size_t &idx);
    extern TOKEN::CChar *decCChar(const std::string &src
        , std::size_t &idx);
    extern TOKEN::SChar *decSChar(const std::string &src
        , std::size_t &idx);
    extern TOKEN::HexQuad *decHexQuad(const std::string &src
        , std::size_t &idx);
    extern TOKEN::EscapeSequence *decEscapeSequence(const std::string &src
        , std::size_t &idx);
    extern TOKEN::HexadecimalDigit *decHexadecimalDigit(const std::string &src
        , std::size_t &idx);
    extern TOKEN::SimpleEscapeSequence *decSimpleEscapeSequence(const std::string &src
        , std::size_t &idx);
    extern TOKEN::OctalEscapeSequence *decOctalEscapeSequence(const std::string &src
        , std::size_t &idx);
    extern TOKEN::HexadecimalEscapeSequence *decHexadecimalEscapeSequence(const std::string &src
        , std::size_t &idx);
    extern TOKEN::OctalDigit *decOctalDigit(const std::string &src
        , std::size_t &idx);
    extern TOKEN::IntegerConstant *decIntegerConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::FloatingConstant *decFloatingConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::DecimalConstant *decDecimalConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::IntegerSuffix *decIntegerSuffix(const std::string &src
        , std::size_t &idx);
    extern TOKEN::OctalConstant *decOctalConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::HexadecimalConstant *decHexadecimalConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::DecimalFloatingConstant *decDecimalFloatingConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::HexadecimalFloatingConstant *decHexadecimalFloatingConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::NonzeroDigit *decNonzeroDigit(const std::string &src
        , std::size_t &idx);
    extern TOKEN::UnsignedSuffix *decUnsignedSuffix(const std::string &src
        , std::size_t &idx);
    extern TOKEN::LongSuffix *decLongSuffix(const std::string &src
        , std::size_t &idx);
    extern TOKEN::LongLongSuffix *decLongLongSuffix(const std::string &src
        , std::size_t &idx);
    extern TOKEN::HexadecimalPrefix *decHexadecimalPrefix(const std::string &src
        , std::size_t &idx);
    extern TOKEN::FractionalConstant *decFractionalConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::ExponentPart *decExponentPart(const std::string &src
        , std::size_t &idx);
    extern TOKEN::FloatingSuffix *decFloatingSuffix(const std::string &src
        , std::size_t &idx);
    extern TOKEN::DigitSequence *decDigitSequence(const std::string &src
        , std::size_t &idx);
    extern TOKEN::HexadecimalFractionalConstant *decHexadecimalFractionalConstant(const std::string &src
        , std::size_t &idx);
    extern TOKEN::BinaryExponentPart *decBinaryExponentPart(const std::string &src
        , std::size_t &idx);
    extern TOKEN::HexadecimalDigitSequence *decHexadecimalDigitSequence(const std::string &src
        , std::size_t &idx);

    inline extern const std::unordered_map<std::string, TOKEN::Punctuator::Tag> PUNCTUATOR_MAP
        = {{"[", TOKEN::Punctuator::Tag::L_SQUARE_BRACKET}
            , {"]", TOKEN::Punctuator::Tag::R_SQUARE_BRACKET}
            , {"(", TOKEN::Punctuator::Tag::L_PARENTHESIS}
            , {")", TOKEN::Punctuator::Tag::R_PARENTHESIS}
            , {"{", TOKEN::Punctuator::Tag::L_CURLY_BRACKET}
            , {"}", TOKEN::Punctuator::Tag::R_CURLY_BRACKET}
            , {".", TOKEN::Punctuator::Tag::PERIOD}
            , {"->", TOKEN::Punctuator::Tag::ARROW}
            , {"++", TOKEN::Punctuator::Tag::INCREMENT}
            , {"--", TOKEN::Punctuator::Tag::DECREMENT}
            , {"&", TOKEN::Punctuator::Tag::BITAND}
            , {"*", TOKEN::Punctuator::Tag::ASTERISK}
            , {"+", TOKEN::Punctuator::Tag::PLUS}
            , {"-", TOKEN::Punctuator::Tag::MINUS}
            , {"~", TOKEN::Punctuator::Tag::COMPL}
            , {"!", TOKEN::Punctuator::Tag::NOT}
            , {"/", TOKEN::Punctuator::Tag::SLASH}
            , {"%", TOKEN::Punctuator::Tag::PERCENT}
            , {"<<", TOKEN::Punctuator::Tag::L_SHIFT}
            , {">>", TOKEN::Punctuator::Tag::R_SHIFT}
            , {"<", TOKEN::Punctuator::Tag::LESS}
            , {">", TOKEN::Punctuator::Tag::GREATER}
            , {"<=", TOKEN::Punctuator::Tag::LESS_EQUAL}
            , {">=", TOKEN::Punctuator::Tag::GREATER_EQUAL}
            , {"==", TOKEN::Punctuator::Tag::EQUAL}
            , {"!=", TOKEN::Punctuator::Tag::NOT_EQUAL}
            , {"^", TOKEN::Punctuator::Tag::XOR}
            , {"|", TOKEN::Punctuator::Tag::BITOR}
            , {"&&", TOKEN::Punctuator::Tag::AND}
            , {"||", TOKEN::Punctuator::Tag::OR}
            , {"\?", TOKEN::Punctuator::Tag::QUESTION}
            , {":", TOKEN::Punctuator::Tag::COLON}
            , {";", TOKEN::Punctuator::Tag::SEMICOLON}
            , {"...", TOKEN::Punctuator::Tag::TRIPLE_PERIOD}
            , {"=", TOKEN::Punctuator::Tag::ASSIGNMENT}
            , {"*=", TOKEN::Punctuator::Tag::ASTERISK_ASSIGNMENT}
            , {"/=", TOKEN::Punctuator::Tag::SLASH_ASSIGNMENT}
            , {"%=", TOKEN::Punctuator::Tag::PERCENT_ASSIGNMENT}
            , {"+=", TOKEN::Punctuator::Tag::PLUS_ASSIGNMENT}
            , {"-=", TOKEN::Punctuator::Tag::MINUS_ASSIGNMENT}
            , {"<<=", TOKEN::Punctuator::Tag::L_SHIFT_ASSIGNMENT}
            , {">>=", TOKEN::Punctuator::Tag::R_SHIFT_ASSIGNMENT}
            , {"&=", TOKEN::Punctuator::Tag::AND_ASSIGNMENT}
            , {"^=", TOKEN::Punctuator::Tag::XOR_ASSIGNMENT}
            , {"|=", TOKEN::Punctuator::Tag::BITOR_ASSIGNMENT}
            , {",", TOKEN::Punctuator::Tag::COMMA}
            , {"#", TOKEN::Punctuator::Tag::HASH}
            , {"##", TOKEN::Punctuator::Tag::DOUBLE_HASH}
            , {"<:", TOKEN::Punctuator::Tag::L_SQUARE_BRACKET}
            , {":>", TOKEN::Punctuator::Tag::R_SQUARE_BRACKET}
            , {"<%", TOKEN::Punctuator::Tag::L_CURLY_BRACKET}
            , {"%>", TOKEN::Punctuator::Tag::R_CURLY_BRACKET}
            , {"%:", TOKEN::Punctuator::Tag::HASH}
            , {"%:%:", TOKEN::Punctuator::Tag::DOUBLE_HASH}
            , {"@", TOKEN::Punctuator::Tag::AT}};
}

}

#endif