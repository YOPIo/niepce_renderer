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
auto MaterialAttributes::AddFloatTexture
(
 MaterialAttributes::Type type,
 const std::shared_ptr<Texture <Float>>& texture
)
  noexcept -> void
{
  auto res = float_textures_.emplace (type, texture);
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::AddSpectrumTexture
(
 MaterialAttributes::Type type,
 const std::shared_ptr<Texture<Spectrum> > &texture
)
  noexcept -> void
{
  auto res = spectrum_textures_.emplace (type, texture);
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
auto MaterialAttributes::SetMaterialType (const niepce::MaterialType& type)
  noexcept -> void
{
  type_ = type;
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::FindFloatTextureOrNullPtr (Type type)
  const noexcept -> std::shared_ptr <Texture <Float>>
{
  try { return float_textures_.at (type); }
  catch (const std::exception &e)
  {
    std::cout << "MaterialAttribute::FindTexture Could not find " << std::endl;
    return nullptr;
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::FindSpectrumTextureOrNullPtr (Type type)
  const noexcept -> std::shared_ptr <Texture <Spectrum>>
{
  try { return spectrum_textures_.at (type); }
  catch (const std::exception &e)
  {
    std::cout << "MaterialAttribute::FindTexture Could not find " << std::endl;
    return nullptr;
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::Clear () -> void
{
  type_ = niepce::MaterialType::kUnknown;
  float_textures_.clear ();
  spectrum_textures_.clear ();
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialAttributes::DetectType (const std::string &name) -> Type
{
  if (name == "emission")    { return Type::kEmission; }
  if (name == "reflectance") { return Type::kReflectance; }
  if (name == "absorption")  { return Type::kAbsorption; }
  if (name == "roughness_u") { return Type::kRoughnessU; }
  if (name == "roughness_v") { return Type::kRoughnessV; }
  if (name == "roughness")   { return Type::kRoughness; }
  if (name == "ior")         { return Type::kIndexOfRefraction; }
  return Type::kUnknown;
}
/*
// ---------------------------------------------------------------------------
*/
auto IsFloatTexture (MaterialAttributes::Type type) -> bool
{
  if (type == MaterialAttributes::Type::kRoughness  ||
      type == MaterialAttributes::Type::kRoughnessU ||
      type == MaterialAttributes::Type::kRoughnessV ||
      type == MaterialAttributes::Type::kIndexOfRefraction)
  {
    return true;
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
auto IsSpectrumTexture (MaterialAttributes::Type type) -> bool
{
  if (type != niepce::MaterialAttributes::Type::kUnknown &&
      !IsFloatTexture (type))
  {
    return true;
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
