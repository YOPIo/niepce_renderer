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
  xml_.LoadFile (filename);
  root_ = xml_.FirstChildElement ();

  // Loop for each element.
  for (auto element = root_->FirstChildElement ();
       element != nullptr;
       element = element->NextSiblingElement ())
  {
    if (IsElementType (element, "camera"))
    {
      ParseRecursive (element);
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseRecursive (tinyxml2::XMLElement* element) -> void
{
  for (auto elem = element->FirstChildElement ();
       elem != nullptr;
       elem = elem->NextSiblingElement ())
  {
    if (IsElementType (elem, "lookat") || IsElementType (elem, "film"))
    {
      ParseRecursive (elem);
      continue;
    }
    if (elem->NoChildren ())
    {
      ParseElement (elem);
      continue;
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseElement (tinyxml2::XMLElement* element)
  noexcept -> void
{
  if (IsElementType (element, "bool"))
  {
    auto attrib = ParseBool (element);
    attributes_.AddBool (attrib.first, attrib.second);
  }
  if (IsElementType (element, "int"))
  {
    auto attrib = ParseInt (element);
    attributes_.AddInt (attrib.first, attrib.second);
  }
  if (IsElementType (element, "float"))
  {
    auto attrib = ParseFloat (element);
    attributes_.AddFloat (attrib.first, attrib.second);
  }
  if (IsElementType (element, "string"))
  {
    auto attrib = ParseString (element);
    attributes_.AddString (attrib.first, attrib.second);
  }
  if (IsElementType (element, "vector3"))
  {
    auto attrib = ParseVector3f (element);
    attributes_.AddVector3f (attrib.first, attrib.second);
  }
  if (IsElementType (element, "point3"))
  {
    auto attrib = ParsePoint3f (element);
    attributes_.AddPoint3f (attrib.first, attrib.second);
  }
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
  if (std::strcmp (element->Attribute ("unit"), "mm") == 0)
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
  const std::string value = element->Attribute ("value");
  return std::make_pair (type + "/" + name, value);
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
auto SceneImporter::IsElementType (tinyxml2::XMLElement* element, const char* type)
  const noexcept -> bool
{
  if (std::strcmp (element->Name (), type) == 0) { return true; }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
