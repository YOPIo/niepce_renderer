cmake_minimum_required (VERSION 2.8)

# Create static library
add_library (Random STATIC
  xorshift.cc)
