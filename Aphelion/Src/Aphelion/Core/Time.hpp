#pragma once
#include <chrono>

#include "Core.hpp"

namespace ap {
class APHELION_API Timer {
 public:
  using Clock = std::chrono::high_resolution_clock;

  Timer() : m_begin(Clock::now()), m_last(m_begin) {}

  float Total() const {
    return float((Clock::now() - m_begin).count() * 1e-9f);
  }

  float Elapsed() const {
    return float((Clock::now() - m_last).count() * 1e-9f);
  }

  float Reset() {
    auto ts = Elapsed();
    m_last = Clock::now();
    return ts;
  }

 private:
  Clock::time_point m_begin;
  Clock::time_point m_last;
};
}  // namespace ap