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
   * @fn Spectrum Evaluate (const)
   * @brief 
   * @param[in] intersection
   *    
   * @return 
   * @exception none
   * @details 
   */
  virtual auto Evaluate
  (
   const Intersection& intersection,
   Float* pdf
  )
    const noexcept -> Spectrum = 0;

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
