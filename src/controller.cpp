#include <iostream>
#include <utility>

#include <boost/optional.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "ga/controller.hpp"
#include "analyzer.hpp"
#include "tree_generator.hpp"
#include "sequencer.hpp"
#include "configure.hpp"
#include "controller.hpp"

Controller::Controller()
{
}

bool Controller::execute()
{
    if(!initialize())
        return false;

    Analyzer source;
    if(!analyzeFile(Configure::SOURCE_FILENAME
        , source))
        return false;

    std::vector<Analyzer> pool;
    for(const auto &file : Configure::POOL)
    {
        pool.emplace_back();
        if(!analyzeFile(file
            , pool.back()))
            return false;
    }

    GA::Controller gaController;
    if(!gaController.execute(source
        , pool))
        return false;

    return true;
}

bool Controller::initialize()
{
    try
    {
        boost::property_tree::ptree ptree;
        boost::property_tree::read_json(CONFIGURE_FILENAME
            , ptree);

        Configure::SOURCE_FILENAME
            = ptree.get<decltype(Configure::SOURCE_FILENAME)>("source_filename");
        Configure::POOL.clear();
        for(const auto &child : ptree.get_child("pool"))
            Configure::POOL.push_back(child.second.data());
        Configure::RESULT_FILENAME
            = ptree.get<decltype(Configure::RESULT_FILENAME)>("result_filename");
        Configure::COMPILER
            = ptree.get<decltype(Configure::COMPILER)>("result_filename");
        Configure::TEST_SCRIPT
            = ptree.get<decltype(Configure::TEST_SCRIPT)>("test_script");
        Configure::TEST_FILENAME
            = ptree.get<decltype(Configure::TEST_FILENAME)>("test_filename");
        Configure::POSITIVE_TEST_PREFIX
            = ptree.get<decltype(Configure::POSITIVE_TEST_PREFIX)>("positive_test_prefix");
        Configure::NEGATIVE_TEST_PREFIX
            = ptree.get<decltype(Configure::NEGATIVE_TEST_PREFIX)>("negative_test_prefix");
        Configure::NUM_POSITIVE_TEST
            = ptree.get<decltype(Configure::NUM_POSITIVE_TEST)>("num_positive_test");
        Configure::NUM_NEGATIVE_TEST
            = ptree.get<decltype(Configure::NUM_NEGATIVE_TEST)>("num_negative_test");
        Configure::POSITIVE_TEST_WEIGHT
            = ptree.get<decltype(Configure::POSITIVE_TEST_WEIGHT)>("positive_test_weight");
        Configure::NEGATIVE_TEST_WEIGHT
            = ptree.get<decltype(Configure::NEGATIVE_TEST_WEIGHT)>("negative_test_weight");
        Configure::GOAL_SCORE
            = ptree.get<decltype(Configure::GOAL_SCORE)>("goal_score");
        Configure::POP_SIZE
            = ptree.get<decltype(Configure::POP_SIZE)>("pop_size");
        Configure::MAX_GEN
            = ptree.get<decltype(Configure::MAX_GEN)>("max_gen");
        Configure::NUM_ELITE
            = ptree.get<decltype(Configure::NUM_ELITE)>("num_elite");
        Configure::TOURNAMENT_SIZE
            = ptree.get<decltype(Configure::TOURNAMENT_SIZE)>("tournament_size");
        Configure::ADDING_PROBABILITY
            = ptree.get<decltype(Configure::ADDING_PROBABILITY)>("adding_probability");
        Configure::SUBTRACTING_PROBABILITY
            = ptree.get<decltype(Configure::SUBTRACTING_PROBABILITY)>("subtracting_probability");
        Configure::SWAPPING_PROBABILITY
            = ptree.get<decltype(Configure::SWAPPING_PROBABILITY)>("swapping_probability");
        Configure::ADDING_NEW_OPERATION_PROBABILITY
            = ptree.get<decltype(Configure::ADDING_NEW_OPERATION_PROBABILITY)>("adding_new_operation_probability");
        Configure::CONCATENATION_PROBABILITY
            = ptree.get<decltype(Configure::CONCATENATION_PROBABILITY)>("concatenation_probability");
    }
    catch(const std::exception &e)
    {
        return initConfigureError(e.what());
    }

    return true;
}

bool Controller::analyzeFile(const std::string &filename
    , Analyzer &analyzer)
{
    Sequencer sequencer;
    if(!sequencer.execute(filename))
        return false;
    
    TreeGenerator treeGenerator{filename, sequencer.seq()};
    if(!treeGenerator.execute())
        return false;
    
    if(!analyzer.execute(filename
        , treeGenerator.translationUnit()))
        return false;
    
    return true;
}

bool Controller::initConfigureError(const std::string &message) const
{
    std::cerr << "Configure error:\n"
        "    what: failed to initialize configure value.\n"
        "    diag: " << message
        << std::endl;
    return false;
}