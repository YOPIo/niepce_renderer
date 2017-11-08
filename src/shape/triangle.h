#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "shape.h"
#include "vertex.h"
#include "../core/geometry.h"
#include "../sampler/sampler_utils.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Triangle : public Shape
{
  /* Triangle constructors */
public:
  Triangle () = delete;

  Triangle
  (
   const std::shared_ptr<Vertex>& v0,
   const std::shared_ptr<Vertex>& v1,
   const std::shared_ptr<Vertex>& v2
   );


  /* Triangle public destructor */
public:
  ~Triangle ();


  /* Triangle public operators */
public:
  Triangle (const Triangle&  t) = default;
  Triangle (      Triangle&& t) = default;

  auto operator = (const Triangle&  t) -> Triangle& = default;
  auto operator = (      Triangle&& t) -> Triangle& = default;


  /* Triangle override methods */
public:
  // Return surface area of triangle
  auto SurfaceArea () const -> Float override;

  // Return bounding box in object coordinate
  auto LocalBounds () const -> Bounds3f override;

  // Return bounding box in world coordinate
  auto WorldBounds () const -> Bounds3f override;

  // Intersection test
  auto IsIntersect
  (
   const Ray&          ray,
   SurfaceInteraction* surface
  )
  const -> bool override;

  // Sample a point on the surface of the shape
  auto Sample (const Sample2f& sample) const -> Interaction override final;

  // Return the PDF
  auto Pdf () const -> Float override final;

  auto ToString () const -> std::string override final;

  /* Triangle private methods */
 private:
  auto GetPosition (size_t idx) const -> Point3f;
  auto GetNormal   (size_t idx) const -> Normal3f;
  auto GetTexcoord (size_t idx) const -> Point2f;


  /* Triangle private data */
public:
  std::array<std::shared_ptr<Vertex>, 3> vertices_;
}; // class Triangle
/*
// ---------------------------------------------------------------------------
*/
// ---------------------------------------------------------------------------
// Create triangle shape function
// ---------------------------------------------------------------------------
auto CreateTriangleShape
(
 const std::shared_ptr<Vertex>& v0,
 const std::shared_ptr<Vertex>& v1,
 const std::shared_ptr<Vertex>& v2
 )
-> std::shared_ptr<Triangle>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TRIANGLE_H_
