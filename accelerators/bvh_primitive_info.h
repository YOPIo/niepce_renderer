#ifndef _BVH_PRIMITIVE_INFO_H_
#define _BVH_PRIMITIVE_INFO_H_

#include "../geometries/point3.h"
#include "../geometries/boundingbox3.h"

namespace niepce
{

struct BVHPrimitiveInfo
{
  /* BVHprimitiveinfo constructors */
  BVHPrimitiveInfo ();
  BVHPrimitiveInfo (std::size_t     index,
                    const Bounds3f& bounds);
  virtual ~BVHPrimitiveInfo ();

  BVHPrimitiveInfo (const BVHPrimitiveInfo&  info) = default;
  BVHPrimitiveInfo (      BVHPrimitiveInfo&& info) = default;


  /* BVHprimitiveinfo operators */
  auto operator = (const BVHPrimitiveInfo&  info) -> BVHPrimitiveInfo& = default;
  auto operator = (      BVHPrimitiveInfo&& info) -> BVHPrimitiveInfo& = default;


  /* BVHprimitiveinfo data */
  Point3f     centroid;
  Bounds3f    bounds;
  std::size_t primitive_number; // Index for reference to primitive
};

}  // namespace niepce

#endif // _BVH_PRIMITIVE_INFO_H_
