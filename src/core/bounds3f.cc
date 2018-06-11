/*!
 * @file bounds3f.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bounds3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Bounds3f::Bounds3f (const Point3f& p1, const Point3f& p2)
{
  const Float minx = std::fmin (p1.X (), p2.X ());
  const Float miny = std::fmin (p1.Y (), p2.Y ());
  const Float minz = std::fmin (p1.Z (), p2.Z ());
  const Float maxx = std::fmax (p1.X (), p2.X ());
  const Float maxy = std::fmax (p1.Y (), p2.Y ());
  const Float maxz = std::fmax (p1.Z (), p2.Z ());

  min_ = Point3f (minx, miny, minz);
  max_ = Point3f (maxx, maxy, maxz);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Center () const noexcept -> Point3f
{
  return Point3f ((min_.X () + max_.X ()) * 0.5,
                  (min_.Y () + max_.Y ()) * 0.5,
                  (min_.Z () + max_.Z ()) * 0.5);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Diagonal () const noexcept -> Vector3f
{
  return max_ - min_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Min () const noexcept -> Point3f
{
  return min_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Max () const noexcept -> Point3f
{
  return max_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::SetMin (const Point3f& p) noexcept -> void
{
  min_ = p;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::SetMax (const Point3f& p) noexcept -> void
{
  max_ = p;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::SurfaceArea () const noexcept -> Float
{
  const Vector3f d = Diagonal ();
  return 2.0 * d.X () * d.Y ()
         + 2.0 * d.Y () * d.Z ()
         + 2.0 * d.Z () * d.X ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Merge (const Bounds3f& bounds) -> void
{
  const Point3f& min = bounds.Min ();
  const Point3f& max = bounds.Max ();

  const Float minx = std::fmin (min_.X (), min.X ());
  const Float miny = std::fmin (min_.Y (), min.Y ());
  const Float minz = std::fmin (min_.Z (), min.Z ());
  const Float maxx = std::fmax (max_.X (), max.X ());
  const Float maxy = std::fmax (max_.Y (), max.Y ());
  const Float maxz = std::fmax (max_.Z (), max.Z ());

  min_ = Point3f (minx, miny, minz);
  max_ = Point3f (maxx, maxy, maxz);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Merge (const Point3f& p) -> void
{
  const Float minx = std::fmin (min_.X (), p.X ());
  const Float miny = std::fmin (min_.Y (), p.Y ());
  const Float minz = std::fmin (min_.Z (), p.Z ());
  const Float maxx = std::fmax (max_.X (), p.X ());
  const Float maxy = std::fmax (max_.Y (), p.Y ());
  const Float maxz = std::fmax (max_.Z (), p.Z ());
  min_ = Point3f (minx, miny, minz);
  max_ = Point3f (maxx, maxy, maxz);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
