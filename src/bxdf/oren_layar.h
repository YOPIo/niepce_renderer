#ifndef _OREN_LAYAR_H_
#define _OREN_LAYAR_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "bxdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class OrenLayar : public Bxdf
{
  /* OrenLayar constructors */
public:
  OrenLayar () = delete;
  OrenLayar
  (
   const Spectrum& reflectance,
   Float sigma
  );


  /* OrenLayar destructor */
public:
  virtual ~OrenLayar () = default;


  /* OrenLayar public operators*/
public:
  OrenLayar (const OrenLayar&  ol) = default;
  OrenLayar (      OrenLayar&& ol) = default;

  auto operator = (const OrenLayar&  ol) -> OrenLayar& = default;
  auto operator = (      OrenLayar&& ol) -> OrenLayar& = default;


  /* OrenLayar public override methods */
  auto Pdf
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Float override final;

  auto Evaluate
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Spectrum override final;

  auto EvaluateAndSample
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
            Vector3f* incident, /* BSDF coordinate system */
      const Sample2f& sample,
            Float*    pdf,
            BsdfType* type
  )
  const -> Spectrum override final;

  auto ToString () const -> std::string override final;


  /* OrenLayar private data */
private:
  const Float a_;
  const Float b_;
  const Spectrum reflectance_;
}; // class OrenLayar
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _OREN_LAYAR_H_
