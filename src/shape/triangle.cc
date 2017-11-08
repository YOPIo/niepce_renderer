#include "triangle.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Triangle::Triangle
(
 const std::shared_ptr<Vertex>& v0,
 const std::shared_ptr<Vertex>& v1,
 const std::shared_ptr<Vertex>& v2
) :
  Shape     (Transform ()),
  vertices_ ( std::array<std::shared_ptr<Vertex>, 3> ({v0, v1, v2}) )
{}
/*
// ---------------------------------------------------------------------------
*/
Triangle::~Triangle ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::SurfaceArea() const -> Float
{
  const Point3f& p0 = *(vertices_[0]->position);
  const Point3f& p1 = *(vertices_[1]->position);
  const Point3f& p2 = *(vertices_[2]->position);
  return 0.5 * Cross(p1 - p0, p2 - p0).Length();
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::LocalBounds () const -> Bounds3f
{
  // Because all of vertices located in world coordinate, transform them to local coordinate
  // TODO: implementation
  return Bounds3f ({});
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::WorldBounds () const -> Bounds3f
{
  const Point3f& p0 = *(vertices_[0]->position);
  const Point3f& p1 = *(vertices_[1]->position);
  const Point3f& p2 = *(vertices_[2]->position);
  return Bounds3f ({p0, p1, p2});
}
/*
// ---------------------------------------------------------------------------
// Reference: Fast, Minimum Storage Ray/Triangle Intersection
// ---------------------------------------------------------------------------
*/
auto Triangle::IsIntersect
(
 const Ray&          ray,
 SurfaceInteraction* interaction
)
const -> bool
{
  // Get vertices which representing a triangle face
  const Point3f& p0 = GetPosition (0);
  const Point3f& p1 = GetPosition (1);
  const Point3f& p2 = GetPosition (2);


  // Find vectors for two edges sharing vertex0
  const Vector3f edge0 = p1 - p0;
  const Vector3f edge1 = p2 - p0;

  const Vector3f pvec = Cross (ray.direction, edge1);

  const Float det = Dot (edge0, pvec);
  if (std::abs (det) < kEpsilon)
  {
    return false;
  }
  Float inv_det = 1.0 / det;

  const Vector3f tvec = ray.origin - p0;
  const Float    u    = Dot (tvec, pvec) * inv_det;
  if (u < 0.0 || u > 1.0)
  {
    return false;
  }

  const Vector3f qvec = Cross (tvec, edge0);
  const Float    v    = Dot (ray.direction, qvec) * inv_det;
  if (v < 0.0 || u + v > 1.0)
  {
    return false;
  }

  const Float t = Dot (edge1, qvec) * inv_det;
  if (std::abs (t) < kEpsilon)
  {
    return false;
  }
  if (t <= kEpsilon)
  {
    return false;
  }

  // Ray intersect with triangle shape
  // Compute hit position, normal, uv coodinate etc...
  const Point3f  position = ray (t);
  const Normal3f normal   = Normalize (Cross (edge0, edge1));
  const Vector3f outgoing = Normalize (-ray.direction);

  // Get UV coordinate, if present
  const Point2f uv0 (GetTexcoord (0));
  const Point2f uv1 (GetTexcoord (1));
  const Point2f uv2 (GetTexcoord (2));

  // Compute the texcoord
  const Float   uv (1.0 - u - v);
  const Point2f texcoord (uv * uv0 + u * uv1 + v * uv2);

  // Compute partial derivatives dpdu and dpdv
  const Vector2f duv02 (uv0 - uv2);
  const Vector2f duv12 (uv1 - uv2);
  const Vector3f dp02  (p0 - p2);
  const Vector3f dp12  (p1 - p2);
  const Float    determinant (duv02.u * duv12.v - duv02.v * duv12.u);

  // Conpute triangle partial derivatives
  Vector3f dpdu, dpdv;
  if (determinant < 1e-5)
  {
      inv_det = 1.0 / determinant;
      dpdu = ( duv12.v * dp02 - duv02.v * dp12) * inv_det;
      dpdv = (-duv12.u * dp02 + duv02.u * dp12) * inv_det;
  }
  if (determinant >= 1e-5 || Cross (dpdu, dpdv).LengthSquared () == 0)
  {
    OrthoNormalBasis (normal, &dpdu, &dpdv);
  }

  // Initialize SurfaceInteraction
  *interaction = SurfaceInteraction (position,
                                     outgoing,
                                     normal,
                                     t,
                                     texcoord,
                                     dpdu,
                                     dpdv,
                                     Normal3f (0, 0, 0),
                                     Normal3f (0, 0, 0));
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::Sample (const Sample2f& sample) const -> Interaction
{
  const Point2f b (SampleUniformTriangle (sample));

  // Get triangle vertices
  const Point3f& p0 = *(vertices_[0]->position);
  const Point3f& p1 = *(vertices_[0]->position);
  const Point3f& p2 = *(vertices_[0]->position);

  Interaction it;
  it.position = b[0] * p0 + b[1] * p1 + (1 - b[0] - b[1]) * p2;
  // Compute surface normal for sampled point on triangle
  it.normal = (Normal3f (Cross (p1 - p0, p2 - p0)));

  /*
  // Ensure correct orientation of the geometric normal; follow the same
  // approach as was used in Triangle::Intersect().
  if (mesh->n)
  {
    Normal3f ns(b[0] * mesh->n[v[0]] + b[1] * mesh->n[v[1]] +
                (1 - b[0] - b[1]) * mesh->n[v[2]]);
    it.normal = Faceforward(it.n, ns);
  }
  else if (reverseOrientation ^ transformSwapsHandedness)
    it.normal *= -1;
  */

  // Compute error bounds for sampled point on triangle
  // Point3f pAbsSum = Abs(b[0] * p0) + Abs(b[1] * p1) + Abs((1 - b[0] - b[1]) * p2);
  // it.pError = gamma(6) * Vector3f(pAbsSum.x, pAbsSum.y, pAbsSum.z);
  return it;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::Pdf () const -> Float
{
  return 1.0 / SurfaceArea ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::ToString () const -> std::string
{
  std::string str ("");
  str += "Shape type: Triangle\n";
  str += "Position : [" + GetPosition(0).ToString () + ", " +
          GetPosition (1).ToString () + ", " +
          GetPosition (2).ToString () + "]\n";
  return str;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::GetPosition (size_t idx) const -> Point3f
{
  // TODO: Range check
  if (vertices_[idx] && vertices_[idx]->position)
  {
    return *(vertices_[idx]->position);
  }
  // std::cerr << "Position does not exist." << std::endl;
  return Point3f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::GetNormal (size_t idx) const -> Normal3f
{
  // todo: Range check
  if (vertices_[idx] && vertices_[idx]->normal)
  {
    return *(vertices_[idx]->normal);
  }
  // std::cerr << "Normal does not exist." << std::endl;
  return Normal3f (0, 1, 0);
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::GetTexcoord (size_t idx) const -> Point2f
{
  // todo: Range check
  if (vertices_[idx]->texcoord != nullptr)
  {
    std::cout << "hogehoge" << std::endl;
    return *(vertices_[idx]->texcoord);
  }
  if (idx == 0) { return Point2f (0, 0); }
  if (idx == 1) { return Point2f (1, 0); }
  if (idx == 2) { return Point2f (1, 1); }
  return Point2f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
