#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <unordered_map>
#include <variant>
#include <vector>
#include <utility>
#include <string>
#include <array>

namespace TOKEN
{

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
class Nondigit;
class UniversalCharacterName;
class DecimalConstant;
class IntegerSuffix;
class OctalConstant;
class HexadecimalConstant;
class DecimalFloatingConstant;
class HexadecimalFloatingConstant;
class CCharSequence;
class SChar;
class HexQuad;
class NonzeroDigit;
class OctalDigit;
class HexadecimalPrefix;
class HexadecimalDigit;
class FractionalConstant;
class ExponentPart;
class FloatingSuffix;
class DigitSequence;
class HexadecimalFractionalConstant;
class BinaryExponentPart;
class HexadecimalDigitSequence;
class Sign;
class CChar;
class EscapeSequence;
class SimpleEscapeSequence;
class OctalEscapeSequence;
class HexadecimalEscapeSequence;
class PreprocessingToken;
class PPNumber;
class UnsignedSuffix;
class LongSuffix;
class LongLongSuffix;
class TranslationUnit;
class ExternalDeclaration;
class FunctionDefinition;
class Declaration;
class DeclarationSpecifiers;
class Declarator;
class DeclarationList;
class CompoundStatement;
class InitDeclaratorList;
class StaticAssertDeclaration;
class StorageClassSpecifier;
class TypeSpecifier;
class TypeQualifier;
class FunctionSpecifier;
class AlignmentSpecifier;
class Pointer;
class DirectDeclarator;
class BlockItemList;
class InitDeclarator;
class ConstantExpression;
class AtomicTypeSpecifier;
class StructOrUnionSpecifier;
class EnumSpecifier;
class TypedefName;
class TypeName;
class TypeQualifierList;
class AssignmentExpression;
class ParameterTypeList;
class IdentifierList;
class BlockItem;
class Initializer;
class ConditionalExpression;
class StructOrUnion;
class StructDeclarationList;
class EnumeratorList;
class SpecifierQualifierList;
class AbstractDeclarator;
class UnaryExpression;
class AssignmentOperator;
class ParameterList;
class Statement;
class InitializerList;
class LogicalORExpression;
class Expression;
class StructDeclaration;
class Enumerator;
class DirectAbstractDeclarator;
class PostfixExpression;
class UnaryOperator;
class CastExpression;
class ParameterDeclaration;
class LabeledStatement;
class ExpressionStatement;
class SelectionStatement;
class IterationStatement;
class JumpStatement;
class Designation;
class LogicalANDExpression;
class StructDeclaratorList;
class PrimaryExpression;
class ArgumentExpressionList;
class DesignatorList;
class InclusiveORExpression;
class StructDeclarator;
class GenericSelection;
class Designator;
class ExclusiveORExpression;
class GenericAssocList;
class ANDExpression;
class GenericAssociation;
class EqualityExpression;
class RelationalExpression;
class ShiftExpression;
class AdditiveExpression;
class MultiplicativeExpression;

struct Token
{
    using Variant = std::variant<std::monostate
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

    Token *copy() const;
    std::string &str(std::string&, std::size_t&) const;
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

    Keyword *copy() const;
    std::string &str(std::string&, std::size_t&) const;

    static const std::unordered_map<Tag, std::string> KEYWORD_MAP;
};

struct Identifier
{
    using Variant = std::variant<std::monostate
        , IdentifierNondigit*
        , Digit*>;
    
    std::vector<Variant> seq;

    template<class... Args>
    Identifier(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~Identifier();

    Identifier *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct Constant
{
    using Variant = std::variant<std::monostate
        , IntegerConstant*
        , FloatingConstant*
        , EnumerationConstant*
        , CharacterConstant*>;
    
    Variant var;

    template<class... Args>
    Constant(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~Constant();

    Constant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
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

    StringLiteral *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct Punctuator
{
    enum class Tag : signed char
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

    Punctuator *copy() const;
    std::string &str(std::string&, std::size_t&) const;

    static const std::unordered_map<Tag, std::string> PUNCTUATOR_MAP;
};

struct IdentifierNondigit
{
    using Variant = std::variant<std::monostate
        , Nondigit*
        , UniversalCharacterName*>;
    
    Variant var;

    template<class... Args>
    IdentifierNondigit(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~IdentifierNondigit();

    IdentifierNondigit *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct Digit
{
    char c;

    constexpr Digit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~Digit() = default;

    Digit *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct IntegerConstant
{
    struct Sdc_is
    {
        DecimalConstant *dc;
        IntegerSuffix *is;
        constexpr Sdc_is(DecimalConstant *indc = nullptr
            , IntegerSuffix *inis = nullptr) noexcept
            : dc(indc)
            , is(inis){}
    };
    struct Soc_is
    {
        OctalConstant *oc;
        IntegerSuffix *is;
        constexpr Soc_is(OctalConstant *inoc = nullptr
            , IntegerSuffix *inis = nullptr) noexcept
            : oc(inoc)
            , is(inis){}
    };
    struct Shc_is
    {
        HexadecimalConstant *hc;
        IntegerSuffix *is;
        constexpr Shc_is(HexadecimalConstant *inhc = nullptr
            , IntegerSuffix *inis = nullptr) noexcept
            : hc(inhc)
            , is(inis){}
    };

    using Variant = std::variant<std::monostate
        , Sdc_is
        , Soc_is
        , Shc_is>;
    
    Variant var;

    template<class... Args>
    IntegerConstant(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~IntegerConstant();

    IntegerConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct FloatingConstant
{
    using Variant = std::variant<std::monostate
        , DecimalFloatingConstant*
        , HexadecimalFloatingConstant*>;
    
    Variant var;

    template<class... Args>
    FloatingConstant(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~FloatingConstant();

    FloatingConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct EnumerationConstant
{
    Identifier *i;

    constexpr EnumerationConstant(Identifier *ini = nullptr) noexcept
        : i(ini){}
    ~EnumerationConstant();

    EnumerationConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct CharacterConstant
{
    enum class Tag : signed char
    {
        NONE
        , L
        , u
        , U
    };

    Tag tag;
    CCharSequence *ccs;
    
    constexpr CharacterConstant(Tag intag = Tag::NONE
        , CCharSequence *inccs = nullptr) noexcept
        : tag(intag)
        , ccs(inccs){}
    ~CharacterConstant();

    CharacterConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct EncodingPrefix
{
    enum class Tag : signed char
    {
        NONE
        , u8
        , u
        , U
        , L
    };

    Tag tag;

    constexpr EncodingPrefix(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~EncodingPrefix() = default;

    EncodingPrefix *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct SCharSequence
{
    std::vector<SChar*> seq;

    template<class... Args>
    SCharSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~SCharSequence();

    SCharSequence *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct Nondigit
{
    char c;

    constexpr Nondigit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~Nondigit() = default;

    Nondigit *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct UniversalCharacterName
{
    struct Su_hq
    {
        HexQuad *hq;
        constexpr Su_hq(HexQuad *inhq = nullptr) noexcept
            : hq(inhq){}
    };
    struct SU_hq_hq
    {
        HexQuad *hq0;
        HexQuad *hq1;
        constexpr SU_hq_hq(HexQuad *inhq0 = nullptr
            , HexQuad *inhq1 = nullptr) noexcept
            : hq0(inhq0)
            , hq1(inhq1){}
    };

    using Variant = std::variant<std::monostate
        , Su_hq
        , SU_hq_hq>;
    
    Variant var;

    template<class... Args>
    UniversalCharacterName(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~UniversalCharacterName();

    UniversalCharacterName *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct DecimalConstant
{
    NonzeroDigit *nd;
    std::vector<Digit*> seq;

    template<class Seq>
    DecimalConstant(NonzeroDigit *innd
        , Seq &&inseq)
        : nd(innd)
        , seq(std::forward<Seq>(inseq)){}
    ~DecimalConstant();

    DecimalConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct OctalConstant
{
    std::vector<OctalDigit*> seq;
    
    template<class Seq>
    OctalConstant(Seq &&inseq)
        : seq(std::forward<Seq>(inseq)){}
    ~OctalConstant();

    OctalConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct HexadecimalConstant
{
    HexadecimalPrefix *hp;
    std::vector<HexadecimalDigit*> seq;

    template<class Seq>
    HexadecimalConstant(HexadecimalPrefix *inhp
        , Seq &&inseq)
        : hp(inhp)
        , seq(std::forward<Seq>(inseq)){}
    ~HexadecimalConstant();

    HexadecimalConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct DecimalFloatingConstant
{
    struct Sfc_ep_fs
    {
        FractionalConstant *fc;
        ExponentPart *ep;
        FloatingSuffix *fs;
        constexpr Sfc_ep_fs(FractionalConstant *infc = nullptr
            , ExponentPart *inep = nullptr
            , FloatingSuffix *infs = nullptr) noexcept
            : fc(infc)
            , ep(inep)
            , fs(infs){}
    };
    struct Sds_ep_fs
    {
        DigitSequence *ds;
        ExponentPart *ep;
        FloatingSuffix *fs;
        constexpr Sds_ep_fs(DigitSequence *inds = nullptr
            , ExponentPart *inep = nullptr
            , FloatingSuffix *infs = nullptr) noexcept
            : ds(inds)
            , ep(inep)
            , fs(infs){}
    };

    using Variant = std::variant<std::monostate
        , Sfc_ep_fs
        , Sds_ep_fs>;

    Variant var;

    template<class... Args>
    DecimalFloatingConstant(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~DecimalFloatingConstant();

    DecimalFloatingConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct HexadecimalFloatingConstant
{
    struct Shp_hfc_bep_fs
    {
        HexadecimalPrefix *hp;
        HexadecimalFractionalConstant *hfc;
        BinaryExponentPart *bep;
        FloatingSuffix *fs;
        constexpr Shp_hfc_bep_fs(HexadecimalPrefix *inhp = nullptr
            , HexadecimalFractionalConstant *inhfc = nullptr
            , BinaryExponentPart *inbep = nullptr
            , FloatingSuffix *infs = nullptr) noexcept
            : hp(inhp)
            , hfc(inhfc)
            , bep(inbep)
            , fs(infs){}
    };
    struct Shp_hds_bep_fs
    {
        HexadecimalPrefix *hp;
        HexadecimalDigitSequence *hds;
        BinaryExponentPart *bep;
        FloatingSuffix *fs;
        constexpr Shp_hds_bep_fs(HexadecimalPrefix *inhp = nullptr
            , HexadecimalDigitSequence *inhds = nullptr
            , BinaryExponentPart *inbep = nullptr
            , FloatingSuffix *infs = nullptr) noexcept
            : hp(inhp)
            , hds(inhds)
            , bep(inbep)
            , fs(infs){}
    };

    using Variant = std::variant<std::monostate
        , Shp_hfc_bep_fs
        , Shp_hds_bep_fs>;

    Variant var;

    template<class... Args>
    HexadecimalFloatingConstant(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~HexadecimalFloatingConstant();

    HexadecimalFloatingConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct CCharSequence
{
    std::vector<CChar*> seq;

    template<class... Args>
    CCharSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~CCharSequence();

    CCharSequence *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct SChar
{
    using Variant = std::variant<std::monostate
        , char
        , EscapeSequence*>;

    Variant var;

    template<class... Args>
    SChar(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~SChar();

    SChar *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct HexQuad
{
    std::array<HexadecimalDigit*, 4> arr;

    template<class... Args>
    HexQuad(Args&&... args)
        : arr(std::forward<Args>(args)...){}
    ~HexQuad();

    HexQuad *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct NonzeroDigit
{
    char c;

    constexpr NonzeroDigit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~NonzeroDigit() = default;

    NonzeroDigit *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct OctalDigit
{
    char c;

    constexpr OctalDigit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~OctalDigit() = default;

    OctalDigit *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct HexadecimalPrefix
{
    enum class Tag : signed char
    {
        NONE
        , x
        , X
    };

    Tag tag;

    constexpr HexadecimalPrefix(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~HexadecimalPrefix() = default;

    HexadecimalPrefix *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct HexadecimalDigit
{
    char c;

    constexpr HexadecimalDigit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~HexadecimalDigit() = default;

    HexadecimalDigit *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct FractionalConstant
{
    struct Sds_ds
    {
        DigitSequence *ds0;
        DigitSequence *ds1;
        constexpr Sds_ds(DigitSequence *inds0 = nullptr
            , DigitSequence *inds1 = nullptr) noexcept
            : ds0(inds0)
            , ds1(inds1){}
    };
    struct Sds
    {
        DigitSequence *ds;
        constexpr Sds(DigitSequence *inds = nullptr) noexcept
            : ds(inds){}
    };

    using Variant = std::variant<std::monostate
        , Sds_ds
        , Sds>;
    
    Variant var;

    template<class... Args>
    FractionalConstant(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~FractionalConstant();

    FractionalConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct ExponentPart
{
    Sign *s;
    DigitSequence *ds;

    constexpr ExponentPart(Sign *ins = nullptr
        , DigitSequence *inds = nullptr) noexcept
        : s(ins)
        , ds(inds){}
    ~ExponentPart();

    ExponentPart *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct Sign
{
    enum class Tag : signed char
    {
        NONE
        , PLUS
        , MINUS
    };

    Tag tag;

    constexpr Sign(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~Sign() = default;

    Sign *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct DigitSequence
{
    std::vector<Digit*> seq;

    template<class... Args>
    DigitSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~DigitSequence();

    DigitSequence *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct HexadecimalFractionalConstant
{
    struct Shds_hds
    {
        HexadecimalDigitSequence *hds0;
        HexadecimalDigitSequence *hds1;
        constexpr Shds_hds(HexadecimalDigitSequence *inhds0 = nullptr
            , HexadecimalDigitSequence *inhds1 = nullptr) noexcept
            : hds0(inhds0)
            , hds1(inhds1){}
    };
    struct Shds
    {
        HexadecimalDigitSequence *hds;
        constexpr Shds(HexadecimalDigitSequence *inhds = nullptr) noexcept
            : hds(inhds){}
    };

    using Variant = std::variant<std::monostate
        , Shds_hds
        , Shds>;

    Variant var;

    template<class... Args>
    HexadecimalFractionalConstant(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~HexadecimalFractionalConstant();

    HexadecimalFractionalConstant *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct BinaryExponentPart
{
    Sign *s;
    DigitSequence *ds;

    constexpr BinaryExponentPart(Sign *ins = nullptr
        , DigitSequence *inds = nullptr) noexcept
        : s(ins)
        , ds(inds){}
    ~BinaryExponentPart();

    BinaryExponentPart *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct HexadecimalDigitSequence
{
    std::vector<HexadecimalDigit*> seq;

    template<class... Args>
    HexadecimalDigitSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~HexadecimalDigitSequence();

    HexadecimalDigitSequence *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct FloatingSuffix
{
    enum class Tag : signed char
    {
        NONE
        , f
        , l
        , F
        , L
    };

    Tag tag;

    constexpr FloatingSuffix(Tag intag = Tag::NONE)
        : tag(intag){}
    ~FloatingSuffix() = default;

    FloatingSuffix *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct CChar
{
    using Variant = std::variant<std::monostate
        , char
        , EscapeSequence*>;

    Variant var;

    template<class... Args>
    CChar(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~CChar();

    CChar *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct EscapeSequence
{
    using Variant = std::variant<std::monostate
        , SimpleEscapeSequence*
        , OctalEscapeSequence*
        , HexadecimalEscapeSequence*
        , UniversalCharacterName*>;

    Variant var;

    template<class... Args>
    EscapeSequence(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~EscapeSequence();

    EscapeSequence *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct SimpleEscapeSequence
{
    char c;
    
    constexpr SimpleEscapeSequence(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~SimpleEscapeSequence() = default;

    SimpleEscapeSequence *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct OctalEscapeSequence
{
    std::vector<OctalDigit*> seq;

    template<class... Args>
    OctalEscapeSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~OctalEscapeSequence();

    OctalEscapeSequence *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct HexadecimalEscapeSequence
{
    std::vector<HexadecimalDigit*> seq;
    
    template<class... Args>
    HexadecimalEscapeSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~HexadecimalEscapeSequence();

    HexadecimalEscapeSequence *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct PreprocessingToken
{
    using Variant = std::variant<std::monostate
        , Identifier*
        , PPNumber*
        , CharacterConstant*
        , StringLiteral*
        , Punctuator*>;
    
    Variant var;

    template<class... Args>
    PreprocessingToken(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~PreprocessingToken();

    PreprocessingToken *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct PPNumber
{
    enum class Tag : signed char
    {
        NONE
        , PERIOD
        , e
        , E
        , p
        , P
    };
    using Variant = std::variant<std::monostate
        , Digit*
        , Tag
        , IdentifierNondigit*
        , Sign*>;
    
    std::vector<Variant> seq;

    template<class... Args>
    PPNumber(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~PPNumber();

    PPNumber *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct IntegerSuffix
{
    struct Sus_ls
    {
        UnsignedSuffix *us;
        LongSuffix *ls;
        constexpr Sus_ls(UnsignedSuffix *inus = nullptr
            , LongSuffix *inls = nullptr) noexcept
            : us(inus)
            , ls(inls){}
    };
    struct Sus_lls
    {
        UnsignedSuffix *us;
        LongLongSuffix *lls;
        constexpr Sus_lls(UnsignedSuffix *inus = nullptr
            , LongLongSuffix *inlls = nullptr) noexcept
            : us(inus)
            , lls(inlls){}
    };
    struct Sls_us
    {
        LongSuffix *ls;
        UnsignedSuffix *us;
        constexpr Sls_us(LongSuffix *inls = nullptr
            , UnsignedSuffix *inus = nullptr) noexcept
            : ls(inls)
            , us(inus){}
    };
    struct Slls_us
    {
        LongLongSuffix *lls;
        UnsignedSuffix *us;
        constexpr Slls_us(LongLongSuffix *inlls = nullptr
            , UnsignedSuffix *inus = nullptr) noexcept
            : lls(inlls)
            , us(inus){}
    };

    using Variant = std::variant<std::monostate
        , Sus_ls
        , Sus_lls
        , Sls_us
        , Slls_us>;

    Variant var;

    template<class... Args>
    IntegerSuffix(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~IntegerSuffix();

    IntegerSuffix *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct UnsignedSuffix
{
    enum class Tag : signed char
    {
        NONE
        , u
        , U
    };

    Tag tag;

    constexpr UnsignedSuffix(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~UnsignedSuffix() = default;

    UnsignedSuffix *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct LongSuffix
{
    enum class Tag : signed char
    {
        NONE
        , l
        , L
    };

    Tag tag;

    constexpr LongSuffix(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~LongSuffix() = default;

    LongSuffix *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct LongLongSuffix
{
    enum class Tag : signed char
    {
        NONE
        , ll
        , LL
    };

    Tag tag;

    constexpr LongLongSuffix(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~LongLongSuffix() = default;

    LongLongSuffix *copy() const;
    std::string &str(std::string&, std::size_t&) const;
};

struct TranslationUnit
{
    std::vector<ExternalDeclaration*> seq;

    template<class ...Args>
    TranslationUnit(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~TranslationUnit();
};

struct ExternalDeclaration
{
    using Var = std::variant<std::monostate
        , FunctionDefinition*
        , Declaration*>;
    
    Var var;
    
    template<class ...Args>
    ExternalDeclaration(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~ExternalDeclaration();
};

struct FunctionDefinition
{
    DeclarationSpecifiers *ds;
    Declarator *d;
    DeclarationList *dl;
    CompoundStatement *cs;

    constexpr FunctionDefinition(DeclarationSpecifiers *inds = nullptr
        , Declarator *ind = nullptr
        , DeclarationList *indl = nullptr
        , CompoundStatement *incs = nullptr) noexcept
        : ds(inds)
        , d(ind)
        , dl(indl)
        , cs(incs){}
    ~FunctionDefinition();
};

struct Declaration
{
    struct Sds_idl
    {
        DeclarationSpecifiers *ds;
        InitDeclaratorList *idl;
        constexpr Sds_idl(DeclarationSpecifiers *inds = nullptr
            , InitDeclaratorList *inidl = nullptr) noexcept
            : ds(inds)
            , idl(inidl){}
    };
    struct Ssad
    {
        StaticAssertDeclaration *sad;
        constexpr Ssad(StaticAssertDeclaration *insad = nullptr) noexcept
            : sad(insad){}
    };

    using Var = std::variant<std::monostate
        , Sds_idl
        , Ssad>;

    Var var;
    
    template<class ...Args>
    Declaration(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~Declaration();
};

struct DeclarationSpecifiers
{
    using Var = std::variant<std::monostate
        , StorageClassSpecifier*
        , TypeSpecifier*
        , TypeQualifier*
        , FunctionSpecifier*
        , AlignmentSpecifier*>;
    
    std::vector<Var> seq;

    template<class ...Args>
    DeclarationSpecifiers(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~DeclarationSpecifiers();
};

struct Declarator
{
    Pointer *p;
    DirectDeclarator *dd;

    constexpr Declarator(Pointer *inp = nullptr
        , DirectDeclarator *indd = nullptr) noexcept
        : p(inp)
        , dd(indd){}
    ~Declarator();
};

struct DeclarationList
{
    std::vector<Declaration*> seq;

    template<class ...Args>
    DeclarationList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~DeclarationList();
};

struct CompoundStatement
{
    BlockItemList *bil;

    CompoundStatement(BlockItemList *inbil = nullptr) noexcept
        : bil(inbil){}
    ~CompoundStatement();
};

struct InitDeclaratorList
{
    std::vector<InitDeclarator*> seq;

    template<class ...Args>
    InitDeclaratorList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~InitDeclaratorList();
};

struct StaticAssertDeclaration
{
    ConstantExpression *ce;
    StringLiteral *sl;

    constexpr StaticAssertDeclaration(ConstantExpression *ince = nullptr
        , StringLiteral *insl = nullptr) noexcept
        : ce(ince)
        , sl(insl){}
    ~StaticAssertDeclaration();
};

struct StorageClassSpecifier
{
    enum class Tag : signed char
    {
        NONE
        , TYPEDEF
        , EXTERN
        , STATIC
        , THREAD_LOCAL
        , AUTO
        , REGISTER
    };

    Tag tag;

    constexpr StorageClassSpecifier(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~StorageClassSpecifier() = default;
};

struct TypeSpecifier
{
    enum class Tag : signed char
    {
        NONE
        , VOID
        , CHAR
        , SHORT
        , INT
        , LONG
        , FLOAT
        , DOUBLE
        , SIGNED
        , UNSIGNED
        , BOOL
        , COMPLEX
    };

    using Var = std::variant<std::monostate
        , Tag
        , AtomicTypeSpecifier*
        , StructOrUnionSpecifier*
        , EnumSpecifier*
        , TypedefName*>;

    Var var;

    template<class ...Args>
    TypeSpecifier(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~TypeSpecifier();
};

struct TypeQualifier
{
    enum class Tag : signed char
    {
        NONE
        , CONST
        , RESTRICT
        , VOLATILE
        , ATOMIC
    };

    Tag tag;

    constexpr TypeQualifier(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~TypeQualifier() = default;
};

struct FunctionSpecifier
{
    enum class Tag : signed char
    {
        NONE
        , INLINE
        , NORETURN
    };

    Tag tag;

    constexpr FunctionSpecifier(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~FunctionSpecifier() = default;
};

struct AlignmentSpecifier
{
    using Var = std::variant<std::monostate
        , TypeName*
        , ConstantExpression*>;

    Var var;

    template<class ...Args>
    AlignmentSpecifier(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~AlignmentSpecifier();
};

struct Pointer
{
    struct Stql
    {
        TypeQualifierList *tql;
        constexpr Stql(TypeQualifierList *intql = nullptr) noexcept
            : tql(intql){}
    };
    struct Stql_p
    {
        TypeQualifierList *tql;
        Pointer *p;
        constexpr Stql_p(TypeQualifierList *intql = nullptr
            , Pointer *inp = nullptr) noexcept
            : tql(intql)
            , p(inp){}
    };

    using Var = std::variant<std::monostate
        , Stql
        , Stql_p>;

    Var var;

    template<class ...Args>
    Pointer(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~Pointer();
};

struct DirectDeclarator
{
    struct Si
    {
        Identifier *i;
        constexpr Si(Identifier *ini = nullptr) noexcept
            : i(ini){}
    };
    struct Sd
    {
        Declarator *d;
        constexpr Sd(Declarator *ind = nullptr) noexcept
            : d(ind){}
    };
    struct Stql_ae
    {
        TypeQualifierList *tql;
        AssignmentExpression *ae;
        bool hasStatic;
        constexpr Stql_ae(TypeQualifierList *intql = nullptr
            , AssignmentExpression *inae = nullptr
            , bool inHasStatic = false) noexcept
            : tql(intql)
            , ae(inae)
            , hasStatic(inHasStatic){}
    };
    struct Stql
    {
        TypeQualifierList *tql;
        constexpr Stql(TypeQualifierList *intql = nullptr) noexcept
            : tql(intql){}
    };
    struct Sptl
    {
        ParameterTypeList *ptl;
        constexpr Sptl(ParameterTypeList *inptl = nullptr) noexcept
            : ptl(inptl){}
    };
    struct Sil
    {
        IdentifierList *il;
        constexpr Sil(IdentifierList *inil = nullptr) noexcept
            : il(inil){}
    };

    using Var = std::variant<std::monostate
        , Si
        , Sd
        , Stql_ae
        , Stql
        , Sptl
        , Sil>;

    std::vector<Var> seq;

    template<class ...Args>
    DirectDeclarator(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~DirectDeclarator();
};

struct BlockItemList
{
    std::vector<BlockItem*> seq;

    template<class ...Args>
    BlockItemList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~BlockItemList();
};

struct InitDeclarator
{
    struct Sd
    {
        Declarator *d;
        constexpr Sd(Declarator *ind = nullptr) noexcept
            : d(ind){}
    };
    struct Sd_i
    {
        Declarator *d;
        Initializer *i;
        constexpr Sd_i(Declarator *ind = nullptr
            , Initializer *ini = nullptr) noexcept
            : d(ind)
            , i(ini){}
    };

    using Var = std::variant<std::monostate
        , Sd
        , Sd_i>;

    Var var;

    template<class ...Args>
    InitDeclarator(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~InitDeclarator();
};

struct ConstantExpression
{
    ConditionalExpression *ce;

    constexpr ConstantExpression(ConditionalExpression *ince = nullptr) noexcept
        : ce(ince){}
    ~ConstantExpression();
};

struct AtomicTypeSpecifier
{
    TypeName *tn;

    constexpr AtomicTypeSpecifier(TypeName *intn = nullptr) noexcept
        : tn(intn){}
    ~AtomicTypeSpecifier();
};

struct StructOrUnionSpecifier
{
    struct Ssou_i_sdl
    {
        StructOrUnion *sou;
        Identifier *i;
        StructDeclarationList *sdl;
        constexpr Ssou_i_sdl(StructOrUnion *insou = nullptr
            , Identifier *ini = nullptr
            , StructDeclarationList *insdl = nullptr) noexcept
            : sou(insou)
            , i(ini)
            , sdl(insdl){}
    };
    struct Ssou_i
    {
        StructOrUnion *sou;
        Identifier *i;
        constexpr Ssou_i(StructOrUnion *insou = nullptr
            , Identifier *ini = nullptr) noexcept
            : sou(insou)
            , i(ini){}
    };

    using Var = std::variant<std::monostate
        , Ssou_i_sdl
        , Ssou_i>;

    Var var;

    template<class ...Args>
    StructOrUnionSpecifier(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~StructOrUnionSpecifier();
};

struct EnumSpecifier
{
    struct Si_el
    {
        Identifier *i;
        EnumeratorList *el;
        constexpr Si_el(Identifier *ini = nullptr
            , EnumeratorList *inel = nullptr) noexcept
            : i(ini)
            , el(inel){}
    };
    struct Si
    {
        Identifier *i;
        constexpr Si(Identifier *ini = nullptr) noexcept
            : i(ini){}
    };

    using Var = std::variant<std::monostate
        , Si_el
        , Si>;
    
    Var var;

    template<class ...Args>
    EnumSpecifier(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~EnumSpecifier();
};

struct TypedefName
{
    Identifier *i;

    constexpr TypedefName(Identifier *ini = nullptr) noexcept
        : i(ini){}
    ~TypedefName();
};

struct TypeName
{
    SpecifierQualifierList *sql;
    AbstractDeclarator *ad;

    constexpr TypeName(SpecifierQualifierList *insql = nullptr
        , AbstractDeclarator *inad = nullptr) noexcept
        : sql(insql)
        , ad(inad){}
    ~TypeName();
};

struct TypeQualifierList
{
    std::vector<TypeQualifier*> seq;

    template<class ...Args>
    TypeQualifierList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~TypeQualifierList();
};

struct AssignmentExpression
{
    struct Sce
    {
        ConditionalExpression *ce;
        constexpr Sce(ConditionalExpression *ince = nullptr) noexcept
            : ce(ince){}
    };
    struct Sue_ao_ae
    {
        UnaryExpression *ue;
        AssignmentOperator *ao;
        AssignmentExpression *ae;
        constexpr Sue_ao_ae(UnaryExpression *inue = nullptr
            , AssignmentOperator *inao = nullptr
            , AssignmentExpression *inae = nullptr) noexcept
            : ue(inue)
            , ao(inao)
            , ae(inae){}
    };
    
    using Var = std::variant<std::monostate
        , Sce
        , Sue_ao_ae>;
    
    Var var;

    template<class ...Args>
    AssignmentExpression(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~AssignmentExpression();
};

struct ParameterTypeList
{
    ParameterList *pl;
    bool isValiable;

    constexpr ParameterTypeList(ParameterList *inpl = nullptr
        , bool inIsValiable = false) noexcept
        : pl(inpl)
        , isValiable(inIsValiable){}
    ~ParameterTypeList();
};

struct IdentifierList
{
    std::vector<Identifier*> seq;

    template<class ...Args>
    IdentifierList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~IdentifierList();
};

struct BlockItem
{
    using Var = std::variant<std::monostate
        , Declaration*
        , Statement*>;

    Var var;

    template<class ...Args>
    BlockItem(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~BlockItem();
};

struct Initializer
{
    using Var = std::variant<std::monostate
        , AssignmentExpression*
        , InitializerList*>;
    
    Var var;

    template<class ...Args>
    Initializer(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~Initializer();
};

struct ConditionalExpression
{
    struct Slore
    {
        LogicalORExpression *lore;
        constexpr Slore(LogicalORExpression *inlore = nullptr) noexcept
            : lore(inlore){}
    };
    struct Slore_e_ce
    {
        LogicalORExpression *lore;
        Expression *e;
        ConditionalExpression *ce;
        constexpr Slore_e_ce(LogicalORExpression *inlore = nullptr
            , Expression *ine = nullptr
            , ConditionalExpression *ince = nullptr) noexcept
            : lore(inlore)
            , e(ine)
            , ce(ince){}
    };

    using Var = std::variant<std::monostate
        , Slore
        , Slore_e_ce>;

    Var var;

    template<class ...Args>
    ConditionalExpression(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~ConditionalExpression();
};

struct StructOrUnion
{
    enum class Tag : signed char
    {
        NONE
        , STRUCT
        , UNION
    };

    Tag tag;

    constexpr StructOrUnion(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~StructOrUnion() = default;
};

struct StructDeclarationList
{
    std::vector<StructDeclaration*> seq;

    template<class ...Args>
    StructDeclarationList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~StructDeclarationList();
};

struct EnumeratorList
{
    std::vector<Enumerator*> seq;

    template<class ...Args>
    EnumeratorList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~EnumeratorList();
};

struct SpecifierQualifierList
{
    using Var = std::variant<std::monostate
        , TypeSpecifier*
        , TypeQualifier*>;

    std::vector<Var> seq;

    template<class ...Args>
    SpecifierQualifierList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~SpecifierQualifierList();
};

struct AbstractDeclarator
{
    struct Sp
    {
        Pointer *p;
        constexpr Sp(Pointer *inp = nullptr) noexcept
            : p(inp){}
    };
    struct Sp_dad
    {
        Pointer *p;
        DirectAbstractDeclarator *dad;
        constexpr Sp_dad(Pointer *inp = nullptr
            , DirectAbstractDeclarator *indad = nullptr) noexcept
            : p(inp)
            , dad(indad){}
    };

    using Var = std::variant<std::monostate
        , Sp
        , Sp_dad>;
    
    Var var;

    template<class ...Args>
    AbstractDeclarator(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~AbstractDeclarator();
};

struct UnaryExpression
{
    struct Spe
    {
        PostfixExpression *pe;
        constexpr Spe(PostfixExpression *inpe = nullptr) noexcept
            : pe(inpe){}
    };
    struct Si_ue
    {
        UnaryExpression *ue;
        constexpr Si_ue(UnaryExpression *inue = nullptr) noexcept
            : ue(inue){}
    };
    struct Sd_ue
    {
        UnaryExpression *ue;
        constexpr Sd_ue(UnaryExpression *inue = nullptr) noexcept
            : ue(inue){}
    };
    struct Suo_ce
    {
        UnaryOperator *uo;
        CastExpression *ce;
        constexpr Suo_ce(UnaryOperator *inuo = nullptr
            , CastExpression *ince = nullptr) noexcept
            : uo(inuo)
            , ce(ince){}
    };
    struct Ss_ue
    {
        UnaryExpression *ue;
        constexpr Ss_ue(UnaryExpression *inue = nullptr) noexcept
            : ue(inue){}
    };
    struct Ss_tn
    {
        TypeName *tn;
        constexpr Ss_tn(TypeName *intn = nullptr) noexcept
            : tn(intn){}
    };
    struct Sa_tn
    {
        TypeName *tn;
        constexpr Sa_tn(TypeName *intn = nullptr) noexcept
            : tn(intn){}
    };

    using Var = std::variant<std::monostate
        , Spe
        , Si_ue
        , Sd_ue
        , Suo_ce
        , Ss_ue
        , Ss_tn
        , Sa_tn>;

    Var var;

    template<class ...Args>
    UnaryExpression(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~UnaryExpression();
};

struct AssignmentOperator
{
    enum class Tag : signed char
    {
        NONE
        , ASSIGNMENT
        , MULTIPLICATION
        , DIVISION
        , REMAINDER
        , ADDITION
        , SUBSTRACTION
        , LEFT_SHIFT
        , RIGHT_SHIFT
        , AND
        , XOR
        , OR
    };

    Tag tag;

    constexpr AssignmentOperator(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~AssignmentOperator() = default;
};

struct ParameterList
{
    std::vector<ParameterDeclaration*> seq;

    template<class ...Args>
    ParameterList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~ParameterList();
};

struct Statement
{
    using Var = std::variant<std::monostate
        , LabeledStatement*
        , CompoundStatement*
        , ExpressionStatement*
        , SelectionStatement*
        , IterationStatement*
        , JumpStatement*>;

    Var var;

    template<class ...Args>
    Statement(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~Statement();
};

struct InitializerList
{
    struct Sd_i
    {
        Designation *d;
        Initializer *i;
        constexpr Sd_i(Designation *ind = nullptr
            , Initializer *ini = nullptr) noexcept
            : d(ind)
            , i(ini){}
    };

    std::vector<Sd_i> seq;

    template<class ...Args>
    InitializerList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~InitializerList();
};

struct LogicalORExpression
{
    std::vector<LogicalANDExpression*> seq;

    template<class ...Args>
    LogicalORExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~LogicalORExpression();
};

struct Expression
{
    std::vector<AssignmentExpression*> seq;

    template<class ...Args>
    Expression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~Expression();
};

struct StructDeclaration
{
    struct Ssql_sdl
    {
        SpecifierQualifierList *sql;
        StructDeclaratorList *sdl;
        constexpr Ssql_sdl(SpecifierQualifierList *insql = nullptr
            , StructDeclaratorList *insdl = nullptr) noexcept
            : sql(insql)
            , sdl(insdl){}
    };
    struct Ssad
    {
        StaticAssertDeclaration *sad;
        constexpr Ssad(StaticAssertDeclaration *insad) noexcept
            : sad(insad){}
    };

    using Var = std::variant<std::monostate
        , Ssql_sdl
        , Ssad>;

    Var var;

    template<class ...Args>
    StructDeclaration(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~StructDeclaration();
};

struct Enumerator
{
    struct Sec
    {
        EnumerationConstant *ec;
        constexpr Sec(EnumerationConstant *inec = nullptr) noexcept
            : ec(inec){}
    };
    struct Sec_ce
    {
        EnumerationConstant *ec;
        ConstantExpression *ce;
        constexpr Sec_ce(EnumerationConstant *inec = nullptr
            , ConstantExpression *ince = nullptr) noexcept
            : ec(inec)
            , ce(ince){}
    };

    using Var = std::variant<std::monostate
        , Sec
        , Sec_ce>;

    Var var;

    template<class ...Args>
    Enumerator(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~Enumerator();
};

struct DirectAbstractDeclarator
{
    struct Sad
    {
        AbstractDeclarator *ad;
        constexpr Sad(AbstractDeclarator *inad = nullptr) noexcept
            : ad(inad){}
    };
    struct Stql_ae
    {
        TypeQualifierList *tql;
        AssignmentExpression *ae;
        bool hasStatic;
        constexpr Stql_ae(TypeQualifierList *intql = nullptr
            , AssignmentExpression *inae = nullptr
            , bool inHasStatic = false) noexcept
            : tql(intql)
            , ae(inae)
            ,hasStatic(inHasStatic){}
    };
    struct Sp
    {
        constexpr Sp() noexcept{}
    };
    struct Sptl
    {
        ParameterTypeList *ptl;
        constexpr Sptl(ParameterTypeList *inptl = nullptr) noexcept
            : ptl(inptl){}
    };

    using Var = std::variant<std::monostate
        , Sad
        , Stql_ae
        , Sp
        , Sptl>;

    std::vector<Var> seq;

    template<class ...Args>
    DirectAbstractDeclarator(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~DirectAbstractDeclarator();
};

struct PostfixExpression
{
    struct Spe
    {
        PrimaryExpression *pe;
        constexpr Spe(PrimaryExpression *inpe = nullptr) noexcept
            : pe(inpe){}
    };
    struct Se
    {
        Expression *e;
        constexpr Se(Expression *ine = nullptr) noexcept
            : e(ine){}
    };
    struct Sael
    {
        ArgumentExpressionList *ael;
        constexpr Sael(ArgumentExpressionList *inael = nullptr) noexcept
            : ael(inael){}
    };
    struct Sp_i
    {
        Identifier *i;
        constexpr Sp_i(Identifier *ini = nullptr) noexcept
            : i(ini){}
    };
    struct Sa_i
    {
        Identifier *i;
        constexpr Sa_i(Identifier *ini = nullptr) noexcept
            : i(ini){}
    };
    struct Si
    {
        constexpr Si() noexcept{}
    };
    struct Sd
    {
        constexpr Sd() noexcept{}
    };
    struct Stn_il
    {
        TypeName *tn;
        IdentifierList *il;
        constexpr Stn_il(TypeName *intn = nullptr
            , IdentifierList *inil = nullptr) noexcept
            : tn(intn)
            , il(inil){}
    };

    using Var = std::variant<std::monostate
        , Spe
        , Se
        , Sael
        , Sp_i
        , Sa_i
        , Si
        , Sd
        , Stn_il>;
    
    std::vector<Var> seq;

    template<class ...Args>
    PostfixExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~PostfixExpression();
};

struct UnaryOperator
{
    enum class Tag : signed char
    {
        NONE
        , ADDRESS
        , POINTER
        , PLUS
        , MINUS
        , COMPLEMENT
        , NOT
    };

    Tag tag;

    constexpr UnaryOperator(Tag intag = Tag::NONE) noexcept
        : tag(intag){}
    ~UnaryOperator() = default;
};

struct CastExpression
{
    struct Sue
    {
        UnaryExpression *ue;
        constexpr Sue(UnaryExpression *inue = nullptr) noexcept
            : ue(inue){}
    };
    struct Stn_ce
    {
        TypeName *tn;
        CastExpression *ce;
        constexpr Stn_ce(TypeName *intn = nullptr
            , CastExpression *ince = nullptr) noexcept
            : tn(intn)
            , ce(ince){}
    };

    using Var = std::variant<std::monostate
        , Sue
        , Stn_ce>;

    Var var;

    template<class ...Args>
    CastExpression(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~CastExpression();
};

struct ParameterDeclaration
{
    struct Sds_d
    {
        DeclarationSpecifiers *ds;
        Declarator *d;
        constexpr Sds_d(DeclarationSpecifiers *inds = nullptr
            , Declarator *ind = nullptr) noexcept
            : ds(inds)
            , d(ind){}
    };
    struct Sds_ad
    {
        DeclarationSpecifiers *ds;
        AbstractDeclarator *ad;
        constexpr Sds_ad(DeclarationSpecifiers *inds = nullptr
            , AbstractDeclarator *inad = nullptr) noexcept
            : ds(inds)
            , ad(inad){}
    };

    using Var = std::variant<std::monostate
        , Sds_d
        , Sds_ad>;

    Var var;

    template<class ...Args>
    ParameterDeclaration(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~ParameterDeclaration();
};

struct LabeledStatement
{
    struct Si_s
    {
        Identifier *i;
        Statement *s;
        constexpr Si_s(Identifier *ini = nullptr
            , Statement *ins = nullptr) noexcept
            : i(ini)
            , s(ins){}
    };
    struct Sce_s
    {
        ConstantExpression *ce;
        Statement *s;
        constexpr Sce_s(ConstantExpression *ince = nullptr
            , Statement *ins = nullptr) noexcept
            : ce(ince)
            , s(ins){}
    };
    struct Ss
    {
        Statement *s;
        constexpr Ss(Statement *ins = nullptr) noexcept
            : s(ins){}
    };

    using Var = std::variant<std::monostate
        , Si_s
        , Sce_s
        , Ss>;

    Var var;

    template<class ...Args>
    LabeledStatement(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~LabeledStatement();
};

struct ExpressionStatement
{
    Expression *e;
    
    constexpr ExpressionStatement(Expression *ine = nullptr) noexcept
        : e(ine){}
    ~ExpressionStatement();
};

struct SelectionStatement
{
    struct Si_e_s
    {
        Expression *e;
        Statement *s;
        constexpr Si_e_s(Expression *ine = nullptr
            , Statement *ins = nullptr) noexcept
            : e(ine)
            , s(ins){}
    };
    struct Si_e_s_s
    {
        Expression *e;
        Statement *s0;
        Statement *s1;
        constexpr Si_e_s_s(Expression *ine = nullptr
            , Statement *ins0 = nullptr
            , Statement *ins1 = nullptr) noexcept
            : e(ine)
            , s0(ins0)
            , s1(ins1){}
    };
    struct Ss_e_s
    {
        Expression *e;
        Statement *s;
        constexpr Ss_e_s(Expression *ine = nullptr
            , Statement *ins = nullptr) noexcept
            : e(ine)
            , s(ins){}
    };

    using Var = std::variant<std::monostate
        , Si_e_s
        , Si_e_s_s
        , Ss_e_s>;
    
    Var var;

    template<class ...Args>
    SelectionStatement(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~SelectionStatement();
};

struct IterationStatement
{
    struct Sw_e_s
    {
        Expression *e;
        Statement *s;
        constexpr Sw_e_s(Expression *ine = nullptr
            , Statement *ins = nullptr) noexcept
            : e(ine)
            , s(ins){}
    };
    struct Sd_s_e
    {
        Statement *s;
        Expression *e;
        constexpr Sd_s_e(Statement *ins = nullptr
            , Expression *ine = nullptr) noexcept
            : s(ins)
            , e(ine){}
    };
    struct Sf_e_e_e_s
    {
        Expression *e0;
        Expression *e1;
        Expression *e2;
        Statement *s;
        constexpr Sf_e_e_e_s(Expression *ine0 = nullptr
            , Expression *ine1 = nullptr
            , Expression *ine2 = nullptr
            , Statement *ins = nullptr) noexcept
            : e0(ine0)
            , e1(ine1)
            , e2(ine2)
            , s(ins){}
    };
    struct Sf_d_e_e_s
    {
        Declaration *d;
        Expression *e0;
        Expression *e1;
        Statement *s;
        constexpr Sf_d_e_e_s(Declaration *ind = nullptr
            , Expression *ine0 = nullptr
            , Expression *ine1 = nullptr
            , Statement *ins = nullptr) noexcept
            : d(ind)
            , e0(ine0)
            , e1(ine1)
            , s(ins){}
    };

    using Var = std::variant<std::monostate
        , Sw_e_s
        , Sd_s_e
        , Sf_e_e_e_s
        , Sf_d_e_e_s>;

    Var var;

    template<class ...Args>
    IterationStatement(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~IterationStatement();
};

struct JumpStatement
{
    struct Sg_i
    {
        Identifier *i;
        constexpr Sg_i(Identifier *ini = nullptr) noexcept
            : i(ini){}
    };
    struct Sc
    {
        constexpr Sc() noexcept{}
    };
    struct Sb
    {
        constexpr Sb() noexcept{}
    };
    struct Sr_e
    {
        Expression *e;
        constexpr Sr_e(Expression *ine = nullptr) noexcept
            : e(ine){}
    };

    using Var = std::variant<std::monostate
        , Sg_i
        , Sc
        , Sb
        , Sr_e>;

    Var var;

    template<class ...Args>
    JumpStatement(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~JumpStatement();
};

struct Designation
{
    DesignatorList *dl;

    constexpr Designation(DesignatorList *indl = nullptr) noexcept
        : dl(indl){}
    ~Designation();
};

struct LogicalANDExpression
{
    std::vector<InclusiveORExpression*> seq;

    template<class ...Args>
    LogicalANDExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~LogicalANDExpression();
};

struct StructDeclaratorList
{
    std::vector<StructDeclarator*> seq;

    template<class ...Args>
    StructDeclaratorList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~StructDeclaratorList();
};

struct PrimaryExpression
{
    using Var = std::variant<std::monostate
        , Identifier*
        , Constant*
        , StringLiteral*
        , Expression*
        , GenericSelection*>;
    
    Var var;

    template<class ...Args>
    PrimaryExpression(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~PrimaryExpression();
};

struct ArgumentExpressionList
{
    std::vector<AssignmentExpression*> seq;

    template<class ...Args>
    ArgumentExpressionList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~ArgumentExpressionList();
};

struct DesignatorList
{
    std::vector<Designator*> seq;

    template<class ...Args>
    DesignatorList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~DesignatorList();
};

struct InclusiveORExpression
{
    std::vector<ExclusiveORExpression*> seq;

    template<class ...Args>
    InclusiveORExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~InclusiveORExpression();
};

struct StructDeclarator
{
    struct Sd
    {
        Declarator *d;
        constexpr Sd(Declarator *ind = nullptr) noexcept
            : d(ind){}
    };
    struct Sd_ce
    {
        Declarator *d;
        ConstantExpression *ce;
        constexpr Sd_ce(Declarator *ind = nullptr
            , ConstantExpression *ince = nullptr) noexcept
            : d(ind)
            , ce(ince){}
    };

    using Var = std::variant<std::monostate
        , Sd
        , Sd_ce>;

    Var var;

    template<class ...Args>
    StructDeclarator(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~StructDeclarator();
};

struct GenericSelection
{
    AssignmentExpression *ae;
    GenericAssocList *gal;

    constexpr GenericSelection(AssignmentExpression *inae = nullptr
        , GenericAssocList *ingal = nullptr) noexcept
        : ae(inae)
        , gal(ingal){}
    ~GenericSelection();
};

struct Designator
{
    using Var = std::variant<std::monostate
        , ConstantExpression*
        , Identifier*>;

    Var var;

    template<class ...Args>
    Designator(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~Designator();
};

struct ExclusiveORExpression
{
    std::vector<ANDExpression*> seq;

    template<class ...Args>
    ExclusiveORExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~ExclusiveORExpression();
};

struct GenericAssocList
{
    std::vector<GenericAssociation*> seq;

    template<class ...Args>
    GenericAssocList(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~GenericAssocList();
};

struct ANDExpression
{
    std::vector<EqualityExpression*> seq;

    template<class ...Args>
    ANDExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~ANDExpression();
};

struct GenericAssociation
{
    struct Stn_ae
    {
        TypeName *tn;
        AssignmentExpression *ae;
        constexpr Stn_ae(TypeName *intn = nullptr
            , AssignmentExpression *inae = nullptr) noexcept
            : tn(intn)
            , ae(inae){}
    };
    struct Sae
    {
        AssignmentExpression *ae;
        constexpr Sae(AssignmentExpression *inae = nullptr) noexcept
            : ae(inae){}
    };

    using Var = std::variant<std::monostate
        , Stn_ae
        , Sae>;

    Var var;

    template<class ...Args>
    GenericAssociation(Args &&...args)
        : var(std::forward<Args>(args)...){}
    ~GenericAssociation();
};

struct EqualityExpression
{
    struct Sre
    {
        RelationalExpression *re;
        constexpr Sre(RelationalExpression *inre = nullptr) noexcept
            : re(inre){}
    };
    struct Se_re
    {
        RelationalExpression *re;
        constexpr Se_re(RelationalExpression *inre = nullptr) noexcept
            : re(inre){}
    };
    struct Sne_re
    {
        RelationalExpression *re;
        constexpr Sne_re(RelationalExpression *inre = nullptr) noexcept
            : re(inre){}
    };

    using Var = std::variant<std::monostate
        , Sre
        , Se_re
        , Sne_re>;

    std::vector<Var> seq;

    template<class ...Args>
    EqualityExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~EqualityExpression();
};

struct RelationalExpression
{
    struct Sse
    {
        ShiftExpression *se;
        constexpr Sse(ShiftExpression *inse = nullptr) noexcept
            : se(inse){}
    };
    struct Sl_se
    {
        ShiftExpression *se;
        constexpr Sl_se(ShiftExpression *inse = nullptr) noexcept
            : se(inse){}
    };
    struct Sg_se
    {
        ShiftExpression *se;
        constexpr Sg_se(ShiftExpression *inse = nullptr) noexcept
            : se(inse){}
    };
    struct Sle_se
    {
        ShiftExpression *se;
        constexpr Sle_se(ShiftExpression *inse = nullptr) noexcept
            : se(inse){}
    };
    struct Sge_se
    {
        ShiftExpression *se;
        constexpr Sge_se(ShiftExpression *inse = nullptr) noexcept
            : se(inse){}
    };

    using Var = std::variant<std::monostate
        , Sse
        , Sl_se
        , Sg_se
        , Sle_se
        , Sge_se>;

    std::vector<Var> seq;

    template<class ...Args>
    RelationalExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~RelationalExpression();
};

struct ShiftExpression
{
    struct Sae
    {
        AdditiveExpression *ae;
        constexpr Sae(AdditiveExpression *inae) noexcept
            : ae(inae){}
    };
    struct Sl_ae
    {
        AdditiveExpression *ae;
        constexpr Sl_ae(AdditiveExpression *inae) noexcept
            : ae(inae){}
    };
    struct Sr_ae
    {
        AdditiveExpression *ae;
        constexpr Sr_ae(AdditiveExpression *inae) noexcept
            : ae(inae){}
    };

    using Var =  std::variant<std::monostate
        , Sae
        , Sl_ae
        , Sr_ae>;

    std::vector<Var> seq;

    template<class ...Args>
    ShiftExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~ShiftExpression();
};

struct AdditiveExpression
{
    struct Sme
    {
        MultiplicativeExpression *me;
        constexpr Sme(MultiplicativeExpression *inme = nullptr)
            : me(inme){}
    };
    struct Sa_me
    {
        MultiplicativeExpression *me;
        constexpr Sa_me(MultiplicativeExpression *inme = nullptr)
            : me(inme){}
    };
    struct Ss_me
    {
        MultiplicativeExpression *me;
        constexpr Ss_me(MultiplicativeExpression *inme = nullptr)
            : me(inme){}
    };

    using Var = std::variant<std::monostate
        , Sme
        , Sa_me
        , Ss_me>;
    
    std::vector<Var> seq;

    template<class ...Args>
    AdditiveExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~AdditiveExpression();
};

struct MultiplicativeExpression
{
    struct Sce
    {
        CastExpression *ce;
        constexpr Sce(CastExpression *ince = nullptr) noexcept
            : ce(ince){}
    };
    struct Sm_ce
    {
        CastExpression *ce;
        constexpr Sm_ce(CastExpression *ince = nullptr) noexcept
            : ce(ince){}
    };
    struct Sd_ce
    {
        CastExpression *ce;
        constexpr Sd_ce(CastExpression *ince = nullptr) noexcept
            : ce(ince){}
    };
    struct Sr_ce
    {
        CastExpression *ce;
        constexpr Sr_ce(CastExpression *ince = nullptr) noexcept
            : ce(ince){}
    };

    using Var = std::variant<std::monostate
        , Sce
        , Sm_ce
        , Sd_ce
        , Sr_ce>;
    
    std::vector<Var> seq;

    template<class ...Args>
    MultiplicativeExpression(Args &&...args)
        : seq(std::forward<Args>(args)...){}
    ~MultiplicativeExpression();
};

}

#endif