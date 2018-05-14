/*!
 * @file triangle.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "triangle.h"
#include "../core/vector2f.h"
#include "../core/point2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Definition of TriangleMesh
// ---------------------------------------------------------------------------
*/
TriangleMesh::TriangleMesh
(
 const std::vector <Point3f>&  positions,
 const std::vector <Vector3f>& normals,
 const std::vector <Point2f>&  texcoords
) :
  positions_ (positions),
  normals_   (normals),
  texcoords_ (texcoords)
{}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::Position (unsigned int idx) const -> const Point3f&
{
  try { return positions_.at (idx); }
  catch (const std::exception& e) { throw e; }
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::Normal (unsigned int idx) const -> const Vector3f&
{
  try { return normals_.at (idx); }
  catch (const std::exception& e) { throw e; }
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::Texcoord (unsigned int idx) const -> const Point2f&
{
  try { return texcoords_.at (idx); }
  catch (const std::exception& e) { throw e; }
}
/*
// ---------------------------------------------------------------------------
// Definition of Triangle
// ---------------------------------------------------------------------------
*/
Triangle::Triangle
(
 const std::shared_ptr <TriangleMesh>& mesh,
 const std::array <unsigned int, 3>& position_indices,
 const std::array <unsigned int, 3>& normal_indices,
 const std::array <unsigned int, 3>& texcoord_indices,
 bool backface_culling
) :
  mesh_ (mesh),
  position_indices_ (position_indices),
  normal_indices_   (normal_indices),
  texcoord_indices_ (texcoord_indices),
  backface_culling_ (backface_culling)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::IsIntersect
(
 const Ray& ray,
 Intersection* intersection
)
  const noexcept -> bool
{
  // Get the positions
  const Point3f& pos0 = Position (0);
  const Point3f& pos1 = Position (1);
  const Point3f& pos2 = Position (2);

  // Find vectors for two edges sharing position 0.
  const Vector3f edge1 = pos1 - pos0;
  const Vector3f edge2 = pos2 - pos0;

  // Begin calculation determinant also used to calculate U parameter.
  const Vector3f pvec = Cross (ray.Direction (), edge2);

  // If determinant is near zero, ray lies in plane of triangle.
  Float det = Dot (edge1, pvec);
  Float inv_det = 1.0 / det;

  // UV parameter.
  Float u = 0;
  Float v = 0;

  // Distance parameter
  Float t = kInfinity;

  if (backface_culling_)
  {
    if (det < kIntersectionEpsilon) { return false; }

    // Calculate distance from position 0 to ray origin.
    const Vector3f tvec = ray.Origin () - pos0;

    // Calculate U parameter and test bounds
    u = Dot (tvec, pvec);
    if (u < 0.0 || u > det) { return false; }

    // Prepare to test V parameter.
    const Vector3f qvec = Cross (tvec, edge1);

    // Calculate V parameter and test bounds
    v = Dot (ray.Direction (), qvec);
    if (v < 0.0 || u + v > det) { return false; }

    // Calculate t scale parameters ray intersects triangle.
    t = Dot (edge2, qvec) * inv_det;
    u *= inv_det;
    v *= inv_det;

    // Calculate the normal.
    const Vector3f normal = Normalize (Cross (edge1, edge2));

    // calculate the texture coordinates.
    const Point2f tex0 = Texcoord (0);
    const Point2f tex1 = Texcoord (1);
    const Point2f tex2 = Texcoord (2);
    const Point2f uv = (1.0 - u - v) * tex0 + u * tex1 + v * tex2;

    // Store intersection info.
    intersection->SetDistance (t);
    intersection->SetPosition (ray.IntersectAt (t));
    intersection->SetNormal (normal);
    intersection->SetTexcoord (uv);
    return true;
  }
  {
    // Backface culling off
    if (std::fabs (det) < kIntersectionEpsilon) { return false; }

    // Calculate distance from pos0 to ray origin
    const Vector3f tvec = ray.Origin () - pos0;

    // Calculate U parameter and test bounds
    u = Dot (tvec, pvec) * inv_det;
    if (u < 0.0 || u > 1.0) { return false; }

    // Prepare to test V parameter
    const Vector3f qvec = Cross (tvec, edge1);

    // Calculate V parameter and test bounds
    v = Dot (ray.Direction (), qvec) * inv_det;
    if (v < 0.0 || u + v > 1.0) { return false; }

    // Calculate t scale parameters ray intersects triangle.
    t = Dot (edge2, qvec) * inv_det;

    // Calculate the normal
    const Vector3f normal = Normalize (Cross (edge1, edge2));

    // calculate the texture coordinates.
    const Point2f tex0 = Texcoord (0);
    const Point2f tex1 = Texcoord (1);
    const Point2f tex2 = Texcoord (2);
    const Point2f uv = (1.0 - u - v) * tex0 + u * tex1 + v * tex2;

    // Store intersection info.
    intersection->SetDistance (t);
    intersection->SetPosition (ray.IntersectAt (t));
    intersection->SetNormal (normal);
    intersection->SetTexcoord (uv);
  }

  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::Normal (unsigned int idx) const -> const Vector3f&
{
  if (mesh_)
  {
    try { return mesh_->Normal (normal_indices_.at (idx)); }
    catch (const std::exception& e) { throw e; }
  }
  // TODO: throw exception
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::Position (unsigned int idx) const -> const Point3f&
{
  if (mesh_)
  {
    try { return mesh_->Position (position_indices_.at (idx)); }
    catch (const std::exception& e) { throw e; }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::Texcoord (unsigned int idx) const -> const Point2f&
{
  if (mesh_)
  {
    try { return mesh_->Texcoord (texcoord_indices_.at (idx)); }
    catch (const std::exception& e) { throw e; }
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

