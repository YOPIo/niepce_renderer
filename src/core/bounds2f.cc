/*!
 * @file bounds2f.inl
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "bounds2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Bounds2f::Bounds2f () :
  min_ (kFloatMax, kFloatMax),
  max_ (kFloatMin, kFloatMin)
{}
/*
// ---------------------------------------------------------------------------
*/
Bounds2f::Bounds2f (const Point2f& p0, const Point2f& p1)
{
  const Float min_x = std::fmin (p0.X (), p1.X ());
  const Float min_y = std::fmin (p0.Y (), p1.Y ());
  const Float max_x = std::fmax (p0.X (), p1.X ());
  const Float max_y = std::fmax (p0.Y (), p1.Y ());

  min_ = Point2f (min_x, min_y);
  max_ = Point2f (max_x, max_y);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::Max () const noexcept -> Point2f
{
  return max_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::Min () const noexcept -> Point2f
{
  return min_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::SetMax (const Point2f& max) noexcept -> void
{
  max_ = max;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::SetMin (const Point2f& min) noexcept -> void
{
  min_ = min;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::ToString () const noexcept -> std::string
{
  return "min: " + min_.ToString () + "\n" +
         "max: " + max_.ToString ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::IsInside (const Point2f &p) const noexcept -> bool
{
  return (min_.X () <= p.X ()) && (p.X () <= max_.X ()) &&
         (min_.Y () <= p.Y ()) && (p.Y () <= max_.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
