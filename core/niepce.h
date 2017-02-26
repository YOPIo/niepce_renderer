#ifndef _NIEPCE_H_
#define _NIEPCE_H_

// Global include std libraries
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "debug.h"
#include "constants.h"

// Data quality
typedef float Float;

namespace niepce
{

// Global class declarations
template <typename T> class Vector2;
template <typename T> class Vector3;
template <typename T> class Vector4;
template <typename T> class Point2;
template <typename T> class Point3;
template <typename T> class Point4;
template <typename T> class Normal3;
template <typename T> class Matrix4x4;
template <typename T> class BoundingBox2;
template <typename T> class BoundingBox3;

/*
  Global typedef
*/
typedef Vector2<int>     Vector2i;
typedef Vector2<Float>   Vector2f;
typedef Vector3<int>     Vector3i;
typedef Vector3<Float>   Vector3f;
typedef Vector4<int>     Vector4i;
typedef Vector4<Float>   Vector4f;
typedef Point2<int>      Point2i;
typedef Point2<Float>    Point2f;
typedef Point3<int>      Point3i;
typedef Point3<Float>    Point3f;
typedef Point4<int>      Point4i;
typedef Point4<Float>    Point4f;
typedef Matrix4x4<int>   Matrix4x4i;
typedef Matrix4x4<Float> Matrix4x4f;
/*
  Global constant expression
*/
constexpr Float kInfinity = std::numeric_limits<Float>::infinity();
constexpr Float kFloatMax = std::numeric_limits<Float>::max();
constexpr Float kEpsilon  = std::numeric_limits<Float>::epsilon() * 0.5;
constexpr Float kPi       = 3.14159265358979323846;

/*
  Global inline functions
*/
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

inline auto Radians(Float degree) -> Float
{
  return (kPi / 180.f) * degree;
}

inline auto Degrees(Float radian) -> Float
{
  return (180.f / kPi) * radian;
}

}; // namespace niepce

#endif // _NIEPCE_H_
