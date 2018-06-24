/*!
 * @file point3f.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/1
 * @details 
 */
#ifndef _POINT3F_H_
#define _POINT3F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Point3f
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class ALIGN16 Point3f final
{
public:
  /* Constructor */
  Point3f ();
  Point3f (Float x, Float y, Float z);
  explicit Point3f (Float t);
#ifdef NIEPCE_USE_SIMD
  Point3f (const __m128& p);
#endif // NIEPCE_USE_SIMD

  ~Point3f () = default;

  Point3f (const Point3f&  p) = default;
  Point3f (      Point3f&& p) = default;

  /* Operators */
  auto operator = (const Point3f&  p) -> Point3f& = default;
  auto operator = (      Point3f&& p) -> Point3f& = default;
  auto operator [] (unsigned int idx) const noexcept -> Float;

public:
  auto At (unsigned int idx) const -> Float;

  auto X () const noexcept -> Float;
  auto Y () const noexcept -> Float;
  auto Z () const noexcept -> Float;
#ifdef NIEPCE_USE_SIMD
  auto Xyz () const noexcept -> __m128;
#endif // NIEPCE_USE_SIMD

  auto SetX (Float x) noexcept -> void;
  auto SetY (Float y) noexcept -> void;
  auto SetZ (Float z) noexcept -> void;

  auto ToString () const noexcept -> std::string;

public:
  static auto Max      () noexcept -> Point3f;
  static auto Min      () noexcept -> Point3f;
  static auto Infinity () noexcept -> Point3f;
  static auto Lowest   () noexcept -> Point3f;
  static auto One      () noexcept -> Point3f;
  static auto Zero     () noexcept -> Point3f;

private:
  union
  {
    struct { Float x_, y_, z_, w_; };
#ifdef NIEPCE_USE_SIMD
    __m128 xyzw_;
#endif // NIEPCE_USE_SIMD
  };
}; // class Point3f
/*
// ---------------------------------------------------------------------------
// Global operator for Point3f.
// ---------------------------------------------------------------------------
*/
auto operator - (const Point3f& rhs, const Point3f& lhs) -> Vector3f;
auto operator * (const Point3f& p, Float s) -> Point3f;
auto operator * (Float s, const Point3f& p) -> Point3f;
auto operator + (const Point3f& lhs, const Point3f& rhs) -> Point3f;
auto operator + (const Point3f& lhs, const Vector3f& rhs) -> Point3f;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _POINT3F_H_
