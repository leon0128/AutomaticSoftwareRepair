#include <iostream>

#include "time_measurer.hpp"

decltype(TimeMeasurer::mMainTagNameMap) TimeMeasurer::mMainTagNameMap
    {{MainTag::INITIALIZING, "initializing"}
        , {MainTag::ANALYZING, "analyzing"}
        , {MainTag::SIMILARITY, "similality calculation"}
        , {MainTag::REPAIR, "repair"}};

decltype(TimeMeasurer::mSimTagNameMap) TimeMeasurer::mSimTagNameMap
    {{SimTag::CALCULATION, "similality calculation"}};

decltype(TimeMeasurer::mGATagNameMap) TimeMeasurer::mGATagNameMap
    {{GATag::INITIALIZING, "initializing"}
        , {GATag::FITNESS, "fitness calculation"}
        , {GATag::MANIPLATION, "manipulation"}};

TimeMeasurer::TimeMeasurer()
    : mMainTimers{}
    , mSimTimers{}
    , mGATimers{}
{
}

void TimeMeasurer::print()
{

}