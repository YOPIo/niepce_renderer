/*!
 * @file material_parameters.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _MATERIAL_PARAMETERS_H_
#define _MATERIAL_PARAMETERS_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class MaterialParameters
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class MaterialParameters
{
public:
  enum Item
  {
    kReflectance,
  };

public:
  //! The default class constructor.
  MaterialParameters () = default;

  //! The copy constructor of the class.
  MaterialParameters (const MaterialParameters& params) = default;

  //! The move constructor of the class.
  MaterialParameters (MaterialParameters&& params) = default;

  //! The default class destructor.
  virtual ~MaterialParameters () = default;

  //! The copy assignment operator of the class.
  auto operator = (const MaterialParameters& params) -> MaterialParameters&
    = default;

  //! The move assignment operator of the class.
  auto operator = (MaterialParameters&& params) -> MaterialParameters&
    = default;

public:
  /*!
   * @fn Vector3f ColorItem (Item)
   * @brief 
   * @param[in] 
   * @return 
   * @exception none
   * @details
   */
  auto ColorItem (Item item) const noexcept -> Vector3f;

  /*!
   * @fn Float FloatItem (Item)
   * @brief 
   * @param[in] 
   * @return 
   * @exception none
   * @details
   */
  auto FloatItem (Item item) const noexcept -> Float;

  /*!
   * @fn void WriteColor (Item)
   * @brief 
   * @param[in] 
   * @return 
   * @exception none
   * @details
   */
  auto SetColorItem (Item item, const Vector3f& color) noexcept -> void;

  /*!
   * @fn void WriteFloat (Item)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto SetFloatItem (Item item, Float value) noexcept -> void;

private:
  std::map <Item, Vector3f> color_items_;
  std::map <Item, Float>    float_items_;
}; // class MaterialParameters
/*
// ---------------------------------------------------------------------------
*/
} // namespace n
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATERIAL_PARAMETERS_H_

