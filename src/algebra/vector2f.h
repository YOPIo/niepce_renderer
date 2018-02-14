#ifndef _VECTOR2F_H_
#define _VECTOR2F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "algebra.h"
/*
// ---------------------------------------------------------------------------
// TODO: Support SIMD
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct ALIGN16 Vector2f final
{
  Vector2f ();
  Vector2f (Float x, Float y);
  explicit Vector2f (Float s);


  virtual ~Vector2f () = default;

  Vector2f (const Vector2f&  p) = default;
  Vector2f (      Vector2f&& p) = default;


  /* Operators */
  auto operator = (const Vector2f&  p) -> Vector2f& = default;
  auto operator = (      Vector2f&& p) -> Vector2f& = default;

  auto operator [] (Index idx) const -> Float;
  auto operator [] (Index idx)       -> Float&;


  /* Methods */
  auto At (Index idx) const -> Float;
  auto At (Index idx)       -> Float&;

  auto Normalize  ()       -> Vector2f&;
  auto Normalized () const -> Vector2f;

  auto Length        () const -> Float;
  auto LengthSquared () const -> Float;

  // Check status
  auto HasNaN       () const -> bool;
  auto IsNormalized () const -> bool;

  auto ToString () const -> std::string;


  /* Constant values */
  static constexpr auto Max      () -> Vector2f;
  static constexpr auto Min      () -> Vector2f;
  static constexpr auto Infinity () -> Vector2f;
  static constexpr auto Lowest   () -> Vector2f;
  static constexpr auto One      () -> Vector2f;
  static constexpr auto Zero     () -> Vector2f;


  /* Vector2f public data */
  union
  {
    std::array <Float, 2> xy;
    std::array <Float, 2> uv;
    std::array <Float, 2> st;
    struct { Float x, y; };
    struct { Float u, v; };
    struct { Float s, t; };
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
#include "vector2f.inl"
/*
// ---------------------------------------------------------------------------
*/
#endif // _VECTOR2F_H_
