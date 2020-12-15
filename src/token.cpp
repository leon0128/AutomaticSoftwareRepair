#include "token.hpp"

Token::~Token()
{
    if(std::holds_alternative<Keyword*>(var))
        delete std::get<Keyword*>(var);
    else if(std::holds_alternative<Identifier*>(var))
        delete std::get<Identifier*>(var);
    else if(std::holds_alternative<Constant*>(var))
        delete std::get<Constant*>(var);
    else if(std::holds_alternative<StringLiteral*>(var))
        delete std::get<StringLiteral*>(var);
    else if(std::holds_alternative<Punctuator*>(var))
        delete std::get<Punctuator*>(var);
}

Identifier::~Identifier()
{
    for(auto &&v : seq)
    {
        if(std::holds_alternative<IdentifierNondigit*>(v))
            delete std::get<IdentifierNondigit*>(v);
        else if(std::holds_alternative<Digit*>(v))
            delete std::get<Digit*>(v);
    }
}

Constant::~Constant()
{
    if(std::holds_alternative<IntegerConstant*>(var))
        delete std::get<IntegerConstant*>(var);
    else if(std::holds_alternative<FloatingConstant*>(var))
        delete std::get<FloatingConstant*>(var);
    else if(std::holds_alternative<EnumerationConstant*>(var))
        delete std::get<EnumerationConstant*>(var);
    else if(std::holds_alternative<CharacterConstant*>(var))
        delete std::get<CharacterConstant*>(var);
}

StringLiteral::~StringLiteral()
{
    delete ep;
    delete scs;
}