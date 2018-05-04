/*!
 * @file scene.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#ifndef _SCENE_H_
#define _SCENE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../primitive/primitive.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Scene
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Scene
{
public:
  //! The default class constructor.
  Scene () = default;

  //! The copy constructor of the class.
  Scene (const Scene& scene) = default;

  //! The move constructor of the class.
  Scene (Scene&& scene) = default;

  //! The default class destructor.
  virtual ~Scene () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Scene& scene) -> Scene& = default;

  //! The move assignment operator of the class.
  auto operator = (Scene&& scene) -> Scene& = default;

public:
  /*!
   * @fn void Intersect (const Ray& ray, Intersection* intersection)
   * @brief 
   * @param[in] ray 
   * @param[out] intersection Ray intersected with a shape or not.
   * @return void
   * @exception none
   * @details
   */
  auto Intersect
  (
   const Ray& ray, // outgoing
   Intersection* intersection
  )
  const noexcept -> bool;

private:
  std::vector <Primitive> primitives_;

}; // class Scene
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
#endif // _SCENE_H_
