#ifndef TIME_MEASURER_HPP
#define TIME_MEASURER_HPP

#include <map>

class TimeMeasurer;

class TimeMeasurer
{
public:
    enum MainTag : unsigned char;
    enum SimTag : unsigned char;
    enum GATag : unsigned char;

    TimeMeasurer();

private:

};

enum TimeMeasurer::MainTag : unsigned char
{
    INITIALIZING
    , ANALYZING
    , SIMILARITY
    , REPAIR
};

enum TimeMeasurer::SimTag : unsigned char
{

};

enum TimeMeasurer::GATag : unsigned char
{

};

#endif