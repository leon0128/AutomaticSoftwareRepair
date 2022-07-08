#ifndef TIME_CONTROLLER_HPP
#define TIME_CONTROLLER_HPP

#include <map>

class TimeController;

class TimeController
{
public:
    enum MainTag : unsigned char
    {
        INITIALIZING
        , ANALYZING
        , SIMILARITY
        , GA
    };
    enum SimTag : unsigned char
    {

    };
    enum GATag : unsigned char
    {
        INITIALIZING
        , FITNESS
        , COMPILING
        , MANIPULATION
    };

    TimeController();

private:

};

#endif