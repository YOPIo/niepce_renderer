/*!
 * @file random_sampler.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _RANDOM_SAMPLER_H_
#define _RANDOM_SAMPLER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../random/xorshift.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class RandomSampler
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class RandomSampler
{
public:
  //! The default class constructor.
  RandomSampler () = default;

  //! The constructor takes a seed.
  RandomSampler (int seed);

  //! The default class destructor.
  virtual ~RandomSampler () = default;

  //! The move constructor of the class.
  RandomSampler (RandomSampler&& sampler) = default;

  //! The move assignment operator of the class.
  auto operator = (RandomSampler&& sampler) -> RandomSampler& = default;

protected:
  //! The copy constructor of the class.
  //! Use Clone() instead.
  RandomSampler (const RandomSampler& sampler) = default;

  //! The copy assignment operator of the class.
  //! Use Clone() instead.
  auto operator = (const RandomSampler& sampler) -> RandomSampler& = default;

public:
  //! @fn std Clone ()
  //! @brief
  //! @param [in] seed
  //! @return 
  //! @exception none
  //! @details 
  auto Clone (int seed) const noexcept -> std::unique_ptr <RandomSampler>;

  //! @fn Float SampleFloat ()
  //! @brief Return the float in [0, 1).
  //! @return Random number in [0, 1).
  //! @exception none
  //! @details 
  auto SampleFloat () noexcept -> Float;

  //! @fn Point2f SamplePoint2f ()
  //! @brief Return the pair of float in [0, 1).
  //! @return Random numbers in [0, 1).
  //! @exception none
  //! @details 
  auto SamplePoint2f () noexcept -> Point2f;

  //! @fn void SetSeed (int)
  //! @brief Set the seed to random number generator in this class.
  //! @param[in] seed 
  //! @return void
  //! @exception none
  //! @details 
  auto SetSeed (int seed) noexcept -> void;

private:
  XorShift rng_;
}; // class RandomSampler
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _RANDOM_SAMPLER_H_
