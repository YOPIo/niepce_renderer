/*!
 * @file texture_attributes.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "material_attributes.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::AddTexture
(
 TextureType attribute,
 const std::shared_ptr<Texture>& texture
)
  -> void
{
  auto res = textures_.emplace (attribute, texture);
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::MaterialType () const noexcept -> niepce::MaterialType
{
  return type_;
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::SetMaterialType(const niepce::MaterialType& type)
  noexcept -> void
{
  type_ = type;
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::FindTexture (TextureType attribute)
  const noexcept -> std::shared_ptr <Texture>
{
  try { return textures_.at (attribute); }
  catch (const std::exception& e)
  {
    std::cerr << "Could not find " << (int)attribute << " texture" << std::endl;
  }
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::Clear () -> void
{
  textures_.clear ();
  type_ = niepce::MaterialType::kUnknown;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
