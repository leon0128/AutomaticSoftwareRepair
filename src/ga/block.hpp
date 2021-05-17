#ifndef GA_BLOCK_HPP
#define GA_BLOCK_HPP

#include <vector>
#include <string>
#include <utility>
#include <limits>

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

class Block;

class Block
{
public:
    static Block *createBlock(const TOKEN::TranslationUnit*
        , std::size_t scopeId);
    static TOKEN::TranslationUnit *createTranslationUnit(const Block*);

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

public:
    std::size_t scopeId{std::numeric_limits<std::size_t>::max()};

    std::vector<std::size_t> decls;
    std::vector<std::pair<std::size_t
        , Block*>> stats;

    ~Block();

    Block *copy() const;
};

}

#endif