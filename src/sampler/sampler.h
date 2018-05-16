/*!
 * @file sampler.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _SAMPLER_H_
#define _SAMPLER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/point2f.h"
#include "../core/point3f.h"
#include "../core/vector2f.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto SampleConcentricDisk (const Point2f& sample) -> Point2f
{
  // Map uniform random numbers to [-1, 1]^2
  const Vector2f offset (2.0 * sample - Point2f (1));

  // Handle degeneracy at the origin
  if (offset.X () == 0 && offset.Y () == 0) { return Point2f (0); }

  Float r, theta;
  if (std::abs (offset.X ()) > std::abs (offset.Y ()))
  {
    r     = offset.X ();
    theta = kPi / 4.0 * (offset.Y () / offset.X ());
  }
  else
  {
    r     = offset.Y ();
    theta = kPi / 2.0 - kPi / 4.0 * (offset.X () / offset.Y ());
  }
  return r * Point2f (std::cos (theta), std::sin (theta));
}
/*
// ---------------------------------------------------------------------------
*/
auto SampleCosineHemisphere (const Point2f& sample) -> Point3f
{
  const Point2f d = SampleConcentricDisk (sample);
  const Float   y
    = std::sqrt (std::fmax (0.0, 1.0 - d.X () * d.X () - d.Y () * d.Y ()));

  return Point3f (d.X (), y, d.Y ());
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SAMPLER_H_
