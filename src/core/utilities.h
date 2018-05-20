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
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _UTILITIES_H_

