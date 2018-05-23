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
    Float z_position_;       // Position of z-component
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
  // Return the distance from film to rear/front
  auto LensRear  () const -> Float { return lens_.back ().thickness_; }
  auto LensFront () const -> Float
  {
    Float sum = 0;
    for (const auto& element : lens_) { sum += element.thickness_; }
    return sum;
    return -lens_.front ().z_position_;
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
