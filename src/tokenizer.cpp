#include <utility>
#include <array>

#include "tokenizer.hpp"

namespace TOKENIZER
{

using namespace TOKEN;

PreprocessingToken *decPreprocessingToken(const std::string &src
    , std::size_t &idx)
{
    PreprocessingToken::Variant var;

    if((var = decPPNumber(src, idx), std::get<PPNumber*>(var) != nullptr)
        || (var = decCharacterConstant(src, idx), std::get<CharacterConstant*>(var) != nullptr)
        || (var = decStringLiteral(src, idx), std::get<StringLiteral*>(var) != nullptr)
        || (var = decIdentifier(src, idx), std::get<Identifier*>(var) != nullptr)
        || (var = decPunctuator(src, idx), std::get<Punctuator*>(var) != nullptr))
        return new PreprocessingToken(var);
    else
        return nullptr;
}

Identifier *decIdentifier(const std::string &src
    , std::size_t &idx)
{
    Identifier::Element var;
    if(var.emplace<IdentifierNondigit*>(decIdentifierNondigit(src, idx)) == nullptr)
        return nullptr;

    Identifier::Seq seq;
    seq.push_back(var);

    while(var.emplace<IdentifierNondigit*>(decIdentifierNondigit(src, idx)) != nullptr
        || var.emplace<Digit*>(decDigit(src, idx)) != nullptr)
        seq.push_back(var);
    
    return new Identifier(std::move(seq));
}

PPNumber *decPPNumber(const std::string &src
    , std::size_t &idx)
{
    std::vector<PPNumber::Variant> seq;

    PPNumber::Variant var = decDigit(src, idx);
    if(std::get<Digit*>(var) != nullptr)
        seq.push_back(var);
    else if(idx < src.size() && src[idx] == '.')
    {
        idx++;
        if(var = decDigit(src, idx), std::get<Digit*>(var) != nullptr)
        {
            seq.emplace_back(PPNumber::Tag::PERIOD);
            seq.push_back(var);
        }
        else
            idx--;
    }

    if(seq.empty())
        return nullptr;

    while(idx < src.size())
    {
        if(src[idx] == '.' && (idx++, true))
            seq.emplace_back(PPNumber::Tag::PERIOD);
        else if(PPNumber::Variant v = PPNumber::Tag::NONE;
            (src[idx] == 'e' && (v = PPNumber::Tag::e, true))
            || (src[idx] == 'E' && (v = PPNumber::Tag::E, true))
            || (src[idx] == 'p' && (v = PPNumber::Tag::p, true))
            || (src[idx] == 'P' && (v = PPNumber::Tag::P, true))
            , std::get<PPNumber::Tag>(v) != PPNumber::Tag::NONE
                && (idx++, true))
        {
            if(var = decSign(src, idx), std::get<Sign*>(var) != nullptr)
            {
                seq.push_back(v);
                seq.push_back(var);
            }
            else if(idx--, var = decIdentifierNondigit(src, idx), std::get<IdentifierNondigit*>(var) != nullptr)
                seq.push_back(var);
            else
                break;
        }
        else if((var = decDigit(src, idx), std::get<Digit*>(var) != nullptr)
            || (var = decIdentifierNondigit(src, idx), std::get<IdentifierNondigit*>(var) != nullptr))
            seq.push_back(var);
        else
            break;
    }

    return new PPNumber(std::move(seq));
}

CharacterConstant *decCharacterConstant(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    CharacterConstant::Tag tag = CharacterConstant::Tag::NONE;

    if(idx < src.size() && 
        ((src[idx] == 'L' && (tag = CharacterConstant::Tag::L, true))
            || src[idx] == 'u' && (tag = CharacterConstant::Tag::u, true)
            || src[idx] == 'U' && (tag = CharacterConstant::Tag::U, true)))
        idx++;
    
    if(idx < src.size() && src[idx] == '\'' && (idx++, true))
    {
        CCharSequence *ccs = decCCharSequence(src, idx);
        if(ccs != nullptr
            && idx < src.size() && src[idx] == '\'' && (idx++, true))
            return new CharacterConstant(tag, ccs);
        else
            delete ccs;
    }

    idx = pre;
    return nullptr;
}

StringLiteral *decStringLiteral(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    EncodingPrefix *ep = decEncodingPrefix(src, idx);
    if(idx < src.size() && src[idx] == '\"' && (idx++, true))
    {
        SCharSequence *scs = decSCharSequence(src, idx);
        if(idx < src.size() && src[idx] == '\"' && (idx++, true))
            return new StringLiteral(ep, scs);
        else
            delete scs;
    }

    delete ep;
    idx = pre;
    return nullptr;
}

Punctuator *decPunctuator(const std::string &src
    , std::size_t &idx)
{
    if(idx >= src.size())
        return nullptr;

    std::string sub = src.substr(idx, 4);
    
    while(!sub.empty())
    {
        if(auto iter = PUNCTUATOR_MAP.find(sub);
            iter != PUNCTUATOR_MAP.end() && (idx += sub.size(), true))
            return new Punctuator(iter->second);
        else
            sub.pop_back();
    }

    return nullptr;
}

IdentifierNondigit *decIdentifierNondigit(const std::string &src
    , std::size_t &idx)
{
    if(IdentifierNondigit::Variant var;
        var.emplace<Nondigit*>(decNondigit(src, idx)) != nullptr
            || var.emplace<UniversalCharacterName*>(decUniversalCharacterName(src, idx)) != nullptr)
        return new IdentifierNondigit(var);
    else
        return nullptr;
}

Digit *decDigit(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size()
        && src[idx] >= '0' && src[idx] <= '9'
        && (idx++, true))
        return new Digit(src[idx - 1]);
    else
        return nullptr;
}

Sign *decSign(const std::string &src
    , std::size_t &idx)
{
    if(Sign::Tag tag = Sign::Tag::NONE;
        idx < src.size()
            && ((src[idx] == '+' && (tag = Sign::Tag::PLUS, true))
                || (src[idx] == '-' && (tag = Sign::Tag::MINUS, true)))
            && (idx++, true))
        return new Sign(tag);
    else
        return nullptr;
}

CCharSequence *decCCharSequence(const std::string &src
    , std::size_t &idx)
{
    std::vector<CChar*> seq;

    for(auto cc = decCChar(src, idx);
        cc != nullptr;
        cc = decCChar(src, idx))
        seq.push_back(cc);

    if(!seq.empty())
        return new CCharSequence(std::move(seq));
    else
        return nullptr;
}

EncodingPrefix *decEncodingPrefix(const std::string &src
    , std::size_t &idx)
{
    if(idx >= src.size())
        return nullptr;

    EncodingPrefix::Tag tag = EncodingPrefix::Tag::NONE;
    if(src[idx] == 'u' && (idx++, true))
    {
        if(idx < src.size() && src[idx] == '8' && (idx++, true))
            tag = EncodingPrefix::Tag::u8;
        else
            tag = EncodingPrefix::Tag::u;
    }
    else if((src[idx] == 'U' && (tag = EncodingPrefix::Tag::U, true))
        || (src[idx] == 'L' && (tag = EncodingPrefix::Tag::L, true)))
        idx++;
    
    if(tag != EncodingPrefix::Tag::NONE)
        return new EncodingPrefix(tag);
    else
        return nullptr;
}

SCharSequence *decSCharSequence(const std::string &src
    , std::size_t &idx)
{
    std::vector<SChar*> seq;

    for(auto sc = decSChar(src, idx);
        sc != nullptr;
        sc = decSChar(src, idx))
        seq.push_back(sc);

    if(!seq.empty())
        return new SCharSequence(std::move(seq));
    else
        return nullptr;    
}

Nondigit *decNondigit(const std::string &src
    , std::size_t &idx)
{
    if(idx >= src.size())
        return nullptr;
    
    if(((src[idx] >= 'a' && src[idx] <= 'z')
        || (src[idx] >= 'A' && src[idx] <= 'Z')
        || (src[idx] == '_'))
        && (idx++, true))
        return new Nondigit(src[idx - 1]);
    else
        return nullptr;
}

UniversalCharacterName *decUniversalCharacterName(const std::string &src
    , std::size_t &idx)
{
    if(idx + 2 >= src.size())
        return nullptr;

    std::size_t pre = idx;

    if(src[idx] == '\\' && (idx++, true))
    {
        UniversalCharacterName::Variant var;
        if(src[idx] == 'u' && (idx++, true))
        {
            if(var.emplace<UniversalCharacterName::Su_hq>(decHexQuad(src, idx)), std::get<UniversalCharacterName::Su_hq>(var).hq != nullptr)
                return new UniversalCharacterName(var);
            else
                delete std::get<UniversalCharacterName::Su_hq>(var).hq;
        }
        else if(src[idx] == 'U' && (idx++, true))
        {
            if(var.emplace<UniversalCharacterName::SU_hq_hq>(nullptr, nullptr),
                (std::get<UniversalCharacterName::SU_hq_hq>(var).hq0 = decHexQuad(src, idx)) != nullptr
                && (std::get<UniversalCharacterName::SU_hq_hq>(var).hq1 = decHexQuad(src, idx)) != nullptr)
                return new UniversalCharacterName(var);
            else
            {
                delete std::get<UniversalCharacterName::SU_hq_hq>(var).hq0;
                delete std::get<UniversalCharacterName::SU_hq_hq>(var).hq1;
            }
        }
    }

    idx = pre;
    return nullptr;
}

CChar *decCChar(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size()
        && src[idx] != '\''
        && src[idx] != '\\'
        && src[idx] != '\n'
        && (idx++, true))
        return new CChar(src[idx - 1]);
    else if(CChar::Variant var = decEscapeSequence(src, idx);
        std::get<EscapeSequence*>(var) != nullptr)
        return new CChar(var);
    else
        return nullptr;
}

SChar *decSChar(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size()
        && src[idx] != '\"'
        && src[idx] != '\\'
        && src[idx] != '\n'
        && (idx++, true))
        return new SChar(src[idx - 1]);
    else if(EscapeSequence *es = decEscapeSequence(src, idx);
        es != nullptr)
        return new SChar(es);
    else
        return nullptr;
}

HexQuad *decHexQuad(const std::string &src
    , std::size_t &idx)
{
    std::array<HexadecimalDigit*, 4> arr;
    arr.fill(nullptr);

    bool isValid = true;
    for(std::size_t i = 0; i < arr.size(); i++)
    {
        if((arr[i] = decHexadecimalDigit(src, idx)) == nullptr
            && (isValid = false, true))
            break;
    }

    if(isValid)
        return new HexQuad(std::move(arr));
    else
    {
        for(auto &&hd : arr)
            delete hd;
        return nullptr;
    }
}

EscapeSequence *decEscapeSequence(const std::string &src
    , std::size_t &idx)
{
    if(EscapeSequence::Variant var;
        var.emplace<SimpleEscapeSequence*>(decSimpleEscapeSequence(src, idx)) != nullptr
        || var.emplace<OctalEscapeSequence*>(decOctalEscapeSequence(src, idx)) != nullptr
        || var.emplace<HexadecimalEscapeSequence*>(decHexadecimalEscapeSequence(src, idx)) != nullptr
        || var.emplace<UniversalCharacterName*>(decUniversalCharacterName(src, idx)) != nullptr)
        return new EscapeSequence(var);
    else
        return nullptr;
}

HexadecimalDigit *decHexadecimalDigit(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size()
        && ((src[idx] >= '0' && src[idx] <= '9')
            || (src[idx] >= 'a' && src[idx] <= 'f')
            || (src[idx] >= 'A' && src[idx] <= 'F'))
        && (idx++, true))
        return new HexadecimalDigit(src[idx - 1]);
    else
        return nullptr;
}

SimpleEscapeSequence *decSimpleEscapeSequence(const std::string &src
    , std::size_t &idx)
{
    if(idx + 1 < src.size()
        && src[idx] == '\\'
        && (src[idx + 1] == '\''
            || src[idx + 1] == '\"'
            || src[idx + 1] == '\?'
            || src[idx + 1] == '\\'
            || src[idx + 1] == 'a'
            || src[idx + 1] == 'b'
            || src[idx + 1] == 'f'
            || src[idx + 1] == 'n'
            || src[idx + 1] == 'r'
            || src[idx + 1] == 't'
            || src[idx + 1] == 'v')
        && (idx += 2, true))
        return new SimpleEscapeSequence(src[idx - 1]);
    else
        return nullptr;
}

OctalEscapeSequence *decOctalEscapeSequence(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size()
        && src[idx] == '\\'
        && (idx++, true))
    {
        std::vector<OctalDigit*> seq;
        for(int i = 0; i < 3; i++)
        {
            if(OctalDigit *od = decOctalDigit(src, idx);
                od != nullptr)
                seq.push_back(od);
            else
                break;
        }

        if(!seq.empty())
            return new OctalEscapeSequence(std::move(seq));
        else
            return idx--, nullptr;
    }
    else
        return nullptr;
}

HexadecimalEscapeSequence *decHexadecimalEscapeSequence(const std::string &src
    , std::size_t &idx)
{
    if(idx + 1 < src.size()
        && src[idx] == '\\'
        && src[idx] == 'x'
        && (idx += 2, true))
    {
        std::vector<HexadecimalDigit*> seq;
        for(HexadecimalDigit *hd = decHexadecimalDigit(src, idx);
            hd != nullptr;
            hd = decHexadecimalDigit(src, idx))
            seq.push_back(hd);
        
        if(!seq.empty())
            return new HexadecimalEscapeSequence(std::move(seq));
        else
            return idx -= 2, nullptr;
    }
    else
        return nullptr;
}

OctalDigit *decOctalDigit(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size()
        && src[idx] >= '0'
        && src[idx] <= '7'
        && (idx++, true))
        return new OctalDigit(src[idx - 1]);
    else
        return nullptr;
}

IntegerConstant *decIntegerConstant(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    if(IntegerConstant::Sdc_is s;
        (s.dc = decDecimalConstant(src, idx)) != nullptr
            && (s.is = decIntegerSuffix(src, idx), true))
        return new IntegerConstant(s);
    else
    {
        idx = pre;
        delete s.dc;
        delete s.is;
    }

    if(IntegerConstant::Soc_is s;
        (s.oc = decOctalConstant(src, idx)) != nullptr
            && (s.is = decIntegerSuffix(src, idx), true))
        return new IntegerConstant(s);
    else
    {
        idx = pre;
        delete s.oc;
        delete s.is;
    }

    if(IntegerConstant::Shc_is s;
        (s.hc = decHexadecimalConstant(src, idx)) != nullptr
            && (s.is = decIntegerSuffix(src, idx), true))
        return new IntegerConstant(s);
    else
    {
        idx = pre;
        delete s.hc;
        delete s.is;
    }

    return nullptr;
}

FloatingConstant *decFloatingConstant(const std::string &src
    , std::size_t &idx)
{
    if(DecimalFloatingConstant *dfc = decDecimalFloatingConstant(src, idx);
        dfc != nullptr)
        return new FloatingConstant(dfc);
    else if(HexadecimalFloatingConstant *hfc = decHexadecimalFloatingConstant(src, idx);
        hfc != nullptr)
        return new FloatingConstant(hfc);
    else
        return nullptr;
}

DecimalConstant *decDecimalConstant(const std::string &src
    , std::size_t &idx)
{
    NonzeroDigit *nd = decNonzeroDigit(src, idx);
    if(nd == nullptr)
        return nullptr;
    
    std::vector<Digit*> seq;
    for(Digit *d = decDigit(src, idx);
        d != nullptr;
        d = decDigit(src, idx))
        seq.push_back(d);
    
    return new DecimalConstant(nd, std::move(seq));
}

IntegerSuffix *decIntegerSuffix(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    if(IntegerSuffix::Sus_lls s;
        (s.us = decUnsignedSuffix(src, idx)) != nullptr
            && (s.lls = decLongLongSuffix(src, idx)) != nullptr)
        return new IntegerSuffix(s);
    else
    {
        idx = pre;
        delete s.us;
        delete s.lls;
    }

    if(IntegerSuffix::Sus_ls s;
        (s.us = decUnsignedSuffix(src, idx)) != nullptr
            && (s.ls = decLongSuffix(src, idx), true))
        return new IntegerSuffix(s);
    else
    {
        idx = pre;
        delete s.us;
        delete s.ls;
    }

    if(IntegerSuffix::Sls_us s;
        (s.ls = decLongSuffix(src, idx)) != nullptr
            && (s.us = decUnsignedSuffix(src, idx), true))
        return new IntegerSuffix(s);
    else
    {
        idx = pre;
        delete s.ls;
        delete s.us;
    }

    if(IntegerSuffix::Slls_us s;
        (s.lls = decLongLongSuffix(src, idx)) != nullptr
            && (s.us = decUnsignedSuffix(src, idx), true))
        return new IntegerSuffix(s);
    else
    {
        idx = pre;
        delete s.lls;
        delete s.us;
    }

    return nullptr;
}

OctalConstant *decOctalConstant(const std::string &src
    , std::size_t &idx)
{
    if(idx >= src.size()
        || src[idx] != '0')
        return nullptr;
    
    idx++;
    std::vector<OctalDigit*> seq;
    for(OctalDigit *od = decOctalDigit(src, idx);
        od != nullptr;
        od = decOctalDigit(src, idx))
        seq.push_back(od);
    
    return new OctalConstant(std::move(seq));
}

HexadecimalConstant *decHexadecimalConstant(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    HexadecimalPrefix *hp = decHexadecimalPrefix(src, idx);
    if(hp == nullptr)
        return nullptr;
    
    std::vector<HexadecimalDigit*> seq;
    for(HexadecimalDigit* hd = decHexadecimalDigit(src, idx);
        hd != nullptr;
        hd = decHexadecimalDigit(src, idx))
        seq.push_back(hd);
    
    if(!seq.empty())
        return new HexadecimalConstant(hp, std::move(seq));
    else
    {
        idx = pre;
        delete hp;
    }

    return nullptr;
}

DecimalFloatingConstant *decDecimalFloatingConstant(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    if(DecimalFloatingConstant::Sfc_ep_fs s;
        (s.fc = decFractionalConstant(src, idx)) != nullptr
            && (s.ep = decExponentPart(src, idx), true)
            && (s.fs = decFloatingSuffix(src, idx), true))
        return new DecimalFloatingConstant(s);
    else
    {
        idx = pre;
        delete s.fc;
        delete s.ep;
        delete s.fs;
    }

    if(DecimalFloatingConstant::Sds_ep_fs s;
        (s.ds = decDigitSequence(src, idx)) != nullptr
            && (s.ep = decExponentPart(src, idx)) != nullptr
            && (s.fs = decFloatingSuffix(src, idx), true))
        return new DecimalFloatingConstant(s);
    else
    {
        idx = pre;
        delete s.ds;
        delete s.ep;
        delete s.fs;
    }

    return nullptr;
}

HexadecimalFloatingConstant *decHexadecimalFloatingConstant(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    if(HexadecimalFloatingConstant::Shp_hfc_bep_fs s;
        (s.hp = decHexadecimalPrefix(src, idx)) != nullptr
            && (s.hfc = decHexadecimalFractionalConstant(src, idx)) != nullptr
            && (s.bep = decBinaryExponentPart(src, idx)) != nullptr
            && (s.fs = decFloatingSuffix(src, idx), true))
        return new HexadecimalFloatingConstant(s);
    else
    {
        idx = pre;
        delete s.hp;
        delete s.hfc;
        delete s.bep;
        delete s.fs;
    }

    if(HexadecimalFloatingConstant::Shp_hds_bep_fs s;
        (s.hp = decHexadecimalPrefix(src, idx)) != nullptr
            && (s.hds = decHexadecimalDigitSequence(src, idx)) != nullptr
            && (s.bep = decBinaryExponentPart(src, idx)) != nullptr
            && (s.fs = decFloatingSuffix(src, idx), true))
        return new HexadecimalFloatingConstant(s);
    else
    {
        idx = pre;
        delete s.hp;
        delete s.hds;
        delete s.bep;
        delete s.fs;
    }

    return nullptr;
}

NonzeroDigit *decNonzeroDigit(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size()
        && (src[idx] >= '1' || src[idx] <= '9'))
        return idx++, new NonzeroDigit(src[idx - 1]);
    else
        return nullptr;
}

UnsignedSuffix *decUnsignedSuffix(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size())
    {
        if(src[idx] == 'u')
            return idx++, new UnsignedSuffix(UnsignedSuffix::Tag::u);
        else if(src[idx] == 'U')
            return idx++, new UnsignedSuffix(UnsignedSuffix::Tag::U);
    }

    return nullptr;
}

LongSuffix *decLongSuffix(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size())
    {
        if(src[idx] == 'l')
            return idx++, new LongSuffix(LongSuffix::Tag::l);
        else if(src[idx] == 'L')
            return idx++, new LongSuffix(LongSuffix::Tag::L);
    }

    return nullptr;
}

LongLongSuffix *decLongLongSuffix(const std::string &src
    , std::size_t &idx)
{
    if(idx + 1 < src.size())
    {
        if(src[idx] == 'l' && src[idx + 1] == 'l')
            return idx += 2, new LongLongSuffix(LongLongSuffix::Tag::ll);
        else if(src[idx] == 'L' && src[idx + 1] == 'L')
            return idx += 2, new LongLongSuffix(LongLongSuffix::Tag::LL);
    }

    return nullptr;
}

HexadecimalPrefix *decHexadecimalPrefix(const std::string &src
    , std::size_t &idx)
{
    if(idx + 1 < src.size())
    {
        if(src[idx] == '0' && src[idx + 1] == 'x')
            return idx += 2, new HexadecimalPrefix(HexadecimalPrefix::Tag::x);
        else if(src[idx] == '0' && src[idx + 1] == 'X')
            return idx += 2, new HexadecimalPrefix(HexadecimalPrefix::Tag::X);
    }

    return nullptr;
}

FractionalConstant *decFractionalConstant(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    if(FractionalConstant::Sds_ds s;
        (s.ds0 = decDigitSequence(src, idx), true)
            && idx < src.size()
            && (src[idx] == '.' ? (idx++, true) : false)
            && (s.ds1 = decDigitSequence(src, idx)) != nullptr)
        return new FractionalConstant(s);
    else
    {
        idx = pre;
        delete s.ds0;
        delete s.ds1;
    }

    if(FractionalConstant::Sds s;
        (s.ds = decDigitSequence(src, idx)) != nullptr
            && idx < src.size()
            && (src[idx] == '.' ? (idx++, true) : false))
        return new FractionalConstant(s);
    else
    {
        idx = pre;
        delete s.ds;
    }

    return nullptr;
}

ExponentPart *decExponentPart(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    Sign *s = nullptr;
    DigitSequence *ds = nullptr;
    if(idx < src.size()
        && (src[idx] == 'e' || src[idx] == 'E' ? (idx++, true) : false)
        && (s = decSign(src, idx)) != nullptr
        && (ds = decDigitSequence(src, idx)) != nullptr)
        return new ExponentPart(s, ds);
    else
    {
        idx = pre;
        delete s;
        delete ds;
    }

    return nullptr;
}

FloatingSuffix *decFloatingSuffix(const std::string &src
    , std::size_t &idx)
{
    if(idx < src.size())
    {
        FloatingSuffix::Tag tag = FloatingSuffix::Tag::NONE;
        if(src[idx] == 'f')
            tag = FloatingSuffix::Tag::f;
        else if(src[idx] == 'l')
            tag = FloatingSuffix::Tag::l;
        else if(src[idx] == 'F')
            tag = FloatingSuffix::Tag::F;
        else if(src[idx] == 'L')
            tag = FloatingSuffix::Tag::L;
        
        if(tag != FloatingSuffix::Tag::NONE)
            return idx++, new FloatingSuffix(tag);
    }

    return nullptr;
}

DigitSequence *decDigitSequence(const std::string &src
    , std::size_t &idx)
{
    std::vector<Digit*> seq;
    for(Digit *d = decDigit(src, idx);
        d != nullptr;
        d = decDigit(src, idx))
        seq.push_back(d);
    
    if(!seq.empty())
        return new DigitSequence(std::move(seq));
    else
        return nullptr;
}

HexadecimalFractionalConstant *decHexadecimalFractionalConstant(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    if(HexadecimalFractionalConstant::Shds_hds s;
        (s.hds0 = decHexadecimalDigitSequence(src, idx), true)
            && idx < src.size()
            && (src[idx] == '.' ? (idx++, true) : false)
            && (s.hds1 = decHexadecimalDigitSequence(src, idx)) != nullptr)
        return new HexadecimalFractionalConstant(s);
    else
    {
        idx = pre;
        delete s.hds0;
        delete s.hds1;
    }

    if(HexadecimalFractionalConstant::Shds s;
        (s.hds = decHexadecimalDigitSequence(src, idx)) != nullptr
            && idx < src.size()
            && (src[idx] == '.' ? (idx++, true) : false))
        return new HexadecimalFractionalConstant(s);
    else
    {
        idx = pre;
        delete s.hds;
    }

    return nullptr;
}

BinaryExponentPart *decBinaryExponentPart(const std::string &src
    , std::size_t &idx)
{
    std::size_t pre = idx;

    Sign *s = nullptr;
    DigitSequence *ds = nullptr;
    if(idx < src.size()
        && (src[idx] == 'p' || src[idx] == 'P' ? (idx++, true) : false)
        && (s = decSign(src, idx), true)
        && (ds = decDigitSequence(src, idx)) != nullptr)
        return new BinaryExponentPart(s, ds);
    else
    {
        idx = pre;
        delete s;
        delete ds;
    }

    return nullptr;
}

HexadecimalDigitSequence *decHexadecimalDigitSequence(const std::string &src
    , std::size_t &idx)
{
    std::vector<HexadecimalDigit*> seq;
    for(HexadecimalDigit *hd = decHexadecimalDigit(src, idx);
        hd != nullptr;
        hd = decHexadecimalDigit(src, idx))
        seq.push_back(hd);
    
    if(!seq.empty())
        return new HexadecimalDigitSequence(std::move(seq));
    else
        return nullptr;
}

}