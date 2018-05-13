/*!
 * @file matte.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _MATTE_H_
#define _MATTE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "material.h"
#include "../texture/texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Matte
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Matte : public Material
{
public:
  //! The default class constructor.
  Matte () = delete;

  //! The constructor takes reflectance texture.
  Matte
  (
   const std::shared_ptr <Texture>& reflectance,
   const std::shared_ptr <Texture>& emission
  );

  //! The move constructor of the class.
  Matte (Matte&& matte) = default;

  //! The default class destructor.
  virtual ~Matte () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Matte& matte) -> Matte& = default;

  //! The move assignment operator of the class.
  auto operator = (Matte&& matte) -> Matte& = default;

public:
  /*!
   * @fn void Return Sample (const)
   * @brief 
   *
   * @param[in] intersection
   *    Underlying surface intersection.
   * @param[out] bsdf_record
   *    Sampled data will be stored.
   * @param[in] sample
   *    2-dimensional sampled values.
   * @return void
   * @exception none
   * @details
   */
  auto Sample
  (
   const Intersection& intersection,
   const Point2f& sample,
   BsdfRecord*    bsdf_record
  )
  const -> void override final;


private:
  //! @brief The reflectance of matte surface.
  std::shared_ptr <Texture> reflectance_;

  //! @brief The emission of matte surface.
  std::shared_ptr <Texture> emission_;
}; // class Matte
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATTE_H_

