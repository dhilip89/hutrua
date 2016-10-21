cmake_minimum_required (VERSION 3.1)

project (hutrua)

set (CMAKE_CXX_STANDARD 11)

add_subdirectory(third_party)
include_directories(${libpng_SOURCE_DIR})

set(HUTRUA_SRCS
  hutrua.cpp
  HtImage.cpp
  HtCanvas.cpp
  HtBitmap.cpp
)

add_library(hutrua ${HUTRUA_SRCS})
target_link_libraries (hutrua libpng zlib)

add_executable(test_hutrua test.cpp)
target_link_libraries (test_hutrua hutrua)
