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
 Float            fov,            // [degree]
 Float            lens_radius,    // [mm]
 Float            focus_distance, // [mm]
 const char*      output,
 const char*      background,
 const char*      aperture,
 unsigned int     resolution_width,
 unsigned int     resolution_height,
 Float            diagonal        // [mm]
) :
  Camera (camera_to_wrold,
          output,
          background,
          resolution_width,
          resolution_height,
          diagonal),
  lens_radius_     (lens_radius)
{
  focal_length_   = diagonal / (2.0 * std::tan (DegreeToRadian (fov / 2.0)));
  sensor_to_lens_ = (focus_distance * focal_length_)
                  / (focus_distance - focal_length_);
  lens_to_object_ = focus_distance;

  ImageIO <bool> aperture_img (aperture);
  const auto width  = static_cast <Float> (aperture_img.Width ());
  const auto height = static_cast <Float> (aperture_img.Height ());
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      if (aperture_img.At (x, y))
      {
        const auto nx = x / width  * 2.0 - 1.0;
        const auto ny = y / height * 2.0 - 1.0;
        aperture_.push_back (Point2f (nx, ny));
      }
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto PinholeCamera::GenerateRay (const CameraSample& samples, Ray *ray)
  const -> Float
{
  // Sample a point on film (image sensor).
  const auto sx = samples.film_.X () / (film_.Width ()  - 1.0);
  const auto sy = samples.film_.Y () / (film_.Height () - 1.0);
  const auto sf = film_.PhysicalBounds ().Lerp (Point2f (sx, sy));
  const auto pfilm = Point3f (-sf.X (), sf.Y (), -sensor_to_lens_);

  // Sample a point on lens. [-1, 1]
  auto plens = Point3f::Zero ();
  if (lens_radius_ > 0)
  {
    const auto s = SampleOnApertureByImage (samples.lens_);
    // const auto s = SampleConcentricDisk (samples.lens_);
    plens = lens_radius_ * Point3f (s.X (), s.Y (), 0.0);
  }

  // Compute a point on object plane.
  const auto dir  = Normalize (Point3f::Zero () - pfilm);
  const auto ft   = lens_to_object_ / dir.Z ();
  const auto pobj = Point3f::Zero () + dir * ft;

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
  const int idx = sample[0] * (aperture_.size () - 1.0);
  return aperture_[idx];
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

  const auto fov = attrs.FindFloat ("fov");
  const auto d   = attrs.FindFloat ("focus_distance");
  const auto r   = attrs.FindFloat ("lens_radius");


  const auto width    = attrs.FindInt ("width");
  const auto height   = attrs.FindInt ("height");
  const auto diagonal = attrs.FindFloat ("diagonal");
  const auto output   = attrs.FindString ("output");
  const auto back     = attrs.FindString ("background");
  const auto aperture = attrs.FindString ("aperture");

  return std::make_shared <PinholeCamera> (t,
                                           fov,
                                           r,
                                           d,
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
