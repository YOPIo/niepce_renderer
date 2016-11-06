#include "material.h"

namespace niepce
{

Material::Material()
{}

Material::Material(const char* name,
                   const Rgb&  emission,
                   const Rgb&  reflectance) :
    name_(name),
    emission_(emission),
    reflectance_(reflectance)
{}

Material::~Material()
{}

auto Material::Name() const -> std::string
{
  return name_;
}

auto Material::Emission() const -> Rgb
{
  return emission_;
}

auto Material::Reflectance() const -> Rgb
{
  return reflectance_;
}

}
