#ifndef GA_CONTROLLER_HPP
#define GA_CONTROLLER_HPP

#include <vector>
#include <utility>

#include "representation.hpp"

namespace TOKEN
{
    class TranslationUnit;
}

namespace GA
{

class Block;

class Controller
{
public:
    Controller(const TOKEN::TranslationUnit*);
    ~Controller();

    bool execute();

private:
    bool initialize();
    
    int fitness(const Representation&) const;
    Representation manipulate(const std::vector<std::pair<int, std::size_t>>&) const;
    std::size_t select(const std::vector<std::pair<int, std::size_t>>&) const;

    const TOKEN::TranslationUnit *mSrc;
    Block *mSrcBlock;
    std::vector<Representation> mGen;
    Representation mResult;
};

}

#endif