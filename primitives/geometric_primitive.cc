#include "geometric_primitive.h"

namespace niepce
{

GeometricPrimitive::GeometricPrimitive () :
    shape_    (nullptr),
    material_ (nullptr)
{}

GeometricPrimitive::GeometricPrimitive (const std::shared_ptr<Shape>&    shape,
                                        const std::shared_ptr<Material>& material) :
    shape_    (shape),
    material_ (material)
{}

GeometricPrimitive::~GeometricPrimitive()
{}

auto GeometricPrimitive::WorldBounds () const -> Bounds3f
{
  return shape_->WorldBounds ();
}

auto GeometricPrimitive::LocalBounds () const -> Bounds3f
{
  return shape_->LocalBounds ();
}

auto GeometricPrimitive::SurfaceArea () const -> Float
{
  return shape_->SurfaceArea ();
}

auto GeometricPrimitive::IsIntersect(const Ray& ray, Interaction *interaction) const -> bool
{
  if ( shape_->IsIntersect (ray, interaction) ) { return true; }
  return false;
}

}  // namespace niepce
