/*!
 * @file point3f.inl
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
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
inline Point3f::Point3f (Float t) :
  x_ (t),
  y_ (t),
  z_ (t)
{}
/*
// ---------------------------------------------------------------------------
*/
inline Point3f::Point3f (Float x, Float y, Float z) :
  x_ (x),
  y_ (y),
  z_ (z)
{}
/*
// ---------------------------------------------------------------------------
*/
inline auto Point3f::operator [] (unsigned int idx) const noexcept -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  return z_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Point3f::operator () (unsigned int idx) const noexcept -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  return z_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Point3f::At (unsigned int idx) const -> Float
{
  if (idx == 0) { return x_; }
  if (idx == 1) { return y_; }
  if (idx == 2) { return z_; }
  throw std::out_of_range ("");
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Point3f::X () const noexcept -> Float
{
  return x_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Point3f::Y () const noexcept -> Float
{
  return y_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Point3f::Z () const noexcept -> Float
{
  return z_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Point3f::SetX (Float x) noexcept -> void
{
  x_ = x;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Point3f::SetY (Float y) noexcept -> void
{
  y_ = y;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Point3f::SetZ (Float z) noexcept -> void
{
  z_ = z;
}
/*
// ---------------------------------------------------------------------------
// Global operator difinition
// ---------------------------------------------------------------------------
*/
inline auto operator - (const Point3f& rhs, const Point3f& lhs) -> Vector3f
{
  return Vector3f (rhs.X () - lhs.X (),
                   rhs.Y () - lhs.Y (),
                   rhs.Z () - lhs.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
