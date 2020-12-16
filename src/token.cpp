#include "token.hpp"

namespace TOKEN
{

Token::~Token()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

Identifier::~Identifier()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::nullptr_t>(v))
            ;
        else if(std::holds_alternative<IdentifierNondigit*>(v))
            delete std::get<IdentifierNondigit*>(v);
        else if(std::holds_alternative<Digit*>(v))
            delete std::get<Digit*>(v);
    }
}

Constant::~Constant()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

StringLiteral::~StringLiteral()
{
    delete ep;
    delete scs;
}

IdentifierNondigit::~IdentifierNondigit()
{
    if(std::holds_alternative<std::nullptr_t>(var))
        ;
    else if(std::holds_alternative<Nondigit*>(var))
        delete std::get<Nondigit*>(var);
    else if(std::holds_alternative<UniversalCharacterName*>(var))
        delete std::get<UniversalCharacterName*>(var);
}

IntegerConstant::~IntegerConstant()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

FloatingConstant::~FloatingConstant()
{
    if(std::holds_alternative<std::nullptr_t>(var))
        ;
    else if(std::holds_alternative<DecimalFloatingConstant*>(var))
        delete std::get<DecimalFloatingConstant*>(var);
    else if(std::holds_alternative<HexadecimalFloatingConstant*>(var))
        delete std::get<HexadecimalFloatingConstant*>(var);
}

EnumerationConstant::~EnumerationConstant()
{
    delete i;
}

CharacterConstant::~CharacterConstant()
{
    delete ccs;
}

SCharSequence::~SCharSequence()
{
    for(auto &&sc : seq)
        delete sc;
}

UniversalCharacterName::~UniversalCharacterName()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

DecimalConstant::~DecimalConstant()
{
    delete nd;
    for(auto &&d : seq)
        delete d;
}

OctalConstant::~OctalConstant()
{
    for(auto &&od : seq)
        delete od;
}

HexadecimalConstant::~HexadecimalConstant()
{
    delete hp;
    for(auto &&hd : seq)
        delete hd;
}

DecimalFloatingConstant::~DecimalFloatingConstant()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

HexadecimalFloatingConstant::~HexadecimalFloatingConstant()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

CCharSequence::~CCharSequence()
{
    for(auto &&cc : seq)
        delete cc;
}

SChar::~SChar()
{
    if(std::holds_alternative<std::nullptr_t>(var)
        || std::holds_alternative<char>(var))
        ;
    else if(std::holds_alternative<EscapeSequence*>(var))
        delete std::get<EscapeSequence*>(var);
}

HexQuad::~HexQuad()
{
    for(auto &&hd : arr)
        delete hd;
}

FractionalConstant::~FractionalConstant()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

ExponentPart::~ExponentPart()
{
    delete s;
    delete ds;
}

DigitSequence::~DigitSequence()
{
    for(auto &&d : seq)
        delete d;
}

HexadecimalFractionalConstant::~HexadecimalFractionalConstant()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

BinaryExponentPart::~BinaryExponentPart()
{
    delete s;
    delete ds;
}

HexadecimalDigitSequence::~HexadecimalDigitSequence()
{
    for(auto &&hd : seq)
        delete hd;
}

CChar::~CChar()
{
    if(std::holds_alternative<std::nullptr_t>(var)
        || std::holds_alternative<char>(var))
        ;
    else if(std::holds_alternative<EscapeSequence*>(var))
        delete std::get<EscapeSequence*>(var);
}

EscapeSequence::~EscapeSequence()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

OctalEscapeSequence::~OctalEscapeSequence()
{
    for(auto &&od : seq)
        delete od;
}

HexadecimalEscapeSequence::~HexadecimalEscapeSequence()
{
    for(auto &&hd : seq)
        delete hd;
}

PreprocessingToken::~PreprocessingToken()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

PPNumber::~PPNumber()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<std::nullptr_t>(v)
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

IntegerSuffix::~IntegerSuffix()
{
    if(std::holds_alternative<std::nullptr_t>(var))
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

}