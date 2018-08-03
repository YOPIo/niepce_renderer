/*!
 * @file scene_importer.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "scene_importer.h"
#include "../core/vector3f.h"
#include "../core/film.h"
#include "../core/transform.h"
#include "../core/material_attributes.h"
#include "../camera/camera.h"
#include "../texture/image_texture.h"
#include "../texture/value_texture.h"
#include "../material/material.h"
#include "../shape/triangle.h"
#include "../primitive/primitive.h"
#include "../light/light.h"
#include "../light/area_light.h"
#include "../light/infinite_light.h"
/*
// ---------------------------------------------------------------------------
*/
#define TINYOBJLOADER_IMPLEMENTATION
// #define TINYOBJLOADER_USE_DOUBLE
#include "../ext/tinyobjloader/tiny_obj_loader.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
SceneImporter::SceneImporter (const char* filename)
{
  Import (filename);
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::Import (const char *filename) -> void
{
  GetFileDirectory (filename, &filepath_);
  xml_.LoadFile (filename);
  root_ = xml_.RootElement ();

  if (!root_)
  {
    std::cout << "Could not found " << filename << std::endl;
    return ;
  }

  // Loop for each element.
  for (auto element = root_->FirstChildElement ();
       element != nullptr;
       element = element->NextSiblingElement ())
  {
    Attributes attributes;
    if (IsElementType (element, "camera"))
    {
      auto type = element->Attribute ("type");
      attributes.AddString ("type", type);
      ParseRecursive (element, &attributes);
      camera_ = CreateCamera (attributes);
      continue;
    }
    if (IsElementType (element, "light"))
    {
      // Parse child
      ParseRecursive (element, &attributes);
      // Get light type.
      auto type = LightType (element->Attribute ("type"));

      if (type == niepce::LightType::kInfiniteLight)
      {
        inf_lights_ = CreateInfiniteLight (attributes);
        continue;
      }
      if (type == niepce::LightType::kAreaLight)
      {
        light_attrs_.emplace (element->Attribute ("id"), attributes);
        continue;
      }
      std::cerr << "Faild to create light" << std::endl;
      continue;
    }
    if (IsElementType (element, "texture"))
    {
      // Parse children.
      ParseRecursive (element, &attributes);
      // Get texture type.
      auto type = TextureType (element->Attribute ("type"));
      // Get texture id.
      auto id = element->Attribute ("id");
      if (type == niepce::TextureType::kImageFloat)
      {
        std::cerr << "unsupporting now" << std::endl;
        continue;
      }
      if (type == niepce::TextureType::kImageSpectrum)
      {
        auto tex = CreateImageTexture <Spectrum> (attributes);
        spectrum_textures_.emplace (id, tex);
        continue;
      }
      if (type == niepce::TextureType::kValueFloat)
      {
        std::cerr << "unsupporting now" << std::endl;
        continue;
      }
      if (type == niepce::TextureType::kValueSpectrum)
      {
        std::cerr << "unsupporting now" << std::endl;
        continue;
      }
    }
    if (IsElementType (element, "material"))
    {
      auto attrib = ParseMaterial (element);
      auto id  = element->Attribute ("id");
      auto mat = CreateMaterial (attrib);
      materials_.emplace (id, mat);
      continue;
    }
    if (IsElementType (element, "shape"))
    {
      // Get shape type
      const auto type = ShapeType (element->Attribute ("type"));
      const auto id = element->Attribute("id");
      attributes.AddString ("id", id);
      ParseRecursive (element, &attributes);
      if (type == niepce::ShapeType::kTriangleMesh)
      {
        LoadObj (attributes);
        continue;
      }
      if (type == niepce::ShapeType::kSphere)
      {
        const auto radius = attributes.FindFloat ("radius");
        const auto t      = attributes.FindTransform ("transform");

        const auto sphere = CreateSphere (t, radius);

        const auto id = attributes.FindString ("material");
        const auto mat    = this->Material (id);
        if (mat == nullptr) { std::cerr << "shape sphere error" << std::endl;}
        primitives_.push_back (CreatePrimitive (sphere, mat, nullptr));
        continue;
      }
      std::cerr << "Shape element was ignored." << std::endl;
      continue;
    }
    if (IsElementType (element, "settings"))
    {
      ParseRecursive (element, &attributes);
      settings_.AddItem (RenderSettings::Item::kNumSamples,
                         attributes.FindInt ("spp"));
      settings_.AddItem (RenderSettings::Item::kPTMaxDepth,
                         attributes.FindInt ("max_depth"));
      settings_.AddItem (RenderSettings::Item::kNumRound,
                         attributes.FindInt ("round"));
    }
  }

  // Construct a scene.
  scene_.reset (CreateScene (primitives_, lights_, inf_lights_));
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ExtractScene () const noexcept -> std::shared_ptr <Scene>
{
  if (scene_) { return scene_; }
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ExtractCamera () const noexcept -> std::shared_ptr <Camera>
{
  if (camera_) { return camera_; }
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ExtractRenderSettings () const noexcept -> RenderSettings
{
  return settings_;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::Material (const std::string &key) const noexcept
  -> std::shared_ptr <niepce::Material>
{
  try { return materials_.at (key); }
  catch (const std::exception& e) { return nullptr; }
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseRecursive
(
 tinyxml2::XMLElement* element,
 Attributes*           attributes
 )
  const -> void
{
  for (auto elem = element->FirstChildElement ();
       elem != nullptr;
       elem = elem->NextSiblingElement ())
  {
    if (IsElementType (elem, "lookat") ||
        IsElementType (elem, "film"))
    {
      ParseRecursive (elem, attributes);
      continue;
    }
    if (IsElementType (elem, "transform"))
    {
      const auto t = ParseTransform (elem);
      attributes->AddTransform (t.first, t.second);
    }
    if (elem->NoChildren ())
    {
      ParseElement (elem, attributes);
      continue;
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseMaterial (tinyxml2::XMLElement* material)
  const -> MaterialAttributes
{
  MaterialAttributes res;

  // Get material type.
  res.SetMaterialType (MaterialType (material));

  // Parse each element.
  for (auto element = material->FirstChildElement ();
       element != nullptr;
       element = element->NextSiblingElement ())
  {
    if (!element->NoChildren ())
    {
      std::cerr << "Ignored element " << element->Name ()
                << " since this element has child element."
                << std::endl;
      continue;
    }

    // Create value texture.
    if (IsElementType (element, "rgb"))
    {
      auto attrib = ParseSpectrum (element);
      auto type   = MaterialAttributes::DetectType (attrib.first);
      auto tex    = CreateValueTexture <Spectrum> (attrib.second);
      res.AddSpectrumTexture (type, tex);
      continue;
    }
    if (IsElementType (element, "float"))
    {
      // Create float texture.
      auto value = ParseFloat (element);
      auto type   = MaterialAttributes::DetectType (value.first);
      auto tex   = CreateValueTexture <Float> (value.second);
      res.AddFloatTexture (type, tex);
      continue;
    }
    // Reference to texture.
    if (IsElementType (element, "reference"))
    {
      auto attrib = ParseString (element);
      const auto name = element->Attribute ("name");
      try
      {
        auto type = MaterialAttributes::DetectType (attrib.first);
        if (IsFloatTexture (type))
        {
          auto tex = float_textures_.at (attrib.second);
          res.AddFloatTexture (type, tex);
          continue;
        }
        if (IsSpectrumTexture (type))
        {
          auto tex = spectrum_textures_.at (attrib.second);
          res.AddSpectrumTexture (type, tex);
          continue;
        }
        std::cerr << "Scene::Importer Unknow texture type was found." << std::endl;
      }
      catch (const std::exception& e)
      {
        std::cerr << "Reference texture could not found." << std::endl;
      }
      continue;
    }
    std::cerr << "Ignored element : " << element->Name () << std::endl;
  }
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseShape (tinyxml2::XMLElement* elements) const -> Attributes
{
  Attributes attrs;
  for (auto e = elements->FirstChildElement ();
       e != nullptr;
       e = e->NextSiblingElement ())
  {
    if (e->NoChildren ())
    {
      std::cerr << "Ignored element in shape";
      continue;
    }
    ParseElement (e, &attrs);
  }
  return attrs;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseElement
(
 tinyxml2::XMLElement* element,
 Attributes*           attributes
)
  const noexcept -> void
{
  if (IsElementType (element, "bool"))
  {
    auto attrib = ParseBool (element);
    attributes->AddBool (attrib.first, attrib.second);
    return ;
  }
  if (IsElementType (element, "int"))
  {
    auto attrib = ParseInt (element);
    attributes->AddInt (attrib.first, attrib.second);
    return ;
  }
  if (IsElementType (element, "float"))
  {
    auto attrib = ParseFloat (element);
    attributes->AddFloat (attrib.first, attrib.second);
    return ;
  }
  if (IsElementType (element, "string"))
  {
    auto attrib = ParseString (element);
    attributes->AddString (attrib.first, attrib.second);
    return ;
  }
  if (IsElementType (element, "vector3"))
  {
    auto attrib = ParseVector3f (element);
    attributes->AddVector3f (attrib.first, attrib.second);
    return ;
  }
  if (IsElementType (element, "rgb"))
  {
    auto attrib = ParseVector3f (element);
    attributes->AddSpectrum (attrib.first, attrib.second);
    return ;
  }
  if (IsElementType (element, "point3"))
  {
    auto attrib = ParsePoint3f (element);
    attributes->AddPoint3f (attrib.first, attrib.second);
    return ;
  }
  if (IsElementType (element, "reference"))
  {
    auto attrib = ParseString (element);
    attributes->AddString (attrib.first, attrib.second);
    return ;
  }
  std::cout << "Ignored element : " << element->Name () << std::endl;
  return ;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseBool (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, bool>
{
  const std::string name = element->Attribute ("name");
  const bool value = element->BoolAttribute ("value");
  return std::make_pair (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseInt (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, int>
{
  const std::string name = element->Attribute ("name");
  const int value = element->IntAttribute ("value");
  return std::make_pair (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseFloat (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, Float>
{
  const std::string name = element->Attribute ("name");
  Float value = element->DoubleAttribute ("value");
  const auto unit = element->Attribute ("unit");
  if (unit != nullptr && std::strcmp (unit, "mm") == 0)
  {
    value *= 0.001;
  }
  return std::make_pair (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseString (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, std::string>
{
  const std::string name  = element->Attribute ("name");
  const std::string type  = element->Parent ()->ToElement ()->Name ();

  std::string value = element->Attribute ("value");
  // HACKME:
  if (name == "filename" || name == "background" || name == "aperture")
  {
    value = filepath_ + value;
  }

  return std::make_pair (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseVector3f (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, Vector3f>
{
  const std::string name = element->Attribute ("name");
  std::stringstream ss (element->Attribute ("value"));
  std::vector <Float> v (std::istream_iterator <Float> {ss},
                         std::istream_iterator <Float> ());
  return std::make_pair (name, Vector3f (v[0], v[1], v[2]));
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParsePoint3f (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, Point3f>
{
  const std::string name = element->Attribute ("name");
  std::stringstream ss (element->Attribute ("value"));
  std::vector <Float> v (std::istream_iterator <Float> {ss},
                         std::istream_iterator <Float> ());
  return std::make_pair (name, Point3f (v[0], v[1], v[2]));
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseSpectrum (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, Spectrum>
{
  const std::string name = element->Attribute ("name");
  std::stringstream ss (element->Attribute ("value"));
  std::vector <Float> v (std::istream_iterator <Float> {ss},
                         std::istream_iterator <Float> ());
  return std::make_pair (name, Spectrum (v[0], v[1], v[2]));
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseTransform (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, Transform>
{
  Vector3f translate, rotate, scale;
  for (auto e = element->FirstChildElement (); e != nullptr;
       e = e->NextSiblingElement())
  {
    if (std::strcmp (e->Attribute ("name"), "translate") == 0)
    {
      const auto t = ParseVector3f (e);
      translate = t.second;
      continue;
    }
    if (std::strcmp (e->Attribute ("name"), "rotate") == 0)
    {
      const auto r = ParseVector3f (e);
      rotate = r.second;
      continue;
    }
    if (std::strcmp (e->Attribute ("name"), "scale") == 0)
    {
      const auto s = ParseVector3f (e);
      scale = s.second;
      continue;
    }
  }
  const auto t = Translate (translate);
  const auto s = Scale (scale.X (), scale.Y (), scale. Z());
  const auto r = RotateX (rotate.X ()) * RotateY (rotate.Y ())
               * RotateZ (rotate.Z ());
  return std::make_pair ("transform", t * s * r);
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::IsElementType
(
 tinyxml2::XMLElement* element,
 const char* type
)
  const noexcept -> bool
{
  if (std::strcmp (element->Name (), type) == 0) { return true; }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::LoadObj (const Attributes& attributes) -> void
{
  const std::string filename = attributes.FindString ("filename");

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  // Load .obj
  std::string err;
  bool ret = tinyobj::LoadObj (&attrib,
                               &shapes,
                               &materials,
                               &err,
                               filename.c_str());
  // Error check.
  if (!err.empty() || !ret) { std::cerr << err << std::endl; return ; }

  // Construct mesh.
  const std::shared_ptr <TriangleMesh> mesh (CreateMesh (attrib.vertices,
                                                         attrib.normals,
                                                         attrib.texcoords));

  std::vector <std::array <int, 3>> p_idxs;
  std::vector <std::array <int, 3>> n_idxs;
  std::vector <std::array <int, 3>> t_idxs;

  // Loop over shapes.
  for (const auto& s : shapes)
  {
    size_t index_offset = 0;
    for (size_t f = 0; f < s.mesh.num_face_vertices.size(); f++)
    {
      int fv = s.mesh.num_face_vertices[f];
      if (fv != 3) {/* Triangle is only supported.*/ return ; }

      // Get triangle position indices.
      std::array <int, 3> p = {s.mesh.indices[index_offset + 0].vertex_index,
                               s.mesh.indices[index_offset + 1].vertex_index,
                               s.mesh.indices[index_offset + 2].vertex_index};
      // Get triangle normal indices.
      std::array <int, 3> n = {s.mesh.indices[index_offset + 0].normal_index,
                               s.mesh.indices[index_offset + 1].normal_index,
                               s.mesh.indices[index_offset + 2].normal_index};
      // Get texture coordinate indices.
      std::array <int, 3> t = {s.mesh.indices[index_offset + 0].texcoord_index,
                               s.mesh.indices[index_offset + 1].texcoord_index,
                               s.mesh.indices[index_offset + 2].texcoord_index};
      // Push indices.
      p_idxs.push_back (p);
      n_idxs.push_back (n);
      t_idxs.push_back (t);
      index_offset += fv;
    }
  }

  // Get shape ID.
  auto sid = attributes.FindString ("id");

  // Construct triangle face.
  const int  size = p_idxs.size ();
  const auto mat_id   = attributes.FindString ("material");
  const auto light_id = attributes.FindString ("light");
  const auto mat   = Material (mat_id);

  for (int i = 0; i < size; ++i)
  {
    // Create triangle.
    std::shared_ptr <Shape> shape (CreateTriangle (mesh,
                                                   p_idxs[i],
                                                   n_idxs[i],
                                                   t_idxs[i]));
    shapes_.emplace (sid, shape);

    // Construct area light if present.
    std::shared_ptr <AreaLight> light = nullptr;
    if (!light_id.empty ())
    {
      light = CreateAreaLight (light_attrs_.at (light_id), shape);
      lights_.push_back (light);
    }

    primitives_.push_back (CreatePrimitive (shape, mat, light));
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::TextureType (const std::string &type)
  const noexcept -> niepce::TextureType
{
  if (type == "image_spectrum") { return niepce::TextureType::kImageSpectrum; }
  if (type == "image_float")    { return niepce::TextureType::kImageFloat;    }
  if (type == "value_spectrum") { return niepce::TextureType::kValueSpectrum; }
  if (type == "value_float")    { return niepce::TextureType::kValueFloat;    }
  return niepce::TextureType::kUnknown;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::MaterialType (tinyxml2::XMLElement* element)
  const noexcept -> niepce::MaterialType
{
  const std::string type = element->Attribute ("type");
  if (type == "matte")   { return niepce::MaterialType::kMatte;   }
  if (type == "metal")   { return niepce::MaterialType::kMetal;   }
  if (type == "plastic") { return niepce::MaterialType::kPlastic; }
  if (type == "mirror")  { return niepce::MaterialType::kMirror;  }
  return niepce::MaterialType::kUnknown;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::LightType (const std::string& type) const noexcept
  -> niepce::LightType
{
  if (type == "infinite") { return niepce::LightType::kInfiniteLight; }
  if (type == "area")     { return niepce::LightType::kAreaLight; }
  return niepce::LightType::kUnknow;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ShapeType (const std::string &str)
  const noexcept -> niepce::ShapeType
{
  if (str == "obj")    { return niepce::ShapeType::kTriangleMesh; }
  if (str == "sphere") { return niepce::ShapeType::kSphere;       }
  return niepce::ShapeType::kUnknown;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::DetectElementType (tinyxml2::XMLElement* elem)
  const noexcept -> ElementType
{
  const auto name = elem->Name ();
  if (std::strcmp (name, "int"))      { return ElementType::kInt; }
  if (std::strcmp (name, "float"))    { return ElementType::kFloat; }
  if (std::strcmp (name, "string"))   { return ElementType::kString; }
  if (std::strcmp (name, "point3"))   { return ElementType::kPoint3; }
  if (std::strcmp (name, "vector3"))  { return ElementType::kVector3; }
  if (std::strcmp (name, "rgb"))      { return ElementType::kRgb; }
  if (std::strcmp (name, "spectrum")) { return ElementType::kSpectrum; }
  if (std::strcmp (name, "camera"))   { return ElementType::kCamera; }
  if (std::strcmp (name, "lookat"))   { return ElementType::kLookAt; }
  if (std::strcmp (name, "film"))     { return ElementType::kFilm; }
  if (std::strcmp (name, "texture"))  { return ElementType::kTexture; }
  if (std::strcmp (name, "material")) { return ElementType::kMaterial; }
  if (std::strcmp (name, "light"))    { return ElementType::kLight; }
  if (std::strcmp (name, "shape"))    { return ElementType::kShape; }
  return ElementType::kUnknown;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
