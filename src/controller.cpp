#include <iostream>
#include <utility>

#include "tree_generator.hpp"
#include "sequencer.hpp"
#include "controller.hpp"

Controller::Controller(int argc, char **argv)
    :mFileMap()
{
    for(int i = 1; i < argc; i++)
        mFileMap.emplace(argv[i], nullptr);
}

bool Controller::execute()
{
    if(!createTree())
        return false;

    return true;
}

bool Controller::createTree()
{
    for(auto &&p : mFileMap)
    {
        Sequencer sequencer(p.first);
        if(!sequencer.execute())
            return false;

        TreeGenerator generator(p.first, sequencer.seq());
        if(!generator.execute())
            return false;

        delete generator.translationUnit();
    }

    return true;
}