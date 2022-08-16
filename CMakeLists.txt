cmake_minimum_required(VERSION 3.19)
project(equilibrium)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/out")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EQ_BUILD_TESTS "yes")

add_library(equilibrium src/rbtree.c)
target_include_directories(equilibrium PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(DEFINED EQ_BUILD_TESTS)
	message(STATUS "Building tests ? " ${EQ_BUILD_TESTS})
  	if("${EQ_BUILD_TESTS}" STREQUAL "yes")
		enable_testing()
		add_subdirectory(tests)
  	endif()
endif()
