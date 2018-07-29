cmake_minimum_required (VERSION 2.8)

add_library (Bsdf STATIC
  bxdf.cc
  bsdf.cc
  bsdf_record.cc
  lambert.cc
  oren_nayar.cc
  # beckmann_distribution.cc
  trowbridge_reitz.cc
  fresnel.cc
  microfacet_reflection.cc
  specular_reflection.cc)
