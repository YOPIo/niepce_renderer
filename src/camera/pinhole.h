/*!
 * @file pinhole.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _PINHOLE_H_
#define _PINHOLE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "camera.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class PinholeCamera
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class PinholeCamera : public Camera
{
public:
  //! The default class constructor.
  PinholeCamera () = delete;

  //! The constructor
  PinholeCamera
  (
   const Transform& camera_to_wrold,
   Float            fov,
   const char*      filename,
   unsigned int     resolution_width,
   unsigned int     resolution_height,
   Float            diagonal
  );

  //! The copy constructor of the class.
  PinholeCamera (const PinholeCamera& camera) = default;

  //! The move constructor of the class.
  PinholeCamera (PinholeCamera&& camera) = default;

  //! The default class destructor.
  virtual ~PinholeCamera () = default;

  //! The copy assignment operator of the class.
  auto operator = (const PinholeCamera& camera) -> PinholeCamera& = default;

  //! The move assignment operator of the class.
  auto operator = (PinholeCamera&& camera) -> PinholeCamera& = default;

private:
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

protected:
  Float distance_to_film_;

}; // class PinholeCamera
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _PINHOLE_H_
