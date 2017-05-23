#include "interaction.h"

namespace niepce
{

Interaction::Interaction() :
    position( Point3f() ),
    direction( Vector3f() ),
    normal( Normal3f() )
{}

Interaction::Interaction(      Float     tt,
                         const Point3f&  p,
                         const Vector3f& dir,
                         const Normal3f& n) :
    t(tt),
    position(p),
    direction(dir),
    normal(n)
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

SurfaceInteraction::SurfaceInteraction(Float tt,
                                       const Point3f&  _pos,  const Vector3f& _dir,
                                       const Normal3f& _n,    const Point2f&  _uv,
                                       const Vector2f& _dpdu, const Vector2f& _dpdv,
                                       const Normal3f& _dndu, const Normal3f& _dndv) :
    Interaction(tt, _pos, _dir, _n),
    uv(_uv),
    dpdu(_dpdu), dpdv(_dpdv),
    dndu(_dndu), dndv(_dndv)
{}

SurfaceInteraction::~SurfaceInteraction()
{}

}  // namespace niepce
