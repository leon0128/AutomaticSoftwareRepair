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
                        if(storageClass.flags.test(static_cast<std::size_t>(IDENTIFIER::StorageClass::Tag::TYPEDEF)))
                            return differentTypeError(identifier);

                        if(!TYPE::equalTo(oPtr->type(), type))
                            return differentTypeError(identifier);
                        
                        if(oPtr->isDefined() && initializer)
                            return redefinedError(identifier);
                        
                        oPtr->storageClass(storageClass);
                        if(bool(initializer))
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

    if(std::holds_alternative<LS::>)
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