#include "interaction.h"

namespace niepce
{

Interaction::Interaction()
{}

Interaction::Interaction(const Point3f&  _position,
                         const Vector3f& _direction,
                         const Normal3f& _normal) :
    position(_position), direction(_direction), normal(_normal)
{}

SurfaceInteraction::SurfaceInteraction()
{}

SurfaceInteraction::SurfaceInteraction(const Point3f&  _position, const Vector3f& _direction,
                                       const Normal3f& _normal,   const Point2f&  _uv,
                                       const Vector2f& _dpdu,     const Vector2f& _dpdv,
                                       const Normal3f& _dndu,     const Normal3f& _dndv) :
    Interaction(_position, _direction, _normal), uv(_uv),
    dpdu(_dpdu), dpdv(_dpdv),
    dndu(_dndu), dndv(_dndv)
{}


}  // namespace niepce
