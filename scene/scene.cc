#include "scene.h"

namespace niepce
{

Scene::Scene ()
{
  // Construct default scene
  MakeCornellBox();
}

Scene::Scene (const char* filename)
{
  // Load a scene
  // LoadScene (filename);
}

Scene::~Scene ()
{}

// Reference: http://www.graphics.cornell.edu/online/box/data.html
auto Scene::MakeCornellBox () -> void
{
  constexpr unsigned int               num_faces = 32;
  std::vector<std::shared_ptr<Vertex>> vertices(28, nullptr);
  std::vector<unsigned int>            vertex_indices   (96);
  std::vector<unsigned int>            material_indices (num_faces);

  std::vector<std::shared_ptr<Material>> materials;
  std::shared_ptr<TriangleMesh>          mesh;

  // Initialize vertices
  // Cornel box body
  vertices[ 0].reset (new  Vertex(  0.0,   0.0,   0.0));
  vertices[ 1].reset (new  Vertex(550.0,   0.0,   0.0));
  vertices[ 2].reset (new  Vertex(550.0,   0.0, 550.0));
  vertices[ 3].reset (new  Vertex(  0.0,   0.0, 550.0));
  vertices[ 4].reset (new  Vertex(  0.0, 550.0,   0.0));
  vertices[ 5].reset (new  Vertex(550.0, 550.0,   0.0));
  vertices[ 6].reset (new  Vertex(550.0, 550.0, 550.0));
  vertices[ 7].reset (new  Vertex(  0.0, 550.0, 550.0));

  // Light
  vertices[ 8].reset (new Vertex(210.0, 550.0, 210.0));
  vertices[ 9].reset (new Vertex(340.0, 550.0, 210.0));
  vertices[10].reset (new Vertex(340.0, 550.0, 340.0));
  vertices[11].reset (new Vertex(210.0, 550.0, 340.0));

  // Short block
  vertices[12].reset (new Vertex( 82.0, 165.0, 225.0));
  vertices[13].reset (new Vertex(130.0, 165.0,  65.0));
  vertices[14].reset (new Vertex(290.0, 165.0, 114.0));
  vertices[15].reset (new Vertex(240.0, 165.0, 272.0));
  vertices[16].reset (new Vertex( 82.0,   0.0, 225.0));
  vertices[17].reset (new Vertex(130.0,   0.0,  65.0));
  vertices[18].reset (new Vertex(290.0,   0.0, 114.0));
  vertices[19].reset (new Vertex(240.0,   0.0, 272.0));

  // Tall block
  vertices[20].reset (new Vertex(423.0, 330.0, 247.0));
  vertices[21].reset (new Vertex(265.0, 330.0, 296.0));
  vertices[22].reset (new Vertex(314.0, 330.0, 456.0));
  vertices[23].reset (new Vertex(472.0, 330.0, 406.0));
  vertices[24].reset (new Vertex(423.0,   0.0, 247.0));
  vertices[25].reset (new Vertex(265.0,   0.0, 296.0));
  vertices[26].reset (new Vertex(314.0,   0.0, 456.0));
  vertices[27].reset (new Vertex(472.0,   0.0, 406.0));

  // Initialize indices
  // Floor (cornell box)
  vertex_indices[ 0] =  0, vertex_indices[ 1] =  2, vertex_indices[ 2] =  1, material_indices[ 0] = 0;
  vertex_indices[ 3] =  0, vertex_indices[ 4] =  3, vertex_indices[ 5] =  2, material_indices[ 1] = 0;
  // Celling (cornell box)
  vertex_indices[ 6] =  4, vertex_indices[ 7] =  5, vertex_indices[ 8] =  7, material_indices[ 2] = 0;
  vertex_indices[ 9] =  5, vertex_indices[10] =  6, vertex_indices[11] =  7, material_indices[ 3] = 0;
  // Back wall (cornell box)
  vertex_indices[12] =  0, vertex_indices[13] =  1, vertex_indices[14] =  5, material_indices[ 4] = 0;
  vertex_indices[15] =  0, vertex_indices[16] =  5, vertex_indices[17] =  4, material_indices[ 5] = 0;
  // Red right wall (cornell box)
  vertex_indices[18] =  1, vertex_indices[19] =  2, vertex_indices[20] =  6, material_indices[ 6] = 1;
  vertex_indices[21] =  1, vertex_indices[22] =  6, vertex_indices[23] =  5, material_indices[ 7] = 1;
  // Green left wall (cornell box)
  vertex_indices[24] =  0, vertex_indices[25] =  4, vertex_indices[26] =  7, material_indices[ 8] = 2;
  vertex_indices[27] =  0, vertex_indices[28] =  7, vertex_indices[29] =  3, material_indices[ 9] = 2;
  // Light (cornell box)
  vertex_indices[30] =  9, vertex_indices[31] = 10, vertex_indices[32] = 11, material_indices[10] = 3;
  vertex_indices[33] =  9, vertex_indices[34] = 11, vertex_indices[35] =  8, material_indices[11] = 3;

  // Top (short block)
  vertex_indices[36] = 12, vertex_indices[37] = 14, vertex_indices[38] = 13, material_indices[12] = 0;
  vertex_indices[39] = 12, vertex_indices[40] = 15, vertex_indices[41] = 14, material_indices[13] = 0;
  // Front (short block)
  vertex_indices[42] = 14, vertex_indices[43] = 15, vertex_indices[44] = 18, material_indices[14] = 0;
  vertex_indices[45] = 15, vertex_indices[46] = 19, vertex_indices[47] = 18, material_indices[15] = 0;
  // Back (short block)
  vertex_indices[48] = 12, vertex_indices[49] = 17, vertex_indices[50] = 13, material_indices[16] = 0;
  vertex_indices[51] = 12, vertex_indices[52] = 16, vertex_indices[53] = 17, material_indices[17] = 0;
  // Right (short block)
  vertex_indices[54] = 13, vertex_indices[55] = 14, vertex_indices[56] = 18, material_indices[18] = 0;
  vertex_indices[57] = 13, vertex_indices[58] = 18, vertex_indices[59] = 17, material_indices[19] = 0;
  // Left (short block)
  vertex_indices[60] = 12, vertex_indices[61] = 19, vertex_indices[62] = 15, material_indices[20] = 0;
  vertex_indices[63] = 12, vertex_indices[64] = 16, vertex_indices[65] = 19, material_indices[21] = 0;

  // Top (tall block)
  vertex_indices[66] = 20, vertex_indices[67] = 21, vertex_indices[68] = 23, material_indices[22] = 0;
  vertex_indices[69] = 21, vertex_indices[70] = 22, vertex_indices[71] = 23, material_indices[23] = 0;
  // Front (tall block
  vertex_indices[72] = 22, vertex_indices[73] = 26, vertex_indices[74] = 23, material_indices[24] = 0;
  vertex_indices[75] = 23, vertex_indices[76] = 26, vertex_indices[77] = 27, material_indices[25] = 0;
  // Back (tall block))
  vertex_indices[78] = 20, vertex_indices[79] = 25, vertex_indices[80] = 21, material_indices[26] = 0;
  vertex_indices[81] = 20, vertex_indices[82] = 24, vertex_indices[83] = 25, material_indices[27] = 0;
  // Right (tall block)
  vertex_indices[84] = 20, vertex_indices[85] = 23, vertex_indices[86] = 27, material_indices[28] = 0;
  vertex_indices[87] = 20, vertex_indices[88] = 27, vertex_indices[89] = 24, material_indices[29] = 0;
  // Left (tall block)
  vertex_indices[90] = 21, vertex_indices[91] = 26, vertex_indices[92] = 22, material_indices[30] = 0;
  vertex_indices[93] = 21, vertex_indices[94] = 25, vertex_indices[95] = 26, material_indices[31] = 0;


  // Material intialization
  std::shared_ptr<Material> white (new Lambert( Vector3f(0.5, 0.5, 0.5),    // Emission
                                                Vector3f(0.4, 0.4, 0.4)) ); // Reflectance
  std::shared_ptr<Material> red   (new Lambert( Vector3f(0.5, 0.0, 0.0),    // Emission
                                                Vector3f(0.5, 0.0, 0.0)) ); // Reflectance
  std::shared_ptr<Material> green (new Lambert( Vector3f(0.0, 0.5, 0.0),    // Emission
                                                Vector3f(0.0, 0.5, 0.0)) ); // Reflectance
  std::shared_ptr<Material> light (new Lambert()); // TODO:
  materials.push_back (white); // Material index 0
  materials.push_back (red);   // Material index 1
  materials.push_back (green); // Material index 2
  materials.push_back (light); // Material index 3

  mesh.reset (new TriangleMesh (vertices, vertex_indices, material_indices) ) ;

  // Construct primitives
  const std::vector<std::shared_ptr<Primitive>> primitives = MakePrimitives (mesh, materials);

  // Build bvh or kdtree
  Construct (primitives);
}

auto Scene::GetSettings () const -> Settings
{
  return settings_;
}

auto Scene::IsIntersect (const Ray &ray, Interaction *interaction) -> bool
{
  
}

auto Scene::MakePrimitives (const std::shared_ptr<TriangleMesh>&          mesh,
                            const std::vector<std::shared_ptr<Material>>& materials)
-> std::vector<std::shared_ptr<Primitive>>
{
  std::vector<std::shared_ptr<Primitive>> res;
  for (int i = 0; i < mesh->NumberOfTriangles(); ++i)
  {
    const unsigned int                m_index   = mesh->GetMaterialIndex(i);
    const std::array<unsigned int, 3> v_indices = mesh->GetFaceIndices(i);

    const std::shared_ptr<Shape>      triangle (new Triangle (mesh->GetVertex(v_indices[0]),
                                                              mesh->GetVertex(v_indices[1]),
                                                              mesh->GetVertex(v_indices[2])) );

    const std::shared_ptr<Primitive>  primitive (new GeometricPrimitive (std::move (triangle),
                                                                         materials[m_index]));
    res.push_back (primitive);
  }
  return res;
}

auto Scene::Construct (const std::vector<std::shared_ptr<Primitive>>& primitives) -> void
{
  // Construct BVH
  root_.reset ( new BVH(primitives) );
}

}  // namespace niepce
