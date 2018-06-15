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
   * @fn std::shared_ptr<Camera> ParseCamera ()
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details 
   */
  auto ParseCamera (tinyxml2::XMLElement* elem) -> std::shared_ptr <Camera>;

  /*!
   * @fn std ParseFilm (tinyxml2)
   * @brief 
   * @param[in] tinyxml2::XMLElement*
   *    
   * @return 
   * @exception none
   * @details 
   */
  auto ParseFilm (tinyxml2::XMLElement* elem) -> std::shared_ptr <Film>;

  /*!
   * @fn int ParseInt (tinyxml2)
   * @brief 
   * @param[in] tinyxml2::Xmlelement*
   *    
   * @return 
   * @exception none
   * @details 
   */
  auto ParseInt (tinyxml2::XMLElement* elem)
    const noexcept -> std::pair <std::string, int>;

  /*!
   * @fn std ParseFloat (tinyxml2)
   * @brief 
   * @param[in] tinyxml2::Xmlelement*
   *    
   * @return 
   * @exception none
   * @details 
   */
  auto ParseFloat (tinyxml2::XMLElement* elem)
    const noexcept -> std::pair <std::string, Float>;

  /*!
   * @fn std ParseString (tinyxml2)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details 
   */
  auto ParseString (tinyxml2::XMLElement* elem)
    const noexcept -> std::pair <std::string, std::string>;

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

public:
  tinyxml2::XMLDocument xml_;
  tinyxml2::XMLElement* root_;
}; // class SceneImporter
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SCENE_IMPORTER_H_
