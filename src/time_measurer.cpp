#include <iostream>
#include <algorithm>

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
    std::cout << "time:\n" << std::flush;

    // this variable is reused sim-tag and repair-tag.
    // don't forget to initialize.
    Timer::Rep total{0};

    // MainTag
    for(std::size_t tag{0ull}; tag < cast(MainTag::TAG_SIZE); tag++)
    {
        Timer::Rep count{timer(MainTag{tag}).count<std::chrono::milliseconds>()};
        std::cout << "    time: "
            << mMainTagNameMap.at(MainTag{tag})
            << ": "
            << count
            << " (ms)"
            << std::endl;
        total += count;
    }
    std::cout << "time-total: " 
        << total << " (ms)"
        << std::endl;

    // SimTag
    total = 0;
    for(std::size_t tag{0ull}; tag < cast(SimTag::TAG_SIZE); tag++)
    {
        Timer::Rep count{timer(SimTag{tag}).count<std::chrono::milliseconds>()};
        std::cout << "    similarity-time: "
            << mSimTagNameMap.at(SimTag{tag})
            << ": "
            << count
            << " (ms)"
            << std::endl;
        total += count;
    }
    std::cout << "similarity-time: total: "
        << total << " (ms)"
        << std::endl;

    // RepairTag
    total = 0;
    for(std::size_t tag{0ull}; tag < cast(RepairTag::TAG_SIZE); tag++)
    {
        Timer::Rep count{timer(RepairTag{tag}).count<std::chrono::milliseconds>()};
        std::cout << "    repair-time: "
            << mRepairTagNameMap.at(RepairTag{tag})
            << ": "
            << count
            << " (ms)"
            << std::endl;
        total += count;
    }
    std::cout << "repair-time: total: " 
        << total << " (ms)"
        << std::endl;
}