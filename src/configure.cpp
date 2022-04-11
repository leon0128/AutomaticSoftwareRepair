#include <iostream>

#include "configure.hpp"

decltype(Configure::flagMap) Configure::flagMap{{"--help", {Tag::HELP, false}}
    , {"--version", {Tag::VERSION, false}}
    , {"--target", {Tag::TARGET, true}}
    , {"--pool", {Tag::POOL, true}}
    , {"--result", {Tag::RESULT, true}}
    , {"--preprocessor", {Tag::PREPROCESSOR, true}}
    , {"--compiler", {Tag::COMPILER, true}}
    , {"--test-scricp", {Tag::TEST_SCRIPT, true}}
    , {"--test-filename", {Tag::TEST_FILENAME, true}}
    , {"--execution", {Tag::EXECUTION, true}}
    , {"--pos-prefix", {Tag::POS_PREFIX, true}}
    , {"--neg-prefix", {Tag::NEG_PREFIX, true}}
    , {"--num-pos", {Tag::NPOS, true}}
    , {"--num-neg", {Tag::NNEG, true}}
    , {"--pos-weight", {Tag::POS_WEIGHT, true}}
    , {"--neg-weight", {Tag::NEG_WEIGHT, true}}
    , {"--goal", {Tag::GOAL, true}}
    , {"--failure", {Tag::FAILURE, true}}
    , {"--pop", {Tag::POP, true}}
    , {"--max", {Tag::MAX, true}}
    , {"--elite", {Tag::ELITE, true}}
    , {"--tournament", {Tag::TOURNAMENT, true}}
    , {"--add-prob", {Tag::ADDING_PROB, true}}
    , {"--sub-prob", {Tag::SUBTRACTING_PROB, true}}
    , {"--swap-prob", {Tag::SWAPPING_PROB, true}}
    , {"--new-operation-prob", {Tag::NEW_OPERATION_PROB, true}}
    , {"--concatenation-prob", {Tag::CONCATENATION_PROB, true}}};

bool Configure::parseCommandLineArguments(int argc, char **argv)
{
    for(int i{1ull}; i < argc; i++)
    {
        auto &&iter{flagMap.find(argv[i])};
        if(iter != flagMap.end())
        {
            if(iter->second.second)
            {
                if(i + 1 >= argc)
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
        else
        {
            if(!readArgument(Tag::SOURCE, argv[i]))
                return false;
        }
    }

    if(!setDefaultValue())
        return false;

    if(!hasValueFlag.test(static_cast<std::size_t>(Tag::SOURCE)))
        return noHasSourceError();

    if(!checkValidity())
        return false;

    return true;
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
        case(Tag::PREPROCESSOR):
            if(!assignString(tag, arg, PREPROCESSOR))
                return false;
            break;
        case(Tag::COMPILER):
            if(!assignString(tag, arg, COMPILER))
                return false;
            break;
        case(Tag::TEST_SCRIPT):
            if(!assignString(tag, arg, TEST_SCRIPT))
                return false;
            break;
        case(Tag::TEST_FILENAME):
            if(!assignString(tag, arg, TEST_FILENAME))
                return false;
            break;
        case(Tag::EXECUTION):
            if(!assignString(tag, arg, EXECUTION_NAME))
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
        case(Tag::NEW_OPERATION_PROB):
            if(!assignDouble(tag, arg, ADDING_NEW_OPERATION_PROBABILITY))
                return false;
            break;
        case(Tag::CONCATENATION_PROB):
            if(!assignDouble(tag, arg, CONCATENATION_PROBABILITY))
                return false;
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
                RESULT_FILENAME = "result.c";
                break;
            case(Tag::PREPROCESSOR):
                PREPROCESSOR = "cpp";
                break;
            case(Tag::COMPILER):
                COMPILER = "gcc";
                break;
            case(Tag::TEST_SCRIPT):
                TEST_SCRIPT = "test.sh";
                break;
            case(Tag::TEST_FILENAME):
                TEST_FILENAME = "__test.c";
                break;
            case(Tag::EXECUTION):
                EXECUTION_NAME = "test";
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
                FAILURE_LIMIT = 10ull;
                break;
            case(Tag::POP):
                POP_SIZE = 10ull;
                break;
            case(Tag::MAX):
                MAX_GEN = 10ull;
                break;
            case(Tag::ELITE):
                NUM_ELITE = 1ull;
                break;
            case(Tag::TOURNAMENT):
                TOURNAMENT_SIZE = 2ull;
                break;
            case(Tag::ADDING_PROB):
                ADDING_PROBABILITY = 0.75;
                break;
            case(Tag::SUBTRACTING_PROB):
                SUBTRACTING_PROBABILITY = 0.25;
                break;
            case(Tag::SWAPPING_PROB):
                SWAPPING_PROBABILITY = 0.0;
                break;
            case(Tag::NEW_OPERATION_PROB):
                ADDING_NEW_OPERATION_PROBABILITY = 0.50;
                break;
            case(Tag::CONCATENATION_PROB):
                CONCATENATION_PROBABILITY = 0.50;
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
    std::cerr << "Configure::unknownFlagError():\n"
        "    flag: " << flag
        << std::endl;
    return false;
}

bool Configure::noArgumentError(const std::string &flag)
{
    std::cerr << "Configure::noArgumentError():\n"
        "    flag: " << flag
        << std::endl;
    return false;
}

bool Configure::noHasSourceError()
{
    std::cerr << "Configure::noHasSourceError():\n"
        << std::flush;
    return false;
}

bool Configure::duplicationError(const std::string &flag)
{
    std::cerr << "Configure::duplicationError():\n"
        "    flag: " << flag
        << std::endl;
    return false;
}

bool Configure::unknownTagError(Tag tag)
{
    std::cerr << "Configure::unknownTagError():\n"
        "    tag: " << static_cast<int>(tag)
        << std::endl;
    return false;
}

bool Configure::valueConvertError(const std::string &arg)
{
    std::cerr << "Configure::valueConvertError():\n"
        "    arg: " << arg
        << std::endl;
    return false;
}

bool Configure::validityError(const std::string &what)
{
    std::cerr << "Configure::validityError():\n"
        "    what: " << what
        << std::endl;
    return false;
}