#ifndef _COMMON_H_
#define _COMMON_H_

#include "../3rdparty/glm/glm.hpp"
#include "../random/random.h"
#include "logger.h"
#include "ray.h"
#include "hit_record.h"
#include "size.h"
#include "size_vector.h"

using Rgb = glm::vec3;

using Float = float;

namespace niepce
{
constexpr Float kEps = 1e-6;
constexpr Float kPi  = 3.14159265358979323846;
}


#endif // _COMMON_H_
