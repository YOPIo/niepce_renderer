#ifndef _STATIC_PRIMITIVE_H_
#define _STATIC_PRIMITIVE_H_

#include "primitive.h"

#include "../core/niepce.h"
#include "../materials/material.h"
#include "../shapes/shape.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// This class have a shape and material
// ---------------------------------------------------------------------------
class GeometricPrimitive : public Primitive
{
  /* Geometricprimitive constructors */
 public:
  GeometricPrimitive ();
  GeometricPrimitive (const std::shared_ptr<Shape>&    shape,
                      const std::shared_ptr<Material>& material);
  virtual ~GeometricPrimitive ();

  GeometricPrimitive (const GeometricPrimitive&  primitive) = default;
  GeometricPrimitive (      GeometricPrimitive&& primitive) = default;


  /* GeometricPrimitive operators */
 public:
  auto operator = (const GeometricPrimitive& primitive) -> GeometricPrimitive& = default;
  auto operator = (GeometricPrimitive&& primitive)      -> GeometricPrimitive& = default;


  /* GeometricPrimitive override functions */
 public:
  // Return bounding box in world or local space coordinate
  auto WorldBounds () const -> Bounds3f override;
  auto LocalBounds () const -> Bounds3f override;

  // Return surface area of a primitive
  auto SurfaceArea () const -> Float override;

  // Ray-Object intersection test interface
  auto IsIntersect (const Ray& ray, Interaction* interaction) const -> bool override;


  /* GeometricPrimitive private data */
 private:
  std::shared_ptr<Shape>    shape_;
  std::shared_ptr<Material> material_;

}; // class GeometricPrimitive


}  // namespace niepce

#endif // _STATIC_PRIMITIVE_H_
