#ifndef _FACE_H_
#define _FACE_H_

#include <memory>

#include "../core/common.h"
#include "geometry.h"
#include "../material/material.h"

namespace niepce
{

class Face
{
 public:
  using GeometryPtr = std::shared_ptr<Geometry>;
  using MaterialPtr = std::shared_ptr<Material>;

 public:
  Face() = default;
  Face(const GeometryPtr& geometry, const MaterialPtr& material);
  Face(GeometryPtr&& geometry, MaterialPtr&& material);
  virtual ~Face() = default;

  Face(const Face& face) = default;
  Face(Face&& face)      = default;
  Face& operator = (const Face& face) = default;
  Face& operator = (Face&& face)      = default;

  auto Geometry() const -> const GeometryPtr;
  auto Material() const -> const MaterialPtr;

  auto IsIntersect(const Ray& ray, HitRecord* hit_record) const -> bool;

 private:
  GeometryPtr geometry_;
  MaterialPtr material_;
};

} // namespace niepce

#endif // _FACE_H_
