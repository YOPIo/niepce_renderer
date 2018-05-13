/*!
 * @file random_sampler.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "random_sampler.h"
#include "../core/point2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
RandomSampler::RandomSampler (int seed) :
  rng_ (seed)
{}
/*
// ---------------------------------------------------------------------------
*/
auto RandomSampler::Clone (int seed) const noexcept -> std::unique_ptr <RandomSampler>
{
  std::unique_ptr <RandomSampler> res (new RandomSampler (*this));
  res->SetSeed (seed);
  return std::move (res);
}
/*
// ---------------------------------------------------------------------------
*/
auto RandomSampler::SampleFloat () noexcept -> Float
{
  return rng_.Next01 ();
}
/*
// ---------------------------------------------------------------------------
*/
auto RandomSampler::SamplePoint2f () noexcept -> Point2f
{
  return Point2f (rng_.Next01 (), rng_.Next01 ());
}
/*
// ---------------------------------------------------------------------------
*/
auto RandomSampler::SetSeed (int seed) noexcept -> void
{
  rng_.SetSeed (seed);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
