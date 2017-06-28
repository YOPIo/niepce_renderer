#include "light.h"

namespace niepce
{

Light::Light (LightType        type,
              unsigned int     num_samples,
              const Transform& local_to_world) :
    type_           (type),
    num_samples_    (num_samples),
    local_to_world_ (local_to_world),
    world_to_local_ () // Todo: inverse matrix
{}

Light::~Light ()
{}

}  // namespace niepce
