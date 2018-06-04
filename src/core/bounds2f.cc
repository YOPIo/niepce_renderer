/*!
 * @file bounds2f.inl
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#include "vector2f.h"
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
auto Bounds2f::Append (const Point2f& p) noexcept -> void
{
  const Float min_x = std::fmin (min_.X (), p.X ());
  const Float max_x = std::fmax (max_.X (), p.X ());
  const Float min_y = std::fmin (min_.Y (), p.Y ());
  const Float max_y = std::fmax (max_.Y (), p.Y ());
  *this = Bounds2f (Point2f (min_x, min_y), Point2f (max_x, max_y));
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::Diagonal () const noexcept -> Float
{
  return (max_ - min_).Length ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::Expand (Float delta) noexcept -> void
{
  const Point2f min = Point2f (min_.X () - delta, min_.Y () - delta);
  const Point2f max = Point2f (max_.X () + delta, max_.Y () - delta);
  *this = Bounds2f (min, max);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::Lerp (const Point2f &t) const noexcept -> Point2f
{
  return Point2f (niepce::Lerp (t.X (), min_.X (), max_.X ()),
                  niepce::Lerp (t.Y (), min_.Y (), max_.Y ()));
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
auto Bounds2f::SurfaceArea () const noexcept -> Float
{
  return Width () * Height ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::Width () const noexcept -> Float
{
  return max_.X () - min_.X ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds2f::Height () const noexcept -> Float
{
  return max_.Y () - min_.Y ();
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
