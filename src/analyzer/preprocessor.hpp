#ifndef ANALYZER_PREPROCESSOR_HPP
#define ANALYZER_PREPROCESSOR_HPP

#include <deque>
#include <string>

#include "common/token.hpp"

namespace ANALYZER
{

class Preprocessor
{
public:
    Preprocessor();
    ~Preprocessor();

    Preprocessor(const Preprocessor&) = delete;
    Preprocessor(Preprocessor&&) = delete;

    bool execute(const std::string &filename);

    auto &&sequence() const noexcept
        {return mPTs;}

private:
    bool initialize(const std::string &filename);
    void finalize();

    bool readFile(const std::string &filename);
    bool concatenateLine();
    bool deleteComment();
    bool addMark();
    bool writeFile(const std::string &filename);
    bool executeCommand(const std::string &inputFilename
        , const std::string &outputFilename);
    bool decompose();
    bool concatenateStringLiteral();

    bool fileReadingError(const std::string &filename) const;
    bool preprocessingError(const std::string &filename) const;
    bool decomposingError(const std::string &filename) const;

    std::string mFilename;
    std::string mMarkedFilename;
    std::string mPreprocessedFilename;
    std::string mContents;
    std::deque<TOKEN::PreprocessingToken*> mPTs;
};

}

#endif