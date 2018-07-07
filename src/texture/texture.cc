/*!
 * @file texture.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "../core/attributes.h"
#include "texture.h"
#include "image_texture.h"
#include "value_texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto CreateTexture
(
 TextureType type,
 const Attributes &attrs
)
  -> std::shared_ptr <Texture <T>>
{
  // If attributes class has filename, then load a image. Otherwise, create
  // value texture.
  const auto filename = attrs.FindString ("filename");
  if (!filename.empty ())
  {
    // Load a image.
    return CreateImageTexture <T> (attrs);
  }
  // Create value texture.
  return CreateValueTexture <T> (attrs);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
