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
#include "../ext/tinyxml2/tinyxml2.h"
#include "../core/attributes.h"
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
  auto ParseRecursive (tinyxml2::XMLElement* element) -> void;

  /*!
   * @fn std::pair <std::string, T> ParseElement (tinyxml2::XMLElement*)
   * @brief 
   * @param[in] element
   *    
   * @return 
   * @exception none
   * @details
   */
  auto ParseElement (tinyxml2::XMLElement* element)
    noexcept -> void;

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

private:
  tinyxml2::XMLDocument xml_;
  tinyxml2::XMLElement* root_;

public:
  Attributes attributes_;
}; // class SceneImporter
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SCENE_IMPORTER_H_
