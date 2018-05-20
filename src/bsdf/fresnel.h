/*!
 * @file fresnel.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _FRESNEL_H_
#define _FRESNEL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class Fresnel
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Fresnel
{
public:
  //! The default class constructor.
  Fresnel () = default;

  //! The copy constructor of the class.
  Fresnel (const Fresnel& fresnel) = default;

  //! The move constructor of the class.
  Fresnel (Fresnel&& fresnel) = default;

  //! The default class destructor.
  virtual ~Fresnel () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Fresnel& fresnel) -> Fresnel& = default;

  //! The move assignment operator of the class.
  auto operator = (Fresnel&& fresnel) -> Fresnel& = default;

public:
  //! @fn Spectrum Evaluate (Float)
  //! @brief 
  //! @param[in] incident_cos_theta
  //!    cos(\theta)
  //! @return 
  //! @exception none
  //! @details 
  virtual auto Evaluate (Float cos_theta1)
    const noexcept -> Float = 0;

}; // class Fresnel
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class FresnelConductor
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class FresnelConductor final : public Fresnel
{
public:
  //! The default class constructor.
  FresnelConductor () = default;

  //! The copy constructor of the class.
  FresnelConductor (const FresnelConductor& conductor) = default;

  //! The move constructor of the class.
  FresnelConductor (FresnelConductor&& conductor) = default;

  //! The default class destructor.
  virtual ~FresnelConductor () = default;

  //! The copy assignment operator of the class.
  auto operator = (const FresnelConductor& conductor) -> FresnelConductor&
    = default;

  //! The move assignment operator of the class.
  auto operator = (FresnelConductor&& conductor) -> FresnelConductor& = default;

public:
  //! @fn Spectrum Evaluate (Float)
  //! @brief 
  //! @param[in] incident_cos_theta
  //!    cos(\theta)
  //! @return 
  //! @exception none
  //! @details 
  auto Evaluate (Float cos_theta1)
    const noexcept -> Float override final;

private:
  Spectrum incident_ior_;
  Spectrum outgoing_ior_;

}; // class FresnelConductor
//! ----------------------------------------------------------------------------
//! @class FresnelDielectric
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class FresnelDielectric final : public Fresnel
{
public:
  //! The default class constructor.
  FresnelDielectric () = delete;

  //! The constructor takes indices of refraction.
  FresnelDielectric (Float outgoing_ior, Float incident_ior);

  //! The copy constructor of the class.
  FresnelDielectric (const FresnelDielectric& dielectric) = default;

  //! The move constructor of the class.
  FresnelDielectric (FresnelDielectric&& dielectric) = default;

  //! The default class destructor.
  virtual ~FresnelDielectric () = default;

  //! The copy assignment operator of the class.
  auto operator = (const FresnelDielectric& dielectric) -> FresnelDielectric&
    = default;

  //! The move assignment operator of the class.
  auto operator = (FresnelDielectric&& dielectric) -> FresnelDielectric&
    = default;

public:
  //! @fn Spectrum Evaluate (Float)
  //! @brief 
  //! @param[in] incident_cos_theta
  //!    cos(\theta)
  //! @return 
  //! @exception none
  //! @details 
  auto Evaluate (Float cos_theta1)
    const noexcept -> Float override final;

private:
  Float outgoing_ior_;
  Float incident_ior_;

}; // class FresnelDielectric
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FRESNEL_H_
