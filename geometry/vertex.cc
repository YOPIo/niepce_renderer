#include "vertex.h"

namespace niepce
{

Vertex::Vertex()
{}

Vertex::Vertex(glm::vec3 position,
               glm::vec3 normal,
               glm::vec3 texcoord) :
    position_(position),
    normal_(normal),
    texcoord_(texcoord)
{}

} // namespace niepce
