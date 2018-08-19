cmake_minimum_required (VERSION 3.10)

# テストプロジェクト名
project (algebra_test)

add_compile_options("-msse4.1")

# GoogleTest を利用
find_package (GTest REQUIRED)
include (GoogleTest)

if (GTEST_FOUND)
  add_executable (${PROJECT_NAME}
    vector3f_test.cc
    test_fresnel.cc
    ../src/core/vector3f.cc
    ../src/bsdf/fresnel.cc)
  target_link_libraries (${PROJECT_NAME} GTest::GTest GTest::Main)
  include_directories (${PROJECT_SOURCE_DIR}/src ${GTEST_INCLUDE_DIRS})
  gtest_add_tests (TARGET ${PROJECT_NAME})
else()

endif ()
