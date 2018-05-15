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
#include "../bsdf/bsdf.h"
#include "../bsdf/lambert.h"
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
   * @fn Return Function (Param)
   * @brief Allocate the BSDF for representing the matte surface.
   * @param[in] intersection
   *    The intersection
   * @param[in] memory
   *    Used to allocate the BSDF.
   * @return The pointer of BSDF.
   * @exception 
   * @details
   */
  virtual auto AllocateBsdf
  (
   const Intersection& intersection,
         MemoryArena*  memory
  )
  const -> Bsdf* override final;

private:
  //! @brief The reflectance of matte surface.
  std::shared_ptr <Texture> reflectance_;
}; // class Matte
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATTE_H_

