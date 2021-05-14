#include <iostream>

#include "scope.hpp"
#include "analyzer.hpp"

const Analyzer::BaseTypeMap Analyzer::BASE_TYPE_MAP
    {{ResultTypeTag::VOID
        , {{BaseTypeTag::VOID}}}
        , {ResultTypeTag::CHAR
            , {{BaseTypeTag::CHAR}}}
        , {ResultTypeTag::S_CHAR
            , {{BaseTypeTag::SIGNED
                , BaseTypeTag::CHAR}}}
        , {ResultTypeTag::U_CHAR
            , {{BaseTypeTag::UNSIGNED
                , {BaseTypeTag::CHAR}}}}
        , {ResultTypeTag::S_SHORT
            , {{BaseTypeTag::SHORT}
                , {BaseTypeTag::SIGNED
                    , BaseTypeTag::SHORT}
                , {BaseTypeTag::SHORT
                    , BaseTypeTag::INT}
                , {BaseTypeTag::SIGNED
                    , BaseTypeTag::SHORT
                    , BaseTypeTag::INT}}}
        , {ResultTypeTag::U_SHORT
            , {{BaseTypeTag::UNSIGNED
                , BaseTypeTag::SHORT}
                , {BaseTypeTag::UNSIGNED
                    , BaseTypeTag::SHORT
                    , BaseTypeTag::INT}}}
        , {ResultTypeTag::S_INT
            , {{BaseTypeTag::INT}
                , {BaseTypeTag::SIGNED}
                , {BaseTypeTag::SIGNED
                    , BaseTypeTag::INT}}}
        , {ResultTypeTag::U_INT
            , {{BaseTypeTag::UNSIGNED}
                , {BaseTypeTag::UNSIGNED
                    , BaseTypeTag::INT}}}
        , {ResultTypeTag::S_LONG
            , {{BaseTypeTag::LONG}
                , {BaseTypeTag::SIGNED
                    , BaseTypeTag::LONG}
                , {BaseTypeTag::LONG
                    , BaseTypeTag::INT}
                , {BaseTypeTag::SIGNED
                    , BaseTypeTag::LONG
                    , BaseTypeTag::INT}}}
        , {ResultTypeTag::U_LONG
            , {{BaseTypeTag::UNSIGNED
                , BaseTypeTag::LONG}
                , {BaseTypeTag::UNSIGNED
                    , BaseTypeTag::LONG
                    , BaseTypeTag::INT}}}
        , {ResultTypeTag::S_LONG_LONG
            , {{BaseTypeTag::LONG
                , BaseTypeTag::LONG}
                , {BaseTypeTag::SIGNED
                    , BaseTypeTag::LONG
                    , BaseTypeTag::LONG}
                , {BaseTypeTag::LONG
                    , BaseTypeTag::LONG
                    , BaseTypeTag::INT}
                , {BaseTypeTag::SIGNED
                    , BaseTypeTag::LONG
                    , BaseTypeTag::LONG
                    , BaseTypeTag::INT}}}
        , {ResultTypeTag::U_LONG_LONG
            , {{BaseTypeTag::UNSIGNED
                , BaseTypeTag::LONG
                , BaseTypeTag::LONG}
                , {BaseTypeTag::UNSIGNED
                    , BaseTypeTag::LONG
                    , BaseTypeTag::LONG
                    , BaseTypeTag::INT}}}
        , {ResultTypeTag::FLOAT
            , {{BaseTypeTag::FLOAT}}}
        , {ResultTypeTag::DOUBLE
            , {{BaseTypeTag::DOUBLE}}}
        , {ResultTypeTag::LONG_DOUBLE
            , {{BaseTypeTag::LONG
                , BaseTypeTag::DOUBLE}}}
        , {ResultTypeTag::BOOL
            , {{BaseTypeTag::BOOL}}}
        , {ResultTypeTag::FLOAT_COMPLEX
            , {{BaseTypeTag::FLOAT
                , BaseTypeTag::COMPLEX}}}
        , {ResultTypeTag::DOUBLE_COMPLEX
            , {{BaseTypeTag::DOUBLE
                , BaseTypeTag::COMPLEX}}}
        , {ResultTypeTag::LONG_DOUBLE_COMPLEX
            , {{BaseTypeTag::LONG
                , BaseTypeTag::DOUBLE
                , BaseTypeTag::COMPLEX}}}};

Analyzer::Analyzer()
    : mFilename{}
    , mTranslationUnit{nullptr}
    , mFlags{}
    , mScope{nullptr}
{
}

Analyzer::~Analyzer()
{
}

bool Analyzer::execute(const std::string &filename
    , TOKEN::TranslationUnit *tu)
{
    mFilename = filename;
    mTranslationUnit = tu;

    if(!tu)
        return true;

    if(!analyze(tu))
        return false;
    
    return true;
}

bool Analyzer::finalize()
{
    delete mTranslationUnit;
    delete mScope;

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

bool Analyzer::analyze(TOKEN::FunctionDefinition *fd)
{
    using Id = TOKEN::Identifier;

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
        auto &&pair{mScope->addIdentifier(id
            , SCOPE::Scope::NamespaceTag::OTHER
            , SCOPE::Scope::ScopeTag::FILE)};
        ID_MAP.emplace(id->id()
            , id);
        
        auto &&identifier{getIdentifier(fd->d)};
        deleteIdentifierElement(identifier);
        identifier->var.emplace<Id::Id>(pair->first->id(), pair->second);
    }
    else
    {
        auto &&funcPtr{std::dynamic_pointer_cast<IDENTIFIER::Function>(idPtr->first)};
        
        if(!funcPtr)
            return differentTypeError(name);

        if(funcPtr->isDefined())
            return redefinedError(name);

        if(!TYPE::equalTo(funcPtr->type(), type))
            return differentTypeError(name);
        
        funcPtr->isDefined(true);
        funcPtr->storageClass(storageClassSpec);
        funcPtr->functionSpecifiers(functionSpec);

        auto &&identifier{getIdentifier(fd->d)};
        deleteIdentifierElement(identifier);
        identifier->var.emplace<Id::Id>(idPtr->first->id(), idPtr->second);
    }

    if(!analyze(fd->cs
        , fd->scopeId))
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

                    auto &&pair{mScope->addIdentifier(id
                        , SCOPE::Scope::NamespaceTag::OTHER)};
                    ID_MAP.emplace(id->id()
                        , id);

                    auto &&i{getIdentifier(declarator)};
                    deleteIdentifierElement(i);
                    i->var.emplace<TOKEN::Identifier::Id>(pair->first->id(), pair->second);
                }
                else
                {
                    if(auto &&tPtr{std::dynamic_pointer_cast<IDENTIFIER::Typedef>(idPtr->first)};
                        bool(tPtr))
                    {
                        if(!storageClass.flags.test(static_cast<std::size_t>(IDENTIFIER::StorageClass::Tag::TYPEDEF)))
                            return differentTypeError(identifier);
                        
                        if(!TYPE::equalTo(tPtr->type(), type))
                            return differentTypeError(identifier);
                    }
                    else if(auto &&oPtr{std::dynamic_pointer_cast<IDENTIFIER::Object>(idPtr->first)};
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
                    else if(auto &&fPtr{std::dynamic_pointer_cast<IDENTIFIER::Function>(idPtr->first)};
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
                    
                    auto &&i{getIdentifier(declarator)};
                    deleteIdentifierElement(i);
                    i->var.emplace<TOKEN::Identifier::Id>(idPtr->first->id(), idPtr->second);
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

bool Analyzer::analyze(const TOKEN::CompoundStatement *cs
    , std::size_t &scopeId)
{
    if(flag(FlagTag::IS_CREATING_BLOCK))
        mScope = mScope->addChild(SCOPE::Scope::ScopeTag::BLOCK);
    
    scopeId = mScope->id();

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

bool Analyzer::analyze(TOKEN::Statement *s)
{
    if(std::holds_alternative<TOKEN::LabeledStatement*>(s->var))
    {
        s->scopeId = mScope->id();
        if(!analyze(std::get<TOKEN::LabeledStatement*>(s->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::CompoundStatement*>(s->var))
    {
        if(!analyze(std::get<TOKEN::CompoundStatement*>(s->var)
            , s->scopeId))
            return false;
    }
    else if(std::holds_alternative<TOKEN::ExpressionStatement*>(s->var))
    {
        s->scopeId = mScope->id();
        if(!analyze(std::get<TOKEN::ExpressionStatement*>(s->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::SelectionStatement*>(s->var))
    {
        s->scopeId = mScope->id();
        if(!analyze(std::get<TOKEN::SelectionStatement*>(s->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::IterationStatement*>(s->var))
    {
        s->scopeId = mScope->id();
        if(!analyze(std::get<TOKEN::IterationStatement*>(s->var)))
            return false;
    }
    else if(std::holds_alternative<TOKEN::JumpStatement*>(s->var))
    {
        s->scopeId = mScope->id();
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
            auto &&pair{mScope->addIdentifier(id
                , SCOPE::Scope::NamespaceTag::LABEL
                , SCOPE::Scope::ScopeTag::FUNCTION)};
            ID_MAP.emplace(id->id()
                , id);
            
            deleteIdentifierElement(s.i);
            s.i->var.emplace<TOKEN::Identifier::Id>(pair->first->id(), pair->second);
        }
        else
        {
            auto &&label{std::dynamic_pointer_cast<IDENTIFIER::Label>(iPtr->first)};
            if(!label)
                return differentTypeError(identifier);
            
            label->isDefined(true);

            deleteIdentifierElement(s.i);
            s.i->var.emplace<TOKEN::Identifier::Id>(iPtr->first->id(), iPtr->second);
        }

        if(!analyze(s.s))
            return false;
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

    mScope = mScope->addChild(SCOPE::Scope::ScopeTag::BLOCK);

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
    
    mScope = mScope->getParent();

    return true;
}

bool Analyzer::analyze(const TOKEN::IterationStatement *is)
{
    using IS = TOKEN::IterationStatement;

    mScope = mScope->addChild(SCOPE::Scope::ScopeTag::BLOCK);

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
    
    mScope = mScope->getParent();

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
            
            auto &&pair{mScope->addIdentifier(id
                , SCOPE::Scope::NamespaceTag::LABEL
                , SCOPE::Scope::ScopeTag::FUNCTION)};
            ID_MAP.emplace(id->id()
                , id);

            deleteIdentifierElement(s.i);
            s.i->var.emplace<TOKEN::Identifier::Id>(pair->first->id(), pair->second);
        }
        else
        {
            deleteIdentifierElement(s.i);
            s.i->var.emplace<TOKEN::Identifier::Id>(iPtr->first->id(), iPtr->second);
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
    {
        auto &&identifier{std::get<TOKEN::Identifier*>(pe->var)};
        auto &&str{TOKEN::str(identifier)};
        auto &&idPtr{mScope->getIdentifier(str
            , SCOPE::Scope::NamespaceTag::OTHER
            , false)};
        if(!idPtr)
            return notDeclarationError(str);

        deleteIdentifierElement(identifier);
        identifier->var.emplace<TOKEN::Identifier::Id>(idPtr->first->id(), idPtr->second);
    }
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

std::optional<std::tuple<IDENTIFIER::StorageClass
    , TYPE::Type
    , IDENTIFIER::FunctionSpecifiers
    , IDENTIFIER::Alignment>>
    Analyzer::analyzeAttributes(const TOKEN::DeclarationSpecifiers *ds)
{
    using namespace TOKEN;

    std::vector<const StorageClassSpecifier*> scsVec;
    std::vector<const TypeSpecifier*> tsVec;
    std::vector<const TypeQualifier*> tqVec;
    std::vector<const FunctionSpecifier*> fsVec;
    std::vector<const AlignmentSpecifier*> asVec;

    for(const auto &v : ds->seq)
    {
        if(std::holds_alternative<StorageClassSpecifier*>(v))
            scsVec.push_back(std::get<StorageClassSpecifier*>(v));
        else if(std::holds_alternative<TypeSpecifier*>(v))
            tsVec.push_back(std::get<TypeSpecifier*>(v));
        else if(std::holds_alternative<TypeQualifier*>(v))
            tqVec.push_back(std::get<TypeQualifier*>(v));
        else if(std::holds_alternative<FunctionSpecifier*>(v))
            fsVec.push_back(std::get<FunctionSpecifier*>(v));
        else if(std::holds_alternative<AlignmentSpecifier*>(v))
            asVec.push_back(std::get<AlignmentSpecifier*>(v));
    }

    auto &&scsOpt{analyzeStorageClassSpecifiers(scsVec)};
    auto &&tOpt{analyzeType(tsVec, tqVec)};
    auto &&fsOpt{analyzeFunctionSpecifiers(fsVec)};
    auto &&asOpt{analyzeAlignmentSpecifier(asVec)};

    if(!(scsOpt && tOpt && fsOpt && asOpt))
        return std::nullopt;
    
    return {std::make_tuple(std::move(*scsOpt)
        , std::move(*tOpt)
        , std::move(*fsOpt)
        , std::move(*asOpt))};
}

std::optional<IDENTIFIER::StorageClass>
    Analyzer::analyzeStorageClassSpecifiers(const std::vector<const TOKEN::StorageClassSpecifier*> &scsVec)
{
    using TTag = TOKEN::StorageClassSpecifier::Tag;
    using ITag = IDENTIFIER::StorageClass::Tag;
    
    static const std::unordered_map<TTag, ITag> tagMap{{TTag::TYPEDEF, ITag::TYPEDEF}
        , {TTag::EXTERN, ITag::EXTERN}
        , {TTag::STATIC, ITag::STATIC}
        , {TTag::THREAD_LOCAL, ITag::THREAD_LOCAL}
        , {TTag::AUTO, ITag::AUTO}
        , {TTag::REGISTER, ITag::REGISTER}};

    IDENTIFIER::StorageClass sc;
    
    for(const auto &scs : scsVec)
    {
        if(const auto &iter{tagMap.find(scs->tag)};
            iter != tagMap.end())
            sc.flags.set(static_cast<std::size_t>(iter->second));
        else 
            variantError("StorageClassSpecifier");
    }

    return {std::move(sc)};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const std::vector<const TOKEN::TypeSpecifier*> &tsVec
        , const std::vector<const TOKEN::TypeQualifier*> &tqVec)
{
    auto &&tOpt{analyzeType(tsVec)};
    auto &&qOpt{analyzeTypeQualifiers(tqVec)};

    if(!(tOpt && qOpt))
        return std::nullopt;

    auto &&result{analyzeType(*tOpt, *qOpt)};
    if(!result)
        return std::nullopt;
    
    return {std::move(result)};
}

std::optional<IDENTIFIER::FunctionSpecifiers>
    Analyzer::analyzeFunctionSpecifiers(const std::vector<const TOKEN::FunctionSpecifier*> &fsVec)
{
    using TTag = TOKEN::FunctionSpecifier::Tag;
    using ITag = IDENTIFIER::FunctionSpecifiers::Tag;

    static const std::unordered_map<TTag, ITag> tagMap{{TTag::INLINE, ITag::INLINE}
        , {TTag::NORETURN, ITag::NORETURN}};
    
    IDENTIFIER::FunctionSpecifiers fs;
    for(const auto &f : fsVec)
    {
        if(const auto &iter{tagMap.find(f->tag)};
            iter != tagMap.end())
            fs.flags.set(static_cast<std::size_t>(iter->second));
        else
            variantError("FunctionSpecifier");
    }

    return {std::move(fs)};
}

std::optional<IDENTIFIER::Alignment>
    Analyzer::analyzeAlignmentSpecifier(const std::vector<const TOKEN::AlignmentSpecifier*> &asVec)
{
    if(asVec.size() > 1)
    {
        invalidAttributeError("AlignmentSpecifier");
        return std::nullopt;
    }

    IDENTIFIER::Alignment alignment;

    if(!asVec.empty())
    {
        if(std::holds_alternative<TOKEN::TypeName*>(asVec.front()->var))
        {
            auto &&tOpt{analyzeType(std::get<TOKEN::TypeName*>(asVec.front()->var))};
            if(!tOpt)
                return std::nullopt;
            
            alignment.var.emplace<TYPE::Type>(std::move(*tOpt));
        }
        else if(std::holds_alternative<TOKEN::ConstantExpression*>(asVec.front()->var))
            alignment.var.emplace<std::shared_ptr<TOKEN::ConstantExpression>>(std::get<TOKEN::ConstantExpression*>(asVec.front()->var)->copy());
        else
            variantError("AlignmentSpecifier");
    }

    return {std::move(alignment)};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const std::vector<const TOKEN::TypeSpecifier*> &tsVec)
{
    using namespace TOKEN;
    using TTag = BaseTypeTag;

    std::bitset<5ull> notEmptyFlags;

    BaseTypeSet tSet;
    std::vector<const AtomicTypeSpecifier*> atsVec;
    std::vector<const StructOrUnionSpecifier*> sousVec;
    std::vector<const EnumSpecifier*> esVec;
    std::vector<const TypedefName*> tnVec;

    for(const auto &ts : tsVec)
    {
        if(std::holds_alternative<TTag>(ts->var))
        {
            tSet.insert(std::get<TTag>(ts->var));
            notEmptyFlags.set(0ull);
        }
        else if(std::holds_alternative<AtomicTypeSpecifier*>(ts->var))
        {
            atsVec.push_back(std::get<AtomicTypeSpecifier*>(ts->var));
            notEmptyFlags.set(1ull);
        }
        else if(std::holds_alternative<StructOrUnionSpecifier*>(ts->var))
        {
            sousVec.push_back(std::get<StructOrUnionSpecifier*>(ts->var));
            notEmptyFlags.set(2ull);
        }
        else if(std::holds_alternative<EnumSpecifier*>(ts->var))
        {
            esVec.push_back(std::get<EnumSpecifier*>(ts->var));
            notEmptyFlags.set(3ull);
        }
        else if(std::holds_alternative<TypedefName*>(ts->var))
        {
            tnVec.push_back(std::get<TypedefName*>(ts->var));
            notEmptyFlags.set(4ull);
        }
    }

    std::optional<TYPE::Type> tOpt;

    if(notEmptyFlags.count() == 1ull)
    {
        if(notEmptyFlags.test(0ull))
            tOpt = analyzeType(tSet);
        else if(notEmptyFlags.test(1ull))
            tOpt = analyzeType(atsVec);
        else if(notEmptyFlags.test(2ull))
            tOpt = analyzeType(sousVec);
        else if(notEmptyFlags.test(3ull))
            tOpt = analyzeType(esVec);
        else if(notEmptyFlags.test(4ull))
            tOpt = analyzeType(tnVec);
    }
    else
    {
        invalidTypeError("multiple type-specifier is specifierd.");
        return {std::nullopt};
    }

    return tOpt;
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const BaseTypeSet &set)
{
    TYPE::Type type;

    for(const auto &mapE : BASE_TYPE_MAP)
    {
        for(const auto &vecE : mapE.second)
        {
            if(vecE == set)
            {
                type.var.emplace<TYPE::Base>(TYPE::Base{mapE.first});
                break;
            }
        }
    }

    if(std::holds_alternative<std::monostate>(type.var))
    {
        invalidTypeError("fail to deduce tyoe from base-type-specifier");
        return {std::nullopt};
    }

    return {std::move(type)};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const std::vector<const TOKEN::AtomicTypeSpecifier*> &atsVec)
{
    if(atsVec.size() == 1ull)
    {
        invalidTypeError("multiple atomic-type-specifiers are given.");
        return {std::nullopt};
    }

    auto &&tOpt{analyzeType(atsVec.front()->tn)};
    if(!tOpt)
        return {std::nullopt};
    
    TYPE::Qualifiers quals;
    quals.flags.set(static_cast<std::size_t>(TYPE::Qualifiers::Tag::ATOMIC));

    tOpt = analyzeType(*tOpt, quals);
    if(!tOpt)
        return {std::nullopt};

    return tOpt;
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const std::vector<const TOKEN::StructOrUnionSpecifier*> &sousVec)
{
    using NTag = SCOPE::Scope::NamespaceTag;
    using Sous = TOKEN::StructOrUnionSpecifier;
    using Sou = TOKEN::StructOrUnion;
    
    auto isUnion{[](const Sou *sou)
        {return sou->tag == Sou::Tag::UNION;}};
    auto isMatchTag{[](const Sou *sou
        , IDENTIFIER::Tag::T t)
        {
            if((sou->tag == Sou::Tag::STRUCT
                && t == IDENTIFIER::Tag::T::STRUCT)
                || (sou->tag == Sou::Tag::UNION
                && t == IDENTIFIER::Tag::T::UNION))
                return true;
            else
                return false;
        }};
    auto define{[&](const TOKEN::StructDeclarationList *sdl
        , std::size_t id)
            -> std::optional<TYPE::Type>
        {
            if(!analyzeMember(sdl, id))
                return {std::nullopt};

            TYPE_MAP.find(id)->second->isDefined(true);
            return {TYPE::Type{TYPE::Struct{id}}};
        }};
    auto addTagInfo{[&](const std::string &tag
        , const Sou *sou
        , TOKEN::Identifier *identifier)
        {
            TYPE::StructInfo sInfo{tag, isUnion(sou)};
            IDENTIFIER::Tag tagIdent{tag
                , sInfo.id()
                , sInfo.isUnion 
                    ? IDENTIFIER::Tag::T::UNION
                    : IDENTIFIER::Tag::T::STRUCT};
            
            std::shared_ptr<IDENTIFIER::Identifier> tagIdentPtr{new IDENTIFIER::Tag{tagIdent}};
            auto &&pair{mScope->addIdentifier(tagIdentPtr, NTag::TAG)};
            ID_MAP.emplace(tagIdent.id(), tagIdentPtr);
            TYPE_MAP.emplace(sInfo.id(), new TYPE::StructInfo{sInfo});
            
            deleteIdentifierElement(identifier);
            identifier->var.emplace<TOKEN::Identifier::Id>(pair->first->id(), pair->second);

            return sInfo.id();
        }};

    if(sousVec.size() != 1ull)
    {
        invalidTypeError("multiple struct-or-union-type-specifiers are given.");
        return {std::nullopt};
    }

    if(std::holds_alternative<Sous::Ssou_i_sdl>(sousVec.front()->var))
    {
        auto &&s{std::get<Sous::Ssou_i_sdl>(sousVec.front()->var)};
        if(!s.i)
        {
            TYPE::StructInfo sInfo{{}, isUnion(s.sou)};
            TYPE_MAP.emplace(sInfo.id(), new TYPE::StructInfo{sInfo});

            return define(s.sdl, sInfo.id());
        }
        else
        {
            std::string tag{TOKEN::str(s.i)};
            auto &&identifier{mScope->getIdentifier(tag, NTag::TAG, true)};
            if(bool(identifier))
            {
                auto &&tagIdent{std::dynamic_pointer_cast<IDENTIFIER::Tag>(identifier->first)};
                if(!tagIdent
                    || !isMatchTag(s.sou, tagIdent->tag()))
                {
                    differentTypeError(tag);
                    return {std::nullopt};
                }

                auto &&iter{TYPE_MAP.find(tagIdent->typeId())};
                if(iter->second->isDefined())
                {
                    redefinedError(tag);
                    return {std::nullopt};
                }

                deleteIdentifierElement(s.i);
                s.i->var.emplace<TOKEN::Identifier::Id>(identifier->first->id(), identifier->second);

                return define(s.sdl, iter->first);
            }
            else
            {
                std::size_t id{addTagInfo(tag, s.sou, s.i)};

                return define(s.sdl, id);
            }
        }
    }
    else
    {
        auto &&s{std::get<Sous::Ssou_i>(sousVec.front()->var)};
        if(flag(FlagTag::IS_DECLARATION_OVER))
        {
            std::string tag{TOKEN::str(s.i)};
            auto &&identifier{mScope->getIdentifier(tag, NTag::TAG, true)};
            if(bool(identifier))
            {
                auto &&tagIdent{std::dynamic_pointer_cast<IDENTIFIER::Tag>(identifier->first)};
                if(!tagIdent
                    || !isMatchTag(s.sou, tagIdent->tag()))
                {
                    differentTypeError(tag);
                    return {std::nullopt};
                }

                deleteIdentifierElement(s.i);
                s.i->var.emplace<TOKEN::Identifier::Id>(identifier->first->id(), identifier->second);

                return TYPE::Type{TYPE::Struct{tagIdent->typeId()}};
            }
            else
            {
                std::size_t id{addTagInfo(tag, s.sou, s.i)};
                
                return TYPE::Type{TYPE::Struct{id}};
            }
        }
        else
        {
            std::string tag{TOKEN::str(s.i)};
            auto &&identifier{mScope->getIdentifier(tag, NTag::TAG, false)};
            if(!identifier)
            {
                std::size_t id{addTagInfo(tag, s.sou, s.i)};
                
                return TYPE::Type{TYPE::Struct{id}};
            }
            else
            {
                auto &&tagIdent{std::dynamic_pointer_cast<IDENTIFIER::Tag>(identifier->first)};
                if(!tagIdent
                    || !isMatchTag(s.sou, tagIdent->tag()))
                {
                    differentTypeError(tag);
                    return {std::nullopt};
                }

                return TYPE::Type{TYPE::Struct{tagIdent->typeId()}};
            }
        }
    }
}

bool Analyzer::analyzeMember(const TOKEN::StructDeclarationList *sdl
    , std::size_t typeId)
{
    using namespace TOKEN;

    auto &&addMemberInfo{[&](std::optional<std::pair<TYPE::Type, std::string>> opt
        , std::shared_ptr<TYPE::StructInfo> &sInfo
        , TOKEN::Identifier *identifier)
        {
            if(!opt)
                return false;

            const auto &[type, ident]{*opt};
            sInfo->members.emplace_back(type, ident);
            std::shared_ptr<IDENTIFIER::Identifier> member{new IDENTIFIER::Member{ident, sInfo->id()}};
            
            ID_MAP.emplace(member->id(), member);
            auto &&pair{mScope->addIdentifier(member, SCOPE::Scope::NamespaceTag::MEMBER)};
            if(!pair)
                return false;

            deleteIdentifierElement(identifier);
            identifier->var.emplace<TOKEN::Identifier::Id>(pair->first->id(), pair->second);

            return true;
        }};

    auto &&sInfo{std::dynamic_pointer_cast<TYPE::StructInfo>(TYPE_MAP.find(typeId)->second)};
    if(!sInfo)
        return differentTypeError(std::to_string(typeId));

    for(const auto &sd : sdl->seq)
    {
        if(std::holds_alternative<StructDeclaration::Ssad>(sd->var))
            continue;
        
        auto &&s{std::get<StructDeclaration::Ssql_sdl>(sd->var)};

        bool oldIsFunction{flag(FlagTag::IS_FUNCTION, false)};
        bool oldIsDeclarationOver{flag(FlagTag::IS_DECLARATION_OVER, !s.sdl)};

        auto &&tOpt{analyzeType(s.sql)};
        if(!tOpt)
            return false;
        
        if(!s.sdl)
            sInfo->members.emplace_back(*tOpt, std::string{});
        else
        {
            for(const auto &sdr: s.sdl->seq)
            {
                if(std::holds_alternative<StructDeclarator::Sd>(sdr->var))
                {   
                    auto &&s{std::get<StructDeclarator::Sd>(sdr->var)};
                    auto &&opt{analyzeTypeAndIdentifier(s.d, *tOpt)};
                    if(!addMemberInfo(opt, sInfo, getIdentifier(s.d)))
                        return false;
                }
                else
                {
                    auto &&s{std::get<StructDeclarator::Sd_ce>(sdr->var)};
                    if(!s.d)
                    {
                        auto &&to{analyzeType(s.ce, *tOpt)};
                        if(!to)
                            return false;
                        
                        sInfo->members.emplace_back(*to, std::string{});
                    }
                    else
                    {
                        auto &&opt{analyzeTypeAndIdentifier(s.d, *tOpt)};

                        if(opt)
                            return false;
                        
                        auto &&[type, ident]{*opt};
                        auto &&to{analyzeType(s.ce, type)};
                        if(!to)
                            return false;
                        
                        if(!addMemberInfo(std::pair<TYPE::Type, std::string>{*to, ident}
                            , sInfo
                            , getIdentifier(s.d)))
                            return false;
                    }
                }
            }            
        }

        flag(FlagTag::IS_FUNCTION, oldIsFunction);
        flag(FlagTag::IS_DECLARATION_OVER, oldIsDeclarationOver);
    }

    return true;
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TOKEN::SpecifierQualifierList *sql)
{
    using namespace TOKEN;

    std::vector<const TypeSpecifier*> tsVec;
    std::vector<const TypeQualifier*> tqVec;

    for(const auto &v : sql->seq)
    {
        if(std::holds_alternative<TypeSpecifier*>(v))
            tsVec.push_back(std::get<TypeSpecifier*>(v));
        else if(std::holds_alternative<TypeQualifier*>(v))
            tqVec.push_back(std::get<TypeQualifier*>(v));
    }

    return analyzeType(tsVec, tqVec);
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TOKEN::ConstantExpression *ce
        , const TYPE::Type &baseType)
{
    std::shared_ptr<TOKEN::ConstantExpression> ptr{ce->copy()};
    TYPE::Bitfield bitfield{baseType, std::move(ptr)};
    return {TYPE::Type{std::move(bitfield)}};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const std::vector<const TOKEN::EnumSpecifier*> &esVec)
{
    using ES = TOKEN::EnumSpecifier;

    auto &&define{[&](const TOKEN::EnumeratorList *el
        , std::size_t id)
            -> std::optional<TYPE::Type>
        {
            if(!analyzeMember(el, id))
                return {std::nullopt};
            
            TYPE_MAP.find(id)->second->isDefined(true);
            return {TYPE::Type{TYPE::Enum{id}}};
        }};

    if(esVec.size() != 1ull)
    {
        invalidTypeError("EnumSpecifier");
        return {std::nullopt};
    }

    const auto &var{esVec.front()->var};

    if(std::holds_alternative<ES::Si_el>(var))
    {
        const auto &s{std::get<ES::Si_el>(var)};

        if(bool(s.i))
        {
            std::string tag{TOKEN::str(s.i)};
            auto &&identifier{mScope->getIdentifier(tag
                , SCOPE::Scope::NamespaceTag::TAG
                , true)};
            
            if(bool(identifier))
            {
                auto &&tagIdent{std::dynamic_pointer_cast<IDENTIFIER::Tag>(identifier->first)};
                if(!tagIdent
                    || tagIdent->tag() != IDENTIFIER::Tag::T::ENUM)
                {
                    differentTypeError(tag);
                    return {std::nullopt};
                }

                auto &&iter{TYPE_MAP.find(tagIdent->typeId())};
                if(iter->second->isDefined())
                {
                    redefinedError(tag);
                    return {std::nullopt};
                }

                deleteIdentifierElement(s.i);
                s.i->var.emplace<TOKEN::Identifier::Id>(identifier->first->id(), identifier->second);

                return define(s.el, iter->first);
            }
            else
            {
                TYPE::EnumInfo eInfo{tag};
                
                std::shared_ptr<IDENTIFIER::Identifier> tagIdentPtr{new IDENTIFIER::Tag{tag, eInfo.id(), IDENTIFIER::Tag::T::ENUM}};
                auto &&pair{mScope->addIdentifier(tagIdentPtr
                    , SCOPE::Scope::NamespaceTag::TAG)};
                ID_MAP.emplace(tagIdentPtr->id()
                    , tagIdentPtr);
                TYPE_MAP.emplace(eInfo.id()
                    , new TYPE::EnumInfo{eInfo});

                deleteIdentifierElement(s.i);
                s.i->var.emplace<TOKEN::Identifier::Id>(pair->first->id(), pair->second);

                return {TYPE::Type{TYPE::Enum{eInfo.id()}}};
            }
        }
        else
        {
            TYPE::EnumInfo eInfo{{}};
            TYPE_MAP.emplace(eInfo.id()
                , new TYPE::EnumInfo{eInfo});
            
            return define(s.el, eInfo.id());
        }
    }
    else if(std::holds_alternative<ES::Si>(var))
    {
        const auto &s{std::get<ES::Si>(var)};

        auto &&tag{TOKEN::str(s.i)};
        
        auto &&iPtr{mScope->getIdentifier(tag
            , SCOPE::Scope::NamespaceTag::TAG
            , false)};
        
        if(!iPtr)
        {
            notDeclarationError(tag);
            return {std::nullopt};
        }

        auto &&ePtr{std::dynamic_pointer_cast<IDENTIFIER::Tag>(iPtr->first)};
        if(!ePtr)
        {
            differentTypeError(tag);
            return {std::nullopt};
        }

        deleteIdentifierElement(s.i);
        s.i->var.emplace<TOKEN::Identifier::Id>(iPtr->first->id(), iPtr->second);

        return {TYPE::Type{TYPE::Enum{ePtr->typeId()}}};
    }
}

bool Analyzer::analyzeMember(const TOKEN::EnumeratorList *el
    , std::size_t typeId)
{
    using E = TOKEN::Enumerator;

    auto &&iter{TYPE_MAP.find(typeId)};
    auto &&enumInfo{std::dynamic_pointer_cast<TYPE::EnumInfo>(iter->second)};

    for(const auto &e : el->seq)
    {
        TOKEN::Identifier *identifier;
        std::shared_ptr<TOKEN::ConstantExpression> ce;

        if(std::holds_alternative<E::Sec>(e->var))
        {
            const auto &s{std::get<E::Sec>(e->var)};
            identifier = s.ec->i;
        }
        else if(std::holds_alternative<E::Sec_ce>(e->var))
        {
            const auto &s{std::get<E::Sec_ce>(e->var)};
            identifier = s.ec->i;
            if(!analyze(s.ce))
                return false;

            ce.reset(s.ce->copy());
        }
        else
            variantError("Enumerator");

        if(bool(mScope->getIdentifier(TOKEN::str(identifier)
            , SCOPE::Scope::NamespaceTag::OTHER
            , true)))
            return redefinedError(TOKEN::str(identifier));

        std::shared_ptr<IDENTIFIER::Identifier> identPtr{new IDENTIFIER::Enum{TOKEN::str(identifier), typeId}};
        auto &&pair{mScope->addIdentifier(identPtr
            , SCOPE::Scope::NamespaceTag::OTHER)};
        ID_MAP.emplace(identPtr->id()
            , identPtr);
        
        enumInfo->members.emplace_back(TOKEN::str(identifier)
            , std::move(ce));
        
        deleteIdentifierElement(identifier);
        identifier->var.emplace<TOKEN::Identifier::Id>(pair->first->id(), pair->second);
    }

    return true;
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const std::vector<const TOKEN::TypedefName*> &tnVec)
{
    if(tnVec.size() != 1ull)
    {
        invalidTypeError("multiple typedef-name are given.");
        return {std::nullopt};
    }

    auto &&str{TOKEN::str(tnVec.front()->i)};
    auto &&identifier{mScope->getIdentifier(str
        , SCOPE::Scope::NamespaceTag::OTHER
        , false)};
    
    if(!identifier)
    {
        notDeclarationError(str);
        return {std::nullopt};
    }

    if(identifier->first->derivedTag() != IDENTIFIER::Identifier::DerivedTag::TYPEDEF)
    {
        differentTypeError(str);
        return {std::nullopt};
    }

    const auto &typedefPtr{std::dynamic_pointer_cast<IDENTIFIER::Typedef>(identifier->first)};

    deleteIdentifierElement(tnVec.front()->i);
    tnVec.front()->i->var.emplace<TOKEN::Identifier::Id>(identifier->first->id(), identifier->second);

    return typedefPtr->type();
}

std::optional<TYPE::Qualifiers>
    Analyzer::analyzeTypeQualifiers(const std::vector<const TOKEN::TypeQualifier*> &tqVec)
{
    using TokenTag = TOKEN::TypeQualifier::Tag;
    using TypeTag = TYPE::Qualifiers::Tag;

    static const std::unordered_map<TokenTag, TypeTag> tagMap
        {{TokenTag::CONST, TypeTag::CONST}
            , {TokenTag::RESTRICT, TypeTag::RESTRICT}
            , {TokenTag::VOLATILE, TypeTag::VOLATILE}
            , {TokenTag::ATOMIC, TypeTag::ATOMIC}};
    
    TYPE::Qualifiers qualifiers;

    for(const auto &tq : tqVec)
    {
        if(const auto &iter{tagMap.find(tq->tag)};
            iter != tagMap.end())
            qualifiers.flags.set(static_cast<std::size_t>(iter->second));
        else
            variantError("TypeQualifier");
    }

    return {std::move(qualifiers)};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TYPE::Type &baseType
        , const TYPE::Qualifiers &qualifiers)
{
    TYPE::Type resultType{baseType};

    if(std::holds_alternative<TYPE::Base>(resultType.var))
        std::get<TYPE::Base>(resultType.var).quals.flags |= qualifiers.flags;
    else if(std::holds_alternative<TYPE::Array>(resultType.var))
        std::get<TYPE::Array>(resultType.var).quals.flags |= qualifiers.flags;
    else if(std::holds_alternative<TYPE::Pointer>(resultType.var))
        std::get<TYPE::Pointer>(resultType.var).quals.flags |= qualifiers.flags;
    else if(std::holds_alternative<TYPE::Enum>(resultType.var))
        std::get<TYPE::Enum>(resultType.var).quals.flags |= qualifiers.flags;
    else if(std::holds_alternative<TYPE::Struct>(resultType.var))
        std::get<TYPE::Struct>(resultType.var).quals.flags |= qualifiers.flags;
    else if(std::holds_alternative<TYPE::Typedef>(resultType.var))
        std::get<TYPE::Typedef>(resultType.var).quals.flags |= qualifiers.flags;
    else if(std::holds_alternative<TYPE::Function>(resultType.var)
        || std::holds_alternative<TYPE::Bitfield>(resultType.var)
        || std::holds_alternative<TYPE::Lvalue>(resultType.var)
        || std::holds_alternative<TYPE::Initializer>(resultType.var))
    {
        invalidAttributeError("type-qualifiers");
        return {std::nullopt};
    }
    else
        variantError("TYPE::Type");
    
    return {std::move(resultType)};
}

std::optional<std::pair<TYPE::Type
    , std::string>>
    Analyzer::analyzeTypeAndIdentifier(const TOKEN::Declarator *declarator
        , const TYPE::Type &baseType)
{
    using DD = TOKEN::DirectDeclarator;

    std::pair<TYPE::Type
        , std::string> result;

    if(bool(declarator->p))
    {
        auto &&typeOpt{analyzeType(declarator->p, baseType)};
        if(!typeOpt)
            return {std::nullopt};
        
        result.first = std::move(*typeOpt);
    }
    else
        result.first = baseType;
    
    for(auto &&iter{declarator->dd->seq.crbegin()};
        iter != declarator->dd->seq.crend();
        iter++)
    {
        if(std::holds_alternative<DD::Si>(*iter))
        {
            const auto &s{std::get<DD::Si>(*iter)};
            result.second = TOKEN::str(s.i);
        }
        else if(std::holds_alternative<DD::Sd>(*iter))
        {
            const auto &s{std::get<DD::Sd>(*iter)};
            
            auto &&pairOpt{analyzeTypeAndIdentifier(s.d, result.first)};
            if(!pairOpt)
                return {std::nullopt};

            result = std::move(*pairOpt);
        }
        else if(std::holds_alternative<DD::Stql_ae>(*iter))
        {
            const auto &s{std::get<DD::Stql_ae>(*iter)};
            
            auto &&typeOpt{analyzeType(s.tql, s.ae, s.hasStatic, false, result.first)};
            if(!typeOpt)
                return {std::nullopt};
        
            result.first = std::move(*typeOpt);
        }
        else if(std::holds_alternative<DD::Stql>(*iter))
        {
            const auto &s{std::get<DD::Stql>(*iter)};

            auto &&typeOpt{analyzeType(s.tql, nullptr, false, true, result.first)};
            if(!typeOpt)
                return {std::nullopt};

            result.first = std::move(*typeOpt);
        }
        else if(std::holds_alternative<DD::Sptl>(*iter))
        {
            const auto &s{std::get<DD::Sptl>(*iter)};

            auto &&typeOpt{analyzeType(s.ptl, result.first)};
            if(!typeOpt)
                return {std::nullopt};

            result.first = std::move(*typeOpt);
        }
        else if(std::holds_alternative<DD::Sil>(*iter))
        {
            const auto &s{std::get<DD::Sil>(*iter)};

            auto &&typeOpt{analyzeType(s.il, result.first)};
            if(!typeOpt)
                return {std::nullopt};

            result.first = std::move(*typeOpt);
        }
        else
            variantError("DirectDeclarator");
    }

    return {std::move(result)};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TOKEN::Pointer *pointer
        , const TYPE::Type &baseType)
{
    using P = TOKEN::Pointer;

    TYPE::Type resultType{TYPE::Pointer{baseType}};

    const TOKEN::TypeQualifierList *tql{nullptr};
    const TOKEN::Pointer *p{nullptr};

    if(std::holds_alternative<P::Stql>(pointer->var))
        tql = std::get<P::Stql>(pointer->var).tql;
    else if(std::holds_alternative<P::Stql_p>(pointer->var))
    {
        const auto &s{std::get<P::Stql_p>(pointer->var)};
        tql = s.tql;
        p = s.p;
    }
    else
        variantError("Pointer");

    if(bool(tql))
    {
        auto &&qualsOpt{analyzeTypeQualifiers(tql)};
        if(!qualsOpt)
            return {std::nullopt};
        
        std::get<TYPE::Pointer>(resultType.var).quals = std::move(*qualsOpt);
    }

    if(bool(p))
    {
        auto &&typeOpt{analyzeType(p, resultType)};
        if(!typeOpt)
            return {std::nullopt};
        
        resultType = std::move(*typeOpt);
    }
    
    return {std::move(resultType)};
}

std::optional<TYPE::Qualifiers>
    Analyzer::analyzeTypeQualifiers(const TOKEN::TypeQualifierList *tql)
{
    return analyzeTypeQualifiers(std::vector<const TOKEN::TypeQualifier*>{tql->seq.cbegin(), tql->seq.cend()});
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TOKEN::TypeQualifierList *tql
        , const TOKEN::AssignmentExpression *ae
        , bool hasStatic
        , bool isVariable
        , const TYPE::Type &baseType)
{
    TYPE::Array array{baseType};

    if(bool(tql))
    {
        auto &&qualsOpt{analyzeTypeQualifiers(tql)};
        if(!qualsOpt)
            return {std::nullopt};
        
        array.quals = std::move(*qualsOpt);
    }

    if(bool(ae))
    {
        if(!analyze(ae))
            return {std::nullopt};

        array.exp.reset(ae->copy());
    }

    array.hasStatic = hasStatic;
    array.isVariable = isVariable;

    return {TYPE::Type{std::move(array)}};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TOKEN::ParameterTypeList *ptl
        , const TYPE::Type &baseType)
{
    TYPE::Function function{baseType};

    for(const auto &pd : ptl->pl->seq)
    {
        auto &&typeOpt{analyzeType(pd)};
        if(!typeOpt)
            return {std::nullopt};
        
        function.paramTypes.push_back(std::move(*typeOpt));
    }

    function.isVariable = ptl->isValiable;

    return {TYPE::Type{std::move(function)}};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TOKEN::IdentifierList *il
        , const TYPE::Type &baseType)
{
    if(bool(il))
    {
        notSupportedError("IdentifierList");
        return {std::nullopt};
    }

    return {TYPE::Type{TYPE::Function{baseType}}};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TOKEN::ParameterDeclaration *pd)
{
    using namespace TOKEN;
    using PD = ParameterDeclaration;

    const DeclarationSpecifiers *ds{nullptr};
    const Declarator *d{nullptr};
    const AbstractDeclarator *ad{nullptr};

    if(std::holds_alternative<PD::Sds_d>(pd->var))
    {
        const auto &s{std::get<PD::Sds_d>(pd->var)};
        ds = s.ds;
        d = s.d;
    }
    else if(std::holds_alternative<PD::Sds_ad>(pd->var))
    {
        const auto &s{std::get<PD::Sds_ad>(pd->var)};
        ds = s.ds;
        ad = s.ad;
    }
    else
        variantError("ParameterDeclaration");

    auto &&attrsOpt{analyzeAttributes(ds)};
    if(!attrsOpt)
        return {std::nullopt};
    
    auto &&[storageClass
        , resultType
        , functionSpecifiers
        , alignment]{*attrsOpt};
    
    if(bool(d))
    {
        auto &&pairOpt{analyzeTypeAndIdentifier(d, resultType)};
        if(!pairOpt)
            return {std::nullopt};
        
        if(bool(mScope->getIdentifier(pairOpt->second
            , SCOPE::Scope::NamespaceTag::OTHER
            , true)))
        {
            redefinedError(pairOpt->second);
            return {std::nullopt};
        }

        std::shared_ptr<IDENTIFIER::Identifier> identifier;

        if(std::holds_alternative<TYPE::Function>(pairOpt->first.var))
        {
             identifier.reset(new IDENTIFIER::Function{pairOpt->second
                , pairOpt->first
                , storageClass
                , functionSpecifiers
                , false});
        }
        else if(!std::holds_alternative<std::monostate>(pairOpt->first.var))
        {
            identifier.reset(new IDENTIFIER::Object{pairOpt->second
                , pairOpt->first
                , storageClass
                , alignment
                , true});
        }
        else
            variantError("TYPE::Type");

        auto &&pair{mScope->addIdentifier(identifier
            , SCOPE::Scope::NamespaceTag::OTHER)};
        ID_MAP.emplace(identifier->id()
            , identifier);

        auto &&i{getIdentifier(d)};
        deleteIdentifierElement(i);
        i->var.emplace<TOKEN::Identifier::Id>(pair->first->id(), pair->second);

        resultType = pairOpt->first;
    }
    else if(bool(ad))
    {
        auto &&typeOpt{analyzeType(ad, resultType)};
        if(!typeOpt)
            return {std::nullopt};
        
        resultType = std::move(*typeOpt);
    }

    return {std::move(resultType)};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TOKEN::AbstractDeclarator *ad
        , const TYPE::Type &baseType)
{
    using namespace TOKEN;
    using AD = AbstractDeclarator;
    using DAD = DirectAbstractDeclarator;

    const Pointer *p{nullptr};
    const DAD *dad{nullptr};

    TYPE::Type resultType;

    if(std::holds_alternative<AD::Sp>(ad->var))
    {
        const auto &s{std::get<AD::Sp>(ad->var)};
        p = s.p;
    }
    else if(std::holds_alternative<AD::Sp_dad>(ad->var))
    {
        const auto &s{std::get<AD::Sp_dad>(ad->var)};
        if(bool(s.p))
            p = s.p;
        dad = s.dad;
    }
    else
        variantError("AbstractDeclarator");
    
    if(bool(p))
    {
        auto &&typeOpt{analyzeType(p, baseType)};
        if(!typeOpt)
            return {std::nullopt};
        
        resultType = std::move(*typeOpt);
    }
    else
        resultType = baseType;
    
    if(bool(dad))
    {
        for(auto &&iter{dad->seq.crbegin()};
            iter != dad->seq.crend();
            iter++)
        {
            if(std::holds_alternative<DAD::Sad>(*iter))
            {
                auto &&s{std::get<DAD::Sad>(*iter)};
                auto &&typeOpt{analyzeType(s.ad, resultType)};
                if(!typeOpt)
                    return {std::nullopt};

                resultType = std::move(*typeOpt);
            }
            else if(std::holds_alternative<DAD::Stql_ae>(*iter))
            {
                auto &&s{std::get<DAD::Stql_ae>(*iter)};
                auto &&typeOpt{analyzeType(s.tql, s.ae, s.hasStatic, false, resultType)};
                if(!typeOpt)
                    return {std::nullopt};
                
                resultType = std::move(*typeOpt);
            }
            else if(std::holds_alternative<DAD::Sp>(*iter))
            {
                auto &&s{std::get<DAD::Sp>(*iter)};
                auto &&typeOpt{analyzeType(nullptr, nullptr, false, true, resultType)};
                if(!typeOpt)
                    return {std::nullopt};

                resultType = std::move(*typeOpt);
            }
            else if(std::holds_alternative<DAD::Sptl>(*iter))
            {
                auto &&s{std::get<DAD::Sptl>(*iter)};
                if(bool(s.ptl))
                {
                    auto &&typeOpt{analyzeType(s.ptl, resultType)};
                    if(!typeOpt)
                        return {std::nullopt};
                    
                    resultType = std::move(*typeOpt);
                }
                else
                {
                    auto &&typeOpt{analyzeType(static_cast<IdentifierList*>(nullptr), resultType)};
                    if(!typeOpt)
                        return {std::nullopt};

                    resultType = std::move(*typeOpt);
                }
            }
            else
                variantError("DirectAbstractDeclarator");
        }
    }

    return {std::move(resultType)};
}

std::optional<TYPE::Type>
    Analyzer::analyzeType(const TOKEN::TypeName *typeName)
{
    TYPE::Type resultType;

    auto &&typeOpt{analyzeType(typeName->sql)};
    if(!typeOpt)
        return {std::nullopt};

    if(bool(typeName->ad))
    {
        auto &&tOpt{analyzeType(typeName->ad, *typeOpt)};
        if(!tOpt)
            return {std::nullopt};
        
        resultType = std::move(*tOpt);
    }
    else
        resultType = std::move(*typeOpt);
    
    return {std::move(resultType)};
}

TOKEN::Identifier *Analyzer::getIdentifier(const TOKEN::Declarator *declarator)
{
    using DD = TOKEN::DirectDeclarator;

    TOKEN::Identifier *identifier{nullptr};

    const auto &var{declarator->dd->seq.front()};
    if(std::holds_alternative<DD::Si>(var))
        identifier = std::get<DD::Si>(var).i;
    else if(std::holds_alternative<DD::Sd>(var))
        identifier = getIdentifier(std::get<DD::Sd>(var).d);
    else
        variantError("DirectDeclarator");
    
    return identifier;
}

void Analyzer::deleteIdentifierElement(TOKEN::Identifier *identifier)
{
    using namespace TOKEN;
    using Id = Identifier;

    if(std::holds_alternative<Id::Seq>(identifier->var))
    {
        for(auto &&e : std::get<Id::Seq>(identifier->var))
        {
            if(std::holds_alternative<IdentifierNondigit*>(e))
                delete std::get<IdentifierNondigit*>(e);
            else if(std::holds_alternative<Digit*>(e))
                delete std::get<Digit*>(e);
        }
    }
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

void Analyzer::variantError(const std::string &className) const
{
    throw std::runtime_error(className.c_str());
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

bool Analyzer::invalidAttributeError(const std::string &message) const
{
    std::cerr << "Analyzer error:\n"
        "    what: invalid attribute.\n"
        "    attr: " << message
        << std::endl;
    return false;
}

bool Analyzer::invalidTypeError(const std::string &message) const
{
    std::cerr << "Analyzer error:\n"
        "    what: invalid type.\n"
        "    --: " << message
        << std::endl;
    return false;
}

bool Analyzer::notDeclarationError(const std::string &identifier) const
{
    std::cerr << "Analyzer error:\n"
        "    what: declaration is not found.\n"
        "    id: " << identifier
        << std::endl;
    return false;
}