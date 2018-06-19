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
 const char*      filename,
 unsigned int     resolution_width,
 unsigned int     resolution_height,
 Float            diagonal
) :
  Camera (camera_to_wrold,
          filename,
          resolution_width,
          resolution_height,
          diagonal),
  lens_radius_     (lens_radius),
  object_distance_ (focus_distance)
{
  // Compute the distance from camera position to film.
  const Float theta = ToRadian (fov * 0.5);
  focal_distance_
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
  const Point3f pfilm = Point3f (-p.X (), p.Y (), -focal_distance_);

  // Generate a ray from 0 to point on film plane.
  *ray = Ray (Point3f::Zero (), Point3f::Zero () - pfilm);

  if (lens_radius_ > 0)
  {
    // Sample a point on lens
    const Point2f s = SampleConcentricDisk (samples.lens_);
    const Point3f plens = lens_radius_ * Point3f (s.X (), s.Y (), 0);

    // Compute a point on object plane.
    const Float t = object_distance_ / ray->Direction ().Z ();
    const Point3f pfocus = ray->IntersectAt (t);

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
auto CreatePinholeCamera (const Attributes& attributes)
  -> std::shared_ptr <Camera>
{
  const Transform t = LookAt (attributes.FindPoint3f  ("origin"),
                              attributes.FindPoint3f  ("target"),
                              attributes.FindVector3f ("up"));

  const Float fov = attributes.FindFloat ("fov");
  const Float lens_radius = attributes.FindFloat ("lens_radius");
  const Float focus_distance = attributes.FindFloat ("focus_distance");

  const int   width    = attributes.FindInt ("width");
  const int   height   = attributes.FindInt ("height");
  const Float diagonal = attributes.FindFloat ("diagonal");
  const std::string filename = attributes.FindString ("filename");
  return std::make_shared <PinholeCamera> (t,
                                           fov,
                                           lens_radius,
                                           focus_distance,
                                           filename.c_str (),
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
