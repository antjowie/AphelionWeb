#pragma once
#include <chrono>

#include "Core.h"

namespace ap
{
class Timer
{
  public:
    using Clock = std::chrono::high_resolution_clock;

    APHELION_API Timer() : begin(Clock::now()), last(begin)
    {
    }

    APHELION_API float Total() const
    {
        return float((Clock::now() - begin).count() * 1e-9f);
    }

    APHELION_API float Elapsed() const
    {
        return float((Clock::now() - last).count() * 1e-9f);
    }

    APHELION_API float Reset()
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
