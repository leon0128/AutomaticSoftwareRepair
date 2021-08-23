#ifndef UTILITY_TIMER_HPP
#define UTILITY_TIMER_HPP

#include <chrono>

namespace TIMER
{

template<class C = std::chrono::high_resolution_clock>
class Timer
{
public:
    using Clock = C;
    using Duration = typename Clock::duration;
    using Rep = typename Clock::rep;

    inline constexpr Timer()
        : mPoint{}
        , mDuration{}{}

    inline void start()
        {mPoint = Clock::now();}
    inline void stop()
        {mDuration += Clock::now() - mPoint;}
    inline void lap()
        {stop();start();}
    
    inline constexpr void reset()
        {mDuration = Duration{};}
    template<class T>
    inline constexpr void set(T &&t)
        {mDuration = std::chrono::duration_cast<Duration>(std::forward<T>(t));}

    template<class Duration = std::chrono::seconds>
    constexpr typename Duration::rep count() const
        {return std::chrono::duration_cast<Duration>(mDuration).count();}
    
    constexpr const Duration &duration() const noexcept
        {return mDuration;}

private:
    std::chrono::time_point<Clock> mPoint;
    Duration mDuration;
};

}

#endif