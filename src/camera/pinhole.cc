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
PinholeCamera::PinholeCamera
(
 const Transform &camera_to_world,
 Float            sensor_to_lens, // [m]
 Float            focal_length,   // [m]
 Float            lens_radius,    // [m]
 const char      *lens_aperture,
 const char      *output,
 int              resolution_width,
 int              resolution_height,
 Float            physical_diagonal
) :
  Camera (camera_to_world,
          output,
          "",
          resolution_width,
          resolution_height,
          physical_diagonal),
  focal_length_   (focal_length),
  lens_radius_    (lens_radius),
  sensor_to_lens_ (sensor_to_lens),
  aperture_       (lens_aperture)
{
  // Compute the distance between lens to object plane by thin lens equation.
  lens_to_object_ = (focal_length_ * sensor_to_lens_)
                  / (sensor_to_lens_ - focal_length_);
}
/*
// ---------------------------------------------------------------------------
*/
auto PinholeCamera::GenerateRay (const CameraSample& samples, Ray *ray)
  const -> Float
{
  // Sample a point on film (image sensor).
  const auto sx = samples.film_.X () / static_cast <Float> (film_.Width ());
  const auto sy = samples.film_.Y () / static_cast <Float> (film_.Height ());
  const auto sf = film_.PhysicalBounds ().Lerp (Point2f (sx, sy));
  const auto pfilm = Point3f (-sf.X (), sf.Y (), -sensor_to_lens_);

  // Sample a point on lens. [-1, 1]
  auto plens = Point3f::Zero ();
  if (lens_radius_ > 0)
  {
    const auto s = SampleConcentricDisk (samples.lens_);
    plens = lens_radius_ * Point3f (s.X (), s.Y (), 0.0);
  }

  // Compute a point on object plane.
  const auto dir  = Normalize (plens - pfilm);
  const auto t    = lens_to_object_ / dir.Z ();
  const auto pobj = plens + dir * t;

  // Compute a ray in camera coordinate.
  *ray = Ray (plens, pobj - plens);

  // Pdf of sampling a pixel on the film.
  const auto pdf_pixel = 1.0 / (film_.Width () * film_.Height ());

  // Pdf of sampling a point on the lens.
  const auto pdf_lens = 1.0 / (lens_radius_ * lens_radius_ * kPi);

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
  if (aperture_.At (x, y))
  {
    return Point2f (sample[0] * 2.0 - 1.0, sample[1] * 2.0 - 1.0);
  }
  return Point2f (0, 0);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreatePinholeCamera (const Attributes& attrs)
  -> std::shared_ptr <Camera>
{
  const auto t = LookAt (attrs.FindPoint3f  ("origin"),
                         attrs.FindPoint3f  ("target"),
                         attrs.FindVector3f ("up"));

  const auto sensor_to_lens = attrs.FindFloat ("film_to_lens");
  const auto focal_length   = attrs.FindFloat ("focal_length");
  const auto lens_radius    = attrs.FindFloat ("lens_radius");


  const auto width    = attrs.FindInt ("width");
  const auto height   = attrs.FindInt ("height");
  const auto diagonal = attrs.FindFloat ("diagonal");
  const auto output   = attrs.FindString ("output");
  const auto back     = attrs.FindString ("background");
  const auto aperture = attrs.FindString ("aperture");

  return std::make_shared <PinholeCamera> (t,
                                           sensor_to_lens, // [m]
                                           focal_length,   // [m]
                                           lens_radius,    // [m]
                                           aperture.c_str (),
                                           output.c_str (),
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
