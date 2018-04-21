#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_
/*
// ---------------------------------------------------------------------------
*/
#include <cmath>
#include <array>
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Data precision
// ---------------------------------------------------------------------------
*/
typedef float Float;
/*
// ---------------------------------------------------------------------------
// Struct and Class forward declaration
// ---------------------------------------------------------------------------
*/
// todo: SIMD化
struct Vector2f;
struct Vector3f;
// 早く実装する
// struct Point2f;  // No implementation, use Vector2f instead
// struct Point3f;  // No implementation, use Vector3f instead
// struct Normal3f; // No implementation, use Vector3f instead
typedef Vector2f Point2f;
typedef Vector3f Ponit3f;
typedef Vector3f Normal3f;
struct Matrix4x4f;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _ALGEBRA_H_
