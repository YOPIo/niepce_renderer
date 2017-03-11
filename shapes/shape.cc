#include "shape.h"

namespace niepce
{

Shape::Shape()
{}

Shape::Shape(const Transform* object_to_world,
             const Transform* world_to_object) :
    local_to_world_(object_to_world),
    world_to_local_(world_to_object)
{}

Shape::~Shape()
{}

} // namespace niepce
