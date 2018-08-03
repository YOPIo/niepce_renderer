/*!
 * @file imageio.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "imageio.h"
#include "bounds2f.h"
#include "point2f.h"
#include "vector3f.h"
/*
// ---------------------------------------------------------------------------
// External library
// ---------------------------------------------------------------------------
*/
#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ext/stb/stb_image_write.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
ImageIO<T>::ImageIO (unsigned int width, unsigned int height) :
  Image<T> (width, height),
  name_ ()
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
ImageIO<T>::ImageIO
(
 const char* filename,
 unsigned int width,
 unsigned int height
) :
  Image<T> (width, height),
  name_ (filename)
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
ImageIO<T>::ImageIO (const char* filename) :
  Image<T> (0, 0),
  name_ (filename)
{
  Load (filename);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
ImageIO<T>::~ImageIO ()
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::Load (const char *filename) -> void
{
  std::cout << "No supported type image" << std::endl;
  std::exit (1);
}
/*6
// ---------------------------------------------------------------------------
*/
template <>
auto ImageIO <Spectrum>::Load (const char *filename) -> void
{
  // File check.
  if (!IsFileExist (filename))
  {
    std::cout << "ImageIO: ";
    std::cout << "Could not found : " << filename << std::endl;
    return ;
  }

  if (FileExtension (filename) == ".hdr")
  {
    // Load .hdr file.
  }

  // Load a image via stbi.
  int width, height, n;
  unsigned char *img = stbi_load (filename, &width, &height, &n, 4);

  // Reallocate the memory and copy image.
  AllocateMemory (width, height);

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      const auto idx = y * width + x;
      const auto r = Uint8ToFloat (img[idx * 4 + 0]); // R
      const auto g = Uint8ToFloat (img[idx * 4 + 1]); // G
      const auto b = Uint8ToFloat (img[idx * 4 + 2]); // B
      const auto a = Uint8ToFloat (img[idx * 4 + 3]); // A
      SetValueAt (x, y, Spectrum (r, g, b));
    }
  }

  stbi_image_free (img);
}
/*
// ---------------------------------------------------------------------------
*/
template <>
auto ImageIO<bool>::Load (const char* filename) -> void
{
  if (!IsFileExist (filename))
  {
    std::cout << "ImageIO: ";
    std::cout << "Could not found " << filename << std::endl;
    return ;
  }

  // Load a image via stbi.
  int width, height, n;
  unsigned char* img = stbi_load (filename, &width, &height, &n, 1);

  // Reallocate memory
  AllocateMemory (width, height);
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      SetValueAt (x, y, static_cast <bool> (img[y * width + x]));
    }
  }
  stbi_image_free (img);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::Save () const noexcept -> void
{
  SaveAs (name_.c_str ());
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::SaveAs (const char *filename) const noexcept -> void
{
  const auto ext = FileExtension (filename);
  if (ext == ".ppm")
  {
    SavePpm (filename);
    return ;
  }
  if (ext == ".png")
  {
    SavePng (filename);
    return ;
  }
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::Rename (const std::string& new_name) noexcept -> void
{
  name_ = new_name;
}
/*
// ---------------------------------------------------------------------------
// Private methods definition
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::AllocateMemory (unsigned int width, unsigned int height) -> void
{
  this->data_.reset (new T [width * height], std::default_delete <T []> ());
  this->width_  = width;
  this->height_ = height;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::SavePng (const char* filename) const noexcept -> void
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::SavePpm (const char* filename) const noexcept -> void
{}
/*
// ---------------------------------------------------------------------------
*/
template <>
auto ImageIO <bool>::SavePpm (const char* filename) const noexcept -> void
{
  std::ofstream os (filename);
  if (!os)
  {
    std::cerr << "Failed to open " << filename << std::endl;
    return ;
  }
  os << "P1\n" << width_ << " " << height_ << "\n";
  for (int y = 0; y < height_; ++y)
  {
    for (int x = 0; x < width_; ++x)
    {
      os << static_cast <int> (At (x, y)) << std::endl;
    }
  }
  os.close ();
}
/*
// ---------------------------------------------------------------------------
*/
template <>
auto ImageIO<Float>::SavePpm (const char* filename) const noexcept -> void
{
  std::ofstream os (filename);
  os << "P2\n" << width_ << " " << height_ << "\n255\n";
  auto func = [&] (int x, int y) -> void
  {
    os << (int)FloatToInt (At (x, y)) << " ";
  };
  For2(func, Width (), Height ());
  os.close ();
}
/*
// ---------------------------------------------------------------------------
*/
template <>
auto ImageIO<Spectrum>::SavePpm (const char* filename) const noexcept -> void
{
  std::ofstream os (filename);
  if (!os)
  {
    std::cerr << "Could not open " << filename << std::endl;
  }
  os << "P3\n" << width_ << " " << height_ << "\n255\n";
  auto func = [&] (int x, int y) -> void
  {
    os << (int)FloatToInt (At (x, y).X ()) << " ";
    os << (int)FloatToInt (At (x, y).Y ()) << " ";
    os << (int)FloatToInt (At (x, y).Z ()) << " ";
  };
  For2(func, Width (), Height ());
  os.close ();
}
/*
// ---------------------------------------------------------------------------
*/
template <>
auto ImageIO <bool>::SavePng (const char* filename) const noexcept -> void
{
  unsigned char *img = new unsigned char [width_ * height_];
  for (int y = 0; y < height_; ++y)
  {
    for (int x = 0; x < width_; ++x)
    {
      img[y * width_ + x] = data_.get () [y * width_ + x] ? 255 : 0;
    }
  }
  stbi_write_png (filename, width_, height_, 1, img,
                  sizeof (unsigned char) * width_);
  delete [] img;
}
/*
// ---------------------------------------------------------------------------
*/
template <>
auto ImageIO <Spectrum>::SavePng (const char* filename) const noexcept -> void
{
  unsigned char *img = new unsigned char [width_ * height_ * 4];
  for (int y = 0; y < height_; ++y)
  {
    for (int x = 0; x < width_; ++x)
    {
      const auto idx = y * width_ + x;
      img[4 * idx + 0] = FloatToInt (At (x, y).X ());
      img[4 * idx + 1] = FloatToInt (At (x, y).Y ());
      img[4 * idx + 2] = FloatToInt (At (x, y).Z ());
      img[4 * idx + 3] = 255;
    }
  }
  stbi_write_png (filename, width_, height_, 4, img,
                  sizeof (unsigned char) * width_ * 4);
  delete [] img;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::SaveHdr (const char* filename) const noexcept -> void
{}
/*
// ---------------------------------------------------------------------------
*/
template class ImageIO <bool>;
template class ImageIO <Float>;
template class ImageIO <Spectrum>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
