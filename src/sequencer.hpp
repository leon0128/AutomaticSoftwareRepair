#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include <vector>
#include <string>

namespace TOKEN
{
    class PreprocessingToken;
}

class Sequencer
{
public:
    Sequencer(const std::string &filename);

    bool execute();

    std::vector<TOKEN::PreprocessingToken*> &sep() noexcept
        {return mSeq;}

private:
    bool openFile(std::string &src);
    bool sequencenize(const std::string &src);

    void omitWS(const std::string &src
        , std::size_t &idx) const;

    std::string mFile;
    std::vector<TOKEN::PreprocessingToken*> mSeq;
};

#endif