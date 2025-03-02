#include "timer.hpp"
#include <chrono>

static constexpr double sConvFactor = 1e9;

double Timer::GetCurrentTime ()
{
    // Return the current time in seconds (as a double)
    return (std::chrono::high_resolution_clock::now ().time_since_epoch ().count () / sConvFactor);
}
