/*
// ---------------------------------------------------------------------------
// mitsuba renderer xml
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
struct Rgb
{
  union
  {
    struct { Float r, g, b; };
    std::array <Float, 3> rgb;
  };
};
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
  auto LoadXml (const char* filename, Scene* scene, Camera* camera) -> void;


  /* XmlLoader private static methods */
public:
  auto ParseBsdf    (const tinyxml2::XMLNode* node) -> MaterialPtr;
  auto ParseSensor  (const tinyxml2::XMLNode* node) -> void;
  auto ParseShape   (const tinyxml2::XMLNode* node) -> void;
  auto ParseEmitter (const tinyxml2::XMLNode* node) -> LightPtr;

  auto ParseFloat (const tinyxml2::XMLNode* node) -> Float;
  auto ParseInt   (const tinyxml2::XMLNode* node) -> int;

  auto ParseRgb      (const tinyxml2::XMLNode* node) -> Vector3f;
  auto ParseSrgb     (const tinyxml2::XMLNode* node) -> void; // No implementation
  auto ParseSpectrum (const tinyxml2::XMLNode* node) -> void; // No implementation

  auto LoadObj (const char* filename, std::vector<ShapePtr>* triangles) -> void;

  auto ParseTexture (const tinyxml2::XMLNode* node) -> void; // No implementation

  auto ParseLambert   (const tinyxml2::XMLNode* node) -> void; // No implementation
  auto ParseOrenNayar (const tinyxml2::XMLNode* node) -> void; // No implementation
  auto ParseMirror    (const tinyxml2::XMLNode* node) -> void; // No implementation
  auto ParseGlass     (const tinyxml2::XMLNode* node) -> void; // No implementation


  /* XmlLoader private data */
public:
  std::string base_path;
  std::vector <IndividualPtr> primitives_;
  std::vector <ShapePtr> shapes_;
  std::map <std::string, MaterialPtr> materials_;
  std::map <std::string, TexturePtr <Spectrum>> textures_;
  std::map <std::string, LightPtr> lights_;

}; // class XmlLoader
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SCENE_LOADER_H_
