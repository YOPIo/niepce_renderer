/*!
 * @file low_discrepancy_sequence.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _LOW_DISCREPANCY_SEQUENCE_H_
#define _LOW_DISCREPANCY_SEQUENCE_H_
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
auto RadicalInverse (int base_index, uint64_t a) -> Float;
/*
// ---------------------------------------------------------------------------
*/
template <int base>
auto RadicalInverseBasedOn (uint64_t n) -> Float
{
  const Float inv_base = 1.0 / static_cast <Float> (base);
  uint64_t reversed_digits = 0;
  Float inv_base_n = 1;
  while (n)
  {
    uint64_t next  = n / base;
    uint64_t digit = n - next * base;
    reversed_digits = reversed_digits * base + digit;
    inv_base_n *= inv_base;
    n = next;
  }
  return std::fmin (reversed_digits * inv_base_n, 1.0 - kEpsilon);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _LOW_DISCREPANCY_SEQUENCE_H_

