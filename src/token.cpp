#include "token.hpp"

namespace TOKEN
{

const std::unordered_map<Keyword::Tag, std::string> Keyword::KEYWORD_MAP
    = {{Tag::AUTO, "auto"}
        , {Tag::BREAK, "break"}
        , {Tag::CASE, "case"}
        , {Tag::CHAR, "char"}
        , {Tag::CONST, "const"}
        , {Tag::CONTINUE, "continue"}
        , {Tag::DEFAULT, "default"}
        , {Tag::DO, "do"}
        , {Tag::DOUBLE, "double"}
        , {Tag::ELSE, "else"}
        , {Tag::ENUM, "enum"}
        , {Tag::EXTERN, "extern"}
        , {Tag::FLOAT, "float"}
        , {Tag::FOR, "for"}
        , {Tag::GOTO, "goto"}
        , {Tag::IF, "if"}
        , {Tag::INLINE, "inline"}
        , {Tag::INT, "int"}
        , {Tag::LONG, "long"}
        , {Tag::REGISTER, "register"}
        , {Tag::RESTRICT, "restrict"}
        , {Tag::RETURN, "return"}
        , {Tag::SHORT, "short"}
        , {Tag::SIGNED, "signed"}
        , {Tag::SIZEOF, "sizeof"}
        , {Tag::STATIC, "static"}
        , {Tag::STRUCT, "struct"}
        , {Tag::SWITCH, "switch"}
        , {Tag::TYPEDEF, "typedef"}
        , {Tag::UNION, "union"}
        , {Tag::UNSIGNED, "unsigned"}
        , {Tag::VOID, "void"}
        , {Tag::VOLATILE, "volatile"}
        , {Tag::WHILE, "while"}
        , {Tag::ALIGNAS, "_Alignas"}
        , {Tag::ALIGNOF, "_Alignof"}
        , {Tag::ATOMIC, "_Atomic"}
        , {Tag::BOOL, "_Bool"}
        , {Tag::COMPLEX, "_Complex"}
        , {Tag::GENERIC, "_Generic"}
        , {Tag::IMAGINARY, "_Imaginary"}
        , {Tag::NORETURN, "_Noreturn"}
        , {Tag::STATIC_ASSERT, "_Static_assert"}
        , {Tag::THREAD_LOCAL, "_Thread_local"}};

const std::unordered_map<Punctuator::Tag, std::string> Punctuator::PUNCTUATOR_MAP
    = {{Tag::L_SQUARE_BRACKET, "["}
        , {Tag::R_SQUARE_BRACKET, "]"}
        , {Tag::L_PARENTHESIS, "("}
        , {Tag::R_PARENTHESIS, ")"}
        , {Tag::L_CURLY_BRACKET, "{"}
        , {Tag::R_CURLY_BRACKET, "}"}
        , {Tag::PERIOD, "."}
        , {Tag::ARROW, "->"}
        , {Tag::INCREMENT, "++"}
        , {Tag::DECREMENT, "--"}
        , {Tag::BITAND, "&"}
        , {Tag::ASTERISK, "*"}
        , {Tag::PLUS, "+"}
        , {Tag::MINUS, "-"}
        , {Tag::COMPL, "~"}
        , {Tag::NOT, "!"}
        , {Tag::SLASH, "/"}
        , {Tag::PERCENT, "%"}
        , {Tag::L_SHIFT, "<<"}
        , {Tag::R_SHIFT, ">>"}
        , {Tag::LESS, "<"}
        , {Tag::GREATER, ">"}
        , {Tag::LESS_EQUAL, "<="}
        , {Tag::GREATER_EQUAL, ">="}
        , {Tag::EQUAL, "=="}
        , {Tag::NOT_EQUAL, "!="}
        , {Tag::XOR, "^"}
        , {Tag::BITOR, "|"}
        , {Tag::AND, "&&"}
        , {Tag::OR, "||"}
        , {Tag::QUESTION, "?"}
        , {Tag::COLON, ":"}
        , {Tag::SEMICOLON, ";"}
        , {Tag::TRIPLE_PERIOD, "..."}
        , {Tag::ASSIGNMENT, "="}
        , {Tag::ASTERISK_ASSIGNMENT, "*="}
        , {Tag::SLASH_ASSIGNMENT, "/="}
        , {Tag::PERCENT_ASSIGNMENT, "%="}
        , {Tag::PLUS_ASSIGNMENT, "+="}
        , {Tag::MINUS_ASSIGNMENT, "-="}
        , {Tag::L_SHIFT_ASSIGNMENT, "<<="}
        , {Tag::R_SHIFT_ASSIGNMENT, ">>="}
        , {Tag::AND_ASSIGNMENT, "&="}
        , {Tag::XOR_ASSIGNMENT, "^="}
        , {Tag::BITOR_ASSIGNMENT, "|="}
        , {Tag::COMMA, ","}
        , {Tag::HASH, "#"}
        , {Tag::DOUBLE_HASH, "##"}};

Token::~Token()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Keyword*>(var))
        delete std::get<Keyword*>(var);
    else if(std::holds_alternative<Identifier*>(var))
        delete std::get<Identifier*>(var);
    else if(std::holds_alternative<Constant*>(var))
        delete std::get<Constant*>(var);
    else if(std::holds_alternative<StringLiteral*>(var))
        delete std::get<StringLiteral*>(var);
    else if(std::holds_alternative<Punctuator*>(var))
        delete std::get<Punctuator*>(var);
}

Token *Token::copy() const
{   
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Keyword*>(var))
        cvar.emplace<Keyword*>(std::get<Keyword*>(var)->copy());
    else if(std::holds_alternative<Identifier*>(var))
        cvar.emplace<Identifier*>(std::get<Identifier*>(var)->copy());
    else if(std::holds_alternative<Constant*>(var))
        cvar.emplace<Constant*>(std::get<Constant*>(var)->copy());
    else if(std::holds_alternative<StringLiteral*>(var))
        cvar.emplace<StringLiteral*>(std::get<StringLiteral*>(var)->copy());
    else if(std::holds_alternative<Punctuator*>(var))
        cvar.emplace<Punctuator*>(std::get<Punctuator*>(var)->copy());
    
    return new Token(cvar);
}

std::string &Token::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Keyword*>(var))
        std::get<Keyword*>(var)->str(res, indent);
    else if(std::holds_alternative<Identifier*>(var))
        std::get<Identifier*>(var)->str(res, indent);
    else if(std::holds_alternative<Constant*>(var))
        std::get<Constant*>(var)->str(res, indent);
    else if(std::holds_alternative<StringLiteral*>(var))
        std::get<Punctuator*>(var)->str(res, indent);
    else if(std::holds_alternative<Punctuator*>(var))
        std::get<Punctuator*>(var)->str(res, indent);
    
    return res;
}

Keyword *Keyword::copy() const
{
    return new Keyword(tag);
}

std::string &Keyword::str(std::string &res, std::size_t &indent) const
{
    if(auto iter = KEYWORD_MAP.find(tag);
        iter != KEYWORD_MAP.end())
        res += iter->second;

    return res;
}

Identifier::~Identifier()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<IdentifierNondigit*>(v))
            delete std::get<IdentifierNondigit*>(v);
        else if(std::holds_alternative<Digit*>(v))
            delete std::get<Digit*>(v);
    }
}

Identifier *Identifier::copy() const
{
    std::vector<Variant> cseq;

    for(auto &&v : seq)
    {
        Variant cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<IdentifierNondigit*>(v))
            cv.emplace<IdentifierNondigit*>(std::get<IdentifierNondigit*>(v)->copy());
        else if(std::holds_alternative<Digit*>(v))
            cv.emplace<Digit*>(std::get<Digit*>(v)->copy());

        cseq.push_back(cv);
    }

    return new Identifier(std::move(cseq));
}

std::string &Identifier::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<IdentifierNondigit*>(v))
            std::get<IdentifierNondigit*>(v)->str(res, indent);
        else if(std::holds_alternative<Digit*>(v))
            std::get<Digit*>(v)->str(res, indent);
    }

    return res;
}

Constant::~Constant()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<IntegerConstant*>(var))
        delete std::get<IntegerConstant*>(var);
    else if(std::holds_alternative<FloatingConstant*>(var))
        delete std::get<FloatingConstant*>(var);
    else if(std::holds_alternative<EnumerationConstant*>(var))
        delete std::get<EnumerationConstant*>(var);
    else if(std::holds_alternative<CharacterConstant*>(var))
        delete std::get<CharacterConstant*>(var);
}

Constant *Constant::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<IntegerConstant*>(var))
        cvar.emplace<IntegerConstant*>(std::get<IntegerConstant*>(var)->copy());
    else if(std::holds_alternative<FloatingConstant*>(var))
        cvar.emplace<FloatingConstant*>(std::get<FloatingConstant*>(var)->copy());
    else if(std::holds_alternative<EnumerationConstant*>(var))
        cvar.emplace<EnumerationConstant*>(std::get<EnumerationConstant*>(var)->copy());
    else if(std::holds_alternative<CharacterConstant*>(var))
        cvar.emplace<CharacterConstant*>(std::get<CharacterConstant*>(var)->copy());
    
    return new Constant(cvar);
}

std::string &Constant::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<IntegerConstant*>(var))
        std::get<IntegerConstant*>(var)->str(res, indent);
    else if(std::holds_alternative<FloatingConstant*>(var))
        std::get<FloatingConstant*>(var)->str(res, indent);
    else if(std::holds_alternative<EnumerationConstant*>(var))
        std::get<EnumerationConstant*>(var)->str(res, indent);
    else if(std::holds_alternative<CharacterConstant*>(var))
        std::get<CharacterConstant*>(var)->str(res, indent);
    
    return res;
}

StringLiteral::~StringLiteral()
{
    delete ep;
    delete scs;
}

StringLiteral *StringLiteral::copy() const
{
    return new StringLiteral(ep != nullptr ? ep->copy() : nullptr
        , scs != nullptr ? scs->copy() : nullptr);
}

std::string &StringLiteral::str(std::string &res, std::size_t &indent) const
{
    if(ep != nullptr)
        ep->str(res, indent);
    res.push_back('\"');
    if(scs != nullptr)
        scs->str(res, indent);
    res.push_back('\"');

    return res;
}

Punctuator *Punctuator::copy() const
{
    return new Punctuator(tag);
}

std::string &Punctuator::str(std::string &res, std::size_t &indent) const
{
    if(auto i = PUNCTUATOR_MAP.find(tag);
        i != PUNCTUATOR_MAP.end())
        res += i->second;
    
    return res;
}

IdentifierNondigit::~IdentifierNondigit()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Nondigit*>(var))
        delete std::get<Nondigit*>(var);
    else if(std::holds_alternative<UniversalCharacterName*>(var))
        delete std::get<UniversalCharacterName*>(var);
}

IdentifierNondigit *IdentifierNondigit::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Nondigit*>(var))
        cvar.emplace<Nondigit*>(std::get<Nondigit*>(var)->copy());
    else if(std::holds_alternative<UniversalCharacterName*>(var))
        cvar.emplace<UniversalCharacterName*>(std::get<UniversalCharacterName*>(var)->copy());
    
    return new IdentifierNondigit(cvar);
}

std::string &IdentifierNondigit::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Nondigit*>(var))
        std::get<Nondigit*>(var)->str(res, indent);
    else if(std::holds_alternative<UniversalCharacterName*>(var))
        std::get<UniversalCharacterName*>(var)->str(res, indent);
    
    return res;
}

Digit *Digit::copy() const
{
    return new Digit(c);
}

std::string &Digit::str(std::string &res, std::size_t &indent) const
{
    res.push_back(c);
    return res;
}

IntegerConstant::~IntegerConstant()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sdc_is>(var))
    {
        auto &&s = std::get<Sdc_is>(var);
        delete s.dc;
        delete s.is;
    }
    else if(std::holds_alternative<Soc_is>(var))
    {
        auto &&s = std::get<Soc_is>(var);
        delete s.oc;
        delete s.is;
    }
    else if(std::holds_alternative<Shc_is>(var))
    {
        auto &&s = std::get<Shc_is>(var);
        delete s.hc;
        delete s.is;
    }
}

IntegerConstant *IntegerConstant::copy() const
{
    Variant cvar;

    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sdc_is>(var))
    {
        auto &&s = std::get<Sdc_is>(var);
        cvar.emplace<Sdc_is>(s.dc->copy()
            , s.is != nullptr ? s.is->copy() : nullptr);
    }
    else if(std::holds_alternative<Soc_is>(var))
    {
        auto &&s = std::get<Soc_is>(var);
        cvar.emplace<Soc_is>(s.oc->copy()
            , s.is != nullptr ? s.is->copy() : nullptr);
    }
    else if(std::holds_alternative<Shc_is>(var))
    {
        auto &&s = std::get<Shc_is>(var);
        cvar.emplace<Shc_is>(s.hc->copy()
            , s.is != nullptr ? s.is->copy() : nullptr);
    }

    return new IntegerConstant(cvar);
}

std::string &IntegerConstant::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sdc_is>(var))
    {
        auto &&s = std::get<Sdc_is>(var);
        s.dc->str(res, indent);
        if(s.is != nullptr)
            s.is->str(res, indent);
    }
    else if(std::holds_alternative<Soc_is>(var))
    {
        auto &&s = std::get<Soc_is>(var);
        s.oc->str(res, indent);
        if(s.is != nullptr)
            s.is->str(res, indent);
    }
    else if(std::holds_alternative<Shc_is>(var))
    {
        auto &&s = std::get<Shc_is>(var);
        s.hc->str(res, indent);
        if(s.is != nullptr)
            s.is->str(res, indent);
    }

    return res;
}

FloatingConstant::~FloatingConstant()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<DecimalFloatingConstant*>(var))
        delete std::get<DecimalFloatingConstant*>(var);
    else if(std::holds_alternative<HexadecimalFloatingConstant*>(var))
        delete std::get<HexadecimalFloatingConstant*>(var);
}

FloatingConstant *FloatingConstant::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<DecimalFloatingConstant*>(var))
        cvar.emplace<DecimalFloatingConstant*>(std::get<DecimalFloatingConstant*>(var)->copy());
    else if(std::holds_alternative<HexadecimalFloatingConstant*>(var))
        cvar.emplace<HexadecimalFloatingConstant*>(std::get<HexadecimalFloatingConstant*>(var)->copy());
    
    return new FloatingConstant(cvar);
}

std::string &FloatingConstant::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<DecimalFloatingConstant*>(var))
        std::get<DecimalFloatingConstant*>(var)->str(res, indent);
    else if(std::holds_alternative<HexadecimalFloatingConstant*>(var))
        std::get<HexadecimalFloatingConstant*>(var)->str(res, indent);
    
    return res;
}

EnumerationConstant::~EnumerationConstant()
{
    delete i;
}

EnumerationConstant *EnumerationConstant::copy() const
{
    return new EnumerationConstant(i->copy());
}

std::string &EnumerationConstant::str(std::string &res, std::size_t &indent) const
{
    return i->str(res, indent);
}

CharacterConstant::~CharacterConstant()
{
    delete ccs;
}

CharacterConstant *CharacterConstant::copy() const
{
    return new CharacterConstant(tag, ccs->copy());
}

std::string &CharacterConstant::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::L):
            res.push_back('L');
            break;
        case(Tag::u):
            res.push_back('u');
            break;
        case(Tag::U):
            res.push_back('U');
            break;
        
        default:;
    }

    res.push_back('\'');
    ccs->str(res, indent);
    res.push_back('\'');

    return res;
}

EncodingPrefix *EncodingPrefix::copy() const
{
    return new EncodingPrefix(tag);
}

std::string &EncodingPrefix::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::u8):
            res += "u8";
            break;
        case(Tag::u):
            res.push_back('u');
            break;
        case(Tag::U):
            res.push_back('U');
            break;
        case(Tag::L):
            res.push_back('L');
            break;
        
        default:;
    }

    return res;
}

SCharSequence::~SCharSequence()
{
    for(auto &&sc : seq)
        delete sc;
}

SCharSequence *SCharSequence::copy() const
{
    std::vector<SChar*> cseq;
    for(auto &&sc : seq)
        cseq.push_back(sc->copy());

    return new SCharSequence(std::move(cseq));
}

std::string &SCharSequence::str(std::string &res, std::size_t &indent) const
{
    for(auto &&sc : seq)
        sc->str(res, indent);
    
    return res;
}

Nondigit *Nondigit::copy() const
{
    return new Nondigit(c);
}

std::string &Nondigit::str(std::string &res, std::size_t &indent) const
{
    res.push_back(c);
    return res;
}

UniversalCharacterName::~UniversalCharacterName()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Su_hq>(var))
    {
        auto &&s = std::get<Su_hq>(var);
        delete s.hq;
    }
    else if(std::holds_alternative<SU_hq_hq>(var))
    {
        auto &&s = std::get<SU_hq_hq>(var);
        delete s.hq0;
        delete s.hq1;
    }
}

UniversalCharacterName *UniversalCharacterName::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Su_hq>(var))
    {
        auto &&s = std::get<Su_hq>(var);
        cvar.emplace<Su_hq>(s.hq->copy());
    }
    else if(std::holds_alternative<SU_hq_hq>(var))
    {
        auto &&s = std::get<SU_hq_hq>(var);
        cvar.emplace<SU_hq_hq>(s.hq0->copy(), s.hq1->copy());
    }
    
    return new UniversalCharacterName(cvar);
}

std::string &UniversalCharacterName::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Su_hq>(var))
    {
        res += "\\u";
        auto &&s = std::get<Su_hq>(var);
        s.hq->str(res, indent);
    }
    else if(std::holds_alternative<SU_hq_hq>(var))
    {
        res += "\\U";
        auto &&s = std::get<SU_hq_hq>(var);
        s.hq0->str(res, indent);
        s.hq1->str(res, indent);
    }

    return res;
}

DecimalConstant::~DecimalConstant()
{
    delete nd;
    for(auto &&d : seq)
        delete d;
}

DecimalConstant *DecimalConstant::copy() const
{
    std::vector<Digit*> cseq;
    for(auto &&d : seq)
        cseq.push_back(d->copy());

    return new DecimalConstant(nd->copy(), std::move(cseq));
}

std::string &DecimalConstant::str(std::string &res, std::size_t &indent) const
{
    nd->str(res, indent);
    for(auto &&d : seq)
        d->str(res, indent);
    
    return res;
}

OctalConstant::~OctalConstant()
{
    for(auto &&od : seq)
        delete od;
}

OctalConstant *OctalConstant::copy() const
{
    std::vector<OctalDigit*> cseq;
    for(auto &&od : seq)
        cseq.push_back(od->copy());
    
    return new OctalConstant(std::move(cseq));
}

std::string &OctalConstant::str(std::string &res, std::size_t &indent) const
{
    res.push_back('0');
    for(auto &&od : seq)
        od->str(res, indent);

    return res;
}

HexadecimalConstant::~HexadecimalConstant()
{
    delete hp;
    for(auto &&hd : seq)
        delete hd;
}

HexadecimalConstant *HexadecimalConstant::copy() const
{
    std::vector<HexadecimalDigit*> cseq;
    for(auto &&hd : seq)
        cseq.push_back(hd->copy());
    
    return new HexadecimalConstant(hp->copy(), std::move(cseq));
}

std::string &HexadecimalConstant::str(std::string &res, std::size_t &indent) const
{
    hp->str(res, indent);
    for(auto &&hd : seq)
        hd->str(res, indent);
    
    return res;
}

DecimalFloatingConstant::~DecimalFloatingConstant()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sfc_ep_fs>(var))
    {
        auto &&s = std::get<Sfc_ep_fs>(var);
        delete s.fc;
        delete s.ep;
        delete s.fs;
    }
    else if(std::holds_alternative<Sds_ep_fs>(var))
    {
        auto &&s = std::get<Sds_ep_fs>(var);
        delete s.ds;
        delete s.ep;
        delete s.fs;
    }
}

DecimalFloatingConstant *DecimalFloatingConstant::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sfc_ep_fs>(var))
    {
        auto &&s = std::get<Sfc_ep_fs>(var);
        cvar.emplace<Sfc_ep_fs>(s.fc->copy()
            , s.ep != nullptr ? s.ep->copy() : nullptr
            , s.fs != nullptr ? s.fs->copy() : nullptr);
    }
    else if(std::holds_alternative<Sds_ep_fs>(var))
    {
        auto &&s = std::get<Sds_ep_fs>(var);
        cvar.emplace<Sds_ep_fs>(s.ds->copy()
            , s.ep->copy()
            , s.fs != nullptr ? s.fs->copy() : nullptr);
    }

    return new DecimalFloatingConstant(cvar);
}

std::string &DecimalFloatingConstant::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sfc_ep_fs>(var))
    {
        auto &&s = std::get<Sfc_ep_fs>(var);
        s.fc->str(res, indent);
        if(s.ep != nullptr)
            s.ep->str(res, indent);
        if(s.fs != nullptr)
            s.fs->str(res, indent);
    }
    else if(std::holds_alternative<Sds_ep_fs>(var))
    {
        auto &&s = std::get<Sds_ep_fs>(var);
        s.ds->str(res, indent);
        s.ep->str(res, indent);
        if(s.fs != nullptr)
            s.fs->str(res, indent);
    }

    return res;
}

HexadecimalFloatingConstant::~HexadecimalFloatingConstant()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Shp_hfc_bep_fs>(var))
    {
        auto &&s = std::get<Shp_hfc_bep_fs>(var);
        delete s.hp;
        delete s.hfc;
        delete s.bep;
        delete s.fs;
    }
    else if(std::holds_alternative<Shp_hds_bep_fs>(var))
    {
        auto &&s = std::get<Shp_hds_bep_fs>(var);
        delete s.hp;
        delete s.hds;
        delete s.bep;
        delete s.fs;
    }
}

HexadecimalFloatingConstant *HexadecimalFloatingConstant::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Shp_hfc_bep_fs>(var))
    {
        auto &&s = std::get<Shp_hfc_bep_fs>(var);
        cvar.emplace<Shp_hfc_bep_fs>(s.hp->copy()
            , s.hfc->copy()
            , s.bep->copy()
            , s.fs != nullptr ? s.fs->copy() : nullptr);
    }
    else if(std::holds_alternative<Shp_hds_bep_fs>(var))
    {
        auto &&s = std::get<Shp_hds_bep_fs>(var);
        cvar.emplace<Shp_hds_bep_fs>(s.hp->copy()
            , s.hds->copy()
            , s.bep->copy()
            , s.fs != nullptr ? s.fs->copy() : nullptr);
    }

    return new HexadecimalFloatingConstant(cvar);
}

std::string &HexadecimalFloatingConstant::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Shp_hfc_bep_fs>(var))
    {
        auto &&s = std::get<Shp_hfc_bep_fs>(var);
        s.hp->str(res, indent);
        s.hfc->str(res, indent);
        s.bep->str(res, indent);
        if(s.fs != nullptr)
            s.fs->str(res, indent);
    }
    else if(std::holds_alternative<Shp_hds_bep_fs>(var))
    {
        auto &&s = std::get<Shp_hds_bep_fs>(var);
        s.hp->str(res, indent);
        s.hds->str(res, indent);
        s.bep->str(res, indent);
        if(s.fs != nullptr)
            s.fs->str(res, indent);
    }

    return res;
}

CCharSequence::~CCharSequence()
{
    for(auto &&cc : seq)
        delete cc;
}

CCharSequence *CCharSequence::copy() const
{
    std::vector<CChar*> cseq;
    for(auto &&cc : seq)
        cseq.push_back(cc->copy());
    
    return new CCharSequence(std::move(cseq));
}

std::string &CCharSequence::str(std::string &res, std::size_t &indent) const
{
    for(auto &&cc : seq)
        cc->str(res, indent);
    
    return res;
}

SChar::~SChar()
{
    if(std::holds_alternative<std::monostate>(var)
        || std::holds_alternative<char>(var))
        ;
    else if(std::holds_alternative<EscapeSequence*>(var))
        delete std::get<EscapeSequence*>(var);
}

SChar *SChar::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<char>(var))
        cvar.emplace<char>(std::get<char>(var));
    else if(std::holds_alternative<EscapeSequence*>(var))
        cvar.emplace<EscapeSequence*>(std::get<EscapeSequence*>(var)->copy());

    return new SChar(cvar);
}

std::string &SChar::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<char>(var))
        res.push_back(std::get<char>(var));
    else if(std::holds_alternative<EscapeSequence*>(var))
        std::get<EscapeSequence*>(var)->str(res, indent);
    
    return res;
}

HexQuad::~HexQuad()
{
    for(auto &&hd : arr)
        delete hd;
}

HexQuad *HexQuad::copy() const
{
    std::array<HexadecimalDigit*, 4> carr;
    for(std::size_t i = 0; i < arr.size(); i++)
        carr[i] = arr[i]->copy();
    
    return new HexQuad(std::move(carr));
}

std::string &HexQuad::str(std::string &res, std::size_t &indent) const
{
    for(auto&& hd : arr)
        hd->str(res, indent);
    
    return res;
}

NonzeroDigit *NonzeroDigit::copy() const
{
    return new NonzeroDigit(c);
}

std::string &NonzeroDigit::str(std::string &res, std::size_t &indent) const
{
    res.push_back(c);
    return res;
}

OctalDigit *OctalDigit::copy() const
{
    return new OctalDigit(c);
}

std::string &OctalDigit::str(std::string &res, std::size_t &indent) const
{
    res.push_back(c);
    return res;
}

HexadecimalPrefix *HexadecimalPrefix::copy() const
{
    return new HexadecimalPrefix(tag);
}

std::string &HexadecimalPrefix::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::x):
            res += "0x";
            break;
        case(Tag::X):
            res += "0X";
            break;
        
        default:;
    }

    return res;
}

HexadecimalDigit *HexadecimalDigit::copy() const
{
    return new HexadecimalDigit(c);
}

std::string &HexadecimalDigit::str(std::string &res, std::size_t &indent) const
{
    res.push_back(c);
    return res;
}

FractionalConstant::~FractionalConstant()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sds_ds>(var))
    {
        auto &&s = std::get<Sds_ds>(var);
        delete s.ds0;
        delete s.ds1;
    }
    else if(std::holds_alternative<Sds>(var))
    {
        auto &&s = std::get<Sds>(var);
        delete s.ds;
    }
}

FractionalConstant *FractionalConstant::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sds_ds>(var))
    {
        auto &&s = std::get<Sds_ds>(var);
        cvar.emplace<Sds_ds>(s.ds0 ? s.ds0->copy() : nullptr
            , s.ds1->copy());
    }
    else if(std::holds_alternative<Sds>(var))
    {
        auto &&s = std::get<Sds>(var);
        cvar.emplace<Sds>(s.ds->copy());
    }

    return new FractionalConstant(cvar);
}

std::string &FractionalConstant::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sds_ds>(var))
    {
        auto &&s = std::get<Sds_ds>(var);
        if(s.ds0 != nullptr)
            s.ds0->str(res, indent);
        res.push_back('.');
        s.ds1->str(res, indent);
    }
    else if(std::holds_alternative<Sds>(var))
    {
        auto &&s = std::get<Sds>(var);
        s.ds->str(res, indent);
        res.push_back('.');
    }

    return res;
}

ExponentPart::~ExponentPart()
{
    delete s;
    delete ds;
}

ExponentPart *ExponentPart::copy() const
{
    return new ExponentPart(s != nullptr ? s->copy() : nullptr
        , ds->copy());
}

std::string &ExponentPart::str(std::string &res, std::size_t &indent) const
{
    res.push_back('e');
    if(s != nullptr)
        s->str(res, indent);
    ds->str(res, indent);

    return res;
}

Sign *Sign::copy() const
{
    return new Sign(tag);
}

std::string &Sign::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::PLUS):
            res.push_back('+');
            break;
        case(Tag::MINUS):
            res.push_back('-');
            break;
        
        default:;
    }

    return res;
}

DigitSequence::~DigitSequence()
{
    for(auto &&d : seq)
        delete d;
}

DigitSequence *DigitSequence::copy() const
{
    std::vector<Digit*> cseq;
    for(auto &&d : seq)
        cseq.push_back(d->copy());
    
    return new DigitSequence(std::move(cseq));
}

std::string &DigitSequence::str(std::string &res, std::size_t &indent) const
{
    for(auto &&d : seq)
        d->str(res, indent);

    return res;
} 

HexadecimalFractionalConstant::~HexadecimalFractionalConstant()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Shds_hds>(var))
    {
        auto &&s = std::get<Shds_hds>(var);
        delete s.hds0;
        delete s.hds1;
    }
    else if(std::holds_alternative<Shds>(var))
    {
        auto &&s = std::get<Shds>(var);
        delete s.hds;
    }
}

HexadecimalFractionalConstant *HexadecimalFractionalConstant::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Shds_hds>(var))
    {
        auto &&s = std::get<Shds_hds>(var);
        cvar.emplace<Shds_hds>(s.hds0 != nullptr ? s.hds0->copy() : nullptr
            , s.hds1->copy());
    }
    else if(std::holds_alternative<Shds>(var))
    {
        auto &&s = std::get<Shds>(var);
        cvar.emplace<Shds>(s.hds->copy());
    }

    return new HexadecimalFractionalConstant(cvar);
}

std::string &HexadecimalFractionalConstant::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Shds_hds>(var))
    {
        auto &&s = std::get<Shds_hds>(var);
        if(s.hds0 != nullptr)
            s.hds0->str(res, indent);
        res.push_back('.');
        s.hds1->str(res, indent);
    }
    else if(std::holds_alternative<Shds>(var))
    {
        auto &&s = std::get<Shds>(var);
        s.hds->str(res, indent);
        res.push_back('.');
    }

    return res;
}

BinaryExponentPart::~BinaryExponentPart()
{
    delete s;
    delete ds;
}

BinaryExponentPart *BinaryExponentPart::copy() const
{
    return new BinaryExponentPart(s != nullptr ? s->copy() : nullptr
        , ds->copy());
};

std::string &BinaryExponentPart::str(std::string &res, std::size_t &indent) const
{
    res.push_back('p');
    if(s != nullptr)
        s->str(res, indent);
    ds->str(res, indent);

    return res;
}

HexadecimalDigitSequence::~HexadecimalDigitSequence()
{
    for(auto &&hd : seq)
        delete hd;
}

HexadecimalDigitSequence *HexadecimalDigitSequence::copy() const
{
    std::vector<HexadecimalDigit*> cseq;
    for(auto &&hd : seq)
        cseq.push_back(hd->copy());
    
    return new HexadecimalDigitSequence(std::move(cseq));
}

std::string &HexadecimalDigitSequence::str(std::string &res, std::size_t &indent) const
{
    for(auto &&hd : seq)
        hd->str(res, indent);
    
    return res;
}

FloatingSuffix *FloatingSuffix::copy() const
{
    return new FloatingSuffix(tag);
}

std::string &FloatingSuffix::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::f):
            res.push_back('f');
            break;
        case(Tag::l):
            res.push_back('L');
            break;
        case(Tag::F):
            res.push_back('F');
            break;
        case(Tag::L):
            res.push_back('L');
            break;
        
        default:;
    }

    return res;
}

CChar::~CChar()
{
    if(std::holds_alternative<std::monostate>(var)
        || std::holds_alternative<char>(var))
        ;
    else if(std::holds_alternative<EscapeSequence*>(var))
        delete std::get<EscapeSequence*>(var);
}

CChar *CChar::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<char>(var))
        cvar.emplace<char>(std::get<char>(var));
    else if(std::holds_alternative<EscapeSequence*>(var))
        cvar.emplace<EscapeSequence*>(std::get<EscapeSequence*>(var)->copy());
    
    return new CChar(cvar);
}

std::string &CChar::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<char>(var))
        res.push_back(std::get<char>(var));
    else if(std::holds_alternative<EscapeSequence*>(var))
        std::get<EscapeSequence*>(var)->str(res, indent);

    return res;
}

EscapeSequence::~EscapeSequence()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<SimpleEscapeSequence*>(var))
        delete std::get<SimpleEscapeSequence*>(var);
    else if(std::holds_alternative<OctalEscapeSequence*>(var))
        delete std::get<OctalEscapeSequence*>(var);
    else if(std::holds_alternative<HexadecimalEscapeSequence*>(var))
        delete std::get<HexadecimalEscapeSequence*>(var);
    else if(std::holds_alternative<UniversalCharacterName*>(var))
        delete std::get<UniversalCharacterName*>(var);
}

EscapeSequence *EscapeSequence::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<SimpleEscapeSequence*>(var))
        cvar.emplace<SimpleEscapeSequence*>(std::get<SimpleEscapeSequence*>(var)->copy());
    else if(std::holds_alternative<OctalEscapeSequence*>(var))
        cvar.emplace<OctalEscapeSequence*>(std::get<OctalEscapeSequence*>(var)->copy());
    else if(std::holds_alternative<HexadecimalEscapeSequence*>(var))
        cvar.emplace<HexadecimalEscapeSequence*>(std::get<HexadecimalEscapeSequence*>(var)->copy());
    else if(std::holds_alternative<UniversalCharacterName*>(var))
        cvar.emplace<UniversalCharacterName*>(std::get<UniversalCharacterName*>(var)->copy());
    
    return new EscapeSequence(cvar);
}

std::string &EscapeSequence::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<SimpleEscapeSequence*>(var))
        std::get<SimpleEscapeSequence*>(var)->str(res, indent);
    else if(std::holds_alternative<OctalEscapeSequence*>(var))
        std::get<OctalEscapeSequence*>(var)->str(res, indent);
    else if(std::holds_alternative<HexadecimalEscapeSequence*>(var))
        std::get<HexadecimalEscapeSequence*>(var)->str(res, indent);
    else if(std::holds_alternative<UniversalCharacterName*>(var))
        std::get<UniversalCharacterName*>(var)->str(res, indent);
    
    return res;
}

SimpleEscapeSequence *SimpleEscapeSequence::copy() const
{
    return new SimpleEscapeSequence(c);
}

std::string &SimpleEscapeSequence::str(std::string &res, std::size_t &indent) const
{
    res.push_back('\\');
    res.push_back(c);
    return res;
}

OctalEscapeSequence::~OctalEscapeSequence()
{
    for(auto &&od : seq)
        delete od;
}

OctalEscapeSequence *OctalEscapeSequence::copy() const
{
    std::vector<OctalDigit*> cseq;
    for(auto &&od : seq)
        cseq.push_back(od->copy());
    
    return new OctalEscapeSequence(std::move(cseq));
}

std::string &OctalEscapeSequence::str(std::string &res, std::size_t &indent) const
{
    res.push_back('\\');
    for(auto &&od : seq)
        od->str(res, indent);
    
    return res;
}

HexadecimalEscapeSequence::~HexadecimalEscapeSequence()
{
    for(auto &&hd : seq)
        delete hd;
}

HexadecimalEscapeSequence *HexadecimalEscapeSequence::copy() const
{
    std::vector<HexadecimalDigit*> cseq;
    for(auto &&hd : seq)
        cseq.push_back(hd->copy());
    
    return new HexadecimalEscapeSequence(std::move(cseq));
}

std::string &HexadecimalEscapeSequence::str(std::string &res, std::size_t &indent) const
{
    res += "\\x";
    for(auto &&hd : seq)
        hd->str(res, indent);

    return res;
}

PreprocessingToken::~PreprocessingToken()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Identifier*>(var))
        delete std::get<Identifier*>(var);
    else if(std::holds_alternative<PPNumber*>(var))
        delete std::get<PPNumber*>(var);
    else if(std::holds_alternative<CharacterConstant*>(var))
        delete std::get<CharacterConstant*>(var);
    else if(std::holds_alternative<StringLiteral*>(var))
        delete std::get<StringLiteral*>(var);
    else if(std::holds_alternative<Punctuator*>(var))
        delete std::get<Punctuator*>(var);
}

PreprocessingToken *PreprocessingToken::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Identifier*>(var))
        cvar.emplace<Identifier*>(std::get<Identifier*>(var)->copy());
    else if(std::holds_alternative<PPNumber*>(var))
        cvar.emplace<PPNumber*>(std::get<PPNumber*>(var)->copy());
    else if(std::holds_alternative<CharacterConstant*>(var))
        cvar.emplace<CharacterConstant*>(std::get<CharacterConstant*>(var)->copy());
    else if(std::holds_alternative<StringLiteral*>(var))
        cvar.emplace<StringLiteral*>(std::get<StringLiteral*>(var)->copy());
    else if(std::holds_alternative<Punctuator*>(var))
        cvar.emplace<Punctuator*>(std::get<Punctuator*>(var)->copy());

    return new PreprocessingToken(cvar);
}

std::string &PreprocessingToken::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Identifier*>(var))
        std::get<Identifier*>(var)->str(res, indent);
    else if(std::holds_alternative<PPNumber*>(var))
        std::get<PPNumber*>(var)->str(res, indent);
    else if(std::holds_alternative<CharacterConstant*>(var))
        std::get<CharacterConstant*>(var)->str(res, indent);
    else if(std::holds_alternative<StringLiteral*>(var))
        std::get<StringLiteral*>(var)->str(res, indent);
    else if(std::holds_alternative<Punctuator*>(var))
        std::get<Punctuator*>(var)->str(res, indent);
    
    return res;
}

PPNumber::~PPNumber()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v)
            || std::holds_alternative<Tag>(v))
            ;
        else if(std::holds_alternative<Digit*>(v))
            delete std::get<Digit*>(v);
        else if(std::holds_alternative<IdentifierNondigit*>(v))
            delete std::get<IdentifierNondigit*>(v);
        else if(std::holds_alternative<Sign*>(v))
            delete std::get<Sign*>(v);
    }
}

PPNumber *PPNumber::copy() const
{
    std::vector<Variant> cseq;
    for(auto &&v : seq)
    {
        Variant cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Digit*>(v))
            cv.emplace<Digit*>(std::get<Digit*>(v)->copy());
        else if(std::holds_alternative<Tag>(v))
            cv.emplace<Tag>(std::get<Tag>(v));
        else if(std::holds_alternative<IdentifierNondigit*>(v))
            cv.emplace<IdentifierNondigit*>(std::get<IdentifierNondigit*>(v)->copy());
        else if(std::holds_alternative<Sign*>(v))
            cv.emplace<Sign*>(std::get<Sign*>(v)->copy());
        
        cseq.push_back(cv);
    }

    return new PPNumber(std::move(cseq));
}

std::string &PPNumber::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Digit*>(v))
            std::get<Digit*>(v)->str(res, indent);
        else if(std::holds_alternative<Tag>(v))
        {
            switch(std::get<Tag>(v))
            {
                case(Tag::PERIOD):
                    res.push_back('.');
                    break;
                case(Tag::e):
                    res.push_back('e');
                    break;
                case(Tag::E):
                    res.push_back('E');
                    break;
                case(Tag::p):
                    res.push_back('p');
                    break;
                case(Tag::P):
                    res.push_back('P');
                    break;
                
                default:;
            }
        }
        else if(std::holds_alternative<IdentifierNondigit*>(v))
            std::get<IdentifierNondigit*>(v)->str(res, indent);
        else if(std::holds_alternative<Sign*>(v))
            std::get<Sign*>(v)->str(res, indent);
    }

    return res;
}

IntegerSuffix::~IntegerSuffix()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sus_ls>(var))
    {
        auto &&s = std::get<Sus_ls>(var);
        delete s.us;
        delete s.ls;
    }
    else if(std::holds_alternative<Sus_lls>(var))
    {
        auto &&s = std::get<Sus_lls>(var);
        delete s.us;
        delete s.lls;
    }
    else if(std::holds_alternative<Sls_us>(var))
    {
        auto &&s = std::get<Sls_us>(var);
        delete s.ls;
        delete s.us;
    }
    else if(std::holds_alternative<Slls_us>(var))
    {
        auto &&s = std::get<Slls_us>(var);
        delete s.lls;
        delete s.us;
    }
}

IntegerSuffix *IntegerSuffix::copy() const
{
    Variant cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sus_ls>(var))
    {
        auto &&s = std::get<Sus_ls>(var);
        cvar.emplace<Sus_ls>(s.us->copy()
            , s.ls != nullptr ? s.ls->copy() : nullptr);
    }
    else if(std::holds_alternative<Sus_lls>(var))
    {
        auto &&s = std::get<Sus_lls>(var);
        cvar.emplace<Sus_lls>(s.us->copy()
            , s.lls->copy());
    }
    else if(std::holds_alternative<Sls_us>(var))
    {
        auto &&s = std::get<Sls_us>(var);
        cvar.emplace<Sls_us>(s.ls->copy()
            , s.us != nullptr ? s.us->copy() : nullptr);
    }
    else if(std::holds_alternative<Slls_us>(var))
    {
        auto &&s = std::get<Slls_us>(var);
        cvar.emplace<Slls_us>(s.lls->copy()
            , s.us != nullptr ? s.us->copy() : nullptr);
    }

    return new IntegerSuffix(var);
}

std::string &IntegerSuffix::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sus_ls>(var))
    {
        auto &&s = std::get<Sus_ls>(var);
        s.us->str(res, indent);
        if(s.ls != nullptr)
            s.ls->str(res, indent);
    }
    else if(std::holds_alternative<Sus_lls>(var))
    {
        auto &&s = std::get<Sus_lls>(var);
        s.us->str(res, indent);
        s.lls->str(res, indent);
    }
    else if(std::holds_alternative<Sls_us>(var))
    {
        auto &&s = std::get<Sls_us>(var);
        s.ls->str(res, indent);
        if(s.us != nullptr)
            s.us->str(res, indent);
    }
    else if(std::holds_alternative<Slls_us>(var))
    {
        auto &&s = std::get<Slls_us>(var);
        s.lls->str(res, indent);
        if(s.us != nullptr)
            s.us->str(res, indent);
    }

    return res;
}

UnsignedSuffix *UnsignedSuffix::copy() const
{
    return new UnsignedSuffix(tag);
}

std::string &UnsignedSuffix::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::u):
            res.push_back('u');
            break;
        case(Tag::U):
            res.push_back('U');
            break;
        
        default:;
    }

    return res;
}

LongSuffix *LongSuffix::copy() const
{
    return new LongSuffix(tag);
}

std::string &LongSuffix::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::l):
            res.push_back('l');
            break;
        case(Tag::L):
            res.push_back('L');
            break;
        
        default:;
    }

    return res;
}

LongLongSuffix *LongLongSuffix::copy() const
{
    return new LongLongSuffix(tag);
}

std::string &LongLongSuffix::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::ll):
            res += "ll";
            break;
        case(Tag::LL):
            res += "LL";
            break;
        
        default:;
    }

    return res;
}

TranslationUnit::~TranslationUnit()
{
    for(auto &&ed : seq)
        delete ed;
}

TranslationUnit *TranslationUnit::copy() const
{
    std::vector<ExternalDeclaration*> cseq;
    for(auto &&ed : seq)
        cseq.push_back(ed->copy());
    
    return new TranslationUnit(std::move(cseq));
}

std::string &TranslationUnit::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);
    for(std::size_t i = 1; i < seq.size(); i++)
    {
        addLine(res, indent);
        addLine(res, indent);
        seq[i]->str(res, indent);
    }

    return res;
}

ExternalDeclaration::~ExternalDeclaration()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<FunctionDefinition*>(var))
        delete std::get<FunctionDefinition*>(var);
    else if(std::holds_alternative<Declaration*>(var))
        delete std::get<Declaration*>(var);
}

ExternalDeclaration *ExternalDeclaration::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<FunctionDefinition*>(var))
        cvar.emplace<FunctionDefinition*>(std::get<FunctionDefinition*>(var)->copy());
    else if(std::holds_alternative<Declaration*>(var))
        cvar.emplace<Declaration*>(std::get<Declaration*>(var)->copy());
    
    return new ExternalDeclaration(cvar);
}

std::string &ExternalDeclaration::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<FunctionDefinition*>(var))
        std::get<FunctionDefinition*>(var)->str(res, indent);
    else if(std::holds_alternative<Declaration*>(var))
        std::get<Declaration*>(var)->str(res, indent);
    
    return res;
}

FunctionDefinition::~FunctionDefinition()
{
    delete ds;
    delete d;
    delete dl;
    delete cs;
}

FunctionDefinition *FunctionDefinition::copy() const
{
    return new FunctionDefinition(ds->copy()
        , d->copy()
        , dl != nullptr ? dl->copy() : nullptr
        , cs->copy());
}

std::string &FunctionDefinition::str(std::string &res, std::size_t &indent) const
{
    ds->str(res, indent);
    res.push_back(' ');
    d->str(res, indent);
    addLine(res, indent);
    if(dl != nullptr)
    {
        addLine(res, indent);
        indent++;
        dl->str(res, indent);
        indent--;
        addLine(res, indent);
    }
    cs->str(res, indent);

    return res;
}

Declaration::~Declaration()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sds_idl>(var))
    {
        auto &&s = std::get<Sds_idl>(var);
        delete s.ds;
        delete s.idl;
    }
    else if(std::holds_alternative<Ssad>(var))
    {
        auto &&s = std::get<Ssad>(var);
        delete s.sad;
    }
}

Declaration *Declaration::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sds_idl>(var))
    {
        auto &&s = std::get<Sds_idl>(var);
        cvar.emplace<Sds_idl>(s.ds->copy()
            , s.idl != nullptr ? s.idl->copy() : nullptr);
    }
    else if(std::holds_alternative<Ssad>(var))
    {
        auto &&s = std::get<Ssad>(var);
        cvar.emplace<Ssad>(s.sad->copy());
    }

    return new Declaration(cvar);
}

std::string &Declaration::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sds_idl>(var))
    {
        auto &&s = std::get<Sds_idl>(var);
        s.ds->str(res, indent);
        if(s.idl != nullptr)
        {
            res.push_back(' ');
            s.idl->str(res, indent);
        }
        res.push_back(';');
    }
    else if(std::holds_alternative<Ssad>(var))
    {
        auto &&s = std::get<Ssad>(var);
        s.sad->str(res, indent);
    }

    return res;
}

DeclarationSpecifiers::~DeclarationSpecifiers()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<StorageClassSpecifier*>(v))
            delete std::get<StorageClassSpecifier*>(v);
        else if(std::holds_alternative<TypeSpecifier*>(v))
            delete std::get<TypeSpecifier*>(v);
        else if(std::holds_alternative<TypeQualifier*>(v))
            delete std::get<TypeQualifier*>(v);
        else if(std::holds_alternative<FunctionSpecifier*>(v))
            delete std::get<FunctionSpecifier*>(v);
        else if(std::holds_alternative<AlignmentSpecifier*>(v))
            delete std::get<AlignmentSpecifier*>(v);
    }
}

DeclarationSpecifiers *DeclarationSpecifiers::copy() const
{
    std::vector<Var> cseq;

    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<StorageClassSpecifier*>(v))
            cv.emplace<StorageClassSpecifier*>(std::get<StorageClassSpecifier*>(v)->copy());
        else if(std::holds_alternative<TypeSpecifier*>(v))
            cv.emplace<TypeSpecifier*>(std::get<TypeSpecifier*>(v)->copy());
        else if(std::holds_alternative<TypeQualifier*>(v))
            cv.emplace<TypeQualifier*>(std::get<TypeQualifier*>(v)->copy());
        else if(std::holds_alternative<FunctionSpecifier*>(v))
            cv.emplace<FunctionSpecifier*>(std::get<FunctionSpecifier*>(v)->copy());
        else if(std::holds_alternative<AlignmentSpecifier*>(v))
            cv.emplace<AlignmentSpecifier*>(std::get<AlignmentSpecifier*>(v)->copy());
    
        cseq.push_back(cv);
    }

    return new DeclarationSpecifiers(std::move(cseq));
}

std::string &DeclarationSpecifiers::str(std::string &res, std::size_t &indent) const
{
    auto s = [&](auto &&v)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<StorageClassSpecifier*>(v))
            std::get<StorageClassSpecifier*>(v)->str(res, indent);
        else if(std::holds_alternative<TypeSpecifier*>(v))
            std::get<TypeSpecifier*>(v)->str(res, indent);
        else if(std::holds_alternative<TypeQualifier*>(v))
            std::get<TypeQualifier*>(v)->str(res, indent);
        else if(std::holds_alternative<FunctionSpecifier*>(v))
            std::get<FunctionSpecifier*>(v)->str(res, indent);
        else if(std::holds_alternative<AlignmentSpecifier*>(v))
            std::get<AlignmentSpecifier*>(v)->str(res, indent);
    };

    if(!seq.empty())
        s(seq.front());
    
    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res.push_back(' ');
        s(seq[i]);
    }

    return res;
}

Declarator::~Declarator()
{
    delete p;
    delete dd;
}

Declarator *Declarator::copy() const
{
    return new Declarator(p != nullptr ? p->copy() : nullptr
        , dd->copy());
}

std::string &Declarator::str(std::string &res, std::size_t &indent) const
{
    if(p != nullptr)
    {
        p->str(res, indent);
        res.push_back(' ');
    }
    dd->str(res, indent);

    return res;
}

DeclarationList::~DeclarationList()
{
    for(auto &&d : seq)
        delete d;
}

DeclarationList *DeclarationList::copy() const
{
    std::vector<Declaration*> cseq;
    for(auto &&d : cseq)
        cseq.push_back(d->copy());
    
    return new DeclarationList(std::move(cseq));
}

std::string &DeclarationList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
    {
        res = std::string(4 * indent, ' ');
        seq.front()->str(res, indent);
    }

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        addLine(res, indent);
        seq[i]->str(res, indent);
    }

    return res;
}

CompoundStatement::~CompoundStatement()
{
    delete bil;
}

CompoundStatement *CompoundStatement::copy() const
{
    return new CompoundStatement(bil != nullptr ? bil->copy() : nullptr);
}

std::string &CompoundStatement::str(std::string &res, std::size_t &indent) const
{
    res.push_back('{');
    indent++;
    addLine(res, indent);
    if(bil != nullptr)
        bil->str(res, indent);
    indent--;
    addLine(res, indent);
    res.push_back('}');

    return res;
}

InitDeclaratorList::~InitDeclaratorList()
{
    for(auto &&id : seq)
        delete id;
}

InitDeclaratorList *InitDeclaratorList::copy() const
{
    std::vector<InitDeclarator*> cseq;
    for(auto &&id : seq)
        cseq.push_back(id->copy());
    
    return new InitDeclaratorList(std::move(cseq));
}

std::string &InitDeclaratorList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);
    
    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += ", ";
        seq[i]->str(res, indent);
    }

    return res;
}

StaticAssertDeclaration::~StaticAssertDeclaration()
{
    delete ce;
    delete sl;
}

StaticAssertDeclaration *StaticAssertDeclaration::copy() const
{
    return new StaticAssertDeclaration(ce->copy()
        , sl->copy());
}

std::string &StaticAssertDeclaration::str(std::string &res, std::size_t &indent) const
{
    res += "_Static_assert(";
    ce->str(res, indent);
    res += ", ";
    sl->str(res, indent);
    res += ");";

    return res;
}

StorageClassSpecifier *StorageClassSpecifier::copy() const
{
    return new StorageClassSpecifier(tag);
}

std::string &StorageClassSpecifier::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::TYPEDEF):
            res += "typedef";
            break;
        case(Tag::EXTERN):
            res += "extern";
            break;
        case(Tag::STATIC):
            res += "static";
            break;
        case(Tag::THREAD_LOCAL):
            res += "_Thread_local";
            break;
        case(Tag::AUTO):
            res += "auto";
            break;
        case(Tag::REGISTER):
            res += "register";
            break;
        
        default:;
    }

    return res;
}

TypeSpecifier::~TypeSpecifier()
{
    if(std::holds_alternative<std::monostate>(var)
        || std::holds_alternative<Tag>(var))
        ;
    else if(std::holds_alternative<AtomicTypeSpecifier*>(var))
        delete std::get<AtomicTypeSpecifier*>(var);
    else if(std::holds_alternative<StructOrUnionSpecifier*>(var))
        delete std::get<StructOrUnionSpecifier*>(var);
    else if(std::holds_alternative<EnumSpecifier*>(var))
        delete std::get<EnumSpecifier*>(var);
    else if(std::holds_alternative<TypedefName*>(var))
        delete std::get<TypedefName*>(var);
}

TypeSpecifier *TypeSpecifier::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Tag>(var))
        cvar.emplace<Tag>(std::get<Tag>(var));
    else if(std::holds_alternative<AtomicTypeSpecifier*>(var))
        cvar.emplace<AtomicTypeSpecifier*>(std::get<AtomicTypeSpecifier*>(var)->copy());
    else if(std::holds_alternative<StructOrUnionSpecifier*>(var))
        cvar.emplace<StructOrUnionSpecifier*>(std::get<StructOrUnionSpecifier*>(var)->copy());
    else if(std::holds_alternative<EnumSpecifier*>(var))
        cvar.emplace<EnumSpecifier*>(std::get<EnumSpecifier*>(var)->copy());
    else if(std::holds_alternative<TypedefName*>(var))
        cvar.emplace<TypedefName*>(std::get<TypedefName*>(var)->copy());
    
    return new TypeSpecifier(cvar);
}

std::string &TypeSpecifier::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Tag>(var))
    {
        switch(std::get<Tag>(var))
        {
            case(Tag::VOID):
                res += "void";
                break;
            case(Tag::CHAR):
                res += "char";
                break;
            case(Tag::SHORT):
                res += "short";
                break;
            case(Tag::INT):
                res += "int";
                break;
            case(Tag::LONG):
                res += "long";
                break;
            case(Tag::FLOAT):
                res += "float";
                break;
            case(Tag::DOUBLE):
                res += "double";
                break;
            case(Tag::SIGNED):
                res += "signed";
                break;
            case(Tag::UNSIGNED):
                res += "unsigned";
                break;
            case(Tag::BOOL):
                res += "_Bool";
                break;
            case(Tag::COMPLEX):
                res += "_Complex";
                break;
            
            default:;
        }
    }
    else if(std::holds_alternative<AtomicTypeSpecifier*>(var))
        std::get<AtomicTypeSpecifier*>(var)->str(res, indent);
    else if(std::holds_alternative<StructOrUnionSpecifier*>(var))
        std::get<StructOrUnionSpecifier*>(var)->str(res, indent);
    else if(std::holds_alternative<EnumSpecifier*>(var))
        std::get<EnumSpecifier*>(var)->str(res, indent);
    else if(std::holds_alternative<TypedefName*>(var))
        std::get<TypedefName*>(var)->str(res, indent);
    
    return res;
}

TypeQualifier *TypeQualifier::copy() const
{
    return new TypeQualifier(tag);
}

std::string &TypeQualifier::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::CONST):
            res += "const";
            break;
        case(Tag::RESTRICT):
            res += "restrict";
            break;
        case(Tag::VOLATILE):
            res += "volatile";
            break;
        case(Tag::ATOMIC):
            res += "_Atomic";
            break;
        
        default:;
    }

    return res;
}

FunctionSpecifier *FunctionSpecifier::copy() const
{
    return new FunctionSpecifier(tag);
}

std::string &FunctionSpecifier::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::INLINE):
            res += "inline";
            break;
        case(Tag::NORETURN):
            res += "_Noreturn";
            break;
        
        default:;
    }

    return res;
}

AlignmentSpecifier::~AlignmentSpecifier()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<TypeName*>(var))
        delete std::get<TypeName*>(var);
    else if(std::holds_alternative<ConstantExpression*>(var))
        delete std::get<ConstantExpression*>(var);
}

AlignmentSpecifier *AlignmentSpecifier::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<TypeName*>(var))
        cvar.emplace<TypeName*>(std::get<TypeName*>(var)->copy());
    else if(std::holds_alternative<ConstantExpression*>(var))
        cvar.emplace<ConstantExpression*>(std::get<ConstantExpression*>(var)->copy());

    return new AlignmentSpecifier(cvar);
}

std::string &AlignmentSpecifier::str(std::string &res, std::size_t &indent) const
{
    res += "_Alignas(";
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<TypeName*>(var))
        std::get<TypeName*>(var)->str(res, indent);
    else if(std::holds_alternative<ConstantExpression*>(var))
        std::get<ConstantExpression*>(var)->str(res, indent);
    
    res += ")";
    return res;
}

Pointer::~Pointer()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Stql>(var))
    {
        auto &&s = std::get<Stql>(var);
        delete s.tql;
    }
    else if(std::holds_alternative<Stql_p>(var))
    {
        auto &&s = std::get<Stql_p>(var);
        delete s.tql;
        delete s.p;
    }
}

Pointer *Pointer::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Stql>(var))
    {
        auto &&s = std::get<Stql>(var);
        cvar.emplace<Stql>(s.tql != nullptr ? s.tql->copy() : nullptr);
    }
    else if(std::holds_alternative<Stql_p>(var))
    {
        auto &&s = std::get<Stql_p>(var);
        cvar.emplace<Stql_p>(s.tql != nullptr ? s.tql->copy() : nullptr
            , s.p->copy());
    }

    return new Pointer(cvar);
}

std::string &Pointer::str(std::string &res, std::size_t &indent) const
{
    res.push_back('*');
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Stql>(var))
    {
        auto &&s = std::get<Stql>(var);
        if(s.tql != nullptr)
        {
            res.push_back(' ');
            s.tql->str(res, indent);
        }
    }
    else if(std::holds_alternative<Stql_p>(var))
    {
        auto &&s = std::get<Stql_p>(var);
        if(s.tql != nullptr)
        {
            res.push_back(' ');
            s.tql->str(res, indent);
        }
        res.push_back(' ');
        s.p->str(res, indent);
    }

    return res;
}

DirectDeclarator::~DirectDeclarator()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Si>(v))
        {
            auto &&s = std::get<Si>(v);
            delete s.i;
        }
        else if(std::holds_alternative<Sd>(v))
        {
            auto &&s = std::get<Sd>(v);
            delete s.d;
        }
        else if(std::holds_alternative<Stql_ae>(v))
        {
            auto &&s = std::get<Stql_ae>(v);
            delete s.tql;
            delete s.ae;
        }
        else if(std::holds_alternative<Stql>(v))
        {
            auto &&s = std::get<Stql>(v);
            delete s.tql;
        }
        else if(std::holds_alternative<Sptl>(v))
        {
            auto &&s = std::get<Sptl>(v);
            delete s.ptl;
        }
        else if(std::holds_alternative<Sil>(v))
        {
            auto &&s = std::get<Sil>(v);
            delete s.il;
        }
    }
}

DirectDeclarator *DirectDeclarator::copy() const
{
    std::vector<Var> cseq;
    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Si>(v))
        {
            auto &&s = std::get<Si>(v);
            cv.emplace<Si>(s.i->copy());
        }
        else if(std::holds_alternative<Sd>(v))
        {
            auto &&s = std::get<Sd>(v);
            cv.emplace<Sd>(s.d->copy());
        }
        else if(std::holds_alternative<Stql_ae>(v))
        {
            auto &&s = std::get<Stql_ae>(v);
            cv.emplace<Stql_ae>(s.tql != nullptr ? s.tql->copy() : nullptr
                , s.ae != nullptr ? s.ae->copy() : nullptr
                , s.hasStatic);
        }
        else if(std::holds_alternative<Stql>(v))
        {
            auto &&s = std::get<Stql>(v);
            cv.emplace<Stql>(s.tql != nullptr ? s.tql->copy() : nullptr);
        }
        else if(std::holds_alternative<Sptl>(v))
        {
            auto &&s = std::get<Sptl>(v);
            cv.emplace<Sptl>(s.ptl->copy());
        }
        else if(std::holds_alternative<Sil>(v))
        {
            auto &&s = std::get<Sil>(v);
            cv.emplace<Sil>(s.il != nullptr ? s.il->copy() : nullptr);
        }

        cseq.push_back(cv);
    }

    return new DirectDeclarator(std::move(cseq));
}

std::string &DirectDeclarator::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Si>(v))
        {
            auto &&s = std::get<Si>(v);
            s.i->str(res, indent);
        }
        else if(std::holds_alternative<Sd>(v))
        {
            auto &&s = std::get<Sd>(v);
            res.push_back('(');
            s.d->str(res, indent);
            res.push_back(')');
        }
        else if(std::holds_alternative<Stql_ae>(v))
        {
            auto &&s = std::get<Stql_ae>(v);
            res.push_back('[');
            if(s.hasStatic)
                res += "static ";
            if(s.tql != nullptr)
            {
                s.tql->str(res, indent);
                if(s.ae != nullptr)
                    res.push_back(' ');
            }
            if(s.ae != nullptr)
                s.ae->str(res, indent);
            
            res.push_back(']');
        }
        else if(std::holds_alternative<Stql>(v))
        {
            auto &&s = std::get<Stql>(v);
            res.push_back('[');
            if(s.tql != nullptr)
            {
                s.tql->str(res, indent);
                res.push_back(' ');
            }
            res.push_back('*');
            res.push_back(']');
        }
        else if(std::holds_alternative<Sptl>(v))
        {
            auto &&s = std::get<Sptl>(v);
            res.push_back('(');
            s.ptl->str(res, indent);
            res.push_back(')');
        }
        else if(std::holds_alternative<Sil>(v))
        {
            auto &&s = std::get<Sil>(v);
            res.push_back('(');
            if(s.il != nullptr)
                s.il->str(res, indent);
            res.push_back(')');
        }
    }

    return res;
}

BlockItemList::~BlockItemList()
{
    for(auto &&bi : seq)
        delete bi;
}

BlockItemList *BlockItemList::copy() const
{
    std::vector<BlockItem*> cseq;
    for(auto &&bi : seq)
        cseq.push_back(bi->copy());
    
    return new BlockItemList(std::move(cseq));
}

std::string &BlockItemList::str(std::string &res, std::size_t &indent) const
{
    for(std::size_t i = 0; i + 1 < seq.size(); i++)
    {
        seq[i]->str(res, indent);
        addLine(res, indent);
    }

    if(!seq.empty())
        seq.back()->str(res, indent);

    return res;
}

InitDeclarator::~InitDeclarator()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sd>(var))
    {
        auto &&s = std::get<Sd>(var);
        delete s.d;
    }
    else if(std::holds_alternative<Sd_i>(var))
    {
        auto &&s = std::get<Sd_i>(var);
        delete s.d;
        delete s.i;
    }
}

InitDeclarator *InitDeclarator::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sd>(var))
    {
        auto &&s = std::get<Sd>(var);
        cvar.emplace<Sd>(s.d->copy());
    }
    else if(std::holds_alternative<Sd_i>(var))
    {
        auto &&s = std::get<Sd_i>(var);
        cvar.emplace<Sd_i>(s.d->copy()
            , s.i->copy());
    }

    return new InitDeclarator(cvar);
}

std::string &InitDeclarator::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sd>(var))
    {
        auto &&s = std::get<Sd>(var);
        s.d->str(res, indent);
    }
    else if(std::holds_alternative<Sd_i>(var))
    {
        auto &&s = std::get<Sd_i>(var);
        s.d->str(res, indent);
        res += " = ";
        s.i->str(res, indent);
    }

    return res;
}

ConstantExpression::~ConstantExpression()
{
    delete ce;
}

ConstantExpression *ConstantExpression::copy() const
{
    return new ConstantExpression(ce->copy());
}

std::string &ConstantExpression::str(std::string &res, std::size_t &indent) const
{
    return ce->str(res, indent);
}

AtomicTypeSpecifier::~AtomicTypeSpecifier()
{
    delete tn;
}

AtomicTypeSpecifier *AtomicTypeSpecifier::copy() const
{
    return new AtomicTypeSpecifier(tn->copy());
}

std::string &AtomicTypeSpecifier::str(std::string &res, std::size_t &indent) const
{
    res += "_Atomic(";
    tn->str(res, indent);
    res.push_back(')');

    return res;
}

StructOrUnionSpecifier::~StructOrUnionSpecifier()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Ssou_i_sdl>(var))
    {
        auto &&s = std::get<Ssou_i_sdl>(var);
        delete s.sou;
        delete s.i;
        delete s.sdl;
    }
    else if(std::holds_alternative<Ssou_i>(var))
    {
        auto &&s = std::get<Ssou_i>(var);
        delete s.sou;
        delete s.i;
    }
}

StructOrUnionSpecifier *StructOrUnionSpecifier::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Ssou_i_sdl>(var))
    {
        auto &&s = std::get<Ssou_i_sdl>(var);
        cvar.emplace<Ssou_i_sdl>(s.sou->copy()
            , s.i != nullptr ? s.i->copy() : nullptr
            , s.sdl->copy());
    }
    else if(std::holds_alternative<Ssou_i>(var))
    {
        auto &&s = std::get<Ssou_i>(var);
        cvar.emplace<Ssou_i>(s.sou->copy()
            , s.i->copy());
    }

    return new StructOrUnionSpecifier(cvar);
}

std::string &StructOrUnionSpecifier::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Ssou_i_sdl>(var))
    {
        auto &&s = std::get<Ssou_i_sdl>(var);
        s.sou->str(res, indent);
        if(s.i != nullptr)
        {
            res.push_back(' ');
            s.i->str(res, indent);
        }
        addLine(res, indent);
        res.push_back('{');
        indent++;
        addLine(res, indent);
        s.sdl->str(res, indent);
        indent--;
        addLine(res, indent);
        res += "}";
    }
    else if(std::holds_alternative<Ssou_i>(var))
    {
        auto &&s = std::get<Ssou_i>(var);
        s.sou->str(res, indent);
        res.push_back(' ');
        s.i->str(res, indent);
    }

    return res;
}

EnumSpecifier::~EnumSpecifier()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Si_el>(var))
    {
        auto &&s = std::get<Si_el>(var);
        delete s.i;
        delete s.el;
    }
    else if(std::holds_alternative<Si>(var))
    {
        auto &&s = std::get<Si>(var);
        delete s.i;
    }
}

EnumSpecifier *EnumSpecifier::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Si_el>(var))
    {
        auto &&s = std::get<Si_el>(var);
        cvar.emplace<Si_el>(s.i != nullptr ? s.i->copy() : nullptr
            , s.el->copy());
    }
    else if(std::holds_alternative<Si>(var))
    {
        auto &&s = std::get<Si>(var);
        cvar.emplace<Si>(s.i->copy());
    }

    return new EnumSpecifier(cvar);
}

std::string &EnumSpecifier::str(std::string &res, std::size_t &indent) const
{
    res += "enum";
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Si_el>(var))
    {
        auto &&s = std::get<Si_el>(var);
        if(s.i != nullptr)
        {
            res.push_back(' ');
            s.i->str(res, indent);
        }
        addLine(res, indent);
        res.push_back('{');
        addLine(res, indent);
        indent++;
        s.el->str(res, indent);
        indent--;
        addLine(res, indent);
        res.push_back('}');
    }
    else if(std::holds_alternative<Si>(var))
    {
        auto &&s = std::get<Si>(var);
        res.push_back(' ');
        s.i->str(res, indent);
    }

    return res;
}

TypedefName::~TypedefName()
{
    delete i;
}

TypedefName *TypedefName::copy() const
{
    return new TypedefName(i->copy());
}

std::string &TypedefName::str(std::string &res, std::size_t &indent) const
{
    return i->str(res, indent);
}

TypeName::~TypeName()
{
    delete sql;
    delete ad;
}

TypeName *TypeName::copy() const
{
    return new TypeName(sql->copy()
        , ad != nullptr ? ad->copy() : nullptr);
}

std::string &TypeName::str(std::string &res, std::size_t &indent) const
{
    sql->str(res, indent);
    if(ad != nullptr)
    {
        res.push_back(' ');
        ad->str(res, indent);
    }

    return res;
}

TypeQualifierList::~TypeQualifierList()
{
    for(auto &&tq : seq)
        delete tq;
}

TypeQualifierList *TypeQualifierList::copy() const
{
    std::vector<TypeQualifier*> cseq;
    for(auto &&tq : seq)
        cseq.push_back(tq->copy());
    
    return new TypeQualifierList(std::move(cseq));
}

std::string &TypeQualifierList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res.push_back(' ');
        seq[i]->str(res, indent);
    }

    return res;
}

AssignmentExpression::~AssignmentExpression()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sce>(var))
    {
        auto &&s = std::get<Sce>(var);
        delete s.ce;
    }
    else if(std::holds_alternative<Sue_ao_ae>(var))
    {
        auto &&s = std::get<Sue_ao_ae>(var);
        delete s.ue;
        delete s.ao;
        delete s.ae;
    }
}

AssignmentExpression *AssignmentExpression::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sce>(var))
    {
        auto &&s = std::get<Sce>(var);
        cvar.emplace<Sce>(s.ce->copy());
    }
    else if(std::holds_alternative<Sue_ao_ae>(var))
    {
        auto &&s = std::get<Sue_ao_ae>(var);
        cvar.emplace<Sue_ao_ae>(s.ue->copy()
            , s.ao->copy()
            , s.ae->copy());
    }

    return new AssignmentExpression(cvar);
}

std::string &AssignmentExpression::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sce>(var))
    {
        auto &&s = std::get<Sce>(var);
        s.ce->str(res, indent);
    }
    else if(std::holds_alternative<Sue_ao_ae>(var))
    {
        auto &&s = std::get<Sue_ao_ae>(var);
        s.ue->str(res, indent);
        res.push_back(' ');
        s.ao->str(res, indent);
        res.push_back(' ');
        s.ae->str(res, indent);
    }

    return res;
}

ParameterTypeList::~ParameterTypeList()
{
    delete pl;
}

ParameterTypeList *ParameterTypeList::copy() const
{
    return new ParameterTypeList(pl->copy());
}

std::string &ParameterTypeList::str(std::string &res, std::size_t &indent) const
{
    pl->str(res, indent);
    if(isValiable)
        res += ", ...";
    
    return res;
}

IdentifierList::~IdentifierList()
{
    for(auto &&i : seq)
        delete i;
}

IdentifierList *IdentifierList::copy() const
{
    std::vector<Identifier*> cseq;
    for(auto &&i : seq)
        cseq.push_back(i->copy());
    
    return new IdentifierList(std::move(cseq));
}

std::string &IdentifierList::str(std::string &res, std::size_t &indnet) const
{
    if(!seq.empty())
        seq.front()->str(res, indnet);
    
    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += ", ";
        seq[i]->str(res, indnet);
    }

    return res;
}

BlockItem::~BlockItem()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Declaration*>(var))
        delete std::get<Declaration*>(var);
    else if(std::holds_alternative<Statement*>(var))
        delete std::get<Statement*>(var);
}

BlockItem *BlockItem::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Declaration*>(var))
        cvar.emplace<Declaration*>(std::get<Declaration*>(var)->copy());
    else if(std::holds_alternative<Statement*>(var))
        cvar.emplace<Statement*>(std::get<Statement*>(var)->copy());
    
    return new BlockItem(cvar);
}

std::string &BlockItem::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Declaration*>(var))
        std::get<Declaration*>(var)->str(res, indent);
    else if(std::holds_alternative<Statement*>(var))
        std::get<Statement*>(var)->str(res, indent);

    return res;
}

Initializer::~Initializer()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<AssignmentExpression*>(var))
        delete std::get<AssignmentExpression*>(var);
    else if(std::holds_alternative<InitializerList*>(var))
        delete std::get<InitializerList*>(var);
}

Initializer *Initializer::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<AssignmentExpression*>(var))
        cvar.emplace<AssignmentExpression*>(std::get<AssignmentExpression*>(var)->copy());
    else if(std::holds_alternative<InitializerList*>(var))
        cvar.emplace<InitializerList*>(std::get<InitializerList*>(var)->copy());
    
    return new Initializer(cvar);
}

std::string &Initializer::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<AssignmentExpression*>(var))
        std::get<AssignmentExpression*>(var)->str(res, indent);
    else if(std::holds_alternative<InitializerList*>(var))
    {
        res.push_back('{');
        std::get<InitializerList*>(var)->str(res, indent);
        res.push_back('}');
    }

    return res;
}

ConditionalExpression::~ConditionalExpression()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Slore>(var))
    {
        auto &&s = std::get<Slore>(var);
        delete s.lore;
    }
    else if(std::holds_alternative<Slore_e_ce>(var))
    {
        auto &&s = std::get<Slore_e_ce>(var);
        delete s.lore;
        delete s.e;
        delete s.ce;
    }
}

ConditionalExpression *ConditionalExpression::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Slore>(var))
    {
        auto &&s = std::get<Slore>(var);
        cvar.emplace<Slore>(s.lore->copy());
    }
    else if(std::holds_alternative<Slore_e_ce>(var))
    {
        auto &&s = std::get<Slore_e_ce>(var);
        cvar.emplace<Slore_e_ce>(s.lore->copy()
            , s.e->copy()
            , s.ce->copy());
    }

    return new ConditionalExpression(cvar);
}

std::string &ConditionalExpression::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Slore>(var))
    {
        auto &&s = std::get<Slore>(var);
        s.lore->str(res, indent);
    }
    else if(std::holds_alternative<Slore_e_ce>(var))
    {
        auto &&s = std::get<Slore_e_ce>(var);
        s.lore->str(res, indent);
        res += " ? ";
        s.e->str(res, indent);
        res += " : ";
        s.ce->str(res, indent);
    }

    return res;
}

StructOrUnion *StructOrUnion::copy() const
{
    return new StructOrUnion(tag);
}

std::string &StructOrUnion::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::STRUCT):
            res += "struct";
            break;
        case(Tag::UNION):
            res += "union";
            break;
        
        default:;
    }

    return res;
}

StructDeclarationList::~StructDeclarationList()
{
    for(auto &&sd : seq)
        delete sd;
}

StructDeclarationList *StructDeclarationList::copy() const
{
    std::vector<StructDeclaration*> cseq;
    for(auto &&sd : seq)
        cseq.push_back(sd->copy());
    
    return new StructDeclarationList(std::move(cseq));
}

std::string &StructDeclarationList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        addLine(res, indent);
        seq[i]->str(res, indent);
    }

    return res;
}

EnumeratorList::~EnumeratorList()
{
    for(auto &&e : seq)
        delete e;
}

EnumeratorList *EnumeratorList::copy() const
{
    std::vector<Enumerator*> cseq;
    for(auto &&e : seq)
        cseq.push_back(e->copy());
    
    return new EnumeratorList(std::move(cseq));
}

std::string &EnumeratorList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
    {
        res += std::string(4 * indent, ' ');
        seq.front()->str(res, indent);
    }

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res.push_back(',');
        addLine(res, indent);
        seq[i]->str(res, indent);
    }

    return res;
}

SpecifierQualifierList::~SpecifierQualifierList()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<TypeSpecifier*>(v))
            delete std::get<TypeSpecifier*>(v);
        else if(std::holds_alternative<TypeQualifier*>(v))
            delete std::get<TypeQualifier*>(v);
        
    }
}

SpecifierQualifierList *SpecifierQualifierList::copy() const
{
    std::vector<Var> cseq;
    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<TypeSpecifier*>(v))
            cv.emplace<TypeSpecifier*>(std::get<TypeSpecifier*>(v)->copy());
        else if(std::holds_alternative<TypeQualifier*>(v))
            cv.emplace<TypeQualifier*>(std::get<TypeQualifier*>(v)->copy());
        
        cseq.push_back(cv);
    }

    return new SpecifierQualifierList(std::move(cseq));
}

std::string &SpecifierQualifierList::str(std::string &res, std::size_t &indent) const
{
    auto s = [&](auto &&v)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<TypeSpecifier*>(v))
            std::get<TypeSpecifier*>(v)->str(res, indent);
        else if(std::holds_alternative<TypeQualifier*>(v))
            std::get<TypeQualifier*>(v)->str(res, indent);
    };

    if(!seq.empty())
        s(seq.front());

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res.push_back(' ');
        s(seq[i]);
    }

    return res;
}

AbstractDeclarator::~AbstractDeclarator()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sp>(var))
    {
        auto &&s = std::get<Sp>(var);
        delete s.p;
    }
    else if(std::holds_alternative<Sp_dad>(var))
    {
        auto &&s = std::get<Sp_dad>(var);
        delete s.p;
        delete s.dad;
    }
}

AbstractDeclarator *AbstractDeclarator::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sp>(var))
    {
        auto &&s = std::get<Sp>(var);
        cvar.emplace<Sp>(s.p->copy());
    }
    else if(std::holds_alternative<Sp_dad>(var))
    {
        auto &&s = std::get<Sp_dad>(var);
        cvar.emplace<Sp_dad>(s.p != nullptr ? s.p->copy() : nullptr
            , s.dad->copy());
    }

    return new AbstractDeclarator(cvar);
}

std::string &AbstractDeclarator::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sp>(var))
    {
        auto &&s = std::get<Sp>(var);
        s.p->str(res, indent);
    }
    else if(std::holds_alternative<Sp_dad>(var))
    {
        auto &&s = std::get<Sp_dad>(var);
        if(s.p != nullptr)
        {
            s.p->str(res, indent);
            res.push_back(' ');
        }
        s.dad->str(res, indent);
    }

    return res;
}

UnaryExpression::~UnaryExpression()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Spe>(var))
    {
        auto &&s = std::get<Spe>(var);
        delete s.pe;
    }
    else if(std::holds_alternative<Si_ue>(var))
    {
        auto &&s = std::get<Si_ue>(var);
        delete s.ue;
    }
    else if(std::holds_alternative<Sd_ue>(var))
    {
        auto &&s = std::get<Sd_ue>(var);
        delete s.ue;
    }
    else if(std::holds_alternative<Suo_ce>(var))
    {
        auto &&s = std::get<Suo_ce>(var);
        delete s.uo;
        delete s.ce;
    }
    else if(std::holds_alternative<Ss_ue>(var))
    {
        auto &&s = std::get<Ss_ue>(var);
        delete s.ue;
    }
    else if(std::holds_alternative<Ss_tn>(var))
    {
        auto &&s = std::get<Ss_tn>(var);
        delete s.tn;
    }
    else if(std::holds_alternative<Sa_tn>(var))
    {
        auto &&s = std::get<Sa_tn>(var);
        delete s.tn;
    }
}

UnaryExpression *UnaryExpression::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Spe>(var))
    {
        auto &&s = std::get<Spe>(var);
        cvar.emplace<Spe>(s.pe->copy());
    }
    else if(std::holds_alternative<Si_ue>(var))
    {
        auto &&s = std::get<Si_ue>(var);
        cvar.emplace<Si_ue>(s.ue->copy());
    }
    else if(std::holds_alternative<Sd_ue>(var))
    {
        auto &&s = std::get<Sd_ue>(var);
        cvar.emplace<Sd_ue>(s.ue->copy());
    }
    else if(std::holds_alternative<Suo_ce>(var))
    {
        auto &&s = std::get<Suo_ce>(var);
        cvar.emplace<Suo_ce>(s.uo->copy()
            , s.ce->copy());
    }
    else if(std::holds_alternative<Ss_ue>(var))
    {
        auto &&s = std::get<Ss_ue>(var);
        cvar.emplace<Ss_ue>(s.ue->copy());
    }
    else if(std::holds_alternative<Ss_tn>(var))
    {
        auto &&s = std::get<Ss_tn>(var);
        cvar.emplace<Ss_tn>(s.tn->copy());
    }
    else if(std::holds_alternative<Sa_tn>(var))
    {
        auto &&s = std::get<Sa_tn>(var);
        cvar.emplace<Sa_tn>(s.tn->copy());
    }

    return new UnaryExpression(cvar);
}

std::string &UnaryExpression::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Spe>(var))
    {
        auto &&s = std::get<Spe>(var);
        s.pe->str(res, indent);
    }
    else if(std::holds_alternative<Si_ue>(var))
    {
        auto &&s = std::get<Si_ue>(var);
        res += "++ ";
        s.ue->str(res, indent);
    }
    else if(std::holds_alternative<Sd_ue>(var))
    {
        auto &&s = std::get<Sd_ue>(var);
        res += "-- ";
        s.ue->str(res, indent);
    }
    else if(std::holds_alternative<Suo_ce>(var))
    {
        auto &&s = std::get<Suo_ce>(var);
        s.uo->str(res, indent);
        res.push_back(' ');
        s.ce->str(res, indent);
    }
    else if(std::holds_alternative<Ss_ue>(var))
    {
        auto &&s = std::get<Ss_ue>(var);
        res += "sizeof ";
        s.ue->str(res, indent);
    }
    else if(std::holds_alternative<Ss_tn>(var))
    {
        auto &&s = std::get<Ss_tn>(var);
        res += "sizeof(";
        s.tn->str(res, indent);
        res.push_back(')');
    }
    else if(std::holds_alternative<Sa_tn>(var))
    {
        auto &&s = std::get<Ss_tn>(var);
        res += "_Alignof(";
        s.tn->str(res, indent);
        res.push_back(')');
    }

    return res;
}

AssignmentOperator *AssignmentOperator::copy() const
{
    return new AssignmentOperator(tag);
}

std::string &AssignmentOperator::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::ASSIGNMENT):
            res.push_back('=');
            break;
        case(Tag::MULTIPLICATION):
            res += "*=";
            break;
        case(Tag::DIVISION):
            res += "/=";
            break;
        case(Tag::REMAINDER):
            res += "%=";
            break;
        case(Tag::ADDITION):
            res += "+=";
            break;
        case(Tag::SUBSTRACTION):
            res += "-=";
            break;
        case(Tag::LEFT_SHIFT):
            res += "<<=";
            break;
        case(Tag::RIGHT_SHIFT):
            res += ">>=";
            break;
        case(Tag::AND):
            res += "&=";
            break;
        case(Tag::XOR):
            res += "^=";
            break;
        case(Tag::OR):
            res += "|=";
            break;
        
        default:;
    }

    return res;
}

ParameterList::~ParameterList()
{
    for(auto &&pd : seq)
        delete pd;
}

ParameterList *ParameterList::copy() const
{
    std::vector<ParameterDeclaration*> cseq;
    for(auto &&pd : seq)
        cseq.push_back(pd->copy());
    
    return new ParameterList(std::move(cseq));
}

std::string &ParameterList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);
    
    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += ", ";
        seq[i]->str(res, indent);
    }

    return res;
}

Statement::~Statement()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<LabeledStatement*>(var))
        delete std::get<LabeledStatement*>(var);
    else if(std::holds_alternative<CompoundStatement*>(var))
        delete std::get<CompoundStatement*>(var);
    else if(std::holds_alternative<ExpressionStatement*>(var))
        delete std::get<ExpressionStatement*>(var);
    else if(std::holds_alternative<SelectionStatement*>(var))
        delete std::get<SelectionStatement*>(var);
    else if(std::holds_alternative<IterationStatement*>(var))
        delete std::get<IterationStatement*>(var);
    else if(std::holds_alternative<JumpStatement*>(var))
        delete std::get<JumpStatement*>(var);
}

Statement *Statement::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<LabeledStatement*>(var))
        cvar.emplace<LabeledStatement*>(std::get<LabeledStatement*>(var)->copy());
    else if(std::holds_alternative<CompoundStatement*>(var))
        cvar.emplace<CompoundStatement*>(std::get<CompoundStatement*>(var)->copy());
    else if(std::holds_alternative<ExpressionStatement*>(var))
        cvar.emplace<ExpressionStatement*>(std::get<ExpressionStatement*>(var)->copy());
    else if(std::holds_alternative<SelectionStatement*>(var))
        cvar.emplace<SelectionStatement*>(std::get<SelectionStatement*>(var)->copy());
    else if(std::holds_alternative<IterationStatement*>(var))
        cvar.emplace<IterationStatement*>(std::get<IterationStatement*>(var)->copy());
    else if(std::holds_alternative<JumpStatement*>(var))
        cvar.emplace<JumpStatement*>(std::get<JumpStatement*>(var)->copy());
    
    return new Statement(cvar);
}

std::string &Statement::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<LabeledStatement*>(var))
        std::get<LabeledStatement*>(var)->str(res, indent);
    else if(std::holds_alternative<CompoundStatement*>(var))
        std::get<CompoundStatement*>(var)->str(res, indent);
    else if(std::holds_alternative<ExpressionStatement*>(var))
        std::get<ExpressionStatement*>(var)->str(res, indent);
    else if(std::holds_alternative<SelectionStatement*>(var))
        std::get<SelectionStatement*>(var)->str(res, indent);
    else if(std::holds_alternative<IterationStatement*>(var))
        std::get<IterationStatement*>(var)->str(res, indent);
    else if(std::holds_alternative<JumpStatement*>(var))
        std::get<JumpStatement*>(var)->str(res, indent);

    return res;
}

InitializerList::~InitializerList()
{
    for(auto &&s : seq)
    {
        delete s.d;
        delete s.i;
    }
}

InitializerList *InitializerList::copy() const
{
    std::vector<Sd_i> cseq;
    for(auto &&s : seq)
    {
        cseq.emplace_back(s.d != nullptr ? s.d->copy() : nullptr
            , s.i->copy());
    }
    
    return new InitializerList(std::move(cseq));
}

std::string &InitializerList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
    {
        if(seq.front().d != nullptr)
        {
            seq.front().d->str(res, indent);
            res.push_back(' ');
        }
        seq.front().i->str(res, indent);
    }

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += ", ";
        if(seq[i].d != nullptr)
        {
            seq[i].d->str(res, indent);
            res.push_back(' ');
        }
        seq[i].i->str(res, indent);
    }

    return res;
}

LogicalORExpression::~LogicalORExpression()
{
    for(auto &&lande : seq)
        delete lande;
}

LogicalORExpression *LogicalORExpression::copy() const
{
    std::vector<LogicalANDExpression*> cseq;
    for(auto &&lande : seq)
        cseq.push_back(lande->copy());
    
    return new LogicalORExpression(std::move(cseq));
}

std::string &LogicalORExpression::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += " || ";
        seq[i]->str(res, indent);
    }

    return res;
}

Expression::~Expression()
{
    for(auto &&ae : seq)
        delete ae;
}

Expression *Expression::copy() const
{
    std::vector<AssignmentExpression*> cseq;
    for(auto &&ae : seq)
        cseq.push_back(ae->copy());

    return new Expression(std::move(cseq));
}

std::string &Expression::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += ", ";
        seq[i]->str(res, indent);
    }

    return res;
}

StructDeclaration::~StructDeclaration()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Ssql_sdl>(var))
    {
        auto &&s = std::get<Ssql_sdl>(var);
        delete s.sql;
        delete s.sdl;
    }
    else if(std::holds_alternative<Ssad>(var))
    {
        auto &&s = std::get<Ssad>(var);
        delete s.sad;
    }
}

StructDeclaration *StructDeclaration::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Ssql_sdl>(var))
    {
        auto &&s = std::get<Ssql_sdl>(var);
        cvar.emplace<Ssql_sdl>(s.sql->copy()
            , s.sdl != nullptr ? s.sdl->copy() : nullptr);
    }
    else if(std::holds_alternative<Ssad>(var))
    {
        auto &&s = std::get<Ssad>(var);
        cvar.emplace<Ssad>(s.sad->copy());
    }

    return new StructDeclaration(cvar);
}

std::string &StructDeclaration::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Ssql_sdl>(var))
    {
        auto &&s = std::get<Ssql_sdl>(var);
        s.sql->str(res, indent);
        if(s.sdl != nullptr)
        {
            res.push_back(' ');
            s.sdl->str(res, indent);
        }
        res.push_back(';');
    }
    else if(std::holds_alternative<Ssad>(var))
    {
        auto &&s = std::get<Ssad>(var);
        s.sad->str(res, indent);
    }

    return res;
}

Enumerator::~Enumerator()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sec>(var))
    {
        auto &&s = std::get<Sec>(var);
        delete s.ec;
    }
    else if(std::holds_alternative<Sec_ce>(var))
    {
        auto &&s = std::get<Sec_ce>(var);
        delete s.ec;
        delete s.ce;
    }
}

Enumerator *Enumerator::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sec>(var))
    {
        auto &&s = std::get<Sec>(var);
        cvar.emplace<Sec>(s.ec->copy());
    }
    else if(std::holds_alternative<Sec_ce>(var))
    {
        auto &&s = std::get<Sec_ce>(var);
        cvar.emplace<Sec_ce>(s.ec->copy()
            , s.ce->copy());
    }

    return new Enumerator(cvar);
}

std::string &Enumerator::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sec>(var))
    {
        auto &&s = std::get<Sec>(var);
        s.ec->str(res, indent);
    }
    else if(std::holds_alternative<Sec_ce>(var))
    {
        auto &&s = std::get<Sec_ce>(var);
        s.ec->str(res, indent);
        res += " = ";
        s.ce->str(res, indent);
    }

    return res;
}

DirectAbstractDeclarator::~DirectAbstractDeclarator()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sad>(v))
        {
            auto &&s = std::get<Sad>(v);
            delete s.ad;
        }
        else if(std::holds_alternative<Stql_ae>(v))
        {
            auto &&s = std::get<Stql_ae>(v);
            delete s.tql;
            delete s.ae;
        }
        else if(std::holds_alternative<Sp>(v))
            ;
        else if(std::holds_alternative<Sptl>(v))
        {
            auto &&s = std::get<Sptl>(v);
            delete s.ptl;
        }
    }
}

DirectAbstractDeclarator *DirectAbstractDeclarator::copy() const
{
    std::vector<Var> cseq;

    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sad>(v))
        {
            auto &&s = std::get<Sad>(v);
            cv.emplace<Sad>(s.ad->copy());
        }
        else if(std::holds_alternative<Stql_ae>(v))
        {
            auto &&s = std::get<Stql_ae>(v);
            cv.emplace<Stql_ae>(s.tql != nullptr ? s.tql->copy() : nullptr
                , s.ae != nullptr ? s.ae->copy() : nullptr
                , s.hasStatic);
        }
        else if(std::holds_alternative<Sp>(v))
        {
            auto &&s = std::get<Sp>(v);
            cv.emplace<Sp>();
        }
        else if(std::holds_alternative<Sptl>(v))
        {
            auto &&s = std::get<Sptl>(v);
            cv.emplace<Sptl>(s.ptl != nullptr ? s.ptl->copy() : nullptr);
        }

        cseq.push_back(cv);
    }

    return new DirectAbstractDeclarator(std::move(cseq));
}

std::string &DirectAbstractDeclarator::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sad>(v))
        {
            auto &&s = std::get<Sad>(v);
            res.push_back('(');
            s.ad->str(res, indent);
            res.push_back(')');
        }
        else if(std::holds_alternative<Stql_ae>(v))
        {
            auto &&s = std::get<Stql_ae>(v);
            res.push_back('[');
            if(s.hasStatic)
                res += "static ";
            if(s.tql != nullptr)
            {
                s.tql->str(res, indent);
                if(s.ae != nullptr)
                    res.push_back(' ');
            }
            if(s.ae != nullptr)
                s.ae->str(res, indent);
            res.push_back(']');
        }
        else if(std::holds_alternative<Sp>(v))
        {
            auto &&s = std::get<Sp>(v);
            res += "[*]";
        }
        else if(std::holds_alternative<Sptl>(v))
        {
            auto &&s = std::get<Sptl>(v);
            res.push_back('(');
            if(s.ptl != nullptr)
                s.ptl->str(res, indent);
            res.push_back(')');
        }
    }

    return res;
}

PostfixExpression::~PostfixExpression()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Spe>(v))
        {
            auto &&s = std::get<Spe>(v);
            delete s.pe;
        }
        else if(std::holds_alternative<Se>(v))
        {
            auto &&s = std::get<Se>(v);
            delete s.e;
        }
        else if(std::holds_alternative<Sael>(v))
        {
            auto &&s = std::get<Sael>(v);
            delete s.ael;
        }
        else if(std::holds_alternative<Sp_i>(v))
        {
            auto &&s = std::get<Sa_i>(v);
            delete s.i;
        }
        else if(std::holds_alternative<Si>(v)
            || std::holds_alternative<Sd>(v))
            ;
        else if(std::holds_alternative<Stn_il>(v))
        {
            auto &&s = std::get<Stn_il>(v);
            delete s.tn;
            delete s.il;
        }
    }
}

PostfixExpression *PostfixExpression::copy() const
{
    std::vector<Var> cseq;
    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Spe>(v))
        {
            auto &&s = std::get<Spe>(v);
            cv.emplace<Spe>(s.pe->copy());
        }
        else if(std::holds_alternative<Se>(v))
        {
            auto &&s = std::get<Se>(v);
            cv.emplace<Se>(s.e->copy());
        }
        else if(std::holds_alternative<Sael>(v))
        {
            auto &&s = std::get<Sael>(v);
            cv.emplace<Sael>(s.ael != nullptr ? s.ael->copy() : nullptr);
        }
        else if(std::holds_alternative<Sp_i>(v))
        {
            auto &&s = std::get<Sp_i>(v);
            cv.emplace<Sp_i>(s.i->copy());
        }
        else if(std::holds_alternative<Sa_i>(v))
        {
            auto &&s = std::get<Sa_i>(v);
            cv.emplace<Sa_i>(s.i->copy());
        }
        else if(std::holds_alternative<Si>(v))
        {
            auto &&s = std::get<Si>(v);
            cv.emplace<Si>();
        }
        else if(std::holds_alternative<Sd>(v))
        {
            auto &&s = std::get<Sd>(v);
            cv.emplace<Sd>();
        }
        else if(std::holds_alternative<Stn_il>(v))
        {
            auto &&s = std::get<Stn_il>(v);
            cv.emplace<Stn_il>(s.tn->copy()
                , s.il->copy());
        }

        cseq.push_back(cv);
    }

    return new PostfixExpression(std::move(cseq));
}

std::string &PostfixExpression::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Spe>(v))
        {
            auto &&s = std::get<Spe>(v);
            s.pe->str(res, indent);
        }
        else if(std::holds_alternative<Se>(v))
        {
            auto &&s = std::get<Se>(v);
            res.push_back('[');
            s.e->str(res, indent);
            res.push_back(']');
        }
        else if(std::holds_alternative<Sael>(v))
        {
            auto &&s = std::get<Sael>(v);
            res.push_back('(');
            if(s.ael != nullptr)
                s.ael->str(res, indent);
            res.push_back(')');
        }
        else if(std::holds_alternative<Sp_i>(v))
        {
            auto &&s = std::get<Sp_i>(v);
            res.push_back('.');
            s.i->str(res, indent);
        }
        else if(std::holds_alternative<Sa_i>(v))
        {
            auto &&s = std::get<Sa_i>(v);
            res += "->";
            s.i->str(res, indent);
        }
        else if(std::holds_alternative<Si>(v))
            res += " ++";
        else if(std::holds_alternative<Sd>(v))
            res += " --";
        else if(std::holds_alternative<Stn_il>(v))
        {
            auto &&s = std::get<Stn_il>(v);
            res.push_back('(');
            s.tn->str(res, indent);
            res.push_back(')');
            res.push_back('{');
            s.il->str(res, indent);
            res.push_back('}');
        }
    }

    return res;
}

UnaryOperator *UnaryOperator::copy() const
{
    return new UnaryOperator(tag);
}

std::string &UnaryOperator::str(std::string &res, std::size_t &indent) const
{
    switch(tag)
    {
        case(Tag::ADDRESS):
            res.push_back('&');
            break;
        case(Tag::POINTER):
            res.push_back('*');
            break;
        case(Tag::PLUS):
            res.push_back('+');
            break;
        case(Tag::MINUS):
            res.push_back('-');
            break;
        case(Tag::COMPLEMENT):
            res.push_back('~');
            break;
        case(Tag::NOT):
            res.push_back('~');
            break;
        
        default:;
    }

    return res;
}

CastExpression::~CastExpression()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sue>(var))
    {
        auto &&s = std::get<Sue>(var);
        delete s.ue;
    }
    else if(std::holds_alternative<Stn_ce>(var))
    {
        auto &&s = std::get<Stn_ce>(var);
        delete s.tn;
        delete s.ce;
    }
}

CastExpression *CastExpression::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sue>(var))
    {
        auto &&s = std::get<Sue>(var);
        cvar.emplace<Sue>(s.ue->copy());
    }
    else if(std::holds_alternative<Stn_ce>(var))
    {
        auto &&s = std::get<Stn_ce>(var);
        cvar.emplace<Stn_ce>(s.tn->copy()
            , s.ce->copy());
    }

    return new CastExpression(cvar);
}

std::string &CastExpression::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sue>(var))
    {
        auto &&s = std::get<Sue>(var);
        s.ue->str(res, indent);
    }
    else if(std::holds_alternative<Stn_ce>(var))
    {
        auto &&s = std::get<Stn_ce>(var);
        res.push_back('(');
        s.tn->str(res, indent);
        res.push_back(')');
        s.ce->str(res, indent);
    }

    return res;
}

ParameterDeclaration::~ParameterDeclaration()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sds_d>(var))
    {
        auto &&s = std::get<Sds_d>(var);
        delete s.ds;
        delete s.d;
    }
    else if(std::holds_alternative<Sds_ad>(var))
    {
        auto &&s = std::get<Sds_ad>(var);
        delete s.ds;
        delete s.ad;
    }
}

ParameterDeclaration *ParameterDeclaration::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sds_d>(var))
    {
        auto &&s = std::get<Sds_d>(var);
        cvar.emplace<Sds_d>(s.ds->copy()
            , s.d->copy());
    }
    else if(std::holds_alternative<Sds_ad>(var))
    {
        auto &&s = std::get<Sds_ad>(var);
        cvar.emplace<Sds_ad>(s.ds->copy()
            , s.ad != nullptr ? s.ad->copy() : nullptr);
    }
    
    return new ParameterDeclaration(cvar);
}

std::string &ParameterDeclaration::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sds_d>(var))
    {
        auto &&s = std::get<Sds_d>(var);
        s.ds->str(res, indent);
        res.push_back(' ');
        s.d->str(res, indent);
    }
    else if(std::holds_alternative<Sds_ad>(var))
    {
        auto &&s = std::get<Sds_ad>(var);
        s.ds->str(res, indent);
        if(s.ad != nullptr)
        {
            res.push_back(' ');
            s.ad->str(res, indent);
        }
    }

    return res;
}

LabeledStatement::~LabeledStatement()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Si_s>(var))
    {
        auto &&s = std::get<Si_s>(var);
        delete s.i;
        delete s.s;
    }
    else if(std::holds_alternative<Sce_s>(var))
    {
        auto &&s = std::get<Sce_s>(var);
        delete s.ce;
        delete s.s;
    }
    else if(std::holds_alternative<Ss>(var))
    {
        auto &&s = std::get<Ss>(var);
        delete s.s;
    }
}

LabeledStatement *LabeledStatement::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Si_s>(var))
    {
        auto &&s = std::get<Si_s>(var);
        cvar.emplace<Si_s>(s.i->copy()
            , s.s->copy());
    }
    else if(std::holds_alternative<Sce_s>(var))
    {
        auto &&s = std::get<Sce_s>(var);
        cvar.emplace<Sce_s>(s.ce->copy()
            , s.s->copy());
    }
    else if(std::holds_alternative<Ss>(var))
    {
        auto &&s = std::get<Ss>(var);
        cvar.emplace<Ss>(s.s->copy());
    }
    
    return new LabeledStatement(cvar);
}

std::string &LabeledStatement::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Si_s>(var))
    {
        auto &&s = std::get<Si_s>(var);
        s.i->str(res, indent);
        res.push_back(':');
        addLine(res, indent);
        s.s->str(res, indent);
    }
    else if(std::holds_alternative<Sce_s>(var))
    {
        auto &&s = std::get<Sce_s>(var);
        res += "case ";
        s.ce->str(res, indent);
        res.push_back(':');
        addLine(res, indent);
        s.s->str(res, indent);
    }
    else if(std::holds_alternative<Ss>(var))
    {
        auto &&s = std::get<Ss>(var);
        res += "default:";
        addLine(res, indent);
        s.s->str(res, indent);
    }

    return res;
}

ExpressionStatement::~ExpressionStatement()
{
    delete e;
}

ExpressionStatement *ExpressionStatement::copy() const
{
    return new ExpressionStatement(e != nullptr ? e->copy() : nullptr);
}

std::string &ExpressionStatement::str(std::string &res, std::size_t &indent) const
{
    if(e != nullptr)
        e->str(res, indent);
    res.push_back(';');
    return res;
}

SelectionStatement::~SelectionStatement()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Si_e_s>(var))
    {
        auto &&s = std::get<Si_e_s>(var);
        delete s.e;
        delete s.s;
    }
    else if(std::holds_alternative<Si_e_s_s>(var))
    {
        auto &&s = std::get<Si_e_s_s>(var);
        delete s.e;
        delete s.s0;
        delete s.s1;
    }
    else if(std::holds_alternative<Ss_e_s>(var))
    {
        auto &&s = std::get<Ss_e_s>(var);
        delete s.e;
        delete s.s;
    }
}

SelectionStatement *SelectionStatement::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Si_e_s>(var))
    {
        auto &&s = std::get<Si_e_s>(var);
        cvar.emplace<Si_e_s>(s.e->copy()
            , s.s->copy());
    }
    else if(std::holds_alternative<Si_e_s_s>(var))
    {
        auto &&s = std::get<Si_e_s_s>(var);
        cvar.emplace<Si_e_s_s>(s.e->copy()
            , s.s0->copy()
            , s.s1->copy());
    }
    else if(std::holds_alternative<Ss_e_s>(var))
    {
        auto &&s = std::get<Ss_e_s>(var);
        cvar.emplace<Ss_e_s>(s.e->copy()
            , s.s->copy());
    }

    return new SelectionStatement(cvar);
}

std::string &SelectionStatement::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Si_e_s>(var))
    {
        auto &&s = std::get<Si_e_s>(var);
        res += "if(";
        s.e->str(res, indent);
        res.push_back(')');
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent++;
        addLine(res, indent);
        s.s->str(res, indent);
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent--;
    }
    else if(std::holds_alternative<Si_e_s_s>(var))
    {
        auto &&s = std::get<Si_e_s_s>(var);
        res += "if(";
        s.e->str(res, indent);
        res.push_back(')');
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s0->var))
            indent++;
        addLine(res, indent);
        s.s0->str(res, indent);
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s0->var))
            indent--;
        addLine(res, indent);
        res += "else";
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s1->var))
            indent++;
        addLine(res, indent);
        s.s1->str(res, indent);
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s1->var))
            indent--;
    }
    else if(std::holds_alternative<Ss_e_s>(var))
    {
        auto &&s = std::get<Ss_e_s>(var);
        res += "switch(";
        s.e->str(res, indent);
        res.push_back(')');
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent++;
        addLine(res, indent);
        s.s->str(res, indent);
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent--;
    }

    return res;
}

IterationStatement::~IterationStatement()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sw_e_s>(var))
    {
        auto &&s = std::get<Sw_e_s>(var);
        delete s.e;
        delete s.s;
    }
    else if(std::holds_alternative<Sd_s_e>(var))
    {
        auto &&s = std::get<Sd_s_e>(var);
        delete s.s;
        delete s.e;
    }
    else if(std::holds_alternative<Sf_e_e_e_s>(var))
    {
        auto &&s = std::get<Sf_e_e_e_s>(var);
        delete s.e0;
        delete s.e1;
        delete s.e2;
        delete s.s;
    }
    else if(std::holds_alternative<Sf_d_e_e_s>(var))
    {
        auto &&s = std::get<Sf_d_e_e_s>(var);
        delete s.d;
        delete s.e0;
        delete s.e1;
        delete s.s;
    }
}

IterationStatement *IterationStatement::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sw_e_s>(var))
    {
        auto &&s = std::get<Sw_e_s>(var);
        cvar.emplace<Sw_e_s>(s.e->copy()
            , s.s->copy());
    }
    else if(std::holds_alternative<Sd_s_e>(var))
    {
        auto &&s = std::get<Sd_s_e>(var);
        cvar.emplace<Sd_s_e>(s.s->copy()
            , s.e->copy());
    }
    else if(std::holds_alternative<Sf_e_e_e_s>(var))
    {
        auto &&s = std::get<Sf_e_e_e_s>(var);
        cvar.emplace<Sf_e_e_e_s>(s.e0 != nullptr ? s.e0->copy() : nullptr
            , s.e1 != nullptr ? s.e1->copy() : nullptr
            , s.e2 != nullptr ? s.e2->copy() : nullptr
            , s.s->copy());
    }
    else if(std::holds_alternative<Sf_d_e_e_s>(var))
    {
        auto &&s = std::get<Sf_d_e_e_s>(var);
        cvar.emplace<Sf_d_e_e_s>(s.d->copy()
            , s.e0 != nullptr ? s.e0->copy() : nullptr
            , s.e1 != nullptr ? s.e1->copy() : nullptr
            , s.s->copy());
    }

    return new IterationStatement(cvar);
}

std::string &IterationStatement::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sw_e_s>(var))
    {
        auto &&s = std::get<Sw_e_s>(var);
        res += "while(";
        s.e->str(res, indent);
        res.push_back(')');
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent++;
        addLine(res, indent);
        s.s->str(res, indent);
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent--;
    }
    else if(std::holds_alternative<Sd_s_e>(var))
    {
        auto &&s = std::get<Sd_s_e>(var);
        res += "do";
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent++;
        addLine(res, indent);
        s.s->str(res, indent);
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent--;
        addLine(res, indent);
        res += "while(";
        s.e->str(res, indent);
        res += ");";
    }
    else if(std::holds_alternative<Sf_e_e_e_s>(var))
    {
        auto &&s = std::get<Sf_e_e_e_s>(var);
        res += "for(";
        if(s.e0 != nullptr)
            s.e0->str(res, indent);
        res.push_back(';');
        if(s.e1 != nullptr)
            s.e1->str(res, indent);
        res.push_back(';');
        if(s.e2 != nullptr)
            s.e2->str(res, indent);
        res.push_back(')');
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent++;
        addLine(res, indent);
        s.s->str(res, indent);
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent--;
    }
    else if(std::holds_alternative<Sf_d_e_e_s>(var))
    {
        auto &&s = std::get<Sf_d_e_e_s>(var);
        res += "for(";
        s.d->str(res, indent);
        if(s.e0 != nullptr)
            s.e0->str(res, indent);
        res.push_back(';');
        if(s.e1 != nullptr)
            s.e1->str(res, indent);
        res.push_back(')');
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent++;
        addLine(res, indent);
        s.s->str(res, indent);
        if(!std::holds_alternative<TOKEN::CompoundStatement*>(s.s->var))
            indent--;
    }

    return res;
}

JumpStatement::~JumpStatement()
{
    if(std::holds_alternative<std::monostate>(var)
        || std::holds_alternative<Sc>(var)
        || std::holds_alternative<Sb>(var))
        ;
    else if(std::holds_alternative<Sg_i>(var))
    {
        auto &&s = std::get<Sg_i>(var);
        delete s.i;
    }
    else if(std::holds_alternative<Sr_e>(var))
    {
        auto &&s = std::get<Sr_e>(var);
        delete s.e;
    }
}

JumpStatement *JumpStatement::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sg_i>(var))
    {
        auto &&s = std::get<Sg_i>(var);
        cvar.emplace<Sg_i>(s.i->copy());
    }
    else if(std::holds_alternative<Sc>(var))
        cvar.emplace<Sc>();
    else if(std::holds_alternative<Sb>(var))
        cvar.emplace<Sb>();
    else if(std::holds_alternative<Sr_e>(var))
    {
        auto &&s = std::get<Sr_e>(var);
        cvar.emplace<Sr_e>(s.e != nullptr ? s.e->copy() : nullptr);
    }

    return new JumpStatement(cvar);
}

std::string &JumpStatement::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sg_i>(var))
    {
        auto &&s = std::get<Sg_i>(var);
        res += "goto ";
        s.i->str(res, indent);
        res.push_back(';');
    }
    else if(std::holds_alternative<Sc>(var))
        res += "continue;";
    else if(std::holds_alternative<Sb>(var))
        res += "break;";
    else if(std::holds_alternative<Sr_e>(var))
    {
        auto &&s = std::get<Sr_e>(var);
        res += "return";
        if(s.e != nullptr)
        {
            res.push_back(' ');
            s.e->str(res, indent);
        }
        res.push_back(';');
    }

    return res;
}

Designation::~Designation()
{
    delete dl;
}

Designation *Designation::copy() const
{
    return new Designation(dl->copy());
}

std::string &Designation::str(std::string &res, std::size_t &indent) const
{
    dl->str(res, indent);
    res += " =";
    return res;
}

LogicalANDExpression::~LogicalANDExpression()
{
    for(auto &&iore : seq)
        delete iore;
}

LogicalANDExpression *LogicalANDExpression::copy() const
{
    std::vector<InclusiveORExpression*> cseq;
    for(auto &&iore : seq)
        cseq.push_back(iore->copy());
    
    return new LogicalANDExpression(std::move(cseq));
}

std::string &LogicalANDExpression::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);
    
    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += " && ";
        seq[i]->str(res, indent);
    }

    return res;
}

StructDeclaratorList::~StructDeclaratorList()
{
    for(auto &&sd : seq)
        delete sd;
}

StructDeclaratorList *StructDeclaratorList::copy() const
{
    std::vector<StructDeclarator*> cseq;
    for(auto &&sd : seq)
        cseq.push_back(sd->copy());

    return new StructDeclaratorList(std::move(cseq));
}

std::string &StructDeclaratorList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);
    
    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += ", ";
        seq[i]->str(res, indent);
    }

    return res;
}

PrimaryExpression::~PrimaryExpression()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Identifier*>(var))
        delete std::get<Identifier*>(var);
    else if(std::holds_alternative<Constant*>(var))
        delete std::get<Constant*>(var);
    else if(std::holds_alternative<StringLiteral*>(var))
        delete std::get<StringLiteral*>(var);
    else if(std::holds_alternative<Expression*>(var))
        delete std::get<Expression*>(var);
    else if(std::holds_alternative<GenericSelection*>(var))
        delete std::get<GenericSelection*>(var);
}

PrimaryExpression *PrimaryExpression::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Identifier*>(var))
        cvar.emplace<Identifier*>(std::get<Identifier*>(var)->copy());
    else if(std::holds_alternative<Constant*>(var))
        cvar.emplace<Constant*>(std::get<Constant*>(var)->copy());
    else if(std::holds_alternative<StringLiteral*>(var))
        cvar.emplace<StringLiteral*>(std::get<StringLiteral*>(var)->copy());
    else if(std::holds_alternative<Expression*>(var))
        cvar.emplace<Expression*>(std::get<Expression*>(var)->copy());
    else if(std::holds_alternative<GenericSelection*>(var))
        cvar.emplace<GenericSelection*>(std::get<GenericSelection*>(var)->copy());

    return new PrimaryExpression(cvar);
}

std::string &PrimaryExpression::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Identifier*>(var))
        std::get<Identifier*>(var)->str(res, indent);
    else if(std::holds_alternative<Constant*>(var))
        std::get<Constant*>(var)->str(res, indent);
    else if(std::holds_alternative<StringLiteral*>(var))
        std::get<StringLiteral*>(var)->str(res, indent);
    else if(std::holds_alternative<Expression*>(var))
    {
        res.push_back('(');
        std::get<Expression*>(var)->str(res, indent);
        res.push_back(')');
    }
    else if(std::holds_alternative<GenericSelection*>(var))
        std::get<GenericSelection*>(var)->str(res, indent);

    return res;
}

ArgumentExpressionList::~ArgumentExpressionList()
{
    for(auto &&ae : seq)
        delete ae;
}

ArgumentExpressionList *ArgumentExpressionList::copy() const
{
    std::vector<AssignmentExpression*> cseq;
    for(auto &&ae : seq)
        cseq.push_back(ae->copy());
    
    return new ArgumentExpressionList(std::move(cseq));
}

std::string &ArgumentExpressionList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);
    
    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += ", ";
        seq[i]->str(res, indent);
    }

    return res;
}

DesignatorList::~DesignatorList()
{
    for(auto &&d : seq)
        delete d;
}

DesignatorList *DesignatorList::copy() const
{
    std::vector<Designator*> cseq;
    for(auto &&d : seq)
        cseq.push_back(d->copy());

    return new DesignatorList(std::move(cseq));
}

std::string &DesignatorList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res.push_back(' ');
        seq[i]->str(res, indent);
    }

    return res;
}

InclusiveORExpression::~InclusiveORExpression()
{
    for(auto &&eore : seq)
        delete eore;
}

InclusiveORExpression *InclusiveORExpression::copy() const
{
    std::vector<ExclusiveORExpression*> cseq;
    for(auto &&iore : seq)
        cseq.push_back(iore->copy());

    return new InclusiveORExpression(std::move(cseq));
}

std::string &InclusiveORExpression::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += " | ";
        seq[i]->str(res, indent);
    }

    return res;   
}

StructDeclarator::~StructDeclarator()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sd>(var))
    {
        auto &&s = std::get<Sd>(var);
        delete s.d;
    }
    else if(std::holds_alternative<Sd_ce>(var))
    {
        auto &&s = std::get<Sd_ce>(var);
        delete s.d;
        delete s.ce;
    }
}

StructDeclarator *StructDeclarator::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sd>(var))
    {
        auto &&s = std::get<Sd>(var);
        cvar.emplace<Sd>(s.d->copy());
    }
    else if(std::holds_alternative<Sd_ce>(var))
    {
        auto &&s = std::get<Sd_ce>(var);
        cvar.emplace<Sd_ce>(s.d != nullptr ? s.d->copy() : nullptr
            , s.ce->copy());
    }
    
    return new StructDeclarator(cvar);
}

std::string &StructDeclarator::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Sd>(var))
    {
        auto &&s = std::get<Sd>(var);
        s.d->str(res, indent);
    }
    else if(std::holds_alternative<Sd_ce>(var))
    {
        auto &&s = std::get<Sd_ce>(var);
        if(s.d != nullptr)
        {
            s.d->str(res, indent);
            res.push_back(' ');
        }
        res += ": ";
        s.ce->str(res, indent);
    }

    return res;
}

GenericSelection::~GenericSelection()
{
    delete ae;
    delete gal;
}

GenericSelection *GenericSelection::copy() const
{
    return new GenericSelection(ae->copy(), gal->copy());
}

std::string &GenericSelection::str(std::string &res, std::size_t &indent) const
{
    res += "_Generic(";
    ae->str(res, indent);
    res += ", ";
    gal->str(res, indent);
    res.push_back(')');

    return res;
}

Designator::~Designator()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<ConstantExpression*>(var))
        delete std::get<ConstantExpression*>(var);
    else if(std::holds_alternative<Identifier*>(var))
        delete std::get<Identifier*>(var);
}

Designator *Designator::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<ConstantExpression*>(var))
        cvar.emplace<ConstantExpression*>(std::get<ConstantExpression*>(var)->copy());
    else if(std::holds_alternative<Identifier*>(var))
        cvar.emplace<Identifier*>(std::get<Identifier*>(var)->copy());
    
    return new Designator(cvar);
}

std::string &Designator::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<ConstantExpression*>(var))
    {
        res.push_back('[');
        std::get<ConstantExpression*>(var)->str(res, indent);
        res.push_back(']');
    }
    else if(std::holds_alternative<Identifier*>(var))
    {
        res.push_back('.');
        std::get<Identifier*>(var)->str(res, indent);
    }

    return res;
}

ExclusiveORExpression::~ExclusiveORExpression()
{
    for(auto &&ande : seq)
        delete ande;
}

ExclusiveORExpression *ExclusiveORExpression::copy() const
{
    std::vector<ANDExpression*> cseq;
    for(auto &&ande : seq)
        cseq.push_back(ande->copy());

    return new ExclusiveORExpression(std::move(cseq));    
}

std::string &ExclusiveORExpression::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += " ^ ";
        seq[i]->str(res, indent);
    }

    return res; 
}

GenericAssocList::~GenericAssocList()
{
    for(auto &&ga : seq)
        delete ga;
}

GenericAssocList *GenericAssocList::copy() const
{
    std::vector<GenericAssociation*> cseq;
    for(auto &&ga : seq)
        cseq.push_back(ga->copy());

    return new GenericAssocList(std::move(cseq));    
}

std::string &GenericAssocList::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += ", ";
        seq[i]->str(res, indent);
    }

    return res;
}

ANDExpression::~ANDExpression()
{
    for(auto &&ee : seq)
        delete ee;
}

ANDExpression *ANDExpression::copy() const
{
    std::vector<EqualityExpression*> cseq;
    for(auto &&ee : seq)
        cseq.push_back(ee->copy());

    return new ANDExpression(std::move(cseq));        
}

std::string &ANDExpression::str(std::string &res, std::size_t &indent) const
{
    if(!seq.empty())
        seq.front()->str(res, indent);

    for(std::size_t i = 1; i < seq.size(); i++)
    {
        res += " & ";
        seq[i]->str(res, indent);
    }

    return res;
}

GenericAssociation::~GenericAssociation()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Stn_ae>(var))
    {
        auto &&s = std::get<Stn_ae>(var);
        delete s.tn;
        delete s.ae;
    }
    else if(std::holds_alternative<Sae>(var))
    {
        auto &&s = std::get<Sae>(var);
        delete s.ae;
    }
}

GenericAssociation *GenericAssociation::copy() const
{
    Var cvar;
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Stn_ae>(var))
    {
        auto &&s = std::get<Stn_ae>(var);
        cvar.emplace<Stn_ae>(s.tn->copy()
            , s.ae->copy());
    }
    else if(std::holds_alternative<Sae>(var))
    {
        auto &&s = std::get<Sae>(var);
        cvar.emplace<Sae>(s.ae->copy());
    }

    return new GenericAssociation(cvar);
}

std::string &GenericAssociation::str(std::string &res, std::size_t &indent) const
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<Stn_ae>(var))
    {
        auto &&s = std::get<Stn_ae>(var);
        s.tn->str(res, indent);
        res += " : ";
        s.ae->str(res, indent);
    }
    else if(std::holds_alternative<Sae>(var))
    {
        auto &&s = std::get<Sae>(var);
        res += "default : ";
        s.ae->str(res, indent);
    }

    return res;
}

EqualityExpression::~EqualityExpression()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sre>(v))
        {
            auto &&s = std::get<Sre>(v);
            delete s.re;
        }
        else if(std::holds_alternative<Se_re>(v))
        {
            auto &&s = std::get<Se_re>(v);
            delete s.re;
        }
        else if(std::holds_alternative<Sne_re>(v))
        {
            auto &&s = std::get<Sne_re>(v);
            delete s.re;
        }
    }
}

EqualityExpression *EqualityExpression::copy() const
{
    std::vector<Var> cseq;
    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sre>(v))
        {
            auto &&s = std::get<Sre>(v);
            cv.emplace<Sre>(s.re->copy());
        }
        else if(std::holds_alternative<Se_re>(v))
        {
            auto &&s = std::get<Se_re>(v);
            cv.emplace<Se_re>(s.re->copy());
        }
        else if(std::holds_alternative<Sne_re>(v))
        {
            auto &&s = std::get<Sne_re>(v);
            cv.emplace<Sne_re>(s.re->copy());
        }

        cseq.push_back(cv);
    }

    return new EqualityExpression(std::move(cseq));
}

std::string &EqualityExpression::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sre>(v))
        {
            auto &&s = std::get<Sre>(v);
            s.re->str(res, indent);
        }
        else if(std::holds_alternative<Se_re>(v))
        {
            auto &&s = std::get<Se_re>(v);
            res += " == ";
            s.re->str(res, indent);
        }
        else if(std::holds_alternative<Sne_re>(v))
        {
            auto &&s = std::get<Sne_re>(v);
            res += " != ";
            s.re->str(res, indent);
        }
    }

    return res;
}

RelationalExpression::~RelationalExpression()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sse>(v))
        {
            auto &&s = std::get<Sse>(v);
            delete s.se;
        }
        else if(std::holds_alternative<Sl_se>(v))
        {
            auto &&s = std::get<Sl_se>(v);
            delete s.se;
        }
        else if(std::holds_alternative<Sg_se>(v))
        {
            auto &&s = std::get<Sg_se>(v);
            delete s.se;
        }
        else if(std::holds_alternative<Sle_se>(v))
        {
            auto &&s = std::get<Sle_se>(v);
            delete s.se;
        }
        else if(std::holds_alternative<Sge_se>(v))
        {
            auto &&s = std::get<Sge_se>(v);
            delete s.se;
        }
    }
}

RelationalExpression *RelationalExpression::copy() const
{
    std::vector<Var> cseq;
    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sse>(v))
        {
            auto &&s = std::get<Sse>(v);
            cv.emplace<Sse>(s.se->copy());
        }
        else if(std::holds_alternative<Sl_se>(v))
        {
            auto &&s = std::get<Sl_se>(v);
            cv.emplace<Sl_se>(s.se->copy());
        }
        else if(std::holds_alternative<Sg_se>(v))
        {
            auto &&s = std::get<Sg_se>(v);
            cv.emplace<Sg_se>(s.se->copy());
        }
        else if(std::holds_alternative<Sle_se>(v))
        {
            auto &&s = std::get<Sle_se>(v);
            cv.emplace<Sle_se>(s.se->copy());
        }
        else if(std::holds_alternative<Sge_se>(v))
        {
            auto &&s = std::get<Sge_se>(v);
            cv.emplace<Sge_se>(s.se->copy());
        }

        cseq.push_back(cv);
    }

    return new RelationalExpression(std::move(cseq));
}

std::string &RelationalExpression::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sse>(v))
        {
            auto &&s = std::get<Sse>(v);
            s.se->str(res, indent);
        }
        else if(std::holds_alternative<Sl_se>(v))
        {
            auto &&s = std::get<Sl_se>(v);
            res += " < ";
            s.se->str(res, indent);
        }
        else if(std::holds_alternative<Sg_se>(v))
        {
            auto &&s = std::get<Sg_se>(v);
            res += " > ";
            s.se->str(res, indent);
        }
        else if(std::holds_alternative<Sle_se>(v))
        {
            auto &&s = std::get<Sle_se>(v);
            res += " <= ";
            s.se->str(res, indent);
        }
        else if(std::holds_alternative<Sge_se>(v))
        {
            auto &&s = std::get<Sge_se>(v);
            res += " >= ";
            s.se->str(res, indent);
        }
    }

    return res;
}

ShiftExpression::~ShiftExpression()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sae>(v))
        {
            auto &&s = std::get<Sae>(v);
            delete s.ae;
        }
        else if(std::holds_alternative<Sl_ae>(v))
        {
            auto &&s = std::get<Sl_ae>(v);
            delete s.ae;
        }
        else if(std::holds_alternative<Sr_ae>(v))
        {
            auto &&s = std::get<Sr_ae>(v);
            delete s.ae;
        }
    }
}

ShiftExpression *ShiftExpression::copy() const
{
    std::vector<Var> cseq;
    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sae>(v))
        {
            auto &&s = std::get<Sae>(v);
            cv.emplace<Sae>(s.ae->copy());
        }
        else if(std::holds_alternative<Sl_ae>(v))
        {
            auto &&s = std::get<Sl_ae>(v);
            cv.emplace<Sl_ae>(s.ae->copy());
        }
        else if(std::holds_alternative<Sr_ae>(v))
        {
            auto &&s = std::get<Sr_ae>(v);
            cv.emplace<Sr_ae>(s.ae->copy());
        }

        cseq.push_back(cv);
    }

    return new ShiftExpression(std::move(cseq));
}

std::string &ShiftExpression::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sae>(v))
        {
            auto &&s = std::get<Sae>(v);
            s.ae->str(res, indent);
        }
        else if(std::holds_alternative<Sl_ae>(v))
        {
            auto &&s = std::get<Sl_ae>(v);
            res += " << ";
            s.ae->str(res, indent);
        }
        else if(std::holds_alternative<Sr_ae>(v))
        {
            auto &&s = std::get<Sr_ae>(v);
            res += " >> ";
            s.ae->str(res, indent);
        }
    }

    return res;
}

AdditiveExpression::~AdditiveExpression()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sme>(v))
        {
            auto &&s = std::get<Sme>(v);
            delete s.me;
        }
        else if(std::holds_alternative<Sa_me>(v))
        {
            auto &&s = std::get<Sa_me>(v);
            delete s.me;
        
        }
        else if(std::holds_alternative<Ss_me>(v))
        {
            auto &&s = std::get<Ss_me>(v);
            delete s.me;
        }
    }
}

AdditiveExpression *AdditiveExpression::copy() const
{
    std::vector<Var> cseq;
    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sme>(v))
        {
            auto &&s = std::get<Sme>(v);
            cv.emplace<Sme>(s.me->copy());
        }
        else if(std::holds_alternative<Sa_me>(v))
        {
            auto &&s = std::get<Sa_me>(v);
            cv.emplace<Sa_me>(s.me->copy());
        }
        else if(std::holds_alternative<Ss_me>(v))
        {
            auto &&s = std::get<Ss_me>(v);
            cv.emplace<Ss_me>(s.me->copy());
        }

        cseq.push_back(cv);
    }

    return new AdditiveExpression(std::move(cseq));
}

std::string &AdditiveExpression::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sme>(v))
        {
            auto &&s = std::get<Sme>(v);
            s.me->str(res, indent);
        }
        else if(std::holds_alternative<Sa_me>(v))
        {
            auto &&s = std::get<Sa_me>(v);
            res += " + ";
            s.me->str(res, indent);
        }
        else if(std::holds_alternative<Ss_me>(v))
        {
            auto &&s = std::get<Ss_me>(v);
            res += " - ";
            s.me->str(res, indent);
        }
    }

    return res;
}

MultiplicativeExpression::~MultiplicativeExpression()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sce>(v))
        {
            auto &&s = std::get<Sce>(v);
            delete s.ce;
        }
        else if(std::holds_alternative<Sm_ce>(v))
        {
            auto &&s = std::get<Sm_ce>(v);
            delete s.ce;
        }
        else if(std::holds_alternative<Sd_ce>(v))
        {
            auto &&s = std::get<Sd_ce>(v);
            delete s.ce;
        }
        else if(std::holds_alternative<Sr_ce>(v))
        {
            auto &&s = std::get<Sr_ce>(v);
            delete s.ce;
        }
    }
}

MultiplicativeExpression *MultiplicativeExpression::copy() const
{
    std::vector<Var> cseq;
    for(auto &&v : seq)
    {
        Var cv;
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sce>(v))
        {
            auto &&s = std::get<Sce>(v);
            cv.emplace<Sce>(s.ce->copy());
        }
        else if(std::holds_alternative<Sm_ce>(v))
        {
            auto &&s = std::get<Sm_ce>(v);
            cv.emplace<Sm_ce>(s.ce->copy());
        }
        else if(std::holds_alternative<Sd_ce>(v))
        {
            auto &&s = std::get<Sd_ce>(v);
            cv.emplace<Sd_ce>(s.ce->copy());
        }
        else if(std::holds_alternative<Sr_ce>(v))
        {
            auto &&s = std::get<Sr_ce>(v);
            cv.emplace<Sr_ce>(s.ce->copy());
        }

        cseq.push_back(cv);
    }

    return new MultiplicativeExpression(std::move(cseq));    
}

std::string &MultiplicativeExpression::str(std::string &res, std::size_t &indent) const
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::monostate>(v))
            ;
        else if(std::holds_alternative<Sce>(v))
        {
            auto &&s = std::get<Sce>(v);
            s.ce->str(res, indent);
        }
        else if(std::holds_alternative<Sm_ce>(v))
        {
            auto &&s = std::get<Sm_ce>(v);
            res += " * ";
            s.ce->str(res, indent);
        }
        else if(std::holds_alternative<Sd_ce>(v))
        {
            auto &&s = std::get<Sd_ce>(v);
            res += " / ";
            s.ce->str(res, indent);
        }
        else if(std::holds_alternative<Sr_ce>(v))
        {
            auto &&s = std::get<Sr_ce>(v);
            res += " % ";
            s.ce->str(res, indent);
        }
    }

    return res;
}

std::string &addLine(std::string &str, std::size_t &indent)
{
    str.push_back('\n');
    str += std::string(4 * indent, ' ');
    return str;
}

}