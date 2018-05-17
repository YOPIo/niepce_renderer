/*!
 * @file sampler.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _SAMPLER_H_
#define _SAMPLER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/point2f.h"
#include "../core/point3f.h"
#include "../core/vector2f.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto SampleConcentricDisk (const Point2f& sample) -> Point2f;
/*
// ---------------------------------------------------------------------------
*/
auto SampleCosineHemisphere (const Point2f& sample) -> Vector3f;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SAMPLER_H_
