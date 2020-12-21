#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <vector>
#include <string>
#include <string>

namespace TOKEN
{
    class PreprocessingToken;
}

class Analyzer
{
public:
    using Sequence = std::vector<TOKEN::PreprocessingToken*>;

    Analyzer(const std::string &file
        , const Sequence &seq);
    ~Analyzer() = default;
    Analyzer(const Analyzer&) = delete;
    Analyzer(Analyzer&&) = delete;

    bool execute();

private:
    std::string mFile;
    const Sequence &mSeq;
};

#endif