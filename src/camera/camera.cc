/*!
 * @file camera.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "camera.h"
#include "pinhole.h"
#include "realistic_camera.h"
#include "../core/attributes.h"
#include "../core/bounds2f.h"
#include "../core/point2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Camera::Camera
(
 const Transform& t,
 const char*  output,
 const char*  background,
 unsigned int width,
 unsigned int height,
 Float diagonal
) :
  film_ (output, width, height, diagonal),
  background_ (background),
  camera_to_world_ (t)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Camera::Background (int x, int y) const -> Spectrum
{
  int sx = x * (background_.Width  () / (Float)film_.Width  ());
  int sy = y * (background_.Height () / (Float)film_.Height ());
  return background_.At (sx, sy);
}
/*
// ---------------------------------------------------------------------------
*/
auto Camera::FilmResolution () const noexcept -> Bounds2f
{
  return film_.Resolution ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Camera::UpdateFilmTile (const FilmTile &tile) -> void
{
  film_.AddFilmTile (tile);
}
/*
// ---------------------------------------------------------------------------
*/
auto Camera::Save () noexcept -> void
{
  film_.ApplyToneMapping (0.18);
  film_.ApplyDenoising ();
  film_.Save ();
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateCamera (const Attributes& attributes) -> std::shared_ptr <Camera>
{
  const std::string type = attributes.FindString ("type");
  if (type == "pinhole")
  {
    return CreatePinholeCamera (attributes);
  }
  if (type == "realistic")
  {
    // Create realistic camera
  }
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
