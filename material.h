#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vector3.h"
#include "ray.h"
#include "random.h"


// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
inline auto Reflect(const Vector3f& incoming,
             const Vector3f& normal) -> Vector3f
{
  return Normalize(incoming - normal * 2.0 * Dot(normal, incoming));
}


// ---------------------------------------------------------------------------
// Material
//  - Diffuse
//  - Specular
//  - Refraction
// ---------------------------------------------------------------------------
class Material
{
  // ---------------------------------------------------------------------------
  // Material types
  // ---------------------------------------------------------------------------
 public:
  enum Type
  {
    kDiffuse,
    kSpecular,
    kRefractance,
    kLight
  };


 public:
  Material()
  {}
  Material(const Vector3f& emission,
           const Vector3f& reflectance) :
      emission_(emission),
      reflectance_(reflectance)
  {}
  virtual ~Material()
  {};

  Material(const Material& mat) = default;
  Material(Material&& mat)      = default;

  auto operator = (const Material& mat) -> Material& = default;
  auto operator = (Material&& mat)      -> Material& = default;

  auto Emission()    -> Vector3f const { return emission_;    }
  auto Refrectance() -> Vector3f const { return reflectance_; };

  // ---------------------------------------------------------------------------
  // Override public methods
  // ---------------------------------------------------------------------------
  // Sample next ray direction
  virtual auto SampleRay(const Vector3f& hitpoint,
                         const Vector3f& incoming,
                         const Vector3f& surface_normal,
                         Float*          pdf,
                         Vector3f*       brdf) const -> Ray = 0;

  // Tell material type
  virtual auto MaterialType() const -> Type = 0;


  // ---------------------------------------------------------------------------
  // Override private methods
  // ---------------------------------------------------------------------------
  // Compute PDF
  virtual auto PDF(const Vector3f& incoming,
                   const Vector3f& normal,
                   const Vector3f& next_ray_dir) const -> Float = 0;

  // Compute BRDF
  virtual auto BRDF(const Vector3f& incoming,
                    const Vector3f& outgoing,
                    const Vector3f& normal  ) const -> Vector3f = 0;

  // ---------------------------------------------------------------------------
  // Material protected data
  // ---------------------------------------------------------------------------
 protected:
  Vector3f emission_;
  Vector3f reflectance_;
};


// ---------------------------------------------------------------------------
// Diffuse Material
// ---------------------------------------------------------------------------
class Diffuse : public Material
{
 public:
  Diffuse()
  {}
  Diffuse(const Vector3f& emission,
          const Vector3f& reflectance) :
      Material(emission, reflectance)
  {}
  virtual ~Diffuse()
  {}

  Diffuse(const Diffuse& mat) = default;
  Diffuse(Diffuse&& mat)      = default;

  auto operator = (const Diffuse& mat) -> Diffuse& = default;
  auto operator = (Diffuse&& mat)      -> Diffuse& = default;

  // ---------------------------------------------------------------------------
  // Override public methods
  // ---------------------------------------------------------------------------
 public:
  // Sample next ray direction
  virtual auto SampleRay(const Vector3f& hitpoint,
                         const Vector3f& incoming,
                         const Vector3f& surface_normal,
                         Float*          pdf,
                         Vector3f*       brdf) const -> Ray override
  {
    // Create orthonormal basis
    const Vector3f normal = Normalize(surface_normal);
    Vector3f tangent;
    if ( normal.x == std::min(normal.x, std::min(normal.y, normal.z)) )
    {
      tangent = Vector3f(0, -1.0 * normal.z, normal.y);
    }
    else if ( normal.y == std::min(normal.x, std::min(normal.y, normal.z)) )
    {
      tangent = Vector3f(-1.0 * normal.z, 0, normal.x);
    }
    else
    {
      tangent = Vector3f(-1.0 * normal.y, normal.x, 0);
    }
    tangent = Normalize(tangent);
    const Vector3f bitangent = Normalize( Cross(tangent, normal) );


    // Importance sampling
    const Float phi = XorShift::Next01() * 2.0 * kPi;
    const Float r2  = XorShift::Next01();
    const Float r2s = std::sqrt(r2);

    const Float tx = r2s * std::cos(phi);
    const Float ty = r2s * std::sin(phi);
    const Float tz = std::sqrt(1.0 - r2);

    const Vector3f next_dir = Normalize( tz * normal + tx * tangent + ty * bitangent );

    // Compute PDF
    *pdf = PDF(incoming, normal, next_dir);

    // Compute BRDF
    *brdf = BRDF(incoming, next_dir, normal);

    return Ray(hitpoint, next_dir);
  }

  // Tell material type
  virtual auto MaterialType() const -> Type override
  {
    return Type::kDiffuse;
  }


  // ---------------------------------------------------------------------------
  // Override private methods
  // ---------------------------------------------------------------------------
 private:
  // Compute PDF
  virtual auto PDF(const Vector3f& incoming,
                   const Vector3f& normal,
                   const Vector3f& next_ray_dir) const -> Float override
  {
    return Dot(normal, next_ray_dir) / kPi;
  }

  // Compute BRDF
  virtual auto BRDF(const Vector3f& incoming,
                    const Vector3f& outgoing,
                    const Vector3f& normal  ) const -> Vector3f override
  {
    return reflectance_ / kPi;
  }
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
  virtual auto MaterialType() const -> Type override
  {
    return Type::kSpecular;
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
  Glass()
  {}
  Glass(const Vector3f& emission,
        const Vector3f& reflection,
        Float refraction) :
      Material(emission, reflection),
      index_of_refraction_(refraction)
  {}
  virtual ~Glass()
  {}

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
                         Vector3f*       brdf) const -> Ray override
  {
    // Is ray come from inside or outside ?
    const Vector3f normal = Dot(incoming, surface_normal) < 0.0 ?
                            surface_normal : -1.0 * surface_normal;
    // True: from outside, False: from inside
    const bool is_into = Dot(normal, surface_normal) > 0.0 ? true : false;

    // Before computing refraction direction, check total reflection
    // Ray never refract if theta2 >= 90
    // Index of refraction in outside is one
    // Snell's law $ n1 * sin(theta1) = n2 * sin(theta2) $
    const Float n = is_into ?
                    1.0 / index_of_refraction_ : index_of_refraction_ / 1.0;
    const Float cos_theta2  = Dot(incoming, normal);
    const Float cos_squared = 1 - n * n * (1 - cos_theta2 * cos_theta2);

    // Compute reflection direction
    const Vector3f reflection_dir = Reflect(incoming, normal);

    // Total reflection
    if (cos_squared < 0.0)
    {
      // DELTA
      *pdf  = 1.0;
      // Compute BRDF value
      *brdf = BRDF(incoming, reflection_dir, normal);

      return Ray(hitpoint, reflection_dir);
    }

    // Compute refraction direction with snell's law
    const Vector3f refraction_dir = Normalize( n * incoming - (cos_theta2 * n + std::sqrt(cos_squared)) * normal );

    // Fresnel's law
    const Float cost1 = Dot(-1.0 * incoming, normal);
    const Float cost2 = std::sqrt(cos_squared);
    const Float r_parallel      = (n * cost1 - cost2) / (n * cost1 + cost2);
    const Float r_perpendicular = (cost1 - n * cost2) / (cost1 + n * cost2);

    // Radiance change when ray come into other material
    const Float factor = n * n;

    // 
    const Float Fr = 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);
    // 
    const Float Ft = (1.0 - Fr) * factor;


    // Dicide refraction or reflection with russian roulette
    const Float probability = Fr;

    if (XorShift::Next01() < probability)
    {
      // Reflection
      *pdf  = 1.0 * probability;
      *brdf = Fr * BRDF(incoming, reflection_dir, surface_normal);
      return Ray(hitpoint, reflection_dir);
    }
    else
    {
      // Refraction
      *pdf  = 1.0 * (1.0f - probability);
      *brdf = Ft * BRDF(incoming, refraction_dir, surface_normal);
      return Ray(hitpoint, refraction_dir);
    }
  }

  // Tell materila type
  virtual auto MaterialType() const -> Type override
  {
    return Type::kRefractance;
  }


  // ---------------------------------------------------------------------------
  // Override private methods
  // ---------------------------------------------------------------------------
 private:
  // Compute PDF
  virtual auto PDF(const Vector3f& incoming,
                   const Vector3f& normal,
                   const Vector3f& next_ray_dir) const -> Float override
  {
    return 0;
  }

  // Compute BRDF
  virtual auto BRDF(const Vector3f& incoming,
                    const Vector3f& outgoing,
                    const Vector3f& normal  ) const -> Vector3f override
  {
    return reflectance_ * 1.0 / Dot(normal, outgoing);
  }


  // ---------------------------------------------------------------------------
  // Glass private data
  // ---------------------------------------------------------------------------
 private:
  Float index_of_refraction_;
};


class Light : public Material
{
 public:
  Light() :
      Material( Vector3f(1, 1, 1),  // Emisstion
                Vector3f(0, 0, 0) ) // Reflectance
  {};
  Light(const Vector3f& emission,
        const Vector3f& reflectance) :
      Material(emission, reflectance)
  {}
  virtual ~Light()
  {};

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
                         Vector3f*       brdf) const -> Ray override
  {
    assert(true);
    return Ray();
  }

  // Tell material type
  virtual auto MaterialType() const -> Type override
  {
    return Type::kLight;
  }


  // ---------------------------------------------------------------------------
  // Override private methods
  // ---------------------------------------------------------------------------
 private:
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


#endif // _MATERIAL_H_
