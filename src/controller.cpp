#include <iostream>
#include <utility>
#include <memory>
#include <filesystem>

#include "utility/output.hpp"
#include "utility/system.hpp"
#include "similarity/controller.hpp"
#include "similarity/representation.hpp"
#include "repair/controller.hpp"
#include "common/time_measurer.hpp"
#include "analyzer/analyzer.hpp"
#include "analyzer/divider.hpp"
#include "analyzer/tree_generator.hpp"
#include "analyzer/sequencer.hpp"
#include "configure.hpp"
#include "controller.hpp"

Controller::Controller()
{
}

bool Controller::execute(int argc, char **argv)
{
    // initialize
    if(!initialize(argc, argv))
        return false;

    

    // create Analyzer from source code to be fixed
    std::shared_ptr<Analyzer> source{createAnalyzer(Configure::SOURCE_FILENAME)};
    if(!source)
        return false;

    // create Analyzers from pool
    std::vector<std::shared_ptr<Analyzer>> pool;
    if(!createAnalyzersFromPool(pool))
        return false;
    if(pool.empty())
        return emptyPoolError();

    // calculate similarity
    std::optional<std::deque<std::deque<double>>> similarity;
    if(Configure::SHOULD_USE_SIMILARITY)
    {
        similarity = calculateSimilarity(source, pool);
        if(!similarity.has_value())
            return false;
    }

    // execute repair
    if(!repair(source, pool, similarity))
        return false;

    if(Configure::SHOULD_OUTPUT_TIME_LOG)
        timeMeasurer().print();

    return true;
}

bool Controller::initialize(int argc, char **argv)
{
    TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::INITIALIZING};

    if(!Configure::parseCommandLineArguments(argc, argv))
        return false;
    
    SYSTEM::shouldOutputLog = Configure::SHOULD_OUTPUT_COMMAND_LOG;

    return true;
}

bool Controller::addAllFiles(std::deque<std::string> &files
    , const std::filesystem::path &path)
{   
    auto &&status{std::filesystem::status(std::filesystem::path(path))};

    switch(status.type())
    {
        case(std::filesystem::file_type::regular):
        {
            if(path.extension().string() == ".c")
                files.push_back(path.string());
            break;
        }
        case(std::filesystem::file_type::directory):
        {
            for(const auto &child : std::filesystem::directory_iterator{path})
            {
                if(!addAllFiles(files
                    , child.path()))
                    return false;
            }
            break;
        }

        default:;
    }

    return true;
}

bool Controller::createAnalyzersFromPool(std::vector<std::shared_ptr<Analyzer>> &pool)
{
    std::deque<std::string> allFiles;
    for(const auto &path : Configure::POOL)
    {
        if(!addAllFiles(allFiles
            , std::filesystem::path{path}))
            return false;
    }

    for(std::size_t i{0ull}; i < allFiles.size(); i++)
    {
        std::shared_ptr<Analyzer> analyzer{createAnalyzer(allFiles[i])};
        if(analyzer)
            pool.push_back(std::move(analyzer));
        else
            poolAnalyzingWarning("ignore this file");
    }

    return true;
}

Analyzer *Controller::createAnalyzer(const std::string &filename)
{
    TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::ANALYZING};

    Sequencer sequencer;
    if(!sequencer.execute(filename))
        return nullptr;
    
    TreeGenerator treeGenerator{filename, sequencer.seq()};
    if(!treeGenerator.execute())
        return nullptr;

    if(!Divider::execute(treeGenerator.translationUnit()))
        return nullptr;
    
    Analyzer *analyzer{new Analyzer{}};
    if(!analyzer->execute(filename
        , treeGenerator.translationUnit()))
    {
        treeGenerator.translationUnit(nullptr);
        delete analyzer;
        return nullptr;
    }

    treeGenerator.translationUnit(nullptr);
    
    return analyzer;
}

std::optional<std::deque<std::deque<double>>> Controller::calculateSimilarity(std::shared_ptr<Analyzer> target
    , const std::vector<std::shared_ptr<Analyzer>> &pool)
{
    TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::SIMILARITY};
    
    std::deque<std::pair<std::string, const TOKEN::TranslationUnit*>> tus;    
    for(const auto &analyzer : pool)
        tus.emplace_back(analyzer->filename(), analyzer->translationUnit());

    SIM::Controller simController;
    if(!simController.execute(std::make_pair(target->filename(), target->translationUnit())
        , tus))
        return std::nullopt;
    
    return {simController.getResults()};
}

bool Controller::repair(std::shared_ptr<Analyzer> target
    , const std::vector<std::shared_ptr<Analyzer>> &pool
    , const std::optional<std::deque<std::deque<double>>> &similarity)
{
    TimeMeasurer::Wrapper wrapper{TimeMeasurer::MainTag::REPAIR};
    
    REPAIR::Controller repairController;
    if(!repairController.execute(target, pool, similarity))
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

bool Controller::poolAnalyzingWarning(const std::string &what) const
{
    std::cerr << "Controller::poolAnalyzingWarning():\n"
        "    what: " << what
        << std::endl;
    return false;
}

bool Controller::emptyPoolError() const
{
    std::cerr << "Controller::emptyPoolError():\n"
        "    what: pool is empty.\n"
        << std::flush;
    return false;
}