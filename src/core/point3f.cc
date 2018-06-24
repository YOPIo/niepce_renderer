/*!
 * @file point3f.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "point3f.h"
#include "vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Point3f::Point3f () :
#ifdef NI_USE_SIMD
  xyzw_ (_mm_setzero_ps ())
#else
  x_ (0), y_ (0), z_ (0)
#endif // NI_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
Point3f::Point3f (Float x, Float y, Float z) :
#ifdef NI_USE_SIMD
  xyzw_ (_mm_set_ps (0, z, y, x))
#else
  x_ (x), y_ (y), z_ (z), w_ (0)
#endif // NI_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
Point3f::Point3f (Float t) :
#ifdef NI_USE_SIMD
  xyzw_ (_mm_set_ps (0, t, t, t))
#else
  x_ (t), y_ (t), z_ (t), w_ (0)
#endif // NI_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
#ifdef NI_USE_SIMD
Point3f::Point3f (const __m128& p) :
  xyzw_ (p)
{}
#endif // NI_USE_SIMD
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::operator [] (unsigned int idx) const noexcept -> Float
{
  return (idx == 0) ? x_ : ((idx == 1) ? y_ : z_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::At (unsigned int idx) const -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  if (idx == 2) { return z_; }
  throw std::out_of_range ("Out of range in Vector3f.");
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::X () const noexcept -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::Y () const noexcept -> Float
{
  return y_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::Z () const noexcept -> Float
{
  return z_;
}
/*
// ---------------------------------------------------------------------------
*/
#ifdef NI_USE_SIMD
auto Point3f::Xyz () const noexcept -> __m128
{
  return xyzw_;
}
#endif // NI_USE_SIMD
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::SetX (Float x) noexcept -> void
{
  x_ = x;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::SetY (Float y) noexcept -> void
{
  y_ = y;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::SetZ (Float z) noexcept -> void
{
  z_ = z;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::ToString () const noexcept -> std::string
{
  return std::string ("["  + std::to_string (x_) +
                      ", " + std::to_string (y_) +
                      ", " + std::to_string (z_) + "]");
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::Max () noexcept -> Point3f
{
  return Point3f (std::numeric_limits <Float>::max ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::Min () noexcept -> Point3f
{
  return Point3f (std::numeric_limits <Float>::min ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::Infinity () noexcept -> Point3f
{
  return Point3f (std::numeric_limits <Float>::infinity ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::Lowest () noexcept -> Point3f
{
  return Point3f (std::numeric_limits <Float>::lowest ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::One () noexcept -> Point3f
{
  return Point3f (1);
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::Zero () noexcept -> Point3f
{
  return Point3f (0);
}
/*
// ---------------------------------------------------------------------------
// Global operator difinition
// ---------------------------------------------------------------------------
*/
auto operator - (const Point3f& lhs, const Point3f& rhs) -> Vector3f
{
#ifdef NI_USE_SIMD
  return Vector3f (_mm_sub_ps (lhs.Xyz (), rhs.Xyz ()));
#else
  return Vector3f (lhs.X () - rhs.X (),
                   lhs.Y () - rhs.Y (),
                   lhs.Z () - rhs.Z ());
#endif // NI_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Point3f& p, Float t) -> Point3f
{
#ifdef NI_USE_SIMD
  const auto s = _mm_set1_ps (t);
  return Point3f (_mm_mul_ps (p.Xyz (), s));
#else
  return Point3f (p.X () * t,
                  p.Y () * t,
                  p.Z () * t);
#endif // NI_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float s, const Point3f& p) -> Point3f
{
  return p * s;
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Point3f& lhs, const Point3f& rhs) -> Point3f
{
#ifdef NI_USE_SIMD
  return Point3f (_mm_add_ps (lhs.Xyz (), rhs.Xyz ()));
#else
  return Point3f (lhs.X () + rhs. X (),
                  lhs.Y () + rhs. Y (),
                  lhs.Z () + rhs. Z ());
#endif // NI_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Point3f& lhs, const Vector3f& rhs) -> Point3f
{
#ifdef NI_USE_SIMD
  return Point3f (_mm_add_ps (lhs.Xyz (), rhs.Xyz ()));
#else
  return Point3f (lhs.X () + rhs. X (),
                  lhs.Y () + rhs. Y (),
                  lhs.Z () + rhs. Z ());
#endif // NI_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
