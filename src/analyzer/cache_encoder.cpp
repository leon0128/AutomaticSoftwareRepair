#include <filesystem>
#include <fstream>
#include <iostream>

#include "cache_encoder.hpp"

namespace ANALYZER
{

CacheEncoder::CacheEncoder()
    : mStream{std::ios_base::out | std::ios_base::binary}
{
}

bool CacheEncoder::execute(const std::string &filename
    , const TOKEN::TranslationUnit *tu)
{
    if(!encode(tu))
        return false;

    if(!output(filename))
        return false;

    return true;
}

bool CacheEncoder::encode(std::monostate)
{
    return true;
}

bool CacheEncoder::encode(const std::string &str)
{
    mStream.write(str.data(), str.size());
    mStream.put('\0');

    return true;
}

bool CacheEncoder::encode(const TOKEN::Identifier::Seq &seq)
{
    if(!encode(seq.size()))
        return false;
    
    for(auto &&var : seq)
    {
        if(!encode(var))
            return false;
    }

    return true;
}

bool CacheEncoder::encode(const TOKEN::Identifier::Element &e)
{
    return encode(e.index())
        && std::visit([&](auto &&arg){return encode(arg);}, e);
}

bool CacheEncoder::encode(const TOKEN::Identifier::Id &id)
{
    return encode(id.first)
        && encode(id.second);
}

bool CacheEncoder::encode(const TOKEN::StringLiteral *sl)
{
    if(!addStatus(sl))
        return true;

    return encode(sl->ep)
        && encode(sl->scs);
}

bool CacheEncoder::encode(const TOKEN::Digit *digit)
{
    if(!addStatus(digit))
        return true;

    return encode(digit->c);
}

bool CacheEncoder::encode(const TOKEN::IntegerConstant::Sdc_is &s)
{
    return encode(s.dc)
        && encode(s.is);
}

bool CacheEncoder::encode(const TOKEN::IntegerConstant::Soc_is &s)
{
    return encode(s.oc)
        && encode(s.is);
}

bool CacheEncoder::encode(const TOKEN::IntegerConstant::Shc_is &s)
{
    return encode(s.hc)
        && encode(s.is);
}

bool CacheEncoder::encode(const TOKEN::EnumerationConstant *ec)
{
    if(!addStatus(ec))
        return true;

    return encode(ec->i);
}

bool CacheEncoder::encode(const TOKEN::CharacterConstant *cc)
{
    if(!addStatus(cc))
        return true;

    return encode(cc->tag)
        && encode(cc->ccs);
}

bool CacheEncoder::encode(const TOKEN::Nondigit *n)
{
    if(!addStatus(n))
        return true;

    return encode(n->c);
}

bool CacheEncoder::encode(const TOKEN::UniversalCharacterName::Su_hq &s)
{
    return encode(s.hq);
}

bool CacheEncoder::encode(const TOKEN::UniversalCharacterName::SU_hq_hq &s)
{
    return encode(s.hq0)
        && encode(s.hq1);
}

bool CacheEncoder::encode(const TOKEN::DecimalConstant *dc)
{
    if(!addStatus(dc))
        return true;

    if(!encode(dc->nd))
        return false;

    for(auto &&d : dc->seq)
    {
        if(!encode(d))
            return false;
    }

    return true;
}

bool CacheEncoder::encode(const TOKEN::HexadecimalConstant *hc)
{
    if(!addStatus(hc))
        return true;

    if(!encode(hc->hp))
        return false;

    for(auto &&hd : hc->seq)
    {
        if(!encode(hd))
            return false;
    }

    return true;
}

bool CacheEncoder::encode(const TOKEN::DecimalFloatingConstant::Sfc_ep_fs &s)
{
    return encode(s.fc)
        && encode(s.ep)
        && encode(s.fs);
}

bool CacheEncoder::encode(const TOKEN::DecimalFloatingConstant::Sds_ep_fs &s)
{
    return encode(s.ds)
        && encode(s.ep)
        && encode(s.fs);
}

bool CacheEncoder::encode(const TOKEN::HexadecimalFloatingConstant::Shp_hfc_bep_fs &s)
{
    return encode(s.hp)
        && encode(s.hfc)
        && encode(s.bep)
        && encode(s.fs);
}

bool CacheEncoder::encode(const TOKEN::HexadecimalFloatingConstant::Shp_hds_bep_fs &s)
{
    return encode(s.hp)
        && encode(s.hds)
        && encode(s.bep)
        && encode(s.fs);
}

bool CacheEncoder::encode(const TOKEN::HexQuad *hq)
{
    if(!addStatus(hq))
        return true;

    for(auto &&hd : hq->arr)
    {
        if(!encode(hd))
            return false;
    }

    return true;
}

bool CacheEncoder::encode(const TOKEN::NonzeroDigit *nd)
{
    if(!addStatus(nd))
        return true;

    return encode(nd->c);
}

bool CacheEncoder::encode(const TOKEN::OctalDigit *od)
{
    if(!addStatus(od))
        return true;

    return encode(od->c);
}

bool CacheEncoder::encode(const TOKEN::HexadecimalDigit *hd)
{
    if(!addStatus(hd))
        return true;

    return encode(hd->c);
}

bool CacheEncoder::encode(const TOKEN::FractionalConstant::Sds_ds &s)
{
    return encode(s.ds0)
        && encode(s.ds1);
}

bool CacheEncoder::encode(const TOKEN::FractionalConstant::Sds &s)
{
    return encode(s.ds);
}

bool CacheEncoder::encode(const TOKEN::ExponentPart *ep)
{
    if(!addStatus(ep))
        return true;

    return encode(ep->s)
        && encode(ep->ds);
}

bool CacheEncoder::encode(const TOKEN::HexadecimalFractionalConstant::Shds_hds &s)
{
    return encode(s.hds0)
        && encode(s.hds1);
}

bool CacheEncoder::encode(const TOKEN::HexadecimalFractionalConstant::Shds &s)
{
    return encode(s.hds);
}

bool CacheEncoder::encode(const TOKEN::BinaryExponentPart *bep)
{
    if(!addStatus(bep))
        return true;

    return encode(bep->s)
        && encode(bep->ds);
}

bool CacheEncoder::encode(const TOKEN::SimpleEscapeSequence *ses)
{
    if(!addStatus(ses))
        return true;

    return encode(ses->c);
}

bool CacheEncoder::encode(const TOKEN::IntegerSuffix::Sus_ls &s)
{
    return encode(s.us)
        && encode(s.ls);
}

bool CacheEncoder::encode(const TOKEN::IntegerSuffix::Sus_lls &s)
{
    return encode(s.us)
        && encode(s.lls);
}

bool CacheEncoder::encode(const TOKEN::IntegerSuffix::Sls_us &s)
{
    return encode(s.ls)
        && encode(s.us);
}

bool CacheEncoder::encode(const TOKEN::IntegerSuffix::Slls_us &s)
{
    return encode(s.lls)
        && encode(s.us);
}

bool CacheEncoder::encode(const TOKEN::FunctionDefinition *fd)
{
    if(!addStatus(fd))
        return true;

    return encode(fd->ds)
        && encode(fd->d)
        && encode(fd->dl)
        && encode(fd->cs)
        && encode(fd->scopeId)
        && encode(fd->statementId);
}

bool CacheEncoder::encode(const TOKEN::Declaration *d)
{
    if(!addStatus(d))
        return true;

    return std::visit([&](auto &&arg){return encode(arg);}, d->var)
        && encode(d->statementId);
}

bool CacheEncoder::encode(const TOKEN::Declaration::Sds_idl &s)
{
    return encode(s.ds)
        && encode(s.idl);
}

bool CacheEncoder::encode(const TOKEN::Declaration::Ssad &s)
{
    return encode(s.sad);
}

bool CacheEncoder::align(std::stringstream::pos_type alignmentSize)
{
    static const char padding[0xff]{'\0'};

    auto &&paddingSize{(alignmentSize - mStream.tellp() % alignmentSize) % alignmentSize};
    mStream.write(padding, paddingSize);
    return true;
}

bool CacheEncoder::output(const std::string &filename) const
{
    std::filesystem::path cacheFilePath{outputFilename(filename)};
    std::filesystem::create_directories(cacheFilePath.parent_path());

    std::ofstream fileStream{cacheFilePath, std::ios_base::out | std::ios_base::binary};
    if(!fileStream.is_open())
        return false;

    fileStream << mStream.str();

    fileStream.close();

    return true;
}

}