#include <iostream>
#include <algorithm>

#include "time_measurer.hpp"

inline namespace COMMON
{

decltype(TimeMeasurer::mMainTagNameMap) TimeMeasurer::mMainTagNameMap
    {{MainTag::INITIALIZING, "initializing"}
        , {MainTag::ANALYZING, "analyzing"}
        , {MainTag::SIMILARITY, "similality calculation"}
        , {MainTag::REPAIR, "repair"}};

decltype(TimeMeasurer::mAnalyzerTagNameMap) TimeMeasurer::mAnalyzerTagNameMap
    {{AnalyzerTag::ANALYZING, "analyzing"}};

decltype(TimeMeasurer::mSimTagNameMap) TimeMeasurer::mSimTagNameMap
    {{SimTag::INITIALIZING, "initializing calculation"}
        , {SimTag::CALCULATION, "similality calculation"}};

decltype(TimeMeasurer::mRepairTagNameMap) TimeMeasurer::mRepairTagNameMap
    {{RepairTag::INITIALIZING, "initializing"}
        , {RepairTag::REP_GENERATION, "rep generation"}
        , {RepairTag::EVALUATION, "evaluation"}};

TimeMeasurer::TimeMeasurer()
    : mMainTimers{}
    , mSimTimers{}
    , mRepairTimers{}
{
}

void TimeMeasurer::print()
{
    std::cout << "time:\n" << std::flush;

    // MainTag
    std::cout << "time-total: " 
        << total<MainTag, std::chrono::milliseconds>() << " (ms)"
        << std::endl;
    for(std::size_t tag{0ull}; tag < cast(MainTag::TAG_SIZE); tag++)
    {
        Timer::Rep count{timer(MainTag{tag}).count<std::chrono::milliseconds>()};
        std::cout << "    time: "
            << mMainTagNameMap.at(MainTag{tag})
            << ": "
            << count
            << " (ms)"
            << std::endl;
    }

    // AnalyzerTag
    std::cout << "analyzer-time: total: "
        << total<AnalyzerTag, std::chrono::milliseconds>() << " (ms)"
        << std::endl;
    for(std::size_t tag{0ull}; tag < cast(AnalyzerTag::TAG_SIZE); tag++)
    {
        Timer::Rep count{timer(AnalyzerTag{tag}).count<std::chrono::milliseconds>()};
        std::cout << "    analyzer-time: "
            << mAnalyzerTagNameMap.at(AnalyzerTag{tag})
            << ": "
            << count
            << " (ms)"
            << std::endl;
    }

    // SimTag
    std::cout << "similarity-time: total: "
        << total<SimTag, std::chrono::milliseconds>() << " (ms)"
        << std::endl;
    for(std::size_t tag{0ull}; tag < cast(SimTag::TAG_SIZE); tag++)
    {
        Timer::Rep count{timer(SimTag{tag}).count<std::chrono::milliseconds>()};
        std::cout << "    similarity-time: "
            << mSimTagNameMap.at(SimTag{tag})
            << ": "
            << count
            << " (ms)"
            << std::endl;
    }

    // RepairTag
    std::cout << "repair-time: total: " 
        << total<RepairTag, std::chrono::milliseconds>() << " (ms)"
        << std::endl;
    for(std::size_t tag{0ull}; tag < cast(RepairTag::TAG_SIZE); tag++)
    {
        Timer::Rep count{timer(RepairTag{tag}).count<std::chrono::milliseconds>()};
        std::cout << "    repair-time: "
            << mRepairTagNameMap.at(RepairTag{tag})
            << ": "
            << count
            << " (ms)"
            << std::endl;
    }
}

}