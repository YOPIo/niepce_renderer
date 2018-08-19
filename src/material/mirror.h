/*!
 * @file mirror.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _MIRROR_H_
#define _MIRROR_H_
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
//! @class Mirror
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Mirror : public Material
{
public:
  //! The default class constructor.
  Mirror () = delete;

  //! The constructor takes reflectance.
  Mirror (const std::shared_ptr <Texture <Spectrum>> &reflectance);

  //! The copy constructor of the class.
  Mirror (const Mirror& mirror) = default;

  //! The move constructor of the class.
  Mirror (Mirror&& mirror) = default;

  //! The default class destructor.
  virtual ~Mirror () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Mirror& mirror) -> Mirror& = default;

  //! The move assignment operator of the class.
  auto operator = (Mirror&& mirror) -> Mirror& = default;

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
  virtual auto AllocateBsdfs
  (
   const Intersection& intersection,
         MemoryArena*  memory
  )
    const -> Bsdf* const override final;

private:
  std::shared_ptr <Texture <Spectrum>> reflectance_;

}; // class Mirror
/*
// ---------------------------------------------------------------------------
*/
auto CreateMirrorMaterial (const MaterialAttributes &attrs)
  -> std::shared_ptr <Material>;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MIRROR_H_

