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
/*
// ---------------------------------------------------------------------------
*/
/*
                                              x
                                              |
                                              |
                                              |
  Scene --------------------------------------|-----> z Film
                                              |
                                              |
                                              |
*/
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
  RealisticCamera () = delete;

  //! The constructor takes
  RealisticCamera
  (
   const Transform& camera_to_world,
   const char*  output,
   const char*  background,
   unsigned int width,
   unsigned int height,
   Float diagonal, // [m]
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
  auto GenerateRay
  (
   const CameraSample& samples,
         Ray*          ray
  )
  const -> Float override final;

public:
  // public:
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
   * @fn void ComputeExitPupilBounds ()
   * @brief 
   * @param[in] begin_x
   *    
   * @param[in] last_x
   *    
   * @return 
   * @exception none
   * @details
   */
  auto PrecomputeExitPupilBounds (Float begin_x, Float last_x)
    const noexcept -> Bounds2f;

  /*!
   * @fn Float FocusOn ()
   * @brief 
   * @param[in] focus_distance
   *    
   * @return 
   * @exception none
   * @details
   */
  auto FocusOn (Float focus_distance) -> void;

  /*!
   * @fn Float SampleExitPupil ()
   * @brief 
   * @param[in] 
   *    
   * @return 
   * @exception none
   * @details
   */
  auto SampleExitPupil
  (
   const Point2f& pfilm,
   const Point2f& plens,
   Float* bound_area
  )
  const noexcept -> Point3f;

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

  /*!
   * @fn bool CanRayThroughApertureelement (const Point3f&, const LensElement&)
   * @brief 
   * @param[in] position
   *
   * @param[in] lens_element
   *
   * @return 
   * @exception none
   * @details
   */
  auto CanRayThroughApertureElement
  (
   const Point3f&     position,
   const LensElement& lens_element
  )
  const noexcept -> bool;

  /*!
   * @fn void LoadLens (const)
   * @brief 
   * @param[in] filename
   *    
   * @param[in] aperture_diameter
   *    
   * @return 
   * @exception none
   * @details
   */
  auto LoadLens
  (
   const char* filename,
   Float aperture_diameter
  )
  -> void;

  // ---------------------------------------------------------------------------

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
public:
  auto RenderExitPupilFrom
  (
   const Point2f& film, // Camera coordinate
   const char* filename
  )
  const noexcept -> void;

  auto Dump () const noexcept -> void
  {
    std::cout << "Dump" << std::endl;
    for (const auto& element : lens_)
    {
      std::printf ("%f, %f, %f, %f\n",
                   element.center_z_,
                   element.curvature_radius_,
                   -element.aperture_radius_,
                   element.aperture_radius_);
    }
    std::cout << std::endl << std::endl;;

    for (const auto& bounds : exit_pupils_)
    {
      std::cout << bounds.ToString() << std::endl;
    }
  }

private:
  const bool simple_weighting_;
  std::vector <LensElement> lens_;
  std::vector <Bounds2f> exit_pupils_;

}; // class RealisticCamera
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _REALISTIC_CAMERA_H_
