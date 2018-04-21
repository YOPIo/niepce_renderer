namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------
*/
inline Vector4f::Vector4f () :
    xyzw_ ({0, 0, 0, 0})
{}
/*
// ---------------------------------------------------------------------------
*/
inline Vector4f::Vector4f (Float x, Float y, Float z, Float w) :
    xyzw_ ({x, y, z, w})
{}
/*
// ---------------------------------------------------------------------------
*/
inline Vector4f::Vector4f (Float s) :
    xyzw_ ({s, s, s, s})
{}
/*
// ---------------------------------------------------------------------------
// Operators
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::operator [] (unsigned idx) const -> Float
{
  return xyzw_[idx];
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::operator [] (unsigned idx) -> Float&
{
  return xyzw_[idx];
}
/*
// ---------------------------------------------------------------------------
// Methods
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::At (unsigned idx) const -> Float
{
  return xyzw_.at (idx);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::At (unsigned idx) -> Float&
{
  return xyzw_.at (idx);
}
/*
// ---------------------------------------------------------------------------
// Getter
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::X () const -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::Y () const -> Float
{
  return y_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::Z () const -> Float
{
  return z_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::W () const -> Float
{
  return w_;
}
/*
// ---------------------------------------------------------------------------
// Setter
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::SetX (Float x) -> void
{
  x_ = x;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::SetY (Float y) -> void
{
  y_ = y;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::SetZ (Float z) -> void
{
  z_ = z;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::SetW (Float w) -> void
{
  w_ = w;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::Normalize () -> Vector4f&
{
  return (*this = *this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::Normalized () const -> Vector4f
{
  return Vector4f (*this / Length ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::Length () const -> Float
{
  return std::sqrt (LengthSquared ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::LengthSquared () const -> Float
{
  return x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;
}
/*
// ---------------------------------------------------------------------------
*/
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::HasNaN () const -> bool
{
  return static_cast <bool> (std::isnan (x_) | std::isnan (y_) |
                             std::isnan (z_) | std::isnan (w_));
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::IsNormalized () const -> bool
{
  const Float eps = 1.0e-5;
  return (std::fabs (LengthSquared () - 1.0) < eps);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector4f::ToString () const -> std::string
{
  return std::string ("[x = "  + std::to_string (x_) +
                      ", y = " + std::to_string (y_) +
                      ", z = " + std::to_string (z_) +
                      ", w = " + std::to_string (w_) + "]");
}
/*
// ---------------------------------------------------------------------------
// Global operators for Vector4f
// ---------------------------------------------------------------------------
*/
inline auto operator == (const Vector4f& lhs, const Vector4f& rhs) -> bool
{
  if (lhs.X () == rhs.X () &&
      lhs.Y () == rhs.Y () &&
      lhs.Z () == rhs.Z () &&
      lhs.W () == rhs.W ())
  {
    return true;
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator != (const Vector4f& lhs, const Vector4f& rhs) -> bool
{
  return !(lhs == rhs);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator - (const Vector4f& v) -> Vector4f
{
  return Vector4f (-v.X (), -v.Y (), -v.Z (), -v.W ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator + (const Vector4f& lhs, const Vector4f& rhs) -> Vector4f
{
  return Vector4f (lhs.X () + rhs.X (),
                   lhs.Y () + rhs.Y (),
                   lhs.Z () + rhs.Z (),
                   lhs.W () + rhs.W ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator - (const Vector4f& lhs, const Vector4f& rhs) -> Vector4f
{
  return Vector4f (lhs.X () - rhs.X (),
                   lhs.Y () - rhs.Y (),
                   lhs.Z () - rhs.Z (),
                   lhs.W () - rhs.W ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator * (const Vector4f& v, Float t) -> Vector4f
{
  return Vector4f (v.X () * t, v.Y () * t, v.Z () * t, v.W () * t);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator * (Float t, const Vector4f& v) -> Vector4f
{
  return Vector4f (v.X () * t, v.Y () * t, v.Z () * t, v.W () * t);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator / (const Vector4f& v, Float t) -> Vector4f
{
  const Float inv = 1.0 / t;
  return Vector4f (v.X () * inv, v.Y () * inv, v.Z () * inv, v.W () * inv);
}
/*
// ---------------------------------------------------------------------------
// Global functions for Vector4f
// ---------------------------------------------------------------------------
*/
inline auto Multiply (const Vector4f& lhs, const Vector4f& rhs) -> Vector4f
{
  return Vector4f (lhs.X () * rhs.X (),
                   lhs.Y () * rhs.Y (),
                   lhs.Z () * rhs.Z (),
                   lhs.W () * rhs.W ());
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

