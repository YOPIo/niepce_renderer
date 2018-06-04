/*!
 * @file imageio.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "imageio.h"
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
ImageIO<T>::ImageIO (unsigned int w, unsigned int h) :
  Image<T> (w, h),
  name_ ("no_name.ppm")
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
auto ImageIO<T>::Load (const char *filename) -> void
{
  // Load a image via stbi.
  int width, height, n;
  unsigned char* data = stbi_load (filename, &width, &height, &n, 1);

  auto to_float = [] (unsigned char c) -> Float
  {
    Float x = int (c) / 255.0;
    return Clamp (x);
  };

  // Reallocate the memory and copy image.
  AllocateMemory (width, height);


}
/*
// ---------------------------------------------------------------------------
*/
template <>
auto ImageIO<Spectrum>::Load (const char *filename) -> void
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

      this->data_[idx] = Spectrum (r, g, b);
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::Save () const noexcept -> void
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::SaveAs (const char *filename) const noexcept -> void
{
  SavePpm (filename);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ImageIO<T>::Set (unsigned int x, unsigned int y, const T& val)
  noexcept -> void
{
  this->data_[y * this->width_ + x] = val;
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
  this->data_.reset (new T [width * height]);
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
auto ImageIO<Float>::SavePpm (const char* filename) const noexcept -> void
{
  auto to_int = [] (Float x) -> unsigned char
  {
    return static_cast <unsigned char> (x * 255 - 1.0 + 0.5);
  };

  std::ofstream os (filename);
  os << "P2\n" << this->width_ << " " << this->height_ << "\n255\n";

  for (int i = 0; i < this->width_ * this->height_; ++i)
  {
    os << (int)FloatToInt (this->data_[i]) << " ";
  }
  os.close ();
}
/*
// ---------------------------------------------------------------------------
*/
template <>
auto ImageIO<Spectrum>::SavePpm (const char* filename) const noexcept -> void
{
  std::ofstream os (filename);
  os << "P3\n" << this->width_ << " " << this->height_ << "\n255\n";
  for (int i = 0; i < this->width_ * this->height_; ++i)
  {
    os << (int)FloatToInt (this->data_[i].X ()) << " ";
    os << (int)FloatToInt (this->data_[i].Y ()) << " ";
    os << (int)FloatToInt (this->data_[i].Z ()) << " ";
  }
  os.close ();
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
