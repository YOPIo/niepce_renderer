#include "face.h"

namespace niepce
{

Face::Face(const GeometryPtr& geometry, const MaterialPtr& material) :
    geometry_(geometry),
    material_(material)
{}

Face::Face(GeometryPtr&& geometry, MaterialPtr&& material) :
    geometry_(std::move(geometry)),
    material_(std::move(material))
{}

auto Face::Geometry() const -> const Face::GeometryPtr
{
  return geometry_;
}

auto Face::Material() const -> const Face::MaterialPtr
{
  return material_;
}

auto Face::IsIntersect(const niepce::Ray &ray, niepce::HitRecord *hit_record) const -> bool
{
  return geometry_->IsIntersect(ray, hit_record);
}

} // namespace niepce
