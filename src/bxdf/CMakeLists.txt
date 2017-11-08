cmake_minimum_required (VERSION 2.8)

add_library(
  Bxdf STATIC
  bsdf.cc
  bsdf_utils.cc
  bxdf.cc
  fresnel.cc
  microfacet.cc
  lambert.cc
  specular.cc
)
