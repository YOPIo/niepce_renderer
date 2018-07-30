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
#include "../sampler/sampler.h"
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
 Float            lens_radius,
 Float            focus_distance,
 const char*      output,
 const char*      background,
 const char*      aperture,
 unsigned int     resolution_width,
 unsigned int     resolution_height,
 Float            diagonal
) :
  Camera (camera_to_wrold,
          output,
          background,
          resolution_width,
          resolution_height,
          diagonal),
  object_distance_ (focus_distance),
  lens_radius_     (lens_radius),
  aperture_        (aperture)
{
  // Compute the distance from camera position to film.
  const Float theta = DegreeToRadian (fov * 0.5);
  focal_distance_
    = std::fabs ((film_.PhysicalBounds ().Width () * 0.5) / std::tan (theta));
}
/*
// ---------------------------------------------------------------------------
*/
auto PinholeCamera::GenerateRay (const CameraSample& samples, Ray *ray)
  const -> Float
{
  // Sample a point on film plane.
  const auto &resolution = film_.Resolution ();
  const auto s = Point2f (samples.film_.X () / (Float)resolution.Width (),
                          samples.film_.Y () / (Float)resolution.Height ());
  const auto p = film_.PhysicalBounds ().Lerp (s);
  const auto pfilm = Point3f (-p.X (), p.Y (), -focal_distance_);

  // Generate a ray from 0 to point on film plane.
  *ray = Ray (Point3f::Zero (), Point3f::Zero () - pfilm);

  if (lens_radius_ > 0)
  {
    // Sample a point on lens
    const auto s     = SampleConcentricDisk (samples.lens_);
    // const auto s = SampleOnApertureByImage (samples.lens_);
    if (s == Point2f (0)) { return 0; }
    const auto plens = lens_radius_ * Point3f (s.X (), s.Y (), 0);

    // Compute a point on object plane.
    const auto t      = object_distance_ / ray->Direction ().Z ();
    const auto pfocus = ray->IntersectAt (t);

    // Update ray
    *ray = Ray (plens, pfocus - plens);
  }

  // Transform to world coordinate.
  *ray = camera_to_world_ * (*ray);

  return 1.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto PinholeCamera::SampleOnApertureByImage (const Point2f &sample)
  const noexcept -> Point2f
{
  const auto x = sample[0] * (Float)aperture_.Width ();
  const auto y = sample[1] * (Float)aperture_.Height ();
  if (!aperture_.At (x, y))
  {
    return Point2f (sample);
  }
  return Point2f (0, 0);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreatePinholeCamera (const Attributes& attributes)
  -> std::shared_ptr <Camera>
{
  const auto t = LookAt (attributes.FindPoint3f  ("origin"),
                         attributes.FindPoint3f  ("target"),
                         attributes.FindVector3f ("up"));

  const auto fov = attributes.FindFloat ("fov");
  const auto lens_radius = attributes.FindFloat ("lens_radius");
  const auto focus_distance = attributes.FindFloat ("focus_distance");

  const auto width    = attributes.FindInt ("width");
  const auto height   = attributes.FindInt ("height");
  const auto diagonal = attributes.FindFloat ("diagonal");
  const auto output   = attributes.FindString ("output");
  const auto back     = attributes.FindString ("background");
  const auto aperture = attributes.FindString ("aperture");

  return std::make_shared <PinholeCamera> (t,
                                           fov,
                                           lens_radius,
                                           focus_distance,
                                           output.c_str (),
                                           back.c_str (),
                                           aperture.c_str (),
                                           width,
                                           height,
                                           diagonal);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
