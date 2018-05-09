/*!
 * @file render_settings.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/22
 * @details 
 */
#include "render_settings.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto RenderSettings::AddItem (Item item, unsigned int val) noexcept -> void
{
  parameters_.insert (std::make_pair (item, val));
}
/*
// ---------------------------------------------------------------------------
*/
auto RenderSettings::GetItem (Item item) const noexcept -> unsigned int
{
  return parameters_.at (item);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
