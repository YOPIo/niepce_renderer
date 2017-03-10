#include "interaction.h"

namespace niepce
{

Interaction::Interaction() :
    position( Point3f() ),
    direction( Vector3f() ),
    normal( Normal3f() )
{}

Interaction::Interaction(const Point3f&  _position,
                         const Vector3f& _direction,
                         const Normal3f& _normal) :
    position(_position), direction(_direction), normal(_normal)
{}

Interaction::~Interaction()
{}

SurfaceInteraction::SurfaceInteraction() :
    Interaction(),
    uv( Point2f() ),
    dpdu( Vector2f() ),
    dpdv( Vector2f() ),
    dndu( Normal3f() ),
    dndv( Normal3f() )
{}

SurfaceInteraction::SurfaceInteraction(const Point3f&  _position, const Vector3f& _direction,
                                       const Normal3f& _normal,   const Point2f&  _uv,
                                       const Vector2f& _dpdu,     const Vector2f& _dpdv,
                                       const Normal3f& _dndu,     const Normal3f& _dndv) :
    Interaction(_position, _direction, _normal), uv(_uv),
    dpdu(_dpdu), dpdv(_dpdv),
    dndu(_dndu), dndv(_dndv)
{}

SurfaceInteraction::~SurfaceInteraction()
{}

}  // namespace niepce
