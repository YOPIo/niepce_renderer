/*
// ---------------------------------------------------------------------------
// mitsuba renderer の xml に対応させる
// ---------------------------------------------------------------------------
*/
#ifndef _SCENE_LOADER_H_
#define _SCENE_LOADER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../ext/tinyxml2/tinyxml2.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class XmlLoader
{
  /* XmlLoader constructors */
public:
  XmlLoader () = default;


  /* XmlLoader destructor */
public:
  virtual ~XmlLoader () = default;


  /* XmlLoader public operators*/
public:
  XmlLoader (const XmlLoader&  loader) = default;
  XmlLoader (      XmlLoader&& loader) = default;

  auto operator = (const XmlLoader&  loader) -> XmlLoader& = default;
  auto operator = (      XmlLoader&& loader) -> XmlLoader& = default;


  /* XmlLoader public static methods */
public:
  auto LoadXml (const char* filename, Scene* scene) -> void;


  /* XmlLoader private static methods */
public:
  auto ParseShape  (const tinyxml2::XMLNode* node) -> void;
  auto ParseSensor (const tinyxml2::XMLNode* node) -> void;
  auto LoadObj     (const char* filename)          -> void;


  /* XmlLoader private data */
private:
  std::string base_path;

  std::vector <ShapePtr> shapes_;

}; // class XmlLoader
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SCENE_LOADER_H_
