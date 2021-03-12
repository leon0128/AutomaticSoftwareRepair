#include <iostream>

#include "scope.hpp"
#include "identifier.hpp"
#include "type.hpp"
#include "token.hpp"
#include "analyzer.hpp"

Analyzer::Analyzer(const std::string &filename
    , TOKEN::TranslationUnit *translationUnit)
    : mFilename(filename)
    , mTranslationUnit(mTranslationUnit != nullptr ? translationUnit->copy() : nullptr)
    , mIdMap()
    , mNextId(0)
    , mScope(new SCOPE::Scope(nullptr, SCOPE::Scope::ScopeTag::FILE))
{
}

Analyzer::~Analyzer()
{
    delete mScope;
}

bool Analyzer::execute()
{
    if(mTranslationUnit == nullptr)
        return true;
    
    if(!analyze(mTranslationUnit))
        return false;

    return true;
}

bool Analyzer::analyze(TOKEN::TranslationUnit *tu)
{
    for(auto &&ed : tu->seq)
    {
        if(std::holds_alternative<TOKEN::Declaration*>(ed->var))
        {
            if(!analyze(std::get<TOKEN::Declaration*>(ed->var)))
                break;
        }
        else if(std::holds_alternative<TOKEN::FunctionDefinition*>(ed->var))
        {
            if(!analyze(std::get<TOKEN::FunctionDefinition*>(ed->var)))
                break;
        }
    }

    return false;
}

std::tuple<IDENTIFIER::Storage
    , TYPE::Type*
    , IDENTIFIER::FunctionSpecifier
    , IDENTIFIER::Alignment*> Analyzer::deduceAttributes(const TOKEN::DeclarationSpecifiers *ds
    , bool isEnd)
{
    std::vector<TOKEN::StorageClassSpecifier*> scsseq;
    std::vector<TOKEN::TypeSpecifier*> tsseq;
    std::vector<TOKEN::TypeQualifier*> tqseq;
    std::vector<TOKEN::FunctionSpecifier*> fsseq;
    std::vector<TOKEN::AlignmentSpecifier*> asseq;

    for(auto &&v : ds->seq)
    {
        if(std::holds_alternative<TOKEN::StorageClassSpecifier*>(v))
            scsseq.push_back(std::get<TOKEN::StorageClassSpecifier*>(v));
        else if(std::holds_alternative<TOKEN::TypeSpecifier*>(v))
            tsseq.push_back(std::get<TOKEN::TypeSpecifier*>(v));
        else if(std::holds_alternative<TOKEN::TypeQualifier*>(v))
            tqseq.push_back(std::get<TOKEN::TypeQualifier*>(v));
        else if(std::holds_alternative<TOKEN::FunctionSpecifier*>(v))
            fsseq.push_back(std::get<TOKEN::FunctionSpecifier*>(v));
        else if(std::holds_alternative<TOKEN::AlignmentSpecifier*>(v))
            asseq.push_back(std::get<TOKEN::AlignmentSpecifier*>(v));
    }

    IDENTIFIER::Storage s = deduceStorage(scsseq);
    TYPE::Type *t = deduceType(tqseq, tsseq, isEnd);
    IDENTIFIER::FunctionSpecifier fs = deduceFunctionSpecifier(fsseq);
    IDENTIFIER::Alignment *a = deduceAlignment(asseq);

    if(t == nullptr || a == nullptr)
    {
        delete t;
        delete a;
        t = nullptr;
        a = nullptr;
    }

    return {s, t, fs, a};
}

TYPE::Type *Analyzer::deduceType(const std::vector<TOKEN::TypeQualifier*> &tqseq
    , const std::vector<TOKEN::TypeSpecifier*> &tsseq
    , bool isEnd)
{
    TYPE::Type *type = nullptr;    

    std::vector<TOKEN::TypeSpecifier::Tag> tagseq;
    for(auto &&ts : tsseq)
    {
        if(std::holds_alternative<TOKEN::TypeSpecifier::Tag>(ts->var))
            tagseq.push_back(std::get<TOKEN::TypeSpecifier::Tag>(ts->var));
        else if(tagseq.size() == 1)
        {
            if(std::holds_alternative<TOKEN::AtomicTypeSpecifier*>(ts->var))
                type = deduceType(std::get<TOKEN::AtomicTypeSpecifier*>(ts->var));
            else if(std::holds_alternative<TOKEN::StructOrUnionSpecifier*>(ts->var))
                type = deduceType(std::get<TOKEN::StructOrUnionSpecifier*>(ts->var), isEnd);
            else if(std::holds_alternative<TOKEN::EnumSpecifier*>(ts->var))
                type = deduceType(std::get<TOKEN::EnumSpecifier*>(ts->var));
            else if(std::holds_alternative<TOKEN::TypedefName*>(ts->var))
                type = deduceType(std::get<TOKEN::TypedefName*>(ts->var));
        }
        else
        {
            std::cerr << "analyzer error:\n"
                "    what: failed to deduce type.\n"
                << std::flush;
            return nullptr;
        }
    }

    if(!tagseq.empty())
        type = deduceType(tagseq);
    
    if(!addQualifier(type, deduceQualifiers(tqseq)))
    {
        delete type;
        return nullptr;
    }

    return type;
}

TYPE::Type *Analyzer::deduceType(const std::vector<TOKEN::TypeSpecifier::Tag> &tsvec)
{
    std::multiset<TOKEN::TypeSpecifier::Tag> set(tsvec.begin(), tsvec.end());
    for(auto &&mapi : TYPE_MAP)
    {
        for(auto &&s : mapi.second)
        {
            if(set == s)
                return new TYPE::Type(new TYPE::Base(mapi.first));
        }
    }

    return nullptr;
}

TYPE::Type *Analyzer::deduceType(const TOKEN::AtomicTypeSpecifier *ats)
{
    TYPE::Type *type = deduceType(ats->tn);
    if(type == nullptr)
        return nullptr;
    
    TYPE::Qualifier atomic;
    atomic.flags.set(static_cast<std::size_t>(TYPE::Qualifier::Tag::ATOMIC));
    if(!addQualifier(type, atomic))
    {
        delete type;
        return nullptr;
    }

    return type;
}

TYPE::Type *Analyzer::deduceType(const TOKEN::StructOrUnionSpecifier *sous
    , bool isEnd)
{
    if(std::holds_alternative<TOKEN::StructOrUnionSpecifier::Ssou_i_sdl>(sous->var))
    {
        auto &&s = std::get<TOKEN::StructOrUnionSpecifier::Ssou_i_sdl>(sous->var);
        IDENTIFIER::Identifier *identifier = nullptr;
        TYPE::IdInfo *idInfo = nullptr;

        if(s.i != nullptr)
        {
            if((identifier = mScope->getIdentifier(SCOPE::Scope::NamespaceTag::TAG, TOKEN::str(s.i), true)) == nullptr)
            {
                identifier 
                    = new IDENTIFIER::Identifier(TOKEN::str(s.i), new IDENTIFIER::Tag(mNextId++
                        , s.sou->tag == TOKEN::StructOrUnion::Tag::STRUCT
                            ? IDENTIFIER::Tag::T::STRUCT
                            : IDENTIFIER::Tag::T::UNION
                        , false));
                mScope->addIdentifier(mScope->scopeTag()
                    , SCOPE::Scope::NamespaceTag::TAG
                    , TOKEN::str(s.i)
                    , identifier);
            }
            else
            {
                if(IDENTIFIER::Tag *t = nullptr;
                    std::holds_alternative<IDENTIFIER::Tag*>(identifier->var)
                        && (t = std::get<IDENTIFIER::Tag*>(identifier->var), true)
                        && !t->isDefined
                        && ((t->tag == IDENTIFIER::Tag::T::STRUCT
                            && s.sou->tag == TOKEN::StructOrUnion::Tag::STRUCT)
                            || (t->tag == IDENTIFIER::Tag::T::UNION
                                && s.sou->tag == TOKEN::StructOrUnion::Tag::UNION)))
                    ;
                else
                {
                    std::cerr << "analyzer error:\n"
                        "    what: duplicate define of struct-or-union or use different kind of tag between previous declaration..\n"
                        "    tag: " << TOKEN::str(s.i)
                        << std::endl;
                    return nullptr;
                }
            }
        }

        if(identifier == nullptr)
        {
            idInfo = new TYPE::IdInfo(mNextId++
                , ""
                , false
                , TYPE::StructInfo(s.sou->tag == TOKEN::StructOrUnion::Tag::UNION));
            mIdMap.emplace(idInfo->id, idInfo);
        }
        else
        {
            auto iter = mIdMap.find(std::get<IDENTIFIER::Tag*>(identifier->var)->id);
            if(iter == mIdMap.end())
            {
                idInfo = new TYPE::IdInfo(mNextId++
                    , identifier->name
                    , false
                    , TYPE::StructInfo(s.sou->tag == TOKEN::StructOrUnion::Tag::UNION));
                mIdMap.emplace(idInfo->id, idInfo);
            }
            else
                idInfo = iter->second;
        }

        if(addMemberInfo(idInfo->id, s.sdl))
        {
            if(identifier != nullptr)
                std::get<IDENTIFIER::Tag*>(identifier->var)->isDefined = true;
            idInfo->isDefined = true;
        
            return new TYPE::Type(new TYPE::Struct(idInfo->id));
        }
    }
    else if(std::holds_alternative<TOKEN::StructOrUnionSpecifier::Ssou_i>(sous->var))
    {
        auto &&s = std::get<TOKEN::StructOrUnionSpecifier::Ssou_i>(sous->var);
        if(isEnd)
        {
            IDENTIFIER::Identifier *identifier
                = mScope->getIdentifier(SCOPE::Scope::NamespaceTag::TAG
                    , TOKEN::str(s.i)
                    , true);
            if(IDENTIFIER::Tag *t = nullptr;
                identifier != nullptr
                    && (t = std::get<IDENTIFIER::Tag*>(identifier->var), true)
                    && ((t->tag == IDENTIFIER::Tag::T::STRUCT
                        && s.sou->tag == TOKEN::StructOrUnion::Tag::STRUCT)
                        || (t->tag == IDENTIFIER::Tag::T::UNION
                            && s.sou->tag == TOKEN::StructOrUnion::Tag::UNION)))
                return new TYPE::Type(new TYPE::Struct(t->id));
            else if(identifier == nullptr)
            {
                identifier
                    = new IDENTIFIER::Identifier(TOKEN::str(s.i)
                        , new IDENTIFIER::Tag(mNextId++
                            , s.sou->tag == TOKEN::StructOrUnion::Tag::STRUCT
                                ? IDENTIFIER::Tag::T::STRUCT
                                : IDENTIFIER::Tag::T::UNION
                            , false));
                mScope->addIdentifier(mScope->scopeTag()
                    , SCOPE::Scope::NamespaceTag::TAG
                    , identifier->name
                    , identifier);
                mIdMap.emplace(std::get<IDENTIFIER::Tag*>(identifier->var)->id
                    , new TYPE::IdInfo(std::get<IDENTIFIER::Tag*>(identifier->var)->id
                        , identifier->name
                        , false
                        , TYPE::StructInfo(s.sou->tag == TOKEN::StructOrUnion::Tag::UNION)));
                
                return new TYPE::Type(new TYPE::Struct(std::get<IDENTIFIER::Tag*>(identifier->var)->id));
            }
            else
            {
                std::cerr << "analyzer error:\n"
                    "    what: use different kind of tag between previous declaration.\n"
                    "    tag: " << identifier->name
                    << std::endl;
            }
        }
        else
        {
            IDENTIFIER::Identifier *identifier
                = mScope->getIdentifier(SCOPE::Scope::NamespaceTag::TAG
                    , TOKEN::str(s.i));
            if(IDENTIFIER::Tag *t = nullptr;
                identifier != nullptr
                    && (t = std::get<IDENTIFIER::Tag*>(identifier->var), true)
                    && ((t->tag == IDENTIFIER::Tag::T::STRUCT
                        && s.sou->tag == TOKEN::StructOrUnion::Tag::STRUCT)
                        || (t->tag == IDENTIFIER::Tag::T::UNION
                            && s.sou->tag == TOKEN::StructOrUnion::Tag::UNION)))
                return new TYPE::Type(new TYPE::Struct(t->id));
            else if(identifier == nullptr)
            {
                identifier
                    = new IDENTIFIER::Identifier(TOKEN::str(s.i)
                        , new IDENTIFIER::Tag(mNextId++
                            , s.sou->tag == TOKEN::StructOrUnion::Tag::STRUCT
                                ? IDENTIFIER::Tag::T::STRUCT
                                : IDENTIFIER::Tag::T::UNION
                            , false));
                mScope->addIdentifier(mScope->scopeTag()
                    , SCOPE::Scope::NamespaceTag::TAG
                    , identifier->name
                    , identifier);
                mIdMap.emplace(std::get<IDENTIFIER::Tag*>(identifier->var)->id
                    , new TYPE::IdInfo(std::get<IDENTIFIER::Tag*>(identifier->var)->id
                        , identifier->name
                        , false
                        , TYPE::StructInfo(s.sou->tag == TOKEN::StructOrUnion::Tag::UNION)));

                return new TYPE::Type(new TYPE::Struct(std::get<IDENTIFIER::Tag*>(identifier->var)->id));
            }
            else
            {
                std::cerr << "analyzer error:\n"
                    "    what: use different kind of tag between previous declaration.\n"
                    "    tag: " << identifier->name
                    << std::endl;
            }
        }
    }

    return nullptr;
}

TYPE::Type *Analyzer::deduceType(const TOKEN::EnumSpecifier *es)
{
    if(std::holds_alternative<TOKEN::EnumSpecifier::Si_el>(es->var))
    {
        std::size_t id = mNextId++;

        auto &&s = std::get<TOKEN::EnumSpecifier::Si_el>(es->var);
        IDENTIFIER::Identifier *identifier = nullptr;
        if(s.i != nullptr)
        {
            if(mScope->getIdentifier(SCOPE::Scope::NamespaceTag::TAG
                , TOKEN::str(s.i)
                , true) != nullptr)
            {
                std::cerr << "analyzer error:\n"
                    "    what: duplicate tag declaration.\n"
                    "    tag: " << TOKEN::str(s.i)
                    << std::endl;
                return nullptr;
            }

            identifier
                = new IDENTIFIER::Identifier(TOKEN::str(s.i)
                    , new IDENTIFIER::Tag(id
                        , IDENTIFIER::Tag::T::ENUM
                        , false));
            mScope->addIdentifier(mScope->scopeTag()
                , SCOPE::Scope::NamespaceTag::TAG
                , identifier->name
                , identifier);
        }

        mIdMap.emplace(id,
            new TYPE::IdInfo(id
                , identifier != nullptr
                    ? identifier->name
                    : ""
                , false
                , TYPE::EnumInfo()));

        for(auto &&e : s.el->seq)
        {
            const TOKEN::EnumerationConstant *ec = nullptr;
            TOKEN::ConstantExpression *ce = nullptr;
            if(std::holds_alternative<TOKEN::Enumerator::Sec>(e->var))
                ec = std::get<TOKEN::Enumerator::Sec>(e->var).ec;
            else if(std::holds_alternative<TOKEN::Enumerator::Sec_ce>(e->var))
            {
                ec = std::get<TOKEN::Enumerator::Sec_ce>(e->var).ec;
                ce = std::get<TOKEN::Enumerator::Sec_ce>(e->var).ce->copy();
            }

            std::get<TYPE::EnumInfo>(mIdMap[id]->var).members.emplace_back(TOKEN::str(ec->i), ce);
            IDENTIFIER::Identifier *i
                = new IDENTIFIER::Identifier(TOKEN::str(ec->i)
                    , new IDENTIFIER::Enumeration(id));
            if(!mScope->addIdentifier(mScope->scopeTag()
                , SCOPE::Scope::NamespaceTag::OTHER
                , i->name
                , i))
            {
                std::cerr << "analyzer error:\n"
                    "    what: duplicate variable declaration.\n"
                    "    name: " << i->name
                    << std::endl;
                delete i;
                return nullptr;
            }
        }

        mIdMap[id]->isDefined = true;
        if(identifier != nullptr)
            std::get<IDENTIFIER::Tag*>(identifier->var)->isDefined = true;
        
        return new TYPE::Type(new TYPE::Enumeration(id));
    }
    else if(std::holds_alternative<TOKEN::EnumSpecifier::Si>(es->var))
    {
        auto &&s = std::get<TOKEN::EnumSpecifier::Si>(es->var);
        
        IDENTIFIER::Identifier *identifier
            = mScope->getIdentifier(SCOPE::Scope::NamespaceTag::TAG
                , TOKEN::str(s.i));
        if(identifier == nullptr
            || std::get<IDENTIFIER::Tag*>(identifier->var)->tag != IDENTIFIER::Tag::T::ENUM)
        {
            std::cerr << "analyzer error:\n"
                "    what: enum tag does not exists.\n"
                "    tag: " << TOKEN::str(s.i)
                << std::endl;
            return nullptr;
        }

        return new TYPE::Type(new TYPE::Enumeration(std::get<IDENTIFIER::Tag*>(identifier->var)->id));
    }

    return nullptr;
}

TYPE::Type *Analyzer::deduceType(const TOKEN::TypedefName *tn)
{
    IDENTIFIER::Identifier *identifier
        = mScope->getIdentifier(SCOPE::Scope::NamespaceTag::OTHER
            , TOKEN::str(tn->i));
    if(identifier == nullptr
        || std::holds_alternative<IDENTIFIER::Typedef*>(identifier->var))
    {
        std::cerr << "analyzer error:\n"
            "    what: typdef name is not declared.\n"
            "    name: " << TOKEN::str(tn->i)
            << std::endl;
        return nullptr;
    }

    return std::get<IDENTIFIER::Typedef*>(identifier->var)->type->copy();
}

TYPE::Type *Analyzer::deduceType(const TOKEN::TypeName *tn)
{
    TYPE::Type *base = deduceType(tn->sql, false);
    if(base == nullptr)
        return nullptr;

    if(tn->ad == nullptr)
        return base;
    else
    {
        TYPE::Type *type = deduceType(base, tn->ad);
        delete base;
        
        return type;
    }
}

TYPE::Type *Analyzer::deduceType(const TOKEN::SpecifierQualifierList *sql
    , bool isEnd)
{
    std::vector<TOKEN::TypeSpecifier*> tsseq;
    std::vector<TOKEN::TypeQualifier*> tqseq;
    
    for(auto &&v : sql->seq)
    {
        if(std::holds_alternative<TOKEN::TypeSpecifier*>(v))
            tsseq.push_back(std::get<TOKEN::TypeSpecifier*>(v));
        else if(std::holds_alternative<TOKEN::TypeQualifier*>(v))
            tqseq.push_back(std::get<TOKEN::TypeQualifier*>(v));
    }

    return deduceType(tqseq, tsseq, isEnd);
}

TYPE::Type *Analyzer::deduceType(const TOKEN::ParameterDeclaration *pd)
{
    TYPE::Type *type = nullptr;

    if(std::holds_alternative<TOKEN::ParameterDeclaration::Sds_d>(pd->var))
    {
        auto &&s = std::get<TOKEN::ParameterDeclaration::Sds_d>(pd->var);
        auto &&[storage, tmp, fs, align] = deduceAttributes(s.ds, false);
        type = tmp;
        
        if(type == nullptr)
            return nullptr;

        auto &&[t, i] = deduceTypeAndIdentifier(type, s.d, true);
        if(t == nullptr)
        {
            delete type;
            delete align;
            return nullptr;
        }

        IDENTIFIER::Identifier *identifier
            = new IDENTIFIER::Identifier(i
                , new IDENTIFIER::Object(t->copy()
                    , storage
                    , align
                    , true));
        if(!mScope->addIdentifier(mScope->scopeTag()
            , SCOPE::Scope::NamespaceTag::OTHER
            , i
            , identifier))
        {
            delete identifier;
            delete t;
            delete type;
            delete align;
            return nullptr;
        }

        type = t;
    }
    else if(std::holds_alternative<TOKEN::ParameterDeclaration::Sds_ad>(pd->var))
    {
        auto &&s = std::get<TOKEN::ParameterDeclaration::Sds_ad>(pd->var);
        auto &&[storage, tmp, fs, align] = deduceAttributes(s.ds, false);
        delete align;
        type = tmp;
        if(type == nullptr)
            return nullptr;

        if(s.ad != nullptr)
        {
            TYPE::Type *tmp = type;
            type = deduceType(type, s.ad);
            if(type == nullptr)
            {
                delete tmp;
                return nullptr;
            }
        }
    }

    return type;
}

TYPE::Type *Analyzer::deduceType(TYPE::Type *base
    , const TOKEN::Pointer *p)
{
    if(std::holds_alternative<TOKEN::Pointer::Stql>(p->var))
    {
        return new TYPE::Type(new TYPE::Pointer(base->copy()
            , std::get<TOKEN::Pointer::Stql>(p->var).tql != nullptr
                ? deduceQualifiers(std::get<TOKEN::Pointer::Stql>(p->var).tql->seq)
                : TYPE::Qualifier()));
    }
    else if(std::holds_alternative<TOKEN::Pointer::Stql_p>(p->var))
    {
        TYPE::Type *type = new TYPE::Type(new TYPE::Pointer(base->copy()
            , std::get<TOKEN::Pointer::Stql_p>(p->var).tql != nullptr
                ? deduceQualifiers(std::get<TOKEN::Pointer::Stql_p>(p->var).tql->seq)
                : TYPE::Qualifier()));
        TYPE::Type *t = deduceType(type, std::get<TOKEN::Pointer::Stql_p>(p->var).p);
        delete type;
        return t;
    }

    return nullptr;
}

TYPE::Qualifier Analyzer::deduceQualifiers(const std::vector<TOKEN::TypeQualifier*> &tqseq)
{
    TYPE::Qualifier ret;
    for(auto &&q : tqseq)
    {
        switch(q->tag)
        {
            case(TOKEN::TypeQualifier::Tag::CONST):
                ret.flags.set(static_cast<std::size_t>(TYPE::Qualifier::Tag::CONST));
                break;
            case(TOKEN::TypeQualifier::Tag::RESTRICT):
                ret.flags.set(static_cast<std::size_t>(TYPE::Qualifier::Tag::RESTRICT));
                break;
            case(TOKEN::TypeQualifier::Tag::VOLATILE):
                ret.flags.set(static_cast<std::size_t>(TYPE::Qualifier::Tag::VOLATILE));
                break;
            case(TOKEN::TypeQualifier::Tag::ATOMIC):
                ret.flags.set(static_cast<std::size_t>(TYPE::Qualifier::Tag::ATOMIC));
                break;
            
            default:;
        }
    }

    return ret;
}

IDENTIFIER::Storage Analyzer::deduceStorage(const std::vector<TOKEN::StorageClassSpecifier*> &seq)
{
    IDENTIFIER::Storage ret = IDENTIFIER::Storage(std::bitset<6>());

    for(auto &&scs : seq)
    {
        switch(scs->tag)
        {
            case(TOKEN::StorageClassSpecifier::Tag::TYPEDEF):
                ret.flags.set(static_cast<std::size_t>(IDENTIFIER::Storage::Tag::TYPEDEF));
                break;
            case(TOKEN::StorageClassSpecifier::Tag::EXTERN):
                ret.flags.set(static_cast<std::size_t>(IDENTIFIER::Storage::Tag::EXTERN));
                break;
            case(TOKEN::StorageClassSpecifier::Tag::STATIC):
                ret.flags.set(static_cast<std::size_t>(IDENTIFIER::Storage::Tag::STATIC));
                break;
            case(TOKEN::StorageClassSpecifier::Tag::THREAD_LOCAL):
                ret.flags.set(static_cast<std::size_t>(IDENTIFIER::Storage::Tag::THREAD_LOCAL));
                break;
            case(TOKEN::StorageClassSpecifier::Tag::AUTO):
                ret.flags.set(static_cast<std::size_t>(IDENTIFIER::Storage::Tag::AUTO));
                break;
            case(TOKEN::StorageClassSpecifier::Tag::REGISTER):
                ret.flags.set(static_cast<std::size_t>(IDENTIFIER::Storage::Tag::REGISTER));
                break;
            
            default:;
        }
    }

    return ret;
}

IDENTIFIER::FunctionSpecifier Analyzer::deduceFunctionSpecifier(const std::vector<TOKEN::FunctionSpecifier*> &seq)
{
    IDENTIFIER::FunctionSpecifier ret = IDENTIFIER::FunctionSpecifier(std::bitset<2>());
    
    for(auto &&fs : seq)
    {
        switch(fs->tag)
        {
            case(TOKEN::FunctionSpecifier::Tag::INLINE):
                ret.flags.set(static_cast<std::size_t>(IDENTIFIER::FunctionSpecifier::Tag::INLINE));
                break;
            case(TOKEN::FunctionSpecifier::Tag::NORETURN):
                ret.flags.set(static_cast<std::size_t>(IDENTIFIER::FunctionSpecifier::Tag::NORETURN));
                break;
            
            default:;
        }
    }

    return ret;
}

IDENTIFIER::Alignment *Analyzer::deduceAlignment(const std::vector<TOKEN::AlignmentSpecifier*> &seq)
{
    if(seq.size() > 2)
    {
        std::cerr << "analyzer error:\n"
            "    what: failed to get alignment information.\n"
            << std::flush;
        return nullptr;
    }

    IDENTIFIER::Alignment *ret = new IDENTIFIER::Alignment();

    if(!seq.empty())
    {
        if(std::holds_alternative<TOKEN::TypeName*>(seq.front()->var))
        {
            TYPE::Type *type = deduceType(std::get<TOKEN::TypeName*>(seq.front()->var));
            if(type != nullptr)
                ret->var.emplace<TYPE::Type*>(type);
            else
            {
                delete ret;
                return nullptr;
            }
        }
        else if(std::holds_alternative<TOKEN::ConstantExpression*>(seq.front()->var))
            ret->var.emplace<TOKEN::ConstantExpression*>(std::get<TOKEN::ConstantExpression*>(seq.front()->var)->copy());
    }

    return ret;
}

bool Analyzer::addArguments(const TOKEN::IdentifierList *il)
{
    for(auto &&i : il->seq)
    {
        IDENTIFIER::Identifier *identifier
            = new IDENTIFIER::Identifier(TOKEN::str(i)
                , new IDENTIFIER::Object(nullptr
                    , IDENTIFIER::Storage(std::bitset<6>())
                    , new IDENTIFIER::Alignment()
                    , true));
        
        if(!mScope->addIdentifier(SCOPE::Scope::ScopeTag::BLOCK
            , SCOPE::Scope::NamespaceTag::OTHER
            , identifier->name
            , identifier))
        {
            std::cerr << "analyzer error:\n"
                "    what: failed to add function-arguments.\n"
                "    arg: " << identifier->name
                << std::endl;
            delete identifier;
            return false;
        }
    }

    return true;
}

bool Analyzer::addQualifier(TYPE::Type *type
    , const TYPE::Qualifier &qualifier) const
{
    if(std::holds_alternative<TYPE::Base*>(type->var))
        std::get<TYPE::Base*>(type->var)->qualifier.flags |= qualifier.flags;
    else if(std::holds_alternative<TYPE::Array*>(type->var))
        std::get<TYPE::Array*>(type->var)->qualifier.flags |= qualifier.flags;
    else if(std::holds_alternative<TYPE::Pointer*>(type->var))
        std::get<TYPE::Pointer*>(type->var)->qualifier.flags |= qualifier.flags;
    else if(std::holds_alternative<TYPE::Enumeration*>(type->var))
        std::get<TYPE::Enumeration*>(type->var)->qualifier.flags |= qualifier.flags;
    else if(std::holds_alternative<TYPE::Struct*>(type->var))
        std::get<TYPE::Struct*>(type->var)->qualifier.flags |= qualifier.flags;
    else if(std::holds_alternative<TYPE::Typedef*>(type->var))
        std::get<TYPE::Typedef*>(type->var)->qualifier.flags |= qualifier.flags;
    else
    {
        std::cerr << "Analyzer error:\n"
            "    what: failed to add type-qualifiers.\n"
            << std::endl;
        return false;
    }

    return true;
}

bool Analyzer::addMemberInfo(std::size_t id
    , const TOKEN::StructDeclarationList *sdl)
{
    for(auto &&sd : sdl->seq)
    {
        if(std::holds_alternative<TOKEN::StructDeclaration::Ssql_sdl>(sd->var))
        {
            TYPE::Type *type = deduceType(std::get<TOKEN::StructDeclaration::Ssql_sdl>(sd->var).sql
                , std::get<TOKEN::StructDeclaration::Ssql_sdl>(sd->var).sdl == nullptr);
            if(type == nullptr)
                return false;
            
            if(auto &&s = std::get<TOKEN::StructDeclaration::Ssql_sdl>(sd->var);
                s.sdl != nullptr)
            {
                for(auto &&sd : s.sdl->seq)
                {
                    if(!addMemberInfo(id, type, sd))
                    {
                        delete type;
                        return false;
                    }
                }
                delete type;
            }
            else
            {
                auto &&info = std::get<TYPE::StructInfo>(mIdMap[id]->var);
                info.members.emplace_back(type, "");
            }
        }
    }

    return true;
}

bool Analyzer::addMemberInfo(std::size_t id
    , TYPE::Type *base
    , const TOKEN::StructDeclarator *sd)
{
    if(std::holds_alternative<TOKEN::StructDeclarator::Sd>(sd->var))
    {
        auto &&s = std::get<TOKEN::StructDeclarator::Sd>(sd->var);
        auto &&[t, i] = deduceTypeAndIdentifier(base, s.d, true);
        
        if(t == nullptr)
            return false;
        
        std::get<TYPE::StructInfo>(mIdMap[id]->var).members.emplace_back(t, i);
        
        IDENTIFIER::Identifier *identifier
            = new IDENTIFIER::Identifier(std::to_string(id) + '.' + i
                , new IDENTIFIER::Member(id
                    , i));
        if(!mScope->addIdentifier(mScope->scopeTag()
            , SCOPE::Scope::NamespaceTag::MEMBER
            , identifier->name
            , identifier))
        {
            std::cerr << "analyzer error:\n"
                "    what: duplicate member of struct-or-union.\n"
                "    name: " << i << "\n"
                "    id: " << id
                << std::endl;
            delete identifier;
            return false;
        }
    }
    else if(std::holds_alternative<TOKEN::StructDeclarator::Sd_ce>(sd->var))
    {
        auto &&s = std::get<TOKEN::StructDeclarator::Sd_ce>(sd->var);

        std::string ident;
        TYPE::Type *type = nullptr;

        if(s.d != nullptr)
        {
            auto &&[t, i] = deduceTypeAndIdentifier(base, s.d, true);
            ident.swap(i);
            if(t == nullptr)
                return false;
            type = t;

            IDENTIFIER::Identifier *identifier
                = new IDENTIFIER::Identifier(std::to_string(id) + '.' + ident
                    , new IDENTIFIER::Member(id
                        , ident));
            if(!mScope->addIdentifier(mScope->scopeTag()
                , SCOPE::Scope::NamespaceTag::MEMBER
                , identifier->name
                , identifier))
            {
                std::cerr << "analyzer error:\n"
                    "    what: duplicate member of struct-or-union.\n"
                    "    name: " << ident << "\n"
                    "    id: " << id
                    << std::endl;
                delete identifier;
                delete type;
                return false;
            }
        }
        else
            type = base->copy();

        type = new TYPE::Type(new TYPE::Bitfield(type, s.ce->copy()));
        std::get<TYPE::StructInfo>(mIdMap[id]->var).members.emplace_back(type, ident);
    }

    return true;
}

TYPE::Type *Analyzer::deduceType(TYPE::Type *base
    , const TOKEN::AbstractDeclarator *ad)
{
    if(std::holds_alternative<TOKEN::AbstractDeclarator::Sp>(ad->var))
        return deduceType(base, std::get<TOKEN::AbstractDeclarator::Sp>(ad->var).p);
    else if(std::holds_alternative<TOKEN::AbstractDeclarator::Sp_dad>(ad->var))
    {
        auto &&s = std::get<TOKEN::AbstractDeclarator::Sp_dad>(ad->var);
        if(s.p != nullptr)
            base = deduceType(base, s.p);
        if(base == nullptr)
            return nullptr;
        
        TYPE::Type *type = deduceType(base, s.dad);
        if(s.p != nullptr)
            delete base;
        return type;
    }

    return nullptr;
}

TYPE::Type *Analyzer::deduceType(TYPE::Type *base
    , const TOKEN::DirectAbstractDeclarator *dad)
{
    TYPE::Type *type = base->copy();

    for(auto iter = dad->seq.rbegin(); iter != dad->seq.rend(); iter++)
    {
        if(std::holds_alternative<TOKEN::DirectAbstractDeclarator::Sad>(*iter))
        {
            TYPE::Type *t = deduceType(type, std::get<TOKEN::DirectAbstractDeclarator::Sad>(*iter).ad);
            delete type;
            type = t;
        }
        else if(std::holds_alternative<TOKEN::DirectAbstractDeclarator::Stql_ae>(*iter))
        {
            auto &&s = std::get<TOKEN::DirectAbstractDeclarator::Stql_ae>(*iter);
            type = new TYPE::Type(new TYPE::Array(type
                , s.ae != nullptr ? s.ae->copy() : nullptr
                , false
                , s.hasStatic
                , s.tql != nullptr
                    ? deduceQualifiers(s.tql->seq)
                    : TYPE::Qualifier()));
        }
        else if(std::holds_alternative<TOKEN::DirectAbstractDeclarator::Sp>(*iter))
        {
            type = new TYPE::Type(new TYPE::Array(type
                , nullptr
                , true
                , false
                , TYPE::Qualifier()));
        }
        else if(std::holds_alternative<TOKEN::DirectAbstractDeclarator::Sptl>(*iter))
        {
            TYPE::Function *function = new TYPE::Function(type, false);
            if(std::get<TOKEN::DirectAbstractDeclarator::Sptl>(*iter).ptl != nullptr)
            {
                auto &&s = std::get<TOKEN::DirectAbstractDeclarator::Sptl>(*iter);
                function->isVariable = s.ptl->isValiable;
                for(auto &&pd : s.ptl->pl->seq)
                {
                    function->arguments.push_back(deduceType(pd));
                    if(function->arguments.back() == nullptr)
                    {
                        delete function;
                        return nullptr;
                    }
                }
            }

            type = new TYPE::Type(function);
        }
    }

    return type;
}

std::pair<TYPE::Type*, std::string> Analyzer::deduceTypeAndIdentifier(TYPE::Type *base
    , const TOKEN::Declarator *d
    , bool isPrototype)
{
    TYPE::Type *type = base;
    if(d->p != nullptr)
    {
        TYPE::Type *type = deduceType(base, d->p);
        if(type == nullptr)
            return {nullptr, ""};
    }

    auto &&[t, i] = deduceTypeAndIdentifier(type, d->dd, isPrototype);
    if(t == nullptr && d->p != nullptr)
        delete type;
    
    return {t, i};
}

std::pair<TYPE::Type*, std::string> Analyzer::deduceTypeAndIdentifier(TYPE::Type *base
    , const TOKEN::DirectDeclarator *dd
    , bool isPrototype)
{
    TYPE::Type *type = base->copy();
    std::string ident;

    for(auto iter = dd->seq.rbegin(); iter != dd->seq.rend(); iter++)
    {
        if(std::holds_alternative<TOKEN::DirectDeclarator::Si>(*iter))
            ident = TOKEN::str(std::get<TOKEN::DirectDeclarator::Si>(*iter).i);
        else if(std::holds_alternative<TOKEN::DirectDeclarator::Sd>(*iter))
        {
            auto &&[t, i] = deduceTypeAndIdentifier(type, std::get<TOKEN::DirectDeclarator::Sd>(*iter).d, isPrototype);
            delete type;
            if(t == nullptr)
                return {t, i};
            type = t;
            ident.swap(i);
        }
        else if(std::holds_alternative<TOKEN::DirectDeclarator::Stql_ae>(*iter))
        {
            auto &&s = std::get<TOKEN::DirectDeclarator::Stql_ae>(*iter);
            TYPE::Array *array = new TYPE::Array(type
                , s.ae != nullptr ? s.ae->copy() : nullptr
                , false
                , s.hasStatic
                , s.tql != nullptr ? deduceQualifiers(s.tql->seq) : TYPE::Qualifier());
            type = new TYPE::Type(array);
        }
        else if(std::holds_alternative<TOKEN::DirectDeclarator::Stql>(*iter))
        {
            auto &&s = std::get<TOKEN::DirectDeclarator::Stql>(*iter);
            TYPE::Array *array = new TYPE::Array(type
                , nullptr
                , true
                , false
                , s.tql != nullptr ? deduceQualifiers(s.tql->seq) : TYPE::Qualifier());
            type = new TYPE::Type(array);
        }
        else if(std::holds_alternative<TOKEN::DirectDeclarator::Sptl>(*iter))
        {
            auto &&s = std::get<TOKEN::DirectDeclarator::Sptl>(*iter);
            TYPE::Function *function = new TYPE::Function(type
                , s.ptl->isValiable);
            
            if(isPrototype)
                mScope = mScope->addChild(SCOPE::Scope::ScopeTag::FUNCTION_PROTOTYPE);

            for(auto &&pd : s.ptl->pl->seq)
            {
                function->arguments.push_back(deduceType(pd));
                if(function->arguments.back() == nullptr)
                {
                    if(isPrototype)
                        mScope = removeScope();

                    delete function;
                    return {nullptr, ""};
                }
            }

            if(isPrototype)
                mScope = removeScope();

            type = new TYPE::Type(function);
        }
        else if(std::holds_alternative<TOKEN::DirectDeclarator::Sil>(*iter))
        {
            TYPE::Function *function = new TYPE::Function(type, false);

            if(std::get<TOKEN::DirectDeclarator::Sil>(*iter).il != nullptr)
            {
                if(!addArguments(std::get<TOKEN::DirectDeclarator::Sil>(*iter).il))
                {
                    delete function;
                    return {nullptr, ""};
                }
            }

            type = new TYPE::Type(function);
        }
    }

    return {type, ident};
}

SCOPE::Scope *Analyzer::removeScope()
{
    SCOPE::Scope *parent = mScope->getParent();
    delete mScope;
    return parent;
}

const std::unordered_map<TYPE::Base::Tag, std::vector<std::multiset<TOKEN::TypeSpecifier::Tag>>> Analyzer::TYPE_MAP
    = {{TYPE::Base::Tag::VOID
        , {{TOKEN::TypeSpecifier::Tag::VOID}}}
        , {TYPE::Base::Tag::CHAR
            , {{TOKEN::TypeSpecifier::Tag::CHAR}}}
        , {TYPE::Base::Tag::S_CHAR
            , {{TOKEN::TypeSpecifier::Tag::SIGNED
                , TOKEN::TypeSpecifier::Tag::CHAR}}}
        , {TYPE::Base::Tag::U_CHAR
            , {{TOKEN::TypeSpecifier::Tag::UNSIGNED
                , {TOKEN::TypeSpecifier::Tag::CHAR}}}}
        , {TYPE::Base::Tag::S_SHORT
            , {{TOKEN::TypeSpecifier::Tag::SHORT}
                , {TOKEN::TypeSpecifier::Tag::SIGNED
                    , TOKEN::TypeSpecifier::Tag::SHORT}
                , {TOKEN::TypeSpecifier::Tag::SHORT
                    , TOKEN::TypeSpecifier::Tag::INT}
                , {TOKEN::TypeSpecifier::Tag::SIGNED
                    , TOKEN::TypeSpecifier::Tag::SHORT
                    , TOKEN::TypeSpecifier::Tag::INT}}}
        , {TYPE::Base::Tag::U_SHORT
            , {{TOKEN::TypeSpecifier::Tag::UNSIGNED
                , TOKEN::TypeSpecifier::Tag::SHORT}
                , {TOKEN::TypeSpecifier::Tag::UNSIGNED
                    , TOKEN::TypeSpecifier::Tag::SHORT
                    , TOKEN::TypeSpecifier::Tag::INT}}}
        , {TYPE::Base::Tag::S_INT
            , {{TOKEN::TypeSpecifier::Tag::INT}
                , {TOKEN::TypeSpecifier::Tag::SIGNED}
                , {TOKEN::TypeSpecifier::Tag::SIGNED
                    , TOKEN::TypeSpecifier::Tag::INT}}}
        , {TYPE::Base::Tag::U_INT
            , {{TOKEN::TypeSpecifier::Tag::UNSIGNED}
                , {TOKEN::TypeSpecifier::Tag::UNSIGNED
                    , TOKEN::TypeSpecifier::Tag::INT}}}
        , {TYPE::Base::Tag::S_LONG
            , {{TOKEN::TypeSpecifier::Tag::LONG}
                , {TOKEN::TypeSpecifier::Tag::SIGNED
                    , TOKEN::TypeSpecifier::Tag::LONG}
                , {TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::INT}
                , {TOKEN::TypeSpecifier::Tag::SIGNED
                    , TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::INT}}}
        , {TYPE::Base::Tag::U_LONG
            , {{TOKEN::TypeSpecifier::Tag::UNSIGNED
                , TOKEN::TypeSpecifier::Tag::LONG}
                , {TOKEN::TypeSpecifier::Tag::UNSIGNED
                    , TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::INT}}}
        , {TYPE::Base::Tag::S_LONG_LONG
            , {{TOKEN::TypeSpecifier::Tag::LONG
                , TOKEN::TypeSpecifier::Tag::LONG}
                , {TOKEN::TypeSpecifier::Tag::SIGNED
                    , TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::LONG}
                , {TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::INT}
                , {TOKEN::TypeSpecifier::Tag::SIGNED
                    , TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::INT}}}
        , {TYPE::Base::Tag::U_LONG_LONG
            , {{TOKEN::TypeSpecifier::Tag::UNSIGNED
                , TOKEN::TypeSpecifier::Tag::LONG
                , TOKEN::TypeSpecifier::Tag::LONG}
                , {TOKEN::TypeSpecifier::Tag::UNSIGNED
                    , TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::LONG
                    , TOKEN::TypeSpecifier::Tag::INT}}}
        , {TYPE::Base::Tag::FLOAT
            , {{TOKEN::TypeSpecifier::Tag::FLOAT}}}
        , {TYPE::Base::Tag::DOUBLE
            , {{TOKEN::TypeSpecifier::Tag::DOUBLE}}}
        , {TYPE::Base::Tag::LONG_DOUBLE
            , {{TOKEN::TypeSpecifier::Tag::LONG
                , TOKEN::TypeSpecifier::Tag::DOUBLE}}}
        , {TYPE::Base::Tag::BOOL
            , {{TOKEN::TypeSpecifier::Tag::BOOL}}}
        , {TYPE::Base::Tag::FLOAT_COMPLEX
            , {{TOKEN::TypeSpecifier::Tag::FLOAT
                , TOKEN::TypeSpecifier::Tag::COMPLEX}}}
        , {TYPE::Base::Tag::DOUBLE_COMPLEX
            , {{TOKEN::TypeSpecifier::Tag::DOUBLE
                , TOKEN::TypeSpecifier::Tag::COMPLEX}}}
        , {TYPE::Base::Tag::LONG_DOUBLE_COMPLEX
            , {{TOKEN::TypeSpecifier::Tag::LONG
                , TOKEN::TypeSpecifier::Tag::DOUBLE
                , TOKEN::TypeSpecifier::Tag::COMPLEX}}}};