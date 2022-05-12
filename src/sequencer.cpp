#include <iostream>
#include <string>
#include <limits>
#include <filesystem>
#include <utility>

#include "utility/system.hpp"
#include "utility/file.hpp"
#include "configure.hpp"
#include "token.hpp"
#include "tokenizer.hpp"
#include "sequencer.hpp"

Sequencer::Sequencer()
    : mFile{}
    , mSeq{}
{
}

Sequencer::~Sequencer()
{
    for(auto &&pt : mSeq)
        delete pt;
}

bool Sequencer::execute(const std::string &filename)
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

bool Sequencer::openFile(std::string &src)
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

bool Sequencer::preprocess()
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

bool Sequencer::sequencenize(const std::string &src)
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

bool Sequencer::convertCharacter()
{
    return true;
}

bool Sequencer::concatenateStringLiteral()
{
    // pre: pre + post
    // post: empty
    auto &&concatenateVector{[&](std::vector<TOKEN::SChar*> &pre
        , std::vector<TOKEN::SChar*> &post)
        -> void
    {
        pre.insert(pre.end()
            , post.begin()
            , post.end());
        post.clear();
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
        if(preSL->ep != nullptr
            ^ postSL->ep != nullptr)
        {
            if(postSL->ep != nullptr)
                std::swap(preSL->ep, postSL->ep);
        }

        concatenateVector(preSL->scs->seq
            , postSL->scs->seq);
        delete mSeq[i + 1ull];
        mSeq.erase(mSeq.begin() + i + 1ull);
        i--;
    }

    return true;
}

void Sequencer::omitWS(const std::string &src
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

bool Sequencer::convertEscapeSequence(TOKEN::EscapeSequence *es
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