/*!
 * @file metal.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _METAL_H_
#define _METAL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "material.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class Metal
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Metal final : public Material
{
public:
  //! The default class constructor.
  Metal () = delete;

  //! The constructor takes reflectance and emission textures.
  Metal
  (
   const std::shared_ptr <Texture <Spectrum>>& absorption,
   const std::shared_ptr <Texture <Float>>& ior,
   const std::shared_ptr <Texture <Float>>& roughness_u,
   const std::shared_ptr <Texture <Float>>& roughness_v
  );

  //! The copy constructor of the class.
  Metal (const Metal& metal) = default;

  //! The move constructor of the class.
  Metal (Metal&& metal) = default;

  //! The default class destructor.
  virtual ~Metal () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Metal& metal) -> Metal& = default;

  //! The move assignment operator of the class.
  auto operator = (Metal&& metal) -> Metal& = default;

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
  auto AllocateBsdfs
  (
   const Intersection& intersection,
         MemoryArena*  memory
  )
  const -> Bsdf* const override final;

private:
  const std::shared_ptr <Texture <Spectrum>> absorption_;
  const std::shared_ptr <Texture <Float>>    roughness_u_;
  const std::shared_ptr <Texture <Float>>    roughness_v_;
  const std::shared_ptr <Texture <Float>>    ior_;

}; // class Metal
/*
// ---------------------------------------------------------------------------
*/
auto CreateMetalMaterial (const MaterialAttributes& attrs)
  -> std::shared_ptr <Material>;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _METAL_H_

