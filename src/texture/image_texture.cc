/*!
 * @file texture.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "image_texture.h"
#include "../core/image.h"
#include "../core/imageio.h"
#include "../core/point2f.h"
#include "../core/vector3f.h"
#include "../core/pixel.h"
#include "../core/intersection.h"
#include "../core/attributes.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
ImageTexture<T>::ImageTexture (const char* filename) :
  image_ (new ImageIO <T> (filename))
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageTexture<T>::Evaluate (const Intersection &isect) const noexcept -> T
{
  if (image_)
  {
    const auto &uv = isect.Texcoord ();
    const auto x = static_cast <Float> (image_->Width ()  - 1) * uv[0];
    const auto y = static_cast <Float> (image_->Height () - 1) * uv[1];
    return image_->At (x, y);
  }
  return T (0);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageTexture<T>::IsBlack () const noexcept -> bool
{
  const auto& width  = image_->Width ();
  const auto& height = image_->Height ();
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      if (image_->At (x, y) != T (0)) { return false; }
    }
  }
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto CreateImageTexture (const Attributes &attrs)
  -> std::shared_ptr <Texture <T>>
{
  // Get filename.
  const auto filename = attrs.FindString ("filename");
  return std::make_shared <ImageTexture <T>> (filename.c_str ());
}
/*
// ---------------------------------------------------------------------------
*/
template class ImageTexture <Float>;
template class ImageTexture <Spectrum>;

template auto CreateImageTexture <Float> (const Attributes&)
  -> std::shared_ptr <Texture <Float>>;
template auto CreateImageTexture <Spectrum> (const Attributes&)
  -> std::shared_ptr <Texture <Spectrum>>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
