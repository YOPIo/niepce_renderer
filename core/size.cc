#include "size.h"

namespace niepce
{

Size::Size()
{}

Size::Size(unsigned width, unsigned height) :
    width_(width),
    height_(height)
{}

Size::~Size()
{}

auto Size::Width() const -> unsigned
{
  return width_;
}

auto Size::Height() const -> unsigned
{
  return height_;
}

}; // namespace niepce
