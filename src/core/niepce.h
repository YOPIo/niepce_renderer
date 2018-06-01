/*!
 * @file niepce.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/20
 * @details 
 */
#ifndef _NIEPCE_H_
#define _NIEPCE_H_
/*
// ---------------------------------------------------------------------------
// Niepce renderer std includes
// ---------------------------------------------------------------------------
*/
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <future>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string>
#include <thread>
#include <type_traits>
/*!
 * @namespace niepce
 */
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Forward class, struct and enum declaration
// ---------------------------------------------------------------------------
*/
class AssembledTiles;
class BeckmannDistribution;
class Bounds2f;
class Bsdf;
class Film;
class FilmTile;
template <typename T> class Image;
template <typename T> class ImageIO;
class Intersection;
class Lambert;
class Material;
class MemoryArena;
class Shape;
class Sphere;
class Tile;
class ThreadPool;
class PathTracer;
class Pixel;
class Point2f;
class Point3f;
class Primitive;
class RamdomSampler;
class Ray;
class Renderer;
class RenderSettings;
class Vector2f;
class Vector3f;
/*
// ---------------------------------------------------------------------------
// Niepce renderer typedefs
// ---------------------------------------------------------------------------
*/
/*!
 * @typedef
 * @brief Choose float or double
 */
typedef double Float;
typedef Vector3f Spectrum;
/*
// ---------------------------------------------------------------------------
// Niepce renderer constant values
// ---------------------------------------------------------------------------
*/
constexpr Float kPi       = 3.141592653589793238462643383279502884197169399375105820974;
constexpr Float kInfinity = std::numeric_limits <Float>::infinity ();
constexpr Float kEpsilon  = std::numeric_limits <Float>::epsilon ();
constexpr Float kFloatMax = std::numeric_limits <Float>::max ();
constexpr Float kFloatMin = std::numeric_limits <Float>::lowest ();
/*
// ---------------------------------------------------------------------------
// Niepce renderer global function
// ---------------------------------------------------------------------------
*/
inline auto Clamp (Float x) -> Float
{
  if (x < 0) { return 0.0; }
  if (x > 1) { return 1.0; }
  return x;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
inline auto Clamp (T x, T min, T max) -> T
{
  if (x < min) { return min; }
  if (x > max) { return max; }
  return x;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Lerp (Float t, Float v1, Float v2) -> Float
{
  return (1 - t) * v1 + t * v2;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto ReverseBits32 (uint32_t n) -> uint32_t
{
  n = (n << 16) | (n >> 16);
  n = ((n & 0x00ff00ff) << 8) | ((n & 0xff00ff00) >> 8);
  n = ((n & 0x0f0f0f0f) << 4) | ((n & 0xf0f0f0f0) >> 4);
  n = ((n & 0x33333333) << 2) | ((n & 0xcccccccc) >> 2);
  n = ((n & 0x55555555) << 1) | ((n & 0xaaaaaaaa) >> 1);
  return n;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto ReverseBits64 (uint64_t n) -> uint64_t
{
  uint64_t n1 = ReverseBits32 (static_cast <uint32_t> (n));
  uint64_t n2 = ReverseBits32 (static_cast <uint32_t> (n >> 32));
  return (n1 << 32) | n2;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto FloatToInt (Float x) -> uint8_t
{
  uint8_t res = static_cast <uint8_t> (x * 255 - 1.0 + 0.5);
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto ToDegree (Float radian) -> Float
{
  return radian * 180.0 / kPi;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _NIEPCE_H_

