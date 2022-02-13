#pragma once
#include "Core.h"

#include <chrono>

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
} // namespace ap
