#ifndef CONFIGURE_HPP
#define CONFIGURE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <bitset>
#include <mutex>

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
        , SUBPROCESS_LOG
        , PREPROCESSOR
        , COMPILER
        , TEST_SCRIPT
        , EXEC_EXTENSION
        , NULL_FILENAME
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
        , NEW_CREATION_PROB
        , NUM_CONCURRENCY
        , MAX_RECURSION
        , USE_SIMILARITY
        , SIM_ORIGINAL
        , SIM_TYPE1
        , SIM_TYPE2
        , SIM_TYPE3
        , SIM_CAPACITY
        , SIM_NUMBER_OF_USE
        , SIM_CHANGE_PROB
        , NUM_ENUM
    };

public:
    static bool parseCommandLineArguments(int argc, char **argv);

#define GET_SAFELY(objectName) \
    inline static auto getSafely##objectName() \
    { \
        static std::mutex mutex; \
        std::lock_guard lock{mutex}; \
        return objectName; \
    }

    inline static std::string SOURCE_FILENAME;
    GET_SAFELY(SOURCE_FILENAME)
    inline static std::vector<std::string> TARGET_FUNCTION_NAMES;
    GET_SAFELY(TARGET_FUNCTION_NAMES)
    inline static std::vector<std::string> POOL;
    GET_SAFELY(POOL)
    inline static std::string RESULT_FILENAME;
    GET_SAFELY(RESULT_FILENAME)

    inline static bool SHOULD_OUTPUT_COMMAND_LOG;
    GET_SAFELY(SHOULD_OUTPUT_COMMAND_LOG)
    inline static bool SHOULD_OUTPUT_TIME_LOG;
    GET_SAFELY(SHOULD_OUTPUT_TIME_LOG)
    inline static bool SHOULD_OUTPUT_REPAIR_LOG;
    GET_SAFELY(SHOULD_OUTPUT_REPAIR_LOG)
    inline static bool SHOULD_OUTPUT_SUBPROCESS_LOG;
    GET_SAFELY(SHOULD_OUTPUT_SUBPROCESS_LOG)

    inline static std::string PREPROCESSOR;
    GET_SAFELY(PREPROCESSOR)
    inline static std::string COMPILER;
    GET_SAFELY(COMPILER)
    inline static std::string TEST_SCRIPT;
    GET_SAFELY(TEST_SCRIPT)
    inline static std::string EXEC_EXTENSION;
    GET_SAFELY(EXEC_EXTENSION)
    inline static std::string EXECUTION_NAME;
    GET_SAFELY(EXECUTION_NAME)
    inline static std::string NULL_FILENAME;
    GET_SAFELY(NULL_FILENAME)
    inline static std::string POSITIVE_TEST_PREFIX;
    GET_SAFELY(POSITIVE_TEST_PREFIX)
    inline static std::string NEGATIVE_TEST_PREFIX;
    GET_SAFELY(NEGATIVE_TEST_PREFIX)
    inline static std::size_t NUM_POSITIVE_TEST;
    GET_SAFELY(NUM_POSITIVE_TEST)
    inline static std::size_t NUM_NEGATIVE_TEST;
    GET_SAFELY(NUM_NEGATIVE_TEST)
    inline static int POSITIVE_TEST_WEIGHT;
    GET_SAFELY(POSITIVE_TEST_WEIGHT)
    inline static int NEGATIVE_TEST_WEIGHT;
    GET_SAFELY(NEGATIVE_TEST_WEIGHT)
    inline static int GOAL_SCORE;
    GET_SAFELY(GOAL_SCORE)

    inline static std::size_t FAILURE_LIMIT;
    GET_SAFELY(FAILURE_LIMIT)

    inline static std::size_t POP_SIZE;
    GET_SAFELY(POP_SIZE)
    inline static std::size_t MAX_GEN;
    GET_SAFELY(MAX_GEN)
    inline static std::size_t NUM_ELITE;
    GET_SAFELY(NUM_ELITE)
    inline static std::size_t TOURNAMENT_SIZE;
    GET_SAFELY(TOURNAMENT_SIZE)

    inline static double ADDING_PROBABILITY;
    GET_SAFELY(ADDING_PROBABILITY)
    inline static double SUBTRACTING_PROBABILITY;
    GET_SAFELY(SUBTRACTING_PROBABILITY)
    inline static double SWAPPING_PROBABILITY;
    GET_SAFELY(SWAPPING_PROBABILITY)

    inline static double NEW_CREATION_PROB;
    GET_SAFELY(NEW_CREATION_PROB)

    inline static std::size_t NUM_CONCURRENCY;
    GET_SAFELY(NUM_CONCURRENCY)
    inline static std::size_t MAX_RECURSION;
    GET_SAFELY(MAX_RECURSION)

    inline static bool SHOULD_USE_SIMILARITY;
    GET_SAFELY(SHOULD_USE_SIMILARITY)

    inline static std::size_t SIM_ORIGINAL;
    GET_SAFELY(SIM_ORIGINAL)
    inline static std::size_t SIM_TYPE1;
    GET_SAFELY(SIM_TYPE1)
    inline static std::size_t SIM_TYPE2;
    GET_SAFELY(SIM_TYPE2)
    inline static std::size_t SIM_TYPE3;
    GET_SAFELY(SIM_TYPE3)
    inline static double SIM_CAPACITY;
    GET_SAFELY(SIM_CAPACITY)
    inline static std::size_t SIM_NUMBER_OF_USE;
    GET_SAFELY(SIM_NUMBER_OF_USE)
    inline static bool SHOULD_CHANGE_PROB;
    GET_SAFELY(SHOULD_CHANGE_PROB)

#undef GET_SAFELY

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