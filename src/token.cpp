#include "token.hpp"

namespace TOKEN
{

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

Keyword *Keyword::copy() const
{
    return new Keyword(tag);
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

Punctuator *Punctuator::copy() const
{
    return new Punctuator(tag);
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

Digit *Digit::copy() const
{
    return new Digit(c);
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

EnumerationConstant::~EnumerationConstant()
{
    delete i;
}

EnumerationConstant *EnumerationConstant::copy() const
{
    return new EnumerationConstant(i->copy());
}

CharacterConstant::~CharacterConstant()
{
    delete ccs;
}

CharacterConstant *CharacterConstant::copy() const
{
    return new CharacterConstant(tag, ccs->copy());
}

EncodingPrefix *EncodingPrefix::copy() const
{
    return new EncodingPrefix(tag);
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

Nondigit *Nondigit::copy() const
{
    return new Nondigit(c);
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

NonzeroDigit *NonzeroDigit::copy() const
{
    return new NonzeroDigit(c);
}

OctalDigit *OctalDigit::copy() const
{
    return new OctalDigit(c);
}

HexadecimalPrefix *HexadecimalPrefix::copy() const
{
    return new HexadecimalPrefix(tag);
}

HexadecimalDigit *HexadecimalDigit::copy() const
{
    return new HexadecimalDigit(c);
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

Sign *Sign::copy() const
{
    return new Sign(tag);
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

FloatingSuffix *FloatingSuffix::copy() const
{
    return new FloatingSuffix(tag);
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

SimpleEscapeSequence *SimpleEscapeSequence::copy() const
{
    return new SimpleEscapeSequence(c);
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

UnsignedSuffix *UnsignedSuffix::copy() const
{
    return new UnsignedSuffix(tag);
}

LongSuffix *LongSuffix::copy() const
{
    return new LongSuffix(tag);
}

LongLongSuffix *LongLongSuffix::copy() const
{
    return new LongLongSuffix(tag);
}

TranslationUnit::~TranslationUnit()
{
    for(auto &&ed : seq)
        delete ed;
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

FunctionDefinition::~FunctionDefinition()
{
    delete ds;
    delete d;
    delete dl;
    delete cs;
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

Declarator::~Declarator()
{
    delete p;
    delete dd;
}

DeclarationList::~DeclarationList()
{
    for(auto &&d : seq)
        delete d;
}

CompoundStatement::~CompoundStatement()
{
    delete bil;
}

InitDeclaratorList::~InitDeclaratorList()
{
    for(auto &&id : seq)
        delete id;
}

StaticAssertDeclaration::~StaticAssertDeclaration()
{
    delete ce;
    delete sl;
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

AlignmentSpecifier::~AlignmentSpecifier()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<TypeName*>(var))
        delete std::get<TypeName*>(var);
    else if(std::holds_alternative<ConstantExpression*>(var))
        delete std::get<ConstantExpression*>(var);
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

BlockItemList::~BlockItemList()
{
    for(auto &&bi : seq)
        delete bi;
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

ConstantExpression::~ConstantExpression()
{
    delete ce;
}

AtomicTypeSpecifier::~AtomicTypeSpecifier()
{
    delete tn;
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

TypedefName::~TypedefName()
{
    delete i;
}

TypeName::~TypeName()
{
    delete sql;
    delete ad;
}

TypeQualifierList::~TypeQualifierList()
{
    for(auto &&tq : seq)
        delete tq;
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

ParameterTypeList::~ParameterTypeList()
{
    delete pl;
}

IdentifierList::~IdentifierList()
{
    for(auto &&i : seq)
        delete i;
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

Initializer::~Initializer()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
    else if(std::holds_alternative<AssignmentExpression*>(var))
        delete std::get<AssignmentExpression*>(var);
    else if(std::holds_alternative<InitializerList*>(var))
        delete std::get<InitializerList*>(var);
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

StructDeclarationList::~StructDeclarationList()
{
    for(auto &&sd : seq)
        delete sd;
}

EnumeratorList::~EnumeratorList()
{
    for(auto &&e : seq)
        delete e;
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

UnaryExpression::~UnaryExpression()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
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

ParameterList::~ParameterList()
{
    for(auto &&pd : seq)
        delete pd;
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

InitializerList::~InitializerList()
{
    for(auto &&s : seq)
    {
        delete s.d;
        delete s.i;
    }
}

LogicalORExpression::~LogicalORExpression()
{
    for(auto &&lande : seq)
        delete lande;
}

Expression::~Expression()
{
    for(auto &&ae : seq)
        delete ae;
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

LabeledStatement::~LabeledStatement()
{
    if(std::holds_alternative<std::monostate>(var))
        ;
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

ExpressionStatement::~ExpressionStatement()
{
    delete e;
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

Designation::~Designation()
{
    delete dl;
}

LogicalANDExpression::~LogicalANDExpression()
{
    for(auto &&iore : seq)
        delete iore;
}

StructDeclaratorList::~StructDeclaratorList()
{
    for(auto &&sd : seq)
        delete sd;
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

ArgumentExpressionList::~ArgumentExpressionList()
{
    for(auto &&ae : seq)
        delete ae;
}

DesignatorList::~DesignatorList()
{
    for(auto &&d : seq)
        delete d;
}

InclusiveORExpression::~InclusiveORExpression()
{
    for(auto &&eore : seq)
        delete eore;
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

GenericSelection::~GenericSelection()
{
    delete ae;
    delete gal;
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

ExclusiveORExpression::~ExclusiveORExpression()
{
    for(auto &&ande : seq)
        delete ande;
}

GenericAssocList::~GenericAssocList()
{
    for(auto &&ga : seq)
        delete ga;
}

ANDExpression::~ANDExpression()
{
    for(auto &&ee : seq)
        delete ee;
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

}