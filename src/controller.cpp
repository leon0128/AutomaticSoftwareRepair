#include <optional>
#include <deque>

#include "utility/system.hpp"
#include "analyzer/controller.hpp"
#include "similarity/controller.hpp"
#include "repair/controller.hpp"
#include "common/time_measurer.hpp"
#include "common/define.hpp"
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
    std::optional<std::deque<std::deque<double>>> similarity;
    if(Configure::SHOULD_USE_SIMILARITY)
    {
        SIM::Controller similarityController;
        {
            TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::SIMILARITY};
            if(!similarityController.execute(target, pool))
                return false;
        }
        similarity = similarityController.moveResults();
    }

    // repair
    REPAIR::Controller repairController;
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::REPAIR};
        if(!repairController.execute(target, pool, similarity))
            return false;
    }

    if(Configure::SHOULD_OUTPUT_SPECIFIED_LOG)
        outputSpecifiedLog();

    return true;
}

bool Controller::initialize(int argc, char **argv)
{
    if(!Configure::parseCommandLineArguments(argc, argv))
        return false;

    return true;
}

void Controller::finalize()
{
    if(Configure::SHOULD_OUTPUT_TIME_LOG)
        timeMeasurer().print();
    if(Configure::SHOULD_OUTPUT_SPECIFIED_LOG)
        std::cout << sstream.str() << std::flush;
}

void Controller::outputSpecifiedLog() const
{   
    using TM = TimeMeasurer;
    sstream << timeMeasurer().total<TM::MainTag, std::chrono::milliseconds>()
        << "," << timeMeasurer().total<TM::AnalyzerTag, std::chrono::milliseconds>()
        << "," << timeMeasurer().total<TM::SimTag, std::chrono::milliseconds>()
        << "," << timeMeasurer().total<TM::RepairTag, std::chrono::milliseconds>()
        << "," << static_cast<int>(Configure::IDENTIFIER_SELECTION_TAG)
        << std::endl;
}