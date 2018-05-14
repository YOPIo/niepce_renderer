/*!
 * @file ioimage.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "ioimage.h"
#include "pixel.h"
/*
// ---------------------------------------------------------------------------
// External library
// ---------------------------------------------------------------------------
*/
#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ext/stb_image_write.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
IOImage::IOImage (const char* filename) :
  Image (),
  name_ (filename)
{
  Load (filename);
}
/*
// ---------------------------------------------------------------------------
*/
auto IOImage::operator ()
(
 unsigned int x,
 unsigned int y
)
  const noexcept -> Pixel
{
  if (x < width_ && y < height_)
  {
    return pixels_[y * width_ + x];
  }
  return pixels_[0];
}
/*
// ---------------------------------------------------------------------------
*/
auto IOImage::At (unsigned int x, unsigned int y) const -> Pixel
{
  if (x < width_ && y < height_)
  {
    return pixels_[y * width_ + x];
  }
  throw std::out_of_range ("");
}
/*
// ---------------------------------------------------------------------------
*/
auto IOImage::Load (const char *filename) -> void
{
  // Load a image via stbi.
  int width, height, n;
  unsigned char* data = stbi_load (filename, &width, &height, &n, 4);

  auto to_float = [] (unsigned char c) -> Float
  {
    Float x = int (c) / 255.0;
    return Clamp (x);
  };

  // Reallocate the memory and copy image.
  AllocateMemory (width, height);
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      const unsigned int idx = y * width + x;
      const Float r = to_float (data[idx * 4 + 0]);
      const Float g = to_float (data[idx * 4 + 1]);
      const Float b = to_float (data[idx * 4 + 2]);
      pixels_[idx] = Pixel (r, g, b);
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto IOImage::Save (Format format) const noexcept -> void
{
  if (format == kHdr)
  {
    SaveHdr (name_.c_str ());
    return ;
  }
  if (format == kPpm)
  {
    SavePpm (name_.c_str ());
  }
  if (format == kPng)
  {
    SavePng (name_.c_str ());
    return ;
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto IOImage::SaveAs (const char *filename, Format format) const noexcept -> void
{
  if (format == kHdr)
  {
    SaveHdr (filename);
    return ;
  }
  if (format == kPpm)
  {
    SavePpm (filename);
  }
  if (format == kPng)
  {
    SavePng (filename);
    return ;
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto IOImage::Rename (const std::string& new_name) noexcept -> void
{
  name_ = new_name;
}
/*
// ---------------------------------------------------------------------------
// Private methods definition
// ---------------------------------------------------------------------------
*/
auto IOImage::AllocateMemory (unsigned int width, unsigned int height) -> void
{
  pixels_.reset (new Pixel[width * height]);
  this->width_  = width;
  this->height_ = height;
}
/*
// ---------------------------------------------------------------------------
*/
auto IOImage::SavePng (const char* filename) const noexcept -> void
{
  auto to_int = [] (Float x) -> unsigned char
  {
    return static_cast <unsigned char> (x * 255 - 1.0 + 0.5);
  };

  unsigned char* data = new unsigned char [width_ * height_];
  for (int y = 0; y < height_; ++y)
  {
    for (int x = 0; x < width_; ++x)
    {
      const unsigned int  idx   = y * width_ + x;
      const unsigned char red   = to_int (pixels_[idx].R ());
      const unsigned char green = to_int (pixels_[idx].G ());
      const unsigned char blue  = to_int (pixels_[idx].B ());
      data[idx + 0] = red;
      data[idx + 1] = green;
      data[idx + 2] = blue;
    }
  }
  stbi_write_png (filename, width_, height_, 3, data, sizeof (unsigned char) * 3);
}
/*
// ---------------------------------------------------------------------------
*/
auto IOImage::SavePpm (const char* filename) const noexcept -> void
{
  auto to_int = [] (Float x) -> unsigned char
  {
    return static_cast <unsigned char> (x * 255 - 1.0 + 0.5);
  };

  std::ofstream os (filename);
  os << "P3\n" << width_ << " " << height_ << " 255\n";
  for (int i = 0; i < width_ * height_; ++i)
  {
    const int red   = to_int (pixels_[i].R ());
    const int green = to_int (pixels_[i].G ());
    const int blue  = to_int (pixels_[i].B ());
    os << red << " " << green << " " << blue << " ";
  }
  os.close ();
}
/*
// ---------------------------------------------------------------------------
*/
auto IOImage::SaveHdr (const char* filename) const noexcept -> void
{
  float* data = new float [width_ * height_ * 3];
  for (int y = 0; y < height_; ++y)
  {
    for (int x = 0; x < width_; ++x)
    {
      const unsigned int idx = y * width_ + x;
      data[idx + 0] = pixels_[idx].R ();
      data[idx + 1] = pixels_[idx].G ();
      data[idx + 2] = pixels_[idx].B ();
    }
  }
  stbi_write_hdr (filename, width_, height_, 0, data);
  delete [] data;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
