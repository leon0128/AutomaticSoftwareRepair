#include <iostream>
#include <string>
#include <filesystem>

#include "path.hpp"
#include "tokenizer.hpp"
#include "sequencer.hpp"

Sequencer::Sequencer(const std::string &filename)
    : mFile(filename)
    , mSeq()
{
}

bool Sequencer::execute()
{
    std::string src;

    if(!openFile(src))
        return false;
    if(!sequencenize(src))
        return false;

    return true;
}

bool Sequencer::openFile(std::string &src)
{
    std::filesystem::path path(mFile);
    if(!PATH::isExist(path, std::filesystem::file_type::regular))
    {
        std::cerr << "sequencer error:\n"
            "    what: file is not found.\n"
            "    file: " << mFile
            << std::endl;
        return false;
    }

    src = PATH::read(path);
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