#ifndef _VECTOR2F_H_
#define _VECTOR2F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class ALIGN16 Vector2f final
{
public:
  /* Constructors */
  Vector2f ();
  Vector2f (Float x, Float y);
  explicit Vector2f (Float s);
#ifdef NIEPCE_USE_SIMD
  Vector2f (const __m128& v);
#endif // NIEPCE_USE_SIMD

  ~Vector2f () = default;

  Vector2f (const Vector2f&  p) = default;
  Vector2f (      Vector2f&& p) = default;


  /* Operators */
  auto operator = (const Vector2f&  p) -> Vector2f& = default;
  auto operator = (      Vector2f&& p) -> Vector2f& = default;

  auto operator [] (unsigned idx) const noexcept -> Float;

 public:
  auto X () const noexcept -> Float;
  auto Y () const noexcept -> Float;
#ifdef NIEPCE_USE_SIMD
  auto Xy () const noexcept -> __m128;
#endif // NIEPCE_USE_SIMD

  auto SetX (Float x) -> void;
  auto SetY (Float y) -> void;

  auto At (unsigned idx) const -> Float;

  auto Length        () const -> Float;
  auto LengthSquared () const -> Float;

  auto Normalize () noexcept -> Vector2f;
  auto HasNaN    () const -> bool;
  auto ToString  () const -> std::string;

  /* Constant values */
  static constexpr auto Max      () -> Vector2f;
  static constexpr auto Min      () -> Vector2f;
  static constexpr auto Infinity () -> Vector2f;
  static constexpr auto Lowest   () -> Vector2f;
  static constexpr auto One      () -> Vector2f;
  static constexpr auto Zero     () -> Vector2f;

  /* Vector2f private data */
private:
  union
  {
    struct { Float x_, y_, z_, w_; };
#ifdef NIEPCE_USE_SIMD
    __m128 xyzw_;
#endif // NIEPCE_USE_SIMD
  };
}; // struct Vector2f
/*
// ---------------------------------------------------------------------------
// Vector2f global operators
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector2f& lhs, const Vector2f& rhs) -> bool;
auto operator != (const Vector2f& lhs, const Vector2f& rhs) -> bool;

auto operator -  (const Vector2f& v) -> Vector2f;

auto operator +  (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f;
auto operator -  (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f;
auto operator *  (const Vector2f& v, Float t) -> Vector2f;
auto operator *  (Float t, const Vector2f& v) -> Vector2f;
auto operator /  (const Vector2f& v, Float t) -> Vector2f;
/*
// ---------------------------------------------------------------------------
// Vector2f global functions
// ---------------------------------------------------------------------------
*/
auto Dot      (const Vector2f& lhs, const Vector2f& rhs) -> Float;
// auto Cross    (const Vector2f& lhs, const Vector2f& rhs) -> Float;
auto Multiply (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _VECTOR2F_H_
