#include <filesystem>
#include <future>

#include "utility/output.hpp"
#include "common/time_measurer.hpp"
#include "analyzer.hpp"
#include "divider.hpp"
#include "tree_generator.hpp"
#include "preprocessor.hpp"
#include "configure.hpp"
#include "controller.hpp"

namespace ANALYZER
{

Controller::Controller()
    : mTarget{}
    , mPool{}
{
}

Controller::~Controller()
{
}

bool Controller::execute()
{
    // target
    if(!analyze(Configure::SOURCE_FILENAME, true))
        return false;
    
    // pool
    std::deque<std::string> poolFilenames;
    for(auto &&pathname : Configure::POOL)
    {
        for(auto &&filename : getFiles(pathname))
            poolFilenames.push_back(filename);
    }



    outputSpecifiedLog();

    return true;
}

std::deque<std::string> Controller::getFiles(const std::string &pathname) const
{
    auto &&addFilesRecursively{[](auto &&recursiveFunc
        , auto &&files
        , auto &&path)
        -> void
        {
            auto &&status{std::filesystem::status(path)};
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
                    for(auto &&child : std::filesystem::directory_iterator{path})
                        recursiveFunc(recursiveFunc, files, child.path());
                    break;
                }

                default:;
            }
        }};

    std::deque<std::string> files;
    addFilesRecursively(addFilesRecursively
        , files
        , std::filesystem::path{pathname});
    
    return files;
}

bool Controller::analyze(const std::string &filename
    , bool isTarget)
{
    Preprocessor preprocessor;
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::AnalyzerTag::PREPROCESSING};
        if(!preprocessor.execute(filename))
            return false;
    }

    auto &&sequence{preprocessor.sequence()};

    TreeGenerator treeGenerator;
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::AnalyzerTag::TREE_GENERATION};
        if(!treeGenerator.execute(filename, sequence))
            return false;
    }

    std::shared_ptr<TOKEN::TranslationUnit> translationUnit{treeGenerator.moveTranslationUnit()};
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::AnalyzerTag::DIVISION};
        if(!Divider::execute(translationUnit.get()))
            return false;
    }

    Analyzer analyzer;
    {
        TimeMeasurer::Wrapper wrapper{TimeMeasurer::AnalyzerTag::ANALYZING};
        if(!analyzer.execute(filename, translationUnit.get()))
            return false;
    }

    std::shared_ptr<SCOPE::Scope> scope{analyzer.moveScope()};

    if(isTarget)
        mTarget = CodeInformation{filename, translationUnit, scope};
    else
        mPool.emplace_back(CodeInformation{filename, translationUnit, scope});

    return true;
}

bool Controller::poolIgnoringWarning(const std::string &filename) const
{
    std::cerr << OUTPUT::charYellowCode
        << "ANALYZER::Controller::poolIgnoringWarning():\n"
        << OUTPUT::resetCode
        << "    what: failed to analyze source code in pool.\n"
        << "          ignored this file.\n"
        << "    filename: " << filename
        << std::endl;
    return false;
}

void Controller::outputSpecifiedLog() const
{
    
}

}