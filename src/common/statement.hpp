#ifndef COMMON_STATEMENT_HPP
#define COMMON_STATEMENT_HPP

#include <unordered_map>
#include <variant>
#include <memory>
#include <utility>
#include <mutex>
#include <string>

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

// map.first: statement id
// map.second: file and function name. (ex: dirA/fileA::funcA)
inline std::unordered_map<std::size_t, std::string> functionNameMap{};
// mutex for functionNameMap
inline std::mutex functionNameMapMutex{};
// safely add element to functionNameMap
template<class ...Args>
std::pair<decltype(functionNameMap)::iterator, bool> emplaceSafelyToFunctionNameMap(Args &&...args);
// safely get element from functionNameMap.
const std::string &atSafelyToFunctionNameMap(std::size_t statementId);

template<class ...Args>
extern std::pair<decltype(STATEMENT_MAP)::iterator, bool> emplaceSafely(Args &&...args);

inline std::size_t NEXT_STATEMENT_ID{0ull};
// this function increments NEXT_STATEMENT_ID
//  and returns value of NEXT_STATEMENT_ID that before incrementation.
extern std::size_t incrementStatementId();

std::size_t addStatement(const Variant &element);

template<class ...Args>
std::pair<decltype(functionNameMap)::iterator, bool> emplaceSafelyToFunctionNameMap(Args &&...args)
{
    std::lock_guard lock{functionNameMapMutex};
    return functionNameMap.emplace(std::forward<Args>(args)...);
}

template<class ...Args>
std::pair<decltype(STATEMENT_MAP)::iterator, bool> emplaceSafely(Args &&...args)
{
    std::unique_lock lock{statementMapMutex};
    return STATEMENT_MAP.emplace(std::forward<Args>(args)...);
}

// RequiredType: Declaration, FunctionDefinition or Statement
template<class RequiredType>
std::shared_ptr<RequiredType> get(std::size_t statementId)
{
    std::unique_lock lock{statementMapMutex};

    auto &&iter{STATEMENT_MAP.find(statementId)};
    if(iter == STATEMENT_MAP.end())
        return {};

    if(std::holds_alternative<std::shared_ptr<RequiredType>>(iter->second))
        return std::get<std::shared_ptr<RequiredType>>(iter->second);
    else
        return {};
}

}

}

#endif