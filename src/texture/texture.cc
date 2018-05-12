/*!
 * @file texture.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "texture.h"
#include "../core/pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Texture::Texture (const char* filename)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Texture::operator ()
(
 unsigned int x,
 unsigned int y
)
  const noexcept -> Pixel
{
  return (*image_) (x, y);
}
/*
// ---------------------------------------------------------------------------
*/
auto Texture::operator () (Float u, Float v) const noexcept -> Pixel
{
  // Convert float to int
  u = Clamp (u);
  v = Clamp (v);
  const unsigned int x
    = static_cast <unsigned int> ((u + 0.5) * image_->Width ());
  const unsigned int y
    = static_cast <unsigned int> ((v + 0.5) * image_->Height ());

  return (*this) (x, y);
}
/*
// ---------------------------------------------------------------------------
*/
auto Texture::At (unsigned int x, unsigned int y) const -> Pixel
{
  try { return image_->At (x, y); }
  catch (const std::exception& e) { throw e; }
}
/*
// ---------------------------------------------------------------------------
*/
auto Texture::At (Float u, Float v) const -> Pixel
{
  // Convert float to int
  u = Clamp (u);
  v = Clamp (v);
  const unsigned int x
    = static_cast <unsigned int> ((u + 0.5) * image_->Width ());
  const unsigned int y
    = static_cast <unsigned int> ((v + 0.5) * image_->Height ());

  return this->At (x, y);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
