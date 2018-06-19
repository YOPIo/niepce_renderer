/*!
 * @file texture_attributes.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "texture_attributes.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto TextureAttributes::AddTexture
(
 TextureType                     attribute,
 const std::shared_ptr<Texture>& texture
)
  -> void
{
  auto res = textures_.emplace (attribute, texture);
  if (res.second) { std::cerr << "Could not add." << std::endl; }
}
/*
// ---------------------------------------------------------------------------
*/
auto TextureAttributes::MaterialType () const noexcept -> niepce::MaterialType
{
  return type_;
}
/*
// ---------------------------------------------------------------------------
*/
auto TextureAttributes::SetMaterialType(const niepce::MaterialType& type)
  noexcept -> void
{
  type_ = type;
}
/*
// ---------------------------------------------------------------------------
*/
auto TextureAttributes::FindTexture (TextureType attribute)
  const noexcept -> std::shared_ptr <Texture>
{
  try { textures_.at (attribute); }
  catch (const std::exception& e)
  {
    std::cerr << "Could not find " << (int)attribute << " texture" << std::endl;
  }
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto TextureAttributes::Clear () -> void
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
