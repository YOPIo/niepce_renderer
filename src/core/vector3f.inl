namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------
*/
inline Vector3f::Vector3f () :
    xyz_ ({0, 0, 0})
{}
/*
// ---------------------------------------------------------------------------
*/
inline Vector3f::Vector3f (Float x, Float y, Float z) :
    xyz_ ({x, y, z})
{}
/*
// ---------------------------------------------------------------------------
*/
inline Vector3f::Vector3f (Float s) :
    xyz_ ({s, s, s})
{}
/*
// ---------------------------------------------------------------------------
// Operators
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::operator [] (unsigned idx) const -> Float
{
  return xyz_[idx];
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::operator [] (unsigned idx) -> Float&
{
  return xyz_[idx];
}
/*
// ---------------------------------------------------------------------------
// Methods
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::At (unsigned idx) const -> Float
{
  return xyz_.at (idx);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::At (unsigned idx) -> Float&
{
  return xyz_.at (idx);
}
/*
// ---------------------------------------------------------------------------
// Getter
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::X () const -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::Y () const -> Float
{
  return y_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::Z () const -> Float
{
  return z_;
}
/*
// ---------------------------------------------------------------------------
// Setter
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::SetX (Float x) -> void
{
  x_ = x;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::SetY (Float y) -> void
{
  y_ = y;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::SetZ (Float z) -> void
{
  z_ = z;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::Normalize () -> Vector3f&
{
  return (*this = *this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::Normalized () const -> Vector3f
{
  return Vector3f (*this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::Length () const -> Float
{
  return std::sqrt (LengthSquared ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::LengthSquared () const -> Float
{
  return x_ * x_ + y_ * y_ + z_ * z_;
}
/*
// ---------------------------------------------------------------------------
*/
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::HasNaN () const -> bool
{
  return static_cast <bool> (std::isnan (x_) | std::isnan (y_) |
                             std::isnan (z_));
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::IsNormalized () const -> bool
{
  const Float eps = 1.0e-5;
  return (std::fabs (LengthSquared () - 1.0) < eps);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector3f::ToString () const -> std::string
{
  return std::string ("[x = "  + std::to_string (x_) +
                      ", y = " + std::to_string (y_) +
                      ", z = " + std::to_string (z_) + "]");
}
/*
// ---------------------------------------------------------------------------
// Global operators for Vector3f
// ---------------------------------------------------------------------------
*/
inline auto operator == (const Vector3f& lhs, const Vector3f& rhs) -> bool
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
inline auto operator != (const Vector3f& lhs, const Vector3f& rhs) -> bool
{
  return !(lhs == rhs);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator - (const Vector3f& v) -> Vector3f
{
  return Vector3f (-v.X (), -v.Y (), -v.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator + (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
  return Vector3f (lhs.X () + rhs.X (),
                   lhs.Y () + rhs.Y (),
                   lhs.Z () + rhs.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator - (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
  return Vector3f (lhs.X () - rhs.X (),
                   lhs.Y () - rhs.Y (),
                   lhs.Z () - rhs.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator * (const Vector3f& v, Float t) -> Vector3f
{
  return Vector3f (v.X () * t, v.Y () * t, v.Z () * t);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator * (Float t, const Vector3f& v) -> Vector3f
{
  return Vector3f (v.X () * t, v.Y () * t, v.Z () * t);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator / (const Vector3f& v, Float t) -> Vector3f
{
  const Float inv = 1.0 / t;
  return Vector3f (v.X () * inv, v.Y () * inv, v.Z () * inv);
}
/*
// ---------------------------------------------------------------------------
// Global functions for Vector3f
// ---------------------------------------------------------------------------
*/
inline auto Dot (const Vector3f& lhs, const Vector3f& rhs) -> Float
{
  return lhs.X () * rhs.X () + lhs.Y () * rhs.Y () + lhs.Z () * rhs.Z ();
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Cross (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
{
  return Vector3f (lhs.Y () * rhs.Z () - lhs.Z () * rhs.Y (),
                   lhs.Z () * rhs.X () - lhs.X () * rhs.Z (),
                   lhs.X () * rhs.Y () - lhs.Y () * rhs.X ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Multiply (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f
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

