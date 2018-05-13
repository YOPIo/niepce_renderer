/*!
 * @file bsdf.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BSDF_H_
#define _BSDF_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class Bsdf
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Bsdf
{
public:
  //! The default class constructor.
  Bsdf () = default;

  //! The copy constructor of the class.
  Bsdf (const Bsdf& bsdf) = default;

  //! The move constructor of the class.
  Bsdf (Bsdf&& bsdf) = default;

  //! The default class destructor.
  virtual ~Bsdf () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Bsdf& bsdf) -> Bsdf& = default;

  //! The move assignment operator of the class.
  auto operator = (Bsdf&& bsdf) -> Bsdf& = default;

private:

}; // class Bsdf
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BSDF_H_
