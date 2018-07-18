/*!
 * @file hammersley.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "hammersley.h"
#include "low_discrepancy_sequence.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
HammersleySampler::HammersleySampler (int num_samples) :
  Sampler (num_samples),
  num_samples_ (num_samples),
  n1_ (0),
  n2_ (0)
{}
/*
// ---------------------------------------------------------------------------
*/
auto HammersleySampler::Next1f () -> Float
{
  return RadicalInverse (2, n1_++);
}
/*
// ---------------------------------------------------------------------------
*/
auto HammersleySampler::Next2f () -> Point2f
{
  const auto res = Point2f (static_cast <Float> (n2_) / num_samples_,
                            RadicalInverse (2, n2_));
  ++n2_;
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
