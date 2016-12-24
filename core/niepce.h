#ifndef _NIEPCE_H_
#define _NIEPCE_H_

// Global include std libraries
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

// Depending includes
#include <glog/logging.h>

// Data quality
typedef float Float;

// Global Constrants
static constexpr Float kInfinity = std::numeric_limits<Float>::infinity();
static constexpr Float kFloatMax = std::numeric_limits<Float>::max();
static constexpr Float kEpsilon  = std::numeric_limits<Float>::epsilon() * 0.5;
static constexpr Float kPi       = 3.14159265358979323846;

namespace niepce
{

// Global inline functions
inline auto Clamp(Float value, Float min = 0.f, Float max = kInfinity) -> Float
{
  if (value < min)
  {
      return min;
  }
  if (value > max)
  {
      return max;
  }
  return value;
}

inline auto Lerp(Float t, Float s1, Float s2) -> Float
{
    return (1.0 - t) * s1 + t * s2;
}

}; // namespace niepce

#endif // _NIEPCE_H_
