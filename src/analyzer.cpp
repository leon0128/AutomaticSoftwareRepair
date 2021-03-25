#include <iostream>

#include "scope.hpp"
#include "analyzer.hpp"

Analyzer::Analyzer()
    : mFlags{}
    , mScope{nullptr}
{
}

Analyzer::~Analyzer()
{
}

bool Analyzer::execute(const TOKEN::TranslationUnit *tu)
{
    if(!tu)
        return true;

    if(!analyze(tu))
        return false;
    
    return true;
}

bool Analyzer::analyze(const TOKEN::TranslationUnit *tu)
{
    mScope = new SCOPE::Scope(mScope
        , SCOPE::Scope::ScopeTag::FILE);

    for(const auto &ed : tu->seq)
    {
        if(std::holds_alternative<TOKEN::FunctionDefinition*>(ed->var))
        {
            if(!analyze(std::get<TOKEN::FunctionDefinition*>(ed->var)))
                return false;
        }
        else if(std::holds_alternative<TOKEN::Declaration*>(ed->var))
        {
            if(!analyze(std::get<TOKEN::Declaration*>(ed->var)))
                return false;
        }
        else
            variantError("ExternalDeclaration");
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::FunctionDefinition *fd)
{
    mScope = mScope->addChild(SCOPE::Scope::ScopeTag::FUNCTION);
    mScope = mScope->addChild(SCOPE::Scope::ScopeTag::BLOCK);

    bool oldIsFunction{flag(FlagTag::IS_FUNCTION, true)};
    bool oldIsDeclarationOver{flag(FlagTag::IS_DECLARATION_OVER, false)};
    bool oldIsCreatingBlock{flag(FlagTag::IS_CREATING_BLOCK, false)};

    auto &&attrsOpt{analyzeAttributes(fd->ds)};
    if(!attrsOpt)
        return false;
    
    auto &&[storageClassSpec
        , baseType
        , functionSpec
        , alignment]{*attrsOpt};

    auto &&tiOpt{analyzeTypeAndIdentifier(fd->d, baseType)};
    if(!tiOpt)
        return false;
    
    auto &&[type
        , name]{*tiOpt};
    
    auto &&idPtr{mScope->getIdentifier(name
        , SCOPE::Scope::NamespaceTag::OTHER
        , false)};
    if(!idPtr)
    {
        std::shared_ptr<IDENTIFIER::Identifier> id{new IDENTIFIER::Function{name
            , type
            , storageClassSpec
            , functionSpec
            , true}};
        mScope->addIdentifier(id
            , SCOPE::Scope::NamespaceTag::OTHER
            , SCOPE::Scope::ScopeTag::FILE);
        ID_MAP.emplace(id->id()
            , id);
    }
    else
    {
        auto &&funcPtr{std::dynamic_pointer_cast<IDENTIFIER::Function>(idPtr)};
        
        if(!funcPtr)
            return differentTypeError(name);

        if(funcPtr->isDefined())
            return redefinedError(name);

        if(!TYPE::equalTo(funcPtr->type(), type))
            return differentTypeError(name);
        
        funcPtr->isDefined(true);
        funcPtr->storageClass(storageClassSpec);
        funcPtr->functionSpecifiers(functionSpec);
    }

    if(!analyze(fd->cs))
        return false;

    flag(FlagTag::IS_FUNCTION, oldIsFunction);
    flag(FlagTag::IS_DECLARATION_OVER, oldIsDeclarationOver);
    flag(FlagTag::IS_CREATING_BLOCK, oldIsCreatingBlock);

    mScope = mScope->getParent();
    mScope = mScope->getParent();

    return true;
}

bool Analyzer::analyze(const TOKEN::Declaration *d)
{
    if(std::holds_alternative<TOKEN::Declaration::Sds_idl>(d->var))
    {
        auto &&s{std::get<TOKEN::Declaration::Sds_idl>(d->var)};
        
        bool oldIsFuncion{flag(FlagTag::IS_FUNCTION, false)};
        bool oldIsDeclarationOver{flag(FlagTag::IS_DECLARATION_OVER, !s.idl)};
        bool oldIsCreatingBlock(flag(FlagTag::IS_CREATING_BLOCK, true));

        auto &&attrsOpt{analyzeAttributes(s.ds)};
        if(!attrsOpt)
            return false;
        
        auto &&[storageClass
            , baseType
            , functionSpec
            , alignment]{*attrsOpt};
        
        if(!s.idl)
            ;
        else
        {
            for(const auto &id : s.idl->seq)
            {
                using ID = TOKEN::InitDeclarator;

                const TOKEN::Initializer *initializer{nullptr};
                const TOKEN::Declarator *declarator{nullptr};
                if(std::holds_alternative<ID::Sd>(id->var))
                    declarator = std::get<ID::Sd>(id->var).d;
                else if(std::holds_alternative<ID::Sd_i>(id->var))
                {
                    initializer = std::get<ID::Sd_i>(id->var).i;
                    declarator = std::get<ID::Sd_i>(id->var).d;
                }
                else
                    variantError("InitDeclarator");

                auto &&tiOpt{analyzeTypeAndIdentifier(declarator
                    , baseType)};
                if(!tiOpt)
                    return false;
                
                auto &&[type
                    , identifier]{*tiOpt};
                
                auto &&idPtr{mScope->getIdentifier(identifier
                    , SCOPE::Scope::NamespaceTag::OTHER
                    , true)};
                if(!idPtr)
                {
                    std::shared_ptr<IDENTIFIER::Identifier> id;
                    if(storageClass.flags.test(static_cast<std::size_t>(IDENTIFIER::StorageClass::Tag::TYPEDEF)))
                    {
                        id.reset(new IDENTIFIER::Typedef{identifier
                            , type});
                    }
                    else if(std::holds_alternative<TYPE::Function>(type.var))
                    {
                        id.reset(new IDENTIFIER::Function{identifier
                            , type
                            , storageClass
                            , functionSpec
                            , false});
                    }
                    else
                    {
                        id.reset(new IDENTIFIER::Object{identifier
                            , type
                            , storageClass
                            , alignment
                            , bool(initializer)});
                    }

                    mScope->addIdentifier(id
                        , SCOPE::Scope::NamespaceTag::OTHER);
                    ID_MAP.emplace(id->id()
                        , id);
                }
                else
                {
                    if(auto &&tPtr{std::dynamic_pointer_cast<IDENTIFIER::Typedef>(idPtr)};
                        bool(tPtr))
                    {
                        if(!storageClass.flags.test(static_cast<std::size_t>(IDENTIFIER::StorageClass::Tag::TYPEDEF)))
                            return differentTypeError(identifier);
                        
                        if(!TYPE::equalTo(tPtr->type(), type))
                            return differentTypeError(identifier);
                    }
                    else if(auto &&oPtr{std::dynamic_pointer_cast<IDENTIFIER::Object>(idPtr)};
                        bool(oPtr))
                    {   
                        if(mScope->scopeTag() != SCOPE::Scope::ScopeTag::FILE)
                            return redefinedError(identifier);

                        if(storageClass.flags.test(static_cast<std::size_t>(IDENTIFIER::StorageClass::Tag::TYPEDEF)))
                            return differentTypeError(identifier);

                        if(!TYPE::equalTo(oPtr->type(), type))
                            return differentTypeError(identifier);
                        
                        if(oPtr->isDefined() && initializer)
                            return redefinedError(identifier);
                        
                        oPtr->storageClass(storageClass);
                        if(bool(initializer)
                            || mScope->scopeTag() != SCOPE::Scope::ScopeTag::FILE)
                            oPtr->isDefined(true);
                    }
                    else if(auto &&fPtr{std::dynamic_pointer_cast<IDENTIFIER::Function>(idPtr)};
                        bool(fPtr))
                    {                        
                        if(storageClass.flags.test(static_cast<std::size_t>(IDENTIFIER::StorageClass::Tag::TYPEDEF)))
                            return differentTypeError(identifier);

                        if(!TYPE::equalTo(fPtr->type(), type))
                            return differentTypeError(identifier);
                        
                        fPtr->storageClass(storageClass);
                        fPtr->functionSpecifiers(functionSpec);
                    }
                    else
                        variantError("IDENTIFIER::Identifier");
                }

                if(bool(initializer))
                {
                    if(!analyze(initializer))
                        return false;
                }
            }
        }

        flag(FlagTag::IS_FUNCTION, oldIsFuncion);
        flag(FlagTag::IS_DECLARATION_OVER, oldIsDeclarationOver);
        flag(FlagTag::IS_CREATING_BLOCK, oldIsCreatingBlock);
    }
    else if(std::holds_alternative<TOKEN::Declaration::Ssad>(d->var))
        ;
    else
        variantError("Declaration");
    
    return true;
}

bool Analyzer::analyze(const TOKEN::CompoundStatement *cs)
{
    if(flag(FlagTag::IS_CREATING_BLOCK))
        mScope = mScope->addChild(SCOPE::Scope::ScopeTag::BLOCK);
    
    bool oldIsCreatingBlock{flag(FlagTag::IS_CREATING_BLOCK, true)};

    if(bool(cs->bil))
    {
        for(const auto &bi : cs->bil->seq)
        {
            if(std::holds_alternative<TOKEN::Declaration*>(bi->var))
            {
                if(!analyze(std::get<TOKEN::Declaration*>(bi->var)))
                    return false;
            }
            else if(std::holds_alternative<TOKEN::Statement*>(bi->var))
            {
                if(!analyze(std::get<TOKEN::Statement*>(bi->var)))
                    return false;
            }
            else
                variantError("BlockItem");
        }
    }

    flag(FlagTag::IS_CREATING_BLOCK, oldIsCreatingBlock);
    
    if(flag(FlagTag::IS_CREATING_BLOCK))
        mScope = mScope->getParent();
    
    return true;
}

bool Analyzer::analyze(const TOKEN::Statement *s)
{
    if(std::holds_alternative<TOKEN::LabeledStatement*>(s->var))
    {
        if(!analyze(std::get<TOKEN::LabeledStatement*>(s->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::CompoundStatement*>(s->var))
    {
        if(!analyze(std::get<TOKEN::CompoundStatement*>(s->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::ExpressionStatement*>(s->var))
    {
        if(!analyze(std::get<TOKEN::ExpressionStatement*>(s->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::SelectionStatement*>(s->var))
    {
        if(!analyze(std::get<TOKEN::SelectionStatement*>(s->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::IterationStatement*>(s->var))
    {
        if(!analyze(std::get<TOKEN::IterationStatement*>(s->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::JumpStatement*>(s->var))
    {
        if(!analyze(std::get<TOKEN::JumpStatement*>(s->var)))
            return false;
    }
    else
        variantError("Statement");
    
    return true;
}

bool Analyzer::analyze(const TOKEN::LabeledStatement *ls)
{
    using LS = TOKEN::LabeledStatement;

    if(std::holds_alternative<LS::Si_s>(ls->var))
    {
        auto &&s{std::get<LS::Si_s>(ls->var)};
        std::string identifier{TOKEN::str(s.i)};

        auto &&iPtr{mScope->getIdentifier(identifier
            , SCOPE::Scope::NamespaceTag::LABEL
            , false)};
        if(!iPtr)
        {
            std::shared_ptr<IDENTIFIER::Identifier> id{new IDENTIFIER::Label{identifier
                , true}};
            mScope->addIdentifier(id
                , SCOPE::Scope::NamespaceTag::LABEL
                , SCOPE::Scope::ScopeTag::FUNCTION);
            ID_MAP.emplace(id->id()
                , id);
        }
        else
        {
            auto &&label{std::dynamic_pointer_cast<IDENTIFIER::Label>(iPtr)};
            if(!label)
                return differentTypeError(identifier);
            
            label->isDefined(true);
        }
    }
    else if(std::holds_alternative<LS::Sce_s>(ls->var))
    {
        auto &&s{std::get<LS::Sce_s>(ls->var)};
        if(!analyze(s.ce))
            return false;

        if(!analyze(s.s))
            return false;
    }
    else if(std::holds_alternative<LS::Ss>(ls->var))
    {
        auto &&s{std::get<LS::Ss>(ls->var)};
        if(!analyze(s.s))
            return false;
    }
    else
        variantError("LabeldStatement");

    return true;
}

bool Analyzer::analyze(const TOKEN::ExpressionStatement *es)
{
    if(bool(es->e))
    {
        if(!analyze(es->e))
            return false;
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::SelectionStatement *ss)
{
    using SS = TOKEN::SelectionStatement;

    if(std::holds_alternative<SS::Si_e_s>(ss->var))
    {
        auto &&s{std::get<SS::Si_e_s>(ss->var)};
        if(!analyze(s.e))
            return false;
        
        if(!analyze(s.s))
            return false;
    }
    else if(std::holds_alternative<SS::Si_e_s_s>(ss->var))
    {
        auto &&s{std::get<SS::Si_e_s_s>(ss->var)};
        if(!analyze(s.e))
            return false;
        
        if(!analyze(s.s0))
            return false;
        
        if(!analyze(s.s1))
            return false;
    }
    else if(std::holds_alternative<SS::Ss_e_s>(ss->var))
    {
        auto &&s{std::get<SS::Ss_e_s>(ss->var)};
        if(!analyze(s.e))
            return false;
        
        if(!analyze(s.s))
            return false;
    }
    else
        variantError("SelectionStatement");
    
    return true;
}

bool Analyzer::analyze(const TOKEN::IterationStatement *is)
{
    using IS = TOKEN::IterationStatement;

    if(std::holds_alternative<IS::Sw_e_s>(is->var))
    {
        auto &&s{std::get<IS::Sw_e_s>(is->var)};
        if(!analyze(s.e))
            return false;

        if(!analyze(s.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sd_s_e>(is->var))
    {
        auto &&s{std::get<IS::Sd_s_e>(is->var)};
        if(!analyze(s.s))
            return false;
        
        if(!analyze(s.e))
            return false;
    }
    else if(std::holds_alternative<IS::Sf_e_e_e_s>(is->var))
    {
        auto &&s{std::get<IS::Sf_e_e_e_s>(is->var)};
        if(!analyze(s.e0))
            return false;
        
        if(!analyze(s.e1))
            return false;
        
        if(!analyze(s.e2))
            return false;
        
        if(!analyze(s.s))
            return false;
    }
    else if(std::holds_alternative<IS::Sf_d_e_e_s>(is->var))
    {
        auto &&s{std::get<IS::Sf_d_e_e_s>(is->var)};
        if(!analyze(s.d))
            return false;
        
        if(!analyze(s.e0))
            return false;
        
        if(!analyze(s.e1))
            return false;
        
        if(!analyze(s.s))
            return false;
    }
    else
        variantError("IterationStatement");
    
    return true;
}

bool Analyzer::analyze(const TOKEN::JumpStatement *js)
{
    using JS = TOKEN::JumpStatement;

    if(std::holds_alternative<JS::Sg_i>(js->var))
    {
        auto &&s{std::get<JS::Sg_i>(js->var)};
        std::string identifier{TOKEN::str(s.i)};

        auto &&iPtr{mScope->getIdentifier(identifier
            , SCOPE::Scope::NamespaceTag::LABEL
            , false)};
        if(!iPtr)
        {
            std::shared_ptr<IDENTIFIER::Identifier> id{new IDENTIFIER::Label{identifier
                , false}};
            
            mScope->addIdentifier(id
                , SCOPE::Scope::NamespaceTag::LABEL
                , SCOPE::Scope::ScopeTag::FUNCTION);
            ID_MAP.emplace(id->id()
                , id);
        }
    }
    else if(std::holds_alternative<JS::Sc>(js->var))
        ;
    else if(std::holds_alternative<JS::Sb>(js->var))
        ;
    else if(std::holds_alternative<JS::Sr_e>(js->var))
    {
        auto &&s{std::get<JS::Sr_e>(js->var)};
        if(bool(s.e))
        {
            if(!analyze(s.e))
                return false;
        }
    }
    else
        variantError("JumpStatement");

    return true;
}

bool Analyzer::analyze(const TOKEN::Initializer *i)
{
    if(std::holds_alternative<TOKEN::AssignmentExpression*>(i->var))
    {
        if(!analyze(std::get<TOKEN::AssignmentExpression*>(i->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::InitializerList*>(i->var))
    {
        if(!analyze(std::get<TOKEN::InitializerList*>(i->var)))
            return false;
    }
    else
        variantError("Initializer");
    
    return true;
}

bool Analyzer::analyze(const TOKEN::InitializerList *il)
{
    for(const auto &s : il->seq)
    {
        if(bool(s.d))
        {
            for(const auto &d : s.d->dl->seq)
            {
                if(std::holds_alternative<TOKEN::ConstantExpression*>(d->var))
                {
                    if(!analyze(std::get<TOKEN::ConstantExpression*>(d->var)))
                        return false;
                }
            }
        }
    }
}

bool Analyzer::analyze(const TOKEN::ConstantExpression *cs)
{
    if(!analyze(cs->ce))
        return false;
    
    return true;
}

bool Analyzer::analyze(const TOKEN::Expression *e)
{
    for(const auto &ae : e->seq)
    {
        if(!analyze(ae))
            return false;
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::AssignmentExpression *ae)
{
    using AE = TOKEN::AssignmentExpression;

    if(std::holds_alternative<AE::Sce>(ae->var))
    {
        auto &&s{std::get<AE::Sce>(ae->var)};
        if(!analyze(s.ce))
            return false;
    }
    else if(std::holds_alternative<AE::Sue_ao_ae>(ae->var))
    {
        auto &&s{std::get<AE::Sue_ao_ae>(ae->var)};
        if(!analyze(s.ue))
            return false;
        
        if(!analyze(s.ae))
            return false;
    }
    else
        variantError("AssignmentExpression");
    
    return true;
}

bool Analyzer::analyze(const TOKEN::ConditionalExpression *ce)
{
    using CE = TOKEN::ConditionalExpression;

    if(std::holds_alternative<CE::Slore>(ce->var))
    {
        auto &&s{std::get<CE::Slore>(ce->var)};
        if(!analyze(s.lore))
            return false;
    }
    else if(std::holds_alternative<CE::Slore_e_ce>(ce->var))
    {
        auto &&s{std::get<CE::Slore_e_ce>(ce->var)};
        if(!analyze(s.lore))
            return false;
        
        if(!analyze(s.e))
            return false;
        
        if(!analyze(s.ce))
            return false;
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::LogicalORExpression *lore)
{
    for(const auto &lande : lore->seq)
    {
        if(!analyze(lande))
            return false;
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::LogicalANDExpression *lande)
{
    for(const auto &iore : lande->seq)
    {
        if(!analyze(iore))
            return false;
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::InclusiveORExpression *iore)
{
    for(const auto &eore : iore->seq)
    {
        if(!analyze(eore))
            return false;
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::ExclusiveORExpression *eore)
{
    for(const auto &ande : eore->seq)
    {
        if(!analyze(ande))
            return false;
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::ANDExpression *ande)
{
    for(const auto &ee : ande->seq)
    {
        if(!analyze(ee))
            return false;
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::EqualityExpression *ee)
{
    using EE = TOKEN::EqualityExpression;

    for(const auto &v : ee->seq)
    {
        if(std::holds_alternative<EE::Sre>(v))
        {
            if(!analyze(std::get<EE::Sre>(v).re))
                return false;
        }
        else if(std::holds_alternative<EE::Se_re>(v))
        {
            if(!analyze(std::get<EE::Se_re>(v).re))
                return false;
        }
        else if(std::holds_alternative<EE::Sne_re>(v))
        {
            if(!analyze(std::get<EE::Sne_re>(v).re))
                return false;
        }
        else
            variantError("EqualityExpression");
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::RelationalExpression *re)
{
    using RE = TOKEN::RelationalExpression;

    for(const auto &v : re->seq)
    {
        if(std::holds_alternative<RE::Sse>(v))
        {
            if(!analyze(std::get<RE::Sse>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sl_se>(v))
        {
            if(!analyze(std::get<RE::Sl_se>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sg_se>(v))
        {
            if(!analyze(std::get<RE::Sg_se>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sle_se>(v))
        {
            if(!analyze(std::get<RE::Sle_se>(v).se))
                return false;
        }
        else if(std::holds_alternative<RE::Sge_se>(v))
        {
            if(!analyze(std::get<RE::Sge_se>(v).se))
                return false;
        }
        else
            variantError("RelationalExpression");
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::ShiftExpression *se)
{
    using SE = TOKEN::ShiftExpression;

    for(const auto &v : se->seq)
    {
        if(std::holds_alternative<SE::Sae>(v))
        {
            if(!analyze(std::get<SE::Sae>(v).ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sl_ae>(v))
        {
            if(!analyze(std::get<SE::Sl_ae>(v).ae))
                return false;
        }
        else if(std::holds_alternative<SE::Sr_ae>(v))
        {
            if(!analyze(std::get<SE::Sr_ae>(v).ae))
                return false;
        }
        else
            variantError("ShiftExpression");
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::AdditiveExpression *ae)
{
    using AE = TOKEN::AdditiveExpression;

    for(const auto &v : ae->seq)
    {
        if(std::holds_alternative<AE::Sme>(v))
        {
            if(!analyze(std::get<AE::Sme>(v).me))
                return false;
        }
        else if(std::holds_alternative<AE::Sa_me>(v))
        {
            if(!analyze(std::get<AE::Sa_me>(v).me))
                return false;
        }
        else if(std::holds_alternative<AE::Ss_me>(v))
        {
            if(!analyze(std::get<AE::Ss_me>(v).me))
                return false;
        }
        else
            variantError("AdditiveExpression");
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::MultiplicativeExpression *me)
{
    using ME = TOKEN::MultiplicativeExpression;

    for(const auto &v : me->seq)
    {
        if(std::holds_alternative<ME::Sce>(v))
        {
            if(!analyze(std::get<ME::Sce>(v).ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sm_ce>(v))
        {
            if(!analyze(std::get<ME::Sm_ce>(v).ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sd_ce>(v))
        {
            if(!analyze(std::get<ME::Sd_ce>(v).ce))
                return false;
        }
        else if(std::holds_alternative<ME::Sr_ce>(v))
        {
            if(!analyze(std::get<ME::Sr_ce>(v).ce))
                return false;
        }
        else
            variantError("MultiplicativeExpression");
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::CastExpression *ce)
{
    using CE = TOKEN::CastExpression;

    if(std::holds_alternative<CE::Sue>(ce->var))
    {
        const auto& s{std::get<CE::Sue>(ce->var)};
        if(!analyze(s.ue))
            return false;
    }
    else if(std::holds_alternative<CE::Stn_ce>(ce->var))
    {
        const auto& s{std::get<CE::Stn_ce>(ce->var)};
        if(!analyzeType(s.tn))
            return false;
        
        if(!analyze(s.ce))
            return false;
    }
    else
        variantError("CastExpression");
    
    return true;
}

bool Analyzer::analyze(const TOKEN::UnaryExpression *ue)
{
    using UE = TOKEN::UnaryExpression;

    if(std::holds_alternative<UE::Spe>(ue->var))
    {
        const auto &s{std::get<UE::Spe>(ue->var)};
        if(!analyze(s.pe))
            return false;
    }
    else if(std::holds_alternative<UE::Si_ue>(ue->var))
    {
        const auto &s{std::get<UE::Si_ue>(ue->var)};
        if(!analyze(s.ue))
            return false;
    }
    else if(std::holds_alternative<UE::Sd_ue>(ue->var))
    {
        const auto &s{std::get<UE::Sd_ue>(ue->var)};
        if(!analyze(s.ue))
            return false;
    }
    else if(std::holds_alternative<UE::Suo_ce>(ue->var))
    {
        const auto &s{std::get<UE::Suo_ce>(ue->var)};
        if(!analyze(s.ce))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_ue>(ue->var))
    {
        const auto &s{std::get<UE::Ss_ue>(ue->var)};
        if(!analyze(s.ue))
            return false;
    }
    else if(std::holds_alternative<UE::Ss_tn>(ue->var))
    {
        const auto &s{std::get<UE::Ss_tn>(ue->var)};
        if(!analyzeType(s.tn))
            return false;
    }
    else if(std::holds_alternative<UE::Sa_tn>(ue->var))
    {
        const auto &s{std::get<UE::Sa_tn>(ue->var)};
        if(!analyzeType(s.tn))
            return false;
    }
    else
        variantError("UnaryExpression");
    
    return true;
}

bool Analyzer::analyze(const TOKEN::PostfixExpression *pe)
{
    using PE = TOKEN::PostfixExpression;

    for(const auto &v : pe->seq)
    {
        if(std::holds_alternative<PE::Spe>(v))
        {
            const auto &s{std::get<PE::Spe>(v)};
            if(!analyze(s.pe))
                return false;
        }
        else if(std::holds_alternative<PE::Se>(v))
        {
            const auto &s{std::get<PE::Se>(v)};
            if(!analyze(s.e))
                return false;
        }
        else if(std::holds_alternative<PE::Sael>(v))
        {
            const auto &s{std::get<PE::Sael>(v)};
            if(bool(s.ael))
            {
                for(const auto &ae : s.ael->seq)
                {
                    if(!analyze(ae))
                        return false;
                }
            }
        }
        else if(std::holds_alternative<PE::Sp_i>(v))
        {
            const auto &s{std::get<PE::Sp_i>(v)};

        }
        else if(std::holds_alternative<PE::Sa_i>(v))
        {
            const auto &s{std::get<PE::Sa_i>(v)};


        }
        else if(std::holds_alternative<PE::Si>(v))
        {
            const auto &s{std::get<PE::Si>(v)};


        }
        else if(std::holds_alternative<PE::Sd>(v))
        {
            const auto &s{std::get<PE::Sd>(v)};


        }
        else if(std::holds_alternative<PE::Stn_il>(v))
        {
            const auto &s{std::get<PE::Stn_il>(v)};
            if(!analyzeType(s.tn))
                return false;
            
            if(!analyze(s.il))
                return false;
        }
        else
            variantError("PostfixExpression");
    }

    return true;
}

bool Analyzer::analyze(const TOKEN::PrimaryExpression *pe)
{
    if(std::holds_alternative<TOKEN::Identifier*>(pe->var))
        ;
    else if(std::holds_alternative<TOKEN::Constant*>(pe->var))
        ;
    else if(std::holds_alternative<TOKEN::StringLiteral*>(pe->var))
        ;
    else if(std::holds_alternative<TOKEN::Expression*>(pe->var))
    {
        if(!analyze(std::get<TOKEN::Expression*>(pe->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::GenericSelection*>(pe->var))
    {
        if(!analyze(std::get<TOKEN::GenericSelection*>(pe->var)))
            return false;
    }
    else
        variantError("PrimaryExpression");
    
    return true;
}

bool Analyzer::analyze(const TOKEN::GenericSelection *gs)
{
    using GA = TOKEN::GenericAssociation;

    if(!analyze(gs->ae))
        return false;
    
    for(const auto &ga : gs->gal->seq)
    {
        if(std::holds_alternative<GA::Stn_ae>(ga->var))
        {
            const auto &s{std::get<GA::Stn_ae>(ga->var)};
            if(!analyzeType(s.tn))
                return false;
            
            if(!analyze(s.ae))
                return false;
        }
        else if(std::holds_alternative<GA::Sae>(ga->var))
        {
            const auto &s{std::get<GA::Sae>(ga->var)};
            if(!analyze(s.ae))
                return false;
        }
        else
            variantError("GenericSelection");
    }
    
    return true;
}

bool Analyzer::flag(Analyzer::FlagTag tag, bool b)
{
    bool old{flag(tag)};
    mFlags.set(static_cast<std::size_t>(tag), b);
    return old;
}

bool Analyzer::flag(Analyzer::FlagTag tag) const
{
    return mFlags.test(static_cast<std::size_t>(tag));
}

void Analyzer::variantError(const char *className) const
{
    throw std::runtime_error(className);
}

bool Analyzer::differentTypeError(const std::string &identifier) const
{
    std::cerr << "Analyzer error:\n"
        "    what: different type that the previously declared identifier.\n"
        "    name: " << identifier
        << std::endl;
    return false;
}

bool Analyzer::redefinedError(const std::string &identifier) const
{
    std::cerr << "Analyzer error:\n"
        "    what: redefined function.\n"
        "    name: " << identifier
        << std::endl;
    return false;
}

bool Analyzer::notSupportedError(const std::string &message) const
{
    std::cerr << "Analyzer error:\n"
        "    what: below function is not supported.\n"
        "    func: " << message
        << std::endl;
    return false;
}