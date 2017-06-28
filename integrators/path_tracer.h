#ifndef _PATH_TRACER_H_
#define _PATH_TRACER_H_

#include "../core/niepce.h"
#include "integrator.h"
#include "../scenes/scene.h"
#include "../randoms/xorshift.h"

namespace niepce
{

class PathTracer : public Integrator
{
 public:
  /* PathTracer constructors */
  PathTracer ();
  virtual ~PathTracer ();

  PathTracer (const PathTracer&  render) = default;
  PathTracer (      PathTracer&& render) = default;

  /* PathTracer operators*/
  auto operator = (const PathTracer& render) -> PathTracer& = default;
  auto operator = (PathTracer&& render)      -> PathTracer& = default;

  /* PathTracer public methods */
 public:
  auto Render () -> void override;

  /* PathTracer private methods */
 private:
  auto RecursiveRender (const XorShift& rnd, unsigned int depth) -> Vector3f;

  /* PathTracer private data */
  std::shared_ptr<Scene>  scene_;
  std::shared_ptr<Camera> camera_;

}; // class PathTracer


}  // namespace niepce

#endif // _PATH_TRACER_H_
