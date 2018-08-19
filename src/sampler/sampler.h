/*!
 * @file sampler.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _SAMPLER_H_
#define _SAMPLER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/point2f.h"
#include "../core/point3f.h"
#include "../core/vector2f.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto SampleConcentricDisk (const Point2f& sample) -> Point2f;
auto SampleCosineHemisphere (const Point2f& sample) -> Vector3f;
auto SampleUniformTriangle (const Point2f& sample) -> Point2f;
//! ----------------------------------------------------------------------------
//! @class Sampler
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Sampler
{
public:
  //! The default class constructor.
  Sampler (int spp);

  //! The copy constructor of the class.
  Sampler (const Sampler& sampler) = default;

  //! The move constructor of the class.
  Sampler (Sampler&& sampler) = default;

  //! The default class destructor.
  virtual ~Sampler () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Sampler& sampler) -> Sampler& = default;

  //! The move assignment operator of the class.
  auto operator = (Sampler&& sampler) -> Sampler& = default;

public:
  /*!
   * @fn Float Next1D ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  virtual auto Next1f () -> Float = 0;

  /*!
   * @fn Point2f Next2f ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  virtual auto Next2f () -> Point2f = 0;

protected:
  const int spp_; // Sample per pixel
}; // class Sampler
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SAMPLER_H_
