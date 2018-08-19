/*!
 * @file xorshift.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _XORSHIFT_H_
#define _XORSHIFT_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class XorShift
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class XorShift
{
public:
  //! The default class constructor.
  XorShift ();

  //! The constructor takes seed to initialize random number generator.
  XorShift (std::uint_fast32_t seed);

  //! The copy constructor of the class.
  XorShift (const XorShift& rng) = default;

  //! The move constructor of the class.
  XorShift (XorShift&& rng) = default;

  //! The default class destructor.
  virtual ~XorShift () = default;

  //! The copy assignment operator of the class.
  auto operator = (const XorShift& rng) -> XorShift& = default;

  //! The move assignment operator of the class.
  auto operator = (XorShift&& rng) -> XorShift& = default;

public:
  /*!
   * @fn void SetSeed (std)
   * @brief Chage seed.
   * @param[in] seed Set the seed to random number generator.
   * @return void
   * @exception none
   * @details
   */
  auto SetSeed (int seed) noexcept -> void;

  /*!
   * @fn Float Next01 ()
   * @brief Return the random number in [0, 1)
   * @return random number in [0, 1) as Float.
   * @exception none
   * @details
   */
  auto Next01 () noexcept -> Float;

  /*!
   * @fn uint_fast32_t Next ()
   * @brief Return the integer in [0, 2^32).
   * @return [0, 1) as unsigned integer.
   * @exception none
   * @details
   */
  auto Next () noexcept -> uint_fast32_t;


private:
  std::uint_fast32_t x_;
  std::uint_fast32_t y_;
  std::uint_fast32_t z_;
  std::uint_fast32_t w_;

}; // class XorShift
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _XORSHIFT_H_
