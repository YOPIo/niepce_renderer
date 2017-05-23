#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../core/boundingbox2.h"
#include "../core/boundingbox3.h"
#include "../core/interaction.h"
#include "../core/niepce.h"
#include "../core/ray.h"
#include "../geometries/normal3.h"
#include "../geometries/point2.h"
#include "../geometries/point3.h"
#include "../geometries/point4.h"
#include "../geometries/vector2.h"
#include "../geometries/vector3.h"
#include "../geometries/vector4.h"
#include "shape.h"

namespace niepce
{

class Sphere : public Shape
{
 public:
  Sphere();
  Sphere(const std::shared_ptr<Transform>& object_to_world,
         const std::shared_ptr<Transform>& world_to_object,
         Float radius);
  Sphere(const Point3f& p, Float radius);
  virtual ~Sphere();

  Sphere(const Sphere& sphere) = default;
  Sphere(Sphere&& sphere)      = default;

  auto operator = (const Sphere& sphere) -> Sphere& = default;
  auto operator = (Sphere&& sphere)      -> Sphere& = default;


  // ---------------------------------------------------------------------------
  // Sphere public override methods
  // ---------------------------------------------------------------------------
 public:
  auto SurfaceArea()      const -> Float    override;
  auto LocalBoundingBox() const -> Bounds3f override;
  auto WorldBoundingBox() const -> Bounds3f override;
  auto IsIntersect(const Ray&   ray,
                   Interaction* inter) const -> bool override;


  // ---------------------------------------------------------------------------
  // Sphere private data
  // ---------------------------------------------------------------------------
 private:
  const Float radius_;
};

}  // namespace niepce

#endif // _SPHERE_H_
