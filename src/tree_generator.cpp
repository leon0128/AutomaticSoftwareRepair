#include <vector>
#include <iostream>
#include <utility>

#include "scope.hpp"
#include "tokenizer.hpp"
#include "tree_generator.hpp"

const std::unordered_map<std::string, TOKEN::Keyword::Tag> TreeGenerator::KEYWORD_MAP
    = {{"auto", TOKEN::Keyword::Tag::AUTO}
        , {"break", TOKEN::Keyword::Tag::BREAK}
        , {"case", TOKEN::Keyword::Tag::CASE}
        , {"char", TOKEN::Keyword::Tag::CHAR}
        , {"const", TOKEN::Keyword::Tag::CONST}
        , {"continue", TOKEN::Keyword::Tag::CONTINUE}
        , {"default", TOKEN::Keyword::Tag::DEFAULT}
        , {"do", TOKEN::Keyword::Tag::DO}
        , {"double", TOKEN::Keyword::Tag::DOUBLE}
        , {"else", TOKEN::Keyword::Tag::ELSE}
        , {"enum", TOKEN::Keyword::Tag::ENUM}
        , {"extern", TOKEN::Keyword::Tag::EXTERN}
        , {"float", TOKEN::Keyword::Tag::FLOAT}
        , {"for", TOKEN::Keyword::Tag::FOR}
        , {"goto", TOKEN::Keyword::Tag::GOTO}
        , {"if", TOKEN::Keyword::Tag::IF}
        , {"inline", TOKEN::Keyword::Tag::INLINE}
        , {"int", TOKEN::Keyword::Tag::INT}
        , {"long", TOKEN::Keyword::Tag::LONG}
        , {"register", TOKEN::Keyword::Tag::REGISTER}
        , {"restrict", TOKEN::Keyword::Tag::RESTRICT}
        , {"return", TOKEN::Keyword::Tag::RETURN}
        , {"short", TOKEN::Keyword::Tag::SHORT}
        , {"signed", TOKEN::Keyword::Tag::SIGNED}
        , {"sizeof", TOKEN::Keyword::Tag::SIZEOF}
        , {"static", TOKEN::Keyword::Tag::STATIC}
        , {"struct", TOKEN::Keyword::Tag::STRUCT}
        , {"switch", TOKEN::Keyword::Tag::SWITCH}
        , {"typedef", TOKEN::Keyword::Tag::TYPEDEF}
        , {"union", TOKEN::Keyword::Tag::UNION}
        , {"unsigned", TOKEN::Keyword::Tag::UNSIGNED}
        , {"void", TOKEN::Keyword::Tag::VOID}
        , {"volatile", TOKEN::Keyword::Tag::VOLATILE}
        , {"while", TOKEN::Keyword::Tag::WHILE}
        , {"_Alignas", TOKEN::Keyword::Tag::ALIGNAS}
        , {"_Alignof", TOKEN::Keyword::Tag::ALIGNOF}
        , {"_Atomic", TOKEN::Keyword::Tag::ATOMIC}
        , {"_Bool", TOKEN::Keyword::Tag::BOOL}
        , {"_Complex", TOKEN::Keyword::Tag::COMPLEX}
        , {"_Generic", TOKEN::Keyword::Tag::GENERIC}
        , {"_Imaginary", TOKEN::Keyword::Tag::IMAGINARY}
        , {"_Noreturn", TOKEN::Keyword::Tag::NORETURN}
        , {"_Static_assert", TOKEN::Keyword::Tag::STATIC_ASSERT}
        , {"_Thread_local", TOKEN::Keyword::Tag::THREAD_LOCAL}};

TreeGenerator::TreeGenerator(const std::string &file
    , const Sequence &seq)
    : mFile(file)
    , mSeq(seq)
    , mIdx(0)
    , mTranslationUnit(nullptr)
{
}

TreeGenerator::~TreeGenerator()
{
}

bool TreeGenerator::execute()
{
    mTranslationUnit = tokTranslationUnit();

    if(mTranslationUnit != nullptr)
        std::cout << TOKEN::str(mTranslationUnit) << std::endl;

    if(mIdx == mSeq.size())
        return true;
    else
    {
        std::cerr << "TreeGenerator error:\n"
            "    what: token-sequence has not been evaluated to the end.\n"
            "    file: " << mFile << "\n"
            "    idx: " << mIdx
            << std::endl;
        return false;
    }
}

TOKEN::TranslationUnit *TreeGenerator::tokTranslationUnit()
{
    std::vector<TOKEN::ExternalDeclaration*> seq;
    for(auto ed = tokExternalDeclaration(); ed != nullptr; ed = tokExternalDeclaration())
        seq.push_back(ed);

    if(!seq.empty())
        return new TOKEN::TranslationUnit(std::move(seq));
    else
        return nullptr;
}

TOKEN::ExternalDeclaration *TreeGenerator::tokExternalDeclaration()
{
    if(TOKEN::Declaration *d = tokDeclaration();
        d != nullptr)
        return new TOKEN::ExternalDeclaration(d);
    else if(TOKEN::FunctionDefinition *fd = tokFunctionDefinition();
        fd != nullptr)
        return new TOKEN::ExternalDeclaration(fd);

    return nullptr;
}

TOKEN::FunctionDefinition *TreeGenerator::tokFunctionDefinition()
{
    std::size_t pre = mIdx;
    TOKEN::DeclarationSpecifiers *ds = nullptr;
    TOKEN::Declarator *d = nullptr;
    TOKEN::DeclarationList *dl = nullptr;
    TOKEN::CompoundStatement *cs = nullptr;

    if((ds = tokDeclarationSpecifiers()) != nullptr
        && (d = tokDeclarator()) != nullptr
        && (dl = tokDeclarationList(), true)
        && (cs = tokCompoundStatement()) != nullptr)
        return new TOKEN::FunctionDefinition(ds, d, dl, cs);
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
    std::size_t pre = mIdx;
    
    // declaration-specifiers init-declarator-list
    if(TOKEN::Declaration::Sds_idl sds_idl;
        (sds_idl.ds = tokDeclarationSpecifiers()) != nullptr
        && (sds_idl.idl = tokInitDeclaratorList(), true)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return new TOKEN::Declaration(sds_idl);
    else
    {
        mIdx = pre;
        delete sds_idl.ds;
        delete sds_idl.idl;
    }
    // static_assert-declaration
    if(TOKEN::Declaration::Ssad ssad;
        (ssad.sad = tokStaticAssertDeclaration()) != nullptr)
        return new TOKEN::Declaration(ssad);

    return nullptr;
}

TOKEN::DeclarationSpecifiers *TreeGenerator::tokDeclarationSpecifiers()
{
    std::vector<TOKEN::DeclarationSpecifiers::Var> seq;
    
    bool hasTypeSpecifier = false;
    while(true)
    {
        TOKEN::DeclarationSpecifiers::Var v;
        if(v.emplace<TOKEN::StorageClassSpecifier*>(tokStorageClassSpecifier()) != nullptr
            || (v.emplace<TOKEN::TypeSpecifier*>(tokTypeSpecifier()) != nullptr && (hasTypeSpecifier = true))
            || v.emplace<TOKEN::TypeQualifier*>(tokTypeQualifier()) != nullptr
            || v.emplace<TOKEN::FunctionSpecifier*>(tokFunctionSpecifier()) != nullptr
            || v.emplace<TOKEN::AlignmentSpecifier*>(tokAlignmentSpecifier()) != nullptr)
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
        return new TOKEN::DeclarationSpecifiers(std::move(seq));
    else
        return nullptr;
}

TOKEN::InitDeclaratorList *TreeGenerator::tokInitDeclaratorList()
{
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
        return new TOKEN::InitDeclaratorList(std::move(seq));
    else
        return nullptr;
}

TOKEN::StaticAssertDeclaration *TreeGenerator::tokStaticAssertDeclaration()
{
    std::size_t pre = mIdx;
    TOKEN::ConstantExpression *ce = nullptr;
    TOKEN::StringLiteral *sl = nullptr;
    
    if(isMatch(TOKEN::Keyword::Tag::STATIC_ASSERT)
        && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
        && (ce = tokConstantExpression()) != nullptr
        && (sl = tokStringLiteral()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return new TOKEN::StaticAssertDeclaration(ce, sl);
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
    if(TOKEN::ConditionalExpression *ce = tokConditionalExpression();
        ce != nullptr)
        return new TOKEN::ConstantExpression(ce);
    else
        return nullptr;
}

TOKEN::StringLiteral *TreeGenerator::tokStringLiteral()
{
    if(mIdx < mSeq.size()
        && std::holds_alternative<TOKEN::StringLiteral*>(mSeq[mIdx]->var))
        return mIdx++, std::get<TOKEN::StringLiteral*>(mSeq[mIdx - 1]->var)->copy();
    else
        return nullptr;
}

TOKEN::Declarator *TreeGenerator::tokDeclarator()
{
    std::size_t pre = mIdx;
    TOKEN::Pointer *p = nullptr;
    TOKEN::DirectDeclarator *dd = nullptr;
    
    if((p = tokPointer(), true)
        && (dd = tokDirectDeclarator()) != nullptr)
        return new TOKEN::Declarator(p, dd);
    else
    {
        mIdx = pre;
        delete p;
        delete dd;
    }

    return nullptr;
}

TOKEN::DeclarationList *TreeGenerator::tokDeclarationList()
{
    std::vector<TOKEN::Declaration*> seq;
    for(TOKEN::Declaration *d = tokDeclaration(); d != nullptr; d = tokDeclaration())
        seq.push_back(d);

    if(!seq.empty())
        return new TOKEN::DeclarationList(std::move(seq));
    else
        return nullptr;
}

TOKEN::CompoundStatement *TreeGenerator::tokCompoundStatement()
{
    std::size_t pre = mIdx;
    TOKEN::BlockItemList *bil = nullptr;
    
    if(isMatch(TOKEN::Punctuator::Tag::L_CURLY_BRACKET)
        && (bil = tokBlockItemList(), true)
        && isMatch(TOKEN::Punctuator::Tag::R_CURLY_BRACKET))
        return new TOKEN::CompoundStatement(bil);
    else
    {
        mIdx = pre;
        delete bil;
    }

    return nullptr;
}

TOKEN::StorageClassSpecifier *TreeGenerator::tokStorageClassSpecifier()
{
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
        return new TOKEN::StorageClassSpecifier(tag);
    else
        return nullptr;
}

TOKEN::TypeSpecifier *TreeGenerator::tokTypeSpecifier()
{
    TOKEN::TypeSpecifier::Var var;
    
    if(isMatch(TOKEN::Keyword::Tag::VOID))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::VOID);
    else if(isMatch(TOKEN::Keyword::Tag::CHAR))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::CHAR);
    else if(isMatch(TOKEN::Keyword::Tag::SHORT))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::SHORT);
    else if(isMatch(TOKEN::Keyword::Tag::INT))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::INT);
    else if(isMatch(TOKEN::Keyword::Tag::LONG))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::LONG);
    else if(isMatch(TOKEN::Keyword::Tag::FLOAT))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::FLOAT);
    else if(isMatch(TOKEN::Keyword::Tag::DOUBLE))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::DOUBLE);
    else if(isMatch(TOKEN::Keyword::Tag::SIGNED))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::SIGNED);
    else if(isMatch(TOKEN::Keyword::Tag::UNSIGNED))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::UNSIGNED);
    else if(isMatch(TOKEN::Keyword::Tag::BOOL))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::BOOL);
    else if(isMatch(TOKEN::Keyword::Tag::COMPLEX))
        var.emplace<TOKEN::TypeSpecifier::Tag>(TOKEN::TypeSpecifier::Tag::COMPLEX);
    else if(var.emplace<TOKEN::AtomicTypeSpecifier*>(tokAtomicTypeSpecifier()) != nullptr
        || var.emplace<TOKEN::StructOrUnionSpecifier*>(tokStructOrUnionSpecifier()) != nullptr
        || var.emplace<TOKEN::EnumSpecifier*>(tokEnumSpecifier()) != nullptr
        || var.emplace<TOKEN::TypedefName*>(tokTypedefName()) != nullptr)
        return new TOKEN::TypeSpecifier(var);
    
    if(std::holds_alternative<TOKEN::TypeSpecifier::Tag>(var))
        return new TOKEN::TypeSpecifier(var);
    else
        return nullptr;
}

TOKEN::TypeQualifier *TreeGenerator::tokTypeQualifier()
{
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
        return new TOKEN::TypeQualifier(tag);
    else
        return nullptr;
}

TOKEN::FunctionSpecifier *TreeGenerator::tokFunctionSpecifier()
{
    TOKEN::FunctionSpecifier::Tag tag = TOKEN::FunctionSpecifier::Tag::NONE;

    if(isMatch(TOKEN::Keyword::Tag::INLINE))
        tag = TOKEN::FunctionSpecifier::Tag::INLINE;
    else if(isMatch(TOKEN::Keyword::Tag::NORETURN))
        tag = TOKEN::FunctionSpecifier::Tag::NORETURN;
    
    if(tag != TOKEN::FunctionSpecifier::Tag::NONE)
        return new TOKEN::FunctionSpecifier(tag);
    else
        return nullptr;
}

TOKEN::AlignmentSpecifier *TreeGenerator::tokAlignmentSpecifier()
{
    TOKEN::AlignmentSpecifier::Var var;
    std::size_t pre = mIdx;

    if(isMatch(TOKEN::Keyword::Tag::ALIGNAS)
        && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
        && var.emplace<TOKEN::TypeName*>(tokTypeName()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return new TOKEN::AlignmentSpecifier(var);
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
        return new TOKEN::AlignmentSpecifier(var);
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
    std::size_t pre = mIdx;

    if(TOKEN::InitDeclarator::Sd_i s;
        (s.d = tokDeclarator()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::ASSIGNMENT)
            && (s.i = tokInitializer()) != nullptr)
        return new TOKEN::InitDeclarator(s);
    else
    {
        mIdx = pre;
        delete s.d;
        delete s.i;
    }

    if(TOKEN::InitDeclarator::Sd s;
        (s.d = tokDeclarator()) != nullptr)
        return new TOKEN::InitDeclarator(s);
    else
    {
        mIdx = pre;
        delete s.d;
    }

    return nullptr;
}

TOKEN::ConditionalExpression *TreeGenerator::tokConditionalExpression()
{
    std::size_t pre = mIdx;

    if(TOKEN::ConditionalExpression::Slore_e_ce s;
        (s.lore = tokLogicalORExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::QUESTION)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.ce = tokConditionalExpression()) != nullptr)
        return new TOKEN::ConditionalExpression(s);
    else
    {
        mIdx = pre;
        delete s.lore;
        delete s.e;
        delete s.ce;
    }

    if(TOKEN::ConditionalExpression::Slore s;
        (s.lore = tokLogicalORExpression()) != nullptr)
        return new TOKEN::ConditionalExpression(s);
    else
    {
        mIdx = pre;
        delete s.lore;
    }

    return nullptr;
}

TOKEN::Pointer *TreeGenerator::tokPointer()
{
    std::size_t pre = mIdx;

    if(TOKEN::Pointer::Stql_p s;
        isMatch(TOKEN::Punctuator::Tag::ASTERISK)
            && (s.tql = tokTypeQualifierList(), true)
            && (s.p = tokPointer()) != nullptr)
        return new TOKEN::Pointer(s);
    else
    {
        mIdx = pre;
        delete s.tql;
        delete s.p;
    }

    if(TOKEN::Pointer::Stql s;
        isMatch(TOKEN::Punctuator::Tag::ASTERISK)
            && (s.tql = tokTypeQualifierList(), true))
        return new TOKEN::Pointer(s);
    else
    {
        mIdx = pre;
        delete s.tql;
    }

    return nullptr;
}

TOKEN::DirectDeclarator *TreeGenerator::tokDirectDeclarator()
{
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

    return new TOKEN::DirectDeclarator(std::move(seq));
}

TOKEN::BlockItemList *TreeGenerator::tokBlockItemList()
{
    std::vector<TOKEN::BlockItem*> seq;
    for(TOKEN::BlockItem *bi = tokBlockItem();
        bi != nullptr;
        bi = tokBlockItem())
        seq.push_back(bi);
    
    if(!seq.empty())
        return new TOKEN::BlockItemList(std::move(seq));
    else
        return nullptr;
}

TOKEN::AtomicTypeSpecifier *TreeGenerator::tokAtomicTypeSpecifier()
{
    std::size_t pre = mIdx;
    
    if(TOKEN::TypeName *tn = nullptr;
        isMatch(TOKEN::Keyword::Tag::ATOMIC)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (tn = tokTypeName()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return new TOKEN::AtomicTypeSpecifier(tn);
    else
    {
        mIdx = pre;
        delete tn;
    }

    return nullptr;
}

TOKEN::StructOrUnionSpecifier *TreeGenerator::tokStructOrUnionSpecifier()
{
    std::size_t pre = mIdx;

    if(TOKEN::StructOrUnionSpecifier::Ssou_i_sdl s;
        (s.sou = tokStructOrUnion()) != nullptr
            && (s.i = tokIdentifier(), true)
            && isMatch(TOKEN::Punctuator::Tag::L_CURLY_BRACKET)
            && (s.sdl = tokStructDeclarationList()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_CURLY_BRACKET))
        return new TOKEN::StructOrUnionSpecifier(s);
    else
    {
        mIdx = pre;
        delete s.sou;
        delete s.i;
        delete s.sdl;
    }

    if(TOKEN::StructOrUnionSpecifier::Ssou_i s;
        (s.sou = tokStructOrUnion()) != nullptr
            && (s.i = tokIdentifier()) != nullptr)
        return new TOKEN::StructOrUnionSpecifier(s);
    else
    {
        mIdx = pre;
        delete s.sou;
        delete s.i;
    }

    return nullptr;
}

TOKEN::EnumSpecifier *TreeGenerator::tokEnumSpecifier()
{
    std::size_t pre = mIdx;

    if(TOKEN::EnumSpecifier::Si_el s;
        isMatch(TOKEN::Keyword::Tag::ENUM)
            && (s.i = tokIdentifier(), true)
            && isMatch(TOKEN::Punctuator::Tag::L_CURLY_BRACKET)
            && (s.el = tokEnumeratorList()) != nullptr
            && (isMatch(TOKEN::Punctuator::Tag::COMMA), true)
            && isMatch(TOKEN::Punctuator::Tag::R_CURLY_BRACKET))
        return new TOKEN::EnumSpecifier(s);
    else
    {
        mIdx = pre;
        delete s.i;
        delete s.el;
    }

    if(TOKEN::EnumSpecifier::Si s;
        isMatch(TOKEN::Keyword::Tag::ENUM)
            && (s.i = tokIdentifier()) != nullptr)
        return new TOKEN::EnumSpecifier(s);
    else
    {
        mIdx = pre;
        delete s.i;
    }

    return nullptr;
}

TOKEN::TypedefName *TreeGenerator::tokTypedefName()
{
    if(TOKEN::Identifier *i = tokIdentifier();
        i != nullptr)
        return new TOKEN::TypedefName(i);
    else
        return nullptr;
}

TOKEN::TypeName *TreeGenerator::tokTypeName()
{
    std::size_t pre = mIdx;
    TOKEN::SpecifierQualifierList *sql = nullptr;
    TOKEN::AbstractDeclarator *ad = nullptr;

    if((sql = tokSpecifierQualifierList()) != nullptr
        && (ad = tokAbstractDeclarator(), true))
        return new TOKEN::TypeName(sql, ad);
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
    std::size_t pre = mIdx;

    if(TOKEN::AssignmentExpression *ae = nullptr;
        (ae = tokAssignmentExpression()) != nullptr)
        return new TOKEN::Initializer(ae);
    else
    {
        mIdx = pre;
        delete ae;
    }

    if(TOKEN::InitializerList *il = nullptr;
        isMatch(TOKEN::Punctuator::Tag::L_CURLY_BRACKET)
            && (il = tokInitializerList()) != nullptr
            && (isMatch(TOKEN::Punctuator::Tag::COMMA), true)
            && isMatch(TOKEN::Punctuator::Tag::R_CURLY_BRACKET))
        return new TOKEN::Initializer(il);
    else
    {
        mIdx = pre;
        delete il;
    }

    return nullptr;
}

TOKEN::LogicalORExpression *TreeGenerator::tokLogicalORExpression()
{
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

    return new TOKEN::LogicalORExpression(std::move(seq));
}

TOKEN::Expression *TreeGenerator::tokExpression()
{
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

    return new TOKEN::Expression(std::move(seq));
}

TOKEN::TypeQualifierList *TreeGenerator::tokTypeQualifierList()
{
    std::vector<TOKEN::TypeQualifier*> seq;
    for(TOKEN::TypeQualifier *tq = tokTypeQualifier();
        tq != nullptr;
        tq = tokTypeQualifier())
        seq.push_back(tq);
    
    if(!seq.empty())
        return new TOKEN::TypeQualifierList(std::move(seq));
    else
        return nullptr;
}

TOKEN::AssignmentExpression *TreeGenerator::tokAssignmentExpression()
{
    std::size_t pre = mIdx;

    if(TOKEN::AssignmentExpression::Sue_ao_ae s;
        (s.ue = tokUnaryExpression()) != nullptr
            && (s.ao = tokAssignmentOperator()) != nullptr
            && (s.ae = tokAssignmentExpression()) != nullptr)
        return new TOKEN::AssignmentExpression(s);
    else
    {
        mIdx = pre;
        delete s.ue;
        delete s.ao;
        delete s.ae;
    }

    if(TOKEN::AssignmentExpression::Sce s;
        (s.ce = tokConditionalExpression()) != nullptr)
        return new TOKEN::AssignmentExpression(s);
    else
    {
        mIdx = pre;
        delete s.ce;
    }

    return nullptr;
}

TOKEN::ParameterTypeList *TreeGenerator::tokParameterTypeList()
{
    if(TOKEN::ParameterList *pl = tokParameterList();
        pl != nullptr)
    {
        std::size_t pre = mIdx;
        if(isMatch(TOKEN::Punctuator::Tag::COMMA)
            && isMatch(TOKEN::Punctuator::Tag::TRIPLE_PERIOD))
            return new TOKEN::ParameterTypeList(pl, true);
        else if(mIdx = pre, true)
            return new TOKEN::ParameterTypeList(pl, false);
    }

    return nullptr;
}

TOKEN::IdentifierList *TreeGenerator::tokIdentifierList()
{
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

    return new TOKEN::IdentifierList(std::move(seq));
}

TOKEN::Identifier *TreeGenerator::tokIdentifier()
{
    if(mIdx < mSeq.size()
        && std::holds_alternative<TOKEN::Identifier*>(mSeq[mIdx]->var))
    {
        if(KEYWORD_MAP.find(TOKEN::str(mSeq[mIdx])) == KEYWORD_MAP.end())
            return mIdx++, std::get<TOKEN::Identifier*>(mSeq[mIdx - 1]->var)->copy();
    }

    return nullptr;
}

TOKEN::BlockItem *TreeGenerator::tokBlockItem()
{
    if(TOKEN::Declaration *d = tokDeclaration();
        d != nullptr)
        return new TOKEN::BlockItem(d);
    else if(TOKEN::Statement *s = tokStatement();
        s != nullptr)
        return new TOKEN::BlockItem(s);
    else
        return nullptr;
}

TOKEN::StructOrUnion *TreeGenerator::tokStructOrUnion()
{
    TOKEN::StructOrUnion::Tag tag = TOKEN::StructOrUnion::Tag::NONE;

    if(isMatch(TOKEN::Keyword::Tag::STRUCT))
        tag = TOKEN::StructOrUnion::Tag::STRUCT;
    else if(isMatch(TOKEN::Keyword::Tag::UNION))
        tag = TOKEN::StructOrUnion::Tag::UNION;
    
    if(tag != TOKEN::StructOrUnion::Tag::NONE)
        return new TOKEN::StructOrUnion(tag);
    else
        return nullptr;
}

TOKEN::StructDeclarationList *TreeGenerator::tokStructDeclarationList()
{
    std::vector<TOKEN::StructDeclaration*> seq;
    
    for(TOKEN::StructDeclaration *sd = tokStructDeclaration();
        sd != nullptr;
        sd = tokStructDeclaration())
        seq.push_back(sd);
    
    if(!seq.empty())
        return new TOKEN::StructDeclarationList(std::move(seq));
    else
        return nullptr;
}

TOKEN::EnumeratorList *TreeGenerator::tokEnumeratorList()
{
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

    return new TOKEN::EnumeratorList(std::move(seq));
}

TOKEN::SpecifierQualifierList *TreeGenerator::tokSpecifierQualifierList()
{
    std::vector<TOKEN::SpecifierQualifierList::Var> seq;

    while(true)
    {
        if(TOKEN::TypeSpecifier *ts = tokTypeSpecifier();
            ts != nullptr)
        {
            seq.emplace_back(ts);
            continue;
        }
        else if(TOKEN::TypeQualifier *tq = tokTypeQualifier();
            tq != nullptr)
        {
            seq.emplace_back(tq);
            continue;
        }
        else
            break;
    }

    if(!seq.empty())
        return new TOKEN::SpecifierQualifierList(std::move(seq));
    else
        return nullptr;
}

TOKEN::AbstractDeclarator *TreeGenerator::tokAbstractDeclarator()
{
    std::size_t pre = mIdx;

    if(TOKEN::AbstractDeclarator::Sp_dad s;
        (s = tokPointer(), true)
            && (s.dad = tokDirectAbstractDeclarator()) != nullptr)
        return new TOKEN::AbstractDeclarator(s);
    else
    {
        mIdx = pre;
        delete s.p;
        delete s.dad;
    }

    if(TOKEN::AbstractDeclarator::Sp s;
        (s.p = tokPointer()) != nullptr)
        return new TOKEN::AbstractDeclarator(s);
    else
    {
        mIdx = pre;
        delete s.p;
    }

    return nullptr;
}

TOKEN::InitializerList *TreeGenerator::tokInitializerList()
{
    std::vector<TOKEN::InitializerList::Sd_i> seq;

    while(true)
    {
        std::size_t pre = mIdx;
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
    }

    if(!seq.empty())
        return new TOKEN::InitializerList(std::move(seq));
    else
        return nullptr;
}

TOKEN::LogicalANDExpression *TreeGenerator::tokLogicalANDExpression()
{
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

    return new TOKEN::LogicalANDExpression(std::move(seq));
}

TOKEN::UnaryExpression *TreeGenerator::tokUnaryExpression()
{
    std::size_t pre = mIdx;

    if(TOKEN::UnaryExpression::Spe s;
        (s.pe = tokPostfixExpression()) != nullptr)
        return new TOKEN::UnaryExpression(s);
    else
    {
        mIdx = pre;
        delete s.pe;
    }

    if(TOKEN::UnaryExpression::Si_ue s;
        isMatch(TOKEN::Punctuator::Tag::INCREMENT)
            && (s.ue = tokUnaryExpression()) != nullptr)
        return new TOKEN::UnaryExpression(s);
    else
    {
        mIdx = pre;
        delete s.ue;
    }

    if(TOKEN::UnaryExpression::Sd_ue s;
        isMatch(TOKEN::Punctuator::Tag::DECREMENT)
            && (s.ue = tokUnaryExpression()) != nullptr)
        return new TOKEN::UnaryExpression(s);
    else
    {
        mIdx = pre;
        delete s.ue;
    }

    if(TOKEN::UnaryExpression::Suo_ce s;
        (s.uo = tokUnaryOperator()) != nullptr
        && (s.ce = tokCastExpression()) != nullptr)
        return new TOKEN::UnaryExpression(s);
    else
    {
        mIdx = pre;
        delete s.uo;
        delete s.ce;
    }

    if(TOKEN::UnaryExpression::Ss_ue s;
        isMatch(TOKEN::Keyword::Tag::SIZEOF)
            && (s.ue = tokUnaryExpression()) != nullptr)
        return new TOKEN::UnaryExpression(s);
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
        return new TOKEN::UnaryExpression(s);
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
        return new TOKEN::UnaryExpression(s);
    else
    {
        mIdx = pre;
        delete s.tn;
    }

    return nullptr;
}

TOKEN::AssignmentOperator *TreeGenerator::tokAssignmentOperator()
{
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
        tag = TOKEN::AssignmentOperator::Tag::SUBSTRACTION;
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
        return new TOKEN::AssignmentOperator(tag);
    else
        return nullptr;
}

TOKEN::ParameterList *TreeGenerator::tokParameterList()
{
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

    return new TOKEN::ParameterList(std::move(seq));
}

TOKEN::Statement *TreeGenerator::tokStatement()
{
    if(TOKEN::LabeledStatement *ls = tokLabeledStatement();
        ls != nullptr)
        return new TOKEN::Statement(ls);
    else if(TOKEN::CompoundStatement *cs = tokCompoundStatement();
        cs != nullptr)
        return new TOKEN::Statement(cs);
    else if(TOKEN::ExpressionStatement *es = tokExpressionStatement();
        es != nullptr)
        return new TOKEN::Statement(es);
    else if(TOKEN::SelectionStatement *ss = tokSelectionStatement();
        ss != nullptr)
        return new TOKEN::Statement(ss);
    else if(TOKEN::IterationStatement *is = tokIterationStatement();
        is != nullptr)
        return new TOKEN::Statement(is);
    else if(TOKEN::JumpStatement *js = tokJumpStatement();
        js != nullptr)
        return new TOKEN::Statement(js);
    
    return nullptr;
}

TOKEN::StructDeclaration *TreeGenerator::tokStructDeclaration()
{
    std::size_t pre = mIdx;

    if(TOKEN::StructDeclaration::Ssql_sdl s;
        (s.sql = tokSpecifierQualifierList()) != nullptr
            && (s.sdl = tokStructDeclaratorList(), true)
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return new TOKEN::StructDeclaration(s);
    else
    {
        mIdx = pre;
        delete s.sql;
        delete s.sdl;
    }

    if(TOKEN::StructDeclaration::Ssad s;
        (s.sad = tokStaticAssertDeclaration()) != nullptr)
        return new TOKEN::StructDeclaration(s);
    else
    {
        mIdx = pre;
        delete s.sad;
    }

    return nullptr;
}

TOKEN::Enumerator *TreeGenerator::tokEnumerator()
{
    std::size_t pre = mIdx;

    if(TOKEN::Enumerator::Sec_ce s;
        (s.ec = tokEnumerationConstant()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::ASSIGNMENT)
            && (s.ce = tokConstantExpression()) != nullptr)
        return new TOKEN::Enumerator(s);
    else
    {
        mIdx = pre;
        delete s.ec;
        delete s.ce;
    }

    if(TOKEN::Enumerator::Sec s;
        (s.ec = tokEnumerationConstant()) != nullptr)
        return new TOKEN::Enumerator(s);
    else
    {
        mIdx = pre;
        delete s.ec;
    }

    return nullptr;
}

TOKEN::DirectAbstractDeclarator *TreeGenerator::tokDirectAbstractDeclarator()
{
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
        return new TOKEN::DirectAbstractDeclarator(std::move(seq));
    else
        return nullptr;
}

TOKEN::Designation *TreeGenerator::tokDesignation()
{
    std::size_t pre = mIdx;
    TOKEN::DesignatorList *dl = nullptr;
    
    if((dl = tokDesignatorList()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::ASSIGNMENT))
        return new TOKEN::Designation(dl);
    else
    {
        mIdx = pre;
        delete dl;
    }

    return nullptr;
}

TOKEN::InclusiveORExpression *TreeGenerator::tokInclusiveORExpression()
{
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

    return new TOKEN::InclusiveORExpression(std::move(seq));
}

TOKEN::PostfixExpression *TreeGenerator::tokPostfixExpression()
{
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

    return new TOKEN::PostfixExpression(std::move(seq));
}

TOKEN::CastExpression *TreeGenerator::tokCastExpression()
{
    std::size_t pre = mIdx;

    if(TOKEN::CastExpression::Stn_ce s;
        isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.tn = tokTypeName()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.ce = tokCastExpression()) != nullptr)
        return new TOKEN::CastExpression(s);
    else
    {
        mIdx = pre;
        delete s.tn;
        delete s.ce;
    }

    if(TOKEN::CastExpression::Sue s;
        (s.ue = tokUnaryExpression()) != nullptr)
        return new TOKEN::CastExpression(s);
    else
    {
        mIdx = pre;
        delete s.ue;
    }

    return nullptr;
}

TOKEN::UnaryOperator *TreeGenerator::tokUnaryOperator()
{
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
        return new TOKEN::UnaryOperator(tag);
    else
        return nullptr;
}

TOKEN::ParameterDeclaration *TreeGenerator::tokParameterDeclaration()
{
    std::size_t pre = mIdx;

    if(TOKEN::ParameterDeclaration::Sds_d s;
        (s.ds = tokDeclarationSpecifiers()) != nullptr
            && (s.d = tokDeclarator()) != nullptr)
        return new TOKEN::ParameterDeclaration(s);
    else
    {
        mIdx = pre;
        delete s.ds;
        delete s.d;
    }

    if(TOKEN::ParameterDeclaration::Sds_ad s;
        (s.ds = tokDeclarationSpecifiers()) != nullptr
            && (s.ad = tokAbstractDeclarator(), true))
        return new TOKEN::ParameterDeclaration(s);
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
    std::size_t pre = mIdx;

    if(TOKEN::LabeledStatement::Si_s s;
        (s.i = tokIdentifier()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.s = tokStatement()) != nullptr)
        return new TOKEN::LabeledStatement(s);
    else
    {
        mIdx = pre;
        delete s.i;
        delete s.s;
    }

    if(TOKEN::LabeledStatement::Sce_s s;
        isMatch(TOKEN::Keyword::Tag::CASE)
            && (s.ce = tokConstantExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.s = tokStatement()) != nullptr)
        return new TOKEN::LabeledStatement(s);
    else
    {
        mIdx = pre;
        delete s.ce;
        delete s.s;
    }

    if(TOKEN::LabeledStatement::Ss s;
        isMatch(TOKEN::Keyword::Tag::DEFAULT)
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.s = tokStatement()) != nullptr)
        return new TOKEN::LabeledStatement(s);
    else
    {
        mIdx = pre;
        delete s.s;
    }

    return nullptr;
}

TOKEN::ExpressionStatement *TreeGenerator::tokExpressionStatement()
{
    std::size_t pre = mIdx;
    TOKEN::Expression *e = nullptr;

    if((e = tokExpression(), true)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return new TOKEN::ExpressionStatement(e);
    else
        return mIdx = pre, nullptr;
}

TOKEN::SelectionStatement *TreeGenerator::tokSelectionStatement()
{
    std::size_t pre = mIdx;

    if(TOKEN::SelectionStatement::Si_e_s_s s;
        isMatch(TOKEN::Keyword::Tag::IF)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.s0 = tokStatement()) != nullptr
            && isMatch(TOKEN::Keyword::Tag::ELSE)
            && (s.s1 = tokStatement()) != nullptr)
        return new TOKEN::SelectionStatement(s);
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
        return new TOKEN::SelectionStatement(s);
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
        return new TOKEN::SelectionStatement(s);
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
    std::size_t pre = mIdx;

    if(TOKEN::IterationStatement::Sw_e_s s;
        isMatch(TOKEN::Keyword::Tag::WHILE)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && (s.s = tokStatement()) != nullptr)
        return new TOKEN::IterationStatement(s);
    else
    {
        mIdx = pre;
        delete s.e;
        delete s.s;
    }

    if(TOKEN::IterationStatement::Sd_s_e s;
        isMatch(TOKEN::Keyword::Tag::DO)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.s = tokStatement()) != nullptr
            && isMatch(TOKEN::Keyword::Tag::WHILE)
            && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (s.e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS)
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return new TOKEN::IterationStatement(s);
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
        return new TOKEN::IterationStatement(s);
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
        return new TOKEN::IterationStatement(s);
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
    std::size_t pre = mIdx;

    if(TOKEN::JumpStatement::Sg_i s;
        isMatch(TOKEN::Keyword::Tag::GOTO)
            && (s.i = tokIdentifier()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return new TOKEN::JumpStatement(s);
    else
    {
        mIdx = pre;
        delete s.i;
    }

    if(isMatch(TOKEN::Keyword::Tag::CONTINUE)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return new TOKEN::JumpStatement(TOKEN::JumpStatement::Sc());
    else
        mIdx = pre;
    
    if(isMatch(TOKEN::Keyword::Tag::BREAK)
        && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return new TOKEN::JumpStatement(TOKEN::JumpStatement::Sb());
    else
        mIdx = pre;

    if(TOKEN::JumpStatement::Sr_e s;
        isMatch(TOKEN::Keyword::Tag::RETURN)
            && (s.e = tokExpression(), true)
            && isMatch(TOKEN::Punctuator::Tag::SEMICOLON))
        return new TOKEN::JumpStatement(s);
    else
    {
        mIdx = pre;
        delete s.e;
    }

    return nullptr;
}

TOKEN::StructDeclaratorList *TreeGenerator::tokStructDeclaratorList()
{
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

    return new TOKEN::StructDeclaratorList(std::move(seq));
}

TOKEN::EnumerationConstant *TreeGenerator::tokEnumerationConstant()
{
    if(TOKEN::Identifier *i = tokIdentifier();
        i != nullptr)
        return new TOKEN::EnumerationConstant(i);
    else
        return nullptr;
}

TOKEN::DesignatorList *TreeGenerator::tokDesignatorList()
{
    std::vector<TOKEN::Designator*> seq;
    for(TOKEN::Designator *d = tokDesignator();
        d != nullptr;
        d = tokDesignator())
        seq.push_back(d);
    
    if(!seq.empty())
        return new TOKEN::DesignatorList(std::move(seq));
    else
        return nullptr;
}

TOKEN::ExclusiveORExpression *TreeGenerator::tokExclusiveORExpression()
{
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

    return new TOKEN::ExclusiveORExpression(std::move(seq));
}

TOKEN::PrimaryExpression *TreeGenerator::tokPrimaryExpression()
{
    std::size_t pre = mIdx;
    
    if(TOKEN::Identifier *i = tokIdentifier();
        i != nullptr)
        return new TOKEN::PrimaryExpression(i);
    else if(TOKEN::Constant *c = tokConstant();
        c != nullptr)
        return new TOKEN::PrimaryExpression(c);
    else if(TOKEN::StringLiteral *sl = tokStringLiteral();
        sl != nullptr)
        return new TOKEN::PrimaryExpression(sl);
    
    if(TOKEN::Expression *e = nullptr;
        isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
            && (e = tokExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return new TOKEN::PrimaryExpression(e);
    else
    {
        mIdx = pre;
        delete e;
    }

    if(TOKEN::GenericSelection *gs = tokGenericSelection();
        gs != nullptr)
        return new TOKEN::PrimaryExpression(gs);
    
    return nullptr;
}

TOKEN::ArgumentExpressionList *TreeGenerator::tokArgumentExpressionList()
{
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

    return new TOKEN::ArgumentExpressionList(std::move(seq));
}

TOKEN::StructDeclarator *TreeGenerator::tokStructDeclarator()
{
    std::size_t pre = mIdx;

    if(TOKEN::StructDeclarator::Sd_ce s;
        (s.d = tokDeclarator(), true)
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.ce = tokConstantExpression()) != nullptr)
        return new TOKEN::StructDeclarator(s);
    else
    {
        mIdx = pre;
        delete s.d;
        delete s.ce;
    }

    if(TOKEN::StructDeclarator::Sd s;
        (s.d = tokDeclarator()) != nullptr)
        return new TOKEN::StructDeclarator(s);
    else
    {
        mIdx = pre;
        delete s.d;
    }

    return nullptr;
}

TOKEN::Designator *TreeGenerator::tokDesignator()
{
    std::size_t pre = mIdx;

    if(TOKEN::ConstantExpression *ce = nullptr;
        isMatch(TOKEN::Punctuator::Tag::L_SQUARE_BRACKET)
            && (ce = tokConstantExpression()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::R_SQUARE_BRACKET))
        return new TOKEN::Designator(ce);
    else
    {
        mIdx = pre;
        delete ce;
    }

    if(TOKEN::Identifier *i = nullptr;
        isMatch(TOKEN::Punctuator::Tag::PERIOD)
            && (i = tokIdentifier()) != nullptr)
        return new TOKEN::Designator(i);
    else
    {
        mIdx = pre;
        delete i;
    }

    return nullptr;
}

TOKEN::ANDExpression *TreeGenerator::tokANDExpression()
{
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

    return new TOKEN::ANDExpression(std::move(seq));
}

TOKEN::Constant *TreeGenerator::tokConstant()
{
    if(TOKEN::IntegerConstant *ic = convIntegerConstant();
        ic != nullptr)
        return new TOKEN::Constant(ic);
    else if(TOKEN::FloatingConstant *fc = convFloatingConstant();
        fc != nullptr)
        return new TOKEN::Constant(fc);
    else if(TOKEN::EnumerationConstant *ec = convEnumerationConstant();
        ec != nullptr)
        return new TOKEN::Constant(ec);
    else if(TOKEN::CharacterConstant *cc = convCharacterConstant();
        cc != nullptr)
        return new TOKEN::Constant(cc);
    
    return nullptr;
}

TOKEN::GenericSelection *TreeGenerator::tokGenericSelection()
{
    std::size_t pre = mIdx;
    TOKEN::AssignmentExpression *ae = nullptr;
    TOKEN::GenericAssocList *gal = nullptr;

    if(isMatch(TOKEN::Keyword::Tag::GENERIC)
        && isMatch(TOKEN::Punctuator::Tag::L_PARENTHESIS)
        && (ae = tokAssignmentExpression()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::COMMA)
        && (gal = tokGenericAssocList()) != nullptr
        && isMatch(TOKEN::Punctuator::Tag::R_PARENTHESIS))
        return new TOKEN::GenericSelection(ae, gal);
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

    return new TOKEN::EqualityExpression(std::move(seq));
}

TOKEN::GenericAssocList *TreeGenerator::tokGenericAssocList()
{
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

    return new TOKEN::GenericAssocList(std::move(seq));
}

TOKEN::RelationalExpression *TreeGenerator::tokRelationalExpression()
{
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

    return new TOKEN::RelationalExpression(std::move(seq));
}

TOKEN::GenericAssociation *TreeGenerator::tokGenericAssociation()
{
    std::size_t pre = mIdx;

    if(TOKEN::GenericAssociation::Stn_ae s;
        (s.tn = tokTypeName()) != nullptr
            && isMatch(TOKEN::Punctuator::Tag::COLON)
            && (s.ae = tokAssignmentExpression()) != nullptr)
        return new TOKEN::GenericAssociation(s);
    else
    {
        mIdx = pre;
        delete s.tn;
        delete s.ae;
    }

    if(TOKEN::GenericAssociation::Sae s;
        (s.ae = tokAssignmentExpression()) != nullptr)
        return new TOKEN::GenericAssociation(s);
    else
    {
        mIdx = pre;
        delete s.ae;
    }

    return nullptr;
}

TOKEN::ShiftExpression *TreeGenerator::tokShiftExpression()
{
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

    return new TOKEN::ShiftExpression(std::move(seq));
}

TOKEN::AdditiveExpression *TreeGenerator::tokAdditiveExpression()
{
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

    return new TOKEN::AdditiveExpression(std::move(seq));
}

TOKEN::MultiplicativeExpression *TreeGenerator::tokMultiplicativeExpression()
{
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

    return new TOKEN::MultiplicativeExpression(std::move(seq));
}

TOKEN::IntegerConstant *TreeGenerator::convIntegerConstant()
{
    if(mIdx < mSeq.size()
        && std::holds_alternative<TOKEN::PPNumber*>(mSeq[mIdx]->var))
    {
        std::string str(TOKEN::str(mSeq[mIdx]));
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
    if(mIdx < mSeq.size()
        && std::holds_alternative<TOKEN::PPNumber*>(mSeq[mIdx]->var))
    {
        std::string str(TOKEN::str(mSeq[mIdx]));
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
    if(mIdx < mSeq.size()
        && std::holds_alternative<TOKEN::CharacterConstant*>(mSeq[mIdx]->var))
        return mIdx++, std::get<TOKEN::CharacterConstant*>(mSeq[mIdx - 1]->var)->copy();
    else
        return nullptr;
}

bool TreeGenerator::isMatch(TOKEN::Keyword::Tag tag)
{
    if(mIdx < mSeq.size()
        && std::holds_alternative<TOKEN::Identifier*>(mSeq[mIdx]->var))
    {
        if(auto iter = KEYWORD_MAP.find(TOKEN::str(mSeq[mIdx]));
            iter != KEYWORD_MAP.end()
                && iter->second == tag)
            return mIdx++, true;
    }
    
    return false;
}

bool TreeGenerator::isMatch(TOKEN::Punctuator::Tag tag)
{
    if(mIdx < mSeq.size()
        && std::holds_alternative<TOKEN::Punctuator*>(mSeq[mIdx]->var))
    {
        if(std::get<TOKEN::Punctuator*>(mSeq[mIdx]->var)->tag == tag)
            return mIdx++, true;
    }
    
    return false;
}