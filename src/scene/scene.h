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
#include "../accelerator/bvh.h"
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

  //! The constructor takes primitives.
  Scene
  (
   const std::vector <std::shared_ptr <Primitive>>& primitives,
   const std::vector <std::shared_ptr <Light>>&     lights,
   const std::shared_ptr <niepce::InfiniteLight>&   inf_light
  );

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
   * @exception no
   * @details
   */
  auto IsIntersect
  (
   const Ray& ray, // outgoing
   Intersection* intersection
  )
  const noexcept -> bool;

  /*!
   * @fn std Light (int)
   * @brief 
   * @param[in] idx
   *    
   * @return 
   * @exception none
   * @details
   */
  auto Light (unsigned int idx)
    const noexcept -> std::shared_ptr <niepce::Light>;

  /*!
   * @fn unsigned NumLight ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto NumLight () const noexcept -> unsigned int;

  /*!
   * @fn std InfiniteLight ()
   * @brief 
   * @param[in] 
   * @return 
   * @exception none
   * @details 
   */
  auto InfiniteLight () const noexcept -> std::shared_ptr <InfiniteLight>;


private:
  Bvh primitives_;
  std::vector <std::shared_ptr <niepce::Light>> lights_;

  std::shared_ptr <niepce::InfiniteLight> infinite_light_;

  std::vector <std::shared_ptr <Primitive>> original_;
}; // class Scene
/*
// ---------------------------------------------------------------------------
*/
auto CreateScene
(
 const std::vector <std::shared_ptr <Primitive>>& p,
 const std::vector <std::shared_ptr <Light>>&     lights,
 const std::shared_ptr <niepce::InfiniteLight>&   inf_light
) -> Scene*;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
#endif // _SCENE_H_
