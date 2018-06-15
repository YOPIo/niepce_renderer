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
      ParseCamera (element);
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseCamera (tinyxml2::XMLElement* camera)
  -> std::shared_ptr <Camera>
{
  std::shared_ptr <Film> film;
  // Loop for each element.
  for (auto element = camera->FirstChildElement ();
       element != nullptr;
       element = element->NextSiblingElement ())
  {
    if (IsElementType (element, "lookat"))
    {
      ParseAttribute <Vector3f> (element->FirstChildElement ());
    }
    if (IsElementType (element, "film"))
    {
      film = ParseFilm (element);
      continue;
    }
  }
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseFilm (tinyxml2::XMLElement* film)
  -> std::shared_ptr <Film>
{
  unsigned int width, height;
  Float diagonal;
  std::string filename;
  for (auto element = film->FirstChildElement ();
       element != nullptr;
       element = element->NextSiblingElement ())
  {
    if (IsAttributeName (element, "width"))
    {
      width = element->IntAttribute ("value");
      continue;
    }
    if (IsAttributeName (element, "height"))
    {
      height = element->IntAttribute ("value");
      continue;
    }
    if (IsAttributeName (element, "diagonal"))
    {
      diagonal = element->DoubleAttribute ("value");
      continue;
    }
    if (IsAttributeName (element, "filename"))
    {
      filename = element->Attribute ("value");
    }
  }
  return std::make_shared <Film> (filename.c_str (), width, height, diagonal);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto SceneImporter::ParseAttribute (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, T>
{
  
}
/*
// ---------------------------------------------------------------------------
*/
template <>
auto SceneImporter::ParseAttribute <Vector3f> (tinyxml2::XMLElement* element)
  const noexcept -> std::pair <std::string, Vector3f>
{
  // Parse string by space, create vector3.
  std::stringstream ss (element->Attribute ("value"));
  std::vector <Float> v (std::istream_iterator <Float> {ss},
                         std::istream_iterator <Float> ());
  for (auto t : v){ std::cout << t << std::endl; }

  return std::make_pair ("", Vector3f ());
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::IsAttributeName
(
 tinyxml2::XMLElement* element,
 const char* type
)
  const noexcept -> bool
{
  if (std::strcmp (element->Attribute ("name"), type) == 0) { return true; }
  return false;
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
