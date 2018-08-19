/*!
 * @file utilities.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _UTILITIES_H_
#define _UTILITIES_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
inline auto RgbToMonochrome (const Spectrum& rgb) -> Float
{
  // http://poynton.ca/notes/colour_and_gamma/ColorFAQ.html
  return (0.2125 * rgb.X ()) + (0.7154 * rgb. Y ()) + (0.0721 * rgb.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
inline auto SolveQuadratic
(
 Float a,
 Float b,
 Float c,
 Float* t1,
 Float* t2
)
  -> bool
{
  // Find quadratic discriminant
  const Float discrim = b * b - 4 * a * c;

  if (discrim < 0) { return false; }

  const Float sqrt_discrim = std::sqrt (discrim);

  // Compute quadratic t1, t2 values
  Float q;
  if (b < 0) { q = -.5 * (b - sqrt_discrim); }
  else { q = -.5 * (b + sqrt_discrim); }

  *t1 = q / a;
  *t2 = c / q;

  if (*t1 > *t2) { std::swap(*t1, *t2); }

  return true;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _UTILITIES_H_

