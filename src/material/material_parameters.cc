/*!
 * @file material_parameters.cc
 * @brief 
 * @author Masashi Yoshida 
 * @date 
 * @details 
 */
#include "material_parameters.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto MaterialParameters::ColorItem (Item item) const noexcept -> Vector3f
{
  return color_items_.at (item);
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialParameters::FloatItem (Item item) const noexcept -> Float
{
  return float_items_.at (item);
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialParameters::SetColorItem
(
 Item item,
 const Vector3f &color
)
  noexcept -> void
{
  color_items_.at (item) = color;
}
/*
// ---------------------------------------------------------------------------
*/
auto MaterialParameters::SetFloatItem (Item item, Float value) noexcept -> void
{
  float_items_.at (item) = value;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

