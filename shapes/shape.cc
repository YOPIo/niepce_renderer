#include "shape.h"

namespace niepce
{

Shape::Shape()
{}

Shape::Shape(const std::shared_ptr<Transform>& object_to_world,
             const std::shared_ptr<Transform>& world_to_object) :
    local_to_world_(object_to_world),
    world_to_local_(world_to_object)
{}

Shape::~Shape()
{}

auto Shape::ToLocalMatrix() -> Matrix4x4f
{
  return world_to_local_->GetMatrix();
}

auto Shape::ToWorldMatrix() -> Matrix4x4f
{
  return local_to_world_->GetMatrix();
}

} // namespace niepce
