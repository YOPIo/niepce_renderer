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
inline auto Reflect (const Vector3f& vector, const Vector3f& normal) -> Vector3f
{
  return -vector + 2.0 * Dot(vector, normal) * normal;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _UTILITIES_H_

