#include "triangle.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// TriangleMesh class
// ---------------------------------------------------------------------------
TriangleMesh::TriangleMesh (const std::vector<Vertex>&       mesh,
                            const std::vector<unsigned int>& indices,
                                  unsigned int               num_triangles) :
    mesh_       (mesh),
    indices_    (indices),
    kTriangles_ (num_triangles)
{}

TriangleMesh::~TriangleMesh ()
{}

auto TriangleMesh::operator [] (unsigned int idx) const -> Vertex
{
  // TODO: Range check
  return mesh_[idx];
}

// ---------------------------------------------------------------------------
// Triangle methods
// ---------------------------------------------------------------------------
Triangle::Triangle (const std::shared_ptr<TriangleMesh>& mesh,
                    const std::array<unsigned int, 3>&   indices) :
    mesh_    (mesh),
    indices_ (indices)
{}

Triangle::~Triangle ()
{}

auto Triangle::SurfaceArea() const -> Float
{
  const Point3f p0 = (*mesh_)[indices_[0]].position;
  const Point3f p1 = (*mesh_)[indices_[1]].position;
  const Point3f p2 = (*mesh_)[indices_[2]].position;
  return 0.5f * Cross(p1 - p0, p2 - p0).Length();
}

auto Triangle::LocalBoundingBox() const -> Bounds3f
{
  // Because all of vertices located in world coordinate, transform them to local coordinate
  const Point3f p0 = *local_to_world_ * (*mesh_)[indices_[0]].position;
  const Point3f p1 = *local_to_world_ * (*mesh_)[indices_[1]].position;
  const Point3f p2 = *local_to_world_ * (*mesh_)[indices_[2]].position;
  return Bounds3f ({p0, p1, p2});
}

auto Triangle::WorldBoundingBox() const -> Bounds3f
{
  const Point3f p0 = (*mesh_)[indices_[0]].position;
  const Point3f p1 = (*mesh_)[indices_[1]].position;
  const Point3f p2 = (*mesh_)[indices_[2]].position;
  return Bounds3f ({p0, p1, p2});
}

auto Triangle::IsIntersect(const Ray &ray, Float *t, SurfaceInteraction *surface) const -> bool
{
  // TODO: implementation
  return true;
}

}  // namespace niepce

