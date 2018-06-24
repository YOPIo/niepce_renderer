/*!
 * @file texture_attributes.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _MATERIAL_ATTRIBUTES_H_
#define _MATERIAL_ATTRIBUTES_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../material/material.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
enum class TextureType : int
{
  kEmission,
  kReflectance,
  kUnknown
};
//! ----------------------------------------------------------------------------
//! @class MaterialAttributes
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class MaterialAttributes
{
public:
  //! The default class constructor.
  MaterialAttributes () = default;

  //! The copy constructor of the class.
  MaterialAttributes (const MaterialAttributes& attributes) = default;

  //! The move constructor of the class.
  MaterialAttributes (MaterialAttributes&& attributes) = default;

  //! The default class destructor.
  virtual ~MaterialAttributes () = default;

  //! The copy assignment operator of the class.
  auto operator = (const MaterialAttributes& attributes)
    -> MaterialAttributes& = default;

  //! The move assignment operator of the class.
  auto operator = (MaterialAttributes&& attributes)
    -> MaterialAttributes& = default;

public:
  /*!
   * @Fn Return AddEmissionTexture ()
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto AddTexture
  (
   TextureType attribute,
   const std::shared_ptr <Texture>& texture
  )
    -> void;

  /*!
   * @fn std FindTexture (const)
   * @brief 
   * @param[in] name
   *    
   * @return 
   * @exception none
   * @details
   */
  auto FindTexture (TextureType attribute)
    const noexcept -> std::shared_ptr <Texture>;

  /*!
   * @fn void SetMaterialType (std)
   * @brief 
   * @param[in] type
   *    
   * @return 
   * @exception none
   * @details
   */
  auto SetMaterialType (const MaterialType& type) noexcept -> void;

  /*!
   * @fn MaterialType MaterialType ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto MaterialType () const noexcept -> MaterialType;

  /*!
   * @fn void Clear ()
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto Clear () -> void;

  // private:
public:
  niepce::MaterialType type_;
  std::map <TextureType, std::shared_ptr <Texture>> textures_;
}; // class MaterialAttributes
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TEXTURE_ATTRIBUTES_H_

