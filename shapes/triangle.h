#include "../core/niepce.h"
#include "../core/transform.h"
#include "../geometries/ray.h"
#include "../geometries/boundingbox3.h"
#include "vertex.h"
#include "shape.h"

namespace niepce
{

struct TriangleMesh
{
  TriangleMesh () = delete;

  TriangleMesh (const std::vector<Vertex>&       mesh,
                const std::vector<unsigned int>& indices,
                      unsigned int               num_triangles);

  virtual ~TriangleMesh ();

  TriangleMesh (const TriangleMesh&  tm) = default;
  TriangleMesh (      TriangleMesh&& tm) = default;


  // ---------------------------------------------------------------------------
  // TriangleMesh operators
  // ---------------------------------------------------------------------------
  auto operator = (const TriangleMesh&  tm) -> TriangleMesh& = default;
  auto operator = (      TriangleMesh&& tm) -> TriangleMesh& = default;

  auto operator [] (unsigned int idx) const -> Vertex;

  // ---------------------------------------------------------------------------
  // TriangleMesh data  (*All of faces should be triangle)
  // ---------------------------------------------------------------------------
  const std::vector<Vertex>       mesh_;       // An array of vertices
  const std::vector<unsigned int> indices_;    // Reference to pointers
  const unsigned int              kTriangles_; // Number of tirangles

  // Todo: append
  // std::shared_ptr<Texture> textures_;
};


// ---------------------------------------------------------------------------
// Triangle class has just three reference indices
// ---------------------------------------------------------------------------
class Triangle : public Shape
{
 public:
  Triangle () = delete;
  Triangle (const std::shared_ptr<TriangleMesh>& mesh,
            const std::array<unsigned int, 3>&   indices);
  virtual ~Triangle ();

  Triangle (const Triangle&  t) = default;
  Triangle (      Triangle&& t) = default;

  auto operator = (const Triangle& t) -> Triangle& = default;
  auto operator = (Triangle&& t)      -> Triangle& = default;

  // Return surface area of triangle
  auto SurfaceArea      () const -> Float;

  // Return bounding box in object coordinate
  auto LocalBoundingBox () const -> Bounds3f;

  // Return bounding box in world coordinate
  auto WorldBoundingBox () const -> Bounds3f;

  // Intersection test
  auto IsIntersect (const Ray&          ray,
                    Float*              t,
                    SurfaceInteraction* surface) const -> bool;

 private:
  std::shared_ptr<TriangleMesh> mesh_;
  std::array<unsigned int,   3> indices_; // A fixed array of references to vertex
};


}  // namespace niepce
