namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------
*/
inline Vector2f::Vector2f () :
    xy_ ({0, 0})
{}
/*
// ---------------------------------------------------------------------------
*/
inline Vector2f::Vector2f (Float x, Float y) :
    xy_ ({x, y})
{}
/*
// ---------------------------------------------------------------------------
*/
inline Vector2f::Vector2f (Float s) :
    xy_ ({s, s})
{}
/*
// ---------------------------------------------------------------------------
// Operators
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::operator [] (unsigned idx_) const -> Float
{
  // todo: Range check
  return xy_[idx_];
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::operator [] (unsigned idx_) -> Float&
{
  // todo: Range check
  return xy_[idx_];
}
/*
// ---------------------------------------------------------------------------
// Methods
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::At (unsigned idx_) const -> Float
{
  // todo: Range check
  return xy_.at (idx_);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::At (unsigned idx_) -> Float&
{
  // todo: Range check
  return xy_.at (idx_);
}
/*
// ---------------------------------------------------------------------------
// Getter
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::X () const -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::Y () const -> Float
{
  return y_;
}
/*
// ---------------------------------------------------------------------------
// Setter
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::SetX (Float x) -> void
{
  x_ = x;
}
/*
// ---------------------------------------------------------------------------
*/

inline auto Vector2f::SetY (Float y) -> void
{
  y_ = y;
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
  return x_ * x_ + y_ * y_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::HasNaN () const -> bool
{
  return static_cast <bool> (std::isnan (x_) | std::isnan (y_));
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::IsNormalized () const -> bool
{
  const Float eps = 1.0e-5;
  return (std::fabs (LengthSquared () - 1.0) < eps);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Vector2f::ToString () const -> std::string
{
  return std::string ("[x = "  + std::to_string (x_) +
                      ", y = " + std::to_string (y_) + "]");
}
/*
// ---------------------------------------------------------------------------
// Global operators for Vector2f
// ---------------------------------------------------------------------------
*/
inline auto operator == (const Vector2f& lhs, const Vector2f& rhs) -> bool
{
  if (lhs.X () == rhs.X () && lhs.Y () == rhs.Y ()) { return true; }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator != (const Vector2f& lhs, const Vector2f& rhs) -> bool
{
  return !(lhs == rhs);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator - (const Vector2f& v) -> Vector2f
{
  return Vector2f (-v.X (), -v.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator + (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
  return Vector2f (lhs.X () + rhs.X (), lhs.Y () + rhs.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator - (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
{
  return Vector2f (lhs.X () - rhs.X (), lhs.Y () - rhs.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator * (const Vector2f& v, Float t) -> Vector2f
{
  return Vector2f (v.X () * t, v.Y () * t);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator * (Float t, const Vector2f& v) -> Vector2f
{
  return Vector2f (v.X () * t, v.Y () * t);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator / (const Vector2f& v, Float t) -> Vector2f
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
inline auto Dot (const Vector2f& lhs, const Vector2f& rhs) -> Float
{
  return lhs.X () * rhs.X () + lhs.Y () * rhs.Y ();
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Cross (const Vector2f& lhs, const Vector2f& rhs) -> Float
{
  return lhs.X () * rhs.Y () - lhs.Y () * rhs.X ();
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Multiply (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f
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

