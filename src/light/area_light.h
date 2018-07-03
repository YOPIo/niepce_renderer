/*!
 * @file area_light.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _AREA_LIGHT_H_
#define _AREA_LIGHT_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/vector3f.h"
#include "light.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class AreaLight
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class AreaLight : public Light
{
public:
  //! The default class constructor.
  AreaLight () = delete;

  //! The constructor takes shape and emission.
  AreaLight
  (
   const std::shared_ptr <Shape>& shape,
   const Spectrum&                emission
  );

  //! The constructor takes emission.
  AreaLight (const Spectrum& emission);

  //! The constructor takes shape.

  //! The copy constructor of the class.
  AreaLight (const AreaLight& light) = default;

  //! The move constructor of the class.
  AreaLight (AreaLight&& light) = default;

  //! The default class destructor.
  virtual ~AreaLight () = default;

  //! The copy assignment operator of the class.
  auto operator = (const AreaLight& light) -> AreaLight& = default;

  //! The move assignment operator of the class.
  auto operator = (AreaLight&& light) -> AreaLight& = default;

public:
  /*!
   * @fn Spectrum Emission ()
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto Emission () const noexcept -> Spectrum override final;

  /*!
   * @fn Point3f SamplePosition (const)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto SamplePosition (const Point2f& sample)
    const noexcept -> Point3f override final;

  /*!
   * @fn Spectrum Evaluate (Float*)
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Evaluate (Float* pdf) -> Spectrum;

  /*!
   * @fn Point3f Sample (const Intersection&, const Point2f&)
   * @brief 
   * @param[in] intersection
   *    
   * @param[in] sample
   *    
   * @return 
   * @exception none
   * @details
   */
  auto Sample
  (
   const Intersection& intersection,
   const Point2f&      sample
  )
  const noexcept -> Point3f;

private:
  const std::shared_ptr <Shape> shape_;
  Spectrum emission_;
}; // class AreaLight
/*
// ---------------------------------------------------------------------------
*/
auto CreateAreaLight (const Attributes& attrib) -> std::shared_ptr <AreaLight>;
auto CreateAreaLight
(
 const Attributes& attrib,
 const std::shared_ptr <Shape>& shape
)
  -> std::shared_ptr <AreaLight>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _AREA_LIGHT_H_

