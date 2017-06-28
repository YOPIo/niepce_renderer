#ifndef _TRIANGLE_MESH_H_
#define _TRIANGLE_MESH_H_

#include "../core/niepce.h"
#include "vertex.h"

namespace niepce
{

struct TriangleMesh
{
  using Vertices = std::vector<std::shared_ptr<Vertex>>;
  using Indices  = std::vector<unsigned int>;

  /* TriangleMesh constructors */
  TriangleMesh () = delete;
  TriangleMesh (const Vertices& vertices,
                const Indices&  vertex_indices,
                const Indices&  material_indices);

  virtual ~TriangleMesh ();
  TriangleMesh (const TriangleMesh&  tm) = default;
  TriangleMesh (      TriangleMesh&& tm) = default;


  /* TriangleMesh operators */
  auto operator = (const TriangleMesh&  tm) -> TriangleMesh& = default;
  auto operator = (      TriangleMesh&& tm) -> TriangleMesh& = default;


  /* TriangleMesh methods */
  auto GetVertex         (unsigned int idx)       -> std::shared_ptr<Vertex>;
  auto GetFaceIndices    (unsigned int idx) const -> std::array<unsigned int, 3>;
  auto GetMaterialIndex  (unsigned int idx) const -> unsigned int;
  auto NumberOfTriangles ()                 const -> unsigned int;

  /* TriangleMesh debug methods */
  auto DumpTriangles () -> void;


  /* TriangleMesh private data */
 private:
  unsigned int num_triangles_;
  Vertices     vertices_;
  Indices      vertex_indices_;
  Indices      material_indices_;
};

}  // namespace niepce

#endif // _TRIANGLE_MESH_H_
