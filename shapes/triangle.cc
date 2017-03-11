#include "triangle.h"

namespace niepce
{

/*
  TriangleVertex's methods
*/
TriangleVertex::TriangleVertex(const Transform& local_to_world,
                               const Point3f&   position,
                               const Normal3f&  normal,
                               const Vector3f&  tangent,
                               const Point2f&   uv) :
    position_(local_to_world * position),
    normal_(local_to_world * normal),
    tangent_(local_to_world * tangent),
    uv_(uv)
{}

TriangleVertex::~TriangleVertex()
{}

/*
  TriangleMesh's methods
*/
TriangleMesh::TriangleMesh(unsigned int    num_triangles,  unsigned int          num_vertices,
                           const int*      vertex_indices, const TriangleVertex* mesh) :
    num_triangles_(num_triangles), num_vertices_(num_vertices)
{
  mesh_ = std::shared_ptr<TriangleVertex[]>(mesh, std::default_delete<TriangleVertex[]>());
}

TriangleMesh::~TriangleMesh()
{}

auto TriangleMesh::operator [] (unsigned int idx) const -> TriangleVertex
{
  Assertf(idx < num_vertices_, "Out of range [0, %d]", num_vertices_ - 1);
  return mesh_.get()[idx];
}

auto TriangleMesh::operator [] (unsigned int idx) -> TriangleVertex&
{
  Assertf(idx < num_vertices_, "Out of range [0, %d]", num_vertices_ - 1);
  return mesh_.get()[idx];
}

/*
  Triangle's methods
*/

Triangle::Triangle(const Transform*    local_to_world, const Transform* world_to_local,
                   const TriangleMesh* mesh,           unsigned int*    idx) :
    Shape(local_to_world, world_to_local),
    mesh_(mesh),
    indices_({idx[0], idx[1], idx[2]})
{}

Triangle::~Triangle()
{}

auto Triangle::SurfaceArea() const -> Float
{
  // Transform vertex to local space

}

auto Triangle::LocalBoundingBox() const -> BBox3f
{
}

auto Triangle::WorldBoundingBox() const -> BBox3f
{
}

auto Triangle::IsIntersect(const Ray &ray, Float *t, SurfaceInteraction *surface) const -> bool
{

  return true;
}

}  // namespace niepce

