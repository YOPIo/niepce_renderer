/*!
 * @file texture_attributes.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _TEXTURE_ATTRIBUTES_H_
#define _TEXTURE_ATTRIBUTES_H_
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
//! @class TextureAttributes
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class TextureAttributes
{
public:
  //! The default class constructor.
  TextureAttributes () = default;

  //! The copy constructor of the class.
  TextureAttributes (const TextureAttributes& attributes) = default;

  //! The move constructor of the class.
  TextureAttributes (TextureAttributes&& attributes) = default;

  //! The default class destructor.
  virtual ~TextureAttributes () = default;

  //! The copy assignment operator of the class.
  auto operator = (const TextureAttributes& attributes) -> TextureAttributes& = default;

  //! The move assignment operator of the class.
  auto operator = (TextureAttributes&& attributes) -> TextureAttributes& = default;

public:
  /*!
   * @fn Return AddEmissionTexture ()
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto AddTexture
  (
   TextureType                attribute,
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

private:
  niepce::MaterialType type_;
  std::map <TextureType, std::shared_ptr <Texture>> textures_;
}; // class TextureAttributes
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TEXTURE_ATTRIBUTES_H_

