/*
// ---------------------------------------------------------------------------
*/
#include "scene_loader.h"
#include "../core/geometry.h"
#include "../camera/camera.h"
#include "../shape/triangle.h"
/*
// ---------------------------------------------------------------------------
// Tinyobj loader include
// ---------------------------------------------------------------------------
*/
#define TINYOBJLOADER_IMPLEMENTATION
#include "../ext/tinyobjloader/tiny_obj_loader.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::LoadXml (const char* filename, Scene* scene, Camera* camera) -> void
{
  using tinyxml2::XMLDocument;
  using tinyxml2::XMLElement;

  // Store file directory
  const std::string fullpath (filename);
  auto idx = fullpath.find_last_of ("/");
  base_path = fullpath.substr (0, idx + 1);

  // Load xml scene file
  XMLDocument xml;
  if (xml.LoadFile (filename))
  {
    std::cerr << "Could not open " << filename << "." << std::endl;
    return ;
  }

  // Get root element
  auto root = xml.RootElement ();

  // Loop over elements
  for (auto node = root->FirstChild ();
       node != NULL;
       node = node->NextSibling () )
  {
    // Get current element and its name
    auto element = node->ToElement ();
    auto name    = std::string (element->Name ());

    // Element should be bsdf, shape, sensor or integrator
    if (name == "bsdf")
    {
      ParseBsdf (node);
      continue;
    }
    if (name == "shape")
    {
      ParseShape (node);
      continue;
    }
    if (name == "sensor")
    {
      ParseSensor (node);
      continue;
    }
    if (name == "integrator")
    {
      continue;
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseBsdf (const tinyxml2::XMLNode* node) -> void
{
  // Get type of BSDF
  const tinyxml2::XMLElement* root_element = node->ToElement ();
  const std::string type = root_element->Attribute ("type");

  MaterialAttributes mtl_attribs;
  for (auto n = node->FirstChild (); n != NULL; n = n->NextSibling ())
  {
    // Get element of child and its name
    const auto elem = n->ToElement ();
    const std::string elem_name = elem->Name ();

    if (elem_name == "rgb")
    {
      
    }
    if (elem_name == "srgb")
    {
      // Todo: support
    }
    if (elem_name == "spectrum")
    {
      // Todo: support
    }

  }
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseSensor (const tinyxml2::XMLNode* node) -> void
{
  // Todo: implementation
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseShape (const tinyxml2::XMLNode* node) -> void
{
  // Specify the type of shape
  const std::string attrib = node->ToElement () ->Attribute ("type");

  if (attrib == "obj")
  {
    // Loop over shape element
    for (auto n = node->FirstChild (); n != NULL; n = n->NextSibling ())
    {
      auto elem = n->ToElement ();

      // nent should has a string nent at least
      if (std::strcmp (elem->Name (), "string") == 0)
      {
        // Load .obj file via tinyobj loader
        const char* obj_filename = elem->Attribute ("value");
        LoadObj ((base_path + std::string (obj_filename)).c_str ());
        continue;
      }

      // BSDF
      if (std::strcmp (elem->Name (), "bsdf") == 0)
      {
        ParseBsdf (n);
        continue;
      }

    }
    return ;
  }

  if (attrib == "sphere")
  {
    // Todo: Support sphere type
    return ;
  }
  return ;
}
/*
// ---------------------------------------------------------------------------
// XmlLoader::LoadObj ignore .mtl file if present
// ---------------------------------------------------------------------------
*/
auto XmlLoader::LoadObj (const char* filename) -> void
{
  // Load .obj file
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t>    shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err;
  bool ret = tinyobj::LoadObj (&attrib, &shapes, &materials, &err, filename);;

  // Error checking
  if (!err.empty ())
  {
    std::cerr << err << std::endl;
    return ;
  }
  if (!ret) { return ; }

  // Construct Point3f from attribute.vertices
  std::vector <Point3f> positions (attrib.vertices.size () / 3);
  for (Index i = 0; i < attrib.vertices.size () / 3; ++i)
  {
    const Float x = attrib.vertices[3 * i + 0];
    const Float y = attrib.vertices[3 * i + 1];
    const Float z = attrib.vertices[3 * i + 2];
    positions[i] = Point3f (x, y, z);
  }
  // Construct Normal3f from attribute.normals if present
  std::vector <Normal3f> normals (attrib.normals.size () / 3);
  for (Index i = 0; i < attrib.normals.size () / 3; ++i)
  {
    const Float x = attrib.normals[3 * i + 0];
    const Float y = attrib.normals[3 * i + 1];
    const Float z = attrib.normals[3 * i + 2];
    normals[i] = Normal3f (x, y, z);
  }
  // Construct Texcoord2f from attribute.texcoords if present
  std::vector <Point2f> texcoords (attrib.texcoords.size () / 2);
  for (Index i = 0; i < attrib.texcoords.size () / 2; ++i)
  {
    const Float u = attrib.texcoords[2 * i + 0];
    const Float v = attrib.texcoords[2 * i + 1];
    texcoords[i] = Point2f (u, v);
  }
  // HACKME: Compute the number of faces
  Index num_face = 0;
  for (const auto& s : shapes)
  {
    for (Index f = 0; f < s.mesh.num_face_vertices.size (); ++f)
    {
      ++num_face;
    }
  }
  // Construct triangle mesh
  const std::shared_ptr<TriangleMesh> mesh = CreateTriangleMesh (num_face,
                                                                 positions,
                                                                 normals,
                                                                 texcoords);

  // Loop over shapes
  for (size_t s = 0; s < shapes.size (); s++)
  {
    // Loop over faces(polygon)
    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size (); f++)
    {
      // Expecting fx should be 3
      const int fv = shapes[s].mesh.num_face_vertices[f];

      // Get indices to refer to triangle
      std::array <Index, 3> position_idx;
      std::array <Index, 3> normal_idx;
      std::array <Index, 3> texcoord_idx;

      // Loop over vertices in the face
      // Get indices of single face
      for (size_t v = 0; v < fv; v++)
      {
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        position_idx[v] = idx.vertex_index;
        normal_idx[v]   = idx.normal_index;
        texcoord_idx[v] = idx.texcoord_index;
      }
      index_offset += fv;

      // Create triangle face
      const ShapePtr triangle = CreateTriangle (mesh,
                                                position_idx,
                                                normal_idx,
                                                texcoord_idx);
      // hackme:
      shapes_.push_back (std::move (triangle));
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseRgb (const tinyxml2::XMLNode* node) -> void
{
  
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseSrgb (const tinyxml2::XMLNode* node) -> void
{
  
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseSpectrum (const tinyxml2::XMLNode* node) -> void
{
  
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseLambert (const tinyxml2::XMLNode* node) -> void
{
  
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseOrenNayar (const tinyxml2::XMLNode* node) -> void
{
  
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseMirror (const tinyxml2::XMLNode* node) -> void
{
  
}
/*
// ---------------------------------------------------------------------------
*/
auto XmlLoader::ParseGlass (const tinyxml2::XMLNode* node) -> void
{
  
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
