#include <iostream>

#include "time_measurer.hpp"

decltype(TimeMeasurer::mMainTagNameMap) TimeMeasurer::mMainTagNameMap
    {{MainTag::INITIALIZING, "initializing"}
        , {MainTag::ANALYZING, "analyzing"}
        , {MainTag::SIMILARITY, "similality calculation"}
        , {MainTag::REPAIR, "repair"}};

decltype(TimeMeasurer::mSimTagNameMap) TimeMeasurer::mSimTagNameMap
    {{SimTag::METRIC, "metrics calculation"}
        , {SimTag::CALCULATION, "similality calculation"}};

decltype(TimeMeasurer::mRepairTagNameMap) TimeMeasurer::mRepairTagNameMap
    {{RepairTag::INITIALIZING, "initializing"}
        , {RepairTag::FILE_CREATION, "file creation"}
        , {RepairTag::COMPILATION, "compilation"}
        , {RepairTag::EVALUATION, "evaluation"}
        , {RepairTag::MANIPLATION, "manipulation"}};

TimeMeasurer::TimeMeasurer()
    : mMainTimers{}
    , mSimTimers{}
    , mRepairTimers{}
{
}

void TimeMeasurer::print()
{
    // MainTag
    for(std::size_t tag{0ull}; tag < cast(MainTag::TAG_SIZE); tag++)
    {
        std::cout << "main-time: "
            << mMainTagNameMap.at(MainTag{tag})
            << ": "
            << timer(MainTag{tag}).count<std::chrono::milliseconds>()
            << " (ms)"
            << std::endl;
    }
    // SimTag
    for(std::size_t tag{0ull}; tag < cast(SimTag::TAG_SIZE); tag++)
    {
        std::cout << "similarity-time: "
            << mSimTagNameMap.at(SimTag{tag})
            << ": "
            << timer(SimTag{tag}).count<std::chrono::milliseconds>()
            << " (ms)"
            << std::endl;
    }
    // RepairTag
    for(std::size_t tag{0ull}; tag < cast(RepairTag::TAG_SIZE); tag++)
    {
        std::cout << "repair-time: "
            << mRepairTagNameMap.at(RepairTag{tag})
            << ": "
            << timer(RepairTag{tag}).count<std::chrono::milliseconds>()
            << " (ms)"
            << std::endl;
    }
}