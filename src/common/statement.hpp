#ifndef COMMON_STATEMENT_HPP
#define COMMON_STATEMENT_HPP

#include <unordered_map>
#include <variant>
#include <memory>
#include <utility>
#include <mutex>

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

inline extern std::unordered_map<std::size_t, Variant> STATEMENT_MAP;
inline decltype(STATEMENT_MAP) STATEMENT_MAP{};
inline extern std::recursive_mutex statementMapMutex;
inline decltype(statementMapMutex) statementMapMutex{};


template<class ...Args>
extern std::pair<decltype(STATEMENT_MAP)::iterator, bool> emplaceSafely(Args &&...args);

inline std::size_t NEXT_STATEMENT_ID{0ull};
extern std::size_t nextIdSafely();

std::size_t addStatement(const Variant &element);


template<class ...Args>
std::pair<decltype(STATEMENT_MAP)::iterator, bool> emplaceSafely(Args &&...args)
{
    std::unique_lock lock{statementMapMutex};
    return STATEMENT_MAP.emplace(std::forward<Args>(args)...);
}

}

}

#endif