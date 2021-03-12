#include <iostream>
#include <utility>

#include "ga/controller.hpp"
#include "normalizer.hpp"
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

        Normalizer normalizer(generator.translationUnit());
        if(!normalizer.execute())
            return false;

        // GA::Controller gaController(normalizer.translationUnit());
        // if(!gaController.execute())
        //     return false;
    }

    return true;
}