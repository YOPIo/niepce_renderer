#include "vector3f.h"
#include "point3f.h"
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
Vector3f::Vector3f () :
#ifdef NIEPCE_USE_SIMD
  xyzw_ (_mm_setzero_ps ())
#else
  x_ (0), y_ (0), z_ (0), w_ (0)
#endif // NIEPCE_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
Vector3f::Vector3f (Float x, Float y, Float z) :
#ifdef NIEPCE_USE_SIMD
  xyzw_ (_mm_set_ps (0, z, y, x))
#else
  x_ (x), y_ (y), z_ (z), w_ (0)
#endif // NIEPCE_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
Vector3f::Vector3f (Float s) :
#ifdef NIEPCE_USE_SIMD
  xyzw_ (_mm_set_ps (0, s, s, s))
#else
  x_ (s), y_ (s), z_ (s), w_ (0)
#endif // NIEPCE_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
#ifdef NIEPCE_USE_SIMD
Vector3f::Vector3f (const __m128& v) :
  xyzw_ (v)
{}
#endif // NIEPCE_USE_SIMD
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::operator [] (unsigned idx) const noexcept -> Float
{
  return (idx == 0) ? x_ : ((idx == 1) ? y_ : z_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::At (unsigned idx) const -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  if (idx == 2) { return z_; }
  throw std::out_of_range ("Out of range in Vector3f.");
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::X () const noexcept -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Y () const noexcept -> Float
{
  return y_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Z () const noexcept -> Float
{
  return z_;
}
/*
// ---------------------------------------------------------------------------
*/
#ifdef NIEPCE_USE_SIMD
auto Vector3f::Xyz () const noexcept -> __m128
{
  return xyzw_;
}
#endif // NIEPCE_USE_SIMD
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::SetX (Float x) noexcept -> void
{
  x_ = x;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::SetY (Float y) noexcept -> void
{
  y_ = y;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::SetZ (Float z) noexcept -> void
{
  z_ = z;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Normalize () noexcept -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  xyzw_ = _mm_div_ps (xyzw_, _mm_sqrt_ps (_mm_dp_ps (xyzw_, xyzw_, 0xFF)));
  return *this;
#else
  const Float inv_len = 1.0 / Length ();
  x_ *= inv_len;
  y_ *= inv_len;
  z_ *= inv_len;
  w_ *= inv_len;
  return *this;
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Length () const -> Float
{
#ifdef NIEPCE_USE_SIMD
  return _mm_cvtss_f32(_mm_sqrt_ss (_mm_dp_ps (xyzw_, xyzw_, 0x71)));
#else
  return std::sqrt (LengthSquared ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::LengthSquared () const -> Float
{
#ifdef NIEPCE_USE_SIMD
  return _mm_cvtss_f32 (_mm_dp_ps (xyzw_, xyzw_, 0x71));
#else
  return x_ * x_ + y_ * y_ + z_ * z_;
#endif
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::HasNaN () const -> bool
{
#ifdef NIEPCE_USE_SIMD
  const __m128 mask = _mm_cmpeq_ps (xyzw_, xyzw_);
  return (_mm_movemask_ps (mask) & 0x0F) != 0x0F;
#else
  return static_cast <bool> (std::isnan (x_) ||
                             std::isnan (y_) ||
                             std::isnan (z_));
#endif
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::ToString () const -> std::string
{
  return std::string ("["  + std::to_string (x_) +
                      ", " + std::to_string (y_) +
                      ", " + std::to_string (z_) + "]");
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::IsBlack () const -> bool
{
  return (x_ != 0) && (y_ != 0) && (z_ != 0);
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Max () noexcept -> Vector3f
{
  return Vector3f (std::numeric_limits <Float>::max ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Min () noexcept -> Vector3f
{
  return Vector3f (std::numeric_limits <Float>::min ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Infinity () noexcept -> Vector3f
{
  return Vector3f (std::numeric_limits <Float>::infinity ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Lowest () noexcept -> Vector3f
{
  return Vector3f (std::numeric_limits <Float>::lowest ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::One () noexcept -> Vector3f
{
  return Vector3f (1);
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Zero () noexcept -> Vector3f
{
  return Vector3f (0);
}
/*
// ---------------------------------------------------------------------------
// Global operators for Vector3f
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector3f& lhs, const Vector3f& rhs) -> bool
{
#ifdef NIEPCE_USE_SIMD
  const auto mask = _mm_movemask_ps (_mm_cmpeq_ps (lhs.Xyz (), rhs.Xyz ()));
  return ((mask & 0x07) == 0x07);
#else
  if (lhs.X () == rhs.X () && lhs.Y () == rhs.Y () && lhs.Z () == rhs.Z () )
  {
    return true;
  }
  return false;
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator != (const Vector3f& lhs, const Vector3f& rhs) -> bool
{
  return !(lhs == rhs);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Vector3f& v) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  const auto mask = _mm_castsi128_ps (_mm_set1_epi32(0x80000000));
  return Vector3f (_mm_xor_ps (v.Xyz (), mask));
#else
  return Vector3f (-v.X (), -v.Y (), -v.Z ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  return Vector3f (_mm_add_ps (lhs.Xyz (), rhs.Xyz ()));
#else
  return Vector3f (lhs.X () + rhs.X (),
                   lhs.Y () + rhs.Y (),
                   lhs.Z () + rhs.Z ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  return Vector3f (_mm_sub_ps (lhs.Xyz (), rhs.Xyz ()));
#else
  return Vector3f (lhs.X () - rhs.X (),
                   lhs.Y () - rhs.Y (),
                   lhs.Z () - rhs.Z ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Vector3f& v, Float t) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  const auto s = _mm_set1_ps (t);
  return Vector3f (_mm_mul_ps (v.Xyz (), s));
#else
  return Vector3f (v.X () * t,
                   v.Y () * t,
                   v.Z () * t);
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float t, const Vector3f& v) -> Vector3f
{
  return v * t;
}
/*
// ---------------------------------------------------------------------------
*/
auto operator / (const Vector3f& v, Float t) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  const auto s = _mm_set1_ps (t);
  return Vector3f (_mm_div_ps (v.Xyz (), s));
#else
  const Float inv = 1.0 / t;
  return Vector3f (v.X () * inv, v.Y () * inv, v.Z () * inv);
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  return Vector3f (_mm_mul_ps (lhs.Xyz (), rhs.Xyz ()));
#else
  return Vector3f (lhs.X () * rhs.X (),
                   lhs.Y () * rhs.Y (),
                   lhs.Z () * rhs.Z ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator / (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  return Vector3f (_mm_div_ps (lhs.Xyz (), rhs.Xyz ()));
#else
  return Vector3f (lhs.X () / rhs.X (),
                   lhs.Y () / rhs.Y (),
                   lhs.Z () / rhs.Z ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
// Global functions for Vector3f
// ---------------------------------------------------------------------------
*/
auto Dot (const Vector3f& lhs, const Vector3f& rhs) -> Float
{
#ifdef NIEPCE_USE_SIMD
  return _mm_cvtss_f32 (_mm_dp_ps (lhs.Xyz (), rhs.Xyz (), 0x71));
#else
  return lhs.X () * rhs.X () + lhs.Y () * rhs.Y () + lhs.Z () * rhs.Z ();
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto Cross (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  const auto tmp0 = _mm_shuffle_ps (lhs.Xyz (), lhs.Xyz (), _MM_SHUFFLE (3, 0, 2, 1));
  const auto tmp1 = _mm_shuffle_ps (rhs.Xyz (), rhs.Xyz (), _MM_SHUFFLE (3, 1, 0, 2));
  const auto tmp2 = _mm_shuffle_ps (lhs.Xyz (), lhs.Xyz (), _MM_SHUFFLE (3, 1, 0, 2));
  const auto tmp3 = _mm_shuffle_ps (rhs.Xyz (), rhs.Xyz (), _MM_SHUFFLE (3, 0, 2, 1));
  return Vector3f (_mm_sub_ps (_mm_mul_ps (tmp0, tmp1), _mm_mul_ps (tmp2, tmp3)));
#else
  return Vector3f (lhs.Y () * rhs.Z () - lhs.Z () * rhs.Y (),
                   lhs.Z () * rhs.X () - lhs.X () * rhs.Z (),
                   lhs.X () * rhs.Y () - lhs.Y () * rhs.X ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto Normalize (const Vector3f& vec) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  auto tmp = vec;
  auto res = tmp.Normalize ();
  return res;
#else
  return vec / vec.Length ();
#endif
}
/*
// ---------------------------------------------------------------------------
*/
auto Multiply (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
#ifdef NIEPCE_USE_SIMD
  return Vector3f (_mm_mul_ps (lhs.Xyz (), rhs.Xyz ()));
#else
  return Vector3f (lhs.X () * rhs.X (),
                   lhs.Y () * rhs.Y (),
                   lhs.Z () * rhs.Z ());
#endif
}
/*
// ---------------------------------------------------------------------------
*/
auto BuildOrthonormalBasis
(
 const Vector3f& normal,
 Vector3f* binormal,
 Vector3f* tangent
)
  -> void
{
  const Float sign = std::copysign (1.0f, normal.Z ()); // 1 or -1
  const Float a = -1.0f / (sign + normal.Z ());
  const Float b = normal.X () * normal.Y () * a;
  *binormal = Vector3f (1.0f + sign * normal.X () * normal.X () * a,
                        sign * b,
                        -sign * normal.X ());
  *tangent = Vector3f (b, sign + normal.Y () * normal.Y () * a, -normal.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Sqrt (const Vector3f &v) -> Vector3f
{
  return Vector3f (std::sqrt (v.X ()),
                   std::sqrt (v.Y ()),
                   std::sqrt (v.Z ()));
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
