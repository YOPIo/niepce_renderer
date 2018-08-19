/*!
 * @file bsdf_record.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BSDF_RECORD_H_
#define _BSDF_RECORD_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/vector3f.h"
#include "bxdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class BsdfRecord
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class BsdfRecord
{
public:
  //! The default class constructor.
  BsdfRecord () = delete;

  //! The constructor takes reference to the underlying surface intersection.
  BsdfRecord (const Intersection& intersection);

  //! The copy constructor of the class.
  BsdfRecord (const BsdfRecord& record) = default;

  //! The move constructor of the class.
  BsdfRecord (BsdfRecord&& record) = default;

  //! The default class destructor.
  virtual ~BsdfRecord () = default;

  //! The copy assignment operator of the class.
  auto operator = (const BsdfRecord& record) -> BsdfRecord& = default;

  //! The move assignment operator of the class.
  auto operator = (BsdfRecord&& record) -> BsdfRecord& = default;

public:
  /*! @fn Float CosTheta ()
   * @brief The $ cos(\theta) $
   * @return Float
   * @exception none
   * @details
   */
  auto CosWeight () const noexcept -> Float;

  /*!
   * @fn Vector3f Outgoing ()
   * @brief The outgoing direction in BSDF coordinate at the underlying surface
   *        intersection.
   * @return Vector3f
   * @exception none
   * @details
   */
  auto Outgoing (bsdf::Coordinate coordinate) const noexcept -> Vector3f;

  /*!
   * @fn Vector3f Incident ()
   * @brief The incident direction in BSDF coordinate at the underlying surface
   *        intersection.
   * @return Vector3f
   * @exception none
   * @details
   */
  auto Incident (bsdf::Coordinate coordinate) const noexcept -> Vector3f;

  /*!
   * @fn Vector3f Bsdf ()
   * @brief Return the evaluated bsdf value.
   * @return Vector3f
   * @exception none
   * @details
   */
  auto Bsdf () const noexcept -> Vector3f;

  /*!
   * @fn Float Pdf ()
   * @brief Return the probability density function value.
   * @return Float
   * @exception none
   * @details
   */
  auto Pdf () const noexcept -> Float;

  /*!
   * @fn niepce SamplingTarget ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto SamplingTarget () const noexcept -> niepce::Bxdf::Type;

  /*!
   * @fn niepce SampledBsdfType ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  auto SampledType () const noexcept -> niepce::Bxdf::Type;


  /*!
   * @fn void SetOutgoing ()
   * @brief Set the outgoing direction to internal data.
   * @param[in] outgoing
   *     The outgoing direction in BSDF coordinates.
   * @return void
   * @exception none
   * @details
   */
  auto SetOutgoing
  (
   const Vector3f   &outgoing,
   bsdf::Coordinate coordinate
  )
  noexcept -> void;

  /*!
   * @fn void SetIncident (const)
   * @brief Set the incident direction to internal data.
   * @param[in] incident
   *    The incident direction in BSDF coordinates.
   * @return void
   * @exception none
   * @details
   */
  auto SetIncident
  (
   const Vector3f  &incident,
   bsdf::Coordinate coordinate
  )
  noexcept -> void;

  /*!
   * @fn void SetBsdfValue (const)
   * @brief Set the calculated bsdf value to internal data.
   * @param[in] bsdf_value
   *    The bsdf value.
   * @return void
   * @exception none
   * @details
   */
  auto SetBsdf (const Spectrum& basf_value) noexcept -> void;

  /*!
   * @fn void SetPdf (Float)
   * @brief Set the pdf value to internal data.
   * @param[in] pdf
   *    The probability density function.
   * @return void
   * @exception none
   * @details
   */
  auto SetPdf (Float pdf) noexcept -> void;

  /*! @fn void SetCosTheta (Float)
   * @brief 
   * @param[in] cos_theta
   *    The $ cos(\theta) $
   * @return 
   * @exception none
   * @details 
   */
  auto SetCosWeight (Float cos_theta) noexcept -> void;

  /*!
   * @fn void SetSamplingTarget (niepce)
   * @brief 
   * @param[in] type
   * @return 
   * @exception none
   * @details
   */
  auto SetSamplingTarget (niepce::Bxdf::Type type) noexcept -> void;

  /*!
   * @fn void SetSampledBsdfType (niepce)
   * @brief 
   * @param[in] type
   * @return 
   * @exception none
   * @details
   */
  auto SetSampledBsdfType (niepce::Bxdf::Type type) noexcept -> void;

private:
  /*!
   * @brief The reference to the underlying surface intersection.
   */
  const Intersection& intersection_;

  /*!
   * @brief
   *   The normalized outgoint direction in BSDF coordinates.
   */
  Vector3f local_outgoing_;

  /*!
   * @brief
   *   The normalized outgoint direction in world coordinates.
   */
  Vector3f world_outgoing_;

  /*!
   * @brief
   *   The normalized incident direction in BSDF coordinates.
   */
  Vector3f local_incident_;

  /*!
   * @brief
   *   The normalized incident direction in world coordinates.
   */
  Vector3f world_incident_;

  /*!
   * @brief
   *   The evaluated value of BSDF.
   */
  Spectrum bsdf_;

  /*!
   * @brief
   *   The probability density function.
   */
  Float pdf_;

  /*!
   * @brief
   *    The $ cos(\theta) $
   */
  Float cos_t_;

  /*!
   * @brief
   *    The type of sampled bsdf.
   */
  niepce::Bxdf::Type sampled_type_;

  /*!
   * @brief
   *    The sampling target type of BSDF.
   */
  niepce::Bxdf::Type target_type_;
}; // class BsdfRecord
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BSDF_RECORD_H_
