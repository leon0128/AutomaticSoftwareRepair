#include <filesystem>
#include <future>
#include <mutex>
#include <condition_variable>
#include <future>
#include <utility>
#include <numeric>
#include <functional>
#include <iostream>

#include "utility/output.hpp"
#include "common/time_measurer.hpp"
#include "analyzer.hpp"
#include "divider.hpp"
#include "tree_generator.hpp"
#include "cache_encoder.hpp"
#include "preprocessor.hpp"
#include "configure.hpp"
#include "controller.hpp"

namespace ANALYZER
{

Controller::Controller()
    : mTarget{}
    , mPool{}
    , mMemberMutex{}
    , mTotalPoolCount{0ull}
    , mSuccessedPoolCount{0ull}
{
}

Controller::~Controller()
{
}

bool Controller::execute()
{
    TimeMeasurer::Wrapper wrapper{TimeMeasurer::AnalyzerTag::ANALYZING};

    // target
    if(!analyze(Configure::SOURCE_FILENAME))
        return false;

    // pool
    std::deque<std::string> poolFilenames;
    for(auto &&pathname : Configure::POOL)
    {
        for(auto &&filename : getFiles(pathname))
            poolFilenames.push_back(filename);
    }

    if(!analyze(poolFilenames))
        return false;

    if(Configure::SHOULD_OUTPUT_ANALYZE_LOG)
        outputAnalyzingLog();
    setSpecifiedLog();

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

bool Controller::analyze(const std::string &filename)
{
    auto &&codeInfo{analyzeSafely(filename)};
    if(!codeInfo.has_value())
        return false;
    
    mTarget = std::move(codeInfo.value());
    return true;
}

bool Controller::analyze(const std::deque<std::string> &filenames)
{
    std::mutex mutex;
    std::condition_variable cv;

    std::deque<std::future<std::optional<CodeInformation>>> futures(Configure::NUM_CONCURRENCY);
    std::deque<std::size_t> availableIndices(futures.size());
    std::iota(availableIndices.begin()
        , availableIndices.end()
        , 0ull);

    // this function is used for std::async function's arguments.
    // future object has this function.
    auto &&analyzeWrapper{[&](std::size_t futuresIdx
        , const std::string &filename)
        -> std::optional<CodeInformation>
        {
            auto &&codeInfo{analyzeSafely(filename)};

            std::unique_lock lock{mutex};
            std::unique_lock memberLock{mMemberMutex};
            mTotalPoolCount++;
            if(codeInfo.has_value())
                mSuccessedPoolCount++;
            availableIndices.push_back(futuresIdx);
            cv.notify_all();
            return codeInfo;
        }};
    auto &&analyzeWrapperWithOutput{[&](std::size_t futuresIdx
        , const std::string &filename)
        -> std::optional<CodeInformation>
        {
            auto &&codeInfo{analyzeWrapper(futuresIdx, filename)};
            outputAnalyzingLog(filename, filenames.size());
            return codeInfo;
        }};

    // function that is passed to future objects.
    std::function<std::optional<CodeInformation>(std::size_t, const std::string&)> analyzingFunc;
    if(Configure::SHOULD_OUTPUT_ANALYZE_LOG)
        analyzingFunc = analyzeWrapperWithOutput;
    else
        analyzingFunc = analyzeWrapper;

    for(std::size_t i{0ull}, size{filenames.size()}; i < size;)
    {
        std::unique_lock lock{mutex};

        if(!availableIndices.empty())
        {
            std::size_t futuresIdx{availableIndices.front()};
            availableIndices.pop_front();

            if(futures.at(futuresIdx).valid())
            {
                auto &&codeInfo{futures.at(futuresIdx).get()};
                if(codeInfo.has_value())
                    mPool.push_back(std::move(codeInfo.value()));
            }

            futures.at(futuresIdx)
                = std::async(std::launch::async
                    , analyzingFunc
                    , futuresIdx
                    , filenames.at(i));
            i++;
        }
        else
            cv.wait(lock, [&]{return !availableIndices.empty();});
    }

    for(auto &&future : futures)
    {
        if(future.valid())
        {
            auto &&codeInfo{future.get()};
            if(codeInfo.has_value())
                mPool.push_back(std::move(codeInfo.value()));
        }
    }

    return true;
}

std::optional<CodeInformation> Controller::analyzeSafely(const std::string &filename)
{
    Preprocessor preprocessor;
    if(!preprocessor.execute(filename))
            return {std::nullopt};

    auto &&sequence{preprocessor.sequence()};

    TreeGenerator treeGenerator;
    if(!treeGenerator.execute(filename, sequence))
        return {std::nullopt};

    std::shared_ptr<TOKEN::TranslationUnit> translationUnit{treeGenerator.moveTranslationUnit()};
    
    if(!Divider::execute(translationUnit.get()))
        return {std::nullopt};

    Analyzer analyzer;
    if(!analyzer.execute(filename, translationUnit.get()))
        return {std::nullopt};

    std::shared_ptr<SCOPE::Scope> scope{analyzer.moveScope()};

    return {CodeInformation{filename, translationUnit, scope}};
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

void Controller::outputAnalyzingLog() const
{
    std::cout << "analyzer-log:\n"
        "    pool.successed rate: ";
    if(mTotalPoolCount == 0)
        std::cout << "0";
    else
        std::cout << static_cast<double>(mSuccessedPoolCount) / static_cast<double>(mTotalPoolCount);
    std::cout << "%.("
    << mSuccessedPoolCount
    << "/"
    << mTotalPoolCount
    << ")"
    << std::endl;
}

void Controller::outputAnalyzingLog(const std::string &filename
    , std::size_t poolSize)
{
    std::unique_lock ioLock{stdioMutex};
    std::unique_lock memberLock{mMemberMutex};
    std::cout << "analyzer-log: "
        << filename << " is analyzed.("
        << mTotalPoolCount
        << "/" << poolSize
        << ")"
    << std::endl;
}

void Controller::setSpecifiedLog() const
{
    
}

}