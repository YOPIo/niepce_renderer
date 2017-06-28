#include "material.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
inline auto Reflect(const Vector3f& incoming,
                    const Vector3f& normal) -> Vector3f
{
  return Normalize(incoming - normal * 2.0 * Dot(normal, incoming));
}


// ---------------------------------------------------------------------------
// Material constructors
// ---------------------------------------------------------------------------
Material::Material()
{}

Material::Material(const Vector3f& emission,
                   const Vector3f& reflectance) :
      emission_(emission),
      reflectance_(reflectance)
{}

Material::~Material()
{}

// ---------------------------------------------------------------------------
// Material public methods
// ---------------------------------------------------------------------------
auto Material::Emission() const -> Vector3f
{
  return emission_;
}

auto Material::Reflectance() const -> Vector3f
{
  return reflectance_;
}


// ---------------------------------------------------------------------------
// Lambert material
// ---------------------------------------------------------------------------
Lambert::Lambert () :
    Material ()
{}

Lambert::Lambert (const Vector3f& emission,
                  const Vector3f& reflectance) :
    Material (emission, reflectance)
{}

Lambert::~Lambert()
{}


// ---------------------------------------------------------------------------
// Lambert public override functions
// ---------------------------------------------------------------------------
auto Lambert::SampleRay(const Vector3f &hitpoint,
                        const Vector3f &incoming,
                        const Vector3f &surface_normal,
                        Float *pdf,
                        Vector3f *brdf) const -> Ray
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

  const Float tz  = XorShift::Next01();
  const Float phi = XorShift::Next01() * 2.0 * kPi;
  const Float k   = sqrt(1.0 - tz * tz);
  const Float tx  = k * cos(phi);
  const Float ty  = k * sin(phi);

  /*
  // Importance sampling
  const Float phi = XorShift::Next01() * 2.0 * kPi;
  const Float r2  = XorShift::Next01();
  const Float r2s = std::sqrt(r2);

  const Float tx = r2s * std::cos(phi);
  const Float ty = r2s * std::sin(phi);
  const Float tz = std::sqrt(1.0 - r2);
  */

  // const Vector3f next_dir = Normalize( tz * normal + tx * tangent + ty * bitangent );
  const Vector3f next_dir = Normalize( tz * normal + tx * tangent + ty * bitangent);

  // Compute PDF
  *pdf = PDF(incoming, normal, next_dir);

  // Compute BRDF
  *brdf = BRDF(incoming, next_dir, normal);

  return Ray(hitpoint, next_dir);
}


auto Lambert::GetMaterialType() const -> Type
{
  return Type::kLambert;
}

// ---------------------------------------------------------------------------
// Lambert protected override methods
// ---------------------------------------------------------------------------
auto Lambert::PDF(const Vector3f& incoming,
                   const Vector3f& normal,
                   const Vector3f& next_ray_dir) const -> Float
{
  return Dot(normal, next_ray_dir) / kPi;
}

auto Lambert::BRDF(const Vector3f &incoming,
                    const Vector3f &outgoing,
                    const Vector3f &normal  ) const -> Vector3f
{
  return reflectance_ / kPi;
}


// ---------------------------------------------------------------------------
// Glass material
// ---------------------------------------------------------------------------
Glass::Glass()
{}

Glass::Glass(const Vector3f& emission,
             const Vector3f& reflection,
             Float refraction) :
    Material(emission, reflection),
    index_of_refraction_(refraction)
{}

Glass::~Glass()
{}

// ---------------------------------------------------------------------------
// Glass public override methods
// ---------------------------------------------------------------------------
auto Glass::SampleRay(const Vector3f& hitpoint,
                      const Vector3f& incoming,
                      const Vector3f& surface_normal,
                      Float*          pdf,
                      Vector3f*       brdf) const -> Ray
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

auto Glass::GetMaterialType() const -> Type
{
  return Type::kGlass;
}


// ---------------------------------------------------------------------------
// Glass private override methods
// ---------------------------------------------------------------------------
auto Glass::PDF(const Vector3f& incoming,
                const Vector3f& normal,
                const Vector3f& next_ray_dir) const -> Float
{
  return 0;
}

auto Glass::BRDF(const Vector3f& incoming,
                 const Vector3f& outgoing,
                 const Vector3f& normal  ) const -> Vector3f
{
  // return reflectance_ * 1.0 / Dot(normal, outgoing);
  return reflectance_ / Dot(normal, outgoing);
}



// ---------------------------------------------------------------------------
// Light material
// ---------------------------------------------------------------------------
Light::Light()
{}

Light::Light(const Vector3f& emission,
             const Vector3f& reflectance) :
    Material(emission, reflectance)
{}

Light::~Light()
{}

auto Light::SampleRay(const Vector3f &hitpoint,
                      const Vector3f &incoming,
                      const Vector3f &surface_normal,
                      Float *pdf,
                      Vector3f *brdf) const -> Ray
{
  assert(true);
  return Ray();
}

auto Light::GetMaterialType() const -> Type
{
  return Type::kLight;
}


}  // namespace niepce
