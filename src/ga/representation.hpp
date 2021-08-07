#ifndef GA_REPRESENTATION_HPP
#define GA_REPRESENTATION_HPP

#include <vector>
#include <optional>
#include <string>
#include <utility>
#include <memory>
#include <unordered_set>

namespace TOKEN
{
    class TranslationUnit;
    class FunctionDefinition;
    class Statement;
}

namespace GA
{

class Operation;
class Representation;
class Block;

class Operation
{
private:
    inline static std::vector<
        std::pair<
            std::pair<
                std::vector<std::size_t>
                , std::vector<std::size_t>>
            , std::size_t>> NEW_STATEMENT_IDS{};
    inline static std::unordered_set<std::size_t> CREATED_STATEMENT_IDS{};
    inline static std::vector<std::size_t> SELECTABLE_FUNCTION_IDS{};

public:
    enum class Tag : unsigned char;

    Tag tag{0u};
    std::vector<std::size_t> src;
    std::vector<std::size_t> dst;
    std::vector<std::size_t> ids;
    std::size_t createdStatId{0ull};

    void print() const;

    static bool initialize(const TOKEN::TranslationUnit *src);

    static std::optional<Operation> createRandomOp(const Block *src
        , const std::vector<const Block*> &pool);
    static std::optional<std::size_t> getStatementId(const Operation&);
    static bool isCreatedStatement(std::size_t);

    inline static constexpr const auto &newStatementIds() noexcept
        {return NEW_STATEMENT_IDS;}

private:
    static bool selectSubDstPos(const Block*
        , std::vector<std::size_t>&);
    static bool selectAddDstPos(const Block*
        , std::vector<std::size_t>&);
    static bool selectAddSrcPos(const std::vector<const Block*>&
        , std::vector<std::size_t>&);
    static bool selectRepDstPos(const Block*
        , std::vector<std::size_t>&);
    static bool selectRepSrcPos(const std::vector<const Block*>&
        , std::vector<std::size_t>&);
    static bool selectAlternativeIds(const std::vector<const Block*>&
        , const Block*
        , Operation&);
    static std::optional<std::size_t> selectFunctionPos(const Block*);

    static std::optional<std::size_t> divideStatement(TOKEN::Statement*
        , std::size_t scopeId);

    static std::optional<std::size_t> getSrcStatementId(const std::vector<const Block*>&
        , const std::vector<std::size_t>&);
    static std::optional<std::size_t> getScopeId(const Block*
        , const std::vector<std::size_t>&);

    static std::shared_ptr<TOKEN::Statement> getStatement(std::size_t);
    static std::size_t getFunctionName(const TOKEN::Declarator*);

    static bool tagError();
    static bool noHasFunctionError();
    static bool noHasStatement(const std::string&);
    static bool positionError(const std::string&);
    static bool variantError(const std::string&);
    static bool notFoundStatementError(std::size_t);
    static bool notFoundStatementError(const std::string&);
    static bool notCreatedOperationError();
    static bool notFoundTargetFunction(const std::string&);
};

enum class Operation::Tag : unsigned char
{
    ADD
    , SUB
    , REP
};

class Representation
{
public:
    std::vector<Operation> ops;

    bool merge(const Block*
        , const Representation&);
    void print() const;

    static std::optional<Representation> createRandomRep(const Block *src
        , const std::vector<const Block*> &pool);
};

}

#endif