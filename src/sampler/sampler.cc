/*!
 * @file sampler.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "sampler.h"
#include "../core/imageio.h"
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
auto SampleCosineHemisphere (const Point2f& sample) -> Vector3f
{
  const Float phi = sample[0] * 2.0 * kPi;
  const Float r2  = sample[1];
  const Float r2s = std::sqrt(r2);
  const Float tx  = r2s * cos(phi);
  const Float ty  = r2s * sin(phi);
  const Float tz  = std::sqrt(1 - r2);

  const Vector3f res
    = tz * Vector3f (0, 0, 1) + tx * Vector3f (1, 0, 0) + ty * Vector3f (0, 1, 0);

  // std::cout << res.X () << ", " << res.Y () << ", "<< res.Z () << std::endl;

  const Point2f d = SampleConcentricDisk (sample);
  const Float   z
    = std::sqrt (std::fmax (0.0, 1.0 - d.X () * d.X () - d.Y () * d.Y ()));

  return Vector3f (d.X (), d.Y (), z);
}
/*
// ---------------------------------------------------------------------------
*/
auto SampleUniformTriangle (const Point2f& sample) -> Point2f
{
  const Float s = std::sqrt (sample[0]);
  return Point2f (1 - s, sample[1] * s);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
