#include <iostream>
#include <string>
#include <variant>
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
    std::size_t idx;
    for(TOKEN::PreprocessingToken *ppt = TOKENIZER::decPreprocessingToken(src, idx);
        ppt != nullptr;
        ppt = TOKENIZER::decPreprocessingToken(src, idx))
        mSeq.push_back(ppt);
    
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