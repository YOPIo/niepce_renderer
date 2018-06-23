#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_
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
class ALIGN16 Vector3f final
{
public:
  /* Constructors */
  Vector3f ();
  Vector3f (Float x, Float y , Float z);
  explicit Vector3f (Float s);
#ifdef NI_USE_SIMD
  explicit Vector3f (const __m128& v);
#endif // NI_USE_SIMD

  ~Vector3f () = default;

  Vector3f (const Vector3f&  v) = default;
  Vector3f (      Vector3f&& v) = default;

  /* Operators */
  auto operator = (const Vector3f&  v) -> Vector3f& = default;
  auto operator = (      Vector3f&& v) -> Vector3f& = default;
  auto operator [] (unsigned idx) const noexcept -> Float;

 public:
  auto At (unsigned idx) const -> Float;

  auto X () const noexcept -> Float;
  auto Y () const noexcept -> Float;
  auto Z () const noexcept -> Float;
#ifdef NI_USE_SIMD
  auto Xyz () const noexcept -> __m128;
#endif // NI_USE_SIMD

  auto SetX (Float x) noexcept -> void;
  auto SetY (Float y) noexcept -> void;
  auto SetZ (Float z) noexcept -> void;

  auto Normalize () noexcept -> Vector3f;

  auto Length ()        const -> Float;
  auto LengthSquared () const -> Float;

  auto HasNaN       () const -> bool;

  auto ToString () const -> std::string;

 public:
  static auto Max      () noexcept -> Vector3f;
  static auto Min      () noexcept -> Vector3f;
  static auto Infinity () noexcept -> Vector3f;
  static auto Lowest   () noexcept -> Vector3f;
  static auto One      () noexcept -> Vector3f;
  static auto Zero     () noexcept -> Vector3f;

 private:
  union
  {
    struct { Float x_, y_, z_, w_; };
#ifdef NI_USE_SIMD
    __m128 xyzw_;
#endif
  };
}; // class Vector3f
/*
// ---------------------------------------------------------------------------
// Global operators for Vector3f
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector3f& lhs, const Vector3f& rhs) -> bool;
auto operator != (const Vector3f& lhs, const Vector3f& rhs) -> bool;
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Vector3f& v) -> Vector3f;
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto operator - (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto operator * (Float t, const Vector3f& v) -> Vector3f;
auto operator * (const Vector3f& v, Float t) -> Vector3f;
auto operator / (const Vector3f& v, Float t) -> Vector3f;
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto operator / (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
/*
// ---------------------------------------------------------------------------
// Global functions for Vector3f
// ---------------------------------------------------------------------------
*/
auto Dot       (const Vector3f& lhs, const Vector3f& rhs) -> Float;
auto Cross     (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto Multiply  (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto Normalize (const Vector3f& vec) -> Vector3f;
auto BuildOrthonormalBasis
(
 const Vector3f& normal,
 Vector3f* binormal,
 Vector3f* tangent
)
  -> void;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _VECTOR3F_H_
