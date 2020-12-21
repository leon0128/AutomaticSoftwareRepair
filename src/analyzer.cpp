#include <iostream>

#include "analyzer.hpp"

Analyzer::Analyzer(const std::string &file
    , const Sequence &seq)
    : mFile(file)
    , mSeq(seq)
{
}

bool Analyzer::execute()
{
    return true;
}