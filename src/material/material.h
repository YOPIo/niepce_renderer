/*!
 * @file material.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#ifndef _MATERIAL_H_
#define _MATERIAL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../texture/texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
enum class MaterialType : uint8_t
{
  kMatte,
  kMetal,
  kPlastic,
  kUnknown
};
//! ----------------------------------------------------------------------------
//! @class Material
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Material
{
public:
  //! The default class constructor.
  Material () = delete;

  //! The constructor takes emission texture.
  Material (const std::shared_ptr <Texture <Spectrum>>& emission);

  //! The constructor takes underlying surface intersection.
  Material (const Intersection& intersection);

  //! The copy constructor of the class.
  Material (const Material& mat) = default;

  //! The move constructor of the class.
  Material (Material&& mat) = default;

  //! The default class destructor.
  virtual ~Material () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Material& mat) -> Material& = default;

  //! The move assignment operator of the class.
  auto operator = (Material&& mat) -> Material& = default;

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
    const -> Bsdf* const = 0;

public:
  /*!
   * @fn bool HasEmission ()
   * @brief Return the surface has emission or not.
   * @return bool
   * @exception none
   * @details
   */
  virtual auto HasEmission () const noexcept -> bool;

  /*!
   * @fn Vector3f Emission ()
   * @brief Return the emission at the surface intersection.
   * @param[in] uv
   *
   * @return 
   *    Vector3f
   * @exception none
   * @details
   */
  virtual auto Emission (const Intersection& isect) const noexcept -> Spectrum;

protected:
  std::shared_ptr <Texture <Spectrum>> emission_;
}; // class Material
/*
// ---------------------------------------------------------------------------
*/
auto CreateMaterial (const MaterialAttributes& attributes)
  -> std::shared_ptr <Material>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATERIAL_H_
