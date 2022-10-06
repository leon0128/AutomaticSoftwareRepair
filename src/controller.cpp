#include "utility/system.hpp"
#include "analyzer/controller.hpp"
#include "similarity/controller.hpp"
#include "repair/controller.hpp"
#include "common/time_measurer.hpp"
#include "configure.hpp"
#include "controller.hpp"

Controller::Controller()
{
}

Controller::~Controller()
{
    finalize();
}

bool Controller::execute(int argc, char **argv)
{
    // initialize
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::INITIALIZING};
        if(!initialize(argc, argv))
            return false;
    }

    // analyze >> calculate >> repair

    // analyze
    ANALYZER::Controller analyzerController;
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::ANALYZING};
        if(!analyzerController.execute())
            return false;
    }

    auto &&target{analyzerController.moveTarget()};
    auto &&pool{analyzerController.movePool()};

    // calculate similarity
    SIM::Controller similarityController;
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::SIMILARITY};
        if(!similarityController.execute(target, pool))
            return false;
    }

    auto &&similarity{similarityController.moveResults()};

    // repair
    REPAIR::Controller repairController;
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::REPAIR};
        if(!repairController.execute(target, pool, similarity))
            return false;
    }

    return true;
}

bool Controller::initialize(int argc, char **argv)
{
    if(!Configure::parseCommandLineArguments(argc, argv))
        return false;
    
    SYSTEM::shouldOutputSubprocessCommand = Configure::SHOULD_OUTPUT_COMMAND_LOG;
    SYSTEM::shouldOutputSubprocessLog = Configure::SHOULD_OUTPUT_SUBPROCESS_LOG;
    SYSTEM::nullFile = Configure::NULL_FILENAME;

    return true;
}

void Controller::finalize()
{
    if(Configure::SHOULD_OUTPUT_TIME_LOG)
        timeMeasurer().print();
}