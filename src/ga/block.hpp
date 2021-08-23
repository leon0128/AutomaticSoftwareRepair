#ifndef GA_BLOCK_HPP
#define GA_BLOCK_HPP

#include <string>
#include <vector>
#include <utility>

#include "../token.hpp"

namespace GA
{

namespace BLOCK
{

class Block;

}

using StatPair = std::pair<std::size_t, BLOCK::Block*>;

namespace BLOCK
{

class Block
{
private:
    std::size_t mScopeId;
    std::vector<std::size_t> mDecls;
    std::vector<StatPair> mStats;

public:
    Block();
    ~Block();
    
    Block(const TOKEN::TranslationUnit*
        , std::size_t scopeId);

    // if block has 2 sub-block which represents if-part and else-part each other,
    // function returns true, elsewise, function returns false.
    bool isIfBlock() const;

    bool add(const std::vector<std::size_t> &pos
        , std::size_t statId);
    bool subtract(const std::vector<std::size_t> &pos);
    bool replace(const std::vector<std::size_t> &pos
        , std::size_t statId);

    TOKEN::TranslationUnit *createTranslationUnit() const;

    Block *copy() const;

    std::size_t scopeId() const noexcept
        {return mScopeId;}
    const auto &decls() const noexcept
        {return mDecls;}
    const auto &stats() const noexcept
        {return mStats;}

private:
    Block(const TOKEN::CompoundStatement*
        , std::size_t scopeId);
    Block(const TOKEN::LabeledStatement*);
    Block(const TOKEN::SelectionStatement*
        , std::size_t scopeId);
    Block(const TOKEN::IterationStatement*);
    Block(const TOKEN::Statement*);
    Block(std::size_t scopeId);

    // use pos[0], pos[1], ... , pos[size - 2]
    Block *getBlock(const std::vector<std::size_t> &pos);

    StatPair createStatPair(const TOKEN::Statement*);

    TOKEN::CompoundStatement *createCompoundStatement() const;
    TOKEN::Statement *createStatement(const StatPair&) const;
    TOKEN::Statement *createStatement() const;

    void move(Block &&other);

    bool variantError(const std::string &className) const;
    bool nullptrError(const std::string &className) const;
};

}

}

#endif