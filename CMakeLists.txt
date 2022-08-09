cmake_minimum_required(VERSION 3.5)
project(equilibrium LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/out")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(GoogleTest)

conan_basic_setup(TARGETS)

add_library(equilibrium SHARED
	src/rbtree/base_rbtree.h
	src/rbtree/rbtree.h
)
target_link_libraries(equilibrium CONAN_PKG::fmt CONAN_PKG::ms-gsl)
target_compile_definitions(equilibrium PRIVATE EQUILIBRIUM_LIBRARY)
set_target_properties(equilibrium PROPERTIES LINKER_LANGUAGE CXX)

add_executable(test_rbtree tests/test_base_rbtree.cpp)
target_link_libraries(test_rbtree equilibrium CONAN_PKG::gtest)
gtest_discover_tests(test_rbtree)

add_executable(test_it_works tests/test_it_works.cpp)
target_link_libraries(test_it_works CONAN_PKG::gtest)
gtest_discover_tests(test_it_works)
