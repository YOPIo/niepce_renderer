#include "triangle.h"

namespace niepce
{

Triangle::Triangle(Vertex v1,
                   Vertex v2,
                   Vertex v3) :
    vertexes_({v1, v2, v3})
{}

Triangle::Triangle(std::array<Vertex, 3>& v) :
    vertexes_(v)
{}

auto Triangle::IsIntersect(const Ray& ray, HitRecord* hit_record) const -> bool
{
  glm::vec3 edge1 = vertexes_[1].position_ - vertexes_[0].position_;
  glm::vec3 edge2 = vertexes_[2].position_ - vertexes_[0].position_;
  glm::vec3 t     = ray.origin_ - vertexes_[0].position_;
  glm::vec3 p     = cross(ray.direction_, edge2);
  Float det = dot(edge1, p);
  if (-kEps < det && det < kEps)    return false;

  Float reciprocal = 1.0f / det;
  Float u = dot(t, p) * reciprocal;
  if (u < 0.0 || u > 1.0)           return false;

  glm::vec3 q = cross(t, edge1);
  Float v = dot(ray.direction_, q);
  if (v < 0.0 || u + v > 1.0)       return false;

  hit_record->distance_ = dot(edge2, q) * reciprocal;
  if (hit_record->distance_ < kEps) return false;

  hit_record->position_ = ray.origin_ + ray.direction_ * hit_record->distance_;
  hit_record->normal_   = normalize( cross(edge1, edge2) );
  return true;
}

} // namespace niepce
