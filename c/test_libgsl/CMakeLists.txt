cmake_minimum_required(VERSION 3.0)
project(test_libgsl C)

find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIRS})
add_executable(main.x main.c)
target_link_libraries(main.x ${GSL_LIBRARIES})
