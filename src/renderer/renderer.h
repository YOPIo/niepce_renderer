/*!
 * @file renderer.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/21
 * @details 
 */
#ifndef _RENDERER_H_
#define _RENDERER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/render_settings.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Renderer
//! @brief The base class for renderer.
//! @details All of class that render the scene should inherit this class. The
//!          renderer class is a interface.
//! ----------------------------------------------------------------------------
class Renderer
{
public:
  //! The default class constructor.
  Renderer (const RenderSettings &settings);

  //! The copy constructor of the class.
  Renderer (const Renderer& renderer) = default;

  //! The move constructor of the class.
  Renderer (Renderer&& renderer) = default;

  //! The default class destructor.
  virtual ~Renderer () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Renderer& renderer) -> Renderer& = default;

  //! The move assignment operator of the class.
  auto operator = (Renderer&& renderer) -> Renderer& = default;

public:
  //! @fn virtual void Render ()
  //! @brief 
  //! @param[in] 
  //! @param[out] 
  //! @return 
  //! @exception none
  //! @details 
  virtual auto Render () -> void = 0;

  const RenderSettings settings_;

}; // class Renderer
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _RENDERER_H_
