#include "aggregate_primitive.h"

namespace niepce
{

AggregatePrimitive::AggregatePrimitive ()
{}

AggregatePrimitive::~AggregatePrimitive ()
{}

auto AggregatePrimitive::WorldBounds () const -> Bounds3f
{
  std::cerr << "Error: AggregatePrimitive was called" << std::endl;
  // TODO: This methods should not be called
}

auto AggregatePrimitive::LocalBounds () const -> Bounds3f
{
  std::cerr << "Error: AggregatePrimitive was called" << std::endl;
  // TODO: This methods should not be called
}

auto AggregatePrimitive::SurfaceArea () const -> Float
{
  std::cerr << "Error: AggregatePrimitive was called" << std::endl;
  // TODO: This methods should not be called
}

auto AggregatePrimitive::IsIntersect(const Ray& ray, Interaction* interaction) const -> bool
{
  std::cerr << "Error: AggregatePrimitive was called" << std::endl;
  // TODO: This methods should not be called
}

}  // namespace niepce
