#include <iostream>

#include "time_measurer.hpp"

decltype(TimeMeasurer::mMainTagNameMap) TimeMeasurer::mMainTagNameMap
    {{MainTag::INITIALIZING, "initializing"}
        , {MainTag::ANALYZING, "analyzing"}
        , {MainTag::SIMILARITY, "similality calculation"}
        , {MainTag::REPAIR, "repair"}};

decltype(TimeMeasurer::mSimTagNameMap) TimeMeasurer::mSimTagNameMap
    {{SimTag::CALCULATION, "similality calculation"}};

decltype(TimeMeasurer::mRepairTagNameMap) TimeMeasurer::mRepairTagNameMap
    {{RepairTag::INITIALIZING, "initializing"}
        , {RepairTag::FITNESS, "fitness calculation"}
        , {RepairTag::MANIPLATION, "manipulation"}};

TimeMeasurer::TimeMeasurer()
    : mMainTimers{}
    , mSimTimers{}
    , mRepairTimers{}
{
}

void TimeMeasurer::print()
{
    auto &&printHelper{[&](const std::string &title
        , auto sizeTag
        , const auto &map)
            -> void
        {
            for(std::size_t i{0ull}; i < cast(sizeTag); i++)
            {
                // std::cout << title
                //     << map.at(decltype(sizeTag){i})
                //     << ": "
                //     << timer(decltype(sizeTag){i}).count<std::chrono::milliseconds>()
                //     << " (ms)"
                //     << std::endl;
                timer(decltype(sizeTag){i}).count<std::chrono::milliseconds>();
            }
        }};

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
}