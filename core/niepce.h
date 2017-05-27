#ifndef _NIEPCE_H_
#define _NIEPCE_H_


// ---------------------------------------------------------------------------
// STL includes
// ---------------------------------------------------------------------------
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>


// ---------------------------------------------------------------------------
// Dependent libraries
// ---------------------------------------------------------------------------
#include <spdlog/async_logger.h>
#include <spdlog/common.h>
#include <spdlog/formatter.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>
#include <spdlog/tweakme.h>

namespace niepce
{

// ---------------------------------------------------------------------------
// Data quality settings
// ---------------------------------------------------------------------------
typedef float Float;

// ---------------------------------------------------------------------------
// Debug
// ---------------------------------------------------------------------------
static auto console = spdlog::stdout_color_mt("console");

// ---------------------------------------------------------------------------
// Render settings
// ---------------------------------------------------------------------------
// Maximum depth
static const int kMaxTrace = 10;
// Samples per pixel
static const int kSamples = 32;
// Image size
static const int kWidth  = 640;
static const int kHeight = 480;

// ---------------------------------------------------------------------------
// Global constant expression
// ---------------------------------------------------------------------------
constexpr Float kInfinity = std::numeric_limits<Float>::infinity();
constexpr Float kFloatMax = std::numeric_limits<Float>::max();
constexpr Float kEpsilon  = std::numeric_limits<Float>::epsilon();
constexpr Float kPi       = 3.14159265358979323846;


// ---------------------------------------------------------------------------
// Global class declarations
// ---------------------------------------------------------------------------

// Defined in /geometries
template <typename T> class BoundingBox2;
template <typename T> class BoundingBox3;
template <typename T> class Matrix4x4;
template <typename T> class Normal3;
template <typename T> class Point2;
template <typename T> class Point3;
template <typename T> class Point4;
template <typename T> class Vector2;
template <typename T> class Vector3;
template <typename T> class Vector4;

typedef Vector2<int>        Vector2i;
typedef Vector2<Float>      Vector2f;
typedef Vector3<int>        Vector3i;
typedef Vector3<Float>      Vector3f;
typedef Vector4<int>        Vector4i;
typedef Vector4<Float>      Vector4f;
typedef Point2<int>         Point2i;
typedef Point2<Float>       Point2f;
typedef Point3<int>         Point3i;
typedef Point3<Float>       Point3f;
typedef Point4<int>         Point4i;
typedef Point4<Float>       Point4f;
typedef Normal3<int>        Normal3i;
typedef Normal3<Float>      Normal3f;
typedef Matrix4x4<int>      Matrix4x4i;
typedef Matrix4x4<Float>    Matrix4x4f;
typedef BoundingBox2<int>   Bounds2i;
typedef BoundingBox2<Float> Bounds2f;
typedef BoundingBox3<int>   Bounds3i;
typedef BoundingBox3<Float> Bounds3f;


// ---------------------------------------------------------------------------
// Global inline functions
// ---------------------------------------------------------------------------
inline auto Clamp(Float value, Float min = 0.f, Float max = kInfinity) -> Float
{
  if (value < min) { return min; }
  if (value > max) { return max; }
  return value;
}

inline auto Lerp(Float t, Float s1, Float s2) -> Float
{
    return (1.0 - t) * s1 + t * s2;
}

template <typename T>
inline auto IsNaN(const T val) -> bool
{
  return std::isnan(val);
}

template<>
inline auto IsNaN(const int val) -> bool
{
  return false;
}

// Convert to radians from degree
inline auto ToRadians(Float degree) -> Float
{
  return (kPi / 180.f) * degree;
}

// Convert to degrees from radian
inline auto ToDegrees(Float radian) -> Float
{
  return (180.f / kPi) * radian;
}

// ---------------------------------------------------------------------------
// Solve quadratic equation $at^2 + bt + c = 0$
// Return boolean value whether solution were found or not.
// ---------------------------------------------------------------------------
inline auto SolveQuadratic(Float a, Float b, Float c, Float* t0, Float* t1) -> bool
{
  const Float discrim = b * b - 4 * a * c;
  if (discrim < 0.f) { return false;  }
  const Float sqrt_discrim = std::sqrt(discrim);

  Float q;
  if (b < 0.f) { q = -0.5f * (b - sqrt_discrim); }
  else         { q = -0.5f * (b + sqrt_discrim); }
  *t0 = q / a;
  *t1 = c / q;
  if (*t0 > *t1) { std::swap(*t0, *t1); }

  return true;
}

inline auto FloatToBits(float f) -> uint32_t
{
  uint32_t ui;
  std::memcpy(&ui, &f, sizeof(float));
  return ui;
}

inline auto BitsToFloat(uint32_t ui) -> float
{
  float f;
  std::memcpy(&f, &ui, sizeof(ui));
  return f;
}

inline auto FloatToBis(double d) -> uint64_t
{
  uint64_t ui;
  std::memcpy(&ui, &d, sizeof(double));
  return ui;
}

inline auto BitsToFloat(uint64_t ui) -> double
{
  double d;
  std::memcpy(&d, &ui, sizeof(ui));
  return d;
}

inline auto NextFloatUp(float v) -> float
{
  // Handle infinity and negative zero.
  if ( std::isinf(v) && v > 0.f ) { return v; }
  if (v == -0.f) { return v = 0.f;  }

  uint32_t ui = FloatToBits(v);
  if (v >= 0) { ++ui; }
  else        { --ui; }

  return BitsToFloat(ui);
}

inline auto NextFloatDown(float v) -> float
{
  // Handle infinity and posiive zero.
  if ( std::isinf(v) && v < 0.f ) { return v; }
  if (v == 0.f) { v = -0.f; }

  uint32_t ui = FloatToBits(v);
  if (v > 0.f) { --ui; }
  else         { ++ui; }

  return BitsToFloat(ui);
}

inline auto NextFloatUp(double v, int delta = 1) -> double
{
  // Handle infinity and negative zero.
  if ( std::isinf(v) && v > 0.f ) { return v; }
  if (v == -0.f) { return v = 0.f;  }

  uint64_t ui = FloatToBits(v);
  if (v >= 0) { ui += delta; }
  else        { ui -= delta; }

  return BitsToFloat(ui);
}

inline auto NextFloatDown(double v, int delta = 1) -> double
{
  // Handle infinity and posiive zero.
  if ( std::isinf(v) && v < 0.f ) { return v; }
  if (v == 0.f) { v = -0.f; }

  uint64_t ui = FloatToBits(v);
  if (v > 0.f) { ui -= delta; }
  else         { ui += delta; }

  return BitsToFloat(ui);
}

inline constexpr auto Gamma(int n ) -> Float
{
  return (n * kEpsilon) / (1 - n * kEpsilon);
}

}; // namespace niepce

#endif // _NIEPCE_H_
