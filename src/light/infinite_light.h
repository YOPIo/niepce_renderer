/*!
 * @file infinite_light.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _INFINITE_LIGHT_H_
#define _INFINITE_LIGHT_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/imageio.h"
#include "light.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class InfiniteLight
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class InfiniteLight final : public Light
{
public:
  //! The default class constructor.
  InfiniteLight () = delete;

  //! The constructor takes transform matrix and filename.
  InfiniteLight (const Transform& light_to_world, const char* filename);

  //! The copy constructor of the class.
  InfiniteLight (const InfiniteLight& light) = default;

  //! The move constructor of the class.
  InfiniteLight (InfiniteLight&& light) = default;

  //! The default class destructor.
  virtual ~InfiniteLight () = default;

  //! The copy assignment operator of the class.
  auto operator = (const InfiniteLight& light) -> InfiniteLight& = default;

  //! The move assignment operator of the class.
  auto operator = (InfiniteLight&& light) -> InfiniteLight& = default;

public:
  /*!
   * @fn Spectrum Emission ()
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto Emission () const noexcept -> Spectrum override final;

  /*!
   * @fn Point3f SamplePosition (const)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto SamplePosition (const Point2f &sample)
    const noexcept -> Point3f override final;

  /*!
   * @fn Spectrum Evaluate (const)
   * @brief 
   * @param[in] intersection
   *    
   * @return 
   * @exception none
   * @details 
   */
  auto Evaluate
  (
   const Intersection& intersection,
   Float* pdf
  )
    const noexcept -> Spectrum;

  /*!
   * @fn Float Pdf ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  auto Pdf () const noexcept -> Float override final;


private:
  std::shared_ptr <ImageIO <Spectrum>> image_;
}; // class InfiniteLight
/*
// ---------------------------------------------------------------------------
*/
auto CreateInfiniteLight (const Attributes& attributes)
  -> std::shared_ptr <InfiniteLight>;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _INFINITE_LIGHT_H_

