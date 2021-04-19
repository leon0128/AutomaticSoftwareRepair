#ifndef GA_REPRESENTATION_HPP
#define GA_REPRESENTATION_HPP

#include <vector>
#include <variant>

namespace TOKEN
{
    class Declaration;
    class FunctionDefinition;
    class Statement;
    class TranslationUnit;
    class CompoundStatement;
    class LabeledStatement;
    class ExpressionStatement;
    class SelectionStatement;
    class IterationStatement;
    class JumpStatement;
};

namespace GA
{

enum class OpTag : signed char;
class Block;
class Operation;
class Representation;

enum class OpTag : signed char
{
    ADD
    , SUB
    , SWAP
};

struct Block
{
    using FunctionOrStatement = std::variant<TOKEN::FunctionDefinition*, TOKEN::Statement*>;
    using Element = std::pair<FunctionOrStatement, Block*>;

    std::size_t scopeId;

    std::vector<TOKEN::Declaration*> decls;
    std::vector<Element> elems;

    template<class Decls, class Elems>
    Block(std::size_t id, Decls &&d, Elems &&e)
        : scopeId{id}
        , decls(d)
        , elems(e){}
    ~Block();

    Block *copy() const;
};

struct Operation
{
    std::vector<std::size_t> src;
    std::vector<std::size_t> dst;
    std::vector<std::size_t> ids;
    OpTag tag{OpTag::ADD};
};

struct Representation
{
    const Block *block;
    std::vector<Operation> ops;

    Representation()
        : block(nullptr)
        , ops(){}

    Representation &append(const Representation&);
    void print() const;
};

extern Block *createBlock(const TOKEN::TranslationUnit*
    , std::size_t scopeId);
extern Block *createBlock(const TOKEN::CompoundStatement*
    , std::size_t scopeId);
extern Block *createBlock(const TOKEN::LabeledStatement*);
extern Block *createBlock(const TOKEN::SelectionStatement*
    , std::size_t scopeId);
extern Block *createBlock(const TOKEN::IterationStatement*);
extern Block::Element createElement(const TOKEN::Statement*);
extern bool manipulateAdd(const Block *srcBlock
    , Block *dstBlock
    , const std::vector<std::size_t> &srcPos
    , const std::vector<std::size_t> &dstPos);
extern bool manipulateSub(Block *dstBlock
    , const std::vector<std::size_t> &dstPos);
extern bool manipulateSwap(Block *dstBlock
    , const std::vector<std::size_t> &lhsPos
    , const std::vector<std::size_t> &rhsPos);

extern Block *createBlock(const Representation&);

extern Representation createRandomRep(const std::vector<const Block*>&
    , std::size_t num = 1ull);
extern OpTag selectOpTag(OpTag def = OpTag::ADD);
extern TOKEN::TranslationUnit *createTranslationUnit(const Block*);
extern TOKEN::CompoundStatement *createCompoundStatement(const Block*);
extern TOKEN::Statement *createStatement(const Block::Element&);
extern TOKEN::Statement *createStatement(const Block*);

}

#endif