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
#include "../bsdf/bsdf_record.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Material
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Material
{
public:
  //! The default class constructor.
  Material ();

  //! The constructor takes emission texture.
  Material (const std::shared_ptr <Texture>& emission);

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
  virtual auto Sample
  (
   const Intersection& intersection,
   const Point2f& sample,
   BsdfRecord*    bsdf_record
  )
  const -> void = 0;

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
  virtual auto Emission (const Point2f& uv) const noexcept -> Vector3f;

protected:
  std::shared_ptr <Texture> emission_;
}; // class Material
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATERIAL_H_
