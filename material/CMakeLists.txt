cmake_minimum_required(VERSION 3.1)

add_library(material STATIC
                     material.cc
                     lambert.cc
                     phong.cc
                     light.cc
                     material_manager.cc
)
