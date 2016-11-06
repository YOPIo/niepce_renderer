#include "size_vector.h"

namespace niepce
{

SizeVec::SizeVec()
{}

SizeVec::SizeVec(const glm::vec3& horizontal, const glm::vec3& vertical) :
    horizontal_(horizontal),
    vertical_(vertical)
{}

SizeVec::~SizeVec()
{}

auto SizeVec::Horizontal() const -> glm::vec3
{
  return horizontal_;
}

auto SizeVec::Vertical() const -> glm::vec3
{
  return vertical_;
}

}; // namespace niepce
