#ifndef _AGGREGATE_PRIMITIVE_H_
#define _AGGREGATE_PRIMITIVE_H_

#include "../core/niepce.h"
#include "primitive.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Interface of accelerators
// ---------------------------------------------------------------------------
class AggregatePrimitive : public Primitive
{
  /* AggregatePrimitive constructors */
 public:
  AggregatePrimitive ();
  virtual ~AggregatePrimitive ();

  AggregatePrimitive (const AggregatePrimitive&  aggregate) = default;
  AggregatePrimitive (      AggregatePrimitive&& aggregate) = default;


  /* AggragatePrimitive operators */
  auto operator = (const AggregatePrimitive&  aggregate) -> AggregatePrimitive& = default;
  auto operator = (      AggregatePrimitive&& aggregate) -> AggregatePrimitive& = default;


  /* Aggragateprimitive override methods */
  auto WorldBounds () const -> Bounds3f override;
  auto LocalBounds () const -> Bounds3f override;

  // Return surface area of a primitive
  auto SurfaceArea () const -> Float override;

  // Ray-Object intersection test interface
  auto IsIntersect(const Ray& ray, Interaction* interaction) const -> bool override;

}; // class AggregatePrimitive

}  // namespace niepce

#endif // _AGGREGATE_PRIMITIVE_H_
