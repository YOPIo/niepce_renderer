#ifndef _SIZE_VECTOR_H_
#define _SIZE_VECTOR_H_

#include "../core/common.h"

namespace niepce
{

class SizeVec
{
 public:
  SizeVec();
  SizeVec(const glm::vec3& horizontal, const glm::vec3& vertical);
  ~SizeVec();

  SizeVec(const SizeVec& vec) = default;
  SizeVec(SizeVec&& vec)      = default;
  SizeVec& operator = (const SizeVec& vec) = default;
  SizeVec& operator = (SizeVec&& vec)      = default;

  auto Horizontal() const -> glm::vec3;
  auto Vertical() const -> glm::vec3;

 protected:
  glm::vec3 horizontal_;
  glm::vec3 vertical_;
};


}; // namespace niepce

#endif // _SIZE_VECTOR_H_
