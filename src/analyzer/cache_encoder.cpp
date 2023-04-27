#include <filesystem>
#include <fstream>
#include <iostream>

#include "utility/output.hpp"
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

bool CacheEncoder::encode(const std::string &s)
{
    mStream.write(s.c_str(), s.size());
    mStream.put('\0');

    return true;
}

bool CacheEncoder::encode(const TOKEN::StringLiteral *sl)
{
    if(!addStatus(sl))
        return true;
    
    return encode(sl->ep)
        && encode(sl->scs);
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

    return encode(dc->nd)
        && encode(dc->seq);
}

bool CacheEncoder::encode(const TOKEN::HexadecimalConstant *hc)
{
    if(!addStatus(hc))
        return true;
    
    return encode(hc->hp)
        && encode(hc->seq);
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

    return encode(hq->arr);
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

    return encode(d->var)
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

bool CacheEncoder::encode(const TOKEN::Declarator *d)
{
    if(!addStatus(d))
        return true;
    
    return encode(d->p)
        && encode(d->asl)
        && encode(d->dd);
}

bool CacheEncoder::encode(const TOKEN::CompoundStatement *cs)
{
    if(!addStatus(cs))
        return true;
    
    return encode(cs->bil);
}

bool CacheEncoder::encode(const TOKEN::StaticAssertDeclaration *sad)
{
    if(!addStatus(sad))
        return true;

    return encode(sad->ce)
        && encode(sad->sl);
}

bool CacheEncoder::encode(const TOKEN::Pointer::Stql &s)
{
    return encode(s.tql);
}

bool CacheEncoder::encode(const TOKEN::Pointer::Stql_p &s)
{
    return encode(s.tql)
        && encode(s.p);
}

bool CacheEncoder::encode(const TOKEN::DirectDeclarator::Si &s)
{
    return encode(s.i);
}

bool CacheEncoder::encode(const TOKEN::DirectDeclarator::Sd &s)
{
    return encode(s.d);
}

bool CacheEncoder::encode(const TOKEN::DirectDeclarator::Stql_ae &s)
{
    return encode(s.tql)
        && encode(s.ae)
        && encode(s.hasStatic);
}

bool CacheEncoder::encode(const TOKEN::DirectDeclarator::Stql &s)
{
    return encode(s.tql);
}

bool CacheEncoder::encode(const TOKEN::DirectDeclarator::Sptl &s)
{
    return encode(s.ptl);
}

bool CacheEncoder::encode(const TOKEN::DirectDeclarator::Sil &s)
{
    return encode(s.il);
}

bool CacheEncoder::encode(const TOKEN::InitDeclarator::Sd &s)
{
    return encode(s.asl0)
        && encode(s.d)
        && encode(s.asl1);
}

bool CacheEncoder::encode(const TOKEN::InitDeclarator::Sd_i &s)
{
    return encode(s.asl0)
        && encode(s.d)
        && encode(s.asl1)
        && encode(s.i);
}

bool CacheEncoder::encode(const TOKEN::InitDeclarator::Sd_ba &s)
{
    return encode(s.asl0)
        && encode(s.d)
        && encode(s.asl1)
        && encode(s.ba)
        && encode(s.asl2);
}

bool CacheEncoder::encode(const TOKEN::ConstantExpression *ce)
{
    if(!addStatus(ce))
        return true;

    return encode(ce->ce);
}

bool CacheEncoder::encode(const TOKEN::AtomicTypeSpecifier *ats)
{
    if(!addStatus(ats))
        return true;

    return encode(ats->tn);
}

bool CacheEncoder::encode(const TOKEN::StructOrUnionSpecifier::Ssou_i_sdl &s)
{
    return encode(s.sou)
        && encode(s.asl)
        && encode(s.i)
        && encode(s.sdl);
}

bool CacheEncoder::encode(const TOKEN::StructOrUnionSpecifier::Ssou_i &s)
{
    return encode(s.sou)
        && encode(s.asl)
        && encode(s.i);
}

bool CacheEncoder::encode(const TOKEN::EnumSpecifier::Si_el &s)
{
    return encode(s.asl)
        && encode(s.i)
        && encode(s.el);
}

bool CacheEncoder::encode(const TOKEN::EnumSpecifier::Si &s)
{
    return encode(s.asl)
        && encode(s.i);
}

bool CacheEncoder::encode(const TOKEN::TypedefName *tn)
{
    if(!addStatus(tn))
        return true;

    return encode(tn->i);
}

bool CacheEncoder::encode(const TOKEN::TypeName *tn)
{
    if(!addStatus(tn))
        return true;

    return encode(tn->sql)
        && encode(tn->ad);
}

bool CacheEncoder::encode(const TOKEN::AssignmentExpression::Sce &s)
{
    return encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::AssignmentExpression::Sue_ao_ae &s)
{
    return encode(s.ue)
        && encode(s.ao)
        && encode(s.ae);
}

bool CacheEncoder::encode(const TOKEN::ParameterTypeList *ptl)
{
    if(!addStatus(ptl))
        return true;
    
    return encode(ptl->pl)
        && encode(ptl->isValiable);
}

bool CacheEncoder::encode(const TOKEN::ConditionalExpression::Slore &s)
{
    return encode(s.lore);
}

bool CacheEncoder::encode(const TOKEN::ConditionalExpression::Slore_e_ce &s)
{
    return encode(s.lore)
        && encode(s.e)
        && encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::AbstractDeclarator::Sp &s)
{
    return encode(s.p);
}

bool CacheEncoder::encode(const TOKEN::AbstractDeclarator::Sp_dad &s)
{
    return encode(s.p)
        && encode(s.dad);
}

bool CacheEncoder::encode(const TOKEN::UnaryExpression::Spe &s)
{
    return encode(s.pe);
}

bool CacheEncoder::encode(const TOKEN::UnaryExpression::Si_ue &s)
{
    return encode(s.ue);
}

bool CacheEncoder::encode(const TOKEN::UnaryExpression::Sd_ue &s)
{
    return encode(s.ue);
}

bool CacheEncoder::encode(const TOKEN::UnaryExpression::Suo_ce &s)
{
    return encode(s.uo)
        && encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::UnaryExpression::Ss_ue &s)
{
    return encode(s.ue);
}

bool CacheEncoder::encode(const TOKEN::UnaryExpression::Ss_tn &s)
{
    return encode(s.tn);
}

bool CacheEncoder::encode(const TOKEN::UnaryExpression::Sa_tn &s)
{
    return encode(s.tn);
}

bool CacheEncoder::encode(const TOKEN::Statement *s)
{
    if(!addStatus(s))
        return true;
    
    return encode(s->var)
        && encode(s->scopeId)
        && encode(s->statementId);
}

bool CacheEncoder::encode(const TOKEN::InitializerList::Sd_i &s)
{
    return encode(s.d)
        && encode(s.i);
}

bool CacheEncoder::encode(const TOKEN::StructDeclaration::Ssql_sdl &s)
{
    return encode(s.sql)
        && encode(s.sdl);
}

bool CacheEncoder::encode(const TOKEN::StructDeclaration::Ssad &s)
{
    return encode(s.sad);
}

bool CacheEncoder::encode(const TOKEN::Enumerator::Sec &s)
{
    return encode(s.ec)
        && encode(s.asl);
}

bool CacheEncoder::encode(const TOKEN::Enumerator::Sec_ce &s)
{
    return encode(s.ec)
        && encode(s.asl)
        && encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::DirectAbstractDeclarator::Sad &s)
{
    return encode(s.ad);
}

bool CacheEncoder::encode(const TOKEN::DirectAbstractDeclarator::Stql_ae &s)
{
    return encode(s.tql)
        && encode(s.ae)
        && encode(s.hasStatic);
}

bool CacheEncoder::encode(const TOKEN::DirectAbstractDeclarator::Sp&)
{
    return true;
}

bool CacheEncoder::encode(const TOKEN::DirectAbstractDeclarator::Sptl &s)
{
    return encode(s.ptl);
}

bool CacheEncoder::encode(const TOKEN::PostfixExpression::Spe &s)
{
    return encode(s.pe);
}

bool CacheEncoder::encode(const TOKEN::PostfixExpression::Se &s)
{
    return encode(s.e);
}

bool CacheEncoder::encode(const TOKEN::PostfixExpression::Sael &s)
{
    return encode(s.ael);
}

bool CacheEncoder::encode(const TOKEN::PostfixExpression::Sp_i &s)
{
    return encode(s.i);
}

bool CacheEncoder::encode(const TOKEN::PostfixExpression::Sa_i &s)
{
    return encode(s.i);
}

bool CacheEncoder::encode(const TOKEN::PostfixExpression::Si&)
{
    return true;
}

bool CacheEncoder::encode(const TOKEN::PostfixExpression::Sd&)
{
    return true;
}

bool CacheEncoder::encode(const TOKEN::PostfixExpression::Stn_il &s)
{
    return encode(s.tn)
        && encode(s.il);
}

bool CacheEncoder::encode(const TOKEN::CastExpression::Sue &s)
{
    return encode(s.ue);
}

bool CacheEncoder::encode(const TOKEN::CastExpression::Stn_ce &s)
{
    return encode(s.tn)
        && encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::ParameterDeclaration::Sds_d &s)
{
    return encode(s.ds)
        && encode(s.d);
}

bool CacheEncoder::encode(const TOKEN::ParameterDeclaration::Sds_ad &s)
{
    return encode(s.ds)
        && encode(s.ad);
}

bool CacheEncoder::encode(const TOKEN::LabeledStatement::Si_s &s)
{
    return encode(s.i)
        && encode(s.asl)
        && encode(s.s);
}

bool CacheEncoder::encode(const TOKEN::LabeledStatement::Sce_s &s)
{
    return encode(s.ce)
        && encode(s.s);
}

bool CacheEncoder::encode(const TOKEN::LabeledStatement::Sce_ce_s &s)
{
    return encode(s.ce0)
        && encode(s.ce1)
        && encode(s.s);
}

bool CacheEncoder::encode(const TOKEN::LabeledStatement::Ss &s)
{
    return encode(s.s);
}

bool CacheEncoder::encode(const TOKEN::ExpressionStatement *es)
{
    if(!addStatus(es))
        return true;

    return encode(es->e);
}

bool CacheEncoder::encode(const TOKEN::SelectionStatement::Si_e_s &s)
{
    return encode(s.e)
        && encode(s.s);
}

bool CacheEncoder::encode(const TOKEN::SelectionStatement::Si_e_s_s &s)
{
    return encode(s.e)
        && encode(s.s0)
        && encode(s.s1);
}

bool CacheEncoder::encode(const TOKEN::SelectionStatement::Ss_e_s &s)
{
    return encode(s.e)
        && encode(s.s);
}

bool CacheEncoder::encode(const TOKEN::IterationStatement::Sw_e_s &s)
{
    return encode(s.e)
        && encode(s.s);
}

bool CacheEncoder::encode(const TOKEN::IterationStatement::Sd_s_e &s)
{
    return encode(s.s)
        && encode(s.e);
}

bool CacheEncoder::encode(const TOKEN::IterationStatement::Sf_e_e_e_s &s)
{
    return encode(s.e0)
        && encode(s.e1)
        && encode(s.e2)
        && encode(s.s);
}

bool CacheEncoder::encode(const TOKEN::IterationStatement::Sf_d_e_e_s &s)
{
    return encode(s.d)
        && encode(s.e0)
        && encode(s.e1)
        && encode(s.s);
}

bool CacheEncoder::encode(const TOKEN::JumpStatement::Sg_i &s)
{
    return encode(s.i);
}

bool CacheEncoder::encode(const TOKEN::JumpStatement::Sc&)
{
    return true;
}

bool CacheEncoder::encode(const TOKEN::JumpStatement::Sb&)
{
    return true;
}

bool CacheEncoder::encode(const TOKEN::JumpStatement::Sr_e &s)
{
    return encode(s.e);
}

bool CacheEncoder::encode(const TOKEN::Designation *d)
{
    if(!addStatus(d))
        return true;

    return encode(d->dl);
}

bool CacheEncoder::encode(const TOKEN::StructDeclarator::Sd &s)
{
    return encode(s.d);
}

bool CacheEncoder::encode(const TOKEN::StructDeclarator::Sd_ce &s)
{
    return encode(s.d)
        && encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::GenericSelection *gs)
{
    if(!addStatus(gs))
        return true;

    return encode(gs->ae)
        && encode(gs->gal);
}

bool CacheEncoder::encode(const TOKEN::GenericAssociation::Stn_ae &s)
{
    return encode(s.tn)
        && encode(s.ae);
}

bool CacheEncoder::encode(const TOKEN::GenericAssociation::Sae &s)
{
    return encode(s.ae);
}

bool CacheEncoder::encode(const TOKEN::EqualityExpression::Sre &s)
{
    return encode(s.re);
}

bool CacheEncoder::encode(const TOKEN::EqualityExpression::Se_re &s)
{
    return encode(s.re);
}

bool CacheEncoder::encode(const TOKEN::EqualityExpression::Sne_re &s)
{
    return encode(s.re);
}

bool CacheEncoder::encode(const TOKEN::RelationalExpression::Sse &s)
{
    return encode(s.se);
}

bool CacheEncoder::encode(const TOKEN::RelationalExpression::Sl_se &s)
{
    return encode(s.se);
}

bool CacheEncoder::encode(const TOKEN::RelationalExpression::Sg_se &s)
{
    return encode(s.se);
}

bool CacheEncoder::encode(const TOKEN::RelationalExpression::Sle_se &s)
{
    return encode(s.se);
}

bool CacheEncoder::encode(const TOKEN::RelationalExpression::Sge_se &s)
{
    return encode(s.se);
}

bool CacheEncoder::encode(const TOKEN::ShiftExpression::Sae &s)
{
    return encode(s.ae);
}

bool CacheEncoder::encode(const TOKEN::ShiftExpression::Sl_ae &s)
{
    return encode(s.ae);
}

bool CacheEncoder::encode(const TOKEN::ShiftExpression::Sr_ae &s)
{
    return encode(s.ae);
}

bool CacheEncoder::encode(const TOKEN::AdditiveExpression::Sme &s)
{
    return encode(s.me);
}

bool CacheEncoder::encode(const TOKEN::AdditiveExpression::Sa_me &s)
{
    return encode(s.me);
}

bool CacheEncoder::encode(const TOKEN::AdditiveExpression::Ss_me &s)
{
    return encode(s.me);
}

bool CacheEncoder::encode(const TOKEN::MultiplicativeExpression::Sce &s)
{
    return encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::MultiplicativeExpression::Sm_ce &s)
{
    return encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::MultiplicativeExpression::Sd_ce &s)
{
    return encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::MultiplicativeExpression::Sr_ce &s)
{
    return encode(s.ce);
}

bool CacheEncoder::encode(const TOKEN::AttributeStatement *as)
{
    if(!addStatus(as))
        return true;

    return encode(as->asl);
}

bool CacheEncoder::encode(const TOKEN::BasicAsm *ba)
{
    if(!addStatus(ba))
        return true;

    return encode(ba->aq)
        && encode(ba->sl);
}

bool CacheEncoder::encode(const TOKEN::ExtendedAsm *ea)
{
    if(!addStatus(ea))
        return true;
    
    return encode(ea->aq)
        && encode(ea->sl)
        && encode(ea->oo)
        && encode(ea->io)
        && encode(ea->clobbers)
        && encode(ea->gl);
}

bool CacheEncoder::encode(const TOKEN::IncludingFile *i)
{
    if(!addStatus(i))
        return true;
    
    return encode(i->filename);
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

bool CacheEncoder::variantIndexError(std::size_t indexSize) const
{
    std::cerr << OUTPUT::charRedCode
        << "ANALYZER::CacheEncoder::variantIndexError():\n"
        << OUTPUT::resetCode
        << "    what: variant's max index size is greater than 255.\n"
        << "    size: " << indexSize
        << std::endl;
    return false;
}

bool CacheEncoder::arraySizeError(std::size_t arraySize) const
{
    std::cerr << OUTPUT::charRedCode
        << "ANALYZER::CacheEncoder::arraySizeError():\n"
        << OUTPUT::resetCode
        << "    what: array's size is greater than 65536.\n"
        << "    size: " << arraySize
        << std::endl;
    return false;
}

}