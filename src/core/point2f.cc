/*!
 * @file point2.inl
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/29
 * @details 
 */
#include "point2f.h"
#include "vector2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Point2f::Point2f () :
#ifdef NIEPCE_USE_SIMD
  xyzw_ (_mm_setzero_ps ())
#else
  x_ (0), y_ (0), z_ (0), w_ (0)
#endif // NIEPCE_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
Point2f::Point2f (Float t) :
#ifdef NIEPCE_USE_SIMD
  xyzw_ (_mm_set_ps (0, 0, t, t))
#else
  x_ (t), y_ (t)
#endif // NIEPCE_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
Point2f::Point2f (Float x, Float y) :
#ifdef NIEPCE_USE_SIMD
  xyzw_ (_mm_set_ps (0, 0, y, x))
#else
  x_ (x), y_ (y)
#endif // NIEPCE_USE_SIMD
{}
/*
// ---------------------------------------------------------------------------
*/
#ifdef NIEPCE_USE_SIMD
Point2f::Point2f (const __m128& p) :
  xyzw_ (p)
{}
#endif // NIEPCE_USE_SIMD
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::operator [] (unsigned int idx) const noexcept -> Float
{
  return ((idx == 0) ? x_ : y_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::At (unsigned int idx) const -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  throw std::out_of_range ("Out of range in Point2f.");
}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::X () const noexcept -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::Y () const noexcept -> Float
{
  return y_;
}
/*
// ---------------------------------------------------------------------------
*/
#ifdef NIEPCE_USE_SIMD
auto Point2f::Xy () const noexcept -> __m128
{
  return xyzw_;
}
#endif // NIEPCE_USE_SIMD
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::SetX(Float x) noexcept -> void
{
  x_ = x;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::SetY (Float y) noexcept -> void
{
  y_ = y;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::ToString () const noexcept -> std::string
{
  return "["   + std::to_string (x_)
        + ", " + std::to_string (y_) + "]";
}
/*
// ---------------------------------------------------------------------------
*/
auto operator == (const Point2f& lhs, const Point2f& rhs) -> bool
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
auto operator != (const Point2f& lhs, const Point2f& rhs) -> bool
{
  return !(lhs == rhs);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Point2f& lhs, const Point2f& rhs) -> Point2f
{
#ifdef NIEPCE_USE_SIMD
  return Point2f (_mm_add_ps (lhs.Xy (), rhs.Xy ()));
#else
  return Point2f (lhs.X () + rhs.X (),
                  lhs.Y () + rhs.Y ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Point2f& lhs, const Point2f& rhs) -> Vector2f
{
#ifdef NIEPCE_USE_SIMD
  return Vector2f (_mm_sub_ps (lhs.Xy(), rhs.Xy ()));
#else
  return Vector2f (lhs.X () - rhs.X (),
                   lhs.Y () - rhs.Y ());
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Point2f& p, Float t) -> Point2f
{
#ifdef NIEPCE_USE_SIMD
  const auto s = _mm_set1_ps (t);
  return Point2f (_mm_mul_ps (p.Xy (), s));
#else
  return Point2f (p.X () * t, p.Y () * t);
#endif // NIEPCE_USE_SIMD
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float t, const Point2f& p) -> Point2f
{
  return p * t;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
