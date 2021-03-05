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

    std::vector<TOKEN::Declaration*> decls;
    std::vector<Element> elems;

    template<class Decls, class Elems>
    Block(Decls &&d, Elems &&e)
        : decls(d)
        , elems(e){}
    ~Block();

    Block *copy() const;
};

struct Operation
{
    std::vector<std::size_t> src;
    std::vector<std::size_t> dst;
    OpTag tag;

    Operation()
        : src()
        , dst()
        , tag(OpTag::ADD){}
};

struct Representation
{
    const Block *block;
    std::vector<Operation> ops;

    Representation()
        : block(nullptr)
        , ops(){}

    Representation &append(const Representation&);
};

extern Block *createBlock(const TOKEN::TranslationUnit*);
extern Block *createBlock(const TOKEN::CompoundStatement*);
extern Block *createBlock(const TOKEN::LabeledStatement*);
extern Block *createBlock(const TOKEN::SelectionStatement*);
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

extern Representation createRandomRep(const Block*
    , std::size_t num = 1);
extern OpTag selectOpTag(OpTag def = OpTag::ADD);
extern TOKEN::TranslationUnit *createTranslationUnit(const Block*);
extern TOKEN::CompoundStatement *createCompoundStatement(const Block*);
extern TOKEN::Statement *createStatement(const Block::Element&);

}

#endif