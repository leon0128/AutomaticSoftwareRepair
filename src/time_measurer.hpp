#ifndef TIME_MEASURER_HPP
#define TIME_MEASURER_HPP

#include <array>
#include <unordered_map>
#include <string>

#include "utility/timer.hpp"

class TimeMeasurer;

// to be used to change tag to array's index
template<class Tag>
constexpr std::size_t cast(Tag tag) noexcept
    {return static_cast<std::size_t>(tag);}

class TimeMeasurer
{
public:
    enum class MainTag : std::size_t;
    enum class SimTag : std::size_t;
    enum class RepairTag : std::size_t;

    enum class MainTag : std::size_t
    {
        INITIALIZING
        , ANALYZING
        , SIMILARITY
        , REPAIR
        , TAG_SIZE // to be used to decide array size
    };

    enum class SimTag : std::size_t
    {
        CALCULATION
        , TAG_SIZE // to be used to decide array size
    };

    enum class RepairTag : std::size_t
    {
        INITIALIZING
        , FITNESS
        , MANIPLATION
        , TAG_SIZE // to be used to decide array size
    };

    TimeMeasurer();

    void print();

    auto &timer(MainTag tag)
        {return mMainTimers.at(cast(tag));}
    auto &timer(SimTag tag)
        {return mSimTimers.at(cast(tag));}
    auto &timer(RepairTag tag)
        {return mRepairTimers.at(cast(tag));}

    const auto &timer(MainTag tag) const
        {return mMainTimers.at(cast(tag));}
    const auto &timer(SimTag tag) const
        {return mSimTimers.at(cast(tag));}
    const auto &timer(RepairTag tag) const
        {return mRepairTimers.at(cast(tag));}

private:
    static const std::unordered_map<MainTag, std::string> mMainTagNameMap;
    static const std::unordered_map<SimTag, std::string> mSimTagNameMap;
    static const std::unordered_map<RepairTag, std::string> mRepairTagNameMap;

    std::array<TIMER::Timer<>, cast(MainTag::TAG_SIZE)> mMainTimers;
    std::array<TIMER::Timer<>, cast(SimTag::TAG_SIZE)> mSimTimers;
    std::array<TIMER::Timer<>, cast(RepairTag::TAG_SIZE)> mRepairTimers;
};

#endif