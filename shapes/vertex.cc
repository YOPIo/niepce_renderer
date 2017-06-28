#include "vertex.h"

namespace niepce
{

Vertex::Vertex () :
    position ( Point3f  (0, 0, 0) ),
    normal   ( Normal3f (0, 0, 0) ),
    uv       ( Point2f  (0, 0) )
{}

Vertex::Vertex (const Point3f&   p,
                const Normal3f&  n,
                const Point2f&   u) :
    position(p),
    normal(n),
    uv(u)
{}

/*
Vertex::Vertex (const Transform& local_to_world,
                const Point3f&   p,   // Position
                const Normal3f&  n,   // Normal
                const Point2f&   u) : // UV
    position(local_to_world * p),
    normal(local_to_world * n),
    uv(u)
{}
*/

Vertex::~Vertex()
{}

}  // namespace niepce
