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
#include "../accelerator/aggregation.h"
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

  //! The constructor takes aggregation.
  Scene (std::unique_ptr <Aggregation>&& aggregation);

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
  auto IsIntersect
  (
   const Ray& ray, // outgoing
   Intersection* intersection
  )
  const noexcept -> bool;

  /*!
   * @fn void Load ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Load () -> void;

  // TODO: Delete
  auto ReadyCornellBox () -> void;
  auto BuildBokehScene () -> void;

public:
  std::vector <std::shared_ptr<Primitive>> primitives_;
}; // class Scene
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
#endif // _SCENE_H_
