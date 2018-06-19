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
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
ImageTexture::ImageTexture (const char* filename) :
  image_ (new ImageIO <Spectrum> (filename))
{}
/*
// ---------------------------------------------------------------------------
*/
auto ImageTexture::Sample (const Point2f& uv) const noexcept -> Spectrum
{
  if (image_)
  {
    const int width  = static_cast <int> (image_->Width ());
    const int height = static_cast <int> (image_->Height ());

    // Convert to integer.
    int x = static_cast <unsigned int> (uv[0] * width);
    int y = static_cast <unsigned int> (uv[1] * height);
    x = Clamp (x, 0, width - 1);
    y = Clamp (y, 0, height - 1);

    const Spectrum s = image_->At (x, y);
    return Vector3f (s.X (), s.Y (), s.Z ());
  }
  return Vector3f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto ImageTexture::IsBlack () const noexcept -> bool
{
  const int& width  = image_->Width ();
  const int& height = image_->Height ();
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      if (image_->At (x, y) != Spectrum::Zero ()) { return false; }
    }
  }
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateImageTexture (const std::string& filename) -> Texture*
{
  return new ImageTexture (filename.c_str ());
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
