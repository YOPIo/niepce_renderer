#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <memory>

#include "../core/common.h"
#include "../core/path.h"

namespace niepce
{

class Image
{
 public:
  using Pixels = std::unique_ptr<glm::vec4[]>;

  Image();
  virtual ~Image();

  Image(const Image& image);
  Image(Image&& image);
  Image& operator = (const Image& image);
  Image& operator = (Image&& image);

  auto At(std::size_t x, std::size_t y) -> glm::vec4&;
  auto ConstAt(std::size_t x, std::size_t y) const -> const glm::vec4&;

  auto Width() const -> int32_t;
  auto Height() const -> int32_t;

  auto Load(const char* filepath) -> void;
  auto SaveAs(const char* filepath) const -> void;

 private:
  auto Begin() -> glm::vec4*;
  auto End() -> glm::vec4*;
  auto ConstBegin() const -> glm::vec4* const;
  auto ConstEnd() const -> glm::vec4* const;

  auto Release() -> void;

  auto ConvertToStbData() const -> const unsigned char*;

  auto CopyRgbPixel(const unsigned char* data, int* cnt) -> void;
  auto CopyRgbaPixel(const unsigned char* data, int* cnt) -> void;

  uint32_t width_;
  uint32_t height_;
  Pixels   pixels_;
};

} // namespace niepce

#endif // _IMAGE_H_
