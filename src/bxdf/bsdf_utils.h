#ifndef _BSDF_UTILS_H_
#define _BSDF_UTILS_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// BSDF��ɸ��
// BSDF�η׻��Ϥ��٤Ƥ��κ�ɸ�ϤǷ׻������(���ɺ�ɸ�ϤǤϤʤ�)
// �Ȥϥ��å׼�(z��)��
// �դ�x����
// ---------------------------------------------------------------------------
*/
auto CosTheta  (const Vector3f& w) -> Float;
auto Cos2Theta (const Vector3f& w) -> Float;
auto SinTheta  (const Vector3f& w) -> Float;
auto Sin2Theta (const Vector3f& w) -> Float;
auto TanTheta  (const Vector3f& w) -> Float;
auto Tan2Theta (const Vector3f& w) -> Float;
auto CosPhi    (const Vector3f& w) -> Float;
auto Cos2Phi   (const Vector3f& w) -> Float;
auto SinPhi    (const Vector3f& w) -> Float;
auto Sin2Phi   (const Vector3f& w) -> Float;

auto IsSameHemisphere (const Vector3f& outgoing, const Vector3f& incident) -> bool;

// Perfect reflection
auto Reflect (const Vector3f& w, const Normal3f& n) -> Vector3f;

// Snell's low
auto Refract
(
 const Vector3f& incident,
 const Normal3f& normal,
       Float     ior,
       Vector3f* refracted
)
-> bool;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BSDF_UTILS_H_
