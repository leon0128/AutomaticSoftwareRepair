#include <iostream>

#include "../token.hpp"
#include "structure_token_metrics.hpp"
#include "token_metricer.hpp"

namespace SIM
{

TokenMetricer::TokenMetricer()
    : mCurrentFilename{}
    , mCurrentSTM{}
    , mSTMs{}
{
}

bool TokenMetricer::execute(const std::string &filename
    , const TOKEN::TranslationUnit *tu)
{
    mCurrentFilename = filename;

    if(!process(tu))
        return false;

    return true;
}

bool TokenMetricer::process(const TOKEN::Identifier *identifier)
{
    using STM = StructureTokenMetrics<std::size_t>;

    mCurrentSTM->array()[STM::IDENTIFIER]++;

    return true;
}

bool TokenMetricer::process(const TOKEN::TranslationUnit *tu)
{
    for(const auto &ed : tu->seq)
    {
        if(!process(ed))
            return false;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::ExternalDeclaration *ed)
{
    using namespace TOKEN;

    if(std::holds_alternative<FunctionDefinition*>(ed->var))
        return process(std::get<FunctionDefinition*>(ed->var));
    else if(std::holds_alternative<Declaration*>(ed->var))
        ;
    else
        return invalidVariantError("TOKEN::ExternalDeclaration");

    return true;
}

bool TokenMetricer::process(const TOKEN::FunctionDefinition *fd)
{
    mCurrentSTM.reset(new StructureTokenMetrics<std::size_t>{});

    mCurrentSTM->filename() = mCurrentFilename;
    mCurrentSTM->functionName() = getIdentifier(fd->d);

    if(!process(fd->ds)
        || !process(fd->d)
        || !(fd->dl ? process(fd->dl) : true)
        || !process(fd->cs))
    {
        mCurrentSTM.reset();
        return false;
    }

    mSTMs.push_back(mCurrentSTM);
    mCurrentSTM.reset();

    return true;
}

bool TokenMetricer::process(const TOKEN::Declaration *declaration)
{
    using namespace TOKEN;
    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<Declaration::Sds_idl>(declaration->var))
    {
        auto &&s{std::get<Declaration::Sds_idl>(declaration->var)};
        if(!process(s.ds)
            || !(s.idl ? process(s.idl) : true))
            return false;
        
        mCurrentSTM->array()[STM::SEMICOLON]++;
    }
    else if(std::holds_alternative<Declaration::Ssad>(declaration->var))
    {
        auto &&s{std::get<Declaration::Ssad>(declaration->var)};
        if(!process(s.sad))
            return false;
    }
    else
        return invalidVariantError("TOKEN::Declaration");

    return true;
}

bool TokenMetricer::process(const TOKEN::InitDeclaratorList *idl)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < idl->seq.size();
        i++)
    {
        if(!process(idl->seq[i]))
            return false;
        
        if(i + 1ull < idl->seq.size())
            mCurrentSTM->array()[STM::COMMA]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::InitDeclarator *id)
{
    using namespace TOKEN;
    using ID = InitDeclarator;
    
    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<ID::Sd>(id->var))
    {
        auto &&s{std::get<ID::Sd>(id->var)};
        if(!process(s.d))
            return false;
    }
    else if(std::holds_alternative<ID::Sd_i>(id->var))
    {
        auto &&s{std::get<ID::Sd_i>(id->var)};
        if(!process(s.d))
            return false;
        
        mCurrentSTM->array()[STM::ASSIGNMENT]++;

        if(!process(s.i))
            return false;
    }
    else
        return invalidVariantError("TOKEN::InitDeclarator");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::Statement *statement)
{
    if(std::holds_alternative<TOKEN::ExpressionStatement*>(statement->var))
        return process(std::get<TOKEN::ExpressionStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::JumpStatement*>(statement->var))
        return process(std::get<TOKEN::JumpStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::LabeledStatement*>(statement->var))
        return process(std::get<TOKEN::LabeledStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::CompoundStatement*>(statement->var))
        return process(std::get<TOKEN::CompoundStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::SelectionStatement*>(statement->var))
        return process(std::get<TOKEN::SelectionStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::IterationStatement*>(statement->var))
        return process(std::get<TOKEN::IterationStatement*>(statement->var));
    else
        return invalidStatementError();

    return true;
}

bool TokenMetricer::process(const TOKEN::JumpStatement *js)
{
    using JS = TOKEN::JumpStatement;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<JS::Sg_i>(js->var))
    {
        auto &&s{std::get<JS::Sg_i>(js->var)};

        mCurrentSTM->array()[STM::GOTO]++;
        
        if(!process(s.i))
            return false;
        
        mCurrentSTM->array()[STM::SEMICOLON];
    }
    else if(std::holds_alternative<JS::Sc>(js->var))
    {
        mCurrentSTM->array()[STM::CONTINUE]++;
        mCurrentSTM->array()[STM::SEMICOLON]++;
    }
    else if(std::holds_alternative<JS::Sb>(js->var))
    {
        mCurrentSTM->array()[STM::BREAK]++;
        mCurrentSTM->array()[STM::SEMICOLON]++;
    }
    else if(std::holds_alternative<JS::Sr_e>(js->var))
    {
        auto &&s{std::get<JS::Sr_e>(js->var)};
        
        mCurrentSTM->array()[STM::RETURN]++;

        if(!(s.e ? process(s.e) : true))
            return false;
        
        mCurrentSTM->array()[STM::SEMICOLON]++;
    }
    else
        return invalidVariantError("TOKEN::JumpStatement");
        
    return true;
}

bool TokenMetricer::process(const TOKEN::ExpressionStatement *es)
{
    using STM = StructureTokenMetrics<std::size_t>;

    if(!(es->e ? process(es->e) : true))
        return false;
    
    mCurrentSTM->array()[STM::SEMICOLON]++;

    return true;
}

bool TokenMetricer::process(const TOKEN::LabeledStatement *ls)
{
    using LS = TOKEN::LabeledStatement;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<LS::Si_s>(ls->var))
    {
        auto &&s{std::get<LS::Si_s>(ls->var)};
        if(!process(s.i))
            return false;

        mCurrentSTM->array()[STM::COLON]++;
        
        if(!process(s.s))
            return false;
    }
    else if(std::holds_alternative<LS::Sce_s>(ls->var))
    {
        auto &&s{std::get<LS::Sce_s>(ls->var)};
    
        mCurrentSTM->array()[STM::CASE]++;
    
        if(!process(s.ce))
            return false;

        mCurrentSTM->array()[STM::COLON]++;
        
        if(!process(s.s))
            return false;
    }
    else if(std::holds_alternative<LS::Ss>(ls->var))
    {
        auto &&s{std::get<LS::Ss>(ls->var)};

        mCurrentSTM->array()[STM::DEFAULT]++;
        mCurrentSTM->array()[STM::COLON]++;

        if(!process(s.s))
            return false;
    }
    else
        return invalidVariantError("TOKEN::LabeledStatement");

    return true;
}

bool TokenMetricer::process(const TOKEN::CompoundStatement *cs)
{
    using namespace TOKEN;

    using STM = StructureTokenMetrics<std::size_t>;

    mCurrentSTM->array()[STM::L_CURLY_BRACKET]++;

    if(!(cs->bil ? process(cs->bil) : true))
        return false;
    
    mCurrentSTM->array()[STM::R_CURLY_BRACKET]++;

    return true;
}

bool TokenMetricer::process(const TOKEN::BlockItemList *bil)
{
    for(const auto &bi : bil->seq)
    {
        if(!process(bi))
            return false;
    }
    
    return true;
}

bool TokenMetricer::process(const TOKEN::BlockItem *bi)
{
    using namespace TOKEN;

    if(std::holds_alternative<Declaration*>(bi->var))
    {
        if(!process(std::get<Declaration*>(bi->var)))
            return false;
    }
    else if(std::holds_alternative<Statement*>(bi->var))
    {
        if(!process(std::get<Statement*>(bi->var)))
            return false;
    }
    else
        return invalidVariantError("TOKEN::BlockItem");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::SelectionStatement *ss)
{
    using SS = TOKEN::SelectionStatement;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<SS::Si_e_s>(ss->var))
    {
        auto &&s{std::get<SS::Si_e_s>(ss->var)};

        mCurrentSTM->array()[STM::IF]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(s.e))
            return false;

        mCurrentSTM->array()[STM::R_PARENTHESIS]++;
        
        if(!process(s.s))
            return false;
    }
    else if(std::holds_alternative<SS::Si_e_s_s>(ss->var))
    {
        auto &&s{std::get<SS::Si_e_s_s>(ss->var)};

        mCurrentSTM->array()[STM::IF]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(s.e))
            return false;
        
        mCurrentSTM->array()[STM::R_PARENTHESIS]++;

        if(!process(s.s0))
            return false;

        mCurrentSTM->array()[STM::ELSE]++;

        if(!process(s.s1))
            return false;
    }
    else if(std::holds_alternative<SS::Ss_e_s>(ss->var))
    {
        auto &&s{std::get<SS::Ss_e_s>(ss->var)};

        mCurrentSTM->array()[STM::SWITCH]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(s.e))
            return false;
        
        mCurrentSTM->array()[STM::R_PARENTHESIS]++;

        if(!process(s.s))
            return false;
    }
    else
        return invalidVariantError("SelectionStatement");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::IterationStatement *is)
{
    using IS = TOKEN::IterationStatement;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<IS::Sw_e_s>(is->var))
    {
        auto &&s{std::get<IS::Sw_e_s>(is->var)};
        
        mCurrentSTM->array()[STM::WHILE]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;
        
        if(!process(s.e))
            return false;

        mCurrentSTM->array()[STM::R_PARENTHESIS]++;
        
        if(!process(s.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sd_s_e>(is->var))
    {
        auto &&s{std::get<IS::Sd_s_e>(is->var)};

        mCurrentSTM->array()[STM::DO]++;

        if(!process(s.s))
            return false;

        mCurrentSTM->array()[STM::WHILE]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;
        
        if(!process(s.e))
            return false;

        mCurrentSTM->array()[STM::R_PARENTHESIS]++;
        mCurrentSTM->array()[STM::SEMICOLON]++;
    }
    else if(std::holds_alternative<IS::Sf_e_e_e_s>(is->var))
    {
        auto &&s{std::get<IS::Sf_e_e_e_s>(is->var)};
        
        mCurrentSTM->array()[STM::FOR]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!(s.e0 ? process(s.e0) : true))
            return false;
        
        mCurrentSTM->array()[STM::SEMICOLON]++;

        if(!(s.e1 ? process(s.e1) : true))
            return false;

        mCurrentSTM->array()[STM::SEMICOLON]++;

        if(!(s.e2 ? process(s.e2) : true))
            return false;
        
        mCurrentSTM->array()[STM::R_PARENTHESIS]++;

        if(!process(s.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sf_d_e_e_s>(is->var))
    {
        auto &&s{std::get<IS::Sf_d_e_e_s>(is->var)};

        mCurrentSTM->array()[STM::FOR]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(s.d))
            return false;
        
        if(!(s.e0 ? process(s.e0) : true))
            return false;
        
        mCurrentSTM->array()[STM::SEMICOLON]++;

        if(!(s.e1 ? process(s.e1) : true))
            return false;
        
        mCurrentSTM->array()[STM::R_PARENTHESIS]++;

        if(!process(s.s))
            return false;
    }
    else
        return invalidVariantError("IterationStatement");

    return true;
}

bool TokenMetricer::process(const TOKEN::Expression *expression)
{
    for(const auto *ae : expression->seq)
    {
        if(!process(ae))
            return false;
    }

    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < expression->seq.size();
        i++)
    {
        if(!process(expression->seq[i]))
            return false;
        
        if(i + 1ull < expression->seq.size())
            mCurrentSTM->array()[STM::COMMA]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::AssignmentExpression *ae)
{
    using AE = TOKEN::AssignmentExpression;

    if(std::holds_alternative<AE::Sce>(ae->var))
    {
        const auto &s{std::get<AE::Sce>(ae->var)};
        if(!process(s.ce))
            return false;
    }
    else if(std::holds_alternative<AE::Sue_ao_ae>(ae->var))
    {
        const auto &s{std::get<AE::Sue_ao_ae>(ae->var)};
        if(!process(s.ue)
            || !process(s.ao)
            || !process(s.ae))
            return false;
    }
    else
        return invalidVariantError("AssignmentExpression");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::AssignmentOperator *ao)
{
    using namespace TOKEN;
    using AO = AssignmentOperator;

    using STM = StructureTokenMetrics<std::size_t>;

    switch(ao->tag)
    {
        case(AO::Tag::ASSIGNMENT):
            mCurrentSTM->array()[STM::ASSIGNMENT]++;
            break;
        case(AO::Tag::MULTIPLICATION):
            mCurrentSTM->array()[STM::ASTERISK_ASSIGNMENT]++;
            break;
        case(AO::Tag::DIVISION):
            mCurrentSTM->array()[STM::SLASH_ASSIGNMENT]++;
            break;
        case(AO::Tag::REMAINDER):
            mCurrentSTM->array()[STM::PERCENT_ASSIGNMENT]++;
            break;
        case(AO::Tag::ADDITION):
            mCurrentSTM->array()[STM::PLUS_ASSIGNMENT]++;
            break;
        case(AO::Tag::SUBTRACTION):
            mCurrentSTM->array()[STM::MINUS_ASSIGNMENT]++;
            break;
        case(AO::Tag::LEFT_SHIFT):
            mCurrentSTM->array()[STM::L_SHIFT_ASSIGNMENT]++;
            break;
        case(AO::Tag::RIGHT_SHIFT):
            mCurrentSTM->array()[STM::R_SHIFT_ASSIGNMENT]++;
            break;
        case(AO::Tag::AND):
            mCurrentSTM->array()[STM::AND_ASSIGNMENT]++;
            break;
        case(AO::Tag::XOR):
            mCurrentSTM->array()[STM::XOR_ASSIGNMENT]++;
            break;
        case(AO::Tag::OR):
            mCurrentSTM->array()[STM::BITOR_ASSIGNMENT]++;
            break;
        
        default:
            invalidVariantError("TOKEN::AssignmentOperator");
            break;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::ConditionalExpression *ce)
{
    using CE = TOKEN::ConditionalExpression;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<CE::Slore>(ce->var))
    {
        const auto &s{std::get<CE::Slore>(ce->var)};
        if(!process(s.lore))
            return false;
    }
    else if(std::holds_alternative<CE::Slore_e_ce>(ce->var))
    {
        const auto &s{std::get<CE::Slore_e_ce>(ce->var)};
        
        if(!process(s.lore))
            return false;
        
        mCurrentSTM->array()[STM::QUESTION]++;

        if(!process(s.e))
            return false;
        
        mCurrentSTM->array()[STM::COLON]++;

        if(!process(s.ce))
            return false;
    }
    else
        return invalidVariantError("ConditionalExpression");

    return true;
}

bool TokenMetricer::process(const TOKEN::LogicalORExpression *lore)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < lore->seq.size();
        i++)
    {
        if(!process(lore->seq[i]))
            return false;
        
        if(i + 1ull < lore->seq.size())
            mCurrentSTM->array()[STM::OR]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::LogicalANDExpression *lande)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < lande->seq.size();
        i++)
    {
        if(!process(lande->seq[i]))
            return false;
    
        if(i + 1ull < lande->seq.size())
            mCurrentSTM->array()[STM::AND]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::InclusiveORExpression *iore)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < iore->seq.size();
        i++)
    {
        if(!process(iore->seq[i]))
            return false;
        
        if(i + 1ull < iore->seq.size())
            mCurrentSTM->array()[STM::BITOR]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::ExclusiveORExpression *eore)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < eore->seq.size();
        i++)
    {
        if(!process(eore->seq[i]))
            return false;

        if(i + 1ull < eore->seq.size())
            mCurrentSTM->array()[STM::XOR]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::ANDExpression *ande)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < ande->seq.size();
        i++)
    {
        if(!process(ande->seq[i]))
            return false;
        
        if(i + 1ull < ande->seq.size())
            mCurrentSTM->array()[STM::BITAND]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::EqualityExpression *ee)
{
    using EE = TOKEN::EqualityExpression;

    using STM = StructureTokenMetrics<std::size_t>;

    for(const auto &v : ee->seq)
    {
        if(std::holds_alternative<EE::Sre>(v))
        {
            if(!process(std::get<EE::Sre>(v).re))
                return false;
        }
        else if(std::holds_alternative<EE::Se_re>(v))
        {
            mCurrentSTM->array()[STM::EQUAL]++;

            if(!process(std::get<EE::Se_re>(v).re))
                return false;
        }
        else if(std::holds_alternative<EE::Sne_re>(v))
        {
            mCurrentSTM->array()[STM::NOT_EQUAL]++;

            if(!process(std::get<EE::Sne_re>(v).re))
                return false;
        }
        else
            return invalidVariantError("EqualityExpression");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::RelationalExpression *re)
{
    using RE = TOKEN::RelationalExpression;

    using STM = StructureTokenMetrics<std::size_t>;

    for(const auto &v : re->seq)
    {
        if(std::holds_alternative<RE::Sse>(v))
        {
            if(!process(std::get<RE::Sse>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sl_se>(v))
        {
            mCurrentSTM->array()[STM::LESS]++;
        
            if(!process(std::get<RE::Sl_se>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sg_se>(v))
        {
            mCurrentSTM->array()[STM::GREATER]++;

            if(!process(std::get<RE::Sg_se>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sle_se>(v))
        {
            mCurrentSTM->array()[STM::LESS_EQUAL]++;

            if(!process(std::get<RE::Sle_se>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sge_se>(v))
        {
            mCurrentSTM->array()[STM::GREATER_EQUAL]++;

            if(!process(std::get<RE::Sge_se>(v).se))
                return false;
        }
        else
            return invalidVariantError("RelationalExpression");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::ShiftExpression *se)
{
    using SE = TOKEN::ShiftExpression;

    using STM = StructureTokenMetrics<std::size_t>;

    for(const auto &v : se->seq)
    {
        if(std::holds_alternative<SE::Sae>(v))
        {
            if(!process(std::get<SE::Sae>(v).ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sl_ae>(v))
        {
            mCurrentSTM->array()[STM::L_SHIFT]++;

            if(!process(std::get<SE::Sl_ae>(v).ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sr_ae>(v))
        {
            mCurrentSTM->array()[STM::R_SHIFT]++;

            if(!process(std::get<SE::Sr_ae>(v).ae))
                return false;
        }
        else
            return invalidVariantError("ShiftExpression");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::AdditiveExpression *ae)
{
    using AE = TOKEN::AdditiveExpression;

    using STM = StructureTokenMetrics<std::size_t>;

    for(const auto &v : ae->seq)
    {
        if(std::holds_alternative<AE::Sme>(v))
        {
            if(!process(std::get<AE::Sme>(v).me))
                return false;
        }
        else if(std::holds_alternative<AE::Sa_me>(v))
        {
            mCurrentSTM->array()[STM::PLUS]++;

            if(!process(std::get<AE::Sa_me>(v).me))
                return false;
        }
        else if(std::holds_alternative<AE::Ss_me>(v))
        {
            mCurrentSTM->array()[STM::MINUS]++;

            if(!process(std::get<AE::Ss_me>(v).me))
                return false;
        }
        else
            return invalidVariantError("AdditiveExpression");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::MultiplicativeExpression *me)
{
    using ME = TOKEN::MultiplicativeExpression;

    using STM = StructureTokenMetrics<std::size_t>;

    for(const auto &v : me->seq)
    {
        if(std::holds_alternative<ME::Sce>(v))
        {
            if(!process(std::get<ME::Sce>(v).ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sm_ce>(v))
        {
            mCurrentSTM->array()[STM::ASTERISK]++;

            if(!process(std::get<ME::Sm_ce>(v).ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sd_ce>(v))
        {
            mCurrentSTM->array()[STM::SLASH]++;

            if(!process(std::get<ME::Sd_ce>(v).ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sr_ce>(v))
        {
            mCurrentSTM->array()[STM::PERCENT]++;

            if(!process(std::get<ME::Sr_ce>(v).ce))
                return false;
        }
        else
            return invalidVariantError("MultiplicativeExpression");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::CastExpression *ce)
{
    using CE = TOKEN::CastExpression;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<CE::Sue>(ce->var))
    {
        if(!process(std::get<CE::Sue>(ce->var).ue))
                return false;
    }
    else if(std::holds_alternative<CE::Stn_ce>(ce->var))
    {
        const auto &s{std::get<CE::Stn_ce>(ce->var)};
        
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(s.tn))
            return false;
        
        mCurrentSTM->array()[STM::R_PARENTHESIS]++;

        if(!process(s.ce))
            return false;
    }
    else
        return invalidVariantError("CastExpression");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::UnaryExpression *ue)
{
    using UE = TOKEN::UnaryExpression;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<UE::Spe>(ue->var))
    {
        if(!process(std::get<UE::Spe>(ue->var).pe))
            return false;
    }
    else if(std::holds_alternative<UE::Si_ue>(ue->var))
    {
        mCurrentSTM->array()[STM::INCREMENT]++;

        if(!process(std::get<UE::Si_ue>(ue->var).ue))
            return false;
    }
    else if(std::holds_alternative<UE::Sd_ue>(ue->var))
    {
        mCurrentSTM->array()[STM::DECREMENT]++;

        if(!process(std::get<UE::Sd_ue>(ue->var).ue))
            return false;
    }
    else if(std::holds_alternative<UE::Suo_ce>(ue->var))
    {
        auto &&s{std::get<UE::Suo_ce>(ue->var)};
        if(!process(s.uo)
            || !process(s.ce))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_ue>(ue->var))
    {
        mCurrentSTM->array()[STM::SIZEOF]++;

        if(!process(std::get<UE::Ss_ue>(ue->var).ue))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_tn>(ue->var))
    {
        mCurrentSTM->array()[STM::SIZEOF]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(std::get<UE::Ss_tn>(ue->var).tn))
            return false;

        mCurrentSTM->array()[STM::R_PARENTHESIS]++;
    }
    else if(std::holds_alternative<UE::Sa_tn>(ue->var))
    {
        mCurrentSTM->array()[STM::ALIGNOF]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(std::get<UE::Sa_tn>(ue->var).tn))
            return false;

        mCurrentSTM->array()[STM::R_PARENTHESIS]++;
    }
    else
        return invalidVariantError("UnaryExpression");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::UnaryOperator *uo)
{
    using namespace TOKEN;
    using UO = UnaryOperator;

    using STM = StructureTokenMetrics<std::size_t>;

    switch(uo->tag)
    {
        case(UO::Tag::ADDRESS):
            mCurrentSTM->array()[STM::BITAND]++;
            break;
        case(UO::Tag::POINTER):
            mCurrentSTM->array()[STM::ASTERISK]++;
            break;
        case(UO::Tag::PLUS):
            mCurrentSTM->array()[STM::PLUS]++;
            break;
        case(UO::Tag::MINUS):
            mCurrentSTM->array()[STM::MINUS]++;
            break;
        case(UO::Tag::COMPLEMENT):
            mCurrentSTM->array()[STM::COMPL]++;
            break;
        case(UO::Tag::NOT):
            mCurrentSTM->array()[STM::NOT]++;
            break;
        default:
            return invalidVariantError("TOKEN::UnaryOperator");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::PostfixExpression *pe)
{
    using PE = TOKEN::PostfixExpression;

    using STM = StructureTokenMetrics<std::size_t>;

    for(const auto &v : pe->seq)
    {
        if(std::holds_alternative<PE::Spe>(v))
        {
            if(!process(std::get<PE::Spe>(v).pe))
                return false;
        }
        else if(std::holds_alternative<PE::Se>(v))
        {
            mCurrentSTM->array()[STM::L_SQUARE_BRACKET]++;

            if(!process(std::get<PE::Se>(v).e))
                return false;

            mCurrentSTM->array()[STM::R_SQUARE_BRACKET]++;
        }
        else if(std::holds_alternative<PE::Sael>(v))
        {
            const auto &s{std::get<PE::Sael>(v)};

            mCurrentSTM->array()[STM::L_PARENTHESIS]++;

            if(!(s.ael ? process(s.ael) : true))
                return false;

            mCurrentSTM->array()[STM::R_PARENTHESIS]++;
        }
        else if(std::holds_alternative<PE::Sp_i>(v))
        {
            mCurrentSTM->array()[STM::PERIOD]++;

            if(!process(std::get<PE::Sp_i>(v).i))
                return false;
        }
        else if(std::holds_alternative<PE::Sa_i>(v))
        {
            mCurrentSTM->array()[STM::ARROW]++;

            if(!process(std::get<PE::Sa_i>(v).i))
                return false;
        }
        else if(std::holds_alternative<PE::Si>(v))
            mCurrentSTM->array()[STM::INCREMENT]++;
        else if(std::holds_alternative<PE::Sd>(v))
            mCurrentSTM->array()[STM::DECREMENT]++;
        else if(std::holds_alternative<PE::Stn_il>(v))
        {
            const auto &s{std::get<PE::Stn_il>(v)};

            mCurrentSTM->array()[STM::L_PARENTHESIS]++;
            
            if(!process(s.tn))
                return false;
            
            mCurrentSTM->array()[STM::R_PARENTHESIS]++;
            mCurrentSTM->array()[STM::L_CURLY_BRACKET]++;

            if(!process(s.il))
                return false;
            
            mCurrentSTM->array()[STM::R_CURLY_BRACKET]++;
        }
        else
            return invalidVariantError("PostfixExpression");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::PrimaryExpression *pe)
{
    using namespace TOKEN;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<Identifier*>(pe->var))
    {
        if(!process(std::get<Identifier*>(pe->var)))
            return false;
    }
    else if(std::holds_alternative<Constant*>(pe->var))
    {
        if(!process(std::get<Constant*>(pe->var)))
            return false;
    }
    else if(std::holds_alternative<StringLiteral*>(pe->var))
        ;
    else if(std::holds_alternative<Expression*>(pe->var))
    {
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(std::get<Expression*>(pe->var)))
            return false;

        mCurrentSTM->array()[STM::R_PARENTHESIS]++;
    }
    else if(std::holds_alternative<GenericSelection*>(pe->var))
    {
        if(!process(std::get<GenericSelection*>(pe->var)))
            return false;
    }
    else
        return invalidVariantError("PrimaryExpression");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::Constant *constant)
{
    using namespace TOKEN;

    if(std::holds_alternative<IntegerConstant*>(constant->var)
        || std::holds_alternative<FloatingConstant*>(constant->var)
        || std::holds_alternative<CharacterConstant*>(constant->var))
        ;
    else if(std::holds_alternative<EnumerationConstant*>(constant->var))
    {
        if(!process(std::get<EnumerationConstant*>(constant->var)))
            return false;
    }
    else
        return invalidVariantError("Constant");

    return true;
}

bool TokenMetricer::process(const TOKEN::GenericSelection *gs)
{
    using STM = StructureTokenMetrics<std::size_t>;

    mCurrentSTM->array()[STM::GENERIC]++;
    mCurrentSTM->array()[STM::L_PARENTHESIS]++;

    if(!process(gs->ae))
        return false;

    mCurrentSTM->array()[STM::COMMA]++;

    if(!process(gs->gal))
        return false;

    mCurrentSTM->array()[STM::R_PARENTHESIS]++;
    
    return true;
}

bool TokenMetricer::process(const TOKEN::GenericAssocList *gal)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < gal->seq.size();
        i++)
    {
        if(!process(gal->seq[i]))
            return false;
        
        if(i + 1ull < gal->seq.size())
            mCurrentSTM->array()[STM::COMMA]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::GenericAssociation *ga)
{
    using GA = TOKEN::GenericAssociation;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<GA::Stn_ae>(ga->var))
    {
        const auto &s{std::get<GA::Stn_ae>(ga->var)};
        
        if(!process(s.tn))
            return false;
        
        mCurrentSTM->array()[STM::COLON]++;

        if(!process(s.ae))
            return false;
    }
    else if(std::holds_alternative<GA::Sae>(ga->var))
    {
        const auto &s{std::get<GA::Sae>(ga->var)};
        
        mCurrentSTM->array()[STM::DEFAULT]++;
        mCurrentSTM->array()[STM::COLON]++;

        if(!process(s.ae))
            return false;
    }
    else
        return invalidVariantError("TOKEN::GenericAssociation");

    return true;
}

bool TokenMetricer::process(const TOKEN::EnumerationConstant *ec)
{
    if(!process(ec->i))
        return false;
    
    return true;
}

bool TokenMetricer::process(const TOKEN::ConstantExpression *ce)
{
    if(!process(ce->ce))
        return false;
    
    return true;
}

bool TokenMetricer::process(const TOKEN::StaticAssertDeclaration *sad)
{
    using STM = StructureTokenMetrics<std::size_t>;

    mCurrentSTM->array()[STM::STATIC_ASSERT]++;
    mCurrentSTM->array()[STM::L_PARENTHESIS]++;

    if(!process(sad->ce))
        return false;

    mCurrentSTM->array()[STM::COMMA]++;
    mCurrentSTM->array()[STM::R_PARENTHESIS]++;
    mCurrentSTM->array()[STM::SEMICOLON]++;
    
    return true;
}

bool TokenMetricer::process(const TOKEN::DeclarationList *dl)
{
    for(const auto &d : dl->seq)
    {
        if(!process(d))
            return false;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::ArgumentExpressionList *ael)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < ael->seq.size();
        i++)
    {
        if(!process(ael->seq[i]))
            return false;
        
        if(i + 1ull < ael->seq.size())
            mCurrentSTM->array()[STM::COMMA]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::InitializerList *il)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < il->seq.size();
        i++)
    {
        auto &&s{il->seq[i]};

        if(!(s.d ? process(s.d) : true))
            return false;
        
        if(!process(s.i))
            return false;

        if(i + 1ull < il->seq.size())
            mCurrentSTM->array()[STM::COMMA]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::Designation *designation)
{
    using STM = StructureTokenMetrics<std::size_t>;

    if(!process(designation->dl))
        return false;

    mCurrentSTM->array()[STM::ASSIGNMENT]++;

    return true;
}

bool TokenMetricer::process(const TOKEN::DesignatorList *dl)
{
    for(const auto *d : dl->seq)
    {
        if(!process(d))
            return false;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::Designator *designator)
{
    using namespace TOKEN;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<ConstantExpression*>(designator->var))
    {
        mCurrentSTM->array()[STM::L_SQUARE_BRACKET]++;

        if(!process(std::get<ConstantExpression*>(designator->var)))
            return false;

        mCurrentSTM->array()[STM::R_SQUARE_BRACKET]++;
    }
    else if(std::holds_alternative<Identifier*>(designator->var))
    {
        mCurrentSTM->array()[STM::PERIOD]++;

        if(!process(std::get<Identifier*>(designator->var)))
            return false;
    }
    else
        return invalidVariantError("Designator");

    return true;
}

bool TokenMetricer::process(const TOKEN::Initializer *initializer)
{
    using namespace TOKEN;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<AssignmentExpression*>(initializer->var))
    {
        if(!process(std::get<AssignmentExpression*>(initializer->var)))
            return false;
    }
    else if(std::holds_alternative<InitializerList*>(initializer->var))
    {
        mCurrentSTM->array()[STM::L_SQUARE_BRACKET]++;

        if(!process(std::get<InitializerList*>(initializer->var)))
            return false;

        mCurrentSTM->array()[STM::R_SQUARE_BRACKET]++;
    }
    else
        return invalidVariantError("TOKEN::Initializer");

    return true;
}

bool TokenMetricer::process(const TOKEN::TypeName *tn)
{
    if(!process(tn->sql)
        || !(tn->ad ? process(tn->ad) : true))
        return false;
    
    return true;
}

bool TokenMetricer::process(const TOKEN::SpecifierQualifierList *sql)
{
    using namespace TOKEN;

    for(const auto &v : sql->seq)
    {
        if(std::holds_alternative<TypeSpecifier*>(v))
        {
            if(!process(std::get<TypeSpecifier*>(v)))
                return false;
        }
        else if(std::holds_alternative<TypeQualifier*>(v))
        {
            if(!process(std::get<TypeQualifier*>(v)))
                return false;
        }
        else
            return invalidVariantError("SpecifierQualifierList");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::TypeSpecifier *ts)
{
    using namespace TOKEN;
    using TS = TypeSpecifier;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<TS::Tag>(ts->var))
    {
        switch(std::get<TS::Tag>(ts->var))
        {
            case(TS::Tag::VOID):
                mCurrentSTM->array()[STM::VOID]++;
                break;
            case(TS::Tag::CHAR):
                mCurrentSTM->array()[STM::CHAR]++;
                break;
            case(TS::Tag::SHORT):
                mCurrentSTM->array()[STM::SHORT]++;
                break;
            case(TS::Tag::INT):
                mCurrentSTM->array()[STM::INT]++;
                break;
            case(TS::Tag::LONG):
                mCurrentSTM->array()[STM::LONG]++;
                break;
            case(TS::Tag::FLOAT):
                mCurrentSTM->array()[STM::FLOAT]++;
                break;
            case(TS::Tag::DOUBLE):
                mCurrentSTM->array()[STM::DOUBLE]++;
                break;
            case(TS::Tag::SIGNED):
                mCurrentSTM->array()[STM::SIGNED]++;
                break;
            case(TS::Tag::UNSIGNED):
                mCurrentSTM->array()[STM::UNSIGNED]++;
                break;
            case(TS::Tag::BOOL):
                mCurrentSTM->array()[STM::BOOL]++;
                break;
            case(TS::Tag::COMPLEX):
                mCurrentSTM->array()[STM::COMPLEX]++;
                break;
            default:
                invalidVariantError("TOKEN::TypeSpecifier::Tag");
                break;
        }
    }
    else if(std::holds_alternative<AtomicTypeSpecifier*>(ts->var))
    {
        if(!process(std::get<AtomicTypeSpecifier*>(ts->var)))
            return false;
    }
    else if(std::holds_alternative<StructOrUnionSpecifier*>(ts->var))
    {
        if(!process(std::get<StructOrUnionSpecifier*>(ts->var)))
            return false;
    }
    else if(std::holds_alternative<EnumSpecifier*>(ts->var))
    {
        if(!process(std::get<EnumSpecifier*>(ts->var)))
            return false;
    }
    else if(std::holds_alternative<TypedefName*>(ts->var))
    {
        if(!process(std::get<TypedefName*>(ts->var)))
            return false;
    }
    else
        return invalidVariantError("TypeSpecifier");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::TypeQualifier *tq)
{
    using namespace TOKEN;
    using TQ = TypeQualifier;

    using STM = StructureTokenMetrics<std::size_t>;

    switch(tq->tag)
    {
        case(TQ::Tag::CONST):
            mCurrentSTM->array()[STM::CONST]++;
            break;
        case(TQ::Tag::RESTRICT):
            mCurrentSTM->array()[STM::RESTRICT]++;
            break;
        case(TQ::Tag::VOLATILE):
            mCurrentSTM->array()[STM::VOLATILE]++;
            break;
        case(TQ::Tag::ATOMIC):
            mCurrentSTM->array()[STM::ATOMIC]++;
            break;
        default:
            return invalidVariantError("TOKEN::TypeQualifier");
            break;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::AtomicTypeSpecifier *ats)
{
    using STM = StructureTokenMetrics<std::size_t>;

    mCurrentSTM->array()[STM::ATOMIC]++;
    mCurrentSTM->array()[STM::L_PARENTHESIS]++;

    if(!process(ats->tn))
        return false;

    mCurrentSTM->array()[STM::R_PARENTHESIS]++;
    
    return true;
}

bool TokenMetricer::process(const TOKEN::StructOrUnionSpecifier *sous)
{
    using SOUS = TOKEN::StructOrUnionSpecifier;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<SOUS::Ssou_i_sdl>(sous->var))
    {
        const auto &s{std::get<SOUS::Ssou_i_sdl>(sous->var)};
        
        if(!process(s.sou)
            || !(s.i ? process(s.i) : true))
            return false;
        
        mCurrentSTM->array()[STM::L_CURLY_BRACKET]++;

        if(!process(s.sdl))
            return false;

        mCurrentSTM->array()[STM::R_CURLY_BRACKET]++;
    }
    else if(std::holds_alternative<SOUS::Ssou_i>(sous->var))
    {
        const auto &s{std::get<SOUS::Ssou_i>(sous->var)};
        if(!process(s.sou)
            || !process(s.i))
            return false;
    }
    else
        return invalidVariantError("StructOrUnionSpecifier");

    return true;
}

bool TokenMetricer::process(const TOKEN::StructOrUnion *sou)
{
    using namespace TOKEN;
    using SOU = StructOrUnion;

    using STM = StructureTokenMetrics<std::size_t>;

    switch(sou->tag)
    {
        case(SOU::Tag::STRUCT):
            mCurrentSTM->array()[STM::STRUCT]++;
            break;
        case(SOU::Tag::UNION):
            mCurrentSTM->array()[STM::UNION]++;
            break;
        
        default:
            return invalidVariantError("TOKEN::StructOrUnion");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::StructDeclarationList *sdl)
{
    for(const auto *sd : sdl->seq)
    {
        if(!process(sd))
            return false;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::StructDeclaration *sd)
{
    using SD = TOKEN::StructDeclaration;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<SD::Ssql_sdl>(sd->var))
    {
        const auto &s{std::get<SD::Ssql_sdl>(sd->var)};
        if(!process(s.sql)
            || !(s.sdl ? process(s.sdl) : true))
            return false;

        mCurrentSTM->array()[STM::SEMICOLON]++;
    }
    else if(std::holds_alternative<SD::Ssad>(sd->var))
    {
        const auto &s{std::get<SD::Ssad>(sd->var)};
        if(!process(s.sad))
            return false;
    }
    else
        return invalidVariantError("StructDeclaration");

    return true;
}

bool TokenMetricer::process(const TOKEN::StructDeclaratorList *sdl)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < sdl->seq.size();
        i++)
    {
        if(!process(sdl->seq[i]))
            return false;
        
        if(i + 1ull < sdl->seq.size())
            mCurrentSTM->array()[STM::COMMA]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::StructDeclarator *sd)
{
    using SD = TOKEN::StructDeclarator;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<SD::Sd>(sd->var))
    {
        const auto &s{std::get<SD::Sd>(sd->var)};
        if(!process(s.d))
            return false;
    }
    else if(std::holds_alternative<SD::Sd_ce>(sd->var))
    {
        const auto &s{std::get<SD::Sd_ce>(sd->var)};
        
        if(!(s.d ? process(s.d) : true))
            return false;

        mCurrentSTM->array()[STM::COLON]++;

        if(!process(s.ce))
            return false;
    }
    else
        return invalidVariantError("StructDeclarator");

    return true;
}

bool TokenMetricer::process(const TOKEN::Declarator *declarator)
{
    if(!(declarator->p ? process(declarator->p) : true)
        || !process(declarator->dd))
        return false;
    
    return true;
}

bool TokenMetricer::process(const TOKEN::DirectDeclarator *dd)
{
    using DD = TOKEN::DirectDeclarator;

    using STM = StructureTokenMetrics<std::size_t>;

    for(const auto &v : dd->seq)
    {
        if(std::holds_alternative<DD::Si>(v))
        {
            const auto &s{std::get<DD::Si>(v)};
            if(!process(s.i))
                return false;
        }
        else if(std::holds_alternative<DD::Sd>(v))
        {
            const auto &s{std::get<DD::Sd>(v)};
            
            mCurrentSTM->array()[STM::L_PARENTHESIS]++;

            if(!process(s.d))
                return false;

            mCurrentSTM->array()[STM::R_PARENTHESIS]++;
        }
        else if(std::holds_alternative<DD::Stql_ae>(v))
        {
            const auto &s{std::get<DD::Stql_ae>(v)};
            
            mCurrentSTM->array()[STM::L_SQUARE_BRACKET]++;
            if(s.hasStatic)
                mCurrentSTM->array()[STM::STATIC]++;
            
            if(!(s.tql ? process(s.tql) : true)
                || !(s.ae ? process(s.ae) : true))
                return false;
            
            mCurrentSTM->array()[STM::R_SQUARE_BRACKET]++;
        }
        else if(std::holds_alternative<DD::Stql>(v))
        {
            auto &&s{std::get<DD::Stql>(v)};
            
            mCurrentSTM->array()[STM::L_SQUARE_BRACKET]++;

            if(!(s.tql ? process(s.tql) : true))
                return false;
            
            mCurrentSTM->array()[STM::ASTERISK]++;
            mCurrentSTM->array()[STM::R_SQUARE_BRACKET]++;
        }
        else if(std::holds_alternative<DD::Sptl>(v))
        {
            const auto &s{std::get<DD::Sptl>(v)};

            mCurrentSTM->array()[STM::L_PARENTHESIS]++;

            if(!process(s.ptl))
                return false;

            mCurrentSTM->array()[STM::R_PARENTHESIS]++;
        }
        else if(std::holds_alternative<DD::Sil>(v))
        {
            const auto &s{std::get<DD::Sil>(v)};

            mCurrentSTM->array()[STM::L_PARENTHESIS]++;

            if(!(s.il ? process(s.il) : true))
                return false;

            mCurrentSTM->array()[STM::R_PARENTHESIS]++;
        }
        else
            return invalidVariantError("DirectDeclarator");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::IdentifierList *il)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < il->seq.size();
        i++)
    {
        if(!process(il->seq[i]))
            return false;
        
        if(i + 1ull < il->seq.size())
            mCurrentSTM->array()[STM::COMMA]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::TypeQualifierList *tql)
{
    for(const auto &tq : tql->seq)
    {
        if(!process(tq))
            return false;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::ParameterTypeList *ptl)
{
    using STM = StructureTokenMetrics<std::size_t>;

    if(!process(ptl->pl))
        return false;

    if(ptl->isValiable)
    {
        mCurrentSTM->array()[STM::COMMA]++;
        mCurrentSTM->array()[STM::TRIPLE_PERIOD]++;
    }
    
    return true;
}

bool TokenMetricer::process(const TOKEN::ParameterList *pl)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < pl->seq.size();
        i++)
    {
        if(!process(pl->seq[i]))
            return false;
        
        if(i + 1ull < pl->seq.size())
            mCurrentSTM->array()[STM::COMMA]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::ParameterDeclaration *pd)
{
    using PD = TOKEN::ParameterDeclaration;

    if(std::holds_alternative<PD::Sds_d>(pd->var))
    {
        const auto &s{std::get<PD::Sds_d>(pd->var)};
        if(!process(s.ds)
            || !process(s.d))
            return false;
    }
    else if(std::holds_alternative<PD::Sds_ad>(pd->var))
    {
        const auto &s{std::get<PD::Sds_ad>(pd->var)};
        if(!process(s.ds)
            || !(s.ad ? process(s.ad) : true))
            return false;
    }
    else
        return invalidVariantError("ParameterDeclaration");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::DeclarationSpecifiers *ds)
{
    using namespace TOKEN;

    for(const auto &v : ds->seq)
    {
        if(std::holds_alternative<StorageClassSpecifier*>(v))
        {
            if(!process(std::get<StorageClassSpecifier*>(v)))
                return false;
        }
        else if(std::holds_alternative<TypeSpecifier*>(v))
        {
            if(!process(std::get<TypeSpecifier*>(v)))
                return false;
        }
        else if(std::holds_alternative<TypeQualifier*>(v))
        {
            if(!process(std::get<TypeQualifier*>(v)))
                return false;
        }
        else if(std::holds_alternative<FunctionSpecifier*>(v))
        {
            if(!process(std::get<FunctionSpecifier*>(v)))
                return false;
        }
        else if(std::holds_alternative<AlignmentSpecifier*>(v))
        {
            if(!process(std::get<AlignmentSpecifier*>(v)))
                return false;
        }
        else
            return invalidVariantError("DeclarationSpecifiers");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::StorageClassSpecifier *scs)
{
    using namespace TOKEN;
    using SCS = StorageClassSpecifier;

    using STM = StructureTokenMetrics<std::size_t>;

    switch(scs->tag)
    {
        case(SCS::Tag::TYPEDEF):
            mCurrentSTM->array()[STM::TYPEDEF]++;
            break;
        case(SCS::Tag::EXTERN):
            mCurrentSTM->array()[STM::EXTERN]++;
            break;
        case(SCS::Tag::STATIC):
            mCurrentSTM->array()[STM::STATIC]++;
            break;
        case(SCS::Tag::THREAD_LOCAL):
            mCurrentSTM->array()[STM::THREAD_LOCAL]++;
            break;
        case(SCS::Tag::AUTO):
            mCurrentSTM->array()[STM::AUTO]++;
            break;
        case(SCS::Tag::REGISTER):
            mCurrentSTM->array()[STM::REGISTER]++;
            break;
        default:
            return invalidVariantError("TOKEN::StorageClassSpecifier");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::FunctionSpecifier *fs)
{
    using namespace TOKEN;
    using FS = FunctionSpecifier;

    using STM = StructureTokenMetrics<std::size_t>;

    switch(fs->tag)
    {
        case(FS::Tag::INLINE):
            mCurrentSTM->array()[STM::INLINE]++;
            break;
        case(FS::Tag::NORETURN):
            mCurrentSTM->array()[STM::NORETURN]++;
            break;

        default:
            return invalidVariantError("TOKEN::FunctionSpecifier");
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::AlignmentSpecifier *as)
{
    using namespace TOKEN;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<TypeName*>(as->var))
    {
        mCurrentSTM->array()[STM::ALIGNAS]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(std::get<TypeName*>(as->var)))
            return false;

        mCurrentSTM->array()[STM::R_PARENTHESIS]++;
    }
    else if(std::holds_alternative<ConstantExpression*>(as->var))
    {
        mCurrentSTM->array()[STM::ALIGNAS]++;
        mCurrentSTM->array()[STM::L_PARENTHESIS]++;

        if(!process(std::get<ConstantExpression*>(as->var)))
            return false;

        mCurrentSTM->array()[STM::R_PARENTHESIS]++;
    }
    else
        return invalidVariantError("AlignmentSpecifier");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::EnumSpecifier *es)
{
    using ES = TOKEN::EnumSpecifier;
    
    using STM = StructureTokenMetrics<std::size_t>;

    mCurrentSTM->array()[STM::ENUM]++;

    if(std::holds_alternative<ES::Si_el>(es->var))
    {
        const auto &s{std::get<ES::Si_el>(es->var)};
        
        if(!(s.i ? process(s.i) : true))
            return false;
        
        mCurrentSTM->array()[STM::L_CURLY_BRACKET]++;

        if(!process(s.el))
            return false;

        mCurrentSTM->array()[STM::R_CURLY_BRACKET]++;
    }
    else if(std::holds_alternative<ES::Si>(es->var))
    {
        const auto &s{std::get<ES::Si>(es->var)};
        if(!process(s.i))
            return false;
    }
    else
        return invalidVariantError("EnumSpecifier");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::EnumeratorList *el)
{
    using STM = StructureTokenMetrics<std::size_t>;

    for(std::size_t i{0ull};
        i < el->seq.size();
        i++)
    {
        if(!process(el->seq[i]))
            return false;
        
        if(i + 1ull < el->seq.size())
            mCurrentSTM->array()[STM::COMMA]++;
    }

    return true;
}

bool TokenMetricer::process(const TOKEN::Enumerator *enumerator)
{
    using E = TOKEN::Enumerator;

    using STM = StructureTokenMetrics<std::size_t>;

    if(std::holds_alternative<E::Sec>(enumerator->var))
    {
        const auto &s{std::get<E::Sec>(enumerator->var)};
        if(!process(s.ec))
            return false;
    }
    else if(std::holds_alternative<E::Sec_ce>(enumerator->var))
    {
        const auto &s{std::get<E::Sec_ce>(enumerator->var)};
        if(!process(s.ec))
            return false;
        
        mCurrentSTM->array()[STM::ASSIGNMENT]++;

        if(!process(s.ce))
            return false;
    }
    else
        return invalidVariantError("TOKEN::Enumerator");

    return true;
}

bool TokenMetricer::process(const TOKEN::TypedefName *tn)
{
    if(!process(tn->i))
        return false;

    return true;
}

bool TokenMetricer::process(const TOKEN::AbstractDeclarator *ad)
{
    using AD = TOKEN::AbstractDeclarator;

    if(std::holds_alternative<AD::Sp>(ad->var))
    {
        const auto &s{std::get<AD::Sp>(ad->var)};
        if(!process(s.p))
            return false;
    }
    else if(std::holds_alternative<AD::Sp_dad>(ad->var))
    {
        const auto &s{std::get<AD::Sp_dad>(ad->var)};
        if(!(s.p ? process(s.p) : true)
            || !process(s.dad))
            return false;
    }
    else
        return invalidVariantError("AbstractDeclarator");
    
    return true;
}

bool TokenMetricer::process(const TOKEN::Pointer *pointer)
{
    using namespace TOKEN;
    
    using STM = StructureTokenMetrics<std::size_t>;

    mCurrentSTM->array()[STM::ASTERISK]++;

    if(std::holds_alternative<Pointer::Stql>(pointer->var))
    {
        auto &&s{std::get<Pointer::Stql>(pointer->var)};
        if(!(s.tql ? process(s.tql) : true))
            return false;
    }
    else if(std::holds_alternative<Pointer::Stql_p>(pointer->var))
    {
        auto &&s{std::get<Pointer::Stql_p>(pointer->var)};
        if(!(s.tql ? process(s.tql) : true)
            || !process(s.p))
            return false;
    }
    else
        return invalidVariantError("TOKEN::Pointer");

    return true;
}

bool TokenMetricer::process(const TOKEN::DirectAbstractDeclarator *dad)
{
    using DAD = TOKEN::DirectAbstractDeclarator;

    using STM = StructureTokenMetrics<std::size_t>;

    for(const auto &v : dad->seq)
    {
        if(std::holds_alternative<DAD::Sad>(v))
        {
            const auto &s{std::get<DAD::Sad>(v)};
            
            mCurrentSTM->array()[STM::L_PARENTHESIS]++;

            if(!process(s.ad))
                return false;

            mCurrentSTM->array()[STM::R_PARENTHESIS]++;
        }
        else if(std::holds_alternative<DAD::Stql_ae>(v))
        {
            const auto &s{std::get<DAD::Stql_ae>(v)};

            mCurrentSTM->array()[STM::L_SQUARE_BRACKET]++;
            if(s.hasStatic)
                mCurrentSTM->array()[STM::STATIC]++;
            
            if(!(s.tql ? process(s.tql) : true)
                || !(s.ae ? process(s.ae) : true))
                return false;

            mCurrentSTM->array()[STM::R_SQUARE_BRACKET]++;
        }
        else if(std::holds_alternative<DAD::Sp>(v))
        {
            mCurrentSTM->array()[STM::L_SQUARE_BRACKET]++;
            mCurrentSTM->array()[STM::ASTERISK]++;
            mCurrentSTM->array()[STM::R_SQUARE_BRACKET]++;
        }
        else if(std::holds_alternative<DAD::Sptl>(v))
        {
            const auto &s{std::get<DAD::Sptl>(v)};

            mCurrentSTM->array()[STM::L_PARENTHESIS]++;

            if(!(s.ptl ? process(s.ptl) : true))
                return false;

            mCurrentSTM->array()[STM::R_PARENTHESIS]++;
        }
        else
            return invalidVariantError("DirectAbstractDeclarator");
    }

    return true;
}

std::string TokenMetricer::getIdentifier(const TOKEN::Declarator *declarator) const
{
    using namespace TOKEN;
    using DD = DirectDeclarator;

    std::string identifier;

    for(;;)
    {
        if(std::holds_alternative<DD::Si>(declarator->dd->seq.front()))
        {
            identifier = TOKEN::str(std::get<DD::Si>(declarator->dd->seq.front()).i);
            break;
        }
        else if(std::holds_alternative<DD::Sd>(declarator->dd->seq.front()))
            declarator = std::get<DD::Sd>(declarator->dd->seq.front()).d;
        else
        {
            invalidVariantError("TOKEN::DirectDeclarator");
            break;
        }
    }

    return identifier;
}

bool TokenMetricer::invalidStatementError() const
{
    std::cerr << "SIM::TokenMetricer error:\n"
        "    what: invalid statement.\n"
        << std::flush;
    return false;
}

bool TokenMetricer::noSupportError(const std::string &name) const
{
    std::cerr << "SIM::TokenMetricer error:\n"
        "    what: no support.\n"
        "    ---: " << name
        << std::endl;
    return false;
}

bool TokenMetricer::invalidVariantError(const std::string &className) const
{
    std::cerr << "SIM::invalidVariant error:\n"
        "    what: variant has invalid entity.\n"
        "    class: " << className
        << std::endl;
    return false;
}

}