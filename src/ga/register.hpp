#ifndef GA_REGISTER_HPP
#define GA_REGISTER_HPP

#include <optional>

#include "../token.hpp"

namespace GA
{

class Register;

class Register
{
public:
    Register() = delete;

    static std::optional<std::size_t> execute(TOKEN::Statement*);

private:
    static std::optional<std::size_t> registerStatement(TOKEN::Statement*);
    static std::optional<std::size_t> registerDeclaration(TOKEN::Declaration*);

    static bool variantError(const std::string &className);
};

}

#endif