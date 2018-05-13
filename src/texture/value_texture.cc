/*!
 * @file texture.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "value_texture.h"
#include "../core/vector3f.h"
#include "../core/pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
ValueTexture::ValueTexture (const Vector3f& value) :
  value_ (value)
{}
/*
// ---------------------------------------------------------------------------
*/
auto ValueTexture::Sample (const Point2f& uv) const noexcept -> Vector3f
{
  return value_;
}
/*
// ---------------------------------------------------------------------------
// Function for the value texture.
// ---------------------------------------------------------------------------
*/
auto CreateValueTexture (const Vector3f& value) -> std::shared_ptr <Texture>
{
  std::shared_ptr <Texture> res (new ValueTexture (value));
  return std::move (res);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
