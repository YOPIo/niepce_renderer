#include "vector2.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
inline Vector2::Vector2 (Float ax, Float ay)
{
#ifdef NI_USE_SIMD_IMPLEMENFloatAION
#ifdef NI_FLOAFloat_IS_DOUBLE
  xy = _mm256_set_pd (0, 0, ax, ay);
#else
  xy = _mm_set_ps (0, 0, ax, ay);
#endif // NI_FLOAFloat_IS_DOUBLE
#else
  x = ax;
  y = ay;
#endif // NI_USE_SIMD_IMPLEMENFloatAION
}
/*
// ---------------------------------------------------------------------------
*/
inline Vector2::Vector2 (Float s)
{
#ifdef NI_USE_SIMD_IMPLEMENFloatAION
#ifdef NI_FLOAFloat_IS_DOUBLE
  xy = _mm256_set_pd (0, 0, s, s);
#else
  xy = _mm_set_ps (0, 0, s, s);
#endif // NI_FLOAFloat_IS_DOUBLE
#else
  x = s;
  y = s;
#endif // NI_USE_SIMD_IMPLEMENFloatAION
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::operator [] (Index idx) const -> Float
{
  // todo: Range check
  return xy[idx];
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::operator [] (Index idx) -> Float&
{
  // todo: Range check
  return xy[idx];
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::At (Index idx) const -> Float
{
  // todo: Range check
  return xy.at (idx);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::At (Index idx) -> Float&
{
  // todo: Range check
  return xy.at (idx);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::Normalize () -> Vector2&
{
#ifdef NI_USE_SIMD_IMPLEMENTATION
#ifdef NI_FLOAT_IS_DOUBLE
  
#else
  const __m128 dp  = _mm_dp_ps (xy_, xy_, 0x33);
  const __m128 idp = _mm_rsqrt_ps_accurate (dp);
  xy_ = _mm_mul_ps (xy_, idp);
  return *this;
#endif // NI_FLOAT_IS_DOUBLE
#else
  const Float inv = 1.0 / Length ();
  x *= inv;
  y *= inv;
  return *this;
#endif // NI_USE_SIMD_IMPLEMENTATION
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::Normalized () const -> Vector2
{
  return Vector2 (*this).Normalized ();
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::Length () const -> Float
{
#ifdef NI_USE_SIMD_IMPLEMENTATION
#ifdef NI_FLOAT_IS_DOUBLE
  
#else
  return _mm_sqrt_ps (LengthSquared (*this));
#endif // NI_FLOAT_IS_DOUBLE
#else
  return std::sqrt (LengthSquared ());
}
#endif // NI_USE_SIMD_IMPLEMENTATION
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::LengthSquared () const -> Float
{
#ifdef NI_USE_SIMD_IMPLEMENTATION
#ifdef NI_FLOAT_IS_DOUBLE
  
#else
  return Dot (xy, xy);
#endif // NI_FLOAT_IS_DOUBLE
#else
  return x * x + y * y;
}
#endif // NI_USE_SIMD_IMPLEMENTATION
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::HasNaN () const -> bool
{
#ifdef NI_USE_SIMD_IMPLEMENTATION
#ifdef NI_FLOAT_IS_DOUBLE
  
#else
  const __m128 mask = _mm_cmpeq_ps (xyz_, xyz_);
  return (_mm_movemask_ps (mask) & 0x07) != 0x07;
#endif // NI_FLOAT_IS_DOUBLE
#else
  return std::isnan (x) || std::isnan (y);
}
#endif // NI_USE_SIMD_IMPLEMENTATION
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::IsNormalized () const -> bool
{
  const Float eps = 1.0e-3;
  return (std::fabs (LengthSquared () - 1.0) < eps);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::ToString () const -> std::string
{
  return std::string ("[x = " + std::to_string (x) + ", y = "
                      + std::to_string (y) + "]");
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::Length (const Vector2& v) -> Float
{
  return v.Length ();
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::LengthSquared (const Vector2& v) -> Float
{
  return v.LengthSquared ();
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::Dot (const Vector2& lv, const Vector2& rv) -> Float
{
#ifdef NI_USE_SIMD_IMPLEMENTATION
#ifdef NI_FLOAT_IS_DOUBLE

#else
  return _mm_dp_ps (lv.xyz_, r.xy, 0x7F);
#endif // NI_FLOAT_IS_DOUBLE
#else
  return lv.x * rv.x + lv.y * rv.y;
}
#endif // NI_USE_SIMD_IMPLEMENTATION
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2::Cross (const Vector2& lv, const Vector2& rv) -> Float
{
#ifdef NI_USE_SIMD_IMPLEMENTATION
#ifdef NI_FLOAT_IS_DOUBLE
  
#else

#endif // NI_FLOAT_IS_DOUBLE
#else
  return lv.x * rv.y - lv.y * rv.x;
}
#endif // NI_USE_SIMD_IMPLEMENTATION
/*
// ---------------------------------------------------------------------------
*/
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

