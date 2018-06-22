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
  x_ (0),
  y_ (0),
  z_ (0)
{}
/*
// ---------------------------------------------------------------------------
*/
Point3f::Point3f (Float t) :
  x_ (t),
  y_ (t),
  z_ (t)
{}
/*
// ---------------------------------------------------------------------------
*/
Point3f::Point3f (Float x, Float y, Float z) :
  x_ (x),
  y_ (y),
  z_ (z)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::operator [] (unsigned int idx) const noexcept -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  return z_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::operator () (unsigned int idx) const noexcept -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  return z_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point3f::At (unsigned int idx) const -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  if (idx == 2) { return z_; }
  throw std::out_of_range ("");
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
  return std::string ("[" + std::to_string (x_) + ", "
                      + std::to_string (y_) + ", "
                      + std::to_string (z_) + "]");
}
/*
// ---------------------------------------------------------------------------
// Global operator difinition
// ---------------------------------------------------------------------------
*/
auto operator - (const Point3f& lhs, const Point3f& rhs) -> Vector3f
{
  return Vector3f (lhs.X () - rhs.X (),
                   lhs.Y () - rhs.Y (),
                   lhs.Z () - rhs.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Point3f& p, Float s) -> Point3f
{
  return Point3f (p.X () * s,
                  p.Y () * s,
                  p.Z () * s);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float s, const Point3f& p) -> Point3f
{
  return Point3f (p.X () * s,
                  p.Y () * s,
                  p.Z () * s);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Point3f& lhs, const Point3f& rhs) -> Point3f
{
  return Point3f (lhs.X () + rhs. X (),
                  lhs.Y () + rhs. Y (),
                  lhs.Z () + rhs. Z ());
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
