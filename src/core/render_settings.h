/*!
 * @file render_settings.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/21
 * @details 
 */
#ifndef _RENDER_SETTINGS_H_
#define _RENDER_SETTINGS_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class RenderSettings
//! @brief
//! @details
//! ----------------------------------------------------------------------------
// Todo: singleton
class RenderSettings
{
public:
  /*!
   * @enum Item
   * @brief It is used to get the rendering setting value from this class.
   * @details
   */
  enum Item
  {
    kWidth,      /*!< The length of width of image. */
    kHeight,     /*!< The length of height of image. */
    kTileWidth,  /*!< The length of width of tile. */
    kTileHeight, /*!< The length of height of tile. */
    kNumThread,  /*!< The number of thread to render a image. */
    kNumSamples, /*!< The number of sampling. */
    kPTMaxDepth, /*!< The number of depth if path tracing avaliable. */
    kNumRound,
  };

public:
  //! Default constructor
  RenderSettings () = default;

  //! Copy constructor
  RenderSettings (const RenderSettings& settings) = default;

  //! Move constructor
  RenderSettings (RenderSettings&& settings) = default;

  //! Destructor
  virtual ~RenderSettings () = default;

  //! Copy assignment operator
  auto operator = (const RenderSettings& settings) -> RenderSettings& = default;

  //! Move assignment operator
  auto operator = (RenderSettings&& settings) -> RenderSettings& = default;

public:
  //! @fn Status AddItem (Parameter, unsigned int)
  //! @brief Add a render setting to internal data.
  //! @param[in] The parameter that you want to add.
  //! @return none
  //! @exception nonen
  //! @details
  auto AddItem (Item param, unsigned int val) noexcept -> void;

  //! @fn unsigned int Get (Parameter)
  //! @brief Get the render setting item.
  //! @param[in] param Item what will return.
  //! @return Return the render setting item as unsigned integer.
  //! @exception none
  //! @details 
  auto GetItem (Item param) const noexcept -> unsigned int;

private:
  std::map <Item, unsigned int> parameters_;

}; // class RenderSettings
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _RENDER_SETTINGS_H_
