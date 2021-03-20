#include <bitset>
#include <iostream>
#include <string>

#include "scope.hpp"
#include "deducer.hpp"

std::optional<std::tuple<IDENTIFIER::StorageClass
    , TYPE::Type
    , IDENTIFIER::FunctionSpecifiers
    , IDENTIFIER::Alignment>> deduceAttributes(const TOKEN::DeclarationSpecifiers *ds
        , SCOPE::Scope* scope
        , bool isEnd)
{
    using namespace TOKEN;
    using ReturnT = std::optional<std::tuple<IDENTIFIER::StorageClass
        , TYPE::Type
        , IDENTIFIER::FunctionSpecifiers
        , IDENTIFIER::Alignment>>;

    std::vector<const StorageClassSpecifier*> scsVec;
    std::vector<const TypeSpecifier*> tsVec;
    std::vector<const TypeQualifier*> tqVec;
    std::vector<const FunctionSpecifier*> fsVec;
    std::vector<const AlignmentSpecifier*> asVec;
    
    for(auto &&v : ds->seq)
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

    auto scOpt{deduceStorageClass(scsVec)};
    auto tOpt{deduceType(tsVec, tqVec, scope, isEnd)};
    auto fsOpt{deduceFunctionSpecifiers(fsVec)};
    auto asOpt{deduceAlignment(asVec, scope)};

    return scOpt && tOpt && fsOpt && asOpt
        ? ReturnT{std::make_tuple(std::move(scOpt.value())
            , std::move(tOpt.value())
            , std::move(fsOpt.value())
            , std::move(asOpt.value()))}
        : std::nullopt;
}

std::optional<IDENTIFIER::StorageClass> deduceStorageClass(const std::vector<const TOKEN::StorageClassSpecifier*> &scVec)
{
    using TTag = TOKEN::StorageClassSpecifier::Tag;
    using ITag = IDENTIFIER::StorageClass::Tag;

    static const std::unordered_map<TTag, ITag> tagMap
        {{TTag::TYPEDEF, ITag::TYPEDEF}
            , {TTag::EXTERN, ITag::EXTERN}
            , {TTag::STATIC, ITag::STATIC}
            , {TTag::THREAD_LOCAL, ITag::THREAD_LOCAL}
            , {TTag::AUTO, ITag::AUTO}
            , {TTag::REGISTER, ITag::REGISTER}};

    IDENTIFIER::StorageClass ret;

    for(const auto &scs : scVec)
    {
        if(auto &&iter{tagMap.find(scs->tag)};
            iter != tagMap.end())
            ret.flags.set(static_cast<std::size_t>(iter->second));
    }

    return {std::move(ret)};
}

std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::TypeSpecifier*> &tsVec
    , const std::vector<const TOKEN::TypeQualifier*> &tqVec
    , SCOPE::Scope *scope
    , bool isEnd)
{
    auto tsOpt{deduceType(tsVec, scope, isEnd)};
    auto tqOpt{deduceQualifiers(tqVec)};

    return tsOpt && tqOpt
        ? addQualifiers(tsOpt.value()
            , tqOpt.value())
        : std::nullopt;
}

std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::TypeSpecifier*> &tsVec
    , SCOPE::Scope *scope
    , bool isEnd)
{
    using namespace TOKEN;
    using TTag = TypeSpecifier::Tag;

    std::bitset<5ull> notEmptyFlags;

    std::multiset<TTag> tSet;
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

    if(notEmptyFlags.count() == 1ull)
    {
        if(notEmptyFlags.test(0ull))
            return deduceType(tSet);
        else if(notEmptyFlags.test(1ull))
            return deduceType(atsVec, scope);
        else if(notEmptyFlags.test(2ull))
            return deduceType(sousVec, scope, isEnd);
        else if(notEmptyFlags.test(3ull))
            return deduceType(esVec, scope);
        else if(notEmptyFlags.test(4ull))
            return deduceType(tnVec, scope);
    }
    else
    {
        std::cerr << "TypeDeducer error:\n"
            "    what: at least one type specifier shall be given.\n"
            << std::flush;
        return std::nullopt;
    }
}

std::optional<TYPE::Type> deduceType(const std::multiset<TOKEN::TypeSpecifier::Tag> &tSet)
{
    for(const auto &mapE : BASE_TYPE_MAP)
    {
        for(const auto &vecE : mapE.second)
        {
            if(vecE == tSet)
                return {TYPE::Type{TYPE::Base{mapE.first}}};
        }
    }

    std::cerr << "TypeDeducer error:\n"
        "    what: fail to deduce type from type-specifier-list.\n"
        << std::flush;
    return std::nullopt;
}

std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::AtomicTypeSpecifier*> &atsVec
    , SCOPE::Scope *scope)
{
    if(atsVec.size() != 1ull)
    {
        std::cerr << "TypeDeducer error:\n"
            "    what: at least one atomic type specifier shall be given.\n"
            << std::flush;
        return std::nullopt;
    }

    auto tOpt{deduceType(atsVec.front()->tn, scope)};
    if(!tOpt)
        return std::nullopt;

    TYPE::Qualifiers quals;
    quals.flags.set(static_cast<std::size_t>(TYPE::Qualifiers::Tag::ATOMIC));

    return addQualifiers(tOpt.value(), quals);    
}

std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::StructOrUnionSpecifier*> &sousVec
    , SCOPE::Scope *scope
    , bool isEnd)
{
    using NTag = SCOPE::Scope::NamespaceTag;
    using Sous = TOKEN::StructOrUnionSpecifier;
    
    auto isUnion{[](const TOKEN::StructOrUnion *sou)
        {return sou->tag == TOKEN::StructOrUnion::Tag::UNION;}};
    auto redefinedError{[](const std::string &tag)
        {
            std::cerr << "TypeDeducer error:\n"
                "    what: tag is redefined.\n"
                "    tag: " << tag
                << std::endl;
            return std::nullopt;
        }};
    auto typeNotMatchError{[](const std::string &tag)
        {
            std::cerr << "TypeDeducer error:\n"
                "    what: type of tag is not match for before declared tag.\n"
                "    tag: " << tag
                << std::endl;
            return std::nullopt;
        }};
    auto isMatchTag{[](const TOKEN::StructOrUnion *sou
        , IDENTIFIER::Tag::T t)
        {
            if((sou->tag == TOKEN::StructOrUnion::Tag::STRUCT
                && t == IDENTIFIER::Tag::T::STRUCT)
                || (sou->tag == TOKEN::StructOrUnion::Tag::UNION
                && t == IDENTIFIER::Tag::T::UNION))
                return true;
            else
                return false;
        }};
    auto define{[](const TOKEN::StructDeclarationList *sdl
        , std::size_t id
        , SCOPE::Scope *s) -> std::optional<TYPE::Type>
        {
            if(!addMember(sdl, id, s))
                return std::nullopt;
            
            TYPE::IdInfo::idMap().find(id)->second->isDefined(true);
            return {TYPE::Type{TYPE::Struct{id}}};
        }};
    auto addTagInfo{[&](const std::string &tag
        , const TOKEN::StructOrUnion *sou)
        {
            TYPE::StructInfo sInfo{tag, isUnion(sou)};
            IDENTIFIER::Tag tagIdent{tag
                , sInfo.id()
                , sInfo.isUnion 
                    ? IDENTIFIER::Tag::T::UNION
                    : IDENTIFIER::Tag::T::STRUCT};
            
            std::shared_ptr<IDENTIFIER::Identifier> tagIdentPtr{new IDENTIFIER::Tag{tagIdent}};
            scope->addIdentifier(tagIdentPtr, NTag::TAG);
            IDENTIFIER::Identifier::idMap().emplace(tagIdent.id(), tagIdentPtr);
            TYPE::IdInfo::idMap().emplace(sInfo.id(), new TYPE::StructInfo{sInfo});

            return sInfo.id();
        }};

    if(sousVec.size() != 1ull)
    {
        std::cerr << "TypeDeducer error:\n"
            "    what: at least one struct or union specifier shall be given.\n"
            << std::flush;
        return std::nullopt;
    }

    if(std::holds_alternative<Sous::Ssou_i_sdl>(sousVec.front()->var))
    {
        auto &&s{std::get<Sous::Ssou_i_sdl>(sousVec.front()->var)};
        if(!s.i)
        {
            TYPE::StructInfo sInfo{{}, isUnion(s.sou)};
            TYPE::IdInfo::idMap().emplace(sInfo.id(), new TYPE::StructInfo{sInfo});
            
            return define(s.sdl, sInfo.id(), scope);
        }
        else
        {
            std::string tag{TOKEN::str(s.i)};
            auto &&identifier{scope->getIdentifier(tag, NTag::TAG, true)};
            if(bool(identifier))
            {
                auto &&tagIdent{std::dynamic_pointer_cast<IDENTIFIER::Tag>(identifier)};
                if(!tagIdent
                    || !isMatchTag(s.sou, tagIdent->tag()))
                    return typeNotMatchError(tag);

                auto &&iter{TYPE::IdInfo::idMap().find(tagIdent->typeId())};
                if(iter->second->isDefined())
                    return redefinedError(tag);
                
                return define(s.sdl, iter->first, scope);
            }
            else
            {
                std::size_t id{addTagInfo(tag, s.sou)};

                return define(s.sdl, id, scope);
            }
        }
    }
    else
    {
        auto &&s{std::get<Sous::Ssou_i>(sousVec.front()->var)};
        if(isEnd)
        {
            std::string tag{TOKEN::str(s.i)};
            auto &&identifier{scope->getIdentifier(tag, NTag::TAG, true)};
            if(bool(identifier))
            {
                auto &&tagIdent{std::dynamic_pointer_cast<IDENTIFIER::Tag>(identifier)};
                if(!tagIdent
                    || !isMatchTag(s.sou, tagIdent->tag()))
                    return typeNotMatchError(tag);
                
                return TYPE::Type{TYPE::Struct{tagIdent->typeId()}};
            }
            else
            {
                std::size_t id{addTagInfo(tag, s.sou)};
                
                return TYPE::Type{TYPE::Struct{id}};
            }
        }
        else
        {
            std::string tag{TOKEN::str(s.i)};
            auto &&identifier{scope->getIdentifier(tag, NTag::TAG, false)};
            if(!identifier)
            {
                std::size_t id{addTagInfo(tag, s.sou)};
                
                return TYPE::Type{TYPE::Struct{id}};
            }
            else
            {
                auto &&tagIdent{std::dynamic_pointer_cast<IDENTIFIER::Tag>(identifier)};
                if(!tagIdent
                    || !isMatchTag(s.sou, tagIdent->tag()))
                    return typeNotMatchError(tag);
                
                return TYPE::Type{TYPE::Struct{tagIdent->typeId()}};
            }
        }
    }
}

bool addMember(const TOKEN::StructDeclarationList *sdl
    , std::size_t typeId
    , SCOPE::Scope *scope)
{
    using namespace TOKEN;

    auto addMemberInfo{[&](std::optional<std::pair<TYPE::Type, std::string>> opt
        , std::shared_ptr<TYPE::StructInfo> &sInfo)
        {
            if(!opt)
                return false;

            auto &&[type, ident]{*opt};
            sInfo->members.emplace_back(type, ident);
            std::shared_ptr<IDENTIFIER::Identifier> member{new IDENTIFIER::Member{ident, sInfo->id()}};
            
            IDENTIFIER::Identifier::idMap().emplace(member->id(), member);
            return scope->addIdentifier(member, SCOPE::Scope::NamespaceTag::MEMBER);
        }};

    auto &&sInfo{std::dynamic_pointer_cast<TYPE::StructInfo>(TYPE::IdInfo::idMap().find(typeId)->second)};
    if(!sInfo)
    {
        std::cerr << "TypeDeducer error:\n"
            "    what: type of tag is not match for before declared tag.\n"
            "    id: " << typeId
            << std::endl;
        return false;
    }

    for(const auto &sd : sdl->seq)
    {
        if(std::holds_alternative<StructDeclaration::Ssad>(sd->var))
            continue;
        
        auto &&s{std::get<StructDeclaration::Ssql_sdl>(sd->var)};
        auto &&tOpt{deduceType(s.sql, scope, !s.sdl)};
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
                    auto &&opt{deduceTypeAndIdentifier(std::get<StructDeclarator::Sd>(sdr->var).d, *tOpt, scope)};
                    if(!addMemberInfo(opt, sInfo))
                        return false;
                }
                else
                {
                    auto &&s{std::get<StructDeclarator::Sd_ce>(sdr->var)};
                    if(!s.d)
                    {
                        auto &&to{deduceType(s.ce, *tOpt)};
                        if(!to)
                            return false;
                        
                        sInfo->members.emplace_back(*to, std::string{});
                    }
                    else
                    {
                        auto &&opt{deduceTypeAndIdentifier(s.d, *tOpt, scope)};

                        if(opt)
                            return false;
                        
                        auto &&[type, ident]{*opt};
                        auto &&to{deduceType(s.ce, type)};
                        if(!to)
                            return false;
                        
                        if(!addMemberInfo(std::pair<TYPE::Type, std::string>{*to, ident}
                            , sInfo))
                            return false;
                    }
                }
            }
        }
    }

    return true;
}

std::optional<TYPE::Type> deduceType(const TOKEN::SpecifierQualifierList *sql
    , SCOPE::Scope *scope
    , bool isEnd)
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

    return deduceType(tsVec, tqVec, scope, isEnd);
}

std::optional<std::pair<TYPE::Type
    , std::string>> deduceTypeAndIdentifier(const TOKEN::Declarator *d
        , const TYPE::Type &baseType
        , SCOPE::Scope *scope)
{
    using DD = TOKEN::DirectDeclarator;

    TYPE::Type resultType{baseType};
    std::string identifier;

    if(bool(d->p))
    {
        if(!addPointer(d->p, resultType))
            return std::nullopt;
    }

    for(auto &&iter{d->dd->seq.crbegin()}; iter != d->dd->seq.crend(); iter++)
    {
        if(std::holds_alternative<DD::Si>(*iter))
            identifier = TOKEN::str(std::get<DD::Si>(*iter).i);
        else if(std::holds_alternative<DD::Sd>(*iter))
        {
            auto &&opt{deduceTypeAndIdentifier(std::get<DD::Sd>(*iter).d
                , resultType
                , scope)};
            if(bool(opt))
                resultType = opt->first
                    , identifier = opt->second;
            else
                return std::nullopt;
        }
        else if(std::holds_alternative<DD::Stql_ae>(*iter))
        {
            auto &&s{std::get<DD::Stql_ae>(*iter)};
            auto &&qOpt{s.tql
                ? deduceQualifiers(s.tql)
                : TYPE::Qualifiers{}};
            
            if(!qOpt)
                return std::nullopt;
            
            resultType = TYPE::Type{TYPE::Array{resultType
                , *qOpt
                , std::shared_ptr<TOKEN::AssignmentExpression>{s.ae
                    ? s.ae->copy()
                    : nullptr}
                , s.hasStatic}};
        }
        else if(std::holds_alternative<DD::Stql>(*iter))
        {
            auto &&s{std::get<DD::Stql>(*iter)};
            auto &&qOpt{s.tql
                ? deduceQualifiers(s.tql)
                : TYPE::Qualifiers{}};
            
            if(!qOpt)
                return std::nullopt;

            resultType = TYPE::Type{TYPE::Array{resultType
                , *qOpt
                , nullptr}};
        }
        else if(std::holds_alternative<DD::Sptl>(*iter))
        {
            auto &&s{std::get<DD::Sptl>(*iter)};
            
        }
    }
}