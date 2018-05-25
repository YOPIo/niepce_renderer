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
 const char* lens_file_path,
 Float focus_distance,
 Float aperture_diameter,
 bool  simple_weighting
) :
  camera_to_world_   (camera_to_world),
  simple_weighting_  (simple_weighting),
  aperture_diameter_ (aperture_diameter)
{
  AttachLens (lens_file_path);
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::TraceLensesFromFilm
(
 const Ray& ray, // Camera coordinates
       Ray* out  // Camera coordinates
)
  const -> bool
{
  Float element_z = 0;

  // Transform $ray$ in camera coordinate to lens coordinate.
  static const Transform camera_to_lens (Scale (1, 1, -1));
  Ray lens_ray (camera_to_lens * ray);

  for (unsigned int i = lens_.size () - 1; i > 0; --i)
  {
    // Get a i'th lens element.
    const LensElement& element = lens_[i];

    // Update ray
    element_z -= element.thickness_;

    // Intersection test (ray and lens element).
    Intersection intersection;
    const bool is_aperture_stop = (element.curvature_radius_ == 0);
    if (is_aperture_stop)
    {
      // Next element is aperture stop.
      const Float t = (element_z - lens_ray.Origin ().Z ())
                    / lens_ray.Direction ().Z ();
      intersection.SetDistance (t);
    }
    else
    {
      // Next element is convex or concave lens.
      intersection =  CanRayThroughSphericalElement (lens_ray, element);
      if (!intersection)
      {
        // Ray cannot pass through a lens.
        return false;
      }
    }

    if (!CanRayThroughApertureElement (intersection.Position (), element))
    {
      // Ray cannot intersect at the outside of aperture.
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
        // Total reflection has occurred.
        lens_ray = Ray (intersection.Position (), w);
      }
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
auto RealisticCamera::TraceLensesFromScene
(
 const Ray& ray,
       Ray* out
)
  const -> bool
{
  Float element_z = -LensFront ();

  // Transform $ray$ in camera coordinate to lens coordinate.
  static const Transform camera_to_lens (Scale (1, 1, -1));
  Ray lens_ray (camera_to_lens * ray);

  for (unsigned int i = 0; i < lens_.size () ; ++i)
  {
    // Get a i'th lens element.
    const LensElement& element = lens_[i];

    // Intersection test (ray and lens element).
    Intersection intersection;
    const bool is_aperture_stop = (element.curvature_radius_ == 0);
    if (is_aperture_stop)
    {
      // Next element is aperture stop.
      const Float t = (element_z - lens_ray.Origin ().Z ())
                    / lens_ray.Direction ().Z ();
      intersection.SetDistance (t);
    }
    else
    {
      // Next element is convex or concave lens.
      intersection =  CanRayThroughSphericalElement (lens_ray, element);
      if (!intersection)
      {
        // Ray cannot pass through a lens.
        return false;
      }
    }

    if (!CanRayThroughApertureElement (intersection.Position (), element))
    {
      // Ray cannot intersect at the outside of aperture.
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
        // Total reflection has occurred.
        lens_ray = Ray (intersection.Position (), w);
      }
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
auto RealisticCamera::CanRayThroughSphericalElement
(
 const Ray& ray, // Lens coordinate
 const LensElement& lens_element
)
  const -> Intersection
{
  Intersection intersection;

  const Vector3f& d = ray.Direction ();
  const Point3f&  o = ray.Origin ();

  const Float& curvature_radius = lens_element.curvature_radius_;
  const Float& aperture_radius  = lens_element.aperture_radius_;

  const Vector3f op = o - Point3f (0, 0, lens_element.center_z_);
  const Float a = d.X () * d.X () + d.Y () * d.Y () + d.Z () * d.Z ();
  const Float b = 2 * (d.X () * op.X () + d.Y () * op.Y () + d.Z () * op.Z ());
  const Float c = op.X () * op.X () + op.Y () * op.Y () + op.Z () * op.Z ()
                - curvature_radius * curvature_radius;
  // Solve quadratic equation
  Float t, t1, t2;
  if (!SolveQuadratic (a, b, c, &t1, &t2))
  {
    // Ray does not intersect with i'th lens.
    return intersection;
  }

  // Select a $t$ based on lens element and ray direction.
  const bool use_closer = (d.Z () > 0) ^ (curvature_radius < 0);
  t = use_closer ? std::min (t1, t2) : std::max (t1, t2);
  if (t < 0)
  {
    return intersection;
  }

  // Compute surface normal of element at ray intersection position.
  Vector3f normal = Normalize (op + t * d);
  normal = (Dot (normal, -d) < 0.f) ? -normal : normal;

  // Store intersection info.
  intersection.SetDistance (t);
  intersection.SetPosition (ray.IntersectAt (t));
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
  const -> bool
{
  const Float& aperture_radius = lens_element.aperture_radius_;

  // Compute the position of intersection.
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
auto RealisticCamera::ComputeThickLensApproximation
(
 std::pair<Float, Float>* fz,
 std::pair<Float, Float>* pz
)
  const -> void
{
  // Find height x from optical axis for parallel rays

  // Compute cardinal points for film side fo lens system
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::ComputeCardinalPoints
(
 const Ray& in,
 const Ray& out,
 Float* focus_point,     // Z-component of focus point
 Float* principal_plane  // Z-component of principal plane
)
  const -> void
{
  // $ t_f = -\frac{o_x}{d_x} $
  const Float tf = -out.Origin ().X () / out.Direction ().X ();
  *focus_point = out.IntersectAt (tf).Z ();

  // $ t_p = \frac{x - o_x}{d_x} $
  const Float tp = (in.Origin ().X () - out.Origin (). X ())
                 / out.Direction ().X ();
  *principal_plane = out.IntersectAt (tp).Z ();
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::AttachLens (const char* filename) noexcept -> void
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
    if (line[0] == '#')
    {
      // Comment begin with '#'.
      continue;
    }

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
    element.aperture_radius_  = float_token[3] * 0.001 / 2.0;

    if (element.curvature_radius_ == 0)
    {
      element.aperture_radius_ = aperture_diameter_ / 2.0;
    }

    lens_.push_back (element);
  }

  // Initialize center of z-component.
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
}  // namespace niepce
