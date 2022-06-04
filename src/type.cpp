#include <iostream>
#include <map>
#include <typeinfo>

#include "analyzer.hpp"
#include "type.hpp"

namespace TYPE
{

std::optional<Type> extractType(const Typedef &typedefType)
{
    return addQualifiers(std::any_cast<Type>(typedefType.refType)
        , typedefType.quals);
}

std::optional<Type> addQualifiers(const Type &type
    , const Qualifiers &quals)
{
    Type returnType{type};

    if(std::holds_alternative<Base>(returnType.var))
        std::get<Base>(returnType.var).quals.flags |= quals.flags;
    else if(std::holds_alternative<Pointer>(returnType.var))
        std::get<Pointer>(returnType.var).quals.flags |= quals.flags;
    else if(std::holds_alternative<Enum>(returnType.var))
        std::get<Enum>(returnType.var).quals.flags |= quals.flags;
    else if(std::holds_alternative<Struct>(returnType.var))
        std::get<Struct>(returnType.var).quals.flags |= quals.flags;
    else if(std::holds_alternative<Typedef>(returnType.var))
        std::get<Typedef>(returnType.var).quals.flags |= quals.flags;
    else
    {
        notSupportedError("TYPE::addQualifiers()");
        return {std::nullopt};
    }

    return {std::move(returnType)};
}

bool equalTo(const Type &lhs
    , const Type &rhs)
{
    if(std::holds_alternative<Typedef>(lhs.var)
        || std::holds_alternative<Typedef>(rhs.var))
    {
        std::optional<Type> lo{std::holds_alternative<Typedef>(lhs.var)
            ? extractType(std::get<Typedef>(lhs.var))
            : lhs};
        std::optional<Type> ro{std::holds_alternative<Typedef>(rhs.var)
            ? extractType(std::get<Typedef>(rhs.var))
            : rhs};
        if(!lo || !ro)
            return false;

        return equalTo(lo.value()
            , ro.value());
    }
    else
    {
        if(lhs.var.index() != rhs.var.index())
            return false;

        if(std::holds_alternative<std::monostate>(lhs.var))
            return false;
        
        if(std::holds_alternative<Base>(lhs.var))
            return equalTo(std::get<Base>(lhs.var)
                , std::get<Base>(rhs.var));
        else if(std::holds_alternative<Function>(lhs.var))
            return equalTo(std::get<Function>(lhs.var)
                , std::get<Function>(rhs.var));
        else if(std::holds_alternative<Array>(lhs.var))
            return equalTo(std::get<Array>(lhs.var)
                , std::get<Array>(rhs.var));
        else if(std::holds_alternative<Pointer>(lhs.var))
            return equalTo(std::get<Pointer>(lhs.var)
                , std::get<Pointer>(rhs.var));
        else if(std::holds_alternative<Enum>(lhs.var))
            return equalTo(std::get<Enum>(lhs.var)
                , std::get<Enum>(rhs.var));
        else if(std::holds_alternative<Struct>(lhs.var))
            return equalTo(std::get<Struct>(lhs.var)
                , std::get<Struct>(rhs.var));
        else if(std::holds_alternative<Bitfield>(lhs.var))
            return equalTo(std::get<Bitfield>(lhs.var)
                , std::get<Bitfield>(rhs.var));
        else
            return notSupportedError("");

        return true;
    }
}

bool equalTo(const Base &lhs
    , const Base &rhs)
{
    return lhs.tag == rhs.tag
        && lhs.quals.flags == rhs.quals.flags;
}

bool equalTo(const Function &lhs
    , const Function &rhs)
{
    if(!equalTo(std::any_cast<Type>(lhs.retType)
        , std::any_cast<Type>(rhs.retType)))
        return false;
    
    if(lhs.paramTypes.size() != rhs.paramTypes.size())
        return false;
    for(std::size_t i{0ull};
        i < lhs.paramTypes.size();
        i++)
    {
        if(!equalTo(lhs.paramTypes[i]
            , rhs.paramTypes[i]))
            return false;
    }

    if(lhs.isVariable != rhs.isVariable)
        return false;
    
    return true;
}

bool equalTo(const Array &lhs
    , const Array &rhs)
{
    if(!equalTo(std::any_cast<Type>(lhs.eleType)
        , std::any_cast<Type>(rhs.eleType)))
        return false;
    
    if(lhs.quals.flags != rhs.quals.flags)
        return false;
    
    return true;
}

bool equalTo(const Pointer &lhs
    , const Pointer &rhs)
{
    if(!equalTo(std::any_cast<Type>(lhs.refType)
        , std::any_cast<Type>(rhs.refType)))
        return false;
    
    if(lhs.quals.flags != rhs.quals.flags)
        return false;
    
    return true;
}

bool equalTo(const Enum &lhs
    , const Enum &rhs)
{
    if(lhs.quals.flags != rhs.quals.flags)
        return false;

    auto &&lhsIter{Analyzer::typeMap().find(lhs.id)};
    auto &&rhsIter{Analyzer::typeMap().find(rhs.id)};

    if(!lhsIter->second->isDefined()
        || !rhsIter->second->isDefined())
        return false;
    
    const auto &lhsEnum{std::dynamic_pointer_cast<EnumInfo>(lhsIter->second)};
    const auto &rhsEnum{std::dynamic_pointer_cast<EnumInfo>(rhsIter->second)};

    if(lhsEnum->members.size() != rhsEnum->members.size())
        return false;
    
    for(std::size_t i{0ull};
        i < lhsEnum->members.size();
        i++)
    {
        if(lhsEnum->members[i].first != rhsEnum->members[i].first)
            return false;
    }
    
    return true;
}

bool equalTo(const Struct &lhs
    , const Struct &rhs)
{
    if(lhs.quals.flags != rhs.quals.flags)
        return false;

    auto &&lhsIdInfo{Analyzer::typeMap().at(lhs.id)};
    auto &&rhsIdInfo{Analyzer::typeMap().at(rhs.id)};
    const auto &lhsStruct{std::dynamic_pointer_cast<StructInfo>(lhsIdInfo)};
    const auto &rhsStruct{std::dynamic_pointer_cast<StructInfo>(rhsIdInfo)};
    if(lhsStruct == nullptr
        || rhsStruct == nullptr)
        return false;

    if(lhsStruct->isUnion != rhsStruct->isUnion)
        return false;

    if(lhsStruct->isDefined()
         != rhsStruct->isDefined())
        return false;

    if(lhsStruct->isDefined())
    {
        if(lhsStruct->members.size() != rhsStruct->members.size())
            return false;
        
        for(std::size_t i{0ull};
            i < lhsStruct->members.size();
            i++)
        {
            if(!equalTo(lhsStruct->members[i].first
                , rhsStruct->members[i].first)
                || lhsStruct->members[i].second != rhsStruct->members[i].second)
                return false;
        }
    }
    else
    {
        if(lhsStruct->tag() != rhsStruct->tag())
            return false;
    }

    return true;
}

bool equalTo(const Bitfield &lhs
    , const Bitfield &rhs)
{
    if(equalTo(std::any_cast<Type>(lhs.refType)
        , std::any_cast<Type>(rhs.refType)))
        return false;
    
    return true;
}

bool equalTo(std::size_t lhs
    , std::size_t rhs)
{
    auto &&lhsIter{Analyzer::typeMap().find(lhs)};
    auto &&rhsIter{Analyzer::typeMap().find(rhs)};

    if(lhsIter->second->derivedTag() != rhsIter->second->derivedTag())
        return false;
    
    switch(lhsIter->second->derivedTag())
    {
        case(IdInfo::DerivedTag::STRUCT):
            return equalTo(Struct{lhs}
                , Struct{rhs});
        case(IdInfo::DerivedTag::ENUM):
            return equalTo(Enum{lhs}
                , Enum{rhs});
    }

    return true;
}

std::string Qualifiers::name() const
{
    static const std::map<Tag, std::string> nameMap
        {{Tag::CONST, "const"}
            , {Tag::RESTRICT, "restrict"}
            , {Tag::VOLATILE, "volatile"}
            , {Tag::ATOMIC, "atomic"}};

    std::string qualifiersName;
    
    for(const auto &[tag, tagName] : nameMap)
    {
        if(flags.test(static_cast<std::size_t>(tag)))
        {
            qualifiersName += tagName;
            qualifiersName.push_back(' ');
        }
    }

    return qualifiersName;
}

std::string Base::name() const
{
    static const std::map<Tag, std::string> nameMap
        {{Tag::VOID, "void"}
            , {Tag::CHAR, "char"}
            , {Tag::S_CHAR, "signed char"}
            , {Tag::U_CHAR, "unsigned char"}
            , {Tag::S_SHORT, "short"}
            , {Tag::U_SHORT, "unsigned short"}
            , {Tag::S_INT, "int"}
            , {Tag::U_INT, "unsigned int"}
            , {Tag::S_LONG, "long"}
            , {Tag::U_LONG, "unsigned long"}
            , {Tag::S_LONG_LONG, "long long"}
            , {Tag::U_LONG_LONG, "unsigned long long"}
            , {Tag::FLOAT, "float"}
            , {Tag::DOUBLE, "double"}
            , {Tag::LONG_DOUBLE, "long double"}
            , {Tag::BOOL, "bool"}
            , {Tag::FLOAT_COMPLEX, "float complex"}
            , {Tag::DOUBLE_COMPLEX, "double complex"}
            , {Tag::LONG_DOUBLE_COMPLEX, "long double complex"}
            , {Tag::BUILTIN_VA_LIST, "builtin_va_list"}};

    std::string baseName{quals.name()};

    baseName += nameMap.at(tag);

    return baseName;
}

std::string Function::name() const
{
    std::string functionName;

    if(retType.type() == typeid(Type))
        functionName += std::any_cast<Type>(retType).name();
    else
        functionName += "[[(Function)unknown object]]";

    functionName.push_back('(');

    for(const auto &param : paramTypes)
    {
        functionName += param.name();
        functionName.push_back(',');
    }

    for(std::size_t i{0ull}; i < paramTypes.size(); i++)
    {
        if(i != 0ull)
            functionName.push_back(',');
        functionName += paramTypes[i].name();
    }

    if(isVariable)
    {
        if(!paramTypes.empty())
            functionName.push_back(',');
        functionName += "...";
    }

    functionName.push_back(')');

    return functionName;
}

std::string Array::name() const
{
    std::string arrayName;

    if(eleType.type() == typeid(Type))
        arrayName += std::any_cast<Type>(eleType).name();
    else
        arrayName += "[[(Array)unknown object]]";

    arrayName.push_back('[');

    if(hasStatic)
        arrayName += "static ";
    
    arrayName += quals.name();
    arrayName.push_back(' ');

    if(exp.get() != nullptr)
    {
        arrayName += TOKEN::str(exp.get());
        arrayName.push_back(' ');
    }

    if(isVariable)
        arrayName.push_back('*');

    arrayName.push_back(']');

    return arrayName;
}

std::string Pointer::name() const
{
    std::string pointerName;

    if(refType.type() == typeid(Type))
        pointerName += std::any_cast<Type>(refType).name();
    else
        pointerName += "[[(Pointer)unknown object]]";

    pointerName += "*";
    
    pointerName += quals.name();

    return pointerName;
}

std::string Enum::name() const
{
    std::string enumName{quals.name()};

    auto &&idInfo{Analyzer::typeMap().at(id)};
    auto &&enumInfo{std::dynamic_pointer_cast<EnumInfo>(idInfo)};

    if(enumInfo.get() != nullptr)
    {
        enumName += "[[(Enum)unknown object]]";
        return enumName;
    }

    enumName += "enum ";
    enumName += enumInfo->tag();

    return enumName;
}

std::string Struct::name() const
{
    std::string structName{quals.name()};

    auto &&idInfo{Analyzer::typeMap().at(id)};
    auto &&structInfo{std::dynamic_pointer_cast<StructInfo>(idInfo)};

    if(structInfo.get() != nullptr)
    {
        structName += "[[(Struct)unknown object]]";
        return structName;
    }

    if(structInfo->isUnion)
        structName += "union ";
    else
        structName += "struct ";

    structName += structInfo->tag();

    return structName;
}

std::string Bitfield::name() const
{
    std::string bitfieldName;

    if(refType.type() != typeid(Type))
    {
        bitfieldName += "[[(Bitfield)unknown object]]";
        return bitfieldName;
    }

    bitfieldName += std::any_cast<Type>(refType).name();
    bitfieldName.push_back(':');
    bitfieldName += TOKEN::str(exp.get());

    return bitfieldName;
}

std::string Typedef::name() const
{
    std::string typedefName{quals.name()};

    if(refType.type() != typeid(Type))
    {
        typedefName += "[[(Typedef)unknown object]]";
        return typedefName;
    }

    typedefName += "[[typedef ";
    typedefName += std::any_cast<Type>(refType).name();
    typedefName += "]]";

    return typedefName;
}

std::string Lvalue::name() const
{
    std::string lvalueName;

    if(refType.type() != typeid(Type))
    {
        lvalueName += "[[(Lvalue) unknown object]]";
        return lvalueName;
    }

    lvalueName += "[[lvalue ";
    lvalueName += std::any_cast<Type>(refType).name();
    lvalueName += "]]";

    return lvalueName;
}

std::string Initializer::name() const
{
    std::string initializerName;

    initializerName += "initializer-list type";

    return initializerName;
}

// helper macro for Type::name() const
// if(std::holds_alternative<TYPENAME>(VARIABLE))
//      return std::get<TYPENAME>(VARIABLE);
#define IF_HOLDS_RETURN_NAME(TYPENAME, VARIABLE) \
    if(std::holds_alternative<TYPENAME>(VARIABLE)) \
        return std::get<TYPENAME>(VARIABLE).name();

std::string Type::name() const
{
    if(std::holds_alternative<std::monostate>(var))
        return {"[[(Type)std::monostate]]"};
    else IF_HOLDS_RETURN_NAME(Base, var)
    else IF_HOLDS_RETURN_NAME(Function, var)
    else IF_HOLDS_RETURN_NAME(Array, var)
    else IF_HOLDS_RETURN_NAME(Pointer, var)
    else IF_HOLDS_RETURN_NAME(Enum, var)
    else IF_HOLDS_RETURN_NAME(Struct, var)
    else IF_HOLDS_RETURN_NAME(Bitfield, var)
    else IF_HOLDS_RETURN_NAME(Typedef, var)
    else IF_HOLDS_RETURN_NAME(Lvalue, var)
    else IF_HOLDS_RETURN_NAME(Initializer, var)
    else
        return {"[[(Type)unknown type]]"};
}

#undef IF_HOLDS_RETURN_NAME

bool notSupportedError(const std::string &msg)
{
    std::cerr << "Type error:\n"
        "    what: not supported.\n"
        "    ---: " << msg
        << std::endl;
    return false;
}

IdInfo::IdInfo(DerivedTag dTag
    , const std::string &tag)
    : mDerivedTag{dTag}
    , mId{NEXT_ID++}
    , mTag{tag}
    , mIsDefined{false}
{
}

IdInfo::~IdInfo()
{
}

StructInfo::StructInfo(const std::string &tag
    , bool b)
    : IdInfo{IdInfo::DerivedTag::STRUCT
        , tag}
    , members{}
    , isUnion{b}
{
}

EnumInfo::EnumInfo(const std::string &tag)
    : IdInfo{IdInfo::DerivedTag::ENUM
        , tag}
    , members{}
{
}

}