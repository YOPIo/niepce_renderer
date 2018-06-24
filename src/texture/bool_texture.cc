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
  if (image_->At (uv.X (), uv.Y ())) { return Spectrum::One (); }
  return Vector3f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
