/*!
 * @file render_settings.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/22
 * @details 
 */
#include "render_settings.h"
#include "status.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto RenderSettings::AddItem (Item item, unsigned int val) -> Status
{
  try
  {
    parameters_.insert (std::make_pair (item, val));
    return Status::kSuccess;
  }
  catch (const std::exception& e)
  {
    
  }
  return Status::kFailure;
}
/*
// ---------------------------------------------------------------------------
*/
auto RenderSettings::GetInt (Item item) -> unsigned int
{
  try
  {
    return parameters_.at (item);
  }
  catch (const std::exception& e)
  {
    // Fix: return non-zero
    return 0;
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
