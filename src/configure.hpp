#ifndef CONFIGURE_HPP
#define CONFIGURE_HPP

#include <string>
#include <vector>

class Configure
{
public:
    inline static std::string SOURCE_FILENAME{"test.c"};
    inline static std::vector<std::string> TARGET_FUNCTION_NAMES{};
    inline static std::vector<std::string>
        POOL{"test.c"
            , "test2.c"
            , "test3.c"};
    inline static std::string RESULT_FILENAME{"repair.c"};

    inline static std::string COMPILER{"gcc"};
    inline static std::string TEST_SCRIPT{"test.sh"};
    inline static std::string TEST_FILENAME{"__test.c"};
    inline static std::string EXECUTION_NAME{"./test"};
    inline static std::string POSITIVE_TEST_PREFIX{"p"};
    inline static std::string NEGATIVE_TEST_PREFIX{"n"};
    inline static std::size_t NUM_POSITIVE_TEST{1ull};
    inline static std::size_t NUM_NEGATIVE_TEST{1ull};
    inline static int POSITIVE_TEST_WEIGHT{1};
    inline static int NEGATIVE_TEST_WEIGHT{10};
    inline static int GOAL_SCORE{11};

    inline static std::size_t FAILURE_LIMIT{10ull};

    inline static std::size_t POP_SIZE{10ull};
    inline static std::size_t MAX_GEN{10ull};
    inline static std::size_t NUM_ELITE{1ull};
    inline static std::size_t TOURNAMENT_SIZE{2ull};

    inline static double ADDING_PROBABILITY{0.75};
    inline static double SUBTRACTING_PROBABILITY{0.25};
    inline static double SWAPPING_PROBABILITY{0.00};

    inline static double ADDING_NEW_OPERATION_PROBABILITY{0.50};
    inline static double CONCATENATION_PROBABILITY{0.50};
};

#endif