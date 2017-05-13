#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "niepce.h"
#include "vector3.h"
#include "material.h"
#include "ray.h"

class Sphere
{
 public:
  Sphere()
  {}
  Sphere(const Float                     radius,
         const Vector3f&                 position,
         const std::shared_ptr<Material> material) :
      radius_(radius),
      position_(position),
      material_(material)
  {}
  virtual ~Sphere()
  {};

  Sphere(const Sphere& sphere) = default;
  Sphere(Sphere&& sphere)      = default;

  auto operator = (const Sphere& sphere) -> Sphere& = default;
  auto operator = (Sphere&& sphere)      -> Sphere& = default;


  // ---------------------------------------------------------------------------
  // Sphere public methods
  // ---------------------------------------------------------------------------
  auto IsIntersect(const Ray &ray, Float* t) const -> bool
  {
    const Vector3f o_p = position_ - ray.origin;
    const Float b   = Dot(o_p, ray.direction);
    const Float det = b * b - Dot(o_p, o_p) + radius_ * radius_;

    if (det < 0) { return false; }

    const Float sqrt_det = std::sqrt(det);
    const Float t1 = b - sqrt_det;
    const Float t2 = b + sqrt_det;

    if (t1 < kEpsilon && t2 < kEpsilon) { return false; }
    if (t1 > kEpsilon) { *t = t1; return true; }
    if (t2 > kEpsilon) { *t = t2; return true; }
    return false;
  }

  auto GetMaterial() const -> const std::shared_ptr<Material>
  {
    return material_;
  }

  auto GetRadius() const -> Float
  {
    return radius_;
  }

  auto GetPosition() const -> Vector3f
  {
    return position_;
  }


  // ---------------------------------------------------------------------------
  // Sphere private member data
  // ---------------------------------------------------------------------------
 private:
  Float    radius_;
  Vector3f position_;
  std::shared_ptr<Material> material_;
};


#endif // _SPHERE_H_
