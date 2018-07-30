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
auto Camera::UpdateFilmTile (const FilmTile &tile, int round) -> void
{
  if (round == 0)
  {
    film_.ReplaceFilmTile (tile);
    return;
  }
  film_.UpdateFilmTile (tile);
}
/*
// ---------------------------------------------------------------------------
*/
auto Camera::Save () const noexcept -> void
{
  Film f = film_;
  ToneMapping (&f);
  f.Save ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Camera::SaveSequence (int round, int spp) const noexcept -> void
{
  static int num = 0;
  Film f (film_);
  for (int y = 0; y < f.Height (); ++y)
  {
    for (int x = 0; x < f.Width (); ++x)
    {
      f.SetValueAt (x, y, f.At (x, y) / spp);
    }
  }
  ToneMapping (&f);
  f.SaveAs (("sequences/" + std::to_string (num++) + ".ppm").c_str ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Camera::FinalProcess (int round, int spp) -> void
{
  for (int y = 0; y < film_.Height (); ++y)
  {
    for (int x = 0; x < film_.Width (); ++x)
    {
      film_.SetValueAt (x, y, film_.At (x, y) / spp);
    }
  }
  ToneMapping (&film_);

  film_.SaveAs (("sequences/" + std::to_string (round) + ".ppm").c_str ());
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
