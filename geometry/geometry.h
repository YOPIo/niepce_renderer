#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../core/common.h"

namespace niepce
{

// interface
class Geometry
{
 protected:
  Geometry();
 public:
  virtual ~Geometry();

  Geometry(const Geometry& geometry) = default;
  Geometry(Geometry&& geometry)      = default;
  Geometry& operator = (const Geometry& geometry) = default;
  Geometry& operator = (Geometry&& geometry)      = default;

  virtual auto IsIntersect(const Ray& ray, HitRecord* hit_record) const -> bool = 0;
};


} // namespace niepce


#endif // _GEOMETRY_H_
