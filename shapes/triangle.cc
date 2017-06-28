#include "triangle.h"

namespace niepce
{

Triangle::Triangle () :
    Shape ()
{}

Triangle::Triangle (const std::shared_ptr<Vertex>& v0,
                    const std::shared_ptr<Vertex>& v1,
                    const std::shared_ptr<Vertex>& v2) :
    Shape     (),
    vertices_ ( {v0, v1, v2} )
{}

Triangle::Triangle (const std::array<std::shared_ptr<Vertex>, 3>& v) :
    Shape     (),
    vertices_ (v)
{}

Triangle::~Triangle ()
{}

auto Triangle::SurfaceArea() const -> Float
{
  const Point3f p0 = vertices_[0]->position;
  const Point3f p1 = vertices_[1]->position;
  const Point3f p2 = vertices_[2]->position;
  return 0.5f * Cross(p1 - p0, p2 - p0).Length();
}

auto Triangle::LocalBounds () const -> Bounds3f
{
  // Because all of vertices located in world coordinate, transform them to local coordinate
  // TODO: implementation
  return Bounds3f ({});
}

auto Triangle::WorldBounds () const -> Bounds3f
{
  const Point3f p0 = vertices_[0]->position;
  const Point3f p1 = vertices_[1]->position;
  const Point3f p2 = vertices_[2]->position;
  return Bounds3f ({p0, p1, p2});
}


// Reference: Fast, Minimum Storage Ray/Triangle Intersection
// http://www.cs.virginia.edu/~gfx/courses/2003/ImageSynthesis/papers/Acceleration/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
auto Triangle::IsIntersect (const Ray &ray, Interaction *interaction) const -> bool
{
  // Get vertices which representing a triangle face
  const Point3f& p0 = vertices_[0]->position;
  const Point3f& p1 = vertices_[1]->position;
  const Point3f& p2 = vertices_[2]->position;

  const Vector3f edge0 = p1 - p0;
  const Vector3f edge1 = p2 - p0;

  const Vector3f vec = ray.origin - p0;

  // calculate determinant
  const Vector3f p   = Cross(ray.direction, edge1);
  const Float    det = Dot(edge0, p);

  if (-kEpsilon < det && det < kEpsilon) { return false; }

  const Float inv_det = 1.0 / det;
  const Float u       = Dot(vec, p) * inv_det;
  if (u < 0.0 || u > 1.0) { return false; }

  const Vector3f q  = Cross(vec, edge0);
  const Float    v = Dot(ray.direction, q) * inv_det;
  if (v < 0.0 || u + v > 1.0) { return false; }

  // calculate hit position
  const Float t_temp = Dot(edge1, q) * inv_det;
  if (t_temp < kEpsilon) { return false; }

  // Compute intersect position
  interaction->position = ray(t_temp);
  // Compute triangle's normal
  interaction->normal = Normalize(Cross(edge0, edge1));

  return true;
}

}  // namespace niepce
