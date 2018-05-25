/*!
 * @file realistic_camera.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _REALISTIC_CAMERA_H_
#define _REALISTIC_CAMERA_H_
/*
// ---------------------------------------------------------------------------
*/
#include "camera.h"
#include "../core/ray.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*!
 * ----------------------------------------------------------------------------
 * @class RealisticCamera
 * @brief
 * @details
 * ----------------------------------------------------------------------------
*/
class RealisticCamera : public Camera
{
public:
  struct LensElement
  {
    Float curvature_radius_; // (m)
    Float thickness_;        // (m)
    Float ior_;
    Float aperture_radius_;  // (m)

    Float center_z_;         // (m)
  };

public:
  //! The default class constructor.
  RealisticCamera () = default;

  //! The constructor takes
  RealisticCamera
  (
   const Transform& camera_to_world,
   const char* lens_file_path,
   Float focus_distance,
   Float aperture_diameter,
   bool  simple_weighting
  );

  //! The copy constructor of the class.
  RealisticCamera (const RealisticCamera& camera) = default;

  //! The move constructor of the class.
  RealisticCamera (RealisticCamera&& camera) = default;

  //! The default class destructor.
  virtual ~RealisticCamera () = default;

  //! The copy assignment operator of the class.
  auto operator = (const RealisticCamera& camera) -> RealisticCamera& = default;

  //! The move assignment operator of the class.
  auto operator = (RealisticCamera&& camera) -> RealisticCamera& = default;

public:
  /*!
   * @fn Ray GenerateRay ()
   * @brief Generate the ray from camera.
   * @return 
   * @exception none
   * @details
   */
  auto GenerateRay () const -> Ray override final
  {}

public:
  // Return the distance from film to rear/front
  auto LensRear  () const -> Float
  {
    // Distance to surface of rear lens.
    return lens_.back ().thickness_;
  }
  auto LensFront () const -> Float
  {
    Float sum = 0;
    for (const auto& element : lens_) { sum += element.thickness_; }
    return sum;
  }

  // Return the aperture radius
  auto RearElementRadius () const -> Float
  {
    return lens_.back ().aperture_radius_;
  }

  // Compute the z-component of focus point and principal plane.
  auto ComputeCardinalPoints
  (
   const Ray& in,
   const Ray& out,
   Float* focus_point,
   Float* principal_plane
  )
  const -> void;

  // First  : Film to scene
  // Second : Scene to film
  auto ComputeThickLensApproximation
  (
   std::pair <Float, Float>* fz, // Focus points
   std::pair <Float, Float>* pz  // Principal plane
  )
  const -> void;

  // Load lens file
  auto AttachLens (const char* filename) noexcept -> void;

  auto TraceLensesFromFilm
  (
   const Ray& ray, // Camera coordinates
         Ray* out  // Camera coordinates
  )
  const -> bool;

  auto TraceLensesFromScene
  (
   const Ray& ray, // Camera coordinate
         Ray* out  // Camera coordinate
  )
  const -> bool;

  auto Dump () const -> void
  {
    // Dump left to right
    for (int i = lens_.size () - 1; i >= 0; --i)
    {
      std::cout << "Center of z      : " << lens_[i].center_z_ << "\n"
                << "Curvature radius : " << lens_[i].curvature_radius_ << "\n"
                << "Aperture radius  : " << lens_[i].aperture_radius_ << "\n"
                << std::endl;
    }
  }

private:
  auto CanRayThroughSphericalElement
  (
   const Ray& in, // Lens coordinate
   const LensElement& lens_element
  )
  const -> Intersection;

  auto CanRayThroughApertureElement
  (
   const Point3f&     position,
   const LensElement& lens_element
  )
  const -> bool;

private:
  const Float aperture_diameter_;
  const Transform camera_to_world_;
  const bool simple_weighting_;
  std::vector <LensElement> lens_;

}; // class RealisticCamera
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _REALISTIC_CAMERA_H_
