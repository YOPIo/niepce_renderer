#include "triangle_mesh.h"

namespace niepce
{

TriangleMesh::TriangleMesh (const Vertices& vertices,
                            const Indices&  vertex_indices,
                            const Indices&  material_indices)
{
  // Copy vertices
  vertices_.clear();
  vertices_ = Vertices (vertices);

  // Copy vertex indices
  vertex_indices_.clear();
  vertex_indices_ = std::vector<unsigned int>(vertex_indices);

  // Copy material indices
  material_indices_.clear();
  material_indices_ = std::vector<unsigned int>(material_indices);
}

TriangleMesh::~TriangleMesh ()
{}

auto TriangleMesh::GetVertex (unsigned int idx) -> std::shared_ptr<Vertex>
{
  // TODO: Range check
  return vertices_[idx];
}

auto TriangleMesh::GetFaceIndices (unsigned int idx) const -> std::array<unsigned int, 3>
{
  // TODO: Range check
  return {vertex_indices_[3 * idx + 0],
          vertex_indices_[3 * idx + 1],
          vertex_indices_[3 * idx + 2]};
}

auto TriangleMesh::GetMaterialIndex (unsigned int idx) const -> unsigned int
{
  // TODO: Range check
  return material_indices_[idx];
}

auto TriangleMesh::NumberOfTriangles () const -> unsigned int
{
  return vertex_indices_.size() / 3;
}

auto TriangleMesh::DumpTriangles () -> void
{
  const unsigned int num_faces = vertex_indices_.size () / 3;

  std::cerr << material_indices_.size () << std::endl;

  std::cerr << "Numver of faces: " << num_faces << std::endl;
  for (int i = 0; i < num_faces; ++i)
  {
    const std::array<unsigned int, 3> indices = GetFaceIndices(i);

    std::cerr << "Face " << i << " : ";
    std::cerr << indices[0] << ", "
              << indices[1] << ", "
              << indices[2] << ", "
              << "Material : "
              << GetMaterialIndex(i) << std::endl;
  }

}

}  // namespace niepce
