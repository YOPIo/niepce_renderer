#include "bvh_primitive_info.h"

namespace niepce
{

BVHPrimitiveInfo::BVHPrimitiveInfo () :
    centroid         (),
    bounds           (),
    primitive_number (0)
{}

BVHPrimitiveInfo::BVHPrimitiveInfo (std::size_t     index,
                                    const Bounds3f& b) :
    primitive_number (index),
    bounds           (b),
    centroid         ( (b.Min() + b.Max()) * 0.5 )
{}

BVHPrimitiveInfo::~BVHPrimitiveInfo()
{}

}  // namespace niepce
