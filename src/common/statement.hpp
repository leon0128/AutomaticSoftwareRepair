#ifndef COMMON_STATEMENT_HPP
#define COMMON_STATEMENT_HPP

#include <unordered_map>
#include <variant>
#include <memory>

inline namespace COMMON
{

namespace TOKEN
{
    class Declaration;
    class FunctionDefinition;
    class Statement;
}

namespace STATEMENT
{

using Variant
    = std::variant<std::shared_ptr<TOKEN::Declaration>
        , std::shared_ptr<TOKEN::FunctionDefinition>
        , std::shared_ptr<TOKEN::Statement>>;

inline std::unordered_map<std::size_t, Variant> STATEMENT_MAP{};
inline std::size_t NEXT_STATEMENT_ID{0ull};

std::size_t addStatement(const Variant &element);

}

}

#endif