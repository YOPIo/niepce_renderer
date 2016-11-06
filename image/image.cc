#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../3rdparty/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../3rdparty/stb_image_write.h"

namespace niepce
{

Image::Image()
{}

Image::~Image()
{}

Image::Image(const Image& image)
{
  this->operator = (image);
}

Image::Image(Image&& image)
{
  this->operator = (std::move(image));
}

Image& Image::operator = (const Image& image)
{
  if(this == &image) return *this;

  Release();

  this->width_  = image.width_;
  this->height_ = image.height_;
  this->pixels_ = std::make_unique<glm::vec4[]>(width_ * height_);
  std::copy(image.ConstBegin(), image.ConstEnd(), this->Begin());
  return *this;
}

Image& Image::operator = (Image&& image)
{
  Release();

  this->width_  = std::move(image.width_);
  this->height_ = std::move(image.height_);
  this->pixels_ = std::move(image.pixels_);
  return *this;
}

auto Image::At(std::size_t x, std::size_t y) -> glm::vec4&
{
  ASSERT(0 <= x && x < width_ && 0 <= y && y < height_);
  return pixels_[y * width_ + x];
}

auto Image::ConstAt(std::size_t x, std::size_t y) const -> const glm::vec4&
{
  ASSERT(0 <= x && x < width_ && 0 <= y && y < height_);
  return pixels_[y * width_ + x];
}

auto Image::Width() const -> int32_t
{
  return width_;
}

auto Image::Height() const -> int32_t
{
  return height_;
}

auto Image::Load(const char* filepath) -> void
{
  Release();

  std::string ext = path::ParseExtension(filepath);
  if (ext == ".bmp" || ext == ".png" || ext == ".tga")
  {
    int x, y, n;
    unsigned char* data = stbi_load(filepath, &x, &y, &n, 0);

    if (data == NULL)
    {
      ERROR("Could not found %s", filepath);
    }

    width_  = x;
    height_ = y;
    pixels_ = std::make_unique<glm::vec4[]>(width_ * height_);

    if (n == 1 || n == 2)
    {
      ERROR("Does not support image type.");
    }

    int cnt = 0;
    while (cnt < width_ * height_ * n)
    {
      if (n == 3)
      {
        CopyRgbPixel(data, &cnt);
        continue;
      }
      if (n == 4)
      {
        CopyRgbaPixel(data, &cnt);
      }
    }

    stbi_image_free(data);
    return ;
  }
  if (ext == ".hdr")
  {
    // TODO: implementation
    return ;
  }
}

auto Image::SaveAs(const char* filepath) const -> void
{
  const unsigned char* data = ConvertToStbData();

  std::string ext = path::ParseExtension(filepath);
  if (ext == ".bmp")
  {
    stbi_write_bmp(filepath, width_, height_, 3, data);
  }
  if (ext == ".png")
  {
    stbi_write_png(filepath, width_, height_, 3, data, 0);
  }
  if (ext == ".tga")
  {
    stbi_write_tga(filepath, width_, height_, 3, data);
  }
  delete[] data;
}

auto Image::Begin() -> glm::vec4*
{
  return pixels_.get();
}

auto Image::End() -> glm::vec4*
{
  return pixels_.get() + (width_ * height_);
}

auto Image::ConstBegin() const -> glm::vec4* const
{
  return pixels_.get();
}

auto Image::ConstEnd() const -> glm::vec4* const
{
  return pixels_.get() + (width_ + height_);
}

auto Image::Release() -> void
{
  width_  = 0;
  height_ = 0;
  pixels_.reset();
}

auto Image::ConvertToStbData() const -> const unsigned char*
{
  unsigned char* data = new unsigned char[width_ * height_ * 3];

  int cnt = 0;
  for (int y = 0; y < height_; ++y)
  {
    for (int x = 0; x < width_; ++x)
    {
      data[cnt] = pixels_[y * width_ + x].r;
      data[cnt] = pixels_[y * width_ + x].g;
      data[cnt] = pixels_[y * width_ + x].b;
      cnt += 3;
    }
  }

  return data;
}

auto Image::CopyRgbPixel(const unsigned char* data, int* cnt) -> void
{
  int r = static_cast<int>(data[*cnt]);
  int g = static_cast<int>(data[*cnt]);
  int b = static_cast<int>(data[*cnt]);
  glm::vec4 pixel(r, g, b, 1);
  pixels_[*cnt / 3] = pixel;
  (*cnt) += 3;
}

auto Image::CopyRgbaPixel(const unsigned char* data, int* cnt) -> void
{
  int a = static_cast<int>(data[*cnt]);
  int r = static_cast<int>(data[*cnt]);
  int g = static_cast<int>(data[*cnt]);
  int b = static_cast<int>(data[*cnt]);
  glm::vec4 pixel(r, g, b, a);
  pixels_[*cnt / 4] = pixel;
  (*cnt) += 4;
}

} // namespace niepce
