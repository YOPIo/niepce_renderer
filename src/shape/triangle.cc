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
#include "../sampler/sampler.h"
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
auto TriangleMesh::Position (int idx) const -> const Point3f&
{
  try { return positions_.at (idx); }
  catch (const std::exception& e) { throw e; }
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::Normal (int idx) const -> const Vector3f&
{
  try { return normals_.at (idx); }
  catch (const std::exception& e) { throw e; }
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::Texcoord (int idx) const -> const Point2f&
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
 const std::array <int, 3>& position_indices,
 const std::array <int, 3>& normal_indices,
 const std::array <int, 3>& texcoord_indices,
 bool backface_culling
) :
  Shape (),
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
  const auto& pos0 = Position (0);
  const auto& pos1 = Position (1);
  const auto& pos2 = Position (2);

  // Find vectors for two edges sharing position 0.
  const auto edge1 = pos1 - pos0;
  const auto edge2 = pos2 - pos0;

  // Begin calculation determinant also used to calculate U parameter.
  const auto pvec = Cross (ray.Direction (), edge2);

  // If determinant is near zero, ray lies in plane of triangle.
  Float det = Dot (edge1, pvec);
  Float inv_det = 1.0 / det;

  // UV parameters.
  Float u = 0;
  Float v = 0;

  // Distance parameter
  Float t = kInfinity;

  // if (false)
  if (backface_culling_)
  {
    if (det < kIntersectionEpsilon) { return false; }

    // Calculate distance from position 0 to ray origin.
    const auto tvec = ray.Origin () - pos0;

    // Calculate U parameter and test bounds
    u = Dot (tvec, pvec);
    if (u < 0.0 || u > det) { return false; }

    // Prepare to test V parameter.
    const auto qvec = Cross (tvec, edge1);

    // Calculate V parameter and test bounds
    v = Dot (ray.Direction (), qvec);
    if (v < 0.0 || u + v > det) { return false; }

    // Calculate t scale parameters ray intersects triangle.
    t = Dot (edge2, qvec) * inv_det;
    u *= inv_det;
    v *= inv_det;

    // Calculate the normal.
    const Vector3f normal = Normalize (Cross (edge1, edge2));
    if (HasNormals ())
    {
      const auto &n1 = Normal (0);
      const auto &n2 = Normal (1);
      const auto &n3 = Normal (2);
      const auto &sn = Normalize ((1.0 - u - v) * n1 + u * n2 + v * n3);
      intersection->SetShadingNormal (sn);
    }

    // calculate the texture coordinates if present.
    Point2f uv;
    if (HasTexcoords ())
    {
      const Point2f tex0 = Texcoord (0);
      const Point2f tex1 = Texcoord (1);
      const Point2f tex2 = Texcoord (2);
      uv = (1.0 - u - v) * tex0 + u * tex1 + v * tex2;
    }

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
    const auto tvec = ray.Origin () - pos0;

    // Calculate U parameter and test bounds
    u = Dot (tvec, pvec) * inv_det;
    if (u < 0.0 || u > 1.0) { return false; }

    // Prepare to test V parameter
    const auto qvec = Cross (tvec, edge1);

    // Calculate V parameter and test bounds
    v = Dot (ray.Direction (), qvec) * inv_det;
    if (v < 0.0 || u + v > 1.0) { return false; }

    // Calculate t scale parameters ray intersects triangle.
    t = Dot (edge2, qvec) * inv_det;

    // Calculate the normal and shading normal.
    const auto normal = Normalize (Cross (edge1, edge2));
    if (HasNormals ())
    {
      const auto &n1 = Normal (0);
      const auto &n2 = Normal (1);
      const auto &n3 = Normal (2);
      const auto &sn = Normalize ((1.0 - u - v) * n1 + u * n2 + v * n3);
      intersection->SetShadingNormal (sn);
    }

    // calculate the texture coordinates if present.
    Point2f uv;
    if (HasTexcoords ())
    {
      const Point2f tex0 = Texcoord (0);
      const Point2f tex1 = Texcoord (1);
      const Point2f tex2 = Texcoord (2);
      uv = (1.0 - u - v) * tex0 + u * tex1 + v * tex2;
    }

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
auto Triangle::Bounds () const noexcept -> Bounds3f
{
  Bounds3f res (Position (0), Position (1));
  res.Merge (Position (2));
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::Sample (const Point2f& sample) const noexcept -> Point3f
{
  const auto s = SampleUniformTriangle (sample);
  const auto& p1 = Position (0);
  const auto& p2 = Position (1);
  const auto& p3 = Position (2);
  return (1.0 - s[0] - s[1]) * p1 + s[0] * p2 + s[1] * p3;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::SurfaceArea () const noexcept -> Float
{
  // Get triangle vertex positions.
  const auto& p1 = Position (0);
  const auto& p2 = Position (1);
  const auto& p3 = Position (2);

  return 0.5 * Cross (p2 - p1, p3 - p1).Length ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::HasNormals () const noexcept -> bool
{
  if (normal_indices_[0] == -1 ||
      normal_indices_[1] == -1 ||
      normal_indices_[2] == -1)
  {
    return false;
  }
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::HasTexcoords () const noexcept -> bool
{
  if (texcoord_indices_[0] != -1 &&
      texcoord_indices_[1] != -1 &&
      texcoord_indices_[2] != -1)
  {
    return true;
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::Normal (int idx) const -> const Vector3f&
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
auto Triangle::Position (int idx) const -> const Point3f&
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
auto Triangle::Texcoord (int idx) const -> const Point2f&
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
auto CreateMesh
(
 const std::vector <Float>& positions,
 const std::vector <Float>& normals,
 const std::vector <Float>& texcoords
)
  -> TriangleMesh*
{
  std::vector <Point3f> pos;
  for (int i = 0; i < positions.size (); i += 3)
  {
    pos.push_back (Point3f (positions[i], positions[i + 1], positions[i + 2]));
  }
  std::vector <Vector3f> nor;
  for (int i = 0; i < normals.size (); i += 3)
  {
    nor.push_back (Vector3f (normals[i], normals[i + 1], normals[i + 2]));
  }
  std::vector <Point2f> tex;
  for (int i = 0; i < texcoords.size (); i += 2)
  {
    tex.push_back (Point2f (texcoords[i], texcoords[i + 1]));
  }
  return new TriangleMesh (pos, nor, tex);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateTriangle
(
 const std::shared_ptr <TriangleMesh>& mesh,
 const std::array <int, 3> p_idx,
 const std::array <int, 3> n_idx,
 const std::array <int, 3> t_idx
)
  -> Triangle*
{
  return new Triangle (mesh, p_idx, n_idx, t_idx, true);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

