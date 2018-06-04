/*!
 * @file realistic_camera.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "realistic_camera.h"
#include "../bsdf/bsdf.h"
#include "../core/utilities.h"
#include "../core/ray.h"
#include "../core/transform.h"
#include "../core/intersection.h"
#include "../core/bounds2f.h"
#include "../core/vector2f.h"
#include "../sampler/low_discrepancy_sequence.h"
#include "../core/imageio.h"
#include "../core/thread_pool.h"
#include "../core/singleton.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
RealisticCamera::RealisticCamera
(
   const Transform& camera_to_world,
   const char* filename,
   unsigned int width,
   unsigned int height,
   Float diagonal, // [mm]
   const char* lens_file_path,
   Float focus_distance,
   Float aperture_diameter,
   bool  simple_weighting
) :
  Camera (camera_to_world, filename, width, height, diagonal),
  simple_weighting_  (simple_weighting)
{
  // Load a lens system file.
  // Converting focus distance unit to m from mm.
  LoadLens (lens_file_path, aperture_diameter * 0.001);

  // Compute focus distance.
  const Float delta = FocusOn (focus_distance);
  lens_.back ().thickness_ = delta;
  for (auto& element : lens_)
  {
    element.center_z_ -= delta;
  }

  /*
  // Precomputing exit pupil bounds
  constexpr static int kSamples = 64;
  exit_pupil_bounds_.resize (kSamples);
  std::vector <std::future<Bounds2f>> futures (kSamples);

  ThreadPool& pool = Singleton <ThreadPool>::Instance ();
  for (int i = 0; i < kSamples; ++i)
  {
    const Float diagonal = film_->Diagonal ();
    const Float begin = static_cast <Float> (i) / kSamples * diagonal / 2.0;
    const Float end   = static_cast <Float> (i + 1) / kSamples * diagonal / 2.0;
    auto func = std::bind (&RealisticCamera::ComputeExitPupilBounds,
                           this,
                           std::placeholders::_1,
                           std::placeholders::_2);
    futures[i] = pool.Enqueue (func, begin, end);
  }

  // Wait for computing exit pupil bounds.
  for (auto& future : futures) { future.wait (); }

  // Copy bounds
  for (int i = 0; i < kSamples; ++i)
  {
    exit_pupil_bounds_[i] = futures[i].get ();
  }
  */
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::GenerateRay
(
 const CameraSample& samples,
       Ray*          ray
)
  const -> Float
{
  // Compute pixle position on film from sample.
  const Bounds2f& film_resolution = Resolution ();
  const Point2f s (samples.film_.X () / film_resolution.Width (),
                   samples.film_.Y () / film_resolution.Height ());
  const Point2f p = PhysicalBounds ().Lerp (s);
  const Point3f film (-p.X (), p.Y (), 0);

  // Sample point on exit pupil.
  Float exit_pupil_area;
  const Point3f rear = SampleExitPupil (Point2f (film.X (), film.Y ()),
                                        samples.lens_,
                                        &exit_pupil_area);

  // Generate ray in camera coordinate.
  const Ray camera_ray (film, rear - film);

  // Testing
  if (!CanRayThroughLensSystemFromFilm (camera_ray, ray))
  {
    // Sampled ray could not through lens system
    // Caller should check this case.
    return 0;
  }

  // Generated ray could through lens system.
  // Transform ray to world coordinate from camera coordinate.
  *ray = Ray (camera_to_world_ * (*ray));

  return 1;
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::CanRayThroughLensSystemFromFilm
(
 const Ray &ray,
       Ray *out
)
  const noexcept -> bool
{
  Float z = 0;

  // Transform $ray$ in camera coordinate to lens coordinate.
  static const Transform camera_to_lens (Scale (1, 1, -1));
  Ray lens_ray (camera_to_lens * ray);

  for (int i = lens_.size () - 1; i >= 0; --i)
  {
    // Get a i'th lens element.
    const LensElement& element = lens_[i];

    // Compute z-component of position of lens surface.
    z -= element.thickness_;

    // Intersection test. (Sphere)
    Intersection intersection;
    const bool is_aperture_stop = (element.curvature_radius_ == 0);
    if (is_aperture_stop)
    {
      // The refracted ray computed in the previous lens element
      // should be pointed toward -z direction.
      const Float t = (z - lens_ray.Origin ().Z ()) / lens_ray.Direction ().Z ();
      intersection.SetDistance (t);
      intersection.SetPosition (lens_ray.IntersectAt (t));
    }
    else
    {
      // Next element is convex or concave lens.
      intersection = CanRayThroughSphericalElement (lens_ray, element);
      if (!intersection) { return false; /* Ray cannot through. */ }
    }

    // Intersection test again. (Aperture)
    if (!CanRayThroughApertureElement (intersection.Position (), element))
    {
      return false;
    }

    // Update ray path.
    if (!is_aperture_stop)
    {
      Vector3f w;
      const Float ior1 = element.ior_;
      const Float ior2 = (i > 0 && lens_[i - 1].ior_ != 0)
                       ? lens_[i - 1].ior_ : 1.0;
      if (!bsdf::Refract (Normalize (-lens_ray.Direction ()),
                          intersection.Normal (),
                          ior1,
                          ior2,
                          &w))
      {
        return false;
      }
      lens_ray = Ray (intersection.Position (), w);
    }
  }

  // Transform $ ray $ in lens coordinate to camera coordinate
  if (out != nullptr)
  {
    static const Transform lens_to_camera (Scale (1, 1, -1));
    *out = lens_to_camera * lens_ray;
  }

  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::CanRayThroughLensSystemFromScene
(
 const Ray& ray,
       Ray* out
)
  const noexcept -> bool
{
  Float z = -LensFront ();

  // Transform $ray$ in camera coordinate to lens coordinate.
  static const Transform camera_to_lens (Scale (1, 1, -1));
  Ray lens_ray (camera_to_lens * ray);

  // Loop rigthmost element to leftmost element in lens coordinate.
  for (int i = 0; i < lens_.size (); ++i)
  {
    // Get a i'th lens element.
    const LensElement& element = lens_[i];

    // Intersection test (Sphere).
    Intersection intersection;
    const bool is_aperture_stop = (element.curvature_radius_ == 0);
    if (is_aperture_stop)
    {
      // Next element is aperture stop.
      const Float t = (z - lens_ray.Origin ().Z ()) / lens_ray.Direction ().Z ();
      intersection.SetDistance (t);
    }
    else
    {
      // Next element is convex or concave lens.
      intersection =  CanRayThroughSphericalElement (lens_ray, element);
      if (!intersection) { return false; /* Ray cannot pass through a lens.*/ }
    }

    // Intersection test again. (Aperture)
    if (!CanRayThroughApertureElement (intersection.Position (), element))
    {
      // Ray cannot intersect at the outside of aperture.
      return false;
    }

    // Update ray path.
    if (!is_aperture_stop)
    {
      Vector3f w;
      const Float ior1 = (i == 0 || lens_[i - 1].ior_ == 0)
                       ? 1 : lens_[i - 1].ior_;
      const Float ior2 = lens_[i].ior_ != 0 ? lens_[i].ior_ : 1;
      if (!bsdf::Refract (Normalize (-lens_ray.Direction ()),
                          intersection.Normal (),
                          ior1,
                          ior2,
                          &w))
      {
        // Total reflection has occurred.
        return false;
      }
      lens_ray = Ray (intersection.Position (), w);
    }

    // Compute the position of i'th lens surface along the z-axis.
    z += element.thickness_;
  }

  // Transform $ ray $ in lens coordinate to camera coordinate
  if (out != nullptr)
  {
    static const Transform lens_to_camera (Scale (1, 1, -1));
    *out = lens_to_camera * lens_ray;
  }

  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::CanRayThroughSphericalElement
(
 const Ray& ray, // Lens coordinate
 const LensElement& lens_element
)
  const noexcept -> Intersection
{
  Intersection intersection;

  const Float& z      = lens_element.center_z_;
  const Float& radius = lens_element.curvature_radius_;

  const Vector3f op = Point3f (0, 0, z) - ray.Origin ();
  const Float    b  = Dot (op, ray.Direction ());
  const Float    c  = b * b - Dot (op, op) + radius * radius;

  if (c < 0.0) { return intersection; }

  const Float sqrt_c = std::sqrt (c);
  const Float t1 = b - sqrt_c;
  const Float t2 = b + sqrt_c;

  const Float t = ((radius < 0) ^ (ray.Direction ().Z () > 0))
                ? std::fmin (t1, t2) : std::fmax (t1, t2);
  if (t < 0)
  {
    std::cout << t1 << ", " << t2 << std::endl;
    return intersection;
  }

  // Compute the intersect position.
  const Point3f position = ray.IntersectAt (t);

  // Compute surface normal of element at ray intersection position.
  Vector3f normal
    = Normalize (position - Point3f (0, 0, lens_element.center_z_));
  // Normal vector should be always minus ray direction.
  normal = Dot (ray.Direction(), normal) > 0 ? -normal : normal;

  // Store intersection info.
  intersection.SetDistance (t);
  intersection.SetPosition (position);
  intersection.SetNormal (normal);
  intersection.MakeHitFlagTrue ();

  return intersection;
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::CanRayThroughApertureElement
(
 const Point3f&     position,
 const LensElement& lens_element
)
  const noexcept -> bool
{
  const Float& aperture_radius = lens_element.aperture_radius_;

  // ompute the position of intersection.
  const Float r2 = position.X () * position.X () + position.Y () * position.Y ();
  if (r2 > aperture_radius * aperture_radius)
  {
    // Ray intersected with a lens at the outside of aperture.
    return false;
  }
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::ComputeCardinalPoints
(
 const Ray& in,  // First ray.
 const Ray& out, // Refracted ray through lens system.
 Float* fz,      // Z-component of focus point.
 Float* pz       // Z-component of principal plane.
)
  const noexcept -> void
{
  // $ t_f = -\frac{o_x}{d_x} $
  const Float tf = -out.Origin ().X () / out.Direction ().X ();
  *fz = out.IntersectAt (tf).Z ();

  // $ t_p = \frac{x - o_x}{d_x} $
  const Float tp = (in.Origin ().X () - out.Origin (). X ())
                 / out.Direction ().X ();
  *pz = out.IntersectAt (tp).Z ();
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::ComputeExitPupilBounds (Float begin_x, Float last_x)
  const noexcept -> Bounds2f
{
  Bounds2f exit_bounds;

  // Sample the points to find the exit pupil at the segment.
  static constexpr int num_samples = 1024 * 1024;

  // The number of rays that exiting a lens system.
  int exiting_rays = 0;

  // The bounds of exit pupil prefer to bigger than perpendicular projection.
  const Float    rear_radius = RearElementRadius ();
  const Bounds2f rear_bounds (Point2f (-1.5 * rear_radius, -1.5 * rear_radius),
                              Point2f ( 1.5 * rear_radius,  1.5 * rear_radius));

  for (int i = 0; i < num_samples; ++i)
  {
    // Find positions of sample points on x segment and rear lens element.
    const Point3f origin (Lerp ((i + 0.5) / num_samples, begin_x, last_x), 0, 0);

    // Sample position on rear lens element bounding box.
    const Float tx = Lerp (RadicalInverse (2, i),
                           rear_bounds.Min ().X (),
                           rear_bounds.Max ().X ());
    const Float ty = Lerp (RadicalInverse (3, i),
                           rear_bounds.Min ().Y (),
                           rear_bounds.Max ().Y ());
    const Point3f target (tx, ty, LensRear ());

    // The sampled point on rear lens element is in exit pupil bounds.
    if (exit_bounds.IsInside (Point2f (tx, ty)))
    {
      exit_bounds.Append (Point2f (tx, ty));
      ++exiting_rays;
      continue;
    }

    // Construct a ray from point on the segment to rear lens element.
    const Ray ray (origin, target - origin);

    // Expand exit pupil bounds if ray through the lens system.
    if (CanRayThroughLensSystemFromFilm (ray, nullptr))
    {
      // Ray through the lens system.
      exit_bounds.Append (Point2f (tx, ty));
      ++exiting_rays;
    }
  }

  if (exiting_rays == 0)
  {
    // No ray from segment through lens system.
    return Bounds2f ();
  }

  // Expand a exit pupil bounds.
  exit_bounds.Expand (2.0 * rear_bounds.Diagonal ()
                      / std::sqrt (num_samples));

  return exit_bounds;
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::LoadLens
(
 const char* filename,
 Float aperture_diameter
)
  -> void
{
  std::ifstream ifs (filename);
  std::string line;

  if (!ifs)
  {
    std::cout << "Could not open " << filename << std::endl;
    return ;
  }

  // Clear lens.
  lens_.clear ();

  // Load a line.
  // Left to right.
  while (std::getline (ifs, line))
  {
    if (line[0] == '#') { /* Comment begin with '#'. */ continue; }

    // Parse by space and store.
    std::istringstream iss (line);
    std::vector <std::string> tokens {std::istream_iterator <std::string> (iss),
                                      std::istream_iterator <std::string> ()};
    if (tokens.size () != 4)
    {
      std::cout << "Invalid file format." << std::endl;
      return;
    }

    // Convert string to Float.x
    std::vector <Float> float_token;
    for (const auto& e : tokens)
    {
      float_token.push_back (std::atof (e.c_str ()));
    }

    // Create lens element object
    LensElement element;
    element.curvature_radius_ = float_token[0] * 0.001;
    element.thickness_        = float_token[1] * 0.001;
    element.ior_              = float_token[2];
    element.aperture_radius_  = float_token[3] / 2.0 * 0.001;

    if (element.curvature_radius_ == 0)
    {
      if (aperture_diameter / 2.0 > element.aperture_radius_)
      {
        // Since the specified size of aperture diameter is greater than maximum
        // size of aperture diameter, set the aperture size to maximum.
        std::cerr << "Since the specified size of aperture diameter is greater than maximum size of aperture diameter, set the aperture size to maximum." << std::endl;
        break;
      }
      element.aperture_radius_ = aperture_diameter / 2.0;
    }

    lens_.push_back (element);
  }

  // Initialize position of center.
  Float z = 0;
  for (int i = lens_.size () - 1; i >= 0; --i)
  {
    z -= lens_[i].thickness_;
    lens_[i].center_z_ = z + lens_[i].curvature_radius_;
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::SampleExitPupil
(
 const Point2f& pfilm,
 const Point2f& plens,
 Float* bound_area
)
  const noexcept -> Point3f
{
  // Find exit pupil bound from film center.

  // Compute index of exit pupil bound for sampling.
  const Float distance
    = std::sqrt (pfilm.X () * pfilm.X () + pfilm.Y () * pfilm.Y ());
  int index = distance / (Diagonal () / 2.0) * exit_pupil_bounds_.size ();
  index = std::min (index, static_cast <int> (exit_pupil_bounds_.size () - 1));

  // Get exit pupil bound
  const Bounds2f& bound = exit_pupil_bounds_[index];

  // Store a area of exit pupil for computing a weight if needed.
  if (bound_area) { *bound_area = bound.SurfaceArea (); }

  // Generate sample point inside exit pupil.
  const Point2f pbound = bound.Lerp (plens);

  // Rotate sampled point inside exit pupil by angle of pfilm with +x axis.
  const Float sin_theta = (distance != 0) ? pfilm.Y () / distance : 0;
  const Float cos_theta = (distance != 0) ? pfilm.X () / distance : 1;
  return Point3f (cos_theta * plens.X () - sin_theta * plens.Y (),
                  sin_theta * plens.X () - cos_theta * plens.Y (),
                  LensRear ());
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::FocusOn (Float focus_distance) -> Float
{
  // focus length
  Float f1, f2;

  // principal planes
  Float p1, p2;

  // Find the height x from optical axis for parallel rays.
  // Works well. (May be)
  const Float x = Diagonal () * 0.001;

  // Compute the focus point and principal plane. (film to scene)
  // Ray should be camera coordinate.
  Ray ray1 (Point3f  (x, 0, LensRear () - 1), // Origin
            Vector3f (0, 0, 1));              // Direction
  Ray out1;
  if (!CanRayThroughLensSystemFromFilm (ray1, &out1))
  {
    // TODO: Fix
    std::cout << "Error FucosOn." << std::endl;
    return -1;
  }
  ComputeCardinalPoints (ray1, out1, &f1, &p1);

  // Compute the focus and principal plane. (scene to film)
  // Ray should be camera coordinate.
  Ray ray2 (Point3f  (-x, 0, LensFront () + 1), // Origin
            Vector3f (0, 0, -1));               // Direction
  Ray out2;
  if (!CanRayThroughLensSystemFromScene (ray2, &out2))
  {
    // TODO: Fix
    std::cout << "Error FucosOn." << std::endl;
    return -1;
  }
  ComputeCardinalPoints (ray2, out2, &f2, &p2);

  // Compute translation of lens to fucus on.
  const Float f = f1 - p1;
  const Float z = -focus_distance;

  const Float delta
    = 0.5 * (p2 - z + p1 - std::sqrt ((p1 - z - p1) * (p1 - z - 4 * f - p1)));

  return delta;
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::RenderExitPupil
(
 const Point2f& film, // Camera coordinate
 const char* filename
)
  const noexcept -> void
{
  const Point3f point_on_film (film.X (), film.Y (), 0);
  const int     num_samples = 1024;
  const Float   radius = RearElementRadius ();

  ImageIO <Float> res (num_samples, num_samples);

  for (int y = 0; y < num_samples; ++y)
  {
    const Float fy = static_cast <Float> (y) /
                     static_cast <Float> (num_samples - 1);
    const Float ly = Lerp (fy, -radius, radius);

    for (int x = 0; x < num_samples; ++x)
    {
      const Float fx = static_cast <Float> (x) /
                       static_cast <Float> (num_samples - 1);
      const Float lx = Lerp (fx, -radius, radius);

      const Point3f target (lx, ly, LensRear ());
      if (lx * lx + ly * ly > radius * radius)
      {
        // Out of aperture.
        res.SetValueAt (x, y, 1);
        continue;
      }
      Ray ray (point_on_film, target - point_on_film);
      if (CanRayThroughLensSystemFromFilm (ray, nullptr))
      {
        // Found exit pupil
        res.SetValueAt (x, y, 0.5);
        continue;
      }
      // Ray cannot through lens system.
      res.SetValueAt (x, y, 0);
    }
  }

  res.SaveAs (filename);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
