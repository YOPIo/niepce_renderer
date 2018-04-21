cmake_minimum_required (VERSION 3.10)

# テストプロジェクト名
project (algebra_test)

# GoogleTest を利用
find_package (GTest REQUIRED)
include (GoogleTest)

if (GTEST_FOUND)
  add_executable (${PROJECT_NAME}
    vector2f_test.cc
    vector3f_test.cc
    vector4f_test.cc)
  target_link_libraries (${PROJECT_NAME} GTest::GTest GTest::Main)
  include_directories (${PROJECT_SOURCE_DIR}/src ${GTEST_INCLUDE_DIRS})
  gtest_add_tests (TARGET ${PROJECT_NAME})
else()

endif ()
