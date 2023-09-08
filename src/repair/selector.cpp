#include <unordered_set>
#include <iostream>
#include <limits>
#include <algorithm>
#include <iterator>

#include "configure.hpp"
#include "utility/output.hpp"
#include "utility/random.hpp"
#include "common/statement.hpp"
#include "common/scope.hpp"
#include "common/identifier.hpp"
#include "common/token.hpp"
#include "register.hpp"
#include "selector.hpp"

namespace REPAIR
{

decltype(Selector::mCache) Selector::mCache{};
decltype(Selector::mCacheMutex) Selector::mCacheMutex{};
decltype(Selector::mAlternativeIdsInit) Selector::mAlternativeIdsInit{};

Selector::Selector()
    : mTag{Tag::CAN_CONVERT}
    , mStatementId{std::numeric_limits<std::size_t>::max()}
    , mScopeId{std::numeric_limits<std::size_t>::max()}
    , mAlternativeIdsRef{mAlternativeIdsInit}
    , mAlternativeIdsIndex{0ull}
{
}

Selector::~Selector()
{
}

bool Selector::canConvert(std::size_t statementId
    , std::size_t scopeId)
{
    Tag prevTag{mTag};
    mTag = Tag::CAN_CONVERT;
    mStatementId = statementId;
    mScopeId = scopeId;

    // if cache has no data, creates a new cache data.
    std::unique_lock<std::mutex> lock{mCacheMutex};
    if(!mCache.contains(std::make_pair(statementId, scopeId)))
    {
        lock.unlock();
        calculateCandidates();
        lock.lock();
    }

    mTag = prevTag;
    return mCache.at(std::make_pair(statementId, scopeId)).has_value();
}

std::pair<std::size_t, bool> Selector::convert(std::size_t statementId
    , std::size_t scopeId
    , std::deque<std::size_t> &alternativeIds)
{
    mTag = Tag::CONVERT;
    mStatementId = statementId;
    mScopeId = scopeId;
    mAlternativeIdsRef = alternativeIds;

    auto &&canConverted{canConvert(statementId, scopeId)};
    if(!canConverted)
    {
        conversionError();
        return {std::numeric_limits<std::size_t>::max(), false};
    }

    if(!selectAlternativeIds())
        return {std::numeric_limits<std::size_t>::max(), false};
    
    TOKEN::Statement *convertedStatement{STATEMENT::get<TOKEN::Statement>(statementId)->copy()};
    if(!select(convertedStatement))
        return {std::numeric_limits<std::size_t>::max(), false};
    
    std::optional<std::size_t> convertedStatementIdOpt{Register::execute(convertedStatement)};
    if(!convertedStatementIdOpt.has_value())
        return {std::numeric_limits<std::size_t>::max(), false};

    return {convertedStatementIdOpt.value(), true};
}

bool Selector::calculateCandidates()
{
    Tag prevTag{mTag};
    mTag = Tag::CREATE_CACHE;

    std::shared_ptr<TOKEN::Statement> statementSp{STATEMENT::get<TOKEN::Statement>(mStatementId)};

    std::unique_lock<std::mutex> lock{mCacheMutex};
    mCache.emplace(std::make_pair(mStatementId, mScopeId)
        , decltype(mCache)::mapped_type::value_type{});
    lock.unlock();

    bool isSuccessful{statementSp.get() != nullptr
        && select(statementSp.get())
        && checkValidity()};

    if(!isSuccessful)
        mCache.at(std::make_pair(mStatementId, mScopeId)) = std::nullopt;

    mTag = prevTag;

    return true;
}

bool Selector::selectAlternativeIds()
{
    std::unique_lock<std::mutex> lock{mCacheMutex};
    const auto &[appearingIds, multimap]{mCache.at(std::make_pair(mStatementId, mScopeId)).value()};

    switch(Configure::getSafelyIDENTIFIER_SELECTION_TAG())
    {
        // random
        case(Configure::IdentifierSelectionTag::RANDOM):
        {
            for(const auto &appearingId : appearingIds)
            {
                auto &&[iter, last]{multimap.equal_range(appearingId)};
                std::advance(iter
                    , RANDOM::RAND(std::distance(iter, last)));
                mAlternativeIdsRef.get().emplace_back(iter->second);
            }
            break;
        }
        // duplicated
        case(Configure::IdentifierSelectionTag::DUPLICATED):
        {
            // key: id that is appeared in base statement.
            // value: candidate id
            std::unordered_map<std::size_t, std::size_t> correspondingMap;
            for(const auto &appearingId : appearingIds)
            {
                if(auto &&mapIter{correspondingMap.find(appearingId)};
                    mapIter == correspondingMap.end())
                {
                    auto &&[multimapIter, last]{multimap.equal_range(appearingId)};
                    std::advance(multimapIter
                        , RANDOM::RAND(std::distance(multimapIter, last)));
                    mAlternativeIdsRef.get().emplace_back(multimapIter->second);
                    correspondingMap.emplace(appearingId
                        , mAlternativeIdsRef.get().back());
                }
                else
                    mAlternativeIdsRef.get().emplace_back(mapIter->second);
            }
            break;
        }
        // no duplicated
        case(Configure::IdentifierSelectionTag::NO_DUPLICATED):
        {
            // key: id that is appeared in base statement.
            // value: candidate id
            std::unordered_map<std::size_t, std::size_t> correspondingMap;
            // key: candidate id that is used another identifier.
            std::unordered_set<std::size_t> usedCandidateSet;
            std::unordered_map<std::size_t, std::deque<std::size_t>> shuffledCandidatesMap;

            for(const auto &appearingId : appearingIds)
            {
                if(!shuffledCandidatesMap.contains(appearingId))
                {
                    shuffledCandidatesMap.emplace(appearingId
                        , std::deque<std::size_t>());
                    for(auto &&[iter, last]{multimap.equal_range(appearingId)};
                        iter != last;
                        iter++)
                        shuffledCandidatesMap.at(appearingId).emplace_back(iter->second);

                    std::shuffle(shuffledCandidatesMap.at(appearingId).begin()
                        , shuffledCandidatesMap.at(appearingId).end()
                        , RANDOM::RAND.engine());
                }

                if(auto &&iter{correspondingMap.find(appearingId)};
                    iter == correspondingMap.end())
                {
                    while(usedCandidateSet.contains(shuffledCandidatesMap.at(appearingId).front()))
                        shuffledCandidatesMap.at(appearingId).pop_front();

                    mAlternativeIdsRef.get().emplace_back(shuffledCandidatesMap.at(appearingId).front());
                    shuffledCandidatesMap.at(appearingId).pop_front();
                    correspondingMap.emplace(appearingId
                        , mAlternativeIdsRef.get().back());
                    usedCandidateSet.emplace(mAlternativeIdsRef.get().back());
                }
                else
                    mAlternativeIdsRef.get().emplace_back(iter->second);
            }

            break;
        }
    }

    return true;
}

bool Selector::checkValidity()
{
    std::unique_lock<std::mutex> lock{mCacheMutex};
    const auto &[appearingIds, multimap]{mCache.at(std::make_pair(mStatementId, mScopeId)).value()};

    bool isValid{true};
    switch(Configure::getSafelyIDENTIFIER_SELECTION_TAG())
    {
        case(Configure::IdentifierSelectionTag::RANDOM):
        case(Configure::IdentifierSelectionTag::DUPLICATED):
        {
            for(const auto &appearingId : appearingIds)
            {
                if(!multimap.contains(appearingId))
                {
                    isValid = false;
                    break;
                }
            }
            break;
        }
        case(Configure::IdentifierSelectionTag::NO_DUPLICATED):
        {
            // key: id that is appeared in base statement.
            std::unordered_set<std::size_t> assignedIdSet;
            // key: used candidate id
            std::unordered_set<std::size_t> usedCandidateSet;
            std::unordered_map<std::size_t, std::deque<std::size_t>> candidateMap;

            for(const auto &appearingId : appearingIds)
            {
                if(!candidateMap.contains(appearingId))
                {
                    candidateMap.emplace(appearingId
                        , std::deque<std::size_t>());
                    for(auto &&[iter, last]{multimap.equal_range(appearingId)};
                        iter != last;
                        iter++)
                        candidateMap.at(appearingId).emplace_back(iter->second);
                }

                if(!assignedIdSet.contains(appearingId))
                {
                    while(true)
                    {
                        if(candidateMap.at(appearingId).empty())
                        {
                            isValid = false;
                            break;
                        }
                        
                        if(usedCandidateSet.contains(candidateMap.at(appearingId).front()))
                            candidateMap.at(appearingId).pop_front();
                        else
                            break;
                    }

                    if(!isValid)
                        break;

                    usedCandidateSet.emplace(candidateMap.at(appearingId).front());
                    assignedIdSet.emplace(appearingId);
                    candidateMap.at(appearingId).pop_front();
                }
            }

            break;
        }
    }

    if(!isValid)
        mCache.at(std::make_pair(mStatementId, mScopeId)) = std::nullopt;

    return true;
}

bool Selector::getVisibleIdentifierList(const std::shared_ptr<IDENTIFIER::Identifier> &id
    , std::deque<std::size_t> &idList)
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
        scope != nullptr;
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
    , std::deque<std::size_t> &idList)
{
    using namespace IDENTIFIER;
    using namespace SCOPE;

    for(std::size_t i{0ull};
        i < idList.size();
        i++)
    {
        if(!isSameType(id
            , IDENTIFIER_MAP.at(idList[i])))
        {
            idList.erase(idList.begin() + i);
            i--;
        }
    }

    return true;
}

bool Selector::convert(TOKEN::Identifier *identifier)
{
    using namespace TOKEN;
    
    if(!std::holds_alternative<Identifier::Id>(identifier->var))
        return invalidVariantError("TOKEN::Identifier");

    auto &&idPair{std::get<Identifier::Id>(identifier->var)};
    idPair.first = mAlternativeIdsRef.get()[mAlternativeIdsIndex++];

    return true;
}

bool Selector::select(TOKEN::Identifier *identifier)
{
    switch(mTag)
    {
        case(Tag::CAN_CONVERT):
        {
            break;
        }
        case(Tag::CREATE_CACHE):
        {
            if(!std::holds_alternative<TOKEN::Identifier::Id>(identifier->var))
                return invalidVariantError("TOKEN::Identifier");

            const auto &[identifierId, scopeId]{std::get<TOKEN::Identifier::Id>(identifier->var)};
            const auto &identifierSp{IDENTIFIER::IDENTIFIER_MAP.at(identifierId)};
            
            std::deque<std::size_t> candidateIds;
            if(!getVisibleIdentifierList(identifierSp, candidateIds)
                || !getSameTypeIdentifier(identifierSp, candidateIds))
                return false;

            std::unique_lock<std::mutex> lock{mCacheMutex};
            auto &&[appearingIds, multimap]{mCache.at(std::make_pair(mStatementId, mScopeId)).value()};
            appearingIds.emplace_back(identifierId);
            if(!multimap.contains(identifierId))
            {
                for(const auto &candidateId : candidateIds)
                    multimap.emplace(identifierId, candidateId);
            }
    
            break;
        }
        case(Tag::CONVERT):
        {
            if(!convert(identifier))
                return false;
            break;
        }
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
    else if(std::holds_alternative<TOKEN::AsmStatement*>(statement->var))
        return select(std::get<TOKEN::AsmStatement*>(statement->var));
    else
        return invalidVariantError("TOKEN::Statement");

    return true;
}

bool Selector::select(const TOKEN::JumpStatement *js)
{
    using JS = TOKEN::JumpStatement;

    if(!Configure::SHOULD_USE_CONTROL_FLOW)
        return false;

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

    if(!Configure::SHOULD_USE_CONTROL_FLOW)
        return false;

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
    else if(std::holds_alternative<LS::Sce_ce_s>(ls->var))
    {
        auto &&s{std::get<LS::Sce_ce_s>(ls->var)};
        if(!select(s.ce0)
            || !select(s.ce1)
            || !select(s.s))
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
        {
            if(mTag == Tag::CREATE_CACHE)
                return false;
            else
                return supportError("declaration is not supported.");            
        }

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
        return supportError("\"for-statement\" which include declaration is not supported");
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
        auto &&il{std::get<InitializerList*>(initializer->var)};
        if(il != nullptr
            && !select(il))
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
    if(declarator->asl != nullptr
        && !select(declarator->asl))
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
                return supportError("IdentifierList");
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
    if(mTag == Tag::CREATE_CACHE)
        return false;
    else
        return supportError("TOKEN::AttributeSpecifier");
}

bool Selector::select(const TOKEN::AttributeStatement *as)
{
    if(!select(as->asl))
        return false;
    
    return true;
}

bool Selector::select(const TOKEN::AsmQualifiers*)
{
    return true;
}

bool Selector::select(const TOKEN::BasicAsm*)
{
    if(mTag == Tag::CREATE_CACHE)
        return false;
    else
        return supportError("TOKEN::BasicAsm");
}

bool Selector::select(const TOKEN::ExtendedAsm*)
{
    if(mTag == Tag::CREATE_CACHE)
        return false;
    else
        return supportError("TOKEN::ExtendedAsm");
}

bool Selector::select(const TOKEN::AsmStatement *as)
{
    if(std::holds_alternative<TOKEN::BasicAsm*>(as->var))
        return select(std::get<TOKEN::BasicAsm*>(as->var));
    else if(std::holds_alternative<TOKEN::ExtendedAsm*>(as->var))
        return select(std::get<TOKEN::ExtendedAsm*>(as->var));
    
    return true;
}

bool Selector::conversionError() const
{
    std::cerr << OUTPUT::charRedCode
        << "REPAIR::Selector::conversionError():\n"
        << OUTPUT::resetCode
        << "    what: failed to conversion statement.\n"
        << std::flush;
    return false;
}

bool Selector::invalidVariantError(const std::string &className) const
{
    std::cerr << OUTPUT::charRedCode
        << "REPAIR::Selector::invalidVariantError():\n"
        << OUTPUT::resetCode
        << "    what: variant has invalid entity.\n"
        "    class: " << className
        << std::endl;
    return false;
}

bool Selector::supportError(const std::string &name) const
{
    std::cerr << OUTPUT::charRedCode
        << "REPAIR::Selector::supportError():\n"
        << OUTPUT::resetCode
        << "    what: no support.\n"
        "    ---: " << name
        << std::endl;
    return false;
}

}