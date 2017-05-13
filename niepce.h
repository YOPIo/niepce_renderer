#ifndef _NIEPCE_H_
#define _NIEPCE_H_

#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Render settings
// ---------------------------------------------------------------------------
// Data
typedef float Float;
// Maximum depth
static const Float kMaxDepth = 10;
// Image size
static const int kWidth  = 640;
static const int kHeight = 480;
// Samples per pixel
static const int kSamples = 32;


// ---------------------------------------------------------------------------
// Global constant values
// ---------------------------------------------------------------------------
static constexpr Float    kPi        = 3.14159265358979323846;
static constexpr Float    kInfinity  = std::numeric_limits<Float>::infinity();
static constexpr Float    kEpsilon   = std::numeric_limits<Float>::epsilon();
static constexpr Float    kFloatMax  = std::numeric_limits<Float>::max();
static constexpr uint32_t kUInt32Max = std::numeric_limits<uint32_t>::max();


// ---------------------------------------------------------------------------
// class forward declaration
// ---------------------------------------------------------------------------
class Vector3f;
class Ray;
class Camera;
class Material;
class Sphere;

typedef Vector3f Rgb;

#endif // _NIEPCE_H_
