#pragma once
#include "Core.h"

namespace ap
{
constexpr inline APHELION_API unsigned Bit(unsigned bit)
{
    return 1 << bit;
}

/**
 * A wrapper for a container to reverse iterate over is using a range based for
 * loop
 * Usage:
 *   for (const auto& item: Reverse(items))
 *
 * NOTE: Doesn't seem to work for Emscripten...
 */
template <typename T> class Reverse
{
  public:
    explicit Reverse(T& iterable) : iterable{iterable}
    {
    }
    auto begin() const
    {
        return std::rbegin(iterable);
    }
    auto end() const
    {
        return std::rend(iterable);
    }

  private:
    T& iterable;
};
} // namespace ap
