/*!
 * @file float_texture.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "float_texture.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
FloatTexture::FloatTexture (Float value) :
  value_(value)
{}
/*
// ---------------------------------------------------------------------------
*/
auto FloatTexture::IsBlack () const noexcept -> bool
{
  return value_ == 0;
}
/*
// ---------------------------------------------------------------------------
*/
auto FloatTexture::Sample (const Point2f &uv) const noexcept -> Spectrum
{
  return Spectrum (value_);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateFloatTexture (Float value) -> std::shared_ptr <Texture>
{
  return std::make_shared <FloatTexture> (value);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

