#ifndef GA_BLOCK_HPP
#define GA_BLOCK_HPP

#include <vector>
#include <string>
#include <utility>
#include <limits>
#include <optional>
#include <unordered_map>
#include <functional>
#include <memory>

namespace TOKEN
{
    class TranslationUnit;
    class CompoundStatement;
    class LabeledStatement;
    class ExpressionStatement;
    class SelectionStatement;
    class IterationStatement;
    class JumpStatement;
    class Statement;
}

namespace GA
{

class Representation;
class Operation;
class Block;

class Block
{
private:
    class Index;

public:
    static Block *createBlock(const TOKEN::TranslationUnit*
        , std::size_t scopeId);
    static bool deleteInvalidOp(const Block*
        , Representation&);

private:
    static Block *createBlock(const TOKEN::CompoundStatement*
        , std::size_t scopeId);
    static Block *createBlock(const TOKEN::LabeledStatement*);
    static Block *createBlock(const TOKEN::SelectionStatement*
        , std::size_t scopeId);
    static Block *createBlock(const TOKEN::IterationStatement*);
    static Block *createBlock(const TOKEN::Statement*);
    static std::pair<std::size_t, Block*> createPair(const TOKEN::Statement*);

    static bool variantError(const std::string &className);
    static bool deleteWarning(const Operation&);

public:
    std::size_t scopeId{std::numeric_limits<std::size_t>::max()};

    std::vector<std::size_t> decls;
    std::vector<std::pair<std::size_t
        , Block*>> stats;

    ~Block();

    Block *copy() const;
    TOKEN::TranslationUnit *createTranslationUnit() const;
    std::shared_ptr<Block> createBlock(const Representation&) const;

    void print() const;

private:
    static bool operateAdd(const Operation&
        , Block*
        , Block::Index&);
    static bool operateSub(const Operation&
        , Block*
        , Block::Index&);
    static bool operateRep(const Operation&
        , Block*
        , Block::Index&);
    static bool selectBlockAndIndex(const Operation&
        , Block*&
        , std::reference_wrapper<Block::Index>&);

    static bool notFoundStatementError(const Operation&);
    static bool noHasDstError();

    TOKEN::CompoundStatement *createCompoundStatement() const;
    TOKEN::Statement *createStatement(const std::pair<std::size_t, Block*>&) const;
    TOKEN::Statement *createStatement() const;
};

class Block::Index
{
public:
    std::vector<
        std::pair<
            std::pair<std::size_t
                , std::size_t>
            , std::optional<Index>>> indices;

    decltype(indices)::iterator find(std::size_t);

    static std::optional<Index> createIndex(const Block*);
};

}

#endif