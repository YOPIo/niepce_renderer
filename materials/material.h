#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../core/niepce.h"
#include "../geometries/ray.h"
#include "../geometries/vector3.h"
#include "../randoms/xorshift.h"


namespace niepce
{

// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
inline auto Reflect(const Vector3f& incoming,
                    const Vector3f& normal) -> Vector3f;

// ---------------------------------------------------------------------------
// Material
//  - Lambert
//  - Specular
//  - Refraction
// ---------------------------------------------------------------------------
class Material
{
 public:
  // ---------------------------------------------------------------------------
  // Material public material type
  // ---------------------------------------------------------------------------
  enum Type
  {
    kLambert,
    kMirror,   // Not implemented now
    kGlass,
    kLight
  };

 public:
  Material ();
  Material (const Vector3f& emission,
            const Vector3f& reflectance);
  virtual ~Material ();

  Material (const Material&  mat) = default;
  Material (      Material&& mat) = default;


  // ---------------------------------------------------------------------------
  // Material public operators
  // ---------------------------------------------------------------------------
 public:
  auto operator = (const Material&  mat) -> Material& = default;
  auto operator = (      Material&& mat) -> Material& = default;


  // ---------------------------------------------------------------------------
  // Material public methods
  // ---------------------------------------------------------------------------
 public:
  auto Emission    () const -> Vector3f;
  auto Reflectance () const -> Vector3f;


  // ---------------------------------------------------------------------------
  // Override public methods
  // ---------------------------------------------------------------------------
 public:
  // Sample next ray direction
  virtual auto SampleRay (const Vector3f& hitpoint,
                          const Vector3f& incoming,
                          const Vector3f& surface_normal,
                                Float*    pdf,
                                Vector3f* brdf) const -> Ray = 0;

  virtual auto GetMaterialType () const -> Type = 0;


  // ---------------------------------------------------------------------------
  // Material protected override methods
  // ---------------------------------------------------------------------------
 protected:
  // Compute PDF
  virtual auto PDF (const Vector3f& incoming,
                    const Vector3f& normal,
                    const Vector3f& next_ray_dir) const -> Float = 0;

  // Compute BRDF
  virtual auto BRDF (const Vector3f& incoming,
                     const Vector3f& outgoing,
                     const Vector3f& normal  ) const -> Vector3f = 0;

  // ---------------------------------------------------------------------------
  // Material protected data
  // ---------------------------------------------------------------------------
 protected:
  Vector3f emission_;
  Vector3f reflectance_;
}; // class Material


// ---------------------------------------------------------------------------
// Diffuse Material
// ---------------------------------------------------------------------------
class Lambert : public Material
{
 public:
  Lambert();
  Lambert(const Vector3f& emission,
          const Vector3f& reflectance);
  virtual ~Lambert();

  Lambert(const Lambert& mat) = default;
  Lambert(Lambert&& mat)      = default;

  auto operator = (const Lambert& mat) -> Lambert& = default;
  auto operator = (Lambert&& mat)      -> Lambert& = default;

  // ---------------------------------------------------------------------------
  // Override public methods
  // ---------------------------------------------------------------------------
 public:
  // Sample next ray direction
  virtual auto SampleRay( const Vector3f& hitpoint,
                          const Vector3f& incoming,
                          const Vector3f& surface_normal,
                                Float*    pdf,
                                Vector3f* brdf) const -> Ray override;

  virtual auto GetMaterialType () const -> Type override;

  // ---------------------------------------------------------------------------
  // Override private methods
  // ---------------------------------------------------------------------------
 protected:
  // Compute PDF
  virtual auto PDF (const Vector3f& incoming,
                    const Vector3f& normal,
                    const Vector3f& next_ray_dir) const -> Float override;

  // Compute BRDF
  virtual auto BRDF (const Vector3f& incoming,
                     const Vector3f& outgoing,
                     const Vector3f& normal  ) const -> Vector3f override;
};

/*
class Mirror : public Material
{
 public:
  Mirror() :
      Material(Vector3f(0, 0, 0),  // emission
               Vector3f(0, 0, 0)), // reflectance
      n(100.0)
  {};
  Mirror(const Vector3f& emission,
         const Vector3f& reflectance,
         Float n_) :
      Material(emission, reflectance),
      n(n_)
  {}
  virtual ~Mirror()
  {};

  Mirror(const Mirror& mat) = default;
  Mirror(Mirror&& mat)      = default;

  auto operator = (const Mirror& mat) -> Mirror& = default;
  auto operator = (Mirror&& mat)      -> Mirror& = default;


  // ---------------------------------------------------------------------------
  // Override methods
  // ---------------------------------------------------------------------------
  // Compute PDF
  virtual auto PDF(const Vector3f& incoming,
                   const Vector3f& normal,
                   const Vector3f& next_ray_dir) const -> Float override
  {
    const Vector3f reflection_dir = Reflect(incoming, normal);
    Float cosine = Dot(reflection_dir, next_ray_dir);
    if (cosine < 0) { cosine = 0.0; }
    return (n + 1.0) / (2.0 / kPi) * std::pow(cosine, n);
  }

  // Compute BRDF
  virtual auto BRDF(const Vector3f& incoming,
                    const Vector3f& outgoing,
                    const Vector3f& normal  ) const -> Vector3f override
  {
    if (Dot(normal, outgoing) < 0)
    {
      return Vector3f(0, 0, 0);
    }

    const Vector3f reflection_dir = Reflect(incoming, normal);
    Float cosine = Dot(reflection_dir, outgoing);
    if (cosine < 0) { cosine = 0.0; }
    return reflectance_ * (n + 2.0) / (2.0 * kPi) * std::pow(cosine, n);
  }

  // Sample next ray direction
  virtual auto SampleRay(const Vector3f& hitpoint,
                         const Vector3f& incoming,
                         const Vector3f& surface_normal) const -> Ray override
  {
    const Vector3f reflection = Reflect(incoming, surface_normal);

    // Compute ortho normal basis
    const Vector3f normal    = Normalize(reflection);
    const Vector3f tangent   = (std::fabs(normal.x) > std::fabs(normal.y)) ?
                                Normalize( Cross(Vector3f(0, 1, 0), normal) ) :
                                Normalize( Cross(Vector3f(1, 0, 0), normal) );
    const Vector3f bitangent = Normalize( Cross(normal, tangent) );


    const Float u1 = XorShift::Next01();
    const Float u2 = XorShift::Next01();

    const Float phi   = u1 * 2.0 * kPi;
    const Float theta = std::acos( std::pow(u2, 1.0 / (n + 1)) );

    const Vector3f next_dir = tangent * std::sin(theta) * std::cos(phi) +
                              normal * std::cos(theta) +
                              bitangent * std::sin(theta) * std::sin(phi);

    return Ray(hitpoint, next_dir);
  }

  // Tell material type
  virtual auto MaterialMaterialType() const -> MaterialType override
  {
    return MaterialType::kSpecular;
  }


  // ---------------------------------------------------------------------------
  // Mirror private data
  // ---------------------------------------------------------------------------
 private:
  Float n;
};
*/

// ---------------------------------------------------------------------------
// Glass Material
// ---------------------------------------------------------------------------
class Glass : public Material
{
 public:
  Glass();
  Glass(const Vector3f& emission,
        const Vector3f& reflection,
        Float refraction);
  virtual ~Glass();

  Glass(const Glass& mat) = default;
  Glass(Glass&& mat)      = default;

  auto operator = (const Glass& mat) -> Glass& = default;
  auto operator = (Glass&& mat)      -> Glass& = default;


  // ---------------------------------------------------------------------------
  // Override public methods
  // ---------------------------------------------------------------------------
 public:
  // Sample next ray direction
  virtual auto SampleRay(const Vector3f& hitpoint,
                         const Vector3f& incoming,
                         const Vector3f& surface_normal,
                         Float*          pdf,
                         Vector3f*       brdf) const -> Ray override;

  virtual auto GetMaterialType() const -> Type override;

  // ---------------------------------------------------------------------------
  // Override private methods
  // ---------------------------------------------------------------------------
 private:
  // Compute PDF
  virtual auto PDF(const Vector3f& incoming,
                   const Vector3f& normal,
                   const Vector3f& next_ray_dir) const -> Float override;

  // Compute BRDF
  virtual auto BRDF(const Vector3f& incoming,
                    const Vector3f& outgoing,
                    const Vector3f& normal  ) const -> Vector3f override;

  // ---------------------------------------------------------------------------
  // Glass private data
  // ---------------------------------------------------------------------------
 private:
  Float index_of_refraction_;
};


class Light : public Material
{
 public:
  Light();
  Light(const Vector3f& emission,
        const Vector3f& reflectance);
  virtual ~Light();

  Light(const Light& mat) = default;
  Light(Light&& mat)      = default;

  auto operator = (const Light& mat) -> Light& = default;
  auto operator = (Light&& mat)      -> Light& = default;

  // ---------------------------------------------------------------------------
  // Override public methods
  // ---------------------------------------------------------------------------
 public:
  // Sample next ray direction
  virtual auto SampleRay(const Vector3f& hitpoint,
                         const Vector3f& incoming,
                         const Vector3f& surface_normal,
                         Float*          pdf,
                         Vector3f*       brdf) const -> Ray override;

  virtual auto GetMaterialType() const -> Type override;


  // ---------------------------------------------------------------------------
  // Override private methods
  // ---------------------------------------------------------------------------
 protected:
  // Compute PDF
  virtual auto PDF(const Vector3f& incoming,
                   const Vector3f& normal,
                   const Vector3f& next_ray_dir) const -> Float override
  {
    assert(true);
    return 0;
  }

  // Compute BRDF
  virtual auto BRDF(const Vector3f& incoming,
                    const Vector3f& outgoing,
                    const Vector3f& normal  ) const -> Vector3f override
  {
    assert(true);
    return Vector3f(0, 0, 0);
  }

};

}  // namespace niepce

#endif // _MATERIAL_H_
