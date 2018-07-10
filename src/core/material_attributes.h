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
//! ----------------------------------------------------------------------------
//! @class MaterialAttributes
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class MaterialAttributes
{
public:
  enum class Type : uint8_t
  {
   kAbsorption,
   kEmission,
   kReflectance,
   kSpecular,
   kRoughness,
   kRoughnessU,
   kRoughnessV,
   kIndexOfRefraction,
   kUnknown
  };

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
   * @fn  AddFloatTexture ()
   * @brief 
   * @param[in] type
   *
   * @param[in] texture
   *
   * @return 
   * @exception none
   * @details 
   */
  auto AddFloatTexture
  (
   MaterialAttributes::Type type,
   const std::shared_ptr <Texture <Float>>& texture
  )
    noexcept -> void;

  /*!
   * @fn void AddSpectrumTexture ()
   * @brief 
   * @param[in] type
   *    
   * @param[in] texture
   *    
   * @return 
   * @exception none
   * @details 
   */
  auto AddSpectrumTexture
  (
   MaterialAttributes::Type type,
   const std::shared_ptr <Texture <Spectrum>>& texture
  )
    noexcept -> void;

  /*!
   * @fn std::shared_ptr <Texture <Float>> FindFloatTextureOrNullPtr (TextureType)
   * @brief 
   * @param[in] type
   * @return 
   * @exception none
   * @details 
   */
  auto FindFloatTextureOrNullPtr (MaterialAttributes::Type type)
    const noexcept -> std::shared_ptr <Texture <Float>>;

  /*!
   * @fn  FindSpectrumTexture (TextureType)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details 
   */
  auto FindSpectrumTextureOrNullPtr (MaterialAttributes::Type type)
    const noexcept -> std::shared_ptr <Texture <Spectrum>>;

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

public:
  static auto DetectType (const std::string &name) -> Type;

private:
  niepce::MaterialType type_;
  std::map <Type, std::shared_ptr <Texture <Float>>> float_textures_;
  std::map <Type, std::shared_ptr <Texture <Spectrum>>> spectrum_textures_;
}; // class MaterialAttributes
/*
// ---------------------------------------------------------------------------
*/
auto IsFloatTexture (MaterialAttributes::Type type) -> bool;
auto IsSpectrumTexture (MaterialAttributes::Type type) -> bool;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TEXTURE_ATTRIBUTES_H_

