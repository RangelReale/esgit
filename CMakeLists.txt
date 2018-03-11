cmake_minimum_required(VERSION 3.0)
project(esgit)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

FIND_PACKAGE(LibGit2)
include_directories(${LIBGIT2_INCLUDE_DIRS})

include_directories(include)

add_subdirectory(src)
add_subdirectory(example)
