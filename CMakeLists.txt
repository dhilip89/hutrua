cmake_minimum_required (VERSION 2.8)

project (hutrua)

# need cmake 3.1
#set (CMAKE_CXX_STANDARD 11)

add_library(hutrua hutrua.cpp)

add_executable(test_hutrua test.cpp)
target_link_libraries (test_hutrua hutrua)