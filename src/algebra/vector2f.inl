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
inline Vector2f::Vector2f () :
    xy ({0, 0})
{}
/*
// ---------------------------------------------------------------------------
*/
inline Vector2f::Vector2f (Float _x, Float _y) :
    xy ({_x, _y})
{}
/*
// ---------------------------------------------------------------------------
*/
inline Vector2f::Vector2f (Float s) :
    xy ({s, s})
{}
/*
// ---------------------------------------------------------------------------
// Operators
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::operator [] (Index idx) const -> Float
{
  // todo: Range check
  return xy[idx];
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::operator [] (Index idx) -> Float&
{
  // todo: Range check
  return xy[idx];
}
/*
// ---------------------------------------------------------------------------
// Methods
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::At (Index idx) const -> Float
{
  // todo: Range check
  return xy.at (idx);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::At (Index idx) -> Float&
{
  // todo: Range check
  return xy.at (idx);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::Normalize () -> Vector2f&
{
  return (*this = *this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::Normalized () const -> Vector2f
{
  return Vector2f (*this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::Length () const -> Float
{
  return std::sqrt (LengthSquared ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::LengthSquared () const -> Float
{
  return x * x + y * y;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::HasNaN () const -> bool
{
  return static_cast <bool> (std::isnan (x) | std::isnan (y));
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::IsNormalized () const -> bool
{
  const Float eps = 1.0e-3;
  return (std::fabs (LengthSquared () - 1.0) < eps);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::ToString () const -> std::string
{
  return std::string ("[x = " + std::to_string (x)+ ", y = "
                      + std::to_string (y) + "]");
}
/*
// ---------------------------------------------------------------------------
// Global operators for Vector2f
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector2f& lhs, const Vector2f& rhs) -> bool
{
  if (lhs.x == rhs.x && lhs.y == rhs.y) { return true; }
  return false;
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
  return Vector2f (-v.x, -v.y);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
  return Vector2f (lhs.x + rhs.x, lhs.y + rhs.y);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
  return Vector2f (lhs.x - rhs.x, lhs.y - rhs.y);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Vector2f& v, Float t) -> Vector2f
{
  return Vector2f (v.x * t, v.y * t);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float t, const Vector2f& v) -> Vector2f
{
  return Vector2f (v.x * t, v.y * t);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator / (const Vector2f& v, Float t) -> Vector2f
{
#if defined (NIEPCE_FLOAT_IS_DOUBLE)
  const Float inv = 1.0 / t;
#else
  const Float inv = 1.0f / t;
#endif
  return Vector2f (v.x * inv, v.y * inv);
}
/*
// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
*/
auto Dot (const Vector2f& lhs, const Vector2f& rhs) -> Float
{
  return lhs.x * rhs.x + lhs.y * rhs.y;
}
/*
auto Cross (const Vector2f& lhs, const Vector2f& rhs) -> Float
{
  return lhs.x * rhs.y - lhs.y * rhs.x;
}
*/
/*
// ---------------------------------------------------------------------------
*/
auto Multiply (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
  return Vector2f (lhs.x * rhs.x, lhs.y * rhs.y);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

