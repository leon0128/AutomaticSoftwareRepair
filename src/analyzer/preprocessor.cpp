#include <iostream>
#include <string>
#include <limits>
#include <filesystem>
#include <utility>

#include "utility/system.hpp"
#include "utility/file.hpp"
#include "configure.hpp"
#include "tokenizer.hpp"
#include "preprocessor.hpp"

namespace ANALYZER
{

Preprocessor::Preprocessor()
    : mFile{}
    , mSeq{}
{
}

Preprocessor::~Preprocessor()
{
    finalize();
}

bool Preprocessor::execute(const std::string &filename)
{
    mFile = filename;
    
    std::string src;

    if(!preprocess()
        || !openFile(src)
        || !sequencenize(src)
        || !convertCharacter()
        || !concatenateStringLiteral())
        return false;

    return true;
}

void Preprocessor::finalize()
{
    for(auto &&pp : mSeq)
        delete pp;
}

bool Preprocessor::openFile(std::string &src)
{
    std::filesystem::path path(Configure::TEST_FILENAME);
    if(!PATH::isExist(path, std::filesystem::file_type::regular))
    {
        std::cerr << "sequencer error:\n"
            "    what: file is not found.\n"
            "    file: " << mFile
            << std::endl;
        return false;
    }

    return PATH::read(path
        , src);
}

bool Preprocessor::preprocess()
{
    std::filesystem::path path{mFile};
    if(!PATH::isExist(path, std::filesystem::file_type::regular))
    {
        std::cerr << "sequencer error:\n"
            "    what: file is not found.\n"
            "    file: " << mFile
            << std::endl;
        return false;
    }

    
    std::string command{SYSTEM::command(Configure::PREPROCESSOR
        , "-P"
        , mFile
        // , "-D__extension__="
        // , "-D__builtin_expect\\(exp,c\\)=\\(exp\\)"
        // , "-D__builtin_offsetof\\(TYPE,MEMBER\\)=\\(\\(size_t\\)\\&\\(\\(TYPE*\\)0\\)-\\>MEMBER\\)"
        , "-o"
        , Configure::TEST_FILENAME
        , ">"
        , SYSTEM::NULLFILE
        , "2>&1")};

    if(SYSTEM::system(command) != 0)
    {
        std::cerr << "Sequencer::preprocess() error:\n"
            "    filename: " << mFile
            << "\n    what: failed to preprocess.\n"
            << std::flush;
        return false;
    }

    return true;
}

bool Preprocessor::sequencenize(const std::string &src)
{
    std::size_t idx = 0;
    while(true)
    {
        omitWS(src, idx);
        if(TOKEN::PreprocessingToken *pt = TOKENIZER::decPreprocessingToken(src, idx);
            pt != nullptr)
            mSeq.push_back(pt);
        else
            break;
    }
    
    if(idx != src.size())
    {
        std::cerr << "sequencer error:\n"
            "    what: failed to decompose to pp-token from src.\n"
            "    file: " << mFile
            << std::endl;
        return false;
    }

    return true;
}

bool Preprocessor::convertCharacter()
{
    return true;
}

bool Preprocessor::concatenateStringLiteral()
{
    // pre: pre + post
    // post: empty
    auto &&concatenateVector{[&](TOKEN::SCharSequence *&pre
        , TOKEN::SCharSequence *&post)
        -> void
    {
        if(pre == nullptr
            && post != nullptr)
            std::swap(pre, post);
        else if(pre != nullptr
            && post != nullptr)
        {
            pre->seq.insert(pre->seq.end()
                , post->seq.begin()
                , post->seq.end());
            post->seq.clear();
        }
    }};

    for(std::size_t i{0ull}; i + 1ull < mSeq.size(); i++)
    {
        if(!std::holds_alternative<TOKEN::StringLiteral*>(mSeq[i]->var)
            || !std::holds_alternative<TOKEN::StringLiteral*>(mSeq[i + 1ull]->var))
            continue;

        auto &&preSL{std::get<TOKEN::StringLiteral*>(mSeq[i]->var)};
        auto &&postSL{std::get<TOKEN::StringLiteral*>(mSeq[i]->var)};

        // if both are not same tag for each other,
        // no change
        if(preSL->ep != nullptr
            && postSL->ep != nullptr)
        {
            if(preSL->ep->tag != postSL->ep->tag)
                continue;
        }

        // if only post-SL has encoding-prefix,
        // move it to pre-SL.
        if((preSL->ep != nullptr)
            ^ (postSL->ep != nullptr))
        {
            if(postSL->ep != nullptr)
                std::swap(preSL->ep, postSL->ep);
        }

        concatenateVector(preSL->scs
            , postSL->scs);
        delete mSeq[i + 1ull];
        mSeq.erase(mSeq.begin() + i + 1ull);
        i--;
    }

    return true;
}

void Preprocessor::omitWS(const std::string &src
    , std::size_t &idx) const
{
    while(idx < src.size()
        && (src[idx] == ' '
            || src[idx] == '\t'
            || src[idx] == '\n'
            || src[idx] == '\v'
            || src[idx] == '\f'))
        idx++;
}

bool Preprocessor::convertEscapeSequence(TOKEN::EscapeSequence *es
    , char &res) const
{
    if(std::holds_alternative<TOKEN::SimpleEscapeSequence*>(es->var))
    {
        char c = std::get<TOKEN::SimpleEscapeSequence*>(es->var)->c;
        if(c == '\''
            || c == '\"'
            || c == '\?'
            || c == '\\')
            res = c;
        else if(c == 'a')
            res = '\a';
        else if(c == 'b')
            res = '\b';
        else if(c == 'f')
            res = '\f';
        else if(c == 'n')
            res = '\n';
        else if(c == 'r')
            res = '\r';
        else if(c == 't')
            res = '\t';
        else if(c == 'v')
            res = '\v';
        else
            return false;
    }
    else if(std::holds_alternative<TOKEN::OctalEscapeSequence*>(es->var))
    {
        int tmp = 0;
        for(auto &&od : std::get<TOKEN::OctalEscapeSequence*>(es->var)->seq)
            tmp = tmp * 010 + (od->c - '0');
        if(tmp <= static_cast<int>(std::numeric_limits<char>::max()))
            res = static_cast<char>(tmp);
        else
            return false;
    }
    else if(std::holds_alternative<TOKEN::HexadecimalEscapeSequence*>(es->var))
    {
        int tmp = 0;
        for(auto &&hd : std::get<TOKEN::HexadecimalEscapeSequence*>(es->var)->seq)
        {
            if(hd->c >= '0' && hd->c <= '9')
                tmp = tmp * 0x10 + (hd->c - '0');
            else if(hd->c >= 'a' && hd->c <= 'f')
                tmp = tmp * 0x10 + (hd->c - 'a') + 10;
            else if(hd->c >= 'A' && hd->c <= 'F')
                tmp = tmp * 0x10 + (hd->c - 'A') + 10;
            else
                return false;
            
            if(tmp > std::numeric_limits<char>::max())
                return false;
        }

        res = static_cast<char>(tmp);
    }

    return true;
}

}