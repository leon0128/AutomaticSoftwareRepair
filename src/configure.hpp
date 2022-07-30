#ifndef CONFIGURE_HPP
#define CONFIGURE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <bitset>

class Configure
{
private:
    enum class Tag
    {
        HELP
        , VERSION
        , SOURCE
        , TARGET
        , POOL
        , RESULT
        , COMMAND_LOG
        , TIME_LOG
        , REPAIR_LOG
        , PREPROCESSOR
        , COMPILER
        , TEST_SCRIPT
        , TEST_FILENAME
        , EXECUTION
        , POS_PREFIX
        , NEG_PREFIX
        , NPOS
        , NNEG
        , POS_WEIGHT
        , NEG_WEIGHT
        , GOAL
        , FAILURE
        , POP
        , MAX
        , ELITE
        , TOURNAMENT
        , ADDING_PROB
        , SUBTRACTING_PROB
        , SWAPPING_PROB
        , NEW_OPERATION_PROB
        , CONCATENATION_PROB
        , MAX_RECURSION
        , SIM_ORIGINAL
        , SIM_TYPE1
        , SIM_TYPE2
        , SIM_TYPE3
        , NUM_ENUM
    };

public:
    static bool parseCommandLineArguments(int argc, char **argv);

    inline static std::string SOURCE_FILENAME;
    inline static std::vector<std::string> TARGET_FUNCTION_NAMES;
    inline static std::vector<std::string> POOL;
    inline static std::string RESULT_FILENAME;

    inline static bool SHOULD_OUTPUT_COMMAND_LOG;
    inline static bool SHOULD_OUTPUT_TIME_LOG;
    inline static bool SHOULD_OUTPUT_REPAIR_LOG;

    inline static std::string PREPROCESSOR;
    inline static std::string COMPILER;
    inline static std::string TEST_SCRIPT;
    inline static std::string TEST_FILENAME;
    inline static std::string EXECUTION_NAME;
    inline static std::string POSITIVE_TEST_PREFIX;
    inline static std::string NEGATIVE_TEST_PREFIX;
    inline static std::size_t NUM_POSITIVE_TEST;
    inline static std::size_t NUM_NEGATIVE_TEST;
    inline static int POSITIVE_TEST_WEIGHT;
    inline static int NEGATIVE_TEST_WEIGHT;
    inline static int GOAL_SCORE;

    inline static std::size_t FAILURE_LIMIT;

    inline static std::size_t POP_SIZE;
    inline static std::size_t MAX_GEN;
    inline static std::size_t NUM_ELITE;
    inline static std::size_t TOURNAMENT_SIZE;

    inline static double ADDING_PROBABILITY;
    inline static double SUBTRACTING_PROBABILITY;
    inline static double SWAPPING_PROBABILITY;

    inline static double ADDING_NEW_OPERATION_PROBABILITY;
    inline static double CONCATENATION_PROBABILITY;

    inline static std::size_t MAX_RECURSION;

    inline static std::size_t SIM_ORIGINAL;
    inline static std::size_t SIM_TYPE1;
    inline static std::size_t SIM_TYPE2;
    inline static std::size_t SIM_TYPE3;

private:
    static bool readArgument(Tag
        , const std::string &arg = std::string{});
    static bool setDefaultValue();
    static bool outputHelp();
    static bool outputVersion();
    static bool assignString(Tag
        , const std::string &arg
        , std::string &target);
    static bool addString(Tag
        , const std::string &arg
        , std::vector<std::string> &target);
    static bool assignInt(Tag
        , const std::string &arg
        , int &target);
    static bool assignSizeT(Tag
        , const std::string &arg
        , std::size_t &target);
    static bool assignDouble(Tag
        , const std::string &arg
        , double &target);
    
    static bool checkDuplication(Tag);
    static bool checkValidity();

    static bool unknownFlagError(const std::string &flag);
    static bool noArgumentError(const std::string &flag);
    static bool noHasSourceError();
    static bool duplicationError(const std::string &flag);
    static bool unknownTagError(Tag);
    static bool valueConvertError(const std::string &arg);
    static bool validityError(const std::string &what);

    // key: flag(ex. --help)
    // value(first): tag
    // value(second): whether flags need extra argument
    static const std::unordered_map<std::string, std::pair<Tag, bool>> flagMap;
    inline static std::bitset<static_cast<std::size_t>(Tag::NUM_ENUM)> hasValueFlag;
};

#endif