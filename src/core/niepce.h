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
class Image;
class IOImage;
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
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _NIEPCE_H_

