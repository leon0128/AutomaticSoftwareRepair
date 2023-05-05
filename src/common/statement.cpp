#include "token.hpp"
#include "statement.hpp"

inline namespace COMMON
{

namespace STATEMENT
{

const std::string &atSafelyToFunctionNameMap(std::size_t statementId)
{
    std::lock_guard lock{functionNameMapMutex};
    return functionNameMap.at(statementId);
}

std::size_t incrementStatementId()
{
    static std::mutex mutex;
    std::lock_guard lock{mutex};
    return NEXT_STATEMENT_ID++;
}

std::size_t addStatement(const Variant &element)
{
    using namespace TOKEN;

    std::size_t statId{incrementStatementId()};

    std::visit([&](auto &&e){e->statementId = statId;}
        , element);
    
    STATEMENT_MAP.emplace(statId, element);

    return statId;
}

}

}