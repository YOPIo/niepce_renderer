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
 const std::string& name,
 const std::shared_ptr<Texture>& texture
)
  -> void
{
  textures_.emplace (name, texture);
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
auto TextureAttributes::FindTexture (const std::string& name)
  const noexcept -> std::shared_ptr <Texture>
{
  try { textures_.at (name); }
  catch (const std::exception& e)
  {
    std::cerr << "Could not find " << name << " texture" << std::endl;
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
