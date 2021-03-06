cmake_minimum_required (VERSION 3.1)

project (hutrua)

set (CMAKE_CXX_STANDARD 11)

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

add_subdirectory(third_party)
include_directories(${libpng_SOURCE_DIR})

set(HUTRUA_SRCS
  HtImage.cpp
  HtCanvas.cpp
  HtBitmap.cpp
)

add_library(hutrua ${HUTRUA_SRCS})
target_link_libraries (hutrua libpng zlib)

add_executable(test_hutrua test.cpp)
target_link_libraries (test_hutrua hutrua)
