/*!
 * @file aggregation.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "aggregation.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto Aggregation::AddPrimitive (const std::shared_ptr<Primitive> &primitive)
  noexcept -> void
{
  primitives_.push_back (primitive);
}
/*
// ---------------------------------------------------------------------------
*/
auto Aggregation::IsIntersect
(
 const Ray &ray,
 Intersection *intersection
)
  const noexcept -> bool
{
  for (const auto& primitive : primitives_)
  {
    // Intersection test
    Intersection tmp;
    if (primitive->IsIntersect (ray, &tmp))
    {
      if (tmp.Distance () < intersection->Distance ())
      {
        *intersection = tmp;
      }
    }
  }
  return static_cast <bool> (*intersection);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

