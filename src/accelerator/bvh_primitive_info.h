/*!
 * @file bvh_primitive_info.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _BVH_PRIMITIVE_INFO_H_
#define _BVH_PRIMITIVE_INFO_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/bounds3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct PrimitiveInfo
{
  PrimitiveInfo () = default;

  PrimitiveInfo (int index, const Bounds3f& b) :
    primitive_index (index),
    bounds (b),
    centroid (0.5f * b.Min () + 0.5f * b.Max ())
  {}

  PrimitiveInfo (const PrimitiveInfo& info) = default;
  PrimitiveInfo (PrimitiveInfo&&) = default;

  auto operator = (const PrimitiveInfo& info) -> PrimitiveInfo& = default;
  auto operator = (PrimitiveInfo&& info) -> PrimitiveInfo& = default;

  ~PrimitiveInfo () = default;

  int      primitive_index; // Reference index to the primitive.
  Bounds3f bounds;
  Point3f  centroid;
};
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BVH_PRIMITIVE_INFO_H_

