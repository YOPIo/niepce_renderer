/*!
 * @file bool_texture.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bool_texture.h"
#include "../core/point2f.h"
#include "../core/vector3f.h"
#include "../core/imageio.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
BoolTexture::BoolTexture (const char* filename) :
  image_ (nullptr)
{
  image_->Load (filename);
}
/*
// ---------------------------------------------------------------------------
*/
auto BoolTexture::Sample (const Point2f &uv) const noexcept -> Spectrum
{
  if (image_)
  {
    const int width  = static_cast <int> (image_->Width ());
    const int height = static_cast <int> (image_->Height ());

    
  }
  return Vector3f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
