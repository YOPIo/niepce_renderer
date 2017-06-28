#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

#include "../core/niepce.h"
#include "../scenes/scene.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Interface
// ---------------------------------------------------------------------------
class Integrator
{
 public:
  /* Integrator constructors */
  Integrator ();
  virtual ~Integrator ();

  Integrator (const Integrator&  integrator) = default;
  Integrator (      Integrator&& integrator) = default;

  /* Integrator operators*/
  auto operator = (const Integrator&  integrator) -> Integrator& = default;
  auto operator =       (Integrator&& integrator) -> Integrator& = default;

  /* Integrator public methods */
  virtual auto Render () -> void = 0;

}; // class Integrator


}  // namespace niepce

#endif // _INTEGRATOR_H_
