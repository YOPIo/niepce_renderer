/*!
 * @file plastic.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _PLASTIC_H_
#define _PLASTIC_H_
/*
// ---------------------------------------------------------------------------
*/
#include "material.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Plastic
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Plastic : public Material
{
public:
  //! The default class constructor.
  Plastic () = delete;

  //! The constructor takes diffuse reflectance, glossy specular and roughness.
  Plastic
  (
   const std::shared_ptr <Texture <Spectrum>> &reflectance,
   const std::shared_ptr <Texture <Spectrum>> &specular,
   const std::shared_ptr <Texture <Float>>    &roughness
  );

  //! The copy constructor of the class.
  Plastic (const Plastic& plastic) = default;

  //! The move constructor of the class.
  Plastic (Plastic&& plastic) = default;

  //! The default class destructor.
  virtual ~Plastic () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Plastic& plastic) -> Plastic& = default;

  //! The move assignment operator of the class.
  auto operator = (Plastic&& plastic) -> Plastic& = default;

public:
  /*!
   * @fn Bsdf* AllocateBsdf (const Intersection&, MemoryArena*)
   * @brief Allocate the BSDF
   * @param[in] intersection
   *    
   * @param[out] memory
   *    
   * @return 
   * @exception none
   * @details
   */
  auto AllocateBsdfs
  (
   const Intersection& intersection,
         MemoryArena*  memory
  )
    const -> Bsdf* const override final;

private:
  // Diffuse reflection
  const std::shared_ptr <Texture <Spectrum>> reflectance_;

  // Glossy specular reflection.
  const std::shared_ptr <Texture <Spectrum>> specular_;

  // Roughness
  const std::shared_ptr <Texture <Float>> roughness_;
}; // class Plastic
/*
// ---------------------------------------------------------------------------
*/
auto CreatePlasticMaterial (const MaterialAttributes &attrs)
  -> std::shared_ptr <Material>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _PLASTIC_H_

