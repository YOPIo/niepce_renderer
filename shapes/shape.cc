#include "shape.h"

namespace niepce
{

Shape::Shape() :
    local_to_world_(nullptr),
    world_to_local_(nullptr)
{}

Shape::Shape(const Point3f& p) :
    local_to_world_(new Transform(p)),
    world_to_local_(new Transform(local_to_world_->GetInvMatrix()))
{}

Shape::Shape(const std::shared_ptr<Transform>& local_to_world,
             const std::shared_ptr<Transform>& world_to_local) :
    local_to_world_(local_to_world),
    world_to_local_(world_to_local)
{}

Shape::~Shape()
{}

} // namespace niepce
