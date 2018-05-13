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
    xy_ ({0, 0})
{}
/*
// ---------------------------------------------------------------------------
*/
Vector2f::Vector2f (Float x, Float y) :
    xy_ ({x, y})
{}
/*
// ---------------------------------------------------------------------------
*/
Vector2f::Vector2f (Float s) :
    xy_ ({s, s})
{}
/*
// ---------------------------------------------------------------------------
// Operators
// ---------------------------------------------------------------------------
*/
auto Vector2f::operator [] (unsigned idx_) const -> Float
{
  // todo: Range check
  return xy_[idx_];
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::operator [] (unsigned idx_) -> Float&
{
  // todo: Range check
  return xy_[idx_];
}
/*
// ---------------------------------------------------------------------------
// Methods
// ---------------------------------------------------------------------------
*/
auto Vector2f::At (unsigned idx_) const -> Float
{
  // todo: Range check
  return xy_.at (idx_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::At (unsigned idx_) -> Float&
{
  // todo: Range check
  return xy_.at (idx_);
}
/*
// ---------------------------------------------------------------------------
// Getter
// ---------------------------------------------------------------------------
*/
auto Vector2f::X () const -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::Y () const -> Float
{
  return y_;
}
/*
// ---------------------------------------------------------------------------
// Setter
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
auto Vector2f::Normalize () -> Vector2f&
{
  return (*this = *this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::Normalized () const -> Vector2f
{
  return Vector2f (*this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::Length () const -> Float
{
  return std::sqrt (LengthSquared ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::LengthSquared () const -> Float
{
  return x_ * x_ + y_ * y_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::HasNaN () const -> bool
{
  return static_cast <bool> (std::isnan (x_) | std::isnan (y_));
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::IsNormalized () const -> bool
{
  const Float eps = 1.0e-5;
  return (std::fabs (LengthSquared () - 1.0) < eps);
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector2f::ToString () const -> std::string
{
  return std::string ("[x = "  + std::to_string (x_) +
                      ", y = " + std::to_string (y_) + "]");
}
/*
// ---------------------------------------------------------------------------
// Global operators for Vector2f
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector2f& lhs, const Vector2f& rhs) -> bool
{
  if (lhs.X () == rhs.X () && lhs.Y () == rhs.Y ()) { return true; }
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
  return Vector2f (-v.X (), -v.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
  return Vector2f (lhs.X () + rhs.X (), lhs.Y () + rhs.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
  return Vector2f (lhs.X () - rhs.X (), lhs.Y () - rhs.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Vector2f& v, Float t) -> Vector2f
{
  return Vector2f (v.X () * t, v.Y () * t);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float t, const Vector2f& v) -> Vector2f
{
  return Vector2f (v.X () * t, v.Y () * t);
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
  return Vector2f (v.X () * inv, v.Y () * inv);
}
/*
// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
*/
auto Dot (const Vector2f& lhs, const Vector2f& rhs) -> Float
{
  return lhs.X () * rhs.X () + lhs.Y () * rhs.Y ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Cross (const Vector2f& lhs, const Vector2f& rhs) -> Float
{
  return lhs.X () * rhs.Y () - lhs.Y () * rhs.X ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Multiply (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
  return Vector2f (lhs.X () * rhs.X (), lhs.Y () * rhs.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
