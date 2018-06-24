#include "vector2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------
*/
Vector2f::Vector2f () :
#ifdef NIEPCE_USE_SIMD
  xyzw_ (_mm_setzero_ps ())
#else
  x_ (0), y_ (0), z_ (0), w_ (0)
#endif // NIEPCE_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
Vector2f::Vector2f (Float x, Float y) :
#ifdef NIEPCE_USE_SIMD
  xyzw_ (_mm_set_ps (0, 0, y, x))
#else
  x_ (x), y_ (y), z_ (0), w_ (0)
#endif // NIEPCE_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
Vector2f::Vector2f (Float s) :
#ifdef NIEPCE_USE_SIMD
  xyzw_ (_mm_set_ps (0, 0, s, s))
#else
  x_ (s), y_ (s), z_ (0), w_ (0)
#endif // NIEPCE_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
#ifdef NIEPCE_USE_SIMD
Vector2f::Vector2f (const __m128& v) :
  xyzw_ (v)
{}
#endif // NIEPCE_USE_SIMD
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::operator [] (unsigned int idx) const noexcept -> Float
{
  return ((idx == 0) ? x_ : y_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::At (unsigned int idx) const -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  throw std::out_of_range ("Out of range in Vector2f.");
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::X () const noexcept -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::Y () const noexcept -> Float
{
  return y_;
}
/*
// ---------------------------------------------------------------------------
*/
#ifdef NIEPCE_USE_SIMD
auto Vector2f::Xy () const noexcept -> __m128
{
  return xyzw_;
}
#endif // NIEPCE_USE_SIMD
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::SetX (Float x) -> void
{
  x_ = x;
}
/*
// ---------------------------------------------------------------------------
*/

auto Vector2f::SetY (Float y) -> void
{
  y_ = y;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::Normalize () noexcept -> Vector2f
{
#ifdef NIEPCE_USE_SIMD
  xyzw_ = _mm_div_ps (xyzw_, _mm_sqrt_ps (_mm_dp_ps (xyzw_, xyzw_, 0xFF)));
  return *this;
#else
  const Float inv_len = 1.0 / Length ();
  x_ *= inv_len;
  y_ *= inv_len;
  z_ = 0;
  w_ = 0;
  return *this;
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::Length () const -> Float
{
#ifdef NIEPCE_USE_SIMD
  return _mm_cvtss_f32 (_mm_sqrt_ss (_mm_dp_ps (xyzw_, xyzw_, 0x71)));
#else
  return std::sqrt (LengthSquared ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::LengthSquared () const -> Float
{
#ifdef NIEPCE_USE_SIMD
  return _mm_cvtss_f32 (_mm_dp_ps (xyzw_, xyzw_, 0x71));
#else
  return x_ * x_ + y_ * y_;
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::HasNaN () const -> bool
{
#ifdef NIEPCE_USE_SIMD
  const __m128 mask = _mm_cmpeq_ps (xyzw_, xyzw_);
  return (_mm_movemask_ps (mask) & 0x0F) != 0x0F;
#else
  return static_cast <bool> (std::isnan (x_) ||
                             std::isnan (y_));
#endif
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::ToString () const -> std::string
{
  return std::string ("["  + std::to_string (x_) +
                      ", " + std::to_string (y_) + "]");
}
/*
// ---------------------------------------------------------------------------
// Global operators for Vector2f
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector2f& lhs, const Vector2f& rhs) -> bool
{
#ifdef NIEPCE_USE_SIMD
  const auto mask = _mm_movemask_ps (_mm_cmpeq_ps (lhs.Xy (), rhs.Xy ()));
  return ((mask & 0x07) == 0x07);
#else
  if (lhs.X () == rhs.X () && lhs.Y () == rhs.Y ())
  {
    return true;
  }
  return false;
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator != (const Vector2f& lhs, const Vector2f& rhs) -> bool
{
  return !(lhs == rhs);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Vector2f& v) -> Vector2f
{
#ifdef NIEPCE_USE_SIMD
  const auto mask = _mm_castsi128_ps (_mm_set1_epi32 (0x80000000));
  return Vector2f (_mm_xor_ps (v.Xy (), mask));
#else

#endif // NIEPCE_USE_SIMD
  return Vector2f (-v.X (), -v.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
#ifdef NIEPCE_USE_SIMD
  return Vector2f (_mm_add_ps (lhs.Xy (), rhs.Xy ()));
#else
  return Vector2f (lhs.X () + rhs.X (), lhs.Y () + rhs.Y ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
#ifdef NIEPCE_USE_SIMD
  return Vector2f (_mm_sub_ps (lhs.Xy (), rhs.Xy ()));
#else
  return Vector2f (lhs.X () - rhs.X (), lhs.Y () - rhs.Y ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Vector2f& v, Float t) -> Vector2f
{
#ifdef NIEPCE_USE_SIMD
  const auto s = _mm_set1_ps (t);
  return Vector2f (_mm_mul_ps (v.Xy (), s));
#else
  return Vector2f (v.X () * t, v.Y () * t);
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float t, const Vector2f& v) -> Vector2f
{
  return v * t;
}
/*
// ---------------------------------------------------------------------------
*/
auto operator / (const Vector2f& v, Float t) -> Vector2f
{
  const Float inv = 1.0 / t;
  return v * inv;
}
/*
// ---------------------------------------------------------------------------
*/
auto Dot (const Vector2f& lhs, const Vector2f& rhs) -> Float
{
#ifdef NIEPCE_USE_SIMD
  return _mm_cvtss_f32 (_mm_dp_ps (lhs.Xy (), rhs.Xy (), 0x71));
#else
  return lhs.X () * rhs.X () + lhs.Y () * rhs.Y ();
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
/*
auto Cross (const Vector2f& lhs, const Vector2f& rhs) -> Float
{
  return lhs.X () * rhs.Y () - lhs.Y () * rhs.X ();
}
*/
/*
// ---------------------------------------------------------------------------
*/
auto Multiply (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
#ifdef NIEPCE_USE_SIMD
  return Vector2f (_mm_mul_ps (lhs.Xy (), rhs.Xy ()));
#else
  return Vector2f (lhs.X () * rhs.X (), lhs.Y () * rhs.Y ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
