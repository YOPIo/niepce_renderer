/*!
 * @file hammersley.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _HAMMERSLEY_H_
#define _HAMMERSLEY_H_
/*
// ---------------------------------------------------------------------------
*/
#include "sampler.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class HammersleySampler
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class HammersleySampler : public Sampler
{
public:
  //! The default class constructor.
  HammersleySampler (int num_samples);

  //! The copy constructor of the class.
  HammersleySampler (const HammersleySampler& s) = default;

  //! The move constructor of the class.
  HammersleySampler (HammersleySampler&& s) = default;

  //! The default class destructor.
  virtual ~HammersleySampler () = default;

  //! The copy assignment operator of the class.
  auto operator = (const HammersleySampler& s) -> HammersleySampler& = default;

  //! The move assignment operator of the class.
  auto operator = (HammersleySampler&& s) -> HammersleySampler& = default;

public:
  /*!
   * @fn Float Next1f ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  auto Next1f () -> Float override;

  /*!
   * @fn Point2f Next2f ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  auto Next2f () -> Point2f override;

private:
  int num_samples_;
  int n1_;
  int n2_;

}; // class HammersleySampler
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _HAMMERSLEY_H_

