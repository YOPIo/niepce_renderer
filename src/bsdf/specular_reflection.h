/*!
 * @file specular_reflection.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _SPECULAR_REFLECTION_H_
#define _SPECULAR_REFLECTION_H_
/*
// ---------------------------------------------------------------------------
*/
#include "bxdf.h"
#include "fresnel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class SpecularReflection
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class SpecularReflection : public Bxdf
{
public:
  //! The default class constructor.
  SpecularReflection () = delete;

  //! The constructor takes fresnel and reflectance.
  SpecularReflection (const Spectrum &reflectance, Fresnel *fresnel);

  //! The copy constructor of the class.
  SpecularReflection (const SpecularReflection& specular) = default;

  //! The move constructor of the class.
  SpecularReflection (SpecularReflection&& specular) = default;

  //! The default class destructor.
  virtual ~SpecularReflection () = default;

  //! The copy assignment operator of the class.
  auto operator = (const SpecularReflection& specular)
    -> SpecularReflection& = default;

  //! The move assignment operator of the class.
  auto operator = (SpecularReflection&& specular)
    -> SpecularReflection& = default;

public:
  /*!
   * @fn Spectrum Sample (BsdfRecord*)
   * @brief 
   * @param[in] 
   * @return 
   * @exception none
   * @details 
   */
  auto Sample (BsdfRecord* record, const Point2f &sample)
    const noexcept -> Spectrum override final;

  /*!
   * @fn Spectrum Evaluate (const)
   * @brief 
   * @param[in] record
   * @return 
   * @exception none
   * @details 
   */
  auto Evaluate (const BsdfRecord &record) const noexcept
    -> Spectrum override final;

  /*!
   * @fn Float Pdf (const)
   * @brief 
   * @param[in] record
   * @return 
   * @exception none
   * @details 
   */
  auto Pdf (const BsdfRecord &record) const noexcept -> Float override final;

private:
  const Spectrum  reflectance_;
  const Fresnel  *fresnel_;
}; // class SpecularReflection
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SPECULAR_REFLECTION_H_

