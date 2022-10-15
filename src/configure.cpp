#include <iostream>
#include <regex>

#include "utility/output.hpp"
#include "configure.hpp"

decltype(Configure::flagMap) Configure::flagMap{{"--help", {Tag::HELP, false}}
    , {"--version", {Tag::VERSION, false}}
    , {"--target", {Tag::TARGET, true}}
    , {"--pool", {Tag::POOL, true}}
    , {"--result", {Tag::RESULT, true}}
    , {"--command-log", {Tag::COMMAND_LOG, false}}
    , {"--time-log", {Tag::TIME_LOG, false}}
    , {"--repair-log", {Tag::REPAIR_LOG, false}}
    , {"--subprocess-log", {Tag::SUBPROCESS_LOG, false}}
    , {"--analyze-log", {Tag::ANALYZE_LOG, false}}
    , {"--specified-log", {Tag::SPECIFIED_LOG, false}}
    , {"--no-ignore-pool", {Tag::NO_IGNORE_POOL, false}}
    , {"--no-divide-for", {Tag::NO_DIVIDE_FOR, false}}
    , {"--preprocessor", {Tag::PREPROCESSOR, true}}
    , {"--compiler", {Tag::COMPILER, true}}
    , {"--builtin", {Tag::BUILTIN, true}}
    , {"--test", {Tag::TEST_SCRIPT, true}}
    , {"--exec-extension", {Tag::EXEC_EXTENSION, true}}
    , {"--null-filename", {Tag::NULL_FILENAME, true}}
    , {"--pos-prefix", {Tag::POS_PREFIX, true}}
    , {"--neg-prefix", {Tag::NEG_PREFIX, true}}
    , {"--num-pos", {Tag::NPOS, true}}
    , {"--num-neg", {Tag::NNEG, true}}
    , {"--pos-weight", {Tag::POS_WEIGHT, true}}
    , {"--neg-weight", {Tag::NEG_WEIGHT, true}}
    , {"--goal", {Tag::GOAL, true}}
    , {"--failure", {Tag::FAILURE, true}}
    , {"--pop", {Tag::POP, true}}
    , {"--gen", {Tag::MAX, true}}
    , {"--elite", {Tag::ELITE, true}}
    , {"--tournament", {Tag::TOURNAMENT, true}}
    , {"--add-prob", {Tag::ADDING_PROB, true}}
    , {"--sub-prob", {Tag::SUBTRACTING_PROB, true}}
    , {"--swap-prob", {Tag::SWAPPING_PROB, true}}
    , {"--new-creation-prob", {Tag::NEW_CREATION_PROB, true}}
    , {"--num-concurrency", {Tag::NUM_CONCURRENCY, true}}
    , {"--max-recursion", {Tag::MAX_RECURSION, true}}
    , {"--no-use-similarity", {Tag::NO_USE_SIMILARITY, false}}
    , {"--original", {Tag::SIM_ORIGINAL, true}}
    , {"--type1", {Tag::SIM_TYPE1, true}}
    , {"--type2", {Tag::SIM_TYPE2, true}}
    , {"--type3", {Tag::SIM_TYPE3, true}}
    , {"--capacity", {Tag::SIM_CAPACITY, true}}
    , {"--num-use-external", {Tag::SIM_NUMBER_OF_USE, true}}
    , {"--no-change-prob", {Tag::SIM_NO_CHANGE_PROB, false}}};

bool Configure::parseCommandLineArguments(int argc, char **argv)
{
    if(!parseOption(argc, argv))
        return false;

    if(!setDefaultValue())
        return false;

    if(!hasValueFlag.test(static_cast<std::size_t>(Tag::SOURCE)))
        return noHasSourceError();

    if(!checkValidity())
        return false;

    return true;
}

bool Configure::parseOption(int argc
    , char **argv)
{
    for(int i{1}; i < argc; i++)
    {
        // parse target source code
        if(!isOption(argv[i]))
        {
            if(!readArgument(Tag::SOURCE, argv[i]))
                return false;
        }
        // option
        else
        {
            auto &&iter{flagMap.find(argv[i])};
            if(iter == flagMap.end())
                return unknownFlagError(argv[i]);
        
            if(iter->second.second)
            {
                if(i + 1 >= argc
                    || isOption(argv[i + 1]))
                    return noArgumentError(argv[i]);
                
                if(!readArgument(iter->second.first, argv[i + 1]))
                    return false;
                
                i++;
            }
            else
            {
                if(!readArgument(iter->second.first))
                    return false;
            }
        }
    }
    
    return true;
}

bool Configure::isOption(const char *arg)
{
    static const std::regex regex{"^--(.*)"};

    return std::regex_match(arg, regex);
}

bool Configure::readArgument(Tag tag
    , const std::string &arg)
{
    switch(tag)
    {
        case(Tag::HELP):
            outputHelp();
            break;
        case(Tag::VERSION):
            outputVersion();
            break;
        case(Tag::SOURCE):
            if(!assignString(tag, arg, SOURCE_FILENAME))
                return false;
            break;
        case(Tag::TARGET):
            if(!addString(tag, arg, TARGET_FUNCTION_NAMES))
                return false;
            break;
        case(Tag::POOL):
            if(!addString(tag, arg, POOL))
                return false;
            break;
        case(Tag::RESULT):
            if(!assignString(tag, arg, RESULT_FILENAME))
                return false;
            break;
        case(Tag::COMMAND_LOG):
            SHOULD_OUTPUT_COMMAND_LOG = true;
            break;
        case(Tag::TIME_LOG):
            SHOULD_OUTPUT_TIME_LOG = true;
            break;
        case(Tag::REPAIR_LOG):
            SHOULD_OUTPUT_REPAIR_LOG = true;
            break;
        case(Tag::SUBPROCESS_LOG):
            SHOULD_OUTPUT_SUBPROCESS_LOG = true;
            break;
        case(Tag::ANALYZE_LOG):
            SHOULD_OUTPUT_ANALYZE_LOG = true;
            break;
        case(Tag::SPECIFIED_LOG):
            SHOULD_OUTPUT_SPECIFIED_LOG = true;
            break;
        case(Tag::NO_IGNORE_POOL):
            SHOULD_IGNORE_POOL = false;
            break;
        case(Tag::NO_DIVIDE_FOR):
            SHOULD_DIVIDE_FOR = false;
        case(Tag::PREPROCESSOR):
            if(!assignString(tag, arg, PREPROCESSOR))
                return false;
            break;
        case(Tag::COMPILER):
            if(!assignString(tag, arg, COMPILER))
                return false;
            break;
        case(Tag::BUILTIN):
            if(!assignString(tag, arg, BUILTIN))
                return false;
            break;
        case(Tag::TEST_SCRIPT):
            if(!assignString(tag, arg, TEST_SCRIPT))
                return false;
            break;
        case(Tag::EXEC_EXTENSION):
            if(!assignString(tag, arg, EXEC_EXTENSION))
                return false;
            break;
        case(Tag::NULL_FILENAME):
            if(!assignString(tag, arg, NULL_FILENAME))
                return false;
            break;
        case(Tag::POS_PREFIX):
            if(!assignString(tag, arg, POSITIVE_TEST_PREFIX))
                return false;
            break;
        case(Tag::NEG_PREFIX):
            if(!assignString(tag, arg, NEGATIVE_TEST_PREFIX))
                return false;
            break;
        case(Tag::NPOS):
            if(!assignSizeT(tag, arg, NUM_POSITIVE_TEST))
                return false;
            break;
        case(Tag::NNEG):
            if(!assignSizeT(tag, arg, NUM_NEGATIVE_TEST))
                return false;
            break;
        case(Tag::POS_WEIGHT):
            if(!assignInt(tag, arg, POSITIVE_TEST_WEIGHT))
                return false;
            break;
        case(Tag::NEG_WEIGHT):
            if(!assignInt(tag, arg, NEGATIVE_TEST_WEIGHT))
                return false;
            break;
        case(Tag::GOAL):
            if(!assignInt(tag, arg, GOAL_SCORE))
                return false;
            break;
        case(Tag::FAILURE):
            if(!assignSizeT(tag, arg, FAILURE_LIMIT))
                return false;
            break;
        case(Tag::POP):
            if(!assignSizeT(tag, arg, POP_SIZE))
                return false;
            break;
        case(Tag::MAX):
            if(!assignSizeT(tag, arg, MAX_GEN))
                return false;
            break;
        case(Tag::ELITE):
            if(!assignSizeT(tag, arg, NUM_ELITE))
                return false;
            break;
        case(Tag::TOURNAMENT):
            if(!assignSizeT(tag, arg, TOURNAMENT_SIZE))
                return false;
            break;
        case(Tag::ADDING_PROB):
            if(!assignDouble(tag, arg, ADDING_PROBABILITY))
                return false;
            break;
        case(Tag::SUBTRACTING_PROB):
            if(!assignDouble(tag, arg, SUBTRACTING_PROBABILITY))
                return false;
            break;
        case(Tag::SWAPPING_PROB):
            if(!assignDouble(tag, arg, SWAPPING_PROBABILITY))
                return false;
            break;
        case(Tag::NEW_CREATION_PROB):
            if(!assignDouble(tag, arg, NEW_CREATION_PROB))
                return false;
            break;
        case(Tag::NUM_CONCURRENCY):
            if(!assignSizeT(tag, arg, NUM_CONCURRENCY))
                return false;
            break;
        case(Tag::MAX_RECURSION):
            if(!assignSizeT(tag, arg, MAX_RECURSION))
                return false;
            break;
        case(Tag::NO_USE_SIMILARITY):
            SHOULD_USE_SIMILARITY = false;
            break;
        case(Tag::SIM_ORIGINAL):
            if(!assignSizeT(tag, arg, SIM_ORIGINAL))
                return false;
            break;
        case(Tag::SIM_TYPE1):
            if(!assignSizeT(tag, arg, SIM_TYPE1))
                return false;
            break;
        case(Tag::SIM_TYPE2):
            if(!assignSizeT(tag, arg, SIM_TYPE2))
                return false;
            break;
        case(Tag::SIM_TYPE3):
            if(!assignSizeT(tag, arg, SIM_TYPE3))
                return false;
            break;
        case(Tag::SIM_CAPACITY):
            if(!assignDouble(tag, arg, SIM_CAPACITY))
                return false;
            break;
        case(Tag::SIM_NUMBER_OF_USE):
            if(!assignSizeT(tag, arg, SIM_NUMBER_OF_USE))
                return false;
            break;
        case(Tag::SIM_NO_CHANGE_PROB):
            SHOULD_CHANGE_PROB = false;
            break;
        default:
            return unknownTagError(tag);
    }

    hasValueFlag.set(static_cast<std::size_t>(tag));

    return true;
}

bool Configure::setDefaultValue()
{
    for(std::size_t i{0ull}; i < static_cast<std::size_t>(Tag::NUM_ENUM); i++)
    {
        if(hasValueFlag.test(i))
            continue;

        switch(static_cast<Tag>(i))
        {
            case(Tag::POOL):
                POOL.emplace_back(SOURCE_FILENAME);
                break;
            case(Tag::RESULT):
                RESULT_FILENAME = "test/result.c";
                break;
            case(Tag::COMMAND_LOG):
                SHOULD_OUTPUT_COMMAND_LOG = false;
                break;
            case(Tag::TIME_LOG):
                SHOULD_OUTPUT_TIME_LOG = false;
                break;
            case(Tag::REPAIR_LOG):
                SHOULD_OUTPUT_REPAIR_LOG = false;
                break;
            case(Tag::SUBPROCESS_LOG):
                SHOULD_OUTPUT_SUBPROCESS_LOG = false;
                break;
            case(Tag::ANALYZE_LOG):
                SHOULD_OUTPUT_ANALYZE_LOG = false;
                break;
            case(Tag::SPECIFIED_LOG):
                SHOULD_OUTPUT_SPECIFIED_LOG = false;
                break;
            case(Tag::NO_IGNORE_POOL):
                SHOULD_IGNORE_POOL = true;
                break;
            case(Tag::NO_DIVIDE_FOR):
                SHOULD_DIVIDE_FOR = true;
                break;
            case(Tag::PREPROCESSOR):
                PREPROCESSOR = "cpp -P -I./test/ -D__extension__=";
                break;
            case(Tag::COMPILER):
                COMPILER = "gcc";
                break;
            case(Tag::BUILTIN):
                BUILTIN = "builtin.h";
                break;
            case(Tag::TEST_SCRIPT):
                TEST_SCRIPT = "test.sh";
                break;
            case(Tag::EXEC_EXTENSION):
                EXEC_EXTENSION = "";
                break;
            case(Tag::NULL_FILENAME):
                NULL_FILENAME = "/dev/null";
                break;
            case(Tag::POS_PREFIX):
                POSITIVE_TEST_PREFIX = "p";
                break;
            case(Tag::NEG_PREFIX):
                NEGATIVE_TEST_PREFIX = "n";
                break;
            case(Tag::NPOS):
                NUM_POSITIVE_TEST = 1ull;
                break;
            case(Tag::NNEG):
                NUM_NEGATIVE_TEST = 1ull;
                break;
            case(Tag::POS_WEIGHT):
                POSITIVE_TEST_WEIGHT = 1;
                break;
            case(Tag::NEG_WEIGHT):
                NEGATIVE_TEST_WEIGHT = 10;
                break;
            case(Tag::GOAL):
                GOAL_SCORE = 11;
                break;
            case(Tag::FAILURE):
                FAILURE_LIMIT = 16ull;
                break;
            case(Tag::POP):
                POP_SIZE = 1000ull;
                break;
            case(Tag::MAX):
                MAX_GEN = 10ull;
                break;
            case(Tag::ELITE):
                NUM_ELITE = 2ull;
                break;
            case(Tag::TOURNAMENT):
                TOURNAMENT_SIZE = 3ull;
                break;
            case(Tag::ADDING_PROB):
                ADDING_PROBABILITY = 0.2;
                break;
            case(Tag::SUBTRACTING_PROB):
                SUBTRACTING_PROBABILITY = 0.2;
                break;
            case(Tag::SWAPPING_PROB):
                SWAPPING_PROBABILITY = 0.6;
                break;
            case(Tag::NEW_CREATION_PROB):
                NEW_CREATION_PROB = 0.20;
                break;
            case(Tag::NUM_CONCURRENCY):
                NUM_CONCURRENCY = 16;
                break;
            case(Tag::MAX_RECURSION):
                MAX_RECURSION = 16ull;
                break;
            case(Tag::NO_USE_SIMILARITY):
                SHOULD_USE_SIMILARITY = true;
                break;
            case(Tag::SIM_ORIGINAL):
                SIM_ORIGINAL = 1ull;
                break;
            case(Tag::SIM_TYPE1):
                SIM_TYPE1 = 4ull;
                break;
            case(Tag::SIM_TYPE2):
                SIM_TYPE2 = 4ull;
                break;
            case(Tag::SIM_TYPE3):
                SIM_TYPE3 = 4ull;
                break;
            case(Tag::SIM_CAPACITY):
                SIM_CAPACITY = 1.0;
                break;
            case(Tag::SIM_NUMBER_OF_USE):
                SIM_NUMBER_OF_USE = 32ull;
                break;
            case(Tag::SIM_NO_CHANGE_PROB):
                SHOULD_CHANGE_PROB = true;
                break;

            default:;
        }
    }

    return true;
}

bool Configure::outputHelp()
{
    std::cout << "help\n"
        << std::flush;
    return true;
}

bool Configure::outputVersion()
{
    std::cout << "version\n"
        << std::flush;
    return true;
}

bool Configure::assignString(Tag tag
    , const std::string &arg
    , std::string &target)
{
    if(!checkDuplication(tag))
        return false;

    target = arg;
    return true;
}

bool Configure::addString(Tag tag
    , const std::string &arg
    , std::vector<std::string> &target)
{
    target.push_back(arg);
    return true;
}

bool Configure::assignInt(Tag tag
    , const std::string &arg
    , int &target)
{
    if(!checkDuplication(tag))
        return false;
    
    try
    {
        target = std::stoi(arg);
    }
    catch(const std::exception &e)
    {
        return valueConvertError(arg);
    }

    return true;
}

bool Configure::assignSizeT(Tag tag
    , const std::string &arg
    , std::size_t &target)
{
    if(!checkDuplication(tag))
        return false;
    
    try
    {
        target = std::stoull(arg);
    }
    catch(const std::exception &e)
    {
        return valueConvertError(arg);
    }

    return true;
}

bool Configure::assignDouble(Tag tag
    , const std::string &arg
    , double &target)
{
    if(!checkDuplication(tag))
        return false;
    
    try
    {
        target = std::stod(arg);
    }
    catch(const std::exception &e)
    {
        return valueConvertError(arg);
    }

    return true;
}

bool Configure::checkDuplication(Tag tag)
{
    if(hasValueFlag.test(static_cast<std::size_t>(tag)))
    {
        std::string flag;
        for(const auto &pair : flagMap)
        {
            if(pair.second.first == tag)
            {
                flag = pair.first;
                break;
            }
        }
        flag = "source file";

        return duplicationError(flag);
    }

    return true;
}

bool Configure::checkValidity()
{
    if(Configure::MAX_GEN <= 0)
        return validityError("MAX_GEN <= 0");
    else if(Configure::POP_SIZE <= 0)
        return validityError("POP_SIZE <= 0");
    else if(Configure::POP_SIZE < Configure::NUM_ELITE)
        return validityError("POP_SIZE < NUM_ELITE");
    else if(Configure::TOURNAMENT_SIZE <= 0
        || Configure::TOURNAMENT_SIZE > Configure::POP_SIZE)
        return validityError("TOURNAMENT_SIZE <= 0 || TOURNAMENT_SIZE > POP_SIZE");
    else if(Configure::POOL.empty())
        return validityError("POOL is empty");
    
    return true;
}

bool Configure::unknownFlagError(const std::string &flag)
{
    std::cerr << OUTPUT::charRedCode
        << "Configure::unknownFlagError():\n"
        << OUTPUT::resetCode
        << "    flag: " << flag
        << std::endl;
    return false;
}

bool Configure::noArgumentError(const std::string &flag)
{
    std::cerr << OUTPUT::charRedCode
        << "Configure::noArgumentError():\n"
        << OUTPUT::resetCode
        << "    flag: " << flag
        << std::endl;
    return false;
}

bool Configure::noHasSourceError()
{
    std::cerr << OUTPUT::charRedCode
        << "Configure::noHasSourceError():\n"
        << OUTPUT::resetCode
        << std::flush;
    return false;
}

bool Configure::duplicationError(const std::string &flag)
{
    std::cerr << OUTPUT::charRedCode
        << "Configure::duplicationError():\n"
        << OUTPUT::resetCode
        << "    flag: " << flag
        << std::endl;
    return false;
}

bool Configure::unknownTagError(Tag tag)
{
    std::cerr << OUTPUT::charRedCode
        << "Configure::unknownTagError():\n"
        << OUTPUT::resetCode
        << "    tag: " << static_cast<int>(tag)
        << std::endl;
    return false;
}

bool Configure::valueConvertError(const std::string &arg)
{
    std::cerr << OUTPUT::charRedCode
        << "Configure::valueConvertError():\n"
        << OUTPUT::resetCode
        << "    arg: " << arg
        << std::endl;
    return false;
}

bool Configure::validityError(const std::string &what)
{
    std::cerr << OUTPUT::charRedCode
        <<  "Configure::validityError():\n"
        << OUTPUT::resetCode
        << "    what: " << what
        << std::endl;
    return false;
}