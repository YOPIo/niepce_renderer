#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "../core/common.h"

namespace niepce
{

struct Vertex
{
  Vertex();
  Vertex(glm::vec3 position,
         glm::vec3 normal,
         glm::vec3 texcoord);
  virtual ~Vertex() = default;

  Vertex(const Vertex& vertex) = default;
  Vertex(Vertex&& vertex)      = default;
  Vertex& operator = (const Vertex& vertex) = default;
  Vertex& operator = (Vertex&& vertex)      = default;

  glm::vec3 position_;
  glm::vec3 normal_;
  glm::vec2 texcoord_;
};

} // namespace niepce

#endif // _VERTEX_H_
