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
Point2f::Point2f (Float t) :
  x_ (t),
  y_ (t)
{}
/*
// ---------------------------------------------------------------------------
*/
Point2f::Point2f (Float x, Float y) :
  x_ (x),
  y_ (y)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::operator [] (unsigned int idx) const noexcept -> Float
{
  if (idx == 0) { return x_; }
  return y_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::At (unsigned int idx) const -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  throw std::out_of_range ("");
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
auto Point2f::U () const noexcept -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::V () const noexcept -> Float
{
  return y_;
}
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
auto Point2f::SetU (Float u) noexcept -> void
{
  this->x_ = u;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::SetV (Float v) noexcept -> void
{
  this->y_ = v;
}
/*
// ---------------------------------------------------------------------------
*/
auto Point2f::ToString () const noexcept -> std::string
{
  return "[" + std::to_string (x_) + ", " + std::to_string(y_) + "]";
}
/*
// ---------------------------------------------------------------------------
*/
auto operator == (const Point2f& lhs, const Point2f& rhs) -> bool
{
  if (lhs.X () == rhs.X () &&
      lhs.Y () == rhs.Y ())
  {
    return true;
  }
  return false;
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
  return Point2f (lhs.X () + rhs.X (),
                  lhs.Y () + rhs.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Point2f& lhs, const Point2f& rhs) -> Vector2f
{
  return Vector2f (lhs.X () - rhs.X (),
                   lhs.Y () - rhs.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Point2f& p, Float t) -> Point2f
{
  return Point2f (p.X () * t, p.Y () * t);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float t, const Point2f& p) -> Point2f
{
  return Point2f (p.X () * t, p.Y () * t);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
