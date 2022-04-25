#include <unordered_set>
#include <iostream>
#include <limits>
#include <algorithm>

#include "../utility/random.hpp"
#include "../scope.hpp"
#include "../identifier.hpp"
#include "../token.hpp"
#include "selector.hpp"

namespace GA
{

Selector::Selector()
    : mIsSelection{false}
    , mIsFittable{false}
    , mScopeId{std::numeric_limits<decltype(mScopeId)>::max()}
    , mIds{std::ref(INIT_VALUE)}
    , mIdx{0ull}
    , mCIds{std::cref(INIT_VALUE)}
    , mIsFittables{}
{
}

Selector::~Selector()
{
}

bool Selector::execute(std::size_t scopeId
    , const TOKEN::Statement *statement
    , std::vector<std::size_t> &ids)
{
    mIsSelection = true;
    mIsFittable = false;

    if(!clear())
        return clearError();

    mScopeId = scopeId;
    mIds = std::ref(ids);

    if(!select(statement))
        return false;

    return true;
}

bool Selector::execute(const std::vector<std::size_t> &ids
    , const TOKEN::Statement *statement)
{
    mIsSelection = false;
    mIsFittable = false;
    
    if(!clear())
        return clearError();
    
    mIdx = 0ull;
    mCIds = std::cref(ids);

    if(!select(statement))
        return false;

    if(mIdx != ids.size())
        return unusedIdError();
    
    return true;
}

bool Selector::isFittable(std::size_t scopeId
    , const TOKEN::Statement *statement)
{
    mIsSelection = false;
    mIsFittable = true;

    if(!clear())
        return clearError();

    mScopeId = scopeId;

    if(!select(statement))
        return false;
    
    return std::all_of(mIsFittables.cbegin()
        , mIsFittables.cend()
        , [](auto &&b){return b;});
}

bool Selector::clear()
{
    mScopeId = std::numeric_limits<decltype(mScopeId)>::max();
    mIds = std::ref(INIT_VALUE);

    mIdx = 0ull;
    mCIds = std::cref(INIT_VALUE);

    mIsFittables.clear();

    return true;
}

bool Selector::getVisibleIdentifierList(const std::shared_ptr<IDENTIFIER::Identifier> &id
    , std::vector<std::size_t> &idList)
{
    using namespace SCOPE;
    using namespace IDENTIFIER;
    
    Scope::NamespaceTag nTag{Scope::NamespaceTag::OTHER};
    switch(id->derivedTag())
    {
        case(Identifier::DerivedTag::OBJECT):
        case(Identifier::DerivedTag::FUNCTION):
        case(Identifier::DerivedTag::ENUM):
        case(Identifier::DerivedTag::TYPEDEF):
            nTag = Scope::NamespaceTag::OTHER;
            break;
        case(Identifier::DerivedTag::TAG):
            nTag = Scope::NamespaceTag::TAG;
            break;
        case(Identifier::DerivedTag::MEMBER):
            nTag = Scope::NamespaceTag::MEMBER;
            break;
        case(Identifier::DerivedTag::LABEL):
            nTag = Scope::NamespaceTag::LABEL;
        break;
    }

    std::unordered_set<std::string> idSet;

    for(auto *scope{Scope::scopeMap().at(mScopeId)};
        scope;
        scope = scope->getParent())
    {
        for(const auto &pair : scope->map(nTag))
        {
            auto &&[iter, isAdded]{idSet.insert(pair.first)};
            if(isAdded)
                idList.push_back(pair.second->id());
        }
    }

    return true;
}

bool Selector::getSameTypeIdentifier(const std::shared_ptr<IDENTIFIER::Identifier> &id
    , std::vector<std::size_t> &idList)
{
    using namespace IDENTIFIER;
    using namespace SCOPE;

    for(std::size_t i{0ull};
        i < idList.size();
        i++)
    {
        if(!isSameType(id
            , Scope::identifierMap().at(idList[i])))
        {
            idList.erase(idList.begin() + i);
            i--;
        }
    }

    return true;
}

bool Selector::selectOne(const std::vector<std::size_t> &idList
    , std::size_t &result)
{
    if(idList.empty())
        return isNotFoundIdentifier();
    
    result = idList[RANDOM::RAND(idList.size())];

    return true;
}

bool Selector::convert(TOKEN::Identifier *identifier)
{
    using namespace TOKEN;

    if(mIdx >= mCIds.get().size())
        return lackIdError();
    
    if(!std::holds_alternative<Identifier::Id>(identifier->var))
        return invalidVariantError("TOKEN::Identifier");

    auto &&idPair{std::get<Identifier::Id>(identifier->var)};
    idPair.first = mCIds.get()[mIdx++];

    return true;
}

bool Selector::select(TOKEN::Identifier *identifier)
{
    using TI = TOKEN::Identifier;

    if(mIsSelection)
    {
        if(!std::holds_alternative<TI::Id>(identifier->var))
            return invalidVariantError("TOKEN::Identifier");

        const auto &idPair{std::get<TI::Id>(identifier->var)};
        const auto &idPtr{SCOPE::Scope::identifierMap().at(idPair.first)};

        std::vector<std::size_t> idList;
        if(!getVisibleIdentifierList(idPtr
            , idList))
            return false;
        
        if(!getSameTypeIdentifier(idPtr
            , idList))
            return false;
        
        std::size_t result{0ull};
        if(!selectOne(idList
            , result))
            return false;
        
        mIds.get().push_back(result);
    }
    else if(mIsFittable)
    {
        if(!std::holds_alternative<TI::Id>(identifier->var))
            return invalidVariantError("TOKEN::Identifier");
        
        const auto &idPair{std::get<TI::Id>(identifier->var)};
        const auto &idPtr{SCOPE::Scope::identifierMap().at(idPair.first)};

        std::vector<std::size_t> idList;
        if(!getVisibleIdentifierList(idPtr
            , idList))
            return false;
        
        if(!getSameTypeIdentifier(idPtr
            , idList))
            return false;
        
        mIsFittables.push_back(!idList.empty());
    }
    else
    {
        if(!convert(identifier))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::Statement *statement)
{
    if(std::holds_alternative<TOKEN::ExpressionStatement*>(statement->var))
        return select(std::get<TOKEN::ExpressionStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::JumpStatement*>(statement->var))
        return select(std::get<TOKEN::JumpStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::LabeledStatement*>(statement->var))
        return select(std::get<TOKEN::LabeledStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::CompoundStatement*>(statement->var))
        return select(std::get<TOKEN::CompoundStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::SelectionStatement*>(statement->var))
        return select(std::get<TOKEN::SelectionStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::IterationStatement*>(statement->var))
        return select(std::get<TOKEN::IterationStatement*>(statement->var));
    else if(std::holds_alternative<TOKEN::AttributeStatement*>(statement->var))
        return select(std::get<TOKEN::AttributeStatement*>(statement->var));
    else
        return invalidStatementError();

    return true;
}

bool Selector::select(const TOKEN::JumpStatement *js)
{
    using JS = TOKEN::JumpStatement;

    if(std::holds_alternative<JS::Sg_i>(js->var))
    {
        const auto &s{std::get<JS::Sg_i>(js->var)};
        if(!select(s.i))
            return false;
    }
    else if(std::holds_alternative<JS::Sr_e>(js->var))
    {
        const auto &s{std::get<JS::Sr_e>(js->var)};
        if(bool(s.e))
            if(!select(s.e))
                return false;
    }
        
    return true;
}

bool Selector::select(const TOKEN::ExpressionStatement *es)
{
    if(bool(es->e))
        if(!select(es->e))
            return false;

    return true;
}

bool Selector::select(const TOKEN::LabeledStatement *ls)
{
    using LS = TOKEN::LabeledStatement;

    if(std::holds_alternative<LS::Si_s>(ls->var))
    {
        auto &&s{std::get<LS::Si_s>(ls->var)};
        if(!select(s.i))
            return false;
        if(s.asl != nullptr
            && select(s.asl))
            return false;
        
        if(!select(s.s))
            return false;
    }
    else if(std::holds_alternative<LS::Sce_s>(ls->var))
    {
        auto &&s{std::get<LS::Sce_s>(ls->var)};
        if(!select(s.ce))
            return false;
        
        if(!select(s.s))
            return false;
    }
    else if(std::holds_alternative<LS::Ss>(ls->var))
    {
        auto &&s{std::get<LS::Ss>(ls->var)};
        if(!select(s.s))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::CompoundStatement *cs)
{
    using namespace TOKEN;

    if(!cs->bil)
        return true;
    
    for(const auto *bi : cs->bil->seq)
    {
        if(std::holds_alternative<Declaration*>(bi->var))
            return notSupportError("declaration is not supported.");
        
        if(std::holds_alternative<Statement*>(bi->var))
        {
            if(!select(std::get<Statement*>(bi->var)))
                return false;
        }
    }

    return true;
}

bool Selector::select(const TOKEN::SelectionStatement *ss)
{
    using SS = TOKEN::SelectionStatement;

    if(std::holds_alternative<SS::Si_e_s>(ss->var))
    {
        auto &&s{std::get<SS::Si_e_s>(ss->var)};
        if(!select(s.e))
            return false;
        
        if(!select(s.s))
            return false;
    }
    else if(std::holds_alternative<SS::Si_e_s_s>(ss->var))
    {
        auto &&s{std::get<SS::Si_e_s_s>(ss->var)};
        if(!select(s.e))
            return false;
        
        if(!select(s.s0))
            return false;

        if(!select(s.s1))
            return false;
    }
    else if(std::holds_alternative<SS::Ss_e_s>(ss->var))
    {
        auto &&s{std::get<SS::Ss_e_s>(ss->var)};
        if(!select(s.e))
            return false;
        
        if(!select(s.s))
            return false;
    }
    else
        return invalidVariantError("SelectionStatement");
    
    return true;
}

bool Selector::select(const TOKEN::IterationStatement *is)
{
    using IS = TOKEN::IterationStatement;

    if(std::holds_alternative<IS::Sw_e_s>(is->var))
    {
        auto &&s{std::get<IS::Sw_e_s>(is->var)};
        if(!select(s.e))
            return false;
        
        if(!select(s.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sd_s_e>(is->var))
    {
        auto &&s{std::get<IS::Sd_s_e>(is->var)};
        if(!select(s.s))
            return false;
        
        if(!select(s.e))
            return false;
    }
    else if(std::holds_alternative<IS::Sf_e_e_e_s>(is->var))
    {
        auto &&s{std::get<IS::Sf_e_e_e_s>(is->var)};
        if((s.e0 &&
            !select(s.e0))
            || (s.e1
                && !select(s.e1))
            || (s.e2
                && !select(s.e2))
            || !select(s.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sf_d_e_e_s>(is->var))
        return notSupportError("\"for-statement\" which include declaration is not supported");
    else
        return invalidVariantError("IterationStatement");

    return true;
}

bool Selector::select(const TOKEN::Expression *expression)
{
    for(const auto *ae : expression->seq)
    {
        if(!select(ae))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::AssignmentExpression *ae)
{
    using AE = TOKEN::AssignmentExpression;

    if(std::holds_alternative<AE::Sce>(ae->var))
    {
        const auto &s{std::get<AE::Sce>(ae->var)};
        if(!select(s.ce))
            return false;
    }
    else if(std::holds_alternative<AE::Sue_ao_ae>(ae->var))
    {
        const auto &s{std::get<AE::Sue_ao_ae>(ae->var)};
        if(!select(s.ue)
            || !select(s.ae))
            return false;
    }
    else
        return invalidVariantError("AssignmentExpression");
    
    return true;
}

bool Selector::select(const TOKEN::ConditionalExpression *ce)
{
    using CE = TOKEN::ConditionalExpression;

    if(std::holds_alternative<CE::Slore>(ce->var))
    {
        const auto &s{std::get<CE::Slore>(ce->var)};
        if(!select(s.lore))
            return false;
    }
    else if(std::holds_alternative<CE::Slore_e_ce>(ce->var))
    {
        const auto &s{std::get<CE::Slore_e_ce>(ce->var)};
        if(!select(s.lore)
            || !select(s.e)
            || !select(s.ce))
            return false;
    }
    else
        return invalidVariantError("ConditionalExpression");

    return true;
}

bool Selector::select(const TOKEN::LogicalORExpression *lore)
{
    for(const auto *lande : lore->seq)
    {
        if(!select(lande))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::LogicalANDExpression *lande)
{
    for(const auto *iore : lande->seq)
    {
        if(!select(iore))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::InclusiveORExpression *iore)
{
    for(const auto *eore : iore->seq)
    {
        if(!select(eore))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::ExclusiveORExpression *eore)
{
    for(const auto *ande : eore->seq)
    {
        if(!select(ande))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::ANDExpression *ande)
{
    for(const auto *ee : ande->seq)
    {
        if(!select(ee))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::EqualityExpression *ee)
{
    using EE = TOKEN::EqualityExpression;

    for(const auto &v : ee->seq)
    {
        if(std::holds_alternative<EE::Sre>(v))
        {
            if(!select(std::get<EE::Sre>(v).re))
                return false;
        }
        else if(std::holds_alternative<EE::Se_re>(v))
        {
            if(!select(std::get<EE::Se_re>(v).re))
                return false;
        }
        else if(std::holds_alternative<EE::Sne_re>(v))
        {
            if(!select(std::get<EE::Sne_re>(v).re))
                return false;
        }
        else
            return invalidVariantError("EqualityExpression");
    }

    return true;
}

bool Selector::select(const TOKEN::RelationalExpression *re)
{
    using RE = TOKEN::RelationalExpression;

    for(const auto &v : re->seq)
    {
        if(std::holds_alternative<RE::Sse>(v))
        {
            if(!select(std::get<RE::Sse>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sl_se>(v))
        {
            if(!select(std::get<RE::Sl_se>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sg_se>(v))
        {
            if(!select(std::get<RE::Sg_se>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sle_se>(v))
        {
            if(!select(std::get<RE::Sle_se>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sge_se>(v))
        {
            if(!select(std::get<RE::Sge_se>(v).se))
                return false;
        }
        else
            return invalidVariantError("RelationalExpression");
    }

    return true;
}

bool Selector::select(const TOKEN::ShiftExpression *se)
{
    using SE = TOKEN::ShiftExpression;

    for(const auto &v : se->seq)
    {
        if(std::holds_alternative<SE::Sae>(v))
        {
            if(!select(std::get<SE::Sae>(v).ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sl_ae>(v))
        {
            if(!select(std::get<SE::Sl_ae>(v).ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sr_ae>(v))
        {
            if(!select(std::get<SE::Sr_ae>(v).ae))
                return false;
        }
        else
            return invalidVariantError("ShiftExpression");
    }

    return true;
}

bool Selector::select(const TOKEN::AdditiveExpression *ae)
{
    using AE = TOKEN::AdditiveExpression;

    for(const auto &v : ae->seq)
    {
        if(std::holds_alternative<AE::Sme>(v))
        {
            if(!select(std::get<AE::Sme>(v).me))
                return false;
        }
        else if(std::holds_alternative<AE::Sa_me>(v))
        {
            if(!select(std::get<AE::Sa_me>(v).me))
                return false;
        }
        else if(std::holds_alternative<AE::Ss_me>(v))
        {
            if(!select(std::get<AE::Ss_me>(v).me))
                return false;
        }
        else
            return invalidVariantError("AdditiveExpression");
    }

    return true;
}

bool Selector::select(const TOKEN::MultiplicativeExpression *me)
{
    using ME = TOKEN::MultiplicativeExpression;

    for(const auto &v : me->seq)
    {
        if(std::holds_alternative<ME::Sce>(v))
        {
            if(!select(std::get<ME::Sce>(v).ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sm_ce>(v))
        {
            if(!select(std::get<ME::Sm_ce>(v).ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sd_ce>(v))
        {
            if(!select(std::get<ME::Sd_ce>(v).ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sr_ce>(v))
        {
            if(!select(std::get<ME::Sr_ce>(v).ce))
                return false;
        }
        else
            return invalidVariantError("MultiplicativeExpression");
    }

    return true;
}

bool Selector::select(const TOKEN::CastExpression *ce)
{
    using CE = TOKEN::CastExpression;

    if(std::holds_alternative<CE::Sue>(ce->var))
    {
        if(!select(std::get<CE::Sue>(ce->var).ue))
                return false;
    }
    else if(std::holds_alternative<CE::Stn_ce>(ce->var))
    {
        const auto &s{std::get<CE::Stn_ce>(ce->var)};
        if(!select(s.tn)
            || !select(s.ce))
            return false;
    }
    else
        return invalidVariantError("CastExpression");
    
    return true;
}

bool Selector::select(const TOKEN::UnaryExpression *ue)
{
    using UE = TOKEN::UnaryExpression;

    if(std::holds_alternative<UE::Spe>(ue->var))
    {
        if(!select(std::get<UE::Spe>(ue->var).pe))
            return false;
    }
    else if(std::holds_alternative<UE::Si_ue>(ue->var))
    {
        if(!select(std::get<UE::Si_ue>(ue->var).ue))
            return false;
    }
    else if(std::holds_alternative<UE::Sd_ue>(ue->var))
    {
        if(!select(std::get<UE::Sd_ue>(ue->var).ue))
            return false;
    }
    else if(std::holds_alternative<UE::Suo_ce>(ue->var))
    {
        if(!select(std::get<UE::Suo_ce>(ue->var).ce))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_ue>(ue->var))
    {
        if(!select(std::get<UE::Ss_ue>(ue->var).ue))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_tn>(ue->var))
    {
        if(!select(std::get<UE::Ss_tn>(ue->var).tn))
            return false;
    }
    else if(std::holds_alternative<UE::Sa_tn>(ue->var))
    {
        if(!select(std::get<UE::Sa_tn>(ue->var).tn))
            return false;
    }
    else
        return invalidVariantError("UnaryExpression");
    
    return true;
}

bool Selector::select(const TOKEN::PostfixExpression *pe)
{
    using PE = TOKEN::PostfixExpression;

    for(const auto &v : pe->seq)
    {
        if(std::holds_alternative<PE::Spe>(v))
        {
            if(!select(std::get<PE::Spe>(v).pe))
                return false;
        }
        else if(std::holds_alternative<PE::Se>(v))
        {
            if(!select(std::get<PE::Se>(v).e))
                return false;
        }
        else if(std::holds_alternative<PE::Sael>(v))
        {
            const auto &s{std::get<PE::Sael>(v)};
            if(bool(s.ael))
                if(!select(s.ael))
                    return false;
        }
        else if(std::holds_alternative<PE::Sp_i>(v))
        {
            // if(!select(std::get<PE::Sp_i>(v).i))
            //     return false;
        }
        else if(std::holds_alternative<PE::Sa_i>(v))
        {
            // if(!select(std::get<PE::Sa_i>(v).i))
            //     return false;
        }
        else if(std::holds_alternative<PE::Si>(v)
            || std::holds_alternative<PE::Sd>(v))
            ;
        else if(std::holds_alternative<PE::Stn_il>(v))
        {
            const auto &s{std::get<PE::Stn_il>(v)};
            if(!select(s.tn)
                || !select(s.il))
                return false;
        }
        else
            return invalidVariantError("PostfixExpression");
    }

    return true;
}

bool Selector::select(const TOKEN::PrimaryExpression *pe)
{
    using namespace TOKEN;

    if(std::holds_alternative<Identifier*>(pe->var))
    {
        if(!select(std::get<Identifier*>(pe->var)))
            return false;
    }
    else if(std::holds_alternative<Constant*>(pe->var))
    {
        if(!select(std::get<Constant*>(pe->var)))
            return false;
    }
    else if(std::holds_alternative<StringLiteral*>(pe->var))
        ;
    else if(std::holds_alternative<Expression*>(pe->var))
    {
        if(!select(std::get<Expression*>(pe->var)))
            return false;
    }
    else if(std::holds_alternative<GenericSelection*>(pe->var))
    {
        if(!select(std::get<GenericSelection*>(pe->var)))
            return false;
    }
    else
        return invalidVariantError("PrimaryExpression");
    
    return true;
}

bool Selector::select(const TOKEN::Constant *constant)
{
    using namespace TOKEN;

    if(std::holds_alternative<IntegerConstant*>(constant->var)
        || std::holds_alternative<FloatingConstant*>(constant->var)
        || std::holds_alternative<CharacterConstant*>(constant->var))
        ;
    else if(std::holds_alternative<EnumerationConstant*>(constant->var))
    {
        if(!select(std::get<EnumerationConstant*>(constant->var)))
            return false;
    }
    else
        return invalidVariantError("Constant");

    return true;
}

bool Selector::select(const TOKEN::GenericSelection *gs)
{
    if(!select(gs->ae)
        || !select(gs->gal))
        return false;
    
    return true;
}

bool Selector::select(const TOKEN::GenericAssocList *gal)
{
    for(const auto *ga : gal->seq)
    {
        if(!select(ga))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::GenericAssociation *ga)
{
    using GA = TOKEN::GenericAssociation;

    if(std::holds_alternative<GA::Stn_ae>(ga->var))
    {
        const auto &s{std::get<GA::Stn_ae>(ga->var)};
        if(!select(s.tn)
            || !select(s.ae))
            return false;
    }
    else if(std::holds_alternative<GA::Sae>(ga->var))
    {
        const auto &s{std::get<GA::Sae>(ga->var)};
        if(!select(s.ae))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::EnumerationConstant *ec)
{
    if(!select(ec->i))
        return false;
    
    return true;
}

bool Selector::select(const TOKEN::ConstantExpression *ce)
{
    if(!select(ce->ce))
        return false;
    
    return true;
}

bool Selector::select(const TOKEN::StaticAssertDeclaration *sad)
{
    if(!select(sad->ce))
        return false;
    
    return true;
}

bool Selector::select(const TOKEN::ArgumentExpressionList *ael)
{
    for(const auto *ae : ael->seq)
    {
        if(!select(ae))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::InitializerList *il)
{
    for(const auto s : il->seq)
    {
        if(bool(s.d))
            if(!select(s.d))
                return false;
        
        if(!select(s.i))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::Designation *designation)
{
    if(!select(designation->dl))
        return false;
    
    return true;
}

bool Selector::select(const TOKEN::DesignatorList *dl)
{
    for(const auto *d : dl->seq)
    {
        if(!select(d))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::Designator *designator)
{
    using namespace TOKEN;

    if(std::holds_alternative<ConstantExpression*>(designator->var))
    {
        if(!select(std::get<ConstantExpression*>(designator->var)))
            return false;
    }
    else if(std::holds_alternative<Identifier*>(designator->var))
    {
        if(!select(std::get<Identifier*>(designator->var)))
            return false;
    }
    else
        return invalidVariantError("Designator");

    return true;
}

bool Selector::select(const TOKEN::Initializer *initializer)
{
    using namespace TOKEN;

    if(std::holds_alternative<AssignmentExpression*>(initializer->var))
    {
        if(!select(std::get<AssignmentExpression*>(initializer->var)))
            return false;
    }
    else if(std::holds_alternative<InitializerList*>(initializer->var))
    {
        if(!select(std::get<InitializerList*>(initializer->var)))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::TypeName *tn)
{
    if(!select(tn->sql))
        return false;
    
    if(bool(tn->ad))
        if(!select(tn->ad))
            return false;
    
    return true;
}

bool Selector::select(const TOKEN::SpecifierQualifierList *sql)
{
    using namespace TOKEN;

    for(const auto &v : sql->seq)
    {
        if(std::holds_alternative<TypeSpecifier*>(v))
        {
            if(!select(std::get<TypeSpecifier*>(v)))
                return false;
        }
        else if(std::holds_alternative<TypeQualifier*>(v))
            ;
        else if(std::holds_alternative<AttributeSpecifierList*>(v))
        {
            if(!select(std::get<AttributeSpecifierList*>(v)))
                return false;
        }
        else
            return invalidVariantError("SpecifierQualifierList");
    }

    return true;
}

bool Selector::select(const TOKEN::TypeSpecifier *ts)
{
    using namespace TOKEN;

    if(std::holds_alternative<TypeSpecifier::Tag>(ts->var))
        ;
    else if(std::holds_alternative<AtomicTypeSpecifier*>(ts->var))
    {
        if(!select(std::get<AtomicTypeSpecifier*>(ts->var)))
            return false;
    }
    else if(std::holds_alternative<StructOrUnionSpecifier*>(ts->var))
    {
        if(!select(std::get<StructOrUnionSpecifier*>(ts->var)))
            return false;
    }
    else if(std::holds_alternative<EnumSpecifier*>(ts->var))
    {
        if(!select(std::get<EnumSpecifier*>(ts->var)))
            return false;
    }
    else if(std::holds_alternative<TypedefName*>(ts->var))
    {
        if(!select(std::get<TypedefName*>(ts->var)))
            return false;
    }
    else
        return invalidVariantError("TypeSpecifier");
    
    return true;
}

bool Selector::select(const TOKEN::AtomicTypeSpecifier *ats)
{
    if(!select(ats->tn))
        return false;
    
    return true;
}

bool Selector::select(const TOKEN::StructOrUnionSpecifier *sous)
{
    using SOUS = TOKEN::StructOrUnionSpecifier;

    if(std::holds_alternative<SOUS::Ssou_i_sdl>(sous->var))
    {
        const auto &s{std::get<SOUS::Ssou_i_sdl>(sous->var)};
        if(s.asl != nullptr
            && !select(s.asl))
            return false;
        if(bool(s.i))
            if(!select(s.i))
                return false;
        if(!select(s.sdl))
            return false;
    }
    else if(std::holds_alternative<SOUS::Ssou_i>(sous->var))
    {
        const auto &s{std::get<SOUS::Ssou_i>(sous->var)};
        if(s.asl != nullptr
            && !select(s.asl))
            return false;
        if(!select(s.i))
            return false;
    }
    else
        return invalidVariantError("StructOrUnionSpecifier");

    return true;
}

bool Selector::select(const TOKEN::StructDeclarationList *sdl)
{
    for(const auto *sd : sdl->seq)
    {
        if(!select(sd))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::StructDeclaration *sd)
{
    using SD = TOKEN::StructDeclaration;

    if(std::holds_alternative<SD::Ssql_sdl>(sd->var))
    {
        const auto &s{std::get<SD::Ssql_sdl>(sd->var)};
        if(!select(s.sql))
            return false;
        if(bool(s.sdl))
            if(!select(s.sdl))
                return false;
    }
    else if(std::holds_alternative<SD::Ssad>(sd->var))
    {
        const auto &s{std::get<SD::Ssad>(sd->var)};
        if(!select(s.sad))
            return false;
    }
    else
        return invalidVariantError("StructDeclaration");

    return true;
}

bool Selector::select(const TOKEN::StructDeclaratorList *sdl)
{
    for(const auto *sd : sdl->seq)
    {
        if(!select(sd))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::StructDeclarator *sd)
{
    using SD = TOKEN::StructDeclarator;

    if(std::holds_alternative<SD::Sd>(sd->var))
    {
        const auto &s{std::get<SD::Sd>(sd->var)};
        if(!select(s.d))
            return false;
    }
    else if(std::holds_alternative<SD::Sd_ce>(sd->var))
    {
        const auto &s{std::get<SD::Sd_ce>(sd->var)};
        if(bool(s.d))
            if(!select(s.d))
                return false;
        if(!select(s.ce))
            return false;
    }
    else
        return invalidVariantError("StructDeclarator");

    return true;
}

bool Selector::select(const TOKEN::Declarator *declarator)
{
    if(bool(declarator->p))
        if(!select(declarator->p))
            return false;
    if(!select(declarator->dd))
        return false;
    
    return true;
}

bool Selector::select(const TOKEN::DirectDeclarator *dd)
{
    using DD = TOKEN::DirectDeclarator;

    for(const auto &v : dd->seq)
    {
        if(std::holds_alternative<DD::Si>(v))
        {
            const auto &s{std::get<DD::Si>(v)};
            if(!select(s.i))
                return false;
        }
        else if(std::holds_alternative<DD::Sd>(v))
        {
            const auto &s{std::get<DD::Sd>(v)};
            if(!select(s.d))
                return false;
        }
        else if(std::holds_alternative<DD::Stql_ae>(v))
        {
            const auto &s{std::get<DD::Stql_ae>(v)};
            if(bool(s.ae))
                if(!select(s.ae))
                    return false;
        }
        else if(std::holds_alternative<DD::Stql>(v))
            ;
        else if(std::holds_alternative<DD::Sptl>(v))
        {
            const auto &s{std::get<DD::Sptl>(v)};
            if(!select(s.ptl))
                return false;
        }
        else if(std::holds_alternative<DD::Sil>(v))
        {
            const auto &s{std::get<DD::Sil>(v)};
            if(bool(s.il))
                return notSupportError("IdentifierList");
        }
        else
            return invalidVariantError("DirectDeclarator");
    }

    return true;
}

bool Selector::select(const TOKEN::ParameterTypeList *ptl)
{
    if(!select(ptl->pl))
        return false;
    
    return true;
}

bool Selector::select(const TOKEN::ParameterList *pl)
{
    for(const auto *pd : pl->seq)
    {
        if(!select(pd))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::ParameterDeclaration *pd)
{
    using PD = TOKEN::ParameterDeclaration;

    if(std::holds_alternative<PD::Sds_d>(pd->var))
    {
        const auto &s{std::get<PD::Sds_d>(pd->var)};
        if(!select(s.ds)
            || !select(s.d))
            return false;
    }
    else if(std::holds_alternative<PD::Sds_ad>(pd->var))
    {
        const auto &s{std::get<PD::Sds_ad>(pd->var)};
        if(!select(s.ds))
            return false;
        
        if(bool(s.ad))
            if(!select(s.ad))
                return false;
    }
    else
        return invalidVariantError("ParameterDeclaration");
    
    return true;
}

bool Selector::select(const TOKEN::DeclarationSpecifiers *ds)
{
    using namespace TOKEN;

    for(const auto &v : ds->seq)
    {
        if(std::holds_alternative<StorageClassSpecifier*>(v)
            || std::holds_alternative<TypeQualifier*>(v)
            || std::holds_alternative<FunctionSpecifier*>(v))
            ;
        else if(std::holds_alternative<TypeSpecifier*>(v))
        {
            if(!select(std::get<TypeSpecifier*>(v)))
                return false;
        }
        else if(std::holds_alternative<AlignmentSpecifier*>(v))
        {
            if(!select(std::get<AlignmentSpecifier*>(v)))
                return false;
        }
        else if(std::holds_alternative<AttributeSpecifierList*>(v))
        {
            if(!select(std::get<AttributeSpecifierList*>(v)))
                return false;
        }
        else
            return invalidVariantError("DeclarationSpecifiers");
    }

    return true;
}

bool Selector::select(const TOKEN::AlignmentSpecifier *as)
{
    using namespace TOKEN;

    if(std::holds_alternative<TypeName*>(as->var))
    {
        if(!select(std::get<TypeName*>(as->var)))
            return false;
    }
    else if(std::holds_alternative<ConstantExpression*>(as->var))
    {
        if(!select(std::get<ConstantExpression*>(as->var)))
            return false;
    }
    else
        return invalidVariantError("AlignmentSpecifier");
    
    return true;
}

bool Selector::select(const TOKEN::EnumSpecifier *es)
{
    using ES = TOKEN::EnumSpecifier;

    if(std::holds_alternative<ES::Si_el>(es->var))
    {
        const auto &s{std::get<ES::Si_el>(es->var)};
        if(s.asl != nullptr
            && !select(s.asl))
            return false;
        if(bool(s.i))
            if(!select(s.i))
                return false;
        if(!select(s.el))
            return false;
    }
    else if(std::holds_alternative<ES::Si>(es->var))
    {
        const auto &s{std::get<ES::Si>(es->var)};
        if(s.asl != nullptr
            && !select(s.asl))
            return false;
        if(!select(s.i))
            return false;
    }
    else
        return invalidVariantError("EnumSpecifier");
    
    return true;
}

bool Selector::select(const TOKEN::EnumeratorList *el)
{
    for(const auto *e : el->seq)
    {
        if(!select(e))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::Enumerator *enumerator)
{
    using E = TOKEN::Enumerator;

    if(std::holds_alternative<E::Sec>(enumerator->var))
    {
        const auto &s{std::get<E::Sec>(enumerator->var)};
        if(!select(s.ec))
            return false;
        if(s.asl != nullptr
            && !select(s.asl))
            return false;
    }
    else if(std::holds_alternative<E::Sec_ce>(enumerator->var))
    {
        const auto &s{std::get<E::Sec_ce>(enumerator->var)};
        if(!select(s.ec))
            return false;
        if(s.asl != nullptr
            && !select(s.asl))
            return false;
        if(!select(s.ce))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::TypedefName *tn)
{
    if(!select(tn->i))
        return false;

    return true;
}

bool Selector::select(const TOKEN::AbstractDeclarator *ad)
{
    using AD = TOKEN::AbstractDeclarator;

    if(std::holds_alternative<AD::Sp>(ad->var))
    {
        const auto &s{std::get<AD::Sp>(ad->var)};
        if(!select(s.p))
            return false;
    }
    else if(std::holds_alternative<AD::Sp_dad>(ad->var))
    {
        const auto &s{std::get<AD::Sp_dad>(ad->var)};
        if(bool(s.p))
            if(!select(s.p))
                return false;
        if(!select(s.dad))
            return false;
    }
    else
        return invalidVariantError("AbstractDeclarator");
    
    return true;
}

bool Selector::select(const TOKEN::Pointer *pointer)
{
    return true;
}

bool Selector::select(const TOKEN::DirectAbstractDeclarator *dad)
{
    using DAD = TOKEN::DirectAbstractDeclarator;

    for(const auto &v : dad->seq)
    {
        if(std::holds_alternative<DAD::Sad>(v))
        {
            const auto &s{std::get<DAD::Sad>(v)};
            if(!select(s.ad))
                return false;
        }
        else if(std::holds_alternative<DAD::Stql_ae>(v))
        {
            const auto &s{std::get<DAD::Stql_ae>(v)};
            if(bool(s.ae))
                if(!select(s.ae))
                    return false;
        }
        else if(std::holds_alternative<DAD::Sp>(v))
            ;
        else if(std::holds_alternative<DAD::Sptl>(v))
        {
            const auto &s{std::get<DAD::Sptl>(v)};
            if(bool(s.ptl))
                if(!select(s.ptl))
                    return false;
        }
        else
            return invalidVariantError("DirectAbstractDeclarator");
    }

    return true;
}

bool Selector::select(const TOKEN::AttributeSpecifierList *asl)
{
    for(auto &&as : asl->seq)
    {
        if(!select(as))
            return false;
    }

    return true;
}

bool Selector::select(const TOKEN::AttributeSpecifier *as)
{
    mIsFittables.push_back(false);

    return true;
}

bool Selector::select(const TOKEN::AttributeStatement *as)
{
    if(!select(as->asl))
        return false;
    
    return true;
}

bool Selector::clearError() const
{
    std::cerr << "GA::Selector error:\n"
        "    what: failed to clear previous value.\n"
        << std::flush;
    return false;
}

bool Selector::invalidStatementError() const
{
    std::cerr << "GA::Selector error:\n"
        "    what: invalid statement.\n"
        << std::flush;
    return false;
}

bool Selector::invalidVariantError(const std::string &className) const
{
    std::cerr << "GA::Selector error:\n"
        "    what: variant has invalid entity.\n"
        "    class: " << className
        << std::endl;
    return false;
}

bool Selector::isNotFoundIdentifier() const
{
    std::cerr << "GA::Selector error:\n"
        "    what: not found identifier that is same type.\n"
        << std::flush;
    return false;
}

bool Selector::notSupportError(const std::string &name) const
{
    std::cerr << "GA::Selector error:\n"
        "    what: not support.\n"
        "    ---: " << name
        << std::endl;
    return false;
}

bool Selector::lackIdError() const
{
    std::cerr << "GA::Selector error:\n"
        "    what: lack of id-list.\n"
        << std::flush;
    return false;
}

bool Selector::unusedIdError() const
{
    std::cerr << "GA::Selector error:\n"
        "    what: exists unused identifier-id.\n"
        << std::flush;
    return false;
}

}