#ifndef _BVH_BUCKET_H_
#define _BVH_BUCKET_H_

#include "../core/niepce.h"
#include "../geometries/boundingbox3.h"

// ---------------------------------------------------------------------------
//  Bucket struct is used only for SAH algorithm
// ---------------------------------------------------------------------------

namespace niepce
{

struct Bucket
{
  unsigned int count = 0;
  Bounds3f     bounds;
};

}  // namespace niepce

#endif // _BVH_BUCKET_H_
