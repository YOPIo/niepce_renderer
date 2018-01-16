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
class XmlLoader
{
 private:
  struct MaterialAttributes
  {
    // TODO: Delete Rgb class
    struct Rgb
    {
      union
      {
        struct {float r, g, b;};
        float rgb[3];
      };
    };

    Rgb   reflectance;
    Rgb   transmittance;
    Float ior; // Index of refraction
    Float roughness_u;
    Float roughness_v;
  };

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
  auto ParseBsdf   (const tinyxml2::XMLNode* node) -> void;
  auto ParseSensor (const tinyxml2::XMLNode* node) -> void;
  auto ParseShape  (const tinyxml2::XMLNode* node) -> void;

  auto ParseRgb      (const tinyxml2::XMLNode* node) -> void;
  auto ParseSpectrum (const tinyxml2::XMLNode* node) -> void;
  auto ParseSrgb     (const tinyxml2::XMLNode* node) -> void;

  auto LoadObj     (const char* filename)          -> void;

  auto ParseLambert   (const tinyxml2::XMLNode* node) -> void;
  auto ParseOrenNayar (const tinyxml2::XMLNode* node) -> void;
  auto ParseMirror    (const tinyxml2::XMLNode* node) -> void;
  auto ParseGlass     (const tinyxml2::XMLNode* node) -> void;


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
