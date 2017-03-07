#include "shape.h"

namespace niepce
{

Shape::Shape()
{}

Shape::Shape(const std::shared_ptr<Transform>& object_to_world,
             const std::shared_ptr<Transform>& world_to_object) :
    object_to_world_(object_to_world),
    world_to_object_(world_to_object)
{}

Shape::~Shape()
{}

} // namespace niepce
