#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>
#include <variant>

#include "../system.hpp"
#include "../random.hpp"
#include "../analyzer.hpp"
#include "../token.hpp"
#include "../configure.hpp"
#include "../scope.hpp"
#include "selector.hpp"
#include "representation.hpp"
#include "controller.hpp"

namespace GA
{

const Analyzer Controller::INIT_VALUE{};
const std::vector<Analyzer> Controller::INIT_VALUES{};

Controller::Controller()
    : mSrcAnalyzer{std::cref(INIT_VALUE)}
    , mAnalyzerPool{std::cref(INIT_VALUES)}
    , mSrcBlock{nullptr}
    , mBlockPool{}
{
}

Controller::~Controller()
{
    delete mSrcBlock;
    for(auto &&block : mBlockPool)
        delete block;
}

bool Controller::execute(const Analyzer &source
    , const std::vector<Analyzer> &pool)
{
    mSrcAnalyzer = std::cref(source);
    mAnalyzerPool = std::cref(pool);

    if(!initialize())
        return false;

    std::cout << "Scope\n" << std::flush;
    for(const auto &pair : SCOPE::Scope::scopeMap())
    {
        std::cout << "idx: " << pair.first << "\n"
            "    tag: " << static_cast<int>(pair.second->scopeTag())
            << std::endl;
    }
    std::cout << "Id\n" << std::endl;
    for(const auto &pair : SCOPE::Scope::identifierMap())
    {
        std::cout << "idx: " << pair.first << "\n"
            "    name: " << pair.second->str()
            << std::endl;
    }

    Representation result;
    if(!geneticAlgorithm(result))
        return false;

    result.print();

    return true;
}

bool Controller::initialize()
{
    if(!(mSrcBlock = ::GA::createBlock(mSrcAnalyzer.get().translationUnit()
        , mSrcAnalyzer.get().scope()->id())))
        return false;
    
    for(const auto &analyzer : mAnalyzerPool.get())
    {
        if(!mBlockPool.emplace_back(::GA::createBlock(analyzer.translationUnit()
            , analyzer.scope()->id())))
            return false;
    }
    
    return true;
}

bool Controller::geneticAlgorithm(Representation &rep)
{
    std::vector<Representation> reps;
    for(std::size_t i{0};
        i < Configure::POP_SIZE;
        i++)
    {
        if(!createRandomRepresentation(reps.emplace_back()))
            return false;
    }
    
    for(std::size_t gen{0};
        gen < Configure::MAX_GEN;
        gen++)
    {
        std::vector<Representation> nextReps;
        Scores scores;

        for(std::size_t i{0};
            i < reps.size();
            i++)
        {
            auto &&pair{scores.emplace_back(fitness(reps[i]), i)};
        }

        std::sort(scores.begin()
            , scores.end()
            , [](const auto &lhs
                , const auto &rhs)
                {return lhs.first > rhs.first;});
        
        rep = reps[scores.front().second];
        if(scores.front().first >= Configure::GOAL_SCORE)
            break;
        
        for(std::size_t i{0};
            i < Configure::NUM_ELITE;
            i++)
            nextReps.push_back(reps[scores[i].second]);
        
        for(std::size_t i{Configure::NUM_ELITE};
            i < Configure::POP_SIZE;
            i++)
        {
            nextReps.emplace_back();
            if(!manipulate(reps
                , scores
                , nextReps.back()))
                return false;
        }

        reps.swap(nextReps);
    }

    return true;
}

int Controller::fitness(const Representation &rep) const
{
    if(!outputToFile(Configure::TEST_FILENAME
        , rep))
        return std::numeric_limits<int>::min();
    
    if(!compile(Configure::TEST_FILENAME))
        return std::numeric_limits<int>::min();
    
    int score{0};
    score += evaluate(Configure::POSITIVE_TEST_PREFIX
        , Configure::NUM_POSITIVE_TEST
        , Configure::POSITIVE_TEST_WEIGHT);
    score += evaluate(Configure::NEGATIVE_TEST_PREFIX
        , Configure::NUM_NEGATIVE_TEST
        , Configure::NEGATIVE_TEST_WEIGHT);
    
    return score;
}

bool Controller::outputToFile(const std::string &filename
    , const Representation &rep) const
{
    auto &&block{createBlock(rep)};
    if(!block)
        return false;

    std::shared_ptr<TOKEN::TranslationUnit> translationUnit{createTranslationUnit(block.get())};
    if(!translationUnit)
        return false;
    
    std::fstream fstr{filename
        , std::ios::out};
    if(!fstr.is_open())
        return openError(filename);

    fstr << TOKEN::str(translationUnit.get())
        << std::endl;
    fstr.close();

    return true;
}

bool Controller::compile(const std::string &filename) const
{
    if(SYSTEM::system(Configure::COMPILER
        , filename
        , "-o"
        , Configure::EXECUTION_NAME
        , "> /dev/null 2>&1")
        != 0)
        return compileError(filename);
    
    return true;
}

int Controller::evaluate(const std::string &prefix
    , std::size_t num
    , int weight) const
{
    int score{0};
    for(std::size_t i{0ull};
        i < num;
        i++)
    {
        if(SYSTEM::system("sh"
            , Configure::TEST_SCRIPT
            , std::string{"./"} + Configure::EXECUTION_NAME
            , prefix + std::to_string(i)) == 0)
            score += weight;
    }

    return score;
}

bool Controller::manipulate(const std::vector<Representation> &reps
    , const Scores &scores
    , Representation &rep)
{
    rep = reps[select(scores)];

    if(Configure::ADDING_NEW_OPERATION_PROBABILITY >= RAND.floating())
    {
        if(!createRandomOperation(rep.ops.emplace_back()))
            return false;
    }
    else
        rep.append(reps[select(scores)]);
    
    return true;
}

std::size_t Controller::select(const Scores &scores) const
{
    Scores sample;
    std::sample(scores.begin()
        , scores.end()
        , std::back_inserter(sample)
        , Configure::TOURNAMENT_SIZE
        , RAND.engine());
    
    return std::max_element(sample.begin()
        , sample.end()
        , [](const auto &lhs
            , const auto &rhs)
            {return lhs.first > rhs.first;})->second;
}

bool Controller::selectBlock(std::vector<std::size_t> &pos
    , bool isPool)
{
    const Block *block{nullptr};

    if(isPool)
    {
        pos.push_back(RAND(mBlockPool.size()));
        block = mBlockPool[pos.back()];
    }
    else
        block = mSrcBlock;
    
    while(block)
    {
        if(block->elems.empty())
            return statementSelectionError("statement is empty");
        
        pos.push_back(RAND.random<std::size_t>(block->elems.size()));
        block = block->elems[pos.back()].second;
    }

    return true;
}

bool Controller::selectAlternativeIdentifier(std::vector<std::size_t> &ids
    , Block::Element &element
    , std::size_t scopeId)
{
    if(bool(element.second))
        return invalidElementError("element has block");
    
    if(!std::holds_alternative<TOKEN::Statement*>(element.first))
        return invalidElementError("");

    auto &&statement{std::get<TOKEN::Statement*>(element.first)};
    Selector selector;
    if(!selector.execute(scopeId
        , statement
        , ids))
        return false;
    
    return true;
}

bool Controller::getBlockElement(Block::Element &element
    , std::size_t &scopeId
    , const std::vector<std::size_t> &pos
    , bool isPool) const
{
    const Block *block{nullptr};
    std::size_t count{0ull};

    if(isPool)
    {
        block = mBlockPool[pos.front()];
        count++;
    }
    else
        block = mSrcBlock;

    for(;
        count < pos.size();
        count++)
    {
        if(pos[count] >= block->elems.size()
            || !block)
            return elementNotFoundError("");

        element = block->elems[pos[count]];
        scopeId = block->scopeId;
        block = element.second;
    }

    return true;
}

bool Controller::getBlock(const std::vector<std::size_t> &pos
    , Block *&block) const
{
    for(std::size_t i{0ull};
        i + 1 < pos.size();
        i++)
    {
        if(!block
            || block->elems.size() <= pos[i])
            return elementNotFoundError("Controller::getBlock");

        block = block->elems[pos[i]].second;
    }

    return true;
}

std::shared_ptr<Block> Controller::createBlock(const Representation &rep) const
{
    std::shared_ptr<Block> block{rep.block->copy()};

    for(const auto &op : rep.ops)
    {
        if(!operate(op
            , block.get()))
            ;
    }

    return std::move(block);
}

bool Controller::operate(const Operation &op
    , Block *block) const
{
    switch(op.tag)
    {
        case(OpTag::ADD):
            if(!operateAdd(op
                , block))
                return false;
            break;
        case(OpTag::SUB):
            if(!operateSub(op
                , block))
                return false;
            break;
        case(OpTag::SWAP):
            if(!operateSwap(op
                , block))
                return false;
            break;
    }

    return true;
}

bool Controller::operateAdd(const Operation &op
    , Block *block) const
{
    Block::Element addedElement;
    std::size_t scopeId{0ull};
    if(!getBlockElement(addedElement
        , scopeId
        , op.src
        , true))
        return false;
    
    if(!std::holds_alternative<TOKEN::Statement*>(addedElement.first))
        return invalidVariantError("Block::Element");
    
    auto *&statement{std::get<TOKEN::Statement*>(addedElement.first)};
    statement = statement->copy();

    Selector selector;
    if(!selector.execute(op.ids
        , statement))
        return false;
    
    if(!getBlock(op.dst
        , block))
        return false;
    
    std::size_t pos{op.dst.back()};
    if(pos > block->elems.size())
        pos = block->elems.size();
    
    block->elems.insert(block->elems.begin() + pos
        , addedElement);
    
    return true;
}

bool Controller::operateSub(const Operation &op
    , Block *block) const
{
    if(!getBlock(op.dst
        , block))
        return false;
    
    if(block->elems.size() >= op.dst.back())
        return invalidElementError("Controller::operateSub");

    std::visit([](auto &&p){delete p;}
        , block->elems[op.dst.back()].first);
    
    block->elems.erase(block->elems.begin() + op.dst.back());

    return true;
}

bool Controller::operateSwap(const Operation &op
    , Block *block) const
{
    return notSupportedError("Controller::operateSwap");
}

bool Controller::createRandomRepresentation(Representation &rep)
{
    rep.block = mSrcBlock;
    rep.ops.emplace_back();

    if(!createRandomOperation(rep.ops.back()))
        return false;

    return true;
}

bool Controller::createRandomOperation(Operation &op)
{
    double prob{RAND.floating()};
    double sum{0.0};

    if((sum += Configure::ADDING_PROBABILITY) >= prob)
        op.tag = OpTag::ADD;
    else if((sum += Configure::SUBTRACTING_PROBABILITY) >= prob)
        op.tag = OpTag::SUB;
    else if((sum += Configure::SWAPPING_PROBABILITY) >= prob)
        op.tag = OpTag::SWAP;
    
    bool isSuccessfull{false};
    std::size_t failureCount{0ull};

    do
    {
        op.src.clear();
        op.dst.clear();
        op.ids.clear();

        switch(op.tag)
        {
            case(OpTag::ADD):
            {
                if(!selectBlock(op.src, true)
                    || !selectBlock(op.dst, false))
                    break;
                Block::Element element;
                std::size_t scopeId{0ull};
                if(!getBlockElement(element
                    , scopeId
                    , op.src
                    , true))
                    break;
                if(!selectAlternativeIdentifier(op.ids
                    , element
                    , scopeId))
                    break;

                isSuccessfull = true;
                break;
            }
            case(OpTag::SUB):
                if(!selectBlock(op.dst, false))
                    break;
                
                isSuccessfull = true;
                break;
            case(OpTag::SWAP):
                if(!selectBlock(op.src, false)
                    || !selectBlock(op.dst, false))
                    break;
                
                isSuccessfull = true;
                break;
            
            default:;
        }

        failureCount++;
    }
    while(!isSuccessfull
        && failureCount < Configure::FAILURE_LIMIT);

    if(!isSuccessfull)
        return reachedFailureLimit("");

    return true;
}

bool Controller::invalidVariantError(const std::string &name) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: variant have invalid type.\n"
        "    class: " << name
        << std::endl;
    return false;
}

bool Controller::openError(const std::string &filename) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: failed to open file.\n"
        "    file: " << filename
        << std::endl;
    return false;
}

bool Controller::compileError(const std::string &filename) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: failed to compile.\n"
        "    file: " << filename
        << std::endl;
    return false;
}

bool Controller::statementSelectionError(const std::string &str) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: failed to select statement.\n"
        "    ---: " << str
        << std::endl;
    return false;
}

bool Controller::elementNotFoundError(const std::string &str) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: failed to find Block::Element from index array.\n"
        "    ---: " << str
        << std::endl;
    return false;
}

bool Controller::invalidElementError(const std::string &str) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: selected element is invalid.\n"
        "    ---: " << str
        << std::endl;
    return false;
}

bool Controller::invalidStatementError(const std::string &str) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: selected statement is invalid.\n"
        "    ---: " << str
        << std::endl;
    return false;
}

bool Controller::reachedFailureLimit(const std::string &str) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: reached failure limit to create operation.\n"
        "    ---:" << str
        << std::endl;
    return false;
}

bool Controller::notSupportedError(const std::string &str) const
{
    std::cerr << "GA::Controller error:\n"
        "    what: not supported.\n"
        "    ---: " << str
        << std::endl;
    return false;
}

}