/*!
 * @file pinhole.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "pinhole.h"
#include "../core/point3f.h"
#include "../core/vector3f.h"
#include "../core/ray.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
PinholeCamera::PinholeCamera
(
 const Transform& camera_to_wrold,
 Float            fov,
 const char*      filename,
 unsigned int     resolution_width,
 unsigned int     resolution_height,
 Float            diagonal
) :
  Camera (camera_to_wrold,
          filename,
          resolution_width,
          resolution_height,
          diagonal)
{
  // Compute the distance from camera position to film.
  const Float theta = ToRadian (fov * 0.5);
  distance_to_film_
    = std::fabs ((PhysicalBounds ().Width () * 0.5) / std::tan (theta));
}
/*
// ---------------------------------------------------------------------------
*/
auto PinholeCamera::GenerateRay (const CameraSample& samples, Ray *ray)
  const -> Float
{
  // Sample a point on film plane.
  const Bounds2f& resolution = Resolution ();
  const Point2f s (samples.film_.X () / resolution.Width (),
                   samples.film_.Y () / resolution.Height ());
  const Point2f p = PhysicalBounds ().Lerp (s);
  const Point3f pfilm = Point3f (-p.X (), p.Y (), -distance_to_film_);

  // Generate a ray from 0 to point on film plane.
  *ray = Ray (Point3f::Zero (), Point3f::Zero () - pfilm);

  // Transform to world coordinate.
  *ray = camera_to_world_ * (*ray);

  return 1.0;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
