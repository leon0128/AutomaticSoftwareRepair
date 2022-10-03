#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include <deque>
#include <string>

namespace TOKEN
{
    class PreprocessingToken;
    class EscapeSequence;
}

class Sequencer
{
public:
    using Sequence = std::deque<TOKEN::PreprocessingToken*>;

    Sequencer();
    ~Sequencer();
    Sequencer(const Sequencer&) = delete;
    Sequencer(Sequencer&&) = delete;

    bool execute(const std::string &filename);

    const Sequence &seq() const noexcept
        {return mSeq;}

private:
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
    Sequence mSeq;
};

#endif