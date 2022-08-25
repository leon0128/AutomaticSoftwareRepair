#ifndef SIMILARITY_CALCULATOR_HPP
#define SIMILARITY_CALCULATOR_HPP

#include <deque>
#include <unordered_map>
#include <string>
#include <array>

#include "representation.hpp"

namespace SIM
{

class Calculator
{
public:
    Calculator() = delete;

    // use Representation::reps to calculate similarity
    // result of calculation is stored to Calculator::mSimilarity
    static bool initialize();
    static void finalize();

    static std::deque<double> calculateSimilarity(const Representation::Element*);

private:
    // this class is used as map::element
    class Element;

    // initialization
    // calculate and register information to mInfo.
    static bool calculateAndRegisterInfo();
    static bool calculateAndRegisterTF();
    static bool calculateAndRegisterDF();
    static bool calculateAndRegisterIDF();
    static bool calculateAndRegisterBoost();

    // query reduction
    // if term that is contained tokens is not exist in mInfo,
    // that term is not used.
    static std::deque<std::size_t> calculateIndicesToUse(Representation::Tag
        , const std::deque<std::string> &tokens);

    // score calculation
    // result is calculated by mInfo and Rep::reps()
    static double calculateScoreSiamese(const Representation::Element *queries
        , const std::array<std::deque<std::size_t>, Representation::castTag(Representation::Tag::SIZE_OF_TAG)> &idxToUseArray
        , std::size_t docIdx);
    static double calculateScore(Representation::Tag
        , const std::deque<std::string> &query
        , const std::deque<std::size_t> &idxToUse
        , std::size_t docIdx);
    static double calculateTF(Representation::Tag
        , const std::string &term
        , std::size_t docIdx);
    static double calculateIDF(Representation::Tag
        , const std::string &term);
    static double calculateBoost(Representation::Tag
        , const std::string &term);
    static double calculateNorm(Representation::Tag
        , std::size_t docIdx);
    static double calculateQueryNorm(Representation::Tag
        , const std::deque<std::string> &query
        , const std::deque<std::size_t> &idxToUse);
    static double calculateCoord(Representation::Tag
        , const std::deque<std::string> &query
        , const std::deque<std::size_t> &idxToUse
        , std::size_t docIdx);

    // delete mInfo
    static void deleteInfo();

    inline static std::array<std::unordered_map<std::string, Element*>, Representation::castTag(Representation::Tag::SIZE_OF_TAG)> mInfo{};
};

class Calculator::Element
{
public:
    std::deque<double> mTF{};
    std::size_t mDF{0ull};
    double mIDF{0.0};
    double mBoost{0.0};
};

}

#endif