#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <variant>
#include <vector>
#include <utility>
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
    using Variant = std::variant<std::monostate
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
};

struct Digit
{
    char c;

    constexpr Digit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~Digit() = default;
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
};

struct EnumerationConstant
{
    Identifier *i;

    constexpr EnumerationConstant(Identifier *ini = nullptr) noexcept
        : i(ini){}
    ~EnumerationConstant();
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
};

struct SCharSequence
{
    std::vector<SChar*> seq;

    template<class... Args>
    SCharSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~SCharSequence();
};

struct Nondigit
{
    char c;

    constexpr Nondigit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~Nondigit() = default;
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
};

struct OctalConstant
{
    std::vector<OctalDigit*> seq;
    
    template<class Seq>
    OctalConstant(Seq &&inseq)
        : seq(std::forward<Seq>(inseq)){}
    ~OctalConstant();
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
};

struct CCharSequence
{
    std::vector<CChar*> seq;

    template<class... Args>
    CCharSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~CCharSequence();
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
};

struct HexQuad
{
    std::array<HexadecimalDigit*, 4> arr;

    template<class... Args>
    HexQuad(Args&&... args)
        : arr(std::forward<Args>(args)...){}
    ~HexQuad();
};

struct NonzeroDigit
{
    char c;

    constexpr NonzeroDigit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~NonzeroDigit() = default;
};

struct OctalDigit
{
    char c;

    constexpr OctalDigit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~OctalDigit() = default;
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
};

struct HexadecimalDigit
{
    char c;

    constexpr HexadecimalDigit(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~HexadecimalDigit() = default;
};

struct FractionalConstant
{
    struct Sds_ds
    {
        DigitSequence *ds0;
        DigitSequence *ds1;
    };
    struct Sds
    {
        DigitSequence *ds;
    };

    using Variant = std::variant<std::monostate
        , Sds_ds
        , Sds>;
    
    Variant var;

    template<class... Args>
    FractionalConstant(Args&&... args)
        : var(std::forward<Args>(args)...){}
    ~FractionalConstant();
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
};

struct DigitSequence
{
    std::vector<Digit*> seq;

    template<class... Args>
    DigitSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~DigitSequence();
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
};

struct HexadecimalDigitSequence
{
    std::vector<HexadecimalDigit*> seq;

    template<class... Args>
    HexadecimalDigitSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~HexadecimalDigitSequence();
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
};

struct SimpleEscapeSequence
{
    char c;
    
    constexpr SimpleEscapeSequence(char inc = static_cast<char>(0)) noexcept
        : c(inc){}
    ~SimpleEscapeSequence() = default;
};

struct OctalEscapeSequence
{
    std::vector<OctalDigit*> seq;

    template<class... Args>
    OctalEscapeSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~OctalEscapeSequence();
};

struct HexadecimalEscapeSequence
{
    std::vector<HexadecimalDigit*> seq;
    
    template<class... Args>
    HexadecimalEscapeSequence(Args&&... args)
        : seq(std::forward<Args>(args)...){}
    ~HexadecimalEscapeSequence();
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
};

}

#endif