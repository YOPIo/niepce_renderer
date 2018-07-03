/*!
 * @file light.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _LIGHT_H_
#define _LIGHT_H_
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
enum class LightType : int
{
  kPointLight,
  kAreaLight,
  kInfiniteLight,
  kUnknow
};
//! ----------------------------------------------------------------------------
//! @class Light
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Light
{
public:
  //! The default class constructor.
  Light ();

  //! The copy constructor of the class.
  Light (const Light& light) = default;

  //! The move constructor of the class.
  Light (Light&& light) = default;

  //! The default class destructor.
  virtual ~Light () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Light& light) -> Light& = default;

  //! The move assignment operator of the class.
  auto operator = (Light&& light) -> Light& = default;

public:
  /*!
   * @fn Return Function (Param)
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  virtual auto Emission () const noexcept -> Spectrum = 0;

  /*!
   * @fn Point3f SamplePosition (const Point2f&)
   * @brief 
   * @param[in] sample
   *    
   * @return 
   * @exception none
   * @details
   */
  virtual auto SamplePosition (const Point2f& sample)
    const noexcept -> Point3f = 0;

protected:

}; // class Light
/*
// ---------------------------------------------------------------------------
*/
auto CreateLight
(
 const LightType&  type,
 const Attributes& attributes
)
  -> std::shared_ptr <Light>;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _LIGHT_H_
