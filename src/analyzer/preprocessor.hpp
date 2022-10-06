#ifndef ANALYZER_PREPROCESSOR_HPP
#define ANALYZER_PREPROCESSOR_HPP

#include <deque>
#include <string>
#include <utility>

#include "common/token.hpp"

namespace ANALYZER
{

class Preprocessor
{
public:
    using Sequence = std::deque<TOKEN::PreprocessingToken*>;

    Preprocessor();
    ~Preprocessor();
    Preprocessor(const Preprocessor&) = delete;
    Preprocessor(Preprocessor&&) = delete;

    bool execute(const std::string &filename);

    const auto &sequence() const noexcept
        {return mSeq;}

private:
    void finalize();

    bool openFile(std::string &src);
    bool preprocess();
    bool sequencenize(const std::string &src);
    bool convertCharacter();
    bool concatenateStringLiteral();

    void omitWS(const std::string &src
        , std::size_t &idx) const;
    bool convertEscapeSequence(TOKEN::EscapeSequence*
        , char &res) const;

    std::string mFile;
    std::string mTemporaryFilename;
    Sequence mSeq;
};

}

#endif