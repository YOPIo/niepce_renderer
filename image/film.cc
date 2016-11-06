#include "film.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../3rdparty/stb_image_write.h"

namespace niepce
{

Film::Film()
{}

Film::Film(const Size& size) :
    size_(size)
{
  if (pixels_)
  {
    pixels_.reset();
  }
  pixels_ = std::make_unique<glm::vec3[]>(size.Width() * size.Height());
}

Film::Film(unsigned width, unsigned height) :
    size_( Size(width, height) )
{
  if (pixels_)
  {
    pixels_.reset();
  }
  pixels_ = std::make_unique<Rgb[]>(width * height);
}

Film::~Film()
{}

Rgb& Film::operator [] (std::size_t idx)
{
  ASSERT(0 <= idx && idx < size_.Width() * size_.Height() && "Out of Range.");
  return pixels_[idx];
}

auto Film::Width() const -> unsigned
{
  return size_.Width();
}

auto Film::Height() const -> unsigned
{
  return size_.Height();
}

// save rendered image as .hdr
auto Film::SaveAs(const char* filename) const -> void
{
  const int width  = size_.Width();
  const int height = size_.Height();
  float* buff = new float[width * height * 3];
  for (int i = 0; i < width * height; ++i)
  {
    buff[3 * i + 0] = pixels_[i].r;
    buff[3 * i + 1] = pixels_[i].g;
    buff[3 * i + 2] = pixels_[i].b;
  }

  for (int i = 0; i < width * height * 3; ++i)
  {
    if (buff[i] > 1.0)
    {
      DEBUG("Over 1, Clamped");
      buff[i] = 1.0;
    }
    if (buff[i] < 0.0)
    {
      DEBUG("Under 0, Clamped");
      buff[i] = 0.0;
    }
  }
  stbi_write_hdr(filename, width, height, 3, buff);

  std::ofstream ofs("cornellbox.ppm");
  ofs << "P3\n" << width << " " << height << "\n255\n";
  for (int i = 0; i < width * height; ++i)
  {
    ofs << static_cast<int>(pixels_[i].r * 255) << " "
        << static_cast<int>(pixels_[i].g * 255) << " "
        << static_cast<int>(pixels_[i].b * 255) << " ";
  }
  ofs.close();

  delete[] buff;
}

} // namespace nipce
