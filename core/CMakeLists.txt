cmake_minimum_required(VERSION 3.1)

add_library(core STATIC
                 hit_record.cc
                 logger.cc
                 path.cc
                 ray.cc
                 scene.cc
                 size_vector.cc
                 size.cc
                 render_manager.cc
)

