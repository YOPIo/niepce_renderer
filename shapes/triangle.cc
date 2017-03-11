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
                               const Point2f&   uv_coordinate) :
    position(local_to_world * position),
    normal(local_to_world * normal),
    tangent(local_to_world * tangent),
    uv(uv_coordinate)
{}

TriangleVertex::~TriangleVertex()
{}

/*
  TriangleMesh's methods
*/
TriangleMesh::TriangleMesh(unsigned int    num_triangles,  unsigned int          num_vertices,
                           const int*      vertex_indices, const TriangleVertex* mesh) :
    num_triangles_(num_triangles), num_vertices_(num_vertices),
    vertex_indices_(vertex_indices, vertex_indices + 3 * num_triangles),
    mesh_(mesh, std::default_delete<TriangleVertex[]>())
{}

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
  // FIXME: 
  const Point3f p0 = mesh_->operator[](indices_[0]).position;
  const Point3f p1 = mesh_->operator[](indices_[1]).position;
  const Point3f p2 = mesh_->operator[](indices_[2]).position;
  return 0.5f * Cross(p1 - p0, p2 - p0).Length();
}

auto Triangle::LocalBoundingBox() const -> BBox3f
{
  // Because all of vertices located in world coordinate, transform them to local coordinate
  // FIXME: 
  const Point3f p0 = *local_to_world_ * mesh_->operator[](indices_[0]).position;
  const Point3f p1 = *local_to_world_ * mesh_->operator[](indices_[1]).position;
  const Point3f p2 = *local_to_world_ * mesh_->operator[](indices_[2]).position;
  return BBox3f({p0, p1, p2});
}

auto Triangle::WorldBoundingBox() const -> BBox3f
{
  // FIXME: 
  const Point3f p0 = mesh_->operator[](indices_[0]).position;
  const Point3f p1 = mesh_->operator[](indices_[1]).position;
  const Point3f p2 = mesh_->operator[](indices_[2]).position;
  return BBox3f({p0, p1, p2});
}

auto Triangle::IsIntersect(const Ray &ray, Float *t, SurfaceInteraction *surface) const -> bool
{
  // TODO: 
  return true;
}

}  // namespace niepce

