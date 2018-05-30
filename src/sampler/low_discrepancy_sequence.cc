/*!
 * @file low_discrepancy_sequence.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "low_discrepancy_sequence.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto RadicalInverse (int base_index, uint64_t a) -> Float
{
  if (base_index == 2)
  {
    // 2^-64 = 5.42101086242752217003726400434970855712890625e-20
    return ReverseBits64 (a) * 5.42101086242752217003726400434970855712890625e-20;
  }
  if (base_index == 3)
  {
    return RadicalInverseBasedOn <3> (a);
  }
  if (base_index == 5)
  {
    return RadicalInverseBasedOn <5> (a);
  }
  if (base_index == 7)
  {
    return RadicalInverseBasedOn <7> (a);
  }

  return 0;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
