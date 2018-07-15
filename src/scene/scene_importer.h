/*!
 * @file scene_importer.h
 * @brief 
 * @author Masashi Yoshidat
 * @date 
 * @details 
 */
#ifndef _SCENE_IMPORTER_H_
#define _SCENE_IMPORTER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/render_settings.h"
#include "../ext/tinyxml2/tinyxml2.h"
#include "../core/attributes.h"
#include "../core/material_attributes.h"
#include "../material/material.h"
#include "../texture/texture.h"
#include "scene.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class SceneImporter
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class SceneImporter
{
public:
  enum class ElementType
  {
   kInt,
   kFloat,
   kString,
   kPoint3,
   kVector3,
   kRgb,
   kSpectrum,
   // Camera components
   kCamera,
   kLookAt,
   kFilm,
   kTexture,
   kMaterial,
   kLight,
   kShape,
   kUnknown
  };
public:
  //! The default class constructor.
  SceneImporter () = delete;

  //! The constructor takes filename.
  SceneImporter (const char* filename);

  //! The copy constructor of the class.
  SceneImporter (const SceneImporter& importer) = default;

  //! The move constructor of the class.
  SceneImporter (SceneImporter&& importer) = default;

  //! The default class destructor.
  virtual ~SceneImporter () = default;

  //! The copy assignment operator of the class.
  auto operator = (const SceneImporter& importer) -> SceneImporter& = default;

  //! The move assignment operator of the class.
  auto operator = (SceneImporter&& importer) -> SceneImporter& = default;

public:
  /*!
   * @fn void Import (const char*)
   * @brief 
   * @param[in] filename
   * @return 
   * @exception none
   * @details 
   */
  auto Import (const char* filename) -> void;

  /*!
   * @fn std::shared_ptr <Camera> ExtractCamera ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto ExtractCamera () const noexcept -> std::shared_ptr <Camera>;

  /*!
   * @fn void ExtractScene ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto ExtractScene () const noexcept -> std::shared_ptr <Scene>;

  auto Material (const std::string& key) const noexcept
    -> std::shared_ptr <Material>;

  auto Light (const std::string& key) const noexcept
    -> std::shared_ptr <AreaLight>;

private:
  /*!
   * @fn void ParseRecursive (tinyxml2)
   * @brief 
   * @param[in] element
   * 
   * @return 
   * @exception none
   * @details
   */
  auto ParseRecursive
  (
   tinyxml2::XMLElement* element,
   Attributes*           attributes
  )
    const -> void;

  /*!
   * @fn void ParseMaterial (tinyxml2::XMLElement* element)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details In material element, it supports rgb and reference element. Other
   *          element will be ignored.
   */
  auto ParseMaterial (tinyxml2::XMLElement* element) const -> MaterialAttributes;

  /*!
   * @fn Attributes ParseShape (tinyxml2)
   * @brief 
   * @param[in] element
   *
   * @return 
   * @exception none
   * @details 
   */
  auto ParseShape (tinyxml2::XMLElement* element) const -> Attributes;

  /*!
   * @fn std::pair <std::string, T> ParseElement (tinyxml2::XMLElement*)
   * @brief 
   * @param[in] element
   *    
   * @return 
   * @exception none
   * @details
   */
  auto ParseElement
  (
   tinyxml2::XMLElement* element,
   Attributes*           attributes
  )
    const noexcept -> void;

  auto ParseBool (tinyxml2::XMLElement* element)
    const noexcept -> std::pair <std::string, bool>;

  auto ParseInt (tinyxml2::XMLElement* element)
    const noexcept -> std::pair <std::string, int>;

  auto ParseFloat (tinyxml2::XMLElement* element)
    const noexcept -> std::pair <std::string, Float>;

  auto ParseString (tinyxml2::XMLElement* element)
    const noexcept -> std::pair <std::string, std::string>;

  auto ParseVector3f (tinyxml2::XMLElement* element)
    const noexcept -> std::pair <std::string, Vector3f>;

  auto ParsePoint3f (tinyxml2::XMLElement* element)
    const noexcept -> std::pair <std::string, Point3f>;

  auto ParseSpectrum (tinyxml2::XMLElement* element)
    const noexcept -> std::pair <std::string, Spectrum>;

  /*!
   * @fn bool IsElementType (tinyxml2)
   * @brief 
   * @param[in] tinyxml2::Xmlelement*
   *    
   * @return 
   * @exception none
   * @details 
   */
  auto IsElementType (tinyxml2::XMLElement* elem, const char* type)
    const noexcept -> bool;

  /*!
   * @fn MaterialType MaterialType
   * @brief 
   * @param[in] element
   * @return 
   * @exception none
   * @details
   */
  auto MaterialType (tinyxml2::XMLElement* element)
    const noexcept -> MaterialType;

  /*!
   * @fn void LoadObj (const char*)
   * @brief 
   * @param[in] filename
   *    
   * @return 
   * @exception none
   * @details
   */
  auto LoadObj (const Attributes& attributes) -> void;

  auto TextureType (const std::string& type) const noexcept -> niepce::TextureType;
  auto LightType (const std::string& type) const noexcept -> niepce::LightType;
  auto ShapeType (const std::string &type) const noexcept -> niepce::ShapeType;

  /*!
   * @fn ElementType DetectElementType (tinyxml2)
   * @brief 
   * @param[in] elem
   *    
   * @return 
   * @exception none
   * @details 
   */
  auto DetectElementType (tinyxml2::XMLElement* elem)
    const noexcept -> ElementType;

private:
  std::string filepath_;

  tinyxml2::XMLDocument xml_;
  tinyxml2::XMLElement* root_;

  RenderSettings settings_;

  // Key   : Texture ID
  // Value : std::shared_ptr <Textrue>
  std::unordered_map <std::string, std::shared_ptr <Texture <Float>>> float_textures_;
  std::unordered_map <std::string, std::shared_ptr <Texture <Spectrum>>> spectrum_textures_;

  // Key   : Material ID
  // Value : std::shared_ptr <Material>
  std::unordered_map <std::string, std::shared_ptr <niepce::Material>> materials_;

  // Key   : Light ID
  // Value : std::shared_ptr <AreaLight>
  std::unordered_map <std::string, Attributes> light_attrs_;
  std::vector <std::shared_ptr <niepce::Light>> lights_;
  std::shared_ptr <InfiniteLight> inf_lights_;

  // Key   : Shape ID
  // Value : std::shared_ptr <Shape>
  std::map <std::string, std::shared_ptr <Shape>>  shapes_;

  std::vector <std::shared_ptr <Primitive>> primitives_;

  std::shared_ptr <Camera> camera_;
  std::shared_ptr <Scene>  scene_;
}; // class SceneImporter
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SCENE_IMPORTER_H_
