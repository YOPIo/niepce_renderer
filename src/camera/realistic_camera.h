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
    Float curvature_radius_; // (mm)
    Float thickness_;        // (mm)
    Float ior_;
    Float aperture_radius_;  // (mm)
    Float z_position_;       // (mm)
  };

public:
  //! The default class constructor.
  RealisticCamera () = default;

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

  auto TraceLensesFromFilm
  (
   const Ray& ray, // Camera coordinates
         Ray* out  // Camera coordinates
  )
  const -> bool;

private:
  auto IntersectWithLensElement
  (
   Float radius,
   Float center,
   const Ray& ray,
   Float* t,
   Vector3f* normal
  )
  const -> bool;

private:
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
