/*!
 * @file shape.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "shape.h"
#include "../core/bounds3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Shape::Shape () :
  world_to_local_ (Transform ()),
  local_to_world_ (Transform ())
{}
/*
// ---------------------------------------------------------------------------
*/
Shape::Shape (const Transform &local_to_world) :
  local_to_world_ (local_to_world),
  world_to_local_ (Inverse (local_to_world))
{}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

