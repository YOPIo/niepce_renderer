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
  /*!
   * @fn bool CanRayThroughLensSystemFromFilm (const Ray&, Ray*) const noexcept
   * @brief 
   * @param[in] ray
   *    Ray in camera coordinate
   * @param[out] out
   *    Ray in camera coordinate that through pass the lens system.
   * @return bool
   * @exception none
   * @details 
   */
  auto CanRayThroughLensSystemFromFilm
  (
   const Ray& ray, // Camera coordinate
         Ray* out  // Camera coordinate
  )
  const noexcept -> bool;

  /*!
   * @fn bool CanRayThroughLensSystemFromScene (const Ray&, Ray*) const noexcept
   * @brief 
   * @param[in] ray
   *    Ray in camera coordinate
   * @param[out] out
   *    Ray in camera coordinate that through pass the lens system.
   * @return bool
   * @exception none
   * @details 
   */
  auto CanRayThroughLensSystemFromScene
  (
   const Ray& ray, // Camera coordinate
         Ray* out  // Camera coordinate
  )
  const noexcept -> bool;

  /*!
   * @fn void ComputeCardinalPoints ()
   * @brief Compute the focus point and principal plane.
   * @param[in] in
   *
   * @prarm[in] out
   *
   * @return 
   * @exception none
   * @details 
   */
  auto ComputeCardinalPoints
  (
   const Ray& in,  // First ray.
   const Ray& out, // Refracted ray through lens system.
   Float* fz,      // Z-component of focus point.
   Float* pz       // Z-component of principal plane.
  )
  const noexcept -> void;

  /*!
   * @fn void ComputeThickLensApproximation (std::pair <Float, Float>*, std::pair <Float, Float>*)
   * @brief 
   * @param[in] in
   *    Pair of focus point and principal plane.
   * @param[in] out
   *    Pair of focus point and principal plane.
   * @return 
   * @exception none
   * @details 
   */
  auto ComputeThickLensApproximation
  (
   // focus point, principal plane.
   std::array <Float, 2>* in,
   std::array <Float, 2>* out
  )
  const noexcept -> void;


private:
  /*!
   * @fn bool CanRAyThroughSphericalElement (const Ray&, const LensElement&)
   * @brief 
   * @param[in] ray
   *    Ray in lens coordiante
   * @param[in] element
   *    Lens element
   * @return bool
   * @exception none
   * @details 
   */
  auto CanRayThroughSphericalElement
  (
   const Ray& ray,
   const LensElement& element
  )
  const noexcept -> Intersection;

  // ---------------------------------------------------------------------------


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

  auto CanRayThroughApertureElement
  (
   const Point3f&     position,
   const LensElement& lens_element
  )
  const -> bool;

private:
  const Float aperture_diameter_;
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
