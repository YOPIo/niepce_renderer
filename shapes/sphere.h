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
  Sphere(const Transform* object_to_world,
         const Transform* world_to_object,
         Float radius);
  virtual ~Sphere();

  Sphere(const Sphere& sphere) = default;
  Sphere(Sphere&& sphere)      = default;

  auto operator = (const Sphere& sphere) -> Sphere& = default;
  auto operator = (Sphere&& sphere)      -> Sphere& = default;

  auto SurfaceArea() const -> Float;
  auto LocalBoundingBox() const -> BBox3f;
  auto WorldBoundingBox() const -> BBox3f;
  auto IsIntersect(const Ray& ray, Float* t, SurfaceInteraction* surface) -> bool;

 private:
  const Float radius_;

  /*
  const Float z_min_, z_max_;

  Theta range: [0,  pi]
  Phi range  : [0, 2pi]
  const Float theta_min_, theta_max_, phi_max_;
  */
};

}  // namespace niepce

#endif // _SPHERE_H_
