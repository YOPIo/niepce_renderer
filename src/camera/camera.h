/*!
 * @file camera.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _CAMERA_H_
#define _CAMERA_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/film.h"
#include "../core/film_tile.h"
#include "../core/transform.h"
#include "camera_sample.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Camera
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Camera : public Film
{
public:
  //! The default class constructor.
  Camera () = delete;

  //! The constructor takes transform matrix.
  Camera
  (
   const Transform& t,
   const char*  filename,
   unsigned int width,   // Resolution
   unsigned int height,  // Resolution
   Float        diagonal // Physical length [m]
  );

  //! The copy constructor of the class.
  Camera (const Camera& camera) = default;

  //! The move constructor of the class.
  Camera (Camera&& camera) = default;

  //! The default class destructor.
  virtual ~Camera () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Camera& camera) -> Camera& = default;

  //! The move assignment operator of the class.
  auto operator = (Camera&& camera) -> Camera& = default;

public:
  /*!
   * @fn Ray GenerateRay ()
   * @brief Generate the ray from camera.
   * @return 
   * @exception none
   * @details
   */
  virtual auto GenerateRay
  (
   const CameraSample& samples,
         Ray*          ray
  )
  const -> Float = 0;

protected:
  /*!
   * @brief Matrix that transform camera coordinate to world coordinates.
   */
  Transform camera_to_world_;
}; // class Camera
/*
// ---------------------------------------------------------------------------
*/
auto CreateCamera (const Attributes& attrib) -> std::shared_ptr <Camera>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _CAMERA_H_
