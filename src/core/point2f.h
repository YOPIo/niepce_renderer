/*!
 * @file point2.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/29
 * @details 
 */
#ifndef _POINT2_H_
#define _POINT2_H_
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
//! @class Point2f
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class ALIGN16 Point2f final
{
public:
  /* Constructors */
  Point2f ();
  Point2f (Float x, Float y);
  explicit Point2f (Float t);
#ifdef NI_USE_SIMD
  Point2f (const __m128& p);
#endif // NI_USE_SIDM

  Point2f (const Point2f&  p) = default;
  Point2f (      Point2f&& p) = default;

  virtual ~Point2f () = default;

  /* Operators */
  auto operator = (const Point2f&  p) -> Point2f& = default;
  auto operator = (      Point2f&& p) -> Point2f& = default;
  auto operator [] (unsigned int idx) const noexcept -> Float;

public:
  auto At (unsigned int idx) const -> Float;
  auto X () const noexcept -> Float;
  auto Y () const noexcept -> Float;
#ifdef NI_USE_SIMD
  auto Xy () const noexcept -> __m128;
#endif // NI_USE_SIMD

  auto SetX (Float x) noexcept -> void;
  auto SetY (Float y) noexcept -> void;

  auto ToString () const noexcept -> std::string;

private:
  union
  {
    struct { Float x_, y_, z_, w_; };
#ifdef NI_USE_SIMD
    __m128 xyzw_;
#endif // NI_USE_SIMD
  };

}; // class Point2f
/*
// ---------------------------------------------------------------------------
// Function for the Point2f
// ---------------------------------------------------------------------------
*/
auto operator == (const Point2f& lhs, const Point2f& rhs) -> bool;
auto operator != (const Point2f& lhs, const Point2f& rhs) -> bool;

auto operator + (const Point2f& lhs, const Point2f& rhs) -> Point2f;
auto operator - (const Point2f& lhs, const Point2f& rhs) -> Vector2f;

auto operator * (const Point2f& p, Float t) -> Point2f;
auto operator * (Float t, const Point2f& p) -> Point2f;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _POINT2_H_
