#include "sphere.h"

namespace niepce
{

Sphere::Sphere(const std::shared_ptr<Transform>& object_to_world,
               const std::shared_ptr<Transform>& world_to_object,
               const Float radius) :
    Shape(object_to_world, world_to_object),
    radius_(radius)
{}

Sphere::~Sphere()
{}

auto Sphere::SurfaceArea() const -> Float
{

}

auto Sphere::ObjectBound() const -> Bound3f
{

}

auto Sphere::IsIntersect(const Ray &ray, Float *t, SurfaceInteraction *surface) -> bool
{
  // Transform Ray to object space

}

}  // namespace niepce
