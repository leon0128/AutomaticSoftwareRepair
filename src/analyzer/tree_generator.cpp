#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

#include "utility/output.hpp"
#include "common/type.hpp"
#include "common/define.hpp"
#include "tokenizer.hpp"
#include "tree_generator.hpp"

namespace ANALYZER
{

// if cache has specific token, its token is returned.
#define IF_CACHE_HAS_TOKEN_RETURN(Type) \
    if(auto &&cache{createFromCache<Type>()}; \
        cache != nullptr) \
        return cache;

TreeGenerator::TreeGenerator()
    : mFile{}
    , mSeq{TEMPORARY_OBJECT}
    , mIdx(0)
    , mTranslationUnit(nullptr)
    , mCacheMap{}
{
}

TreeGenerator::~TreeGenerator()
{
    delete mTranslationUnit;
    for(auto &&[pos, element] : mCacheMap)
    {
        std::visit([](auto &&token){delete token;}
            , element->mToken);
        delete element;
    }
}

bool TreeGenerator::execute(const std::string &filename
    , const Sequence &sequence)
{
    mFile = filename;
    mSeq = sequence;

    mTranslationUnit = tokTranslationUnit();

    if(mIdx == mSeq.get().size()
        && mTranslationUnit)
        return true;
    else
        return noEvaluatedError();
}

TOKEN::TranslationUnit *TreeGenerator::tokTranslationUnit()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::TranslationUnit)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::ExternalDeclaration*> seq;
    for(auto ed = tokExternalDeclaration(); ed != nullptr; ed = tokExternalDeclaration())
        seq.push_back(ed);

    if(!seq.empty())
        return registerToCache(new TOKEN::TranslationUnit(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::ExternalDeclaration *TreeGenerator::tokExternalDeclaration()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ExternalDeclaration)
    std::size_t beginIdx{mIdx};

    if(TOKEN::Declaration *d = tokDeclaration();
        d != nullptr)
        return registerToCache(new TOKEN::ExternalDeclaration(d), beginIdx);
    else if(TOKEN::FunctionDefinition *fd = tokFunctionDefinition();
        fd != nullptr)
        return registerToCache(new TOKEN::ExternalDeclaration(fd), beginIdx);
    else if(TOKEN::IncludingFile *i{tokIncludingFile()};
        i != nullptr)
        return registerToCache(new TOKEN::ExternalDeclaration{i}, beginIdx);

    return nullptr;
}

TOKEN::FunctionDefinition *TreeGenerator::tokFunctionDefinition()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::FunctionDefinition)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    TOKEN::DeclarationSpecifiers *ds = nullptr;
    TOKEN::Declarator *d = nullptr;
    TOKEN::DeclarationList *dl = nullptr;
    TOKEN::CompoundStatement *cs = nullptr;

    if((ds = tokDeclarationSpecifiers()) != nullptr
        && (d = tokDeclarator()) != nullptr
        && (dl = tokDeclarationList(), true)
        && (cs = tokCompoundStatement()) != nullptr)
        return registerToCache(new TOKEN::FunctionDefinition(ds, d, dl, cs), beginIdx);
    else
    {
        mIdx = pre;
        delete ds;
        delete d;
        delete dl;
        delete cs;
    }

    return nullptr;
}

TOKEN::Declaration *TreeGenerator::tokDeclaration()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Declaration)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    
    // declaration-specifiers init-declarator-list
    if(TOKEN::Declaration::Sds_idl sds_idl;
        (sds_idl.ds = tokDeclarationSpecifiers()) != nullptr
        && (sds_idl.idl = tokInitDeclaratorList(), true)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return registerToCache(new TOKEN::Declaration(sds_idl), beginIdx);
    else
    {
        mIdx = pre;
        delete sds_idl.ds;
        delete sds_idl.idl;
    }
    // static_assert-declaration
    if(TOKEN::Declaration::Ssad ssad;
        (ssad.sad = tokStaticAssertDeclaration()) != nullptr)
        return registerToCache(new TOKEN::Declaration(ssad), beginIdx);

    return nullptr;
}

TOKEN::DeclarationSpecifiers *TreeGenerator::tokDeclarationSpecifiers()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::DeclarationSpecifiers)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::DeclarationSpecifiers::Var> seq;
    
    bool hasTypeSpecifier = false;
    while(true)
    {
        TOKEN::DeclarationSpecifiers::Var v;
        if(v.emplace<TOKEN::StorageClassSpecifier*>(tokStorageClassSpecifier()) != nullptr
            || (v.emplace<TOKEN::TypeSpecifier*>(tokTypeSpecifier()) != nullptr && (hasTypeSpecifier = true))
            || v.emplace<TOKEN::TypeQualifier*>(tokTypeQualifier()) != nullptr
            || v.emplace<TOKEN::FunctionSpecifier*>(tokFunctionSpecifier()) != nullptr
            || v.emplace<TOKEN::AlignmentSpecifier*>(tokAlignmentSpecifier()) != nullptr
            || v.emplace<TOKEN::AttributeSpecifierList*>(tokAttributeSpecifierList()) != nullptr)
            seq.push_back(v);
        else
            break;
    
        if(TOKEN::Identifier *i = nullptr;
            hasTypeSpecifier
                && (i = tokIdentifier()) != nullptr)
        {
            delete i;
            mIdx--;
            break;
        }
    }

    if(!seq.empty())
        return registerToCache(new TOKEN::DeclarationSpecifiers(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::InitDeclaratorList *TreeGenerator::tokInitDeclaratorList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::InitDeclaratorList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::InitDeclarator*> seq;
    TOKEN::InitDeclarator *id = tokInitDeclarator();
    if(id != nullptr)
    {
        seq.push_back(id);
    
        while(true)
        {
            if(isMatch(TOKEN::Punctuator::Tag::COMMA))
            {
                if((id = tokInitDeclarator()) != nullptr)
                    seq.push_back(id);
                else
                {
                    mIdx--;
                    break;
                }
            }
            else
                break;
        }
    }

    if(!seq.empty())
        return registerToCache(new TOKEN::InitDeclaratorList(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::StaticAssertDeclaration *TreeGenerator::tokStaticAssertDeclaration()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::StaticAssertDeclaration)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    TOKEN::ConstantExpression *ce = nullptr;
    TOKEN::StringLiteral *sl = nullptr;
    
    if(isMatch(TOKEN::Keyword::Tag::STATIC_ASSERT)
        && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
        && (ce = tokConstantExpression()) != nullptr
        && (sl = tokStringLiteral()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return registerToCache(new TOKEN::StaticAssertDeclaration(ce, sl), beginIdx);
    else
    {
        mIdx = pre;
        delete ce;
        delete sl;
    }

    return nullptr;
}

TOKEN::ConstantExpression *TreeGenerator::tokConstantExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ConstantExpression)
    std::size_t beginIdx{mIdx};

    if(TOKEN::ConditionalExpression *ce = tokConditionalExpression();
        ce != nullptr)
        return registerToCache(new TOKEN::ConstantExpression(ce), beginIdx);
    else
        return nullptr;
}

TOKEN::StringLiteral *TreeGenerator::tokStringLiteral()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::StringLiteral)
    std::size_t beginIdx{mIdx};

    if(mIdx < mSeq.get().size()
        && std::holds_alternative<TOKEN::StringLiteral*>(mSeq.get()[mIdx]->var))
        return mIdx++, registerToCache(std::get<TOKEN::StringLiteral*>(mSeq.get()[mIdx - 1]->var)->copy(), beginIdx);
    else
        return nullptr;
}

TOKEN::Declarator *TreeGenerator::tokDeclarator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Declarator)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    TOKEN::Pointer *p = nullptr;
    TOKEN::AttributeSpecifierList *asl{nullptr};
    TOKEN::DirectDeclarator *dd = nullptr;
    
    if((p = tokPointer(), true)
        && (asl = tokAttributeSpecifierList(), true)
        && (dd = tokDirectDeclarator()) != nullptr)
        return registerToCache(new TOKEN::Declarator(p, asl, dd), beginIdx);
    else
    {
        mIdx = pre;
        delete p;
        delete asl;
        delete dd;
    }

    return nullptr;
}

TOKEN::DeclarationList *TreeGenerator::tokDeclarationList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::DeclarationList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::Declaration*> seq;
    for(TOKEN::Declaration *d = tokDeclaration(); d != nullptr; d = tokDeclaration())
        seq.push_back(d);

    if(!seq.empty())
        return registerToCache(new TOKEN::DeclarationList(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::CompoundStatement *TreeGenerator::tokCompoundStatement()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::CompoundStatement)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    TOKEN::BlockItemList *bil = nullptr;
    
    if(isMatch(TOKEN::Punctuator::Tag::L_CURLY_BRACKET)
        && (bil = tokBlockItemList(), true)
        && isMatch(TOKEN::Punctuator::Tag::R_CURLY_BRACKET))
        return registerToCache(new TOKEN::CompoundStatement(bil), beginIdx);
    else
    {
        mIdx = pre;
        delete bil;
    }

    return nullptr;
}

TOKEN::StorageClassSpecifier *TreeGenerator::tokStorageClassSpecifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::StorageClassSpecifier)
    std::size_t beginIdx{mIdx};

    TOKEN::StorageClassSpecifier::Tag tag = TOKEN::StorageClassSpecifier::Tag::NONE;

    if(isMatch(TOKEN::Keyword::Tag::TYPEDEF))
        tag = TOKEN::StorageClassSpecifier::Tag::TYPEDEF;
    else if(isMatch(TOKEN::Keyword::Tag::EXTERN))
        tag = TOKEN::StorageClassSpecifier::Tag::EXTERN;
    else if(isMatch(TOKEN::Keyword::Tag::STATIC))
        tag = TOKEN::StorageClassSpecifier::Tag::STATIC;
    else if(isMatch(TOKEN::Keyword::Tag::THREAD_LOCAL))
        tag = TOKEN::StorageClassSpecifier::Tag::THREAD_LOCAL;
    else if(isMatch(TOKEN::Keyword::Tag::AUTO))
        tag = TOKEN::StorageClassSpecifier::Tag::AUTO;
    else if(isMatch(TOKEN::Keyword::Tag::REGISTER))
        tag = TOKEN::StorageClassSpecifier::Tag::REGISTER;

    if(tag != TOKEN::StorageClassSpecifier::Tag::NONE)
        return registerToCache(new TOKEN::StorageClassSpecifier(tag), beginIdx);
    else
        return nullptr;
}

TOKEN::TypeSpecifier *TreeGenerator::tokTypeSpecifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::TypeSpecifier)
    std::size_t beginIdx{mIdx};

    std::size_t preIdx{mIdx};
    TOKEN::TypeSpecifier::Var var;
    
    if(std::shared_ptr<TOKEN::Keyword> keyword{tokKeyword()};
        keyword.get() != nullptr)
    {
        if(auto &&iter{TYPE::KEYWORD_TYPE_MAP.find(keyword->tag)};
            iter != TYPE::KEYWORD_TYPE_MAP.end())
        {
            var.emplace<TOKEN::TypeSpecifier::Tag>(iter->second);
            return registerToCache(new TOKEN::TypeSpecifier{var}, beginIdx);
        }

        mIdx = preIdx;
    }

    if(var.emplace<TOKEN::AtomicTypeSpecifier*>(tokAtomicTypeSpecifier()) != nullptr
        || var.emplace<TOKEN::StructOrUnionSpecifier*>(tokStructOrUnionSpecifier()) != nullptr
        || var.emplace<TOKEN::EnumSpecifier*>(tokEnumSpecifier()) != nullptr
        || var.emplace<TOKEN::TypedefName*>(tokTypedefName()) != nullptr)
        return registerToCache(new TOKEN::TypeSpecifier(var), beginIdx);
    
    return nullptr;
}

TOKEN::TypeQualifier *TreeGenerator::tokTypeQualifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::TypeQualifier)
    std::size_t beginIdx{mIdx};

    TOKEN::TypeQualifier::Tag tag = TOKEN::TypeQualifier::Tag::NONE;
    
    if(isMatch(TOKEN::Keyword::Tag::CONST))
        tag = TOKEN::TypeQualifier::Tag::CONST;
    else if(isMatch(TOKEN::Keyword::Tag::RESTRICT))
        tag = TOKEN::TypeQualifier::Tag::RESTRICT;
    else if(isMatch(TOKEN::Keyword::Tag::VOLATILE))
        tag = TOKEN::TypeQualifier::Tag::VOLATILE;
    else if(isMatch(TOKEN::Keyword::Tag::ATOMIC))
        tag = TOKEN::TypeQualifier::Tag::ATOMIC;

    if(tag != TOKEN::TypeQualifier::Tag::NONE)
        return registerToCache(new TOKEN::TypeQualifier(tag), beginIdx);
    else
        return nullptr;
}

TOKEN::FunctionSpecifier *TreeGenerator::tokFunctionSpecifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::FunctionSpecifier)
    std::size_t beginIdx{mIdx};

    TOKEN::FunctionSpecifier::Tag tag = TOKEN::FunctionSpecifier::Tag::NONE;

    if(isMatch(TOKEN::Keyword::Tag::INLINE))
        tag = TOKEN::FunctionSpecifier::Tag::INLINE;
    else if(isMatch(TOKEN::Keyword::Tag::NORETURN))
        tag = TOKEN::FunctionSpecifier::Tag::NORETURN;
    
    if(tag != TOKEN::FunctionSpecifier::Tag::NONE)
        return registerToCache(new TOKEN::FunctionSpecifier(tag), beginIdx);
    else
        return nullptr;
}

TOKEN::AlignmentSpecifier *TreeGenerator::tokAlignmentSpecifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AlignmentSpecifier)
    std::size_t beginIdx{mIdx};

    TOKEN::AlignmentSpecifier::Var var;
    std::size_t pre = mIdx;

    if(isMatch(TOKEN::Keyword::Tag::ALIGNAS)
        && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
        && var.emplace<TOKEN::TypeName*>(tokTypeName()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return registerToCache(new TOKEN::AlignmentSpecifier(var), beginIdx);
    else
    {
        mIdx = pre;
        if(std::holds_alternative<TOKEN::TypeName*>(var))
            delete std::get<TOKEN::TypeName*>(var);
    }

    if(isMatch(TOKEN::Keyword::Tag::ALIGNAS)
        && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
        && var.emplace<TOKEN::ConstantExpression*>(tokConstantExpression()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return registerToCache(new TOKEN::AlignmentSpecifier(var), beginIdx);
    else
    {
        mIdx = pre;
        if(std::holds_alternative<TOKEN::ConstantExpression*>(var))
            delete std::get<TOKEN::ConstantExpression*>(var);
    }

    return nullptr;
}

TOKEN::InitDeclarator *TreeGenerator::tokInitDeclarator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::InitDeclarator)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::InitDeclarator::Sd_i s;
        (s.asl0 = tokAttributeSpecifierList(), true)
            && (s.d = tokDeclarator()) != nullptr
            && (s.asl1 = tokAttributeSpecifierList(), true)
            && isMatch(TOKEN::Punctuator::Tag::ASSIGNMENT)
            && (s.i = tokInitializer()) != nullptr)
        return registerToCache(new TOKEN::InitDeclarator(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.asl0;
        delete s.d;
        delete s.asl1;
        delete s.i;
    }

    if(TOKEN::InitDeclarator::Sd_ba s;
        (s.asl0 = tokAttributeSpecifierList(), true)
            && (s.d = tokDeclarator()) != nullptr
            && (s.asl1 = tokAttributeSpecifierList(), true)
            && (s.ba = tokBasicAsm())
            && (s.asl2 = tokAttributeSpecifierList(), true))
        return registerToCache(new TOKEN::InitDeclarator{s}, beginIdx);
    else
    {
        mIdx = pre;
        delete s.asl0;
        delete s.d;
        delete s.asl1;
        delete s.ba;
    }

    if(TOKEN::InitDeclarator::Sd s;
        (s.asl0 = tokAttributeSpecifierList(), true)
            && (s.d = tokDeclarator()) != nullptr
            && (s.asl1 = tokAttributeSpecifierList(), true))
        return registerToCache(new TOKEN::InitDeclarator(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.asl0;
        delete s.d;
        delete s.asl1;
    }

    return nullptr;
}

TOKEN::ConditionalExpression *TreeGenerator::tokConditionalExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ConditionalExpression)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::ConditionalExpression::Slore_e_ce s;
        (s.lore = tokLogicalORExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::QUESTION)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.ce = tokConditionalExpression()) != nullptr)
        return registerToCache(new TOKEN::ConditionalExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.lore;
        delete s.e;
        delete s.ce;
    }

    if(TOKEN::ConditionalExpression::Slore s;
        (s.lore = tokLogicalORExpression()) != nullptr)
        return registerToCache(new TOKEN::ConditionalExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.lore;
    }

    return nullptr;
}

TOKEN::Pointer *TreeGenerator::tokPointer()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Pointer)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::Pointer::Stql_p s;
        isMatch(TOKEN::Punctuator::Tag::ASTERISK)
            && (s.tql = tokTypeQualifierList(), true)
            && (s.p = tokPointer()) != nullptr)
        return registerToCache(new TOKEN::Pointer(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.tql;
        delete s.p;
    }

    if(TOKEN::Pointer::Stql s;
        isMatch(TOKEN::Punctuator::Tag::ASTERISK)
            && (s.tql = tokTypeQualifierList(), true))
        return registerToCache(new TOKEN::Pointer(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.tql;
    }

    return nullptr;
}

TOKEN::DirectDeclarator *TreeGenerator::tokDirectDeclarator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::DirectDeclarator)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::DirectDeclarator::Var> seq;
    std::size_t pre = mIdx;

    if(TOKEN::Identifier *i = tokIdentifier();
        i != nullptr)
        seq.emplace_back(TOKEN::DirectDeclarator::Si(i));
    else if(TOKEN::Declarator *d = nullptr;
        isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (d = tokDeclarator()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        seq.emplace_back(TOKEN::DirectDeclarator::Sd(d));
    else
    {
        mIdx = pre;
        delete i;
        delete d;
        return nullptr;
    }

    while(true)
    {
        pre = mIdx;
        if(TOKEN::DirectDeclarator::Stql_ae s;
            isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
                && (s.tql = tokTypeQualifierList(), true)
                && (s.ae = tokAssignmentExpression(), true)
                && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET)
                && (s.hasStatic = false, true))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.tql;
            delete s.ae;
        }

        if(TOKEN::DirectDeclarator::Stql_ae s;
            isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
                && isMatch(TOKEN::Keyword::Tag::STATIC)
                && (s.tql = tokTypeQualifierList(), true)
                && (s.ae = tokAssignmentExpression()) != nullptr
                && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET)
                && (s.hasStatic = true, true))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.tql;
            delete s.ae;
        }

        if(TOKEN::DirectDeclarator::Stql_ae s;
            isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
                && (s.tql = tokTypeQualifierList()) != nullptr
                && isMatch(TOKEN::Keyword::Tag::STATIC)
                && (s.ae = tokAssignmentExpression()) != nullptr
                && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET)
                && (s.hasStatic = true, true))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.tql;
            delete s.ae;
        }

        if(TOKEN::DirectDeclarator::Stql s;
            isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
                && (s.tql = tokTypeQualifierList(), true)
                && isMatch(TOKEN::Punctuator::Tag::ASTERISK)
                && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.tql;
        }

        if(TOKEN::DirectDeclarator::Sptl s;
            isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
                && (s.ptl = tokParameterTypeList()) != nullptr
                && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.ptl;
        }

        if(TOKEN::DirectDeclarator::Sil s;
            isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
                && (s.il = tokIdentifierList(), true)
                && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.il;
        }

        break;
    }

    return registerToCache(new TOKEN::DirectDeclarator(std::move(seq)), beginIdx);
}

TOKEN::BlockItemList *TreeGenerator::tokBlockItemList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::BlockItemList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::BlockItem*> seq;
    for(TOKEN::BlockItem *bi = tokBlockItem();
        bi != nullptr;
        bi = tokBlockItem())
        seq.push_back(bi);
    
    if(!seq.empty())
        return registerToCache(new TOKEN::BlockItemList(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::AtomicTypeSpecifier *TreeGenerator::tokAtomicTypeSpecifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AtomicTypeSpecifier)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    
    if(TOKEN::TypeName *tn = nullptr;
        isMatch(TOKEN::Keyword::Tag::ATOMIC)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (tn = tokTypeName()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return registerToCache(new TOKEN::AtomicTypeSpecifier(tn), beginIdx);
    else
    {
        mIdx = pre;
        delete tn;
    }

    return nullptr;
}

TOKEN::StructOrUnionSpecifier *TreeGenerator::tokStructOrUnionSpecifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::StructOrUnionSpecifier)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::StructOrUnionSpecifier::Ssou_i_sdl s;
        (s.sou = tokStructOrUnion()) != nullptr
            && (s.asl = tokAttributeSpecifierList(), true)
            && (s.i = tokIdentifier(), true)
            && isMatch(TOKEN::Punctuator::Tag::L_CURLY_BRACKET)
            && (s.sdl = tokStructDeclarationList()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_CURLY_BRACKET))
        return registerToCache(new TOKEN::StructOrUnionSpecifier(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.sou;
        delete s.asl;
        delete s.i;
        delete s.sdl;
    }

    if(TOKEN::StructOrUnionSpecifier::Ssou_i s;
        (s.sou = tokStructOrUnion()) != nullptr
            && (s.asl = tokAttributeSpecifierList(), true)
            && (s.i = tokIdentifier()) != nullptr)
        return registerToCache(new TOKEN::StructOrUnionSpecifier(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.sou;
        delete s.asl;
        delete s.i;
    }

    return nullptr;
}

TOKEN::EnumSpecifier *TreeGenerator::tokEnumSpecifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::EnumSpecifier)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::EnumSpecifier::Si_el s;
        isMatch(TOKEN::Keyword::Tag::ENUM)
            && (s.asl = tokAttributeSpecifierList(), true)
            && (s.i = tokIdentifier(), true)
            && isMatch(TOKEN::Punctuator::Tag::L_CURLY_BRACKET)
            && (s.el = tokEnumeratorList()) != nullptr
            && (isMatch(TOKEN::Punctuator::Tag::COMMA), true)
            && isMatch(TOKEN::Punctuator::Tag::R_CURLY_BRACKET))
        return registerToCache(new TOKEN::EnumSpecifier(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.asl;
        delete s.i;
        delete s.el;
    }

    if(TOKEN::EnumSpecifier::Si s;
        isMatch(TOKEN::Keyword::Tag::ENUM)
            && (s.asl = tokAttributeSpecifierList(), true)
            && (s.i = tokIdentifier()) != nullptr)
        return registerToCache(new TOKEN::EnumSpecifier(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.asl;
        delete s.i;
    }

    return nullptr;
}

TOKEN::TypedefName *TreeGenerator::tokTypedefName()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::TypedefName)
    std::size_t beginIdx{mIdx};

    if(TOKEN::Identifier *i = tokIdentifier();
        i != nullptr)
        return registerToCache(new TOKEN::TypedefName(i), beginIdx);
    else
        return nullptr;
}

TOKEN::TypeName *TreeGenerator::tokTypeName()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::TypeName)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    TOKEN::SpecifierQualifierList *sql = nullptr;
    TOKEN::AbstractDeclarator *ad = nullptr;

    if((sql = tokSpecifierQualifierList()) != nullptr
        && (ad = tokAbstractDeclarator(), true))
        return registerToCache(new TOKEN::TypeName(sql, ad), beginIdx);
    else
    {
        mIdx = pre;
        delete sql;
        delete ad;
    }

    return nullptr;
}

TOKEN::Initializer *TreeGenerator::tokInitializer()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Initializer)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::AssignmentExpression *ae = nullptr;
        (ae = tokAssignmentExpression()) != nullptr)
        return registerToCache(new TOKEN::Initializer(ae), beginIdx);
    else
    {
        mIdx = pre;
        delete ae;
    }

    if(TOKEN::InitializerList *il = nullptr;
        isMatch(TOKEN::Punctuator::Tag::L_CURLY_BRACKET)
            && (il = tokInitializerList(), true)
            && (isMatch(TOKEN::Punctuator::Tag::COMMA), true)
            && isMatch(TOKEN::Punctuator::Tag::R_CURLY_BRACKET))
        return registerToCache(new TOKEN::Initializer(il), beginIdx);
    else
    {
        mIdx = pre;
        delete il;
    }

    return nullptr;
}

TOKEN::LogicalORExpression *TreeGenerator::tokLogicalORExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::LogicalORExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::LogicalANDExpression*> seq;

    TOKEN::LogicalANDExpression *lande = tokLogicalANDExpression();
    if(lande != nullptr)
        seq.push_back(lande);
    else
        return nullptr;
    
    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::OR)
            && (lande = tokLogicalANDExpression()) != nullptr)
            seq.push_back(lande);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::LogicalORExpression(std::move(seq)), beginIdx);
}

TOKEN::Expression *TreeGenerator::tokExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Expression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::AssignmentExpression*> seq;
    
    TOKEN::AssignmentExpression *ae = tokAssignmentExpression();
    if(ae != nullptr)
        seq.push_back(ae);
    else
        return nullptr;

    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::COMMA)
            && (ae = tokAssignmentExpression()) != nullptr)
            seq.push_back(ae);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::Expression(std::move(seq)), beginIdx);
}

TOKEN::TypeQualifierList *TreeGenerator::tokTypeQualifierList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::TypeQualifierList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::TypeQualifier*> seq;
    for(TOKEN::TypeQualifier *tq = tokTypeQualifier();
        tq != nullptr;
        tq = tokTypeQualifier())
        seq.push_back(tq);
    
    if(!seq.empty())
        return registerToCache(new TOKEN::TypeQualifierList(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::AssignmentExpression *TreeGenerator::tokAssignmentExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AssignmentExpression)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::AssignmentExpression::Sue_ao_ae s;
        (s.ue = tokUnaryExpression()) != nullptr
            && (s.ao = tokAssignmentOperator()) != nullptr
            && (s.ae = tokAssignmentExpression()) != nullptr)
        return registerToCache(new TOKEN::AssignmentExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ue;
        delete s.ao;
        delete s.ae;
    }

    if(TOKEN::AssignmentExpression::Sce s;
        (s.ce = tokConditionalExpression()) != nullptr)
        return registerToCache(new TOKEN::AssignmentExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ce;
    }

    return nullptr;
}

TOKEN::ParameterTypeList *TreeGenerator::tokParameterTypeList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ParameterTypeList)
    std::size_t beginIdx{mIdx};

    if(TOKEN::ParameterList *pl = tokParameterList();
        pl != nullptr)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::COMMA)
            && isMatch(TOKEN::Punctuator::Tag::TRIPLE_PERIOD))
            return registerToCache(new TOKEN::ParameterTypeList(pl, true), beginIdx);
        else if(mIdx = pre, true)
            return registerToCache(new TOKEN::ParameterTypeList(pl, false), beginIdx);
    }

    return nullptr;
}

TOKEN::IdentifierList *TreeGenerator::tokIdentifierList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::IdentifierList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::Identifier*> seq;

    TOKEN::Identifier *i = tokIdentifier();
    if(i != nullptr)
        seq.push_back(i);
    else
        return nullptr;

    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::COMMA)
            && (i = tokIdentifier()) != nullptr)
            seq.push_back(i);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::IdentifierList(std::move(seq)), beginIdx);
}

TOKEN::Identifier *TreeGenerator::tokIdentifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Identifier)
    std::size_t beginIdx{mIdx};

    if(mIdx < mSeq.get().size()
        && std::holds_alternative<TOKEN::Identifier*>(mSeq.get()[mIdx]->var))
    {
        if(TOKEN::Keyword::STR_KEYWORD_MAP.find(TOKEN::str(mSeq.get()[mIdx])) == TOKEN::Keyword::STR_KEYWORD_MAP.end())
            return mIdx++, registerToCache(std::get<TOKEN::Identifier*>(mSeq.get()[mIdx - 1]->var)->copy(), beginIdx);
    }

    return nullptr;
}

TOKEN::BlockItem *TreeGenerator::tokBlockItem()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::BlockItem)
    std::size_t beginIdx{mIdx};

    if(auto *s{tokStatement()};
        bool(s))
        return registerToCache(new TOKEN::BlockItem{s}, beginIdx);
    else if(auto *d{tokDeclaration()};
        bool(d))
        return registerToCache(new TOKEN::BlockItem{d}, beginIdx);
    else
        return nullptr;
}

TOKEN::StructOrUnion *TreeGenerator::tokStructOrUnion()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::StructOrUnion)
    std::size_t beginIdx{mIdx};

    TOKEN::StructOrUnion::Tag tag = TOKEN::StructOrUnion::Tag::NONE;

    if(isMatch(TOKEN::Keyword::Tag::STRUCT))
        tag = TOKEN::StructOrUnion::Tag::STRUCT;
    else if(isMatch(TOKEN::Keyword::Tag::UNION))
        tag = TOKEN::StructOrUnion::Tag::UNION;
    
    if(tag != TOKEN::StructOrUnion::Tag::NONE)
        return registerToCache(new TOKEN::StructOrUnion(tag), beginIdx);
    else
        return nullptr;
}

TOKEN::StructDeclarationList *TreeGenerator::tokStructDeclarationList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::StructDeclarationList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::StructDeclaration*> seq;
    
    for(TOKEN::StructDeclaration *sd = tokStructDeclaration();
        sd != nullptr;
        sd = tokStructDeclaration())
        seq.push_back(sd);
    
    if(!seq.empty())
        return registerToCache(new TOKEN::StructDeclarationList(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::EnumeratorList *TreeGenerator::tokEnumeratorList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::EnumeratorList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::Enumerator*> seq;

    TOKEN::Enumerator *e = tokEnumerator();
    if(e != nullptr)
        seq.push_back(e);
    else
        return nullptr;
    
    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::COMMA)
            && (e = tokEnumerator()) != nullptr)
            seq.push_back(e);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::EnumeratorList(std::move(seq)), beginIdx);
}

TOKEN::SpecifierQualifierList *TreeGenerator::tokSpecifierQualifierList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::SpecifierQualifierList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::SpecifierQualifierList::Var> seq;

    bool hasTypeSpecifier{false};
    while(true)
    {
        TOKEN::TypeSpecifier *ts{nullptr};
        TOKEN::TypeQualifier *tq{nullptr};
        TOKEN::AttributeSpecifierList *asl{nullptr};
        if((ts = tokTypeSpecifier()))
        {
            hasTypeSpecifier = true;
            seq.emplace_back(ts);
        }
        else if((tq = tokTypeQualifier()))
            seq.emplace_back(tq);
        else if((asl = tokAttributeSpecifierList()))
            seq.emplace_back(asl);
        else
            break;

        if(hasTypeSpecifier)
        {
            std::size_t preIdx{mIdx};
            if(auto *sdl{tokStructDeclaratorList()};
                sdl != nullptr)
            {
                delete sdl;
                mIdx = preIdx;
                break;
            }
        }
    }

    if(!seq.empty())
        return registerToCache(new TOKEN::SpecifierQualifierList(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::AbstractDeclarator *TreeGenerator::tokAbstractDeclarator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AbstractDeclarator)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::AbstractDeclarator::Sp_dad s;
        (s = tokPointer(), true)
            && (s.dad = tokDirectAbstractDeclarator()) != nullptr)
        return registerToCache(new TOKEN::AbstractDeclarator(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.p;
        delete s.dad;
    }

    if(TOKEN::AbstractDeclarator::Sp s;
        (s.p = tokPointer()) != nullptr)
        return registerToCache(new TOKEN::AbstractDeclarator(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.p;
    }

    return nullptr;
}

TOKEN::InitializerList *TreeGenerator::tokInitializerList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::InitializerList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::InitializerList::Sd_i> seq;

    bool isFirst{true};
    while(true)
    {
        std::size_t pre = mIdx;

        if(!isFirst && !isMatch(TOKEN::Punctuator::Tag::COMMA))
            break;

        if(TOKEN::InitializerList::Sd_i s;
            (s.d = tokDesignation(), true)
                && (s.i = tokInitializer()) != nullptr)
            seq.push_back(s);
        else
        {
            mIdx = pre;
            delete s.d;
            delete s.i;
            break;
        }

        isFirst = false;
    }

    if(!seq.empty())
        return registerToCache(new TOKEN::InitializerList(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::LogicalANDExpression *TreeGenerator::tokLogicalANDExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::LogicalANDExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::InclusiveORExpression*> seq;

    TOKEN::InclusiveORExpression *iore = tokInclusiveORExpression();
    if(iore != nullptr)
        seq.push_back(iore);
    else
        return nullptr;
    
    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::AND)
            && (iore = tokInclusiveORExpression()) != nullptr)
            seq.push_back(iore);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::LogicalANDExpression(std::move(seq)), beginIdx);
}

TOKEN::UnaryExpression *TreeGenerator::tokUnaryExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::UnaryExpression)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::UnaryExpression::Spe s;
        (s.pe = tokPostfixExpression()) != nullptr)
        return registerToCache(new TOKEN::UnaryExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.pe;
    }

    if(TOKEN::UnaryExpression::Si_ue s;
        isMatch(TOKEN::Punctuator::Tag::INCREMENT)
            && (s.ue = tokUnaryExpression()) != nullptr)
        return registerToCache(new TOKEN::UnaryExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ue;
    }

    if(TOKEN::UnaryExpression::Sd_ue s;
        isMatch(TOKEN::Punctuator::Tag::DECREMENT)
            && (s.ue = tokUnaryExpression()) != nullptr)
        return registerToCache(new TOKEN::UnaryExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ue;
    }

    if(TOKEN::UnaryExpression::Suo_ce s;
        (s.uo = tokUnaryOperator()) != nullptr
        && (s.ce = tokCastExpression()) != nullptr)
        return registerToCache(new TOKEN::UnaryExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.uo;
        delete s.ce;
    }

    if(TOKEN::UnaryExpression::Ss_ue s;
        isMatch(TOKEN::Keyword::Tag::SIZEOF)
            && (s.ue = tokUnaryExpression()) != nullptr)
        return registerToCache(new TOKEN::UnaryExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ue;
    }

    if(TOKEN::UnaryExpression::Ss_tn s;
        isMatch(TOKEN::Keyword::Tag::SIZEOF)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.tn = tokTypeName()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return registerToCache(new TOKEN::UnaryExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.tn;
    }

    if(TOKEN::UnaryExpression::Sa_tn s;
        isMatch(TOKEN::Keyword::Tag::ALIGNOF)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.tn = tokTypeName()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return registerToCache(new TOKEN::UnaryExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.tn;
    }

    return nullptr;
}

TOKEN::AssignmentOperator *TreeGenerator::tokAssignmentOperator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AssignmentOperator)
    std::size_t beginIdx{mIdx};

    TOKEN::AssignmentOperator::Tag tag = TOKEN::AssignmentOperator::Tag::NONE;

    if(isMatch(TOKEN::Punctuator::Tag::ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::ASSIGNMENT;
    else if(isMatch(TOKEN::Punctuator::Tag::ASTERISK_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::MULTIPLICATION;
    else if(isMatch(TOKEN::Punctuator::Tag::SLASH_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::DIVISION;
    else if(isMatch(TOKEN::Punctuator::Tag::PERCENT_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::REMAINDER;
    else if(isMatch(TOKEN::Punctuator::Tag::PLUS_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::ADDITION;
    else if(isMatch(TOKEN::Punctuator::Tag::MINUS_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::SUBTRACTION;
    else if(isMatch(TOKEN::Punctuator::Tag::L_SHIFT_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::LEFT_SHIFT;
    else if(isMatch(TOKEN::Punctuator::Tag::R_SHIFT_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::RIGHT_SHIFT;
    else if(isMatch(TOKEN::Punctuator::Tag::AND_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::AND;
    else if(isMatch(TOKEN::Punctuator::Tag::XOR_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::XOR;
    else if(isMatch(TOKEN::Punctuator::Tag::BITOR_ASSIGNMENT))
        tag = TOKEN::AssignmentOperator::Tag::OR;

    if(tag != TOKEN::AssignmentOperator::Tag::NONE)
        return registerToCache(new TOKEN::AssignmentOperator(tag), beginIdx);
    else
        return nullptr;
}

TOKEN::ParameterList *TreeGenerator::tokParameterList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ParameterList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::ParameterDeclaration*> seq;

    TOKEN::ParameterDeclaration *pd = tokParameterDeclaration();
    if(pd != nullptr)
        seq.push_back(pd);
    else
        return nullptr;

    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::COMMA)
            && (pd = tokParameterDeclaration()) != nullptr)
            seq.push_back(pd);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::ParameterList(std::move(seq)), beginIdx);
}

TOKEN::Statement *TreeGenerator::tokStatement()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Statement)
    std::size_t beginIdx{mIdx};

    if(TOKEN::LabeledStatement *ls = tokLabeledStatement();
        ls != nullptr)
        return registerToCache(new TOKEN::Statement(ls), beginIdx);
    else if(TOKEN::CompoundStatement *cs = tokCompoundStatement();
        cs != nullptr)
        return registerToCache(new TOKEN::Statement(cs), beginIdx);
    else if(TOKEN::ExpressionStatement *es = tokExpressionStatement();
        es != nullptr)
        return registerToCache(new TOKEN::Statement(es), beginIdx);
    else if(TOKEN::SelectionStatement *ss = tokSelectionStatement();
        ss != nullptr)
        return registerToCache(new TOKEN::Statement(ss), beginIdx);
    else if(TOKEN::IterationStatement *is = tokIterationStatement();
        is != nullptr)
        return registerToCache(new TOKEN::Statement(is), beginIdx);
    else if(TOKEN::JumpStatement *js = tokJumpStatement();
        js != nullptr)
        return registerToCache(new TOKEN::Statement(js), beginIdx);
    else if(TOKEN::AttributeStatement *as{tokAttributeStatement()};
        as != nullptr)
        return registerToCache(new TOKEN::Statement{as}, beginIdx);
    else if(TOKEN::AsmStatement *as{tokAsmStatement()};
        as != nullptr)
        return registerToCache(new TOKEN::Statement{as}, beginIdx);
    
    return nullptr;
}

TOKEN::StructDeclaration *TreeGenerator::tokStructDeclaration()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::StructDeclaration)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::StructDeclaration::Ssql_sdl s;
        (s.sql = tokSpecifierQualifierList()) != nullptr
            && (s.sdl = tokStructDeclaratorList(), true)
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return registerToCache(new TOKEN::StructDeclaration(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.sql;
        delete s.sdl;
    }

    if(TOKEN::StructDeclaration::Ssad s;
        (s.sad = tokStaticAssertDeclaration()) != nullptr)
        return registerToCache(new TOKEN::StructDeclaration(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.sad;
    }

    return nullptr;
}

TOKEN::Enumerator *TreeGenerator::tokEnumerator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Enumerator)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::Enumerator::Sec_ce s;
        (s.ec = tokEnumerationConstant()) != nullptr
            && (s.asl = tokAttributeSpecifierList(), true)
            && isMatch(TOKEN::Punctuator::Tag::ASSIGNMENT)
            && (s.ce = tokConstantExpression()) != nullptr)
        return registerToCache(new TOKEN::Enumerator(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ec;
        delete s.asl;
        delete s.ce;
    }

    if(TOKEN::Enumerator::Sec s;
        (s.ec = tokEnumerationConstant()) != nullptr
        && (s.asl = tokAttributeSpecifierList(), true))
        return registerToCache(new TOKEN::Enumerator(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ec;
        delete s.asl;
    }

    return nullptr;
}

TOKEN::DirectAbstractDeclarator *TreeGenerator::tokDirectAbstractDeclarator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::DirectAbstractDeclarator)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    std::vector<TOKEN::DirectAbstractDeclarator::Var> seq;

    if(TOKEN::DirectAbstractDeclarator::Sad s;
        isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.ad = tokAbstractDeclarator()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        seq.emplace_back(s);
    else
        mIdx = pre;

    while(true)
    {
        pre = mIdx;

        if(TOKEN::DirectAbstractDeclarator::Stql_ae s;
            isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
                && (s.tql = tokTypeQualifierList(), true)
                && (s.ae = tokAssignmentExpression(), true)
                && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET)
                && (s.hasStatic = false, true))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.tql;
            delete s.ae;
        }

        if(TOKEN::DirectAbstractDeclarator::Stql_ae s;
            isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
                && isMatch(TOKEN::Keyword::Tag::STATIC)
                && (s.tql = tokTypeQualifierList(), true)
                && (s.ae = tokAssignmentExpression()) != nullptr
                && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET)
                && (s.hasStatic = true, true))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.tql;
            delete s.ae;
        }

        if(TOKEN::DirectAbstractDeclarator::Stql_ae s;
            isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
                && (s.tql = tokTypeQualifierList()) != nullptr
                && isMatch(TOKEN::Keyword::Tag::STATIC)
                && (s.ae = tokAssignmentExpression()) != nullptr
                && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET)
                && (s.hasStatic = true))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.tql;
            delete s.ae;
        }

        if(isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
            && isMatch(TOKEN::Punctuator::Tag::ASTERISK)
            && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET))
        {
            seq.emplace_back(TOKEN::DirectAbstractDeclarator::Sp());
            continue;
        }
        else
            mIdx = pre;

        if(TOKEN::DirectAbstractDeclarator::Sptl s;
            isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
                && (s.ptl = tokParameterTypeList(), true)
                && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.ptl;
        }

        break;
    }

    if(!seq.empty())
        return registerToCache(new TOKEN::DirectAbstractDeclarator(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::Designation *TreeGenerator::tokDesignation()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Designation)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    TOKEN::DesignatorList *dl = nullptr;
    
    if((dl = tokDesignatorList()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::ASSIGNMENT))
        return registerToCache(new TOKEN::Designation(dl), beginIdx);
    else
    {
        mIdx = pre;
        delete dl;
    }

    return nullptr;
}

TOKEN::InclusiveORExpression *TreeGenerator::tokInclusiveORExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::InclusiveORExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::ExclusiveORExpression*> seq;

    TOKEN::ExclusiveORExpression *eore = tokExclusiveORExpression();
    if(eore != nullptr)
        seq.push_back(eore);
    else
        return nullptr;

    while(true)
    {
        std::size_t pre = mIdx;

        if(isMatch(TOKEN::Punctuator::Tag::BITOR)
            && (eore = tokExclusiveORExpression()) != nullptr)
            seq.push_back(eore);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::InclusiveORExpression(std::move(seq)), beginIdx);
}

TOKEN::PostfixExpression *TreeGenerator::tokPostfixExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::PostfixExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::PostfixExpression::Var> seq;
    std::size_t pre = mIdx;

    if(TOKEN::PostfixExpression::Spe s;
        (s.pe = tokPrimaryExpression()) != nullptr)
        seq.emplace_back(s);
    else if(TOKEN::PostfixExpression::Stn_il s;
        (mIdx = pre, true)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.tn = tokTypeName()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && isMatch(TOKEN::Punctuator::Tag::L_CURLY_BRACKET)
            && (s.il = tokInitializerList()) != nullptr
            && (isMatch(TOKEN::Punctuator::Tag::COMMA), true)
            && isMatch(TOKEN::Punctuator::Tag::R_CURLY_BRACKET))
        seq.emplace_back(s);
    else
        return mIdx = pre, nullptr;

    while(true)
    {
        pre = mIdx;

        if(TOKEN::PostfixExpression::Se s;
            isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
                && (s.e = tokExpression()) != nullptr
                && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.e;
        }

        if(TOKEN::PostfixExpression::Sael s;
            isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
                && (s.ael = tokArgumentExpressionList(), true)
                && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.ael;
        }

        if(TOKEN::PostfixExpression::Sp_i s;
            isMatch(TOKEN::Punctuator::Tag::PERIOD)
                && (s.i = tokIdentifier()) != nullptr)
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.i;
        }

        if(TOKEN::PostfixExpression::Sa_i s;
            isMatch(TOKEN::Punctuator::Tag::ARROW)
                && (s.i = tokIdentifier()) != nullptr)
        {
            seq.emplace_back(s);
            continue;
        }
        else
        {
            mIdx = pre;
            delete s.i;
        }

        if(isMatch(TOKEN::Punctuator::Tag::INCREMENT))
        {
            seq.emplace_back(TOKEN::PostfixExpression::Si());
            continue;
        }
        else
            mIdx = pre;

        if(isMatch(TOKEN::Punctuator::Tag::DECREMENT))
        {
            seq.emplace_back(TOKEN::PostfixExpression::Sd());
            continue;
        }
        else
            mIdx = pre;

        break;
    }

    return registerToCache(new TOKEN::PostfixExpression(std::move(seq)), beginIdx);
}

TOKEN::CastExpression *TreeGenerator::tokCastExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::CastExpression)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::CastExpression::Stn_ce s;
        isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.tn = tokTypeName()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.ce = tokCastExpression()) != nullptr)
        return registerToCache(new TOKEN::CastExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.tn;
        delete s.ce;
    }

    if(TOKEN::CastExpression::Sue s;
        (s.ue = tokUnaryExpression()) != nullptr)
        return registerToCache(new TOKEN::CastExpression(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ue;
    }

    return nullptr;
}

TOKEN::UnaryOperator *TreeGenerator::tokUnaryOperator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::UnaryOperator)
    std::size_t beginIdx{mIdx};

    TOKEN::UnaryOperator::Tag tag = TOKEN::UnaryOperator::Tag::NONE;

    if(isMatch(TOKEN::Punctuator::Tag::BITAND))
        tag = TOKEN::UnaryOperator::Tag::ADDRESS;
    else if(isMatch(TOKEN::Punctuator::Tag::ASTERISK))
        tag = TOKEN::UnaryOperator::Tag::POINTER;
    else if(isMatch(TOKEN::Punctuator::Tag::PLUS))
        tag = TOKEN::UnaryOperator::Tag::PLUS;
    else if(isMatch(TOKEN::Punctuator::Tag::MINUS))
        tag = TOKEN::UnaryOperator::Tag::MINUS;
    else if(isMatch(TOKEN::Punctuator::Tag::COMPL))
        tag = TOKEN::UnaryOperator::Tag::COMPLEMENT;
    else if(isMatch(TOKEN::Punctuator::Tag::NOT))
        tag = TOKEN::UnaryOperator::Tag::NOT;
    
    if(tag != TOKEN::UnaryOperator::Tag::NONE)
        return registerToCache(new TOKEN::UnaryOperator(tag), beginIdx);
    else
        return nullptr;
}

TOKEN::ParameterDeclaration *TreeGenerator::tokParameterDeclaration()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ParameterDeclaration)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::ParameterDeclaration::Sds_d s;
        (s.ds = tokDeclarationSpecifiers()) != nullptr
            && (s.d = tokDeclarator()) != nullptr)
        return registerToCache(new TOKEN::ParameterDeclaration(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ds;
        delete s.d;
    }

    if(TOKEN::ParameterDeclaration::Sds_ad s;
        (s.ds = tokDeclarationSpecifiers()) != nullptr
            && (s.ad = tokAbstractDeclarator(), true))
        return registerToCache(new TOKEN::ParameterDeclaration(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ds;
        delete s.ad;
    }

    return nullptr;
}

TOKEN::LabeledStatement *TreeGenerator::tokLabeledStatement()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::LabeledStatement)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::LabeledStatement::Si_s s;
        (s.i = tokIdentifier()) != nullptr
            && (s.asl = tokAttributeSpecifierList(), true)
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.s = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::LabeledStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.i;
        delete s.asl;
        delete s.s;
    }

    if(TOKEN::LabeledStatement::Sce_s s;
        isMatch(TOKEN::Keyword::Tag::CASE)
            && (s.ce = tokConstantExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.s = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::LabeledStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ce;
        delete s.s;
    }

    if(TOKEN::LabeledStatement::Sce_ce_s s;
        isMatch(TOKEN::Keyword::Tag::CASE)
            && (s.ce0 = tokConstantExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::TRIPLE_PERIOD)
            && (s.ce1 = tokConstantExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.s = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::LabeledStatement{s}, beginIdx);
    else
    {
        mIdx = pre;
        delete s.ce0;
        delete s.ce1;
        delete s.s;
    }

    if(TOKEN::LabeledStatement::Ss s;
        isMatch(TOKEN::Keyword::Tag::DEFAULT)
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.s = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::LabeledStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.s;
    }

    return nullptr;
}

TOKEN::ExpressionStatement *TreeGenerator::tokExpressionStatement()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ExpressionStatement)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    TOKEN::Expression *e = nullptr;

    if((e = tokExpression(), true)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return registerToCache(new TOKEN::ExpressionStatement(e), beginIdx);
    else
        return mIdx = pre, nullptr;
}

TOKEN::SelectionStatement *TreeGenerator::tokSelectionStatement()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::SelectionStatement)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::SelectionStatement::Si_e_s_s s;
        isMatch(TOKEN::Keyword::Tag::IF)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.s0 = tokStatement()) != nullptr
            && isMatch(TOKEN::Keyword::Tag::ELSE)
            && (s.s1 = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::SelectionStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.e;
        delete s.s0;
        delete s.s1;
    }

    if(TOKEN::SelectionStatement::Si_e_s s;
        isMatch(TOKEN::Keyword::Tag::IF)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.s = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::SelectionStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.e;
        delete s.s;
    }

    if(TOKEN::SelectionStatement::Ss_e_s s;
        isMatch(TOKEN::Keyword::Tag::SWITCH)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.s = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::SelectionStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.e;
        delete s.s;
    }

    return nullptr;
}

TOKEN::IterationStatement *TreeGenerator::tokIterationStatement()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::IterationStatement)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::IterationStatement::Sw_e_s s;
        isMatch(TOKEN::Keyword::Tag::WHILE)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.s = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::IterationStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.e;
        delete s.s;
    }

    if(TOKEN::IterationStatement::Sd_s_e s;
        isMatch(TOKEN::Keyword::Tag::DO)
            && (s.s = tokStatement()) != nullptr
            && isMatch(TOKEN::Keyword::Tag::WHILE)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return registerToCache(new TOKEN::IterationStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.s;
        delete s.e;
    }

    if(TOKEN::IterationStatement::Sf_e_e_e_s s;
        isMatch(TOKEN::Keyword::Tag::FOR)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.e0 = tokExpression(), true)
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON)
            && (s.e1 = tokExpression(), true)
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON)
            && (s.e2 = tokExpression(), true)
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.s = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::IterationStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.e0;
        delete s.e1;
        delete s.e2;
        delete s.s;
    }

    if(TOKEN::IterationStatement::Sf_d_e_e_s s;
        isMatch(TOKEN::Keyword::Tag::FOR)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.d = tokDeclaration()) != nullptr
            && (s.e0 = tokExpression(), true)
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON)
            && (s.e1 = tokExpression(), true)
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.s = tokStatement()) != nullptr)
        return registerToCache(new TOKEN::IterationStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.d;
        delete s.e0;
        delete s.e1;
        delete s.s;
    }

    return nullptr;
}

TOKEN::JumpStatement *TreeGenerator::tokJumpStatement()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::JumpStatement)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::JumpStatement::Sg_i s;
        isMatch(TOKEN::Keyword::Tag::GOTO)
            && (s.i = tokIdentifier()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return registerToCache(new TOKEN::JumpStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.i;
    }

    if(isMatch(TOKEN::Keyword::Tag::CONTINUE)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return registerToCache(new TOKEN::JumpStatement(TOKEN::JumpStatement::Sc()), beginIdx);
    else
        mIdx = pre;
    
    if(isMatch(TOKEN::Keyword::Tag::BREAK)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return registerToCache(new TOKEN::JumpStatement(TOKEN::JumpStatement::Sb()), beginIdx);
    else
        mIdx = pre;

    if(TOKEN::JumpStatement::Sr_e s;
        isMatch(TOKEN::Keyword::Tag::RETURN)
            && (s.e = tokExpression(), true)
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return registerToCache(new TOKEN::JumpStatement(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.e;
    }

    return nullptr;
}

TOKEN::StructDeclaratorList *TreeGenerator::tokStructDeclaratorList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::StructDeclaratorList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::StructDeclarator*> seq;
    
    TOKEN::StructDeclarator *sd = tokStructDeclarator();
    if(sd != nullptr)
        seq.push_back(sd);
    else
        return nullptr;

    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::COMMA)
            && (sd = tokStructDeclarator()) != nullptr)
            seq.push_back(sd);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::StructDeclaratorList(std::move(seq)), beginIdx);
}

TOKEN::EnumerationConstant *TreeGenerator::tokEnumerationConstant()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::EnumerationConstant)
    std::size_t beginIdx{mIdx};

    if(TOKEN::Identifier *i = tokIdentifier();
        i != nullptr)
        return registerToCache(new TOKEN::EnumerationConstant(i), beginIdx);
    else
        return nullptr;
}

TOKEN::DesignatorList *TreeGenerator::tokDesignatorList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::DesignatorList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::Designator*> seq;
    for(TOKEN::Designator *d = tokDesignator();
        d != nullptr;
        d = tokDesignator())
        seq.push_back(d);
    
    if(!seq.empty())
        return registerToCache(new TOKEN::DesignatorList(std::move(seq)), beginIdx);
    else
        return nullptr;
}

TOKEN::ExclusiveORExpression *TreeGenerator::tokExclusiveORExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ExclusiveORExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::ANDExpression*> seq;

    TOKEN::ANDExpression *ande = tokANDExpression();
    if(ande != nullptr)
        seq.push_back(ande);
    else
        return nullptr;

    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::XOR)
            && (ande = tokANDExpression()) != nullptr)
            seq.push_back(ande);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::ExclusiveORExpression(std::move(seq)), beginIdx);
}

TOKEN::PrimaryExpression *TreeGenerator::tokPrimaryExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::PrimaryExpression)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::Identifier *i = tokIdentifier();
        i != nullptr)
        return registerToCache(new TOKEN::PrimaryExpression(i), beginIdx);
    else if(TOKEN::Constant *c = tokConstant();
        c != nullptr)
        return registerToCache(new TOKEN::PrimaryExpression(c), beginIdx);
    else if(TOKEN::StringLiteral *sl = tokStringLiteral();
        sl != nullptr)
        return registerToCache(new TOKEN::PrimaryExpression(sl), beginIdx);
    
    if(TOKEN::Expression *e = nullptr;
        isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return registerToCache(new TOKEN::PrimaryExpression(e), beginIdx);
    else
    {
        mIdx = pre;
        delete e;
    }

    if(TOKEN::GenericSelection *gs = tokGenericSelection();
        gs != nullptr)
        return registerToCache(new TOKEN::PrimaryExpression(gs), beginIdx);
    
    return nullptr;
}

TOKEN::ArgumentExpressionList *TreeGenerator::tokArgumentExpressionList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ArgumentExpressionList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::AssignmentExpression*> seq;

    TOKEN::AssignmentExpression *ae = tokAssignmentExpression();
    if(ae != nullptr)
        seq.push_back(ae);
    else
        return nullptr;

    while(true)
    {
        std::size_t pre = mIdx;
        
        if(isMatch(TOKEN::Punctuator::Tag::COMMA)
            && (ae = tokAssignmentExpression()) != nullptr)
            seq.push_back(ae);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::ArgumentExpressionList(std::move(seq)), beginIdx);
}

TOKEN::StructDeclarator *TreeGenerator::tokStructDeclarator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::StructDeclarator)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::StructDeclarator::Sd_ce s;
        (s.d = tokDeclarator(), true)
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.ce = tokConstantExpression()) != nullptr)
        return registerToCache(new TOKEN::StructDeclarator(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.d;
        delete s.ce;
    }

    if(TOKEN::StructDeclarator::Sd s;
        (s.d = tokDeclarator()) != nullptr)
        return registerToCache(new TOKEN::StructDeclarator(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.d;
    }

    return nullptr;
}

TOKEN::Designator *TreeGenerator::tokDesignator()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Designator)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::ConstantExpression *ce = nullptr;
        isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
            && (ce = tokConstantExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET))
        return registerToCache(new TOKEN::Designator(ce), beginIdx);
    else
    {
        mIdx = pre;
        delete ce;
    }

    if(TOKEN::Identifier *i = nullptr;
        isMatch(TOKEN::Punctuator::Tag::PERIOD)
            && (i = tokIdentifier()) != nullptr)
        return registerToCache(new TOKEN::Designator(i), beginIdx);
    else
    {
        mIdx = pre;
        delete i;
    }

    return nullptr;
}

TOKEN::ANDExpression *TreeGenerator::tokANDExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ANDExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::EqualityExpression*> seq;

    TOKEN::EqualityExpression *ee = tokEqualityExpression();
    if(ee != nullptr)
        seq.push_back(ee);
    else
        return nullptr;

    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::BITAND)
            && (ee = tokEqualityExpression()) != nullptr)
            seq.push_back(ee);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::ANDExpression(std::move(seq)), beginIdx);
}

TOKEN::Constant *TreeGenerator::tokConstant()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Constant)
    std::size_t beginIdx{mIdx};

    if(TOKEN::IntegerConstant *ic = convIntegerConstant();
        ic != nullptr)
        return registerToCache(new TOKEN::Constant(ic), beginIdx);
    else if(TOKEN::FloatingConstant *fc = convFloatingConstant();
        fc != nullptr)
        return registerToCache(new TOKEN::Constant(fc), beginIdx);
    else if(TOKEN::EnumerationConstant *ec = convEnumerationConstant();
        ec != nullptr)
        return registerToCache(new TOKEN::Constant(ec), beginIdx);
    else if(TOKEN::CharacterConstant *cc = convCharacterConstant();
        cc != nullptr)
        return registerToCache(new TOKEN::Constant(cc), beginIdx);
    
    return nullptr;
}

TOKEN::GenericSelection *TreeGenerator::tokGenericSelection()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::GenericSelection)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;
    TOKEN::AssignmentExpression *ae = nullptr;
    TOKEN::GenericAssocList *gal = nullptr;

    if(isMatch(TOKEN::Keyword::Tag::GENERIC)
        && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
        && (ae = tokAssignmentExpression()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::COMMA)
        && (gal = tokGenericAssocList()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return registerToCache(new TOKEN::GenericSelection(ae, gal), beginIdx);
    else
    {
        mIdx = pre;
        delete ae;
        delete gal;
    }

    return nullptr;
}

TOKEN::EqualityExpression *TreeGenerator::tokEqualityExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::EqualityExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::EqualityExpression::Var> seq;

    TOKEN::RelationalExpression *re = tokRelationalExpression();
    if(re != nullptr)
        seq.emplace_back(TOKEN::EqualityExpression::Sre(re));
    else
        return nullptr;
    
    while(true)
    {
        std::size_t pre = mIdx;
        
        if(isMatch(TOKEN::Punctuator::Tag::EQUAL)
            && (re = tokRelationalExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::EqualityExpression::Se_re(re));
            continue;
        }
        else
            mIdx = pre;
        
        if(isMatch(TOKEN::Punctuator::Tag::NOT_EQUAL)
            && (re = tokRelationalExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::EqualityExpression::Sne_re(re));
            continue;
        }
        else
            mIdx = pre;

        break;
    }

    return registerToCache(new TOKEN::EqualityExpression(std::move(seq)), beginIdx);
}

TOKEN::GenericAssocList *TreeGenerator::tokGenericAssocList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::GenericAssocList)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::GenericAssociation*> seq;

    TOKEN::GenericAssociation *ga = tokGenericAssociation();
    if(ga != nullptr)
        seq.push_back(ga);
    else
        return nullptr;
    
    while(true)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::COMMA)
            && (ga = tokGenericAssociation()) != nullptr)
            seq.push_back(ga);
        else
        {
            mIdx = pre;
            break;
        }
    }

    return registerToCache(new TOKEN::GenericAssocList(std::move(seq)), beginIdx);
}

TOKEN::RelationalExpression *TreeGenerator::tokRelationalExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::RelationalExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::RelationalExpression::Var> seq;
    
    TOKEN::ShiftExpression *se = tokShiftExpression();
    if(se != nullptr)
        seq.emplace_back(TOKEN::RelationalExpression::Sse(se));
    else
        return nullptr;
    
    while(true)
    {
        std::size_t pre = mIdx;

        if(isMatch(TOKEN::Punctuator::Tag::LESS)
            && (se = tokShiftExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::RelationalExpression::Sl_se(se));
            continue;
        }
        else
            mIdx = pre;
        
        if(isMatch(TOKEN::Punctuator::Tag::GREATER)
            && (se = tokShiftExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::RelationalExpression::Sg_se(se));
            continue;
        }
        else
            mIdx = pre;

        if(isMatch(TOKEN::Punctuator::Tag::LESS_EQUAL)
            && (se = tokShiftExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::RelationalExpression::Sle_se(se));
            continue;
        }
        else
            mIdx = pre;

        if(isMatch(TOKEN::Punctuator::Tag::GREATER_EQUAL)
            && (se = tokShiftExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::RelationalExpression::Sge_se(se));
            continue;
        }
        else
            mIdx = pre;

        break;
    }

    return registerToCache(new TOKEN::RelationalExpression(std::move(seq)), beginIdx);
}

TOKEN::GenericAssociation *TreeGenerator::tokGenericAssociation()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::GenericAssociation)
    std::size_t beginIdx{mIdx};

    std::size_t pre = mIdx;

    if(TOKEN::GenericAssociation::Stn_ae s;
        (s.tn = tokTypeName()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.ae = tokAssignmentExpression()) != nullptr)
        return registerToCache(new TOKEN::GenericAssociation(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.tn;
        delete s.ae;
    }

    if(TOKEN::GenericAssociation::Sae s;
        (s.ae = tokAssignmentExpression()) != nullptr)
        return registerToCache(new TOKEN::GenericAssociation(s), beginIdx);
    else
    {
        mIdx = pre;
        delete s.ae;
    }

    return nullptr;
}

TOKEN::ShiftExpression *TreeGenerator::tokShiftExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ShiftExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::ShiftExpression::Var> seq;

    TOKEN::AdditiveExpression *ae = tokAdditiveExpression();
    if(ae != nullptr)
        seq.emplace_back(TOKEN::ShiftExpression::Sae(ae));
    else
        return nullptr;
    
    while(true)
    {
        std::size_t pre = mIdx;

        if(isMatch(TOKEN::Punctuator::Tag::L_SHIFT)
            && (ae = tokAdditiveExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::ShiftExpression::Sl_ae(ae));
            continue;
        }
        else
            mIdx = pre;
        
        if(isMatch(TOKEN::Punctuator::Tag::R_SHIFT)
            && (ae = tokAdditiveExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::ShiftExpression::Sr_ae(ae));
            continue;
        }
        else
            mIdx = pre;

        break;
    }

    return registerToCache(new TOKEN::ShiftExpression(std::move(seq)), beginIdx);
}

TOKEN::AdditiveExpression *TreeGenerator::tokAdditiveExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AdditiveExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::AdditiveExpression::Var> seq;

    TOKEN::MultiplicativeExpression *me = tokMultiplicativeExpression();
    if(me != nullptr)
        seq.emplace_back(TOKEN::AdditiveExpression::Sme(me));
    else
        return nullptr;
    
    while(true)
    {
        std::size_t pre = mIdx;
        
        if(isMatch(TOKEN::Punctuator::Tag::PLUS)
            && (me = tokMultiplicativeExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::AdditiveExpression::Sa_me(me));
            continue;
        }
        else
            mIdx = pre;

        if(isMatch(TOKEN::Punctuator::Tag::MINUS)
            && (me = tokMultiplicativeExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::AdditiveExpression::Ss_me(me));
            continue;
        }
        else
            mIdx = pre;

        break;
    }

    return registerToCache(new TOKEN::AdditiveExpression(std::move(seq)), beginIdx);
}

TOKEN::MultiplicativeExpression *TreeGenerator::tokMultiplicativeExpression()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::MultiplicativeExpression)
    std::size_t beginIdx{mIdx};

    std::vector<TOKEN::MultiplicativeExpression::Var> seq;

    TOKEN::CastExpression *ce = tokCastExpression();
    if(ce != nullptr)
        seq.emplace_back(TOKEN::MultiplicativeExpression::Sce(ce));
    else
        return nullptr;
    
    while(true)
    {
        std::size_t pre = mIdx;

        if(isMatch(TOKEN::Punctuator::Tag::ASTERISK)
            && (ce = tokCastExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::MultiplicativeExpression::Sm_ce(ce));
            continue;
        }
        else
            mIdx = pre;

        if(isMatch(TOKEN::Punctuator::Tag::SLASH)
            && (ce = tokCastExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::MultiplicativeExpression::Sd_ce(ce));
            continue;
        }
        else
            mIdx = pre;

        if(isMatch(TOKEN::Punctuator::Tag::PERCENT)
            && (ce = tokCastExpression()) != nullptr)
        {
            seq.emplace_back(TOKEN::MultiplicativeExpression::Sr_ce(ce));
            continue;
        }
        else
            mIdx = pre;

        break;
    }

    return registerToCache(new TOKEN::MultiplicativeExpression(std::move(seq)), beginIdx);
}

TOKEN::Keyword *TreeGenerator::tokKeyword()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::Keyword)
    std::size_t beginIdx{mIdx};

    if(mIdx >= mSeq.get().size())
        return nullptr;

    auto &&pt{mSeq.get()[mIdx]};

    if(!std::holds_alternative<TOKEN::Identifier*>(pt->var))
        return nullptr;

    auto &&iter{TOKEN::Keyword::STR_KEYWORD_MAP.find(TOKEN::str(pt))};

    if(iter == TOKEN::Keyword::STR_KEYWORD_MAP.end())
        return nullptr;
    
    mIdx++;
    return registerToCache(new TOKEN::Keyword{iter->second}, beginIdx);
}

TOKEN::AttributeSpecifier *TreeGenerator::tokAttributeSpecifier()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AttributeSpecifier)
    std::size_t beginIdx{mIdx};

    using namespace TOKEN;

    std::size_t pre{mIdx};
    int numParenthesis{0};

    std::vector<Token*> seq;

    if(isMatch(Keyword::Tag::ATTRIBUTE)
        && isMatch(Punctuator::Tag::L_PARENTHESIS)
        && isMatch(Punctuator::Tag::L_PARENTHESIS))
    {
        while(true)
        {
            if(mIdx >= mSeq.get().size())
            {
                mIdx = pre;
                for(auto &&t : seq)
                    delete t;
                return nullptr;
            }

            std::size_t currentIdx{mIdx};
            if(numParenthesis == 0
                && isMatch(Punctuator::Tag::R_PARENTHESIS)
                && isMatch(Punctuator::Tag::R_PARENTHESIS))
                break;
            else
                mIdx = currentIdx;

            if(isMatch(Punctuator::Tag::L_PARENTHESIS))
            {
                mIdx--;
                seq.push_back(convToken());
                numParenthesis++;
            }
            else if(isMatch(Punctuator::Tag::R_PARENTHESIS))
            {
                mIdx--;
                seq.push_back(convToken());
                numParenthesis--;
            }
            else
                seq.push_back(convToken());
        }
    }
    else
    {
        mIdx = pre;
        return nullptr;
    }

    return registerToCache(new AttributeSpecifier{std::move(seq)}, beginIdx);
}

TOKEN::AttributeSpecifierList *TreeGenerator::tokAttributeSpecifierList()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AttributeSpecifierList)
    std::size_t beginIdx{mIdx};

    using namespace TOKEN;

    std::vector<AttributeSpecifier*> seq;
    for(auto &&as{tokAttributeSpecifier()};
        as != nullptr;
        as = tokAttributeSpecifier())
        seq.push_back(as);
    
    if(seq.empty())
        return nullptr;
    
    return registerToCache(new AttributeSpecifierList{std::move(seq)}, beginIdx);
}

TOKEN::AttributeStatement *TreeGenerator::tokAttributeStatement()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AttributeStatement)
    std::size_t beginIdx{mIdx};

    using namespace TOKEN;

    std::size_t preIdx{mIdx};

    auto *asl{tokAttributeSpecifierList()};
    if(asl != nullptr
        && isMatch(Punctuator::Tag::SEMICOLON))
        return registerToCache(new AttributeStatement{asl}, beginIdx);
    else
    {
        mIdx = preIdx;
        delete asl;
        return nullptr;
    }

    return nullptr;
}

TOKEN::AsmQualifiers *TreeGenerator::tokAsmQualifiers()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AsmQualifiers)
    std::size_t beginIdx{mIdx};

    using namespace TOKEN;
    using AQ = AsmQualifiers;

    std::vector<AQ::Tag> seq;
    
    if(isMatch(Keyword::Tag::VOLATILE))
        seq.push_back(AQ::Tag::VOLATILE);
    else if(isMatch(Keyword::Tag::INLINE))
        seq.push_back(AQ::Tag::INLINE);
    else if(isMatch(Keyword::Tag::GOTO))
        seq.push_back(AQ::Tag::GOTO);
    
    if(!seq.empty())
        return registerToCache(new AsmQualifiers{seq}, beginIdx);
    else
        return nullptr;
}

TOKEN::BasicAsm *TreeGenerator::tokBasicAsm()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::BasicAsm)
    std::size_t beginIdx{mIdx};

    using namespace TOKEN;

    std::size_t preIdx{mIdx};

    BasicAsm *ba{new BasicAsm{}};

    if(isMatch(Keyword::Tag::ASM)
        && (ba->aq = tokAsmQualifiers(), true)
        && isMatch(Punctuator::Tag::L_PARENTHESIS)
        && ((ba->sl = tokStringLiteral()) != nullptr)
        && isMatch(Punctuator::Tag::R_PARENTHESIS))
        return registerToCache(ba, beginIdx);
    else
    {
        mIdx = preIdx;
        delete ba;
        return nullptr;
    }
}

TOKEN::ExtendedAsm *TreeGenerator::tokExtendedAsm()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::ExtendedAsm)
    std::size_t beginIdx{mIdx};

    using namespace TOKEN;

    // this function is not need to free seq's memory
    // even if new Tokens are added to seq.
    auto &&tokTokens{[&](std::vector<Token*> &seq)
        -> bool
    {
        if(!isMatch(Punctuator::Tag::COLON))
            return false;
        
        std::size_t preIdx{mIdx};
        int numParenthesis{0};

        // exit conditions:
        //  numParenthesis is 0
        //  and next token is ':' or ')'
        while(!(numParenthesis == 0
            && (isMatch(Punctuator::Tag::COLON)
                || isMatch(Punctuator::Tag::R_PARENTHESIS))))
        {
            if(mIdx >= mSeq.get().size())
            {
                mIdx = preIdx;
                return false;
            }

            if(isMatch(Punctuator::Tag::L_PARENTHESIS))
                numParenthesis++, mIdx--;
            else if(isMatch(Punctuator::Tag::R_PARENTHESIS))
                numParenthesis--, mIdx--;
            
            if(Token *token{convToken()};
                token != nullptr)
                seq.push_back(token);
            else
            {
                mIdx = preIdx;
                return false;
            }
        }

        // back to before ':' or ')'
        mIdx--;
        return true;
    }};

    std::size_t preIdx{mIdx};

    ExtendedAsm *ea{new ExtendedAsm{}};

    if(!(isMatch(Keyword::Tag::ASM)
        && (ea->aq = tokAsmQualifiers(), true)
        && isMatch(Punctuator::Tag::L_PARENTHESIS)
        && (ea->sl = tokStringLiteral())))
    {
        mIdx = preIdx;
        delete ea;
        return nullptr;
    }

    // output operands
    if(!tokTokens(ea->oo))
    {
        mIdx = preIdx;
        delete ea;
        return nullptr;
    }

    // input operands
    // clobbers
    // goto labels
    tokTokens(ea->io);
    tokTokens(ea->clobbers);
    tokTokens(ea->gl);

    if(isMatch(Punctuator::Tag::R_PARENTHESIS))
        return registerToCache(ea, beginIdx);
    else
    {
        mIdx = preIdx;
        delete ea;
        return nullptr;
    }
}

TOKEN::AsmStatement *TreeGenerator::tokAsmStatement()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::AsmStatement)
    std::size_t beginIdx{mIdx};

    using namespace TOKEN;

    std::size_t preIdx{mIdx};
    AsmStatement *as{new AsmStatement{std::monostate{}}};

    if(as->var.emplace<BasicAsm*>(tokBasicAsm()) == nullptr
        && as->var.emplace<ExtendedAsm*>(tokExtendedAsm()) == nullptr)
    {
        delete as;
        return nullptr;
    }

    if(isMatch(Punctuator::Tag::SEMICOLON))
        return registerToCache(as, beginIdx);
    else
    {
        mIdx = preIdx;
        delete as;
        return nullptr;
    }
}

TOKEN::IncludingFile *TreeGenerator::tokIncludingFile()
{
    IF_CACHE_HAS_TOKEN_RETURN(TOKEN::IncludingFile)
    std::size_t beginIdx{mIdx};

    using namespace TOKEN;

    auto &&getFilename{[&](Punctuator::Tag delimiterTag)
        -> std::string
        {
            std::string filename;
            for(; mIdx < mSeq.get().size(); mIdx++)
            {
                if(isMatch(delimiterTag))
                {
                    mIdx--;
                    break;
                }
                
                filename += TOKEN::str(mSeq.get()[mIdx]);
            }

            return filename;
        }};

    std::size_t preIdx{mIdx};

    std::string filename;

    if(!isMatch(Punctuator::Tag::AT))
        return nullptr;
    
    // @<includingFile>
    if(isMatch(Punctuator::Tag::LESS))
    {
        filename.push_back('<');
        filename += getFilename(Punctuator::Tag::GREATER);
        filename.push_back('>');
        if(!isMatch(Punctuator::Tag::GREATER))
            return mIdx = preIdx, nullptr;
    }
    // @"includeFile"
    else if(auto &&sl{tokStringLiteral()};
        sl != nullptr)
    {
        filename = TOKEN::str(sl);
        delete sl;
    }
    else
        return mIdx = preIdx, nullptr;

    return registerToCache(new IncludingFile{std::move(filename)}, beginIdx);
}

TOKEN::IntegerConstant *TreeGenerator::convIntegerConstant()
{
    if(mIdx < mSeq.get().size()
        && std::holds_alternative<TOKEN::PPNumber*>(mSeq.get()[mIdx]->var))
    {
        std::string str(TOKEN::str(mSeq.get()[mIdx]));
        std::size_t idx = 0;
        TOKEN::IntegerConstant *ic = TOKENIZER::decIntegerConstant(str, idx);
        if(ic != nullptr
            && idx == str.size())
            return mIdx++, ic;
        else
            delete ic;
    }

    return nullptr;
}

TOKEN::FloatingConstant *TreeGenerator::convFloatingConstant()
{
    if(mIdx < mSeq.get().size()
        && std::holds_alternative<TOKEN::PPNumber*>(mSeq.get()[mIdx]->var))
    {
        std::string str(TOKEN::str(mSeq.get()[mIdx]));
        std::size_t idx = 0;
        TOKEN::FloatingConstant *fc = TOKENIZER::decFloatingConstant(str, idx);
        if(fc != nullptr
            && idx == str.size())
            return mIdx++, fc;
        else
            delete fc;
    }

    return nullptr;
}

TOKEN::EnumerationConstant *TreeGenerator::convEnumerationConstant()
{
    if(TOKEN::Identifier *i = tokIdentifier();
        i != nullptr)
        return new TOKEN::EnumerationConstant(i);
    else
        return nullptr;
}

TOKEN::CharacterConstant *TreeGenerator::convCharacterConstant()
{
    if(mIdx < mSeq.get().size()
        && std::holds_alternative<TOKEN::CharacterConstant*>(mSeq.get()[mIdx]->var))
        return mIdx++, std::get<TOKEN::CharacterConstant*>(mSeq.get()[mIdx - 1]->var)->copy();
    else
        return nullptr;
}

TOKEN::Token *TreeGenerator::convToken()
{
    if(mIdx >= mSeq.get().size())
        return nullptr;

    TOKEN::Token *returnToken{new TOKEN::Token{}};
    if(std::holds_alternative<TOKEN::Identifier*>(mSeq.get()[mIdx]->var))
    {
        auto &&iter{TOKEN::Keyword::STR_KEYWORD_MAP.find(TOKEN::str(std::get<TOKEN::Identifier*>(mSeq.get()[mIdx]->var)))};
        if(iter != TOKEN::Keyword::STR_KEYWORD_MAP.end())
            returnToken->var.emplace<TOKEN::Keyword*>(new TOKEN::Keyword{iter->second});
        else
            returnToken->var.emplace<TOKEN::Identifier*>(std::get<TOKEN::Identifier*>(mSeq.get()[mIdx]->var)->copy());

        mIdx++;
    }
    else if(std::holds_alternative<TOKEN::PPNumber*>(mSeq.get()[mIdx]->var)
        || std::holds_alternative<TOKEN::CharacterConstant*>(mSeq.get()[mIdx]->var))
    {
        if(returnToken->var.emplace<TOKEN::Constant*>(tokConstant()) == nullptr)
            returnToken->var.emplace<std::monostate>(std::monostate{});

        // mIdx is increased by tokConstant()
    }
    else if(std::holds_alternative<TOKEN::StringLiteral*>(mSeq.get()[mIdx]->var))
    {
        returnToken->var.emplace<TOKEN::StringLiteral*>(std::get<TOKEN::StringLiteral*>(mSeq.get()[mIdx]->var)->copy());
        mIdx++;
    }
    else if(std::holds_alternative<TOKEN::Punctuator*>(mSeq.get()[mIdx]->var))
    {
        returnToken->var.emplace<TOKEN::Punctuator*>(std::get<TOKEN::Punctuator*>(mSeq.get()[mIdx]->var)->copy());
        mIdx++;
    }

    if(!std::holds_alternative<std::monostate>(returnToken->var))
        return returnToken;
    else
    {
        delete returnToken;
        return nullptr;
    }
}

bool TreeGenerator::isMatch(TOKEN::Keyword::Tag tag)
{
    if(mIdx < mSeq.get().size()
        && std::holds_alternative<TOKEN::Identifier*>(mSeq.get()[mIdx]->var))
    {
        if(auto iter = TOKEN::Keyword::STR_KEYWORD_MAP.find(TOKEN::str(mSeq.get()[mIdx]));
            iter != TOKEN::Keyword::STR_KEYWORD_MAP.end()
                && iter->second == tag)
            return mIdx++, true;
    }
    
    return false;
}

bool TreeGenerator::isMatch(TOKEN::Punctuator::Tag tag)
{
    if(mIdx < mSeq.get().size()
        && std::holds_alternative<TOKEN::Punctuator*>(mSeq.get()[mIdx]->var))
    {
        if(std::get<TOKEN::Punctuator*>(mSeq.get()[mIdx]->var)->tag == tag)
            return mIdx++, true;
    }
    
    return false;
}

bool TreeGenerator::noEvaluatedError() const
{
    static const constexpr std::size_t numPreOutput{15ull};
    static const constexpr std::size_t numPostOutput{5ull};

    std::lock_guard lock{stdioMutex};

    std::size_t endPos{0ull};
    if(!mCacheMap.empty())
    {
        for(auto &&[beginPos, element] : mCacheMap)
            endPos = element->mEnd > endPos ? element->mEnd : endPos;
    }

    std::cerr << OUTPUT::charRedCode
        << "ANALYZER::TreeGenerator::noEvaluatedError():\n"
        << OUTPUT::resetCode
        << "    what: token-sequence has not been evaluated to the end.\n"
        "    file: " << mFile << "\n"
        "    idx: " << endPos << "\n"
        "    token: ";

    for(std::size_t i{endPos >= numPreOutput
            ? endPos - numPreOutput
            : 0ull};
        i < endPos + numPostOutput
            && i < mSeq.get().size();
        i++)
    {
        if(i + 1ull == endPos || i == endPos)
            std::cerr << OUTPUT::charRedCode;
        else
            std::cerr << OUTPUT::resetCode;
        std::cerr << TOKEN::str(mSeq.get().at(i)) << ' ';
    }

    std::cerr << OUTPUT::resetCode << std::endl;

    return false;
}

}