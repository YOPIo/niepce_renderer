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
*/
#include "../../cmake_config.h"
/*
// ---------------------------------------------------------------------------
*/
#ifdef _WIN32
   #define NOMINMAX
   #ifdef _WIN64
      #define NIEPCE_BUILD_TARGET_IS_WIN64
   #else
      #define NIEPCE_BUILD_TARGET_IS_WIN32
   #endif

#elif __APPLE__
   #define NIEPCE_BUILD_TARGET_IS_APPLE

#elif __linux__
   #define NIEPCE_BUILD_TARGET_IS_LINUX

#elif __unix__
   #define NIEPCE_BUILD_TARGET_IS_UNIX

#else
   #error "Unknown compiler"
#endif
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
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
/*
// ---------------------------------------------------------------------------
// Alignment definition
// ---------------------------------------------------------------------------
*/
#if defined (NIEPCE_BUILD_TARGET_IS_WINDOWS)
   #define NIEPCE_ALIGN(bit) __declspec(align(bit))
#else
   #define NIEPCE_ALIGN(bit) alignas((bit))
#endif // NIEPCE_BUILD_TARGET_IS_WINDOWS

#define ALIGN16  NIEPCE_ALIGN(16)
#define ALIGN32  NIEPCE_ALIGN(32)
#define ALIGN64  NIEPCE_ALIGN(64)
#define ALIGN128 NIEPCE_ALIGN(128)
/*
// ---------------------------------------------------------------------------
// Niepce renderer SIMD include
// ---------------------------------------------------------------------------
*/
#ifdef NIEPCE_USE_SIMD
   #include <xmmintrin.h>
   #include <smmintrin.h>
#endif // NIEPCE_USE_SIMD
/*
// ---------------------------------------------------------------------------
*/

/*
// ---------------------------------------------------------------------------
*/
#include "../ext/easyloggingpp/easylogging++.h"
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
class AreaLight;
class Attributes;
class AssembledTiles;
class BeckmannDistribution;
class Bounds2f;
class Bxdf;
class Bsdfs;
class Bsdf;
class BsdfRecord;
enum class BsdfType;
class Camera;
struct CameraSample;
class Film;
class FilmTile;
template <typename T> class Image;
template <typename T> class ImageIO;
class InfiniteLight;
class Intersection;
class Lambert;
class Light;
class Material;
class MaterialAttributes;
class MemoryArena;
class Shape;
class Sphere;
template <typename T> class Texture;
class ThreadPool;
class Tile;
class Transform;
class PathTracer;
class PinholeCamera;
class Pixel;
class Point2f;
class Point3f;
class Primitive;
class RamdomSampler;
class Ray;
class RealisticCamera;
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
// ---------------------------------------------------------------------------
// DO NOT CHANGE FLOAT TO DOUBLE !!
// ---------------------------------------------------------------------------
typedef float Float;
/*
// ---------------------------------------------------------------------------
*/
typedef Vector3f Spectrum;
/*
// ---------------------------------------------------------------------------
// Niepce renderer constant values
// ---------------------------------------------------------------------------
*/
static constexpr Float kPi = 3.141592653589793238462643383279502884197169399375;
static constexpr Float kInfinity = std::numeric_limits <Float>::infinity ();
static constexpr Float kEpsilon  = std::numeric_limits <Float>::epsilon ();
static constexpr Float kFloatMax = std::numeric_limits <Float>::max ();
static constexpr Float kFloatMin = std::numeric_limits <Float>::lowest ();
static constexpr Float kOne      = 1.0;
static constexpr Float kZero     = 0.0;
/*
// ---------------------------------------------------------------------------
// Niepce renderer global function
// ---------------------------------------------------------------------------
*/
inline auto GetFileDirectory
(
 const std::string& filename,
       std::string* directory
)
  -> void
{
#ifdef _WIN32
  const char split = '\\';
#else
  const char split = '/';
#endif
  const size_t pos = filename.rfind (split);
  if (std::string::npos != pos)
  {
    *directory = filename.substr(0, pos + 1);
  }
}
/*
// ---------------------------------------------------------------------------
*/
inline auto IsFileExist (const std::string& filename) -> bool
{
  const std::ifstream ifs (filename, std::ios::in);
  return static_cast <bool> (ifs);
}
/*
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
inline auto FileExtension (const std::string &filepath) -> std::string
{
  const char *ext = std::strrchr (filepath.c_str (), '.');
  return std::string (ext);
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
inline auto DegreeToRadian (Float degree) -> Float
{
  return degree / 180.0 * kPi;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Uint8ToFloat (uint8_t val) -> Float
{
  return Clamp (static_cast <Float> (val) / 256.0f, 0.0f, 1.0f);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _NIEPCE_H_

