#include "../core/niepce.h"
#include "../core/transform.h"
#include "shape.h"

namespace niepce
{

/*
  NOTE: All of vertex positions of triangles are stored as world space coordinate
*/
struct TriangleVertex
{
  TriangleVertex() = delete;
  TriangleVertex(const Transform& local_to_world,
                 const Point3f&   position,
                 const Normal3f&  normal,
                 const Vector3f&  tangent,
                 const Point2f&   uv);
  virtual ~TriangleVertex();

  TriangleVertex(const TriangleVertex& tm) = default;
  TriangleVertex(TriangleVertex&& tm)      = default;

  auto operator = (const TriangleVertex& tm) -> TriangleVertex& = default;
  auto operator = (TriangleVertex&& tm)      -> TriangleVertex& = default;

  Point3f  position; // Vertex positions
  Normal3f normal;   // Normal vectors at the vertex position
  Vector3f tangent;  // Tangent vectors at the vertex position
  Point2f  uv;       // Parametric (u, v) values at the vertex position
};

struct TriangleMesh
{
  TriangleMesh() = delete;
  TriangleMesh(unsigned int    num_triangle,   unsigned int          num_vertices,
               const int*      vertex_indices, const TriangleVertex* mesh);
  virtual ~TriangleMesh();

  TriangleMesh(const TriangleMesh& tm) = default;
  TriangleMesh(TriangleMesh&& tm)      = default;

  auto operator = (const TriangleMesh& tm) -> TriangleMesh& = default;
  auto operator = (TriangleMesh&& tm)      -> TriangleMesh& = default;

  auto operator [] (unsigned int idx) const -> TriangleVertex;
  auto operator [] (unsigned int idx)       -> TriangleVertex&;

  // Member data
  const unsigned int num_triangles_; // Number of tirangles
  const unsigned int num_vertices_;  // Number of vertices

  std::vector<unsigned int>       vertex_indices_; // An array of indices
  std::shared_ptr<TriangleVertex> mesh_;           // An array of vertices
};

/*
  Triangle class has three indices
*/
class Triangle : public Shape
{
 public:
  Triangle() = delete;
  Triangle(const Transform*    local_to_world, const Transform* world_to_local,
           const TriangleMesh* mesh,           unsigned int*    idx);
  virtual ~Triangle();

  Triangle(const Triangle& t) = default;
  Triangle(Triangle&& t)      = default;

  auto operator = (const Triangle& t) -> Triangle& = default;
  auto operator = (Triangle&& t)      -> Triangle& = default;

  auto SurfaceArea() const -> Float;
  auto LocalBoundingBox() const -> BBox3f;
  auto WorldBoundingBox() const -> BBox3f;
  auto IsIntersect(const Ray& ray, Float* t, SurfaceInteraction* surface) const -> bool;

 private:
  std::shared_ptr<TriangleMesh> mesh_;
  std::array<unsigned int, 3>   indices_; // A fixed array of references to face
};

/*

*/


}  // namespace niepce
