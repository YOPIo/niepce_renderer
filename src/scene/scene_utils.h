#ifndef _SCENE_UTILS_H_
#define _SCENE_UTILS_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "scene.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto CreateCornellBox () -> std::pair<std::shared_ptr<Camera>, Scene>;
auto SphereAndPlane   () -> std::pair<std::shared_ptr<Camera>, Scene>;
auto CreateComparisonSphereScene ()
    -> std::pair<std::shared_ptr<Camera>, Scene>;
auto CreateSphereScene () -> std::pair<std::shared_ptr<Camera>, Scene>;
auto CreateSphereCornellBox () -> std::pair<std::shared_ptr<Camera>, Scene>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SCENE_UTILS_H_
