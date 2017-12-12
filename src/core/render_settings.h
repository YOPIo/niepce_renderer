#ifndef _RENDER_SETTINGS_H_
#define _RENDER_SETTINGS_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct RenderSettings
{
  RenderSettings();
  virtual ~RenderSettings();

  RenderSettings(const RenderSettings&  settings) = default;
  RenderSettings(      RenderSettings&& settings) = default;

  auto operator = (const RenderSettings&  settings) -> RenderSettings& = default;
  auto operator = (      RenderSettings&& settings) -> RenderSettings& = default;

  // RenderSettings data
  std::pair <uint32_t, uint32_t> resolution;
};
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _RENDER_SETTINGS_H_
