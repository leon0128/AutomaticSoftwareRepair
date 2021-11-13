#include <iostream>
#include <utility>

#include <boost/optional.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "ga/controller.hpp"
#include "analyzer.hpp"
#include "divider.hpp"
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
    {
        source.finalize();
        return false;
    }

    std::vector<Analyzer> pool{Configure::POOL.size()};
    for(std::size_t i{0ull};
        i < pool.size();
        i++)
    {
        if(!analyzeFile(Configure::POOL[i]
            , pool[i]))
        {
            for(auto &&a : pool)
                a.finalize();
            return false;
        }        
    }

    GA::Controller gaController;
    if(!gaController.execute(source
        , pool))
        return false;

    source.finalize();
    for(auto && a : pool)
        a.finalize();

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
        Configure::TARGET_FUNCTION_NAMES.clear();
        for(const auto &child : ptree.get_child("target_function_names"))
            Configure::TARGET_FUNCTION_NAMES.push_back(child.second.data());
        Configure::POOL.clear();
        for(const auto &child : ptree.get_child("pool"))
            Configure::POOL.push_back(child.second.data());
        Configure::RESULT_FILENAME
            = ptree.get<decltype(Configure::RESULT_FILENAME)>("result_filename");
        Configure::COMPILER
            = ptree.get<decltype(Configure::COMPILER)>("compiler");
        Configure::TEST_SCRIPT
            = ptree.get<decltype(Configure::TEST_SCRIPT)>("test_script");
        Configure::TEST_FILENAME
            = ptree.get<decltype(Configure::TEST_FILENAME)>("test_filename");
        Configure::EXECUTION_NAME
            = ptree.get<decltype(Configure::EXECUTION_NAME)>("execution_name");
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
        Configure::FAILURE_LIMIT
            = ptree.get<decltype(Configure::FAILURE_LIMIT)>("failure_limit");
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

    if(Configure::MAX_GEN <= 0)
        return initConfigureError("MAX_GEN <= 0");
    else if(Configure::POP_SIZE <= 0)
        return initConfigureError("POP_SIZE <= 0");
    else if(Configure::POP_SIZE < Configure::NUM_ELITE)
        return initConfigureError("POP_SIZE < NUM_ELITE");
    else if(Configure::TOURNAMENT_SIZE <= 0
        || Configure::TOURNAMENT_SIZE > Configure::POP_SIZE)
        return initConfigureError("TOURNAMENT_SIZE <= 0 || TOURNAMENT_SIZE > POP_SIZE");
    else if(Configure::POOL.empty())
        return initConfigureError("POOL is empty");

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

    if(!Divider::execute(treeGenerator.translationUnit()))
        return false;
    
    if(!analyzer.execute(filename
        , treeGenerator.translationUnit()))
    {
        treeGenerator.translationUnit(nullptr);
        return false;
    }

    treeGenerator.translationUnit(nullptr);
    
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