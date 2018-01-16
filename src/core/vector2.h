#ifndef _VECTOR2_H_
#define _VECTOR2_H_
/*
// ---------------------------------------------------------------------------
*/
#include "algebra.h"
/*
// ---------------------------------------------------------------------------
// template で生成するのは double, float, int32_t, uint32_t のみ
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class ALIGN (SIMD_ALIGN) Vector2 final
{
public:
  Vector2 (Float x = 0, Float y = 0);
  explicit Vector2 (Float s);


public:
  virtual ~Vector2 () = default;

public:
  Vector2 (const Vector2&  p) = default;
  Vector2 (      Vector2&& p) = default;


  /* Operators */
public:
  auto operator = (const Vector2&  p) -> Vector2& = default;
  auto operator = (      Vector2&& p) -> Vector2& = default;

  auto operator [] (Index idx) const -> Float;
  auto operator [] (Index idx)       -> Float&;


  /* Methods */
public:
  auto At (Index idx) const -> Float;
  auto At (Index idx)       -> Float&;

  auto Normalize  ()       -> Vector2&;
  auto Normalized () const -> Vector2;

  auto Length        () const -> Float;
  auto LengthSquared () const -> Float;

  // Check status
  auto HasNaN       () const -> bool;
  auto IsNormalized () const -> bool;

  auto ToString () const -> std::string;


  /* Static methods */
public:
  static auto Length        (const Vector2& v) -> Float;
  static auto LengthSquared (const Vector2& v) -> Float;
  static auto Dot   (const Vector2& rv, const Vector2& lv) -> Float;
  static auto Cross (const Vector2& rv, const Vector2& lv) -> Float;


  /* Constant values */
 public:
  static constexpr auto Max      () -> Vector2;
  static constexpr auto Min      () -> Vector2;
  static constexpr auto Infinity () -> Vector2;
  static constexpr auto Lowest   () -> Vector2;
  static constexpr auto One      () -> Vector2;
  static constexpr auto Zero     () -> Vector2;


  /* Data */
public:
#ifdef NI_USE_SIMD_IMPLEMENTATION
  union
  {
#ifdef NI_FLOAT_IS_DOUBLE
    __m256d xy256;
#else
    __m128 xy128;
#endif // NI_FLOAT_IS_DOUBLE
    struct { Float x, y, z, w; };
    struct { Float u, v, s, t; };
    struct { Float s, t, u, v; };
    std::array <Float, 4> xy;
  };
#else
  union
  {
    struct { Float x, y; };
    struct { Float u, v; };
    struct { Float s, t; };
    std::array <Float, 2> xy;
  };
#endif // NI_USE_SIMD_IMPLEMENTATION
}; // class Vector2
/*
// ---------------------------------------------------------------------------
// Vector2 global operators
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector2& lp, const Vector2& rp) -> bool;
auto operator != (const Vector2& lp, const Vector2& rp) -> bool;
auto operator -  (const Vector2& rv) -> Vector2;
auto operator +  (const Vector2& lp, const Vector2& rp) -> Vector2;
auto operator -  (const Vector2& lp, const Vector2& rp) -> Vector2;
auto operator *  (const Vector2& p, Float s) -> Vector2;
auto operator *  (Float s, const Vector2& p) -> Vector2;
auto operator /  (const Vector2& p, Float s) -> Vector2;
auto operator += (Vector2& lv, const Vector2& rv) -> Vector2&;
auto operator -= (Vector2& lv, const Vector2& rv) -> Vector2&;
auto operator *= (Vector2& lv, Float rv) -> Vector2&;
auto operator /= (Vector2& lv, Float rv) -> Vector2&;
/*
// ---------------------------------------------------------------------------
// Vector2 global functions
// ---------------------------------------------------------------------------
*/
auto Dot   (const Vector2& lv, const Vector2& rv) -> Float;
auto Cross (const Vector2& lv, const Vector2& rv) -> Float;
auto Mul   (const Vector2& lv, const Vector2& rv) -> Vector2;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _VECTOR2_H_
