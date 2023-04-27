#ifndef ANALYZER_CACHE_ENCODER_HPP
#define ANALYZER_CACHE_ENCODER_HPP

#include <string>
#include <sstream>
#include <type_traits>

#include "common/token.hpp"

namespace ANALYZER
{

class CacheEncoder
{
public:
    // should use only relative filename.
    static std::string outputFilename(const std::string &filename)
        {return "./cache/" + filename + ".tree";}

    CacheEncoder();
    ~CacheEncoder() = default;

    bool execute(const std::string &filename
        , const TOKEN::TranslationUnit*);

private:
    // if T has only member var(std::variant),
    //  this function should be used to encode.
    // this function executes encode function to element that var has.
    template<class T>
    auto encode(const T *t)
        -> decltype(t->var, bool{});
    // if T has only member seq(std::vector),
    //  this function should be used to encode.
    // this function executes encode function to elements that seq has.
    template<class T>
    auto encode(const T *t)
        -> decltype(t->seq, bool{});
    // if T has only member tag(T::Tag),
    //  this function should be used to encode.
    // this function executes encode function to tag.
    template<class T>
    auto encode(const T *t)
        -> decltype(t->tag, bool{});
    // if T has only member c(char)
    //  this function should be used to encode.
    // this function executes encode function to c.
    template<class T>
    auto encode(const T *t)
        -> decltype(t->c, bool{});

    // this function is used to encode any variant types.
    // maximum index size: 255.  
    template<class ...Types>
    bool encode(const std::variant<Types...>&);

    // this function is used to encode any array types.
    // maximum array size: 65536.
    template<class Array>
    auto encode(const Array &array)
        -> decltype(array.size(), array.begin(), array.end(), bool{});

    // this function is used to encode integral value.
    template<class Integral>
    auto encode(Integral)
        -> std::enable_if_t<std::is_integral_v<Integral>, bool>;
    
    // this function is used to encode enum value.
    template<class Enum>
    auto encode(Enum)
        -> std::enable_if_t<std::is_enum_v<Enum>, bool>;

    // other tokens
    bool encode(std::monostate);
    bool encode(const std::string&);
    template<class First, class Second>
    bool encode(const std::pair<First, Second>&);
    bool encode(const TOKEN::StringLiteral*);
    bool encode(const TOKEN::IntegerConstant::Sdc_is&);
    bool encode(const TOKEN::IntegerConstant::Soc_is&);
    bool encode(const TOKEN::IntegerConstant::Shc_is&);
    bool encode(const TOKEN::EnumerationConstant*);
    bool encode(const TOKEN::CharacterConstant*);
    bool encode(const TOKEN::UniversalCharacterName::Su_hq&);
    bool encode(const TOKEN::UniversalCharacterName::SU_hq_hq&);
    bool encode(const TOKEN::DecimalConstant*);
    bool encode(const TOKEN::HexadecimalConstant*);
    bool encode(const TOKEN::DecimalFloatingConstant::Sfc_ep_fs&);
    bool encode(const TOKEN::DecimalFloatingConstant::Sds_ep_fs&);
    bool encode(const TOKEN::HexadecimalFloatingConstant::Shp_hfc_bep_fs&);
    bool encode(const TOKEN::HexadecimalFloatingConstant::Shp_hds_bep_fs&);
    bool encode(const TOKEN::HexQuad*);
    bool encode(const TOKEN::FractionalConstant::Sds_ds&);
    bool encode(const TOKEN::FractionalConstant::Sds&);
    bool encode(const TOKEN::ExponentPart*);
    bool encode(const TOKEN::HexadecimalFractionalConstant::Shds_hds&);
    bool encode(const TOKEN::HexadecimalFractionalConstant::Shds&);
    bool encode(const TOKEN::BinaryExponentPart*);
    bool encode(const TOKEN::IntegerSuffix::Sus_ls&);
    bool encode(const TOKEN::IntegerSuffix::Sus_lls&);
    bool encode(const TOKEN::IntegerSuffix::Sls_us&);
    bool encode(const TOKEN::IntegerSuffix::Slls_us&);
    bool encode(const TOKEN::FunctionDefinition*);
    bool encode(const TOKEN::Declaration*);
    bool encode(const TOKEN::Declaration::Sds_idl&);
    bool encode(const TOKEN::Declaration::Ssad&);
    bool encode(const TOKEN::Declarator*);
    bool encode(const TOKEN::CompoundStatement*);
    bool encode(const TOKEN::StaticAssertDeclaration*);
    bool encode(const TOKEN::Pointer::Stql&);
    bool encode(const TOKEN::Pointer::Stql_p&);
    bool encode(const TOKEN::DirectDeclarator::Si&);
    bool encode(const TOKEN::DirectDeclarator::Sd&);
    bool encode(const TOKEN::DirectDeclarator::Stql_ae&);
    bool encode(const TOKEN::DirectDeclarator::Stql&);
    bool encode(const TOKEN::DirectDeclarator::Sptl&);
    bool encode(const TOKEN::DirectDeclarator::Sil&);
    bool encode(const TOKEN::InitDeclarator::Sd&);
    bool encode(const TOKEN::InitDeclarator::Sd_i&);
    bool encode(const TOKEN::InitDeclarator::Sd_ba&);
    bool encode(const TOKEN::ConstantExpression*);
    bool encode(const TOKEN::AtomicTypeSpecifier*);
    bool encode(const TOKEN::StructOrUnionSpecifier::Ssou_i_sdl&);
    bool encode(const TOKEN::StructOrUnionSpecifier::Ssou_i&);
    bool encode(const TOKEN::EnumSpecifier::Si_el&);
    bool encode(const TOKEN::EnumSpecifier::Si&);
    bool encode(const TOKEN::TypedefName*);
    bool encode(const TOKEN::TypeName*);
    bool encode(const TOKEN::AssignmentExpression::Sce&);
    bool encode(const TOKEN::AssignmentExpression::Sue_ao_ae&);
    bool encode(const TOKEN::ParameterTypeList*);
    bool encode(const TOKEN::ConditionalExpression::Slore&);
    bool encode(const TOKEN::ConditionalExpression::Slore_e_ce&);
    bool encode(const TOKEN::AbstractDeclarator::Sp&);
    bool encode(const TOKEN::AbstractDeclarator::Sp_dad&);
    bool encode(const TOKEN::UnaryExpression::Spe&);
    bool encode(const TOKEN::UnaryExpression::Si_ue&);
    bool encode(const TOKEN::UnaryExpression::Sd_ue&);
    bool encode(const TOKEN::UnaryExpression::Suo_ce&);
    bool encode(const TOKEN::UnaryExpression::Ss_ue&);
    bool encode(const TOKEN::UnaryExpression::Ss_tn&);
    bool encode(const TOKEN::UnaryExpression::Sa_tn&);
    bool encode(const TOKEN::Statement*);
    bool encode(const TOKEN::InitializerList::Sd_i&);
    bool encode(const TOKEN::StructDeclaration::Ssql_sdl&);
    bool encode(const TOKEN::StructDeclaration::Ssad&);
    bool encode(const TOKEN::Enumerator::Sec&);
    bool encode(const TOKEN::Enumerator::Sec_ce&);
    bool encode(const TOKEN::DirectAbstractDeclarator::Sad&);
    bool encode(const TOKEN::DirectAbstractDeclarator::Stql_ae&);
    bool encode(const TOKEN::DirectAbstractDeclarator::Sp&);
    bool encode(const TOKEN::DirectAbstractDeclarator::Sptl&);
    bool encode(const TOKEN::PostfixExpression::Spe&);
    bool encode(const TOKEN::PostfixExpression::Se&);
    bool encode(const TOKEN::PostfixExpression::Sael&);
    bool encode(const TOKEN::PostfixExpression::Sp_i&);
    bool encode(const TOKEN::PostfixExpression::Sa_i&);
    bool encode(const TOKEN::PostfixExpression::Si&);
    bool encode(const TOKEN::PostfixExpression::Sd&);
    bool encode(const TOKEN::PostfixExpression::Stn_il&);
    bool encode(const TOKEN::CastExpression::Sue&);
    bool encode(const TOKEN::CastExpression::Stn_ce&);
    bool encode(const TOKEN::ParameterDeclaration::Sds_d&);
    bool encode(const TOKEN::ParameterDeclaration::Sds_ad&);
    bool encode(const TOKEN::LabeledStatement::Si_s&);
    bool encode(const TOKEN::LabeledStatement::Sce_s&);
    bool encode(const TOKEN::LabeledStatement::Sce_ce_s&);
    bool encode(const TOKEN::LabeledStatement::Ss&);
    bool encode(const TOKEN::ExpressionStatement*);
    bool encode(const TOKEN::SelectionStatement::Si_e_s&);
    bool encode(const TOKEN::SelectionStatement::Si_e_s_s&);
    bool encode(const TOKEN::SelectionStatement::Ss_e_s&);
    bool encode(const TOKEN::IterationStatement::Sw_e_s&);
    bool encode(const TOKEN::IterationStatement::Sd_s_e&);
    bool encode(const TOKEN::IterationStatement::Sf_e_e_e_s&);
    bool encode(const TOKEN::IterationStatement::Sf_d_e_e_s&);
    bool encode(const TOKEN::JumpStatement::Sg_i&);
    bool encode(const TOKEN::JumpStatement::Sc&);
    bool encode(const TOKEN::JumpStatement::Sb&);
    bool encode(const TOKEN::JumpStatement::Sr_e&);
    bool encode(const TOKEN::Designation*);
    bool encode(const TOKEN::StructDeclarator::Sd&);
    bool encode(const TOKEN::StructDeclarator::Sd_ce&);
    bool encode(const TOKEN::GenericSelection*);
    bool encode(const TOKEN::GenericAssociation::Stn_ae&);
    bool encode(const TOKEN::GenericAssociation::Sae&);
    bool encode(const TOKEN::EqualityExpression::Sre&);
    bool encode(const TOKEN::EqualityExpression::Se_re&);
    bool encode(const TOKEN::EqualityExpression::Sne_re&);
    bool encode(const TOKEN::RelationalExpression::Sse&);
    bool encode(const TOKEN::RelationalExpression::Sl_se&);
    bool encode(const TOKEN::RelationalExpression::Sg_se&);
    bool encode(const TOKEN::RelationalExpression::Sle_se&);
    bool encode(const TOKEN::RelationalExpression::Sge_se&);
    bool encode(const TOKEN::ShiftExpression::Sae&);
    bool encode(const TOKEN::ShiftExpression::Sl_ae&);
    bool encode(const TOKEN::ShiftExpression::Sr_ae&);
    bool encode(const TOKEN::AdditiveExpression::Sme&);
    bool encode(const TOKEN::AdditiveExpression::Sa_me&);
    bool encode(const TOKEN::AdditiveExpression::Ss_me&);
    bool encode(const TOKEN::MultiplicativeExpression::Sce&);
    bool encode(const TOKEN::MultiplicativeExpression::Sm_ce&);
    bool encode(const TOKEN::MultiplicativeExpression::Sd_ce&);
    bool encode(const TOKEN::MultiplicativeExpression::Sr_ce&);
    bool encode(const TOKEN::AttributeStatement*);
    bool encode(const TOKEN::BasicAsm*);
    bool encode(const TOKEN::ExtendedAsm*);
    bool encode(const TOKEN::IncludingFile*);

    // add padding (max: 255)
    // it's should be called before arithmetic element is written.
    bool align(std::stringstream::pos_type alignmentSize);

    // add pointer status to mStream.
    // if pointer has value(i.e. not nullptr), add '\x1' to mStream and return true.
    // otherwise(i.e. nullptr), add '\x0' to mStream and return false.
    template<class T>
    bool addStatus(const T*);

    bool output(const std::string &filename) const;

    // this function is called if variant index size is greater than 255.
    bool variantIndexError(std::size_t indexSize) const;
    // this function is called if array size is greater than 65536.
    bool arraySizeError(std::size_t arraySize) const;

    std::stringstream mStream;
};

template<class T>
auto CacheEncoder::encode(const T *t)
    -> decltype(t->var, bool{})
{
    if(!addStatus(t))
        return true;

    return encode(t->var);
}

template<class T>
auto CacheEncoder::encode(const T *t)
    -> decltype(t->seq, bool{})
{
    if(!addStatus(t))
        return true;

    return encode(t->seq);
}

template<class T>
auto CacheEncoder::encode(const T *t)
    -> decltype(t->tag, bool{})
{
    if(!addStatus(t))
        return true;
    
    return encode(t->tag);
}

template<class T>
auto CacheEncoder::encode(const T *t)
    -> decltype(t->c, bool{})
{
    if(!addStatus(t))
        return true;

    return encode(t->c);
}

template<class ...Types>
bool CacheEncoder::encode(const std::variant<Types...> &v)
{
    if(v.index() > 255ull)
        return variantIndexError(v.index());

    return encode(static_cast<unsigned char>(v.index()))
        && std::visit([&](auto &&arg){return encode(arg);}, v);
}

template<class Array>
auto CacheEncoder::encode(const Array &a)
    -> decltype(a.size(), a.begin(), a.end(), bool{})
{
    if(a.size() > 65536ull)
        return arraySizeError(a.size());

    if(!encode(static_cast<unsigned short>(a.size())))
        return false;

    for(auto &&e : a)
    {
        if(!encode(e))
            return false;
    }

    return true;
}

template<class Integral>
auto CacheEncoder::encode(Integral i)
    -> std::enable_if_t<std::is_integral_v<Integral>, bool>
{
    if(!align(std::alignment_of_v<Integral>))
        return false;
    
    mStream.write(reinterpret_cast<const char*>(&i)
        , sizeof(i));

    return true;
}

template<class Tag>
auto CacheEncoder::encode(Tag t)
    -> std::enable_if_t<std::is_enum_v<Tag>, bool>
{
    return encode(static_cast<std::underlying_type_t<Tag>>(t));
}

template<class First, class Second>
bool CacheEncoder::encode(const std::pair<First, Second> &p)
{
    return encode(p.first)
        && encode(p.second);
}

template<class T>
bool CacheEncoder::addStatus(const T *t)
{
    if(t != nullptr)
    {
        mStream.put('\x1');
        return true;
    }
    else
    {
        mStream.put('\x0');
        return false;
    }
}

}

#endif