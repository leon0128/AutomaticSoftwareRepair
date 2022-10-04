#include "token.hpp"
#include "statement.hpp"

inline namespace COMMON
{

namespace STATEMENT
{

std::size_t addStatement(const Variant &element)
{
    using namespace TOKEN;

    std::size_t statId{NEXT_STATEMENT_ID++};

    std::visit([&](auto &&e){e->statementId = statId;}
        , element);
    
    STATEMENT_MAP.emplace(statId, element);

    return statId;
}

}

}