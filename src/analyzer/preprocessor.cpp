#include <iostream>
#include <regex>
#include <utility>
#include <filesystem>
#include <iomanip>

#include "configure.hpp"
#include "utility/system.hpp"
#include "utility/file.hpp"
#include "utility/output.hpp"
#include "common/define.hpp"
#include "tokenizer.hpp"
#include "preprocessor.hpp"

namespace ANALYZER
{

Preprocessor::Preprocessor()
    : mFilename{}
    , mMarkedFilename{PATH::getTempFilename() + ".c"}
    , mPreprocessedFilename{PATH::getTempFilename() + ".c"}
    , mContents{}
    , mPTs{}
{
}

Preprocessor::~Preprocessor()
{
    finalize();
}

bool Preprocessor::execute(const std::string &filename)
{
    if(!initialize(filename))
        return false;

    if(!addBuiltinFile())
        return false;

    if(!readFile(mFilename))
        return false;

    if(!concatenateLine())
        return false;

    if(!deleteComment())
        return false;

    if(!addMark())
        return false;

    if(!writeFile(mMarkedFilename))
        return false;

    if(!executeCommand(mMarkedFilename, mPreprocessedFilename))
        return false;

    mContents.clear();
    if(!readFile(mPreprocessedFilename))
        return false;

    if(!decompose())
        return false;

    if(!concatenateStringLiteral())
        return false;

    return true;
}

bool Preprocessor::initialize(const std::string &filename)
{
    mFilename = filename;

    return true;
}

void Preprocessor::finalize()
{
    PATH::remove(mMarkedFilename);
    PATH::remove(mPreprocessedFilename);
    for(auto &&pt : mPTs)
        delete pt;
}

bool Preprocessor::addBuiltinFile()
{
    if(Configure::BUILTIN.empty())
        return true;

    mContents += "#include \"";
    mContents += Configure::BUILTIN;
    mContents += "\"\n";

    return true;
}

bool Preprocessor::readFile(const std::string &filename)
{
    if(!PATH::read(filename, mContents))
        return fileReadingError(filename);
    
    return true;
}

bool Preprocessor::concatenateLine()
{
    static std::regex regex{"\\\\\\n"};

    mContents = std::regex_replace(mContents, regex, "");

    return true;
}

bool Preprocessor::deleteComment()
{
    static std::regex regex{"(//.*)|(/\\*(.|\n)*?\\*/)"};

    mContents = std::regex_replace(mContents, regex, " ");

    return true;
}

bool Preprocessor::addMark()
{
    static std::regex regex{"#( |\t|\n|\v|\f)*?include( |\t|\n|\v|\f)*?(<.*?>|\".*?\")"};

    std::deque<std::string> includedFiles;
    for(auto &&iter{std::sregex_iterator(mContents.begin(), mContents.end(), regex)};
        iter != std::sregex_iterator();
        iter++)
        includedFiles.push_back(iter->str(iter->size() - 1ull));

    mContents
        = std::regex_replace(mContents
            , regex
            , "@\n$&\n@\n");

    for(std::size_t pos{mContents.find("@\n")}
            , count{0ull};
        pos != std::string::npos;
        pos = mContents.find("@\n", pos + 1ull)
            , count++)
    {
        mContents.insert(pos + 1ull
            , includedFiles.at(count / 2ull));
    }

    return true;
}

bool Preprocessor::writeFile(const std::string &filename)
{
    if(!PATH::write(filename, mContents))
        return false;

    return true;
}

bool Preprocessor::executeCommand(const std::string &input
    , const std::string &output)
{
    std::string command{SYSTEM::command(Configure::PREPROCESSOR
        , "-I./"
        , "-I./" + std::filesystem::path{mFilename}.remove_filename().string()
        , input
        , "-o"
        , output)};

    controlOutputLog(command);

    if(SYSTEM::system(command) != 0)
        return preprocessingError(mFilename);

    return true;
}

bool Preprocessor::decompose()
{
    auto &&omitWhiteSpace{[&](std::size_t &idx)
        -> void
        {
            while(idx < mContents.size()
                && (mContents[idx] == ' '
                    || mContents[idx] == '\t'
                    || mContents[idx] == '\n'
                    || mContents[idx] == '\v'
                    || mContents[idx] == '\f'))
                idx++;
        }};

    std::size_t index{0ull};

    while(true)
    {
        omitWhiteSpace(index);
        if(TOKEN::PreprocessingToken *pt{TOKENIZER::decPreprocessingToken(mContents, index)};
            pt != nullptr)
            mPTs.push_back(pt);
        else
            break;
    }

    if(index != mContents.size())
        return decomposingError(mFilename);

    return true;
}

bool Preprocessor::concatenateStringLiteral()
{
    auto &&concatenateSequence{[](TOKEN::SCharSequence *&pre
        , TOKEN::SCharSequence *&post)
        -> void
        {
            if(!pre && post)
                std::swap(pre, post);
            else if(pre && post)
            {
                pre->seq.insert(pre->seq.end()
                    , post->seq.begin()
                    , post->seq.end());
                post->seq.clear();
            }
        }};

    for(std::size_t i{0ull}; i + 1ull < mPTs.size(); i++)
    {
        if(!std::holds_alternative<TOKEN::StringLiteral*>(mPTs[i]->var)
            || !std::holds_alternative<TOKEN::StringLiteral*>(mPTs[i + 1ull]->var))
            continue;
    
        auto &&preSL{std::get<TOKEN::StringLiteral*>(mPTs[i]->var)};
        auto &&postSL{std::get<TOKEN::StringLiteral*>(mPTs[i + 1ull]->var)};

        // if both's tag aren't same tag for each other, no change
        if(preSL->ep && postSL->ep)
        {
            if(preSL->ep->tag != postSL->ep->tag)
                continue;
        }
        // if only postSL has ep, ep is swapped.
        else if((preSL->ep != nullptr) ^ (postSL->ep != nullptr))
        {
            if(postSL->ep != nullptr)
                std::swap(preSL->ep, postSL->ep);
        }

        concatenateSequence(preSL->scs, postSL->scs);
        delete mPTs[i + 1ull];
        mPTs.erase(mPTs.begin() + i + 1ull);
        i--;
    }

    return true;
}

bool Preprocessor::fileReadingError(const std::string &filename) const
{   
    std::cerr << OUTPUT::charRedCode
        << "ANALYZER::Preprocessor::fileReadingError():\n"
        << OUTPUT::resetCode
        << "    what: failed to read file.\n"
        "    filename: " << filename
        << std::endl;
    return false;
}

bool Preprocessor::preprocessingError(const std::string &filename) const
{
    std::cerr << OUTPUT::charRedCode
        << "ANALYZER::Preprocessor::preprocessingError():\n"
        << OUTPUT::resetCode
        << "    what: failed to preprocess.\n"
        "    filename: " << mFilename
        << std::endl;
    return false;
}

bool Preprocessor::decomposingError(const std::string &filename) const
{
    std::cerr << OUTPUT::charRedCode
        << "ANALYZER::Preprocessor::decomposingError():\n"
        << OUTPUT::resetCode
        << "    what: failed to decompose to preprocessing-token from source code.\n"
        "    filename: " << mFilename
        << std::endl;
    return false;
}

}