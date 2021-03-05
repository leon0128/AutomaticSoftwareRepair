#ifndef GA_CONFUGURE_HPP
#define GA_CONFIGURE_HPP

#include <cstddef>

namespace GA
{

class Configure
{
public:
    inline static std::size_t POP_SIZE = 10;
    inline static std::size_t MAX_GEN = 2;
    inline static std::size_t NUM_ELITE = 1;
    inline static std::size_t TOURNAMENT_SIZE = 2;

    inline static int GOAL_SCORE = 10;

    inline static const char *COMPILER = "gcc";
    inline static const char *TEST_NAME = "__test";
    inline static const char *TEST_SCRIPT = "test.sh";
    inline static const char *POSITIVE_TEST_PREFIX = "p";
    inline static const char *NEGATIVE_TEST_PREFIX = "n";
    inline static int NUM_POSITIVE = 1;
    inline static int NUM_NEGATIVE = 0;
    inline static int POSITIVE_WEIGHT = 1;
    inline static int NEGATIVE_WEIGHT = 10;

    inline static double ADDING_PROBABILITY = 0.50;
    inline static double SUBTRACTING_PROBABILITY = 0.25;
    inline static double SWAPPING_PROBABILITY = 0.25;

    inline static double NEW_OPERATION_PROBABILITY = 0.50;
    inline static double COMBINATION_PROBABILITY = 0.50;
};

}

#endif