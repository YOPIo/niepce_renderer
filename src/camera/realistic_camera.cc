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
 bool  simple_weighting
) :
  camera_to_world_  (camera_to_world),
  simple_weighting_ (simple_weighting)
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

  const Vector3f op = o - Point3f (0, 0, lens_element.z_position_);
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
auto RealisticCamera::AttachLens (const char* filename) noexcept -> void
{
  std::ifstream ifs (filename);
  std::string line;

  while (std::getline (ifs, line))
  {
    if (line[0] == '#')
    {
      // Comment begin with '#'.
      continue;
    }

    // Parse by space
    std::istringstream iss (line);
    std::vector <std::string> tokens {std::istream_iterator <std::string> (iss),
                                      std::istream_iterator <std::string> ()};

    for (const auto& t : tokens)
    {
      std::cout << t << " ";
    }
    std::cout << std::endl;
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
