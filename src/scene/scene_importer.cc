/*!
 * @file scene_importer.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "scene_importer.h"
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

}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseCamera (tinyxml2::XMLElement* camera)
  -> std::shared_ptr <Camera>
{

}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseFilm (tinyxml2::XMLElement* film)
  -> std::shared_ptr <Film>
{

}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseInt (tinyxml2::XMLElement* node)
  const noexcept -> std::pair <std::string, int>
{

}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseFloat (tinyxml2::XMLElement* )
  const noexcept -> std::pair <std::string, Float>
{
}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::ParseString (tinyxml2::XMLElement* elem)
  const noexcept -> std::pair <std::string, std::string>
{

}
/*
// ---------------------------------------------------------------------------
*/
auto SceneImporter::IsElementType (tinyxml2::XMLElement* elem, const char* type)
  const noexcept -> bool
{

}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
