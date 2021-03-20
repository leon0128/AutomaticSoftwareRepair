#ifndef DEDUCER_HPP
#define DEDUCER_HPP

#include <utility>
#include <unordered_map>
#include <set>
#include <vector>
#include <optional>

#include "token.hpp"
#include "type.hpp"
#include "identifier.hpp"

namespace SCOPE
{
    class Scope;
}

extern std::optional<std::tuple<IDENTIFIER::StorageClass
    , TYPE::Type
    , IDENTIFIER::FunctionSpecifiers
    , IDENTIFIER::Alignment>> deduceAttributes(const TOKEN::DeclarationSpecifiers*
        , SCOPE::Scope*
        , bool isEnd);
extern std::optional<IDENTIFIER::StorageClass> deduceStorageClass(const std::vector<const TOKEN::StorageClassSpecifier*>&);

extern std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::TypeSpecifier*>&
    , const std::vector<const TOKEN::TypeQualifier*>&
    , SCOPE::Scope*
    , bool isEnd);
extern std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::TypeSpecifier*>&
    , SCOPE::Scope*
    , bool isEnd);
extern std::optional<TYPE::Type> deduceType(const std::multiset<TOKEN::TypeSpecifier::Tag>&);
extern std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::AtomicTypeSpecifier*>&
    , SCOPE::Scope*);
extern std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::StructOrUnionSpecifier*>&
    , SCOPE::Scope*
    , bool isEnd);
extern bool addMember(const TOKEN::StructDeclarationList*
    , std::size_t id
    , SCOPE::Scope*);
extern std::optional<TYPE::Type> deduceType(const TOKEN::SpecifierQualifierList*
    , SCOPE::Scope*
    , bool isEnd);
extern std::optional<std::pair<TYPE::Type
    , std::string>> deduceTypeAndIdentifier(const TOKEN::Declarator*
        , const TYPE::Type&
        , SCOPE::Scope*);
extern bool addPointer(const TOKEN::Pointer*
    , TYPE::Type&);
extern std::optional<TYPE::Type> deduceType(const TOKEN::ConstantExpression*
    , const TYPE::Type&);
extern std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::EnumSpecifier*>&
    , SCOPE::Scope*);
extern std::optional<TYPE::Type> deduceType(const std::vector<const TOKEN::TypedefName*>&
    , SCOPE::Scope*);
extern std::optional<TYPE::Type> deduceType(const TOKEN::TypeName*
    , SCOPE::Scope*);

extern std::optional<TYPE::Qualifiers> deduceQualifiers(const std::vector<const TOKEN::TypeQualifier*>&);
extern std::optional<TYPE::Qualifiers> deduceQualifiers(const TOKEN::TypeQualifierList*);
extern std::optional<IDENTIFIER::FunctionSpecifiers> deduceFunctionSpecifiers(const std::vector<const TOKEN::FunctionSpecifier*>&);
extern std::optional<IDENTIFIER::Alignment> deduceAlignment(const std::vector<const TOKEN::AlignmentSpecifier*>&
    , SCOPE::Scope*);

extern std::optional<TYPE::Type> addQualifiers(const TYPE::Type&
    , const TYPE::Qualifiers&);

extern inline const std::unordered_map<TYPE::Base::Tag
    , std::vector<std::multiset<TOKEN::TypeSpecifier::Tag>>> BASE_TYPE_MAP
    {{TYPE::Base::Tag::VOID
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

#endif