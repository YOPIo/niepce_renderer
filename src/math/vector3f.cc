/*
// ---------------------------------------------------------------------------
*/
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
    xyz_ ({0, 0, 0})
{}
/*
// ---------------------------------------------------------------------------
*/
Vector3f::Vector3f (Float x, Float y, Float z) :
    xyz_ ({x, y, z})
{}
/*
// ---------------------------------------------------------------------------
*/
Vector3f::Vector3f (Float s) :
    xyz_ ({s, s, s})
{}
/*
// ---------------------------------------------------------------------------
// Operators
// ---------------------------------------------------------------------------
*/
auto Vector3f::operator [] (unsigned idx) const -> Float
{
  return xyz_[idx];
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::operator [] (unsigned idx) -> Float&
{
  return xyz_[idx];
}
/*
// ---------------------------------------------------------------------------
// Methods
// ---------------------------------------------------------------------------
*/
auto Vector3f::At (unsigned idx) const -> Float
{
  return xyz_.at (idx);
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::At (unsigned idx) -> Float&
{
  return xyz_.at (idx);
}
/*
// ---------------------------------------------------------------------------
// Getter
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
// Setter
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
auto Vector3f::Normalize () -> Vector3f&
{
  return (*this = *this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Normalized () const -> Vector3f
{
  return Vector3f (*this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::Length () const -> Float
{
  return std::sqrt (LengthSquared ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::LengthSquared () const -> Float
{
  return x_ * x_ + y_ * y_ + z_ * z_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::HasNaN () const -> bool
{
  return static_cast <bool> (std::isnan (x_) | std::isnan (y_) |
                             std::isnan (z_));
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::IsNormalized () const -> bool
{
  const Float eps = 1.0e-5;
  return (std::fabs (LengthSquared () - 1.0) < eps);
}
/*
// ---------------------------------------------------------------------------
*/
auto Vector3f::ToString () const -> std::string
{
  return std::string ("[x = "  + std::to_string (x_) +
                      ", y = " + std::to_string (y_) +
                      ", z = " + std::to_string (z_) + "]");
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
  if (lhs.X () == rhs.X () &&
      lhs.Y () == rhs.Y () &&
      lhs.Z () == rhs.Z () )
  {
    return true;
  }
  return false;
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
  return Vector3f (-v.X (), -v.Y (), -v.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
  return Vector3f (lhs.X () + rhs.X (),
                   lhs.Y () + rhs.Y (),
                   lhs.Z () + rhs.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Vector3f& lhs, const Point3f& rhs) -> Point3f
{
  return Point3f (lhs.X () + rhs.X (),
                  lhs.Y () + rhs.Y (),
                  lhs.Z () + rhs.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Point3f& lhs, const Vector3f& rhs) -> Point3f
{
  return Point3f (lhs.X () + rhs.X (),
                  lhs.Y () + rhs.Y (),
                  lhs.Z () + rhs.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
  return Vector3f (lhs.X () - rhs.X (),
                   lhs.Y () - rhs.Y (),
                   lhs.Z () - rhs.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Vector3f& v, Float t) -> Vector3f
{
  return Vector3f (v.X () * t, v.Y () * t, v.Z () * t);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float t, const Vector3f& v) -> Vector3f
{
  return Vector3f (v.X () * t, v.Y () * t, v.Z () * t);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator / (const Vector3f& v, Float t) -> Vector3f
{
  const Float inv = 1.0 / t;
  return Vector3f (v.X () * inv, v.Y () * inv, v.Z () * inv);
}
/*
// ---------------------------------------------------------------------------
// Global functions for Vector3f
// ---------------------------------------------------------------------------
*/
auto Dot (const Vector3f& lhs, const Vector3f& rhs) -> Float
{
  return lhs.X () * rhs.X () + lhs.Y () * rhs.Y () + lhs.Z () * rhs.Z ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Cross (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
  return Vector3f (lhs.Y () * rhs.Z () - lhs.Z () * rhs.Y (),
                   lhs.Z () * rhs.X () - lhs.X () * rhs.Z (),
                   lhs.X () * rhs.Y () - lhs.Y () * rhs.X ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Multiply (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
  return Vector3f (lhs.X () * rhs.X (),
                   lhs.Y () * rhs.Y (),
                   lhs.Z () * rhs.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
