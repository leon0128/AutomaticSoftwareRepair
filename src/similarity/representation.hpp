#ifndef SIMILARITY_REPRESENTATION_HPP
#define SIMILARITY_REPRESENTATION_HPP

#include <array>
#include <deque>
#include <string>

namespace SIM
{

class RepresentationCreator;

class Representation
{
public:
    // public class declarations
    enum class Tag : std::size_t;
    class Element;

    // public static member functions
    static void deleteReps();

    static auto &reps() noexcept
        {return mReps;}
    static constexpr std::size_t castTag(Tag tag) noexcept
        {return static_cast<std::size_t>(tag);}

    // public member functions
    Representation()
        : mGramSize{0ull}
        , mTokens{}{}
    Representation(std::size_t gramSize
        , const std::deque<std::string> &tokens)
        : mGramSize{gramSize}
        , mTokens{tokens}{}
    Representation(std::size_t gramSize
        , std::deque<std::string> &&tokens)
        : mGramSize{gramSize}
        , mTokens{tokens}{}

    const auto & gramSize() const noexcept
        {return mGramSize;}
    auto &gramSize() noexcept
        {return mGramSize;}
    const auto &tokens() const noexcept
        {return mTokens;}
    auto &tokens() noexcept
        {return mTokens;}

private:
    // private static member variable declarations
    static std::deque<Element*> mReps;

    // private member variable declarations
    std::size_t mGramSize;
    std::deque<std::string> mTokens;
};

enum class Representation::Tag : std::size_t
{
    ORIGINAL
    , TYPE1
    , TYPE2
    , TYPE3
    , SIZE_OF_TAG
};

class Representation::Element
{
public:
    std::string mFilename{"__unspecific-filename__"};
    std::string mFunctionName{"__unspecific-function-name__"};
    std::array<Representation, castTag(Tag::SIZE_OF_TAG)> mReps{Representation{}}; 
};

}

#endif