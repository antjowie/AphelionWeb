#pragma once
#include "Core.h"
#include "Log.h"

#include <chrono>
#include <string>

namespace ap
{
class APHELION_API Timer
{
public:
    using Clock = std::chrono::high_resolution_clock;

    Timer() : begin(Clock::now()), last(begin)
    {
    }

    float Total() const
    {
        return float((Clock::now() - begin).count() * 1e-9f);
    }

    float Elapsed() const
    {
        return float((Clock::now() - last).count() * 1e-9f);
    }

    float Reset()
    {
        auto ts = Elapsed();
        last = Clock::now();
        return ts;
    }

private:
    Clock::time_point begin;
    Clock::time_point last;
};

/*
 * Utility class that prints a string and it's execution time afterwards
 * TODO likely should be part of instrumentation
 */
class APHELION_API TimeLog
{
public:
    TimeLog(const std::string& text) : text(text)
    {
        AP_TRACE("Creating: {}", text);
    }
    ~TimeLog()
    {
        AP_TRACE("Finished ({}s): {}", time.Elapsed(), text);
    }

private:
    const std::string& text;
    Timer time;
};
} // namespace ap
