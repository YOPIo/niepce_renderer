/*!
 * @file bsdfs.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BSDFS_H_
#define _BSDFS_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "bxdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Bsdf
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Bsdf : public Bxdf
{
public:
  //! The default class constructor.
  Bsdf () = delete;

  //! The constructor takes intersection.
  Bsdf (const Intersection &isect);

  //! The copy constructor of the class.
  Bsdf (const Bsdf& bsdfs) = default;

  //! The move constructor of the class.
  Bsdf (Bsdf&& bsdfs) = default;

  //! The default class destructor.
  virtual ~Bsdf () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Bsdf& bsdfs) -> Bsdf& = default;

  //! The move assignment operator of the class.
  auto operator = (Bsdf&& bsdfs) -> Bsdf& = default;

public:
  /*!
   * @fn void AddBxdf (Bxdf*)
   * @brief 
   * @param[in] bxdf
   * @return 
   * @exception none
   * @details
   */
  auto AddBxdf (Bxdf* bxdf) noexcept -> void;

public:
  /*!
   * @brief Compute the pdf.
   * @param[in] outgoing
   *    The outgoing direction in BRDF coordinates.
   * @param[in] incident
   *    The incident direction in BRDF coordinates.
   * @return Value of pdf.
   * @exception none
   * @details
   */
  auto Pdf (const BsdfRecord& record)
    const noexcept -> Float override final;

  /*!
   * @brief Evlauate the BXDF
   *
   * @param[in] outgoing
   *    The outgoing direction in the BXDF coordinates.
   * @param[in] incident
   *    The incident direction in the BXDF coordinates.
   *
   * @return The evaluated BXDF.
   *
   * @exception none
   * @details
   */
  auto Evaluate (const BsdfRecord& record)
    const noexcept -> Spectrum override final;

  /*!
   * @brief Sample the BXDF.
   *
   * @param[out] record
   *    Bxdfrecord 
   * @param[in] sample
   *    The uniform distributed sample on [0, 1]^2.
   *
   * @return 
   * @exception none
   * @details
   */
  auto Sample (BsdfRecord* record, const Point2f &sample)
    const noexcept -> Spectrum override final;

  /*!
   * @fn Vector3f WorldToLocal (const)
   * @brief 
   * @param[in] v
   *    
   * @return 
   * @exception none
   * @details
   */
  auto WorldToLocal (const Vector3f &v) const noexcept -> Vector3f;

  /*!
   * @fn Return LocalToWorld (const)
   * @brief 
   * @param[in] v
   *    
   * @return 
   * @exception none
   * @details
   */
  auto LocalToWorld (const Vector3f &v) const noexcept -> Vector3f;


private:
  std::vector <Bxdf*> bxdfs_;
  const Intersection& isect_;
}; // class Bsdf
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BSDFS_H_

