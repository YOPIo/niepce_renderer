/*!
 * @file realistic_camera.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "realistic_camera.h"
#include "../core/utilities.h"
#include "../core/ray.h"
#include "../core/transform.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
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
    Float t;
    Vector3f normal;

    const bool is_aperture_stop = (element.curvature_radius_ == 0);
    if (is_aperture_stop)
    {
      // Next element is aperture stop.
      t = (element_z - lens_ray.Origin ().Z ()) / lens_ray.Direction ().Z ();
    }
    else
    {
      // Next element is convex or concave lens.
      
    }

    // Intersection test again (ray position and element aperture).

    // Update ray path.
  }

  /*
  // ---------------------------------------------------------------------------
  */
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto RealisticCamera::IntersectWithLensElement
(
   Float radius,
   Float center,
   const Ray& ray,
   Float* t,
   Vector3f* normal
)
  const -> bool
{
  const Vector3f& d = ray.Direction ();
  const Point3f&  o = ray.Origin ();

  const Vector3f op = o - Point3f (0, 0, center);

  const Float a = d.X () * d.X () + d.Y () * d.Y () + d.Z () * d.Z ();
  const Float b = 2 * (d.X () * op.X () + d.Y () * op.Y () + d.Z () * op.Z ());
  const Float c = op.X () * op.X () + op.Y () * op.Y () + op.Z () * op.Z ()
                - radius * radius;
  // Solve quadratic equation
  Float t1, t2;
  if (!SolveQuadratic (a, b, c, &t1, &t2))
  {
    // Ray does not intersect with i'th lens.
    return false;
  }

  // Select a $t$ based on lens element and ray direction.
  const bool use_closer = (d.Z () > 0) ^ (radius < 0);
  *t = use_closer ? std::min (t1, t2) : std::max (t1, t2);
  if (*t < 0)
  {
    return false;
  }

  // Compute the position of intersection.
  const Point3f hit_position = ray.IntersectAt (*t);
  
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
