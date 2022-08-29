#include <iostream>
#include <utility>

#include "../configure.hpp"
#include "representation.hpp"
#include "representation_creator.hpp"

namespace SIM
{

#define IF_HOLDS_IF_PROCESS_RETURN_FALSE(CLASS, VARIABLE) \
    if(std::holds_alternative<CLASS>(VARIABLE)) \
    { \
        if(!process(std::get<CLASS>(VARIABLE))) \
            return false; \
    }

const std::unordered_map<RepresentationCreator::TypeTag, std::string> RepresentationCreator::mTypeTagMap
    {{TypeTag::DATA_TYPE, "D"}
        , {TypeTag::CLASS_TYPE, "C"}
        , {TypeTag::KEYWORD, "K"}
        , {TypeTag::OPERATOR, "O"}
        , {TypeTag::STRING_LITERAL, "S"}
        , {TypeTag::NUMBER, "N"}
        , {TypeTag::IDENTIFIER, "I"}};

bool RepresentationCreator::createAndRegister(const std::string &filename
    , const TOKEN::TranslationUnit *tu)
{
    using Rep = Representation;
    using RC = RepresentationCreator;

    std::array<RC*, Rep::castTag(Rep::Tag::SIZE_OF_TAG)> rcarr{new OriginalRepresentationCreator{Configure::SIM_ORIGINAL}
        , new Type1RepresentationCreator{Configure::SIM_TYPE1}
        , new Type2RepresentationCreator{Configure::SIM_TYPE2}
        , new Type3RepresentationCreator{Configure::SIM_TYPE3}};

    for(auto &&rc : rcarr)
    {
        if(!rc->execute(tu))
            return false;
    }

    // move tokens from RC to Rep
    for(std::size_t i{0ull}; i < rcarr.front()->functionTokens().size(); i++)
    {
        Rep::Element *element{new Rep::Element{filename, rcarr.front()->functionTokens()[i].first}};
        for(std::size_t j{0ull}; j < rcarr.size(); j++)
            element->mReps[j].tokens() = std::move(rcarr[j]->functionTokens()[i].second);
        Rep::reps().push_back(element);
    }

    return true;
}

RepresentationCreator::RepresentationCreator(std::size_t gramSize)
    : mGramSize{gramSize}
    , mFunctionTokens{}
{
}

RepresentationCreator::~RepresentationCreator()
{
}

bool RepresentationCreator::execute(const TOKEN::TranslationUnit *tu)
{
    if(!process(tu))
        return false;

    if(!concatenateTokens())
        return false;

    return true;
}

bool RepresentationCreator::concatenateTokens()
{
    for(auto &&[funcName, tokens] : mFunctionTokens)
    {
        if(tokens.size() < mGramSize)
            return tokenSizeError(funcName);

        std::deque<std::string> nGramTokens;
        for(std::size_t i{0ull}; i + mGramSize <= tokens.size(); i++)
        {
            nGramTokens.emplace_back(tokens[i]);
            for(std::size_t j{1ull}; j < mGramSize; j++)
                nGramTokens.back() += tokens[i + j];
        }

        tokens = std::move(nGramTokens);
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::TranslationUnit *tu)
{
    using FD = TOKEN::FunctionDefinition;

    for(auto &&ed : tu->seq)
    {
        if(std::holds_alternative<FD*>(ed->var))
        {
            if(!process(std::get<FD*>(ed->var)))
                return false;
        }
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::FunctionDefinition *fd)
{
    if(!setFunctionName(fd->d))
        return false;

    if(!process(fd->ds)
        || !process(fd->d)
        || !(fd->dl != nullptr ? process(fd->dl) : true)
        || !process(fd->cs))
        return false;

    return true;
}

bool RepresentationCreator::process(const TOKEN::DeclarationSpecifiers *ds)
{
    using namespace TOKEN;
    using SCS = StorageClassSpecifier;
    using TS = TypeSpecifier;
    using TQ = TypeQualifier;
    using FS = FunctionSpecifier;
    using AS = AlignmentSpecifier;
    using ASL = AttributeSpecifierList;

    for(auto &&var : ds->seq)
    {
        IF_HOLDS_IF_PROCESS_RETURN_FALSE(SCS*, var)
        else IF_HOLDS_IF_PROCESS_RETURN_FALSE(TS*, var)
        else IF_HOLDS_IF_PROCESS_RETURN_FALSE(TQ*, var)
        else IF_HOLDS_IF_PROCESS_RETURN_FALSE(FS*, var)
        else IF_HOLDS_IF_PROCESS_RETURN_FALSE(AS*, var)
        else IF_HOLDS_IF_PROCESS_RETURN_FALSE(ASL*, var)
        else
            return variantError("TOKEN::DeclarationSpecifiers");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::Declarator *declarator)
{
    if(!(declarator->p != nullptr ? process(declarator->p) : true)
        || !process(declarator->dd))
        return false;

    return true;
}

bool RepresentationCreator::process(const TOKEN::DeclarationList *dl)
{
    return processAgainstSequence(dl->seq);
}

bool RepresentationCreator::process(const TOKEN::CompoundStatement *cs)
{
    addToken("{");

    if(!(cs->bil != nullptr ? process(cs->bil) : true))
        return false;
    
    addToken("}");

    return true;
}

bool RepresentationCreator::process(const TOKEN::StorageClassSpecifier *scs)
{
    addToken(TOKEN::str(scs));

    return true;
}

bool RepresentationCreator::process(const TOKEN::TypeSpecifier *ts)
{
    using namespace TOKEN;

    if(std::holds_alternative<TypeSpecifier::Tag>(ts->var))
    {
        addToken(TOKEN::str(ts));
    }
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(AtomicTypeSpecifier*, ts->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(StructOrUnionSpecifier*, ts->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(EnumSpecifier*, ts->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(TypedefName*, ts->var)
    else
        return variantError("TOKEN::TypeSpecifier");

    return true;
}

bool RepresentationCreator::process(const TOKEN::FunctionSpecifier *fs)
{
    addToken(TOKEN::str(fs));
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::AlignmentSpecifier *as)
{
    using namespace TOKEN;

    addToken("_Alignas");
    addToken("(");

    IF_HOLDS_IF_PROCESS_RETURN_FALSE(TypeName*, as->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(ConstantExpression*, as->var)
    else
        return variantError("TOKEN::AlignmentSpecifier");
    
    addToken(")");

    return true;
}

bool RepresentationCreator::process(const TOKEN::Pointer *pointer)
{
    using namespace TOKEN;

    if(std::holds_alternative<Pointer::Stql>(pointer->var))
    {
        auto &&stql{std::get<Pointer::Stql>(pointer->var)};
        addToken("*");
        if(!(stql.tql != nullptr ? process(stql.tql) : true))
            return false;
    }
    else if(std::holds_alternative<Pointer::Stql_p>(pointer->var))
    {
        auto &&stp{std::get<Pointer::Stql_p>(pointer->var)};
        addToken("*");
        if(!(stp.tql != nullptr ? process(stp.tql) : true)
            || !process(stp.p))
            return false;
    }
    else
        return variantError("TOKEN::Pointer");

    return true;
}

bool RepresentationCreator::process(const TOKEN::DirectDeclarator *dd)
{
    using DD = TOKEN::DirectDeclarator;

    for(auto &&var : dd->seq)
    {
        if(std::holds_alternative<DD::Si>(var))
        {
            auto &&si{std::get<DD::Si>(var)};
            if(!process(si.i))
                return false;
        }
        else if(std::holds_alternative<DD::Sd>(var))
        {
            auto &&sd{std::get<DD::Sd>(var)};
            addToken("(");
            if(!process(sd.d))
                return false;
            addToken(")");
        }
        else if(std::holds_alternative<DD::Stql_ae>(var))
        {
            auto &&sta{std::get<DD::Stql_ae>(var)};
            addToken("[");
            if(sta.hasStatic)
                addToken("static");
            if(!(sta.tql != nullptr ? process(sta.tql) : true)
                || !(sta.ae != nullptr ? process(sta.ae) : true))
                return false;
            addToken("]");
        }
        else if(std::holds_alternative<DD::Stql>(var))
        {
            auto &&st{std::get<DD::Stql>(var)};
            addToken("[");
            if(!(st.tql != nullptr ? process(st.tql) : true))
                return false;
            addToken("*");
            addToken("]");
        }
        else if(std::holds_alternative<DD::Sptl>(var))
        {
            auto &&sp{std::get<DD::Sptl>(var)};
            addToken("(");
            if(!process(sp.ptl))
                return false;
            addToken(")");
        }
        else if(std::holds_alternative<DD::Sil>(var))
        {
            auto &&si{std::get<DD::Sil>(var)};
            addToken("(");
            if(!(si.il != nullptr ? process(si.il) : true))
                return false;
            addToken(")");
        }
        else
            return variantError("TOKEN::DirectDeclarator");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::Declaration *declaration)
{
    using namespace TOKEN;

    if(std::holds_alternative<Declaration::Sds_idl>(declaration->var))
    {
        auto &&sdi{std::get<Declaration::Sds_idl>(declaration->var)};
        if(!process(sdi.ds)
            || !(sdi.idl != nullptr ? process(sdi.idl) : true))
            return false;
        addToken(";");
    }
    else if(std::holds_alternative<Declaration::Ssad>(declaration->var))
    {
        auto &&ss{std::get<Declaration::Ssad>(declaration->var)};
        if(!process(ss.sad))
            return false;
    }
    else
        return variantError("TOKEN::Declaration");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::BlockItemList *bil)
{
    return processAgainstSequence(bil->seq);
}

bool RepresentationCreator::process(const TOKEN::TypeQualifierList *tql)
{
    return processAgainstSequence(tql->seq);
}

bool RepresentationCreator::process(const TOKEN::Identifier *identifier)
{
    addToken(TOKEN::str(identifier));

    return true;
}

bool RepresentationCreator::process(const TOKEN::AssignmentExpression *ae)
{
    using AE = TOKEN::AssignmentExpression;

    if(std::holds_alternative<AE::Sce>(ae->var))
    {
        auto &&sc{std::get<AE::Sce>(ae->var)};
        if(!process(sc.ce))
            return false;
    }
    else if(std::holds_alternative<AE::Sue_ao_ae>(ae->var))
    {
        auto &&suaa{std::get<AE::Sue_ao_ae>(ae->var)};
        if(!process(suaa.ue)
            || !process(suaa.ao)
            || !process(suaa.ae))
            return false;
    }
    else
        return variantError("TOKEN::AssignmentExpression");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::ParameterTypeList *ptl)
{
    if(!process(ptl->pl))
        return false;

    if(ptl->isValiable)
    {
        addToken(",");
        addToken("...");
    }
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::IdentifierList *il)
{
    return processAgainstSequence(il->seq, ",");
}

bool RepresentationCreator::process(const TOKEN::InitDeclaratorList *idl)
{
    return processAgainstSequence(idl->seq, ",");
}

bool RepresentationCreator::process(const TOKEN::StaticAssertDeclaration *sad)
{
    addToken("_Static_assert");
    addToken("(");
    if(!process(sad->ce))
        return false;
    addToken(",");
    if(!process(sad->sl))
        return false;
    addToken(")");
    addToken(";");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::BlockItem *bi)
{
    using namespace TOKEN;

    IF_HOLDS_IF_PROCESS_RETURN_FALSE(Declaration*, bi->var)
    IF_HOLDS_IF_PROCESS_RETURN_FALSE(Statement*, bi->var)
    else
        return variantError("BlockItem");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::TypeQualifier *tq)
{
    addToken(TOKEN::str(tq));

    return true;
}

bool RepresentationCreator::process(const TOKEN::ConditionalExpression *ce)
{
    using CE = TOKEN::ConditionalExpression;

    if(std::holds_alternative<CE::Slore>(ce->var))
    {
        auto &&sl{std::get<CE::Slore>(ce->var)};
        if(!process(sl.lore))
            return false;
    }
    else if(std::holds_alternative<CE::Slore_e_ce>(ce->var))
    {
        auto &&slec{std::get<CE::Slore_e_ce>(ce->var)};
        if(!process(slec.lore))
            return false;
        addToken("?");
        if(!process(slec.e))
            return false;
        addToken(":");
        if(!process(slec.ce))
            return false;
    }
    else
        variantError("TOKEN::ConditionalExpression");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::UnaryExpression *ue)
{
    using UE = TOKEN::UnaryExpression;

    if(std::holds_alternative<UE::Spe>(ue->var))
    {
        auto &&sp{std::get<UE::Spe>(ue->var)};
        if(!process(sp.pe))
            return false;
    }
    else if(std::holds_alternative<UE::Si_ue>(ue->var))
    {
        auto &&siu{std::get<UE::Si_ue>(ue->var)};
        addToken("++");
        if(!process(siu.ue))
            return false;
    }
    else if(std::holds_alternative<UE::Sd_ue>(ue->var))
    {
        auto &&sdu{std::get<UE::Sd_ue>(ue->var)};
        addToken("--");
        if(!process(sdu.ue))
            return false;
    }
    else if(std::holds_alternative<UE::Suo_ce>(ue->var))
    {
        auto &&suc{std::get<UE::Suo_ce>(ue->var)};
        if(!process(suc.uo)
            || !process(suc.ce))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_ue>(ue->var))
    {
        auto &&ssu{std::get<UE::Ss_ue>(ue->var)};
        addToken("sizeof");
        if(!process(ssu.ue))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_tn>(ue->var))
    {
        auto &&sst{std::get<UE::Ss_tn>(ue->var)};
        addToken("sizeof");
        addToken("(");
        if(!process(sst.tn))
            return false;
        addToken(")");
    }
    else if(std::holds_alternative<UE::Sa_tn>(ue->var))
    {
        auto &&sat{std::get<UE::Sa_tn>(ue->var)};
        addToken("_Alignof");
        addToken("(");
        if(!process(sat.tn))
            return false;
        addToken(")");
    }
    else
        return variantError("TOKEN::UnaryExpression");

    return true;
}

bool RepresentationCreator::process(const TOKEN::AssignmentOperator *ao)
{
    addToken(TOKEN::str(ao));

    return true;
}

bool RepresentationCreator::process(const TOKEN::ParameterList *pl)
{
    return processAgainstSequence(pl->seq, ",");
}

bool RepresentationCreator::process(const TOKEN::InitDeclarator *id)
{
    using ID = TOKEN::InitDeclarator;

    if(std::holds_alternative<ID::Sd>(id->var))
    {
        auto &&sd{std::get<ID::Sd>(id->var)};
        if(!(sd.asl0 != nullptr ? process(sd.asl0) : true)
            || !process(sd.d)
            || !(sd.asl1 != nullptr ? process(sd.asl1) : true))
            return false;
    }
    else if(std::holds_alternative<ID::Sd_i>(id->var))
    {
        auto &&sdi{std::get<ID::Sd_i>(id->var)};
        if(!(sdi.asl0 != nullptr ? process(sdi.asl0) : true)
            || !process(sdi.d)
            || !(sdi.asl1 != nullptr ? process(sdi.asl1) : true))
            return false;
        addToken("=");
        if(!process(sdi.i))
            return false;
    }
    else if(std::holds_alternative<ID::Sd_ba>(id->var))
    {
        auto &&sdb{std::get<ID::Sd_ba>(id->var)};
        if(!(sdb.asl0 != nullptr ? process(sdb.asl0) : true)
            || !process(sdb.d)
            || !(sdb.asl1 != nullptr ? process(sdb.asl1) : true)
            || !process(sdb.ba)
            || !(sdb.asl2 != nullptr ? process(sdb.asl2) : true))
            return false;
    }
    else
        return variantError("TOKEN::InitDeclarator");

    return true;
}

bool RepresentationCreator::process(const TOKEN::ConstantExpression *ce)
{
    if(!process(ce->ce))
        return false;
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::StringLiteral *sl)
{
    if(!(sl->ep != nullptr ? process(sl->ep) : true))
        return false;
    addToken("\"");
    if(!(sl->scs != nullptr ? process(sl->scs) : true))
        return false;
    addToken("\"");

    return true;
}

bool RepresentationCreator::process(const TOKEN::Statement *statement)
{
    using namespace TOKEN;

    IF_HOLDS_IF_PROCESS_RETURN_FALSE(LabeledStatement*, statement->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(CompoundStatement*, statement->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(ExpressionStatement*, statement->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(SelectionStatement*, statement->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(IterationStatement*, statement->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(JumpStatement*, statement->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(AttributeStatement*, statement->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(AsmStatement*, statement->var)
    else
        return variantError("TOKEN::Statement");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::LogicalORExpression *lore)
{
    return processAgainstSequence(lore->seq, "||");
}

bool RepresentationCreator::process(const TOKEN::Expression *expression)
{
    return processAgainstSequence(expression->seq, ",");
}

bool RepresentationCreator::process(const TOKEN::PostfixExpression *pe)
{
    using PE = TOKEN::PostfixExpression;

    for(auto &&var : pe->seq)
    {
        if(std::holds_alternative<PE::Spe>(var))
        {
            auto &&sp{std::get<PE::Spe>(var)};
            if(!process(sp.pe))
                return false;
        }
        else if(std::holds_alternative<PE::Se>(var))
        {
            auto &&se{std::get<PE::Se>(var)};
            addToken("[");
            if(!process(se.e))
                return false;
            addToken("]");
        }
        else if(std::holds_alternative<PE::Sael>(var))
        {
            auto &&sa{std::get<PE::Sael>(var)};
            addToken("(");
            if(!(sa.ael != nullptr ? process(sa.ael) : true))
                return false;
            addToken(")");
        }
        else if(std::holds_alternative<PE::Sp_i>(var))
        {
            auto &&si{std::get<PE::Sp_i>(var)};
            addToken(".");
            if(!process(si.i))
                return false;
        }
        else if(std::holds_alternative<PE::Sa_i>(var))
        {
            auto &&si{std::get<PE::Sa_i>(var)};
            addToken("->");
            if(!process(si.i))
                return false;
        }
        else if(std::holds_alternative<PE::Si>(var))
        {
            addToken("++");
        }
        else if(std::holds_alternative<PE::Sd>(var))
        {
            addToken("--");
        }
        else if(std::holds_alternative<PE::Stn_il>(var))
        {
            auto &&sti{std::get<PE::Stn_il>(var)};
            addToken("(");
            if(!process(sti.tn))
                return false;
            addToken(")");
            addToken("{");
            if(!process(sti.il))
                return false;
            addToken("}");
        }
        else
            return variantError("TOKEN::PostfixExpression");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::UnaryOperator *uo)
{
    addToken(TOKEN::str(uo));

    return true;
}

bool RepresentationCreator::process(const TOKEN::CastExpression *ce)
{
    using CE = TOKEN::CastExpression;

    if(std::holds_alternative<CE::Sue>(ce->var))
    {
        auto &&su{std::get<CE::Sue>(ce->var)};
        if(!process(su.ue))
            return false;
    }
    else if(std::holds_alternative<CE::Stn_ce>(ce->var))
    {
        auto &&stc{std::get<CE::Stn_ce>(ce->var)};
        addToken("(");
        if(!process(stc.tn))
            return false;
        addToken(")");
        if(!process(stc.ce))
            return false;
    }
    else
        return variantError("TOKEN::CastExpression");

    return true;
}

bool RepresentationCreator::process(const TOKEN::TypeName *tn)
{
    if(!process(tn->sql)
        || !(tn->ad != nullptr ? process(tn->ad) : true))
        return false;
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::ParameterDeclaration *pd)
{
    using PD = TOKEN::ParameterDeclaration;

    if(std::holds_alternative<PD::Sds_d>(pd->var))
    {
        auto &&sdd{std::get<PD::Sds_d>(pd->var)};
        if(!process(sdd.ds)
            || !process(sdd.d))
            return false;
    }
    else if(std::holds_alternative<PD::Sds_ad>(pd->var))
    {
        auto &&sda{std::get<PD::Sds_ad>(pd->var)};
        if(!process(sda.ds)
            || !(sda.ad != nullptr ? process(sda.ad) : true))
            return false;
    }
    else
        return variantError("TOKEN::ParameterDeclaration");

    return true;
}

bool RepresentationCreator::process(const TOKEN::Initializer *initializer)
{
    using namespace TOKEN;

    if(std::holds_alternative<AssignmentExpression*>(initializer->var))
    {
        if(!process(std::get<AssignmentExpression*>(initializer->var)))
            return false;
    }
    else if(std::holds_alternative<InitializerList*>(initializer->var))
    {
        addToken("{");
        if(!process(std::get<InitializerList*>(initializer->var)))
            return false;
        addToken("}");
    }
    else
        return variantError("TOKEN::Initializer");

    return true;
}

bool RepresentationCreator::process(const TOKEN::EncodingPrefix *ep)
{
    addToken(TOKEN::str(ep));
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::LabeledStatement *ls)
{
    using LS = TOKEN::LabeledStatement;

    if(std::holds_alternative<LS::Si_s>(ls->var))
    {
        auto &&sis{std::get<LS::Si_s>(ls->var)};
        if(!process(sis.i)
            || !(sis.asl != nullptr ? process(sis.asl) : true))
            return false;
        addToken(":");
        if(!process(sis.s))
            return false;
    }
    else if(std::holds_alternative<LS::Sce_s>(ls->var))
    {
        auto &&scs{std::get<LS::Sce_s>(ls->var)};
        addToken("case");
        if(!process(scs.ce))
            return false;
        addToken(":");
        if(!process(scs.s))
            return false;
    }
    else if(std::holds_alternative<LS::Ss>(ls->var))
    {
        auto &&ss{std::get<LS::Ss>(ls->var)};
        addToken("default");
        addToken(":");
        if(!process(ss.s))
            return false;
    }
    else
        return variantError("TOKEN::LabeledStatement");

    return true;
}

bool RepresentationCreator::process(const TOKEN::ExpressionStatement *es)
{
    if(!(es->e != nullptr ? process(es->e) : true))
        return false;
    
    addToken(";");

    return true;
}

bool RepresentationCreator::process(const TOKEN::SelectionStatement *ss)
{
    using SS = TOKEN::SelectionStatement;

    if(std::holds_alternative<SS::Si_e_s>(ss->var))
    {
        auto &&ses{std::get<SS::Si_e_s>(ss->var)};
        addToken("if");
        addToken("(");
        if(!process(ses.e))
            return false;
        addToken(")");
        if(!process(ses.s))
            return false;
    }
    else if(std::holds_alternative<SS::Si_e_s_s>(ss->var))
    {
        auto &&sess{std::get<SS::Si_e_s_s>(ss->var)};
        addToken("if");
        addToken("(");
        if(!process(sess.e))
            return false;
        addToken(")");
        if(!process(sess.s0))
            return false;
        addToken("else");
        if(!process(sess.s1))
            return false;
    }
    else if(std::holds_alternative<SS::Ss_e_s>(ss->var))
    {
        auto &&ses{std::get<SS::Ss_e_s>(ss->var)};
        addToken("switch");
        addToken("(");
        if(!process(ses.e))
            return false;
        addToken(")");
        if(!process(ses.s))
            return false;
    }
    else
        return variantError("TOKEN::SelectionStatement");

    return true;
}

bool RepresentationCreator::process(const TOKEN::IterationStatement *is)
{
    using IS = TOKEN::IterationStatement;

    if(std::holds_alternative<IS::Sw_e_s>(is->var))
    {
        auto &&ses{std::get<IS::Sw_e_s>(is->var)};
        addToken("while");
        addToken("(");
        if(!process(ses.e))
            return false;
        addToken(")");
        if(!process(ses.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sd_s_e>(is->var))
    {
        auto &&sse{std::get<IS::Sd_s_e>(is->var)};
        addToken("do");
        if(!process(sse.s))
            return false;
        addToken("while");
        addToken("(");
        if(!process(sse.e))
            return false;
        addToken(")");
        addToken(";");
    }
    else if(std::holds_alternative<IS::Sf_e_e_e_s>(is->var))
    {
        auto &&seees{std::get<IS::Sf_e_e_e_s>(is->var)};
        addToken("for");
        addToken("(");
        if(!(seees.e0 != nullptr ? process(seees.e0) : true))
            return false;
        addToken(";");
        if(!(seees.e1 != nullptr ? process(seees.e1) : true))
            return false;
        addToken(";");
        if(!(seees.e2 != nullptr ? process(seees.e2) : true))
            return false;
        addToken(")");
        if(!process(seees.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sf_d_e_e_s>(is->var))
    {
        auto &&sdees{std::get<IS::Sf_d_e_e_s>(is->var)};
        addToken("for");
        addToken("(");
        if(!process(sdees.d)
            || !(sdees.e0 != nullptr ? process(sdees.e0) : true))
            return false;
        addToken(";");
        if(!(sdees.e1 != nullptr ? process(sdees.e1) : true))
            return false;
        addToken(")");
        if(!process(sdees.s))
            return false;
    }
    else
        return variantError("TOKEN::IterationStatement");

    return true;
}

bool RepresentationCreator::process(const TOKEN::JumpStatement *js)
{
    using JS = TOKEN::JumpStatement;

    if(std::holds_alternative<JS::Sg_i>(js->var))
    {
        auto &&si{std::get<JS::Sg_i>(js->var)};
        addToken("goto");
        if(!process(si.i))
            return false;
        addToken(";");
    }
    else if(std::holds_alternative<JS::Sc>(js->var))
    {
        addToken("continue");
        addToken(";");
    }
    else if(std::holds_alternative<JS::Sb>(js->var))
    {
        addToken("break");
        addToken(";");
    }
    else if(std::holds_alternative<JS::Sr_e>(js->var))
    {
        auto &&se{std::get<JS::Sr_e>(js->var)};
        addToken("return");
        if(!(se.e != nullptr ? process(se.e) : true))
            return false;
        addToken(";");
    }
    else
        return variantError("TOKEN::JumpStatement");

    return true;
}

bool RepresentationCreator::process(const TOKEN::SCharSequence *scs)
{
    addToken(TOKEN::str(scs));

    return true;
}

bool RepresentationCreator::process(const TOKEN::LogicalANDExpression *lande)
{
    return processAgainstSequence(lande->seq, "&&");
}

bool RepresentationCreator::process(const TOKEN::PrimaryExpression *pe)
{
    using namespace TOKEN;

    IF_HOLDS_IF_PROCESS_RETURN_FALSE(Identifier*, pe->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(Constant*, pe->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(StringLiteral*, pe->var)
    else if(std::holds_alternative<Expression*>(pe->var))
    {
        addToken("(");
        if(!process(std::get<Expression*>(pe->var)))
            return false;
        addToken(")");
    }
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(GenericSelection*, pe->var)
    else
        return variantError("TOKEN::PrimaryExpression");

    return true;
}

bool RepresentationCreator::process(const TOKEN::ArgumentExpressionList *ael)
{
    return processAgainstSequence(ael->seq, ",");
}

bool RepresentationCreator::process(const TOKEN::InitializerList *il)
{
    for(std::size_t i{0ull}; i < il->seq.size(); i++)
    {
        if(!(il->seq[i].d != nullptr ? process(il->seq[i].d) : true)
            || !process(il->seq[i].i))
            return false;
        
        if(i + 1ull != il->seq.size())
            addToken(",");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::SpecifierQualifierList *sql)
{
    using namespace TOKEN;

    for(auto &&var : sql->seq)
    {
        IF_HOLDS_IF_PROCESS_RETURN_FALSE(TypeSpecifier*, var)
        else IF_HOLDS_IF_PROCESS_RETURN_FALSE(TypeQualifier*, var)
        else IF_HOLDS_IF_PROCESS_RETURN_FALSE(AttributeSpecifierList*, var)
        else
            return variantError("TOKEN::SpecifierQualifierList");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::AbstractDeclarator *ad)
{
    using AD = TOKEN::AbstractDeclarator;

    if(std::holds_alternative<AD::Sp>(ad->var))
    {
        auto &&sp{std::get<AD::Sp>(ad->var)};
        if(!process(sp.p))
            return false;
    }
    else if(std::holds_alternative<AD::Sp_dad>(ad->var))
    {
        auto &&spd{std::get<AD::Sp_dad>(ad->var)};
        if(!(spd.p != nullptr ? process(spd.p) : true)
            || !process(spd.dad))
            return false;
    }
    else
        return variantError("TOKEN::AbstractDeclarator");

    return true;
}

bool RepresentationCreator::process(const TOKEN::InclusiveORExpression *iore)
{
    return processAgainstSequence(iore->seq, "|");
}

bool RepresentationCreator::process(const TOKEN::Constant *constant)
{
    using namespace TOKEN;

    IF_HOLDS_IF_PROCESS_RETURN_FALSE(IntegerConstant*, constant->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(FloatingConstant*, constant->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(EnumerationConstant*, constant->var)
    else IF_HOLDS_IF_PROCESS_RETURN_FALSE(CharacterConstant*, constant->var)
    else
        return variantError("TOKEN::Constant");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::GenericSelection *gs)
{
    addToken("_Generic");
    addToken("(");
    if(!process(gs->ae))
        return false;
    addToken(",");
    if(!process(gs->gal))
        return false;
    addToken(")");

    return true;
}

bool RepresentationCreator::process(const TOKEN::Designation *designation)
{
    if(!process(designation->dl))
        return false;
    
    addToken("=");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::AtomicTypeSpecifier *ats)
{
    addToken("_Atomic");
    addToken("(");
    if(!process(ats->tn))
        return false;
    addToken(")");

    return true;
}

bool RepresentationCreator::process(const TOKEN::StructOrUnionSpecifier *sous)
{
    using SOUS = TOKEN::StructOrUnionSpecifier;

    if(std::holds_alternative<SOUS::Ssou_i_sdl>(sous->var))
    {
        auto &&ssis{std::get<SOUS::Ssou_i_sdl>(sous->var)};
        if(!process(ssis.sou)
            || !(ssis.asl != nullptr ? process(ssis.asl) : true)
            || !(ssis.i != nullptr ? process(ssis.i) : true))
            return false;
        addToken("{");
        if(!process(ssis.sdl))
            return false;
        addToken("}");
    }
    else if(std::holds_alternative<SOUS::Ssou_i>(sous->var))
    {
        auto &&ssi{std::get<SOUS::Ssou_i>(sous->var)};
        if(!process(ssi.sou)
            || !(ssi.asl != nullptr ? process(ssi.asl) : true)
            || !process(ssi.i))
            return false;
    }
    else
        return variantError("TOKEN::StructOrUnionSpecifier");

    return true;
}

bool RepresentationCreator::process(const TOKEN::EnumSpecifier *es)
{
    using ES = TOKEN::EnumSpecifier;

    if(std::holds_alternative<ES::Si_el>(es->var))
    {
        auto &&sie{std::get<ES::Si_el>(es->var)};
        addToken("enum");
        if(!(sie.asl != nullptr ? process(sie.asl) : true)
            || !(sie.i != nullptr ? process(sie.i) : true))
            return false;
        addToken("{");
        if(!process(sie.el))
            return false;
        addToken("}");
    }
    else if(std::holds_alternative<ES::Si>(es->var))
    {
        auto &&si{std::get<ES::Si>(es->var)};
        addToken("enum");
        if(!(si.asl != nullptr ? process(si.asl) : true)
            || !process(si.i))
            return false;
    }
    else
        return variantError("TOKEN::EnumSpecifier");

    return true;
}

bool RepresentationCreator::process(const TOKEN::TypedefName *tn)
{
    if(!process(tn->i))
        return false;
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::DirectAbstractDeclarator *dad)
{
    using DAD = TOKEN::DirectAbstractDeclarator;

    for(auto &&var : dad->seq)
    {
        if(std::holds_alternative<DAD::Sad>(var))
        {
            auto &&sa{std::get<DAD::Sad>(var)};
            addToken("(");
            if(!process(sa.ad))
                return false;
            addToken(")");
        }
        else if(std::holds_alternative<DAD::Stql_ae>(var))
        {
            auto &&sta{std::get<DAD::Stql_ae>(var)};
            addToken("[");
            if(sta.hasStatic)
                addToken("static");
            if(!(sta.tql != nullptr ? process(sta.tql) : true)
                || !(sta.ae != nullptr ? process(sta.ae) : true))
                return false;
            addToken("]");
        }
        else if(std::holds_alternative<DAD::Sp>(var))
        {
            addToken("[");
            addToken("*");
            addToken("]");
        }
        else if(std::holds_alternative<DAD::Sptl>(var))
        {
            auto &&sp{std::get<DAD::Sptl>(var)};
            addToken("(");
            if(!(sp.ptl != nullptr ? process(sp.ptl) : true))
                return false;
            addToken(")");
        }
        else
            return variantError("TOKEN::DirectAbstractDeclarator");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::ExclusiveORExpression *eore)
{
    return processAgainstSequence(eore->seq, "^");
}

bool RepresentationCreator::process(const TOKEN::IntegerConstant *ic)
{
    addToken(TOKEN::str(ic));

    return true;
}

bool RepresentationCreator::process(const TOKEN::FloatingConstant *fc)
{
    addToken(TOKEN::str(fc));

    return true;
}

bool RepresentationCreator::process(const TOKEN::EnumerationConstant *ec)
{
    if(!process(ec->i))
        return false;
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::CharacterConstant *cc)
{
    addToken(TOKEN::str(cc));

    return true;
}

bool RepresentationCreator::process(const TOKEN::GenericAssocList *gal)
{
    return processAgainstSequence(gal->seq, ",");
}

bool RepresentationCreator::process(const TOKEN::DesignatorList *dl)
{
    return processAgainstSequence(dl->seq);
}

bool RepresentationCreator::process(const TOKEN::StructOrUnion *sou)
{
    addToken(TOKEN::str(sou));

    return true;
}

bool RepresentationCreator::process(const TOKEN::StructDeclarationList *sdl)
{
    return processAgainstSequence(sdl->seq);
}

bool RepresentationCreator::process(const TOKEN::EnumeratorList *el)
{
    return processAgainstSequence(el->seq, ",");
}

bool RepresentationCreator::process(const TOKEN::ANDExpression *ande)
{
    return processAgainstSequence(ande->seq, "&");
}

bool RepresentationCreator::process(const TOKEN::GenericAssociation *ga)
{
    using GA = TOKEN::GenericAssociation;

    if(std::holds_alternative<GA::Stn_ae>(ga->var))
    {
        auto &&sta{std::get<GA::Stn_ae>(ga->var)};
        if(!process(sta.tn))
            return false;
        addToken(":");
        if(!process(sta.ae))
            return false;
    }
    else if(std::holds_alternative<GA::Sae>(ga->var))
    {
        auto &&sa{std::get<GA::Sae>(ga->var)};
        addToken("default");
        addToken(":");
        if(!process(sa.ae))
            return false;
    }
    else
        return variantError("TOKEN::GEnericAssociation");

    return true;
}

bool RepresentationCreator::process(const TOKEN::Designator *designator)
{
    using namespace TOKEN;

    if(std::holds_alternative<ConstantExpression*>(designator->var))
    {
        addToken("[");
        if(!process(std::get<ConstantExpression*>(designator->var)))
            return false;
        addToken("]");
    }
    else if(std::holds_alternative<Identifier*>(designator->var))
    {
        addToken(".");
        if(!process(std::get<Identifier*>(designator->var)))
            return false;
    }
    else
        return variantError("TOKEN::Designator");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::StructDeclaration *sd)
{
    using SD = TOKEN::StructDeclaration;

    if(std::holds_alternative<SD::Ssql_sdl>(sd->var))
    {
        auto &&sss{std::get<SD::Ssql_sdl>(sd->var)};
        if(!process(sss.sql)
            || !(sss.sdl != nullptr ? process(sss.sdl) : true))
            return false;
        addToken(";");
    }
    else if(std::holds_alternative<SD::Ssad>(sd->var))
    {
        auto &&ss{std::get<SD::Ssad>(sd->var)};
        if(!process(ss.sad))
            return false;
    }
    else
        return variantError("TOKEN::StructDeclaration");
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::Enumerator *enumerator)
{
    using  E = TOKEN::Enumerator;

    if(std::holds_alternative<E::Sec>(enumerator->var))
    {
        auto &&se{std::get<E::Sec>(enumerator->var)};
        if(!process(se.ec)
            || !(se.asl != nullptr ? process(se.asl) : true))
            return false;
    }
    else if(std::holds_alternative<E::Sec_ce>(enumerator->var))
    {
        auto &&sec{std::get<E::Sec_ce>(enumerator->var)};
        if(!process(sec.ec)
            || !(sec.asl != nullptr ? process(sec.asl) : true))
            return false;
        addToken("=");
        if(!process(sec.ce))
            return false;
    }
    else
        return variantError("TOKEN::Enumerator");

    return true;
}

bool RepresentationCreator::process(const TOKEN::EqualityExpression *ee)
{
    using EE = TOKEN::EqualityExpression;

    for(auto &&var : ee->seq)
    {
        if(std::holds_alternative<EE::Sre>(var))
        {
            auto &&sr{std::get<EE::Sre>(var)};
            if(!process(sr.re))
                return false;
        }
        else if(std::holds_alternative<EE::Se_re>(var))
        {
            auto &&sr{std::get<EE::Se_re>(var)};
            addToken("==");
            if(!process(sr.re))
                return false;
        }
        else if(std::holds_alternative<EE::Sne_re>(var))
        {
            auto &&sr{std::get<EE::Sne_re>(var)};
            addToken("!=");
            if(!process(sr.re))
                return false;
        }
        else
            return variantError("TOKEN::EqualityExpression");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::StructDeclaratorList *sdl)
{
    return processAgainstSequence(sdl->seq, ",");
}

bool RepresentationCreator::process(const TOKEN::RelationalExpression *re)
{
    using RE = TOKEN::RelationalExpression;

    for(auto &&var : re->seq)
    {
        if(std::holds_alternative<RE::Sse>(var))
        {
            auto &&ss{std::get<RE::Sse>(var)};
            if(!process(ss.se))
                return false;
        }
        else if(std::holds_alternative<RE::Sl_se>(var))
        {
            auto &&ss{std::get<RE::Sl_se>(var)};
            addToken("<");
            if(!process(ss.se))
                return false;
        }
        else if(std::holds_alternative<RE::Sg_se>(var))
        {
            auto &&ss{std::get<RE::Sg_se>(var)};
            addToken(">");
            if(!process(ss.se))
                return false;
        }
        else if(std::holds_alternative<RE::Sle_se>(var))
        {
            auto &&ss{std::get<RE::Sle_se>(var)};
            addToken("<=");
            if(!process(ss.se))
                return false;
        }
        else if(std::holds_alternative<RE::Sge_se>(var))
        {
            auto &&ss{std::get<RE::Sge_se>(var)};
            addToken(">=");
            if(!process(ss.se))
                return false;
        }
        else
            return variantError("TOKEN::RelationalExpression");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::StructDeclarator *sd)
{
    using SD = TOKEN::StructDeclarator;

    if(std::holds_alternative<SD::Sd>(sd->var))
    {
        auto &&s{std::get<SD::Sd>(sd->var)};
        if(!process(s.d))
            return false;
    }
    else if(std::holds_alternative<SD::Sd_ce>(sd->var))
    {
        auto &&sdc{std::get<SD::Sd_ce>(sd->var)};
        if(!(sdc.d != nullptr ? process(sdc.d) : true))
            return false;
        addToken(":");
        if(!process(sdc.ce))
            return false;
    }
    else
        return variantError("TOKEN::StructDeclarator");

    return true;
}

bool RepresentationCreator::process(const TOKEN::ShiftExpression *se)
{
    using SE = TOKEN::ShiftExpression;

    for(auto &&var : se->seq)
    {
        if(std::holds_alternative<SE::Sae>(var))
        {
            auto &&sa{std::get<SE::Sae>(var)};
            if(!process(sa.ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sl_ae>(var))
        {
            auto &&sa{std::get<SE::Sl_ae>(var)};
            addToken("<<");
            if(!process(sa.ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sr_ae>(var))
        {
            auto &&sa{std::get<SE::Sr_ae>(var)};
            addToken(">>");
            if(!process(sa.ae))
                return false;
        }
        else
            return variantError("TOKEN::ShiftExpression");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::AdditiveExpression *ae)
{
    using AE = TOKEN::AdditiveExpression;

    for(auto &&var : ae->seq)
    {
        if(std::holds_alternative<AE::Sme>(var))
        {
            auto &&sm{std::get<AE::Sme>(var)};
            if(!process(sm.me))
                return false;
        }
        else if(std::holds_alternative<AE::Sa_me>(var))
        {
            auto &&sm{std::get<AE::Sa_me>(var)};
            addToken("+");
            if(!process(sm.me))
                return false;
        }
        else if(std::holds_alternative<AE::Ss_me>(var))
        {
            auto &&sm{std::get<AE::Ss_me>(var)};
            addToken("-");
            if(!process(sm.me))
                return false;
        }
        else
            return variantError("TOKEN::AdditiveExpression");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::MultiplicativeExpression *me)
{
    using ME = TOKEN::MultiplicativeExpression;

    for(auto &&var : me->seq)
    {
        if(std::holds_alternative<ME::Sce>(var))
        {
            auto &&sc{std::get<ME::Sce>(var)};
            if(!process(sc.ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sm_ce>(var))
        {
            auto &&sc{std::get<ME::Sm_ce>(var)};
            addToken("*");
            if(!process(sc.ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sd_ce>(var))
        {
            auto &&sc{std::get<ME::Sd_ce>(var)};
            addToken("/");
            if(!process(sc.ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sr_ce>(var))
        {
            auto &&sc{std::get<ME::Sr_ce>(var)};
            addToken("%");
            if(!process(sc.ce))
                return false;
        }
        else
            return variantError("TOKEN::MultiplicativeExpression");
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::Token *token)
{
    using namespace TOKEN;

    if(std::holds_alternative<Keyword*>(token->var))
        return process(std::get<Keyword*>(token->var));
    else if(std::holds_alternative<Identifier*>(token->var))
        return process(std::get<Identifier*>(token->var));
    else if(std::holds_alternative<Constant*>(token->var))
        return process(std::get<Constant*>(token->var));
    else if(std::holds_alternative<StringLiteral*>(token->var))
        return process(std::get<StringLiteral*>(token->var));
    else if(std::holds_alternative<Punctuator*>(token->var))
        return process(std::get<Punctuator*>(token->var));
    else
        return variantError("TOKEN::Token");

    return true;
}

bool RepresentationCreator::process(const TOKEN::Keyword *keyword)
{
    addToken(TOKEN::str(keyword));

    return true;
}

bool RepresentationCreator::process(const TOKEN::Punctuator *punctuator)
{
    addToken(TOKEN::str(punctuator));
    
    return true;
}

bool RepresentationCreator::process(const TOKEN::AttributeSpecifier *as)
{
    addToken("__attribute__");
    addToken("(");
    addToken("(");

    for(auto &&t : as->seq)
    {
        if(!process(t))
            return false;
    }

    addToken(")");
    addToken(")");

    return true;
}

bool RepresentationCreator::process(const TOKEN::AttributeSpecifierList *asl)
{
    for(auto &&as : asl->seq)
    {
        if(!process(as))
            return false;
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::AttributeStatement *as)
{
    if(!process(as->asl))
        return false;
    
    addToken(";");

    return true;
}

bool RepresentationCreator::process(const TOKEN::BasicAsm *ba)
{
    addToken("__asm__");
    
    if(ba->aq != nullptr
        && !process(ba->aq))
        return false;
    
    addToken("(");
    if(!process(ba->sl))
        return false;
    addToken(")");

    return true;
}

bool RepresentationCreator::process(const TOKEN::ExtendedAsm *ea)
{
    addToken("__asm__");

    if(ea->aq != nullptr
        && !process(ea->aq))
        return false;
    
    addToken("(");
    
    if(!process(ea->sl))
        return false;
    
    addToken(":");
    for(auto &&t : ea->oo)
    {
        if(!process(t))
            return false;
    }

    if(!ea->io.empty() || !ea->gl.empty())
    {
        addToken(":");
        for(auto &&t : ea->io)
        {
            if(!process(t))
                return false;
        }
    }

    if(!ea->clobbers.empty() || !ea->clobbers.empty())
    {
        addToken(":");
        for(auto &&t : ea->clobbers)
        {
            if(!process(t))
                return false;
        }
    }

    if(!ea->gl.empty())
    {
        addToken(":");
        for(auto &&t : ea->gl)
        {
            if(!process(t))
                return false;
        }
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::AsmQualifiers *aq)
{
    using AQ = TOKEN::AsmQualifiers;

    for(auto &&tag : aq->seq)
    {
        switch(tag)
        {
            case(AQ::Tag::VOLATILE):
                addToken("volatile");
                break;
            case(AQ::Tag::INLINE):
                addToken("inline");
                break;
            case(AQ::Tag::GOTO):
                addToken("goto");
                break;
            
            default:;
        }
    }

    return true;
}

bool RepresentationCreator::process(const TOKEN::AsmStatement *as)
{
    using namespace TOKEN;

    if(std::holds_alternative<BasicAsm*>(as->var))
    {
        if(!process(std::get<BasicAsm*>(as->var)))
            return false;
    }
    else if(std::holds_alternative<ExtendedAsm*>(as->var))
    {
        if(!process(std::get<ExtendedAsm*>(as->var)))
            return false;
    }
    else
        return variantError("TOKEN::AsmStatement");

    addToken(";");

    return true;
}

bool RepresentationCreator::setFunctionName(const TOKEN::Declarator *declarator)
{
    using DD = TOKEN::DirectDeclarator;

    std::string functionName;

    DD *dd{declarator->dd};
    while(true)
    {
        if(std::holds_alternative<DD::Si>(dd->seq.front()))
        {
            functionName = TOKEN::str(std::get<DD::Si>(dd->seq.front()).i);
            break;
        }
        else if(std::holds_alternative<DD::Sd>(dd->seq.front()))
            dd = std::get<DD::Sd>(dd->seq.front()).d->dd;
        else
            return variantError("TOKEN::DirectDeclarator");
    }

    mFunctionTokens.emplace_back();
    mFunctionTokens.back().first = functionName;
    
    return true;
}

bool RepresentationCreator::variantError(const std::string &className) const
{
    std::cerr << "SIM::RepresentationCreator::variantError():\n"
        "    class: " << className
        << std::endl;
    return false;
}

bool RepresentationCreator::tokenSizeError(const std::string &funcName) const
{
    std::cerr << "SIM::RepresentationCreator::tokenSizeError():\n"
        "    what: size of tokens is less than gram-size.\n"
        "    function-name: " << funcName
        << "\n    gram-size: " << mGramSize
        << std::endl;
    return false;
}

bool Type2RepresentationCreator::process(const TOKEN::TypeSpecifier *ts)
{
    using namespace TOKEN;
    using RC = RepresentationCreator;

    if(std::holds_alternative<TypeSpecifier::Tag>(ts->var))
        addToken(mTypeTagMap.at(TypeTag::DATA_TYPE));
    else if(std::holds_alternative<AtomicTypeSpecifier*>(ts->var))
        return RC::process(std::get<AtomicTypeSpecifier*>(ts->var));
    else if(std::holds_alternative<StructOrUnionSpecifier*>(ts->var))
        return RC::process(std::get<StructOrUnionSpecifier*>(ts->var));
    else if(std::holds_alternative<EnumSpecifier*>(ts->var))
        return RC::process(std::get<EnumSpecifier*>(ts->var));
    else if(std::holds_alternative<TypedefName*>(ts->var))
        return RC::process(std::get<TypedefName*>(ts->var));
    else
        return variantError("TOKEN::TypeSpecifier");

    return true;
}

bool Type2RepresentationCreator::process(const TOKEN::Identifier *identifier)
{
    addToken(mTypeTagMap.at(TypeTag::IDENTIFIER));

    return true;
}

bool Type2RepresentationCreator::process(const TOKEN::StringLiteral *sl)
{
    addToken(mTypeTagMap.at(TypeTag::STRING_LITERAL));

    return true;
}

bool Type2RepresentationCreator::process(const TOKEN::StructOrUnionSpecifier *sous)
{
    using SOUS = TOKEN::StructOrUnionSpecifier;
    using RC = RepresentationCreator;

    if(std::holds_alternative<SOUS::Ssou_i_sdl>(sous->var))
    {
        auto &&ssis{std::get<SOUS::Ssou_i_sdl>(sous->var)};
        if(!RC::process(ssis.sou)
            || !(ssis.asl != nullptr ? RC::process(ssis.asl) : true))
            return false;
        if(ssis.i != nullptr)
            addToken(mTypeTagMap.at(TypeTag::CLASS_TYPE));

        addToken("{");
        if(!RC::process(ssis.sdl))
            return false;
        addToken("}");
    }
    else if(std::holds_alternative<SOUS::Ssou_i>(sous->var))
    {
        auto &&ssi{std::get<SOUS::Ssou_i>(sous->var)};
        if(!RC::process(ssi.sou)
            || !(ssi.asl != nullptr ? RC::process(ssi.asl) : true))
            return false;
        addToken(mTypeTagMap.at(TypeTag::CLASS_TYPE));
    }
    else
        return variantError("TOKEN::StructOrUnionSpecifier");

    return true;
}

bool Type2RepresentationCreator::process(const TOKEN::EnumSpecifier *es)
{
    using ES = TOKEN::EnumSpecifier;
    using RC = RepresentationCreator;

    if(std::holds_alternative<ES::Si_el>(es->var))
    {
        auto &&sie{std::get<ES::Si_el>(es->var)};
        addToken("enum");
        if(!(sie.asl != nullptr ? RC::process(sie.asl) : true))
            return false;
        if(sie.i != nullptr)
            addToken(mTypeTagMap.at(TypeTag::CLASS_TYPE));
        addToken("{");
        if(!RC::process(sie.el))
            return false;
        addToken("}");
    }
    else if(std::holds_alternative<ES::Si>(es->var))
    {
        auto &&si{std::get<ES::Si>(es->var)};
        addToken("enum");
        if(!(si.asl != nullptr ? RC::process(si.asl) : true))
            return false;
        addToken(mTypeTagMap.at(TypeTag::CLASS_TYPE));
    }
    else
        return variantError("TOKEN::EnumSpecifier");

    return true;
}

bool Type2RepresentationCreator::process(const TOKEN::TypedefName *tn)
{
    addToken(mTypeTagMap.at(TypeTag::CLASS_TYPE));

    return true;
}

bool Type2RepresentationCreator::process(const TOKEN::IntegerConstant *ic)
{
    addToken(mTypeTagMap.at(TypeTag::NUMBER));

    return true;
}

bool Type2RepresentationCreator::process(const TOKEN::FloatingConstant *fc)
{
    addToken(mTypeTagMap.at(TypeTag::NUMBER));

    return true;
}

bool Type2RepresentationCreator::process(const TOKEN::CharacterConstant *c)
{
    addToken(mTypeTagMap.at(TypeTag::NUMBER));
    
    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::StorageClassSpecifier *scs)
{
    addToken(mTypeTagMap.at(TypeTag::KEYWORD));

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::FunctionSpecifier *fs)
{
    addToken(mTypeTagMap.at(TypeTag::KEYWORD));

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::AlignmentSpecifier *as)
{
    using namespace TOKEN;
    using RC = RepresentationCreator;

    addToken(mTypeTagMap.at(TypeTag::KEYWORD));
    addToken("(");

    if(std::holds_alternative<TypeName*>(as->var))
    {
        if(!RC::process(std::get<TypeName*>(as->var)))
            return false;
    }
    else if(std::holds_alternative<ConstantExpression*>(as->var))
    {
        if(!RC::process(std::get<ConstantExpression*>(as->var)))
            return false;
    }
    else
        variantError("TOKEN::AlignmentSpecifier");
    
    addToken(")");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::Pointer *pointer)
{
    using namespace TOKEN;
    using RC = RepresentationCreator;

    addToken(mTypeTagMap.at(TypeTag::OPERATOR));

    if(std::holds_alternative<Pointer::Stql>(pointer->var))
    {
        auto &&stql{std::get<Pointer::Stql>(pointer->var)};
        if(!(stql.tql != nullptr ? RC::process(stql.tql) : true))
            return false;
    }
    else if(std::holds_alternative<Pointer::Stql_p>(pointer->var))
    {
        auto &&stp{std::get<Pointer::Stql_p>(pointer->var)};
        if(!(stp.tql != nullptr ? RC::process(stp.tql) : true)
            || !RC::process(stp.p))
            return false;
    }
    else
        return variantError("TOKEN::Pointer");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::DirectDeclarator *dd)
{
    using DD = TOKEN::DirectDeclarator;
    using RC = RepresentationCreator;
    using T2 = Type2RepresentationCreator;

    for(auto &&var : dd->seq)
    {
        if(std::holds_alternative<DD::Si>(var))
        {
            auto &&si{std::get<DD::Si>(var)};
            if(!T2::process(si.i))
                return false;
        }
        else if(std::holds_alternative<DD::Sd>(var))
        {
            auto &&sd{std::get<DD::Sd>(var)};
            addToken("(");
            if(!RC::process(sd.d))
                return false;
            addToken(")");
        }
        else if(std::holds_alternative<DD::Stql_ae>(var))
        {
            auto &&sta{std::get<DD::Stql_ae>(var)};
            addToken("[");
            if(sta.hasStatic)
                addToken(mTypeTagMap.at(TypeTag::KEYWORD));
            if(!(sta.tql != nullptr ? RC::process(sta.tql) : true)
                || !(sta.ae != nullptr ? RC::process(sta.ae) : true))
                return false;
            addToken("]");
        }
        else if(std::holds_alternative<DD::Stql>(var))
        {
            auto &&st{std::get<DD::Stql>(var)};
            addToken("[");
            if(!(st.tql != nullptr ? RC::process(st.tql) : true))
                return false;
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            addToken("]");
        }
        else if(std::holds_alternative<DD::Sptl>(var))
        {
            auto &&sp{std::get<DD::Sptl>(var)};
            addToken("(");
            if(!process(sp.ptl))
                return false;
            addToken(")");
        }
        else if(std::holds_alternative<DD::Sil>(var))
        {
            auto &&si{std::get<DD::Sil>(var)};
            addToken("(");
            if(!(si.il != nullptr ? RC::process(si.il) : true))
                return false;
            addToken(")");
        }
        else
            return variantError("TOKEN::DirectDeclarator");
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::ParameterTypeList *ptl)
{
    using RC = RepresentationCreator;

    if(!RC::process(ptl->pl))
        return false;

    if(ptl->isValiable)
    {
        addToken(mTypeTagMap.at(TypeTag::OPERATOR));
        addToken(mTypeTagMap.at(TypeTag::OPERATOR));
    }
    
    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::StaticAssertDeclaration *sad)
{
    using RC = RepresentationCreator;
    using T2 = Type2RepresentationCreator;

    addToken(mTypeTagMap.at(TypeTag::KEYWORD));
    addToken("(");
    if(!RC::process(sad->ce))
        return false;
    addToken(",");
    if(!T2::process(sad->sl))
        return false;
    addToken(")");
    addToken(";");
    
    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::TypeQualifier *tq)
{
    addToken(mTypeTagMap.at(TypeTag::KEYWORD));

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::ConditionalExpression *ce)
{
    using RC = RepresentationCreator;
    using CE = TOKEN::ConditionalExpression;

    if(std::holds_alternative<CE::Slore>(ce->var))
    {
        auto &&sl{std::get<CE::Slore>(ce->var)};
        if(!process(sl.lore))
            return false;
    }
    else if(std::holds_alternative<CE::Slore_e_ce>(ce->var))
    {
        auto &&slec{std::get<CE::Slore_e_ce>(ce->var)};
        if(!process(slec.lore))
            return false;
        addToken(mTypeTagMap.at(TypeTag::OPERATOR));
        if(!RC::process(slec.e))
            return false;
        addToken(mTypeTagMap.at(TypeTag::OPERATOR));
        if(!process(slec.ce))
            return false;
    }
    else
        variantError("TOKEN::ConditionalExpression");
    
    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::UnaryExpression *ue)
{
    using RC = RepresentationCreator;
    using UE = TOKEN::UnaryExpression;

    if(std::holds_alternative<UE::Spe>(ue->var))
    {
        auto &&sp{std::get<UE::Spe>(ue->var)};
        if(!process(sp.pe))
            return false;
    }
    else if(std::holds_alternative<UE::Si_ue>(ue->var))
    {
        auto &&siu{std::get<UE::Si_ue>(ue->var)};
        addToken(mTypeTagMap.at(TypeTag::OPERATOR));
        if(!process(siu.ue))
            return false;
    }
    else if(std::holds_alternative<UE::Sd_ue>(ue->var))
    {
        auto &&sdu{std::get<UE::Sd_ue>(ue->var)};
        addToken(mTypeTagMap.at(TypeTag::OPERATOR));
        if(!process(sdu.ue))
            return false;
    }
    else if(std::holds_alternative<UE::Suo_ce>(ue->var))
    {
        auto &&suc{std::get<UE::Suo_ce>(ue->var)};
        if(!process(suc.uo)
            || !RC::process(suc.ce))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_ue>(ue->var))
    {
        auto &&ssu{std::get<UE::Ss_ue>(ue->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        if(!process(ssu.ue))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_tn>(ue->var))
    {
        auto &&sst{std::get<UE::Ss_tn>(ue->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken("(");
        if(!RC::process(sst.tn))
            return false;
        addToken(")");
    }
    else if(std::holds_alternative<UE::Sa_tn>(ue->var))
    {
        auto &&sat{std::get<UE::Sa_tn>(ue->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken("(");
        if(!RC::process(sat.tn))
            return false;
        addToken(")");
    }
    else
        return variantError("TOKEN::UnaryExpression");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::AssignmentOperator *ao)
{
    addToken(mTypeTagMap.at(TypeTag::OPERATOR));

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::InitDeclarator *id)
{
    using RC = RepresentationCreator;
    using ID = TOKEN::InitDeclarator;

    if(std::holds_alternative<ID::Sd>(id->var))
    {
        auto &&sd{std::get<ID::Sd>(id->var)};
        if(!RC::process(sd.d))
            return false;
    }
    else if(std::holds_alternative<ID::Sd_i>(id->var))
    {
        auto &&sdi{std::get<ID::Sd_i>(id->var)};
        if(!RC::process(sdi.d))
            return false;
        addToken(mTypeTagMap.at(TypeTag::OPERATOR));
        if(!RC::process(sdi.i))
            return false;
    }
    else
        return variantError("TOKEN::InitDeclarator");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::LogicalORExpression *lore)
{
    return processAgainstSequence(lore->seq, mTypeTagMap.at(TypeTag::OPERATOR));
}

bool Type3RepresentationCreator::process(const TOKEN::PostfixExpression *pe)
{
    using RC = RepresentationCreator;
    using T2 = Type2RepresentationCreator;
    using PE = TOKEN::PostfixExpression;

    for(auto &&var : pe->seq)
    {
        if(std::holds_alternative<PE::Spe>(var))
        {
            auto &&sp{std::get<PE::Spe>(var)};
            if(!RC::process(sp.pe))
                return false;
        }
        else if(std::holds_alternative<PE::Se>(var))
        {
            auto &&se{std::get<PE::Se>(var)};
            addToken("[");
            if(!RC::process(se.e))
                return false;
            addToken("]");
        }
        else if(std::holds_alternative<PE::Sael>(var))
        {
            auto &&sa{std::get<PE::Sael>(var)};
            addToken("(");
            if(!(sa.ael != nullptr ? RC::process(sa.ael) : true))
                return false;
            addToken(")");
        }
        else if(std::holds_alternative<PE::Sp_i>(var))
        {
            auto &&si{std::get<PE::Sp_i>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!T2::process(si.i))
                return false;
        }
        else if(std::holds_alternative<PE::Sa_i>(var))
        {
            auto &&si{std::get<PE::Sa_i>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!T2::process(si.i))
                return false;
        }
        else if(std::holds_alternative<PE::Si>(var))
        {
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
        }
        else if(std::holds_alternative<PE::Sd>(var))
        {
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
        }
        else if(std::holds_alternative<PE::Stn_il>(var))
        {
            auto &&sti{std::get<PE::Stn_il>(var)};
            addToken("(");
            if(!RC::process(sti.tn))
                return false;
            addToken(")");
            addToken("{");
            if(!RC::process(sti.il))
                return false;
            addToken("}");
        }
        else
            return variantError("TOKEN::PostfixExpression");
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::UnaryOperator *uo)
{
    addToken(mTypeTagMap.at(TypeTag::OPERATOR));

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::LabeledStatement *ls)
{
    using RC = RepresentationCreator;
    using T2 = Type2RepresentationCreator;
    using LS = TOKEN::LabeledStatement;

    if(std::holds_alternative<LS::Si_s>(ls->var))
    {
        auto &&sis{std::get<LS::Si_s>(ls->var)};
        if(!T2::process(sis.i))
            return false;
        addToken(":");
        if(!RC::process(sis.s))
            return false;
    }
    else if(std::holds_alternative<LS::Sce_s>(ls->var))
    {
        auto &&scs{std::get<LS::Sce_s>(ls->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        if(!RC::process(scs.ce))
            return false;
        addToken(":");
        if(!RC::process(scs.s))
            return false;
    }
    else if(std::holds_alternative<LS::Ss>(ls->var))
    {
        auto &&ss{std::get<LS::Ss>(ls->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken(":");
        if(!RC::process(ss.s))
            return false;
    }
    else
        return variantError("TOKEN::LabeledStatement");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::SelectionStatement *ss)
{
    using RC = RepresentationCreator;
    using SS = TOKEN::SelectionStatement;

    if(std::holds_alternative<SS::Si_e_s>(ss->var))
    {
        auto &&ses{std::get<SS::Si_e_s>(ss->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken("(");
        if(!RC::process(ses.e))
            return false;
        addToken(")");
        if(!RC::process(ses.s))
            return false;
    }
    else if(std::holds_alternative<SS::Si_e_s_s>(ss->var))
    {
        auto &&sess{std::get<SS::Si_e_s_s>(ss->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken("(");
        if(!RC::process(sess.e))
            return false;
        addToken(")");
        if(!RC::process(sess.s0))
            return false;
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        if(!RC::process(sess.s1))
            return false;
    }
    else if(std::holds_alternative<SS::Ss_e_s>(ss->var))
    {
        auto &&ses{std::get<SS::Ss_e_s>(ss->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken("(");
        if(!RC::process(ses.e))
            return false;
        addToken(")");
        if(!RC::process(ses.s))
            return false;
    }
    else
        return variantError("TOKEN::SelectionStatement");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::IterationStatement *is)
{
    using RC = RepresentationCreator;
    using IS = TOKEN::IterationStatement;

    if(std::holds_alternative<IS::Sw_e_s>(is->var))
    {
        auto &&ses{std::get<IS::Sw_e_s>(is->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken("(");
        if(!RC::process(ses.e))
            return false;
        addToken(")");
        if(!RC::process(ses.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sd_s_e>(is->var))
    {
        auto &&sse{std::get<IS::Sd_s_e>(is->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        if(!RC::process(sse.s))
            return false;
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken("(");
        if(!RC::process(sse.e))
            return false;
        addToken(")");
        addToken(";");
    }
    else if(std::holds_alternative<IS::Sf_e_e_e_s>(is->var))
    {
        auto &&seees{std::get<IS::Sf_e_e_e_s>(is->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken("(");
        if(!(seees.e0 != nullptr ? RC::process(seees.e0) : true))
            return false;
        addToken(";");
        if(!(seees.e1 != nullptr ? RC::process(seees.e1) : true))
            return false;
        addToken(";");
        if(!(seees.e2 != nullptr ? RC::process(seees.e2) : true))
            return false;
        addToken(")");
        if(!RC::process(seees.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sf_d_e_e_s>(is->var))
    {
        auto &&sdees{std::get<IS::Sf_d_e_e_s>(is->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken("(");
        if(!RC::process(sdees.d)
            || !(sdees.e0 != nullptr ? RC::process(sdees.e0) : true))
            return false;
        addToken(";");
        if(!(sdees.e1 != nullptr ? RC::process(sdees.e1) : true))
            return false;
        addToken(")");
        if(!RC::process(sdees.s))
            return false;
    }
    else
        return variantError("TOKEN::IterationStatement");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::JumpStatement *js)
{
    using RC = RepresentationCreator;
    using T2 = RepresentationCreator;
    using JS = TOKEN::JumpStatement;

    if(std::holds_alternative<JS::Sg_i>(js->var))
    {
        auto &&si{std::get<JS::Sg_i>(js->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        if(!T2::process(si.i))
            return false;
        addToken(";");
    }
    else if(std::holds_alternative<JS::Sc>(js->var))
    {
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken(";");
    }
    else if(std::holds_alternative<JS::Sb>(js->var))
    {
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken(";");
    }
    else if(std::holds_alternative<JS::Sr_e>(js->var))
    {
        auto &&se{std::get<JS::Sr_e>(js->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        if(!(se.e != nullptr ? RC::process(se.e) : true))
            return false;
        addToken(";");
    }
    else
        return variantError("TOKEN::JumpStatement");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::LogicalANDExpression *lande)
{
    return processAgainstSequence(lande->seq, mTypeTagMap.at(TypeTag::OPERATOR));
}

bool Type3RepresentationCreator::process(const TOKEN::InclusiveORExpression *iore)
{
    return processAgainstSequence(iore->seq, mTypeTagMap.at(TypeTag::OPERATOR));
}

bool Type3RepresentationCreator::process(const TOKEN::GenericSelection *gs)
{
    using RC = RepresentationCreator;

    addToken(mTypeTagMap.at(TypeTag::KEYWORD));
    addToken("(");
    if(!RC::process(gs->ae))
        return false;
    addToken(",");
    if(!RC::process(gs->gal))
        return false;
    addToken(")");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::Designation *designation)
{
    using RC = RepresentationCreator;

    if(!RC::process(designation->dl))
        return false;
    
    addToken(mTypeTagMap.at(TypeTag::OPERATOR));
    
    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::AtomicTypeSpecifier *ats)
{
    using RC = RepresentationCreator;

    addToken(mTypeTagMap.at(TypeTag::KEYWORD));
    addToken("(");
    if(!RC::process(ats->tn))
        return false;
    addToken(")");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::EnumSpecifier *es)
{
    using RC = RepresentationCreator;
    using ES = TOKEN::EnumSpecifier;

    if(std::holds_alternative<ES::Si_el>(es->var))
    {
        auto &&sie{std::get<ES::Si_el>(es->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        if(sie.i != nullptr)
            addToken(mTypeTagMap.at(TypeTag::CLASS_TYPE));
        addToken("{");
        if(!RC::process(sie.el))
            return false;
        addToken("}");
    }
    else if(std::holds_alternative<ES::Si>(es->var))
    {
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken(mTypeTagMap.at(TypeTag::CLASS_TYPE));
    }
    else
        return variantError("TOKEN::EnumSpecifier");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::DirectAbstractDeclarator *dad)
{
    using RC = RepresentationCreator;
    using DAD = TOKEN::DirectAbstractDeclarator;

    for(auto &&var : dad->seq)
    {
        if(std::holds_alternative<DAD::Sad>(var))
        {
            auto &&sa{std::get<DAD::Sad>(var)};
            addToken("(");
            if(!RC::process(sa.ad))
                return false;
            addToken(")");
        }
        else if(std::holds_alternative<DAD::Stql_ae>(var))
        {
            auto &&sta{std::get<DAD::Stql_ae>(var)};
            addToken("[");
            if(sta.hasStatic)
                addToken(mTypeTagMap.at(TypeTag::KEYWORD));
            if(!(sta.tql != nullptr ? RC::process(sta.tql) : true)
                || !(sta.ae != nullptr ? RC::process(sta.ae) : true))
                return false;
            addToken("]");
        }
        else if(std::holds_alternative<DAD::Sp>(var))
        {
            addToken("[");
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            addToken("]");
        }
        else if(std::holds_alternative<DAD::Sptl>(var))
        {
            auto &&sp{std::get<DAD::Sptl>(var)};
            addToken("(");
            if(!(sp.ptl != nullptr ? process(sp.ptl) : true))
                return false;
            addToken(")");
        }
        else
            return variantError("TOKEN::DirectAbstractDeclarator");
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::ExclusiveORExpression *eore)
{
    return processAgainstSequence(eore->seq, mTypeTagMap.at(TypeTag::OPERATOR));
}

bool Type3RepresentationCreator::process(const TOKEN::StructOrUnion *sou)
{
    addToken(mTypeTagMap.at(TypeTag::KEYWORD));
    
    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::ANDExpression *ande)
{
    return processAgainstSequence(ande->seq, mTypeTagMap.at(TypeTag::OPERATOR));
}

bool Type3RepresentationCreator::process(const TOKEN::GenericAssociation *ga)
{
    using RC = RepresentationCreator;
    using GA = TOKEN::GenericAssociation;

    if(std::holds_alternative<GA::Stn_ae>(ga->var))
    {
        auto &&sta{std::get<GA::Stn_ae>(ga->var)};
        if(!RC::process(sta.tn))
            return false;
        addToken(":");
        if(!RC::process(sta.ae))
            return false;
    }
    else if(std::holds_alternative<GA::Sae>(ga->var))
    {
        auto &&sa{std::get<GA::Sae>(ga->var)};
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
        addToken(":");
        if(!RC::process(sa.ae))
            return false;
    }
    else
        return variantError("TOKEN::GEnericAssociation");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::Enumerator *enumerator)
{
    using RC = RepresentationCreator;
    using E = TOKEN::Enumerator;

    if(std::holds_alternative<E::Sec>(enumerator->var))
    {
        auto &&se{std::get<E::Sec>(enumerator->var)};
        if(!RC::process(se.ec))
            return false;
    }
    else if(std::holds_alternative<E::Sec_ce>(enumerator->var))
    {
        auto &&sec{std::get<E::Sec_ce>(enumerator->var)};
        if(!RC::process(sec.ec))
            return false;
        addToken(mTypeTagMap.at(TypeTag::OPERATOR));
        if(!RC::process(sec.ce))
            return false;
    }
    else
        return variantError("TOKEN::Enumerator");

    return true;    
}

bool Type3RepresentationCreator::process(const TOKEN::EqualityExpression *ee)
{
    using EE = TOKEN::EqualityExpression;

    for(auto &&var : ee->seq)
    {
        if(std::holds_alternative<EE::Sre>(var))
        {
            auto &&sr{std::get<EE::Sre>(var)};
            if(!process(sr.re))
                return false;
        }
        else if(std::holds_alternative<EE::Se_re>(var))
        {
            auto &&sr{std::get<EE::Se_re>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(sr.re))
                return false;
        }
        else if(std::holds_alternative<EE::Sne_re>(var))
        {
            auto &&sr{std::get<EE::Sne_re>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(sr.re))
                return false;
        }
        else
            return variantError("TOKEN::EqualityExpression");
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::RelationalExpression *re)
{
    using RE = TOKEN::RelationalExpression;

    for(auto &&var : re->seq)
    {
        if(std::holds_alternative<RE::Sse>(var))
        {
            auto &&ss{std::get<RE::Sse>(var)};
            if(!process(ss.se))
                return false;
        }
        else if(std::holds_alternative<RE::Sl_se>(var))
        {
            auto &&ss{std::get<RE::Sl_se>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(ss.se))
                return false;
        }
        else if(std::holds_alternative<RE::Sg_se>(var))
        {
            auto &&ss{std::get<RE::Sg_se>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(ss.se))
                return false;
        }
        else if(std::holds_alternative<RE::Sle_se>(var))
        {
            auto &&ss{std::get<RE::Sle_se>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(ss.se))
                return false;
        }
        else if(std::holds_alternative<RE::Sge_se>(var))
        {
            auto &&ss{std::get<RE::Sge_se>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(ss.se))
                return false;
        }
        else
            return variantError("TOKEN::RelationalExpression");
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::ShiftExpression *se)
{
    using SE = TOKEN::ShiftExpression;

    for(auto &&var : se->seq)
    {
        if(std::holds_alternative<SE::Sae>(var))
        {
            auto &&sa{std::get<SE::Sae>(var)};
            if(!process(sa.ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sl_ae>(var))
        {
            auto &&sa{std::get<SE::Sl_ae>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(sa.ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sr_ae>(var))
        {
            auto &&sa{std::get<SE::Sr_ae>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(sa.ae))
                return false;
        }
        else
            return variantError("TOKEN::ShiftExpression");
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::AdditiveExpression *ae)
{
    using AE = TOKEN::AdditiveExpression;

    for(auto &&var : ae->seq)
    {
        if(std::holds_alternative<AE::Sme>(var))
        {
            auto &&sm{std::get<AE::Sme>(var)};
            if(!process(sm.me))
                return false;
        }
        else if(std::holds_alternative<AE::Sa_me>(var))
        {
            auto &&sm{std::get<AE::Sa_me>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(sm.me))
                return false;
        }
        else if(std::holds_alternative<AE::Ss_me>(var))
        {
            auto &&sm{std::get<AE::Ss_me>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!process(sm.me))
                return false;
        }
        else
            return variantError("TOKEN::AdditiveExpression");
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::MultiplicativeExpression *me)
{
    using RC = RepresentationCreator;
    using ME = TOKEN::MultiplicativeExpression;

    for(auto &&var : me->seq)
    {
        if(std::holds_alternative<ME::Sce>(var))
        {
            auto &&sc{std::get<ME::Sce>(var)};
            if(!RC::process(sc.ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sm_ce>(var))
        {
            auto &&sc{std::get<ME::Sm_ce>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!RC::process(sc.ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sd_ce>(var))
        {
            auto &&sc{std::get<ME::Sd_ce>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!RC::process(sc.ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sr_ce>(var))
        {
            auto &&sc{std::get<ME::Sr_ce>(var)};
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            if(!RC::process(sc.ce))
                return false;
        }
        else
            return variantError("TOKEN::MultiplicativeExpression");
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::Keyword *keyword)
{
    addToken(mTypeTagMap.at(TypeTag::KEYWORD));

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::Punctuator *punctuator)
{
    using namespace TOKEN;

    switch(punctuator->tag)
    {
        case(Punctuator::Tag::L_SQUARE_BRACKET):
        case(Punctuator::Tag::R_SQUARE_BRACKET):
        case(Punctuator::Tag::L_PARENTHESIS):
        case(Punctuator::Tag::R_PARENTHESIS):
        case(Punctuator::Tag::L_CURLY_BRACKET):
        case(Punctuator::Tag::R_CURLY_BRACKET):
        case(Punctuator::Tag::COLON):
        case(Punctuator::Tag::SEMICOLON):
        case(Punctuator::Tag::COMMA):
        case(Punctuator::Tag::TRIPLE_PERIOD):
            addToken(str(punctuator));
            break;
        
        default:
            addToken(mTypeTagMap.at(TypeTag::OPERATOR));
            break;
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::AttributeSpecifier *as)
{
    using RC = RepresentationCreator;

    addToken(mTypeTagMap.at(TypeTag::KEYWORD));
    addToken("(");
    addToken("(");
    
    for(auto &&t : as->seq)
    {
        if(!RC::process(t))
            return false;
    }

    addToken(")");
    addToken(")");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::BasicAsm *ba)
{
    using T2 = Type2RepresentationCreator;

    addToken(mTypeTagMap.at(TypeTag::KEYWORD));

    if(ba->aq != nullptr
        && !process(ba->aq))
        return false;
    
    addToken("(");
    if(!T2::process(ba->sl))
        return false;
    addToken(")");

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::ExtendedAsm *ea)
{
    using RC = RepresentationCreator;
    using T2 = Type2RepresentationCreator;

    addToken(mTypeTagMap.at(TypeTag::KEYWORD));

    if(ea->aq != nullptr
        && !process(ea->aq))
        return false;
    
    addToken("(");
    
    if(!T2::process(ea->sl))
        return false;
    
    addToken(":");
    for(auto &&t : ea->oo)
    {
        if(!RC::process(t))
            return false;
    }

    if(!ea->io.empty() || !ea->gl.empty())
    {
        addToken(":");
        for(auto &&t : ea->io)
        {
            if(!RC::process(t))
                return false;
        }
    }

    if(!ea->clobbers.empty() || !ea->clobbers.empty())
    {
        addToken(":");
        for(auto &&t : ea->clobbers)
        {
            if(!RC::process(t))
                return false;
        }
    }

    if(!ea->gl.empty())
    {
        addToken(":");
        for(auto &&t : ea->gl)
        {
            if(!RC::process(t))
                return false;
        }
    }

    return true;
}

bool Type3RepresentationCreator::process(const TOKEN::AsmQualifiers *aq)
{
    for(std::size_t i{0ull}; i < aq->seq.size(); i++)
        addToken(mTypeTagMap.at(TypeTag::KEYWORD));
    
    return true;
}

}