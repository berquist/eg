cmake_minimum_required(VERSION 3.20)
project(ex_gif-h CXX)

if(NOT TARGET gif-h)
    add_library(gif-h INTERFACE IMPORTED)
    set(_DIR "${CMAKE_CURRENT_SOURCE_DIR}/foo/bar/baz")
    target_include_directories(gif-h INTERFACE "${_DIR}/gif-h")
    unset(_DIR)
endif(NOT TARGET gif-h)

add_executable(gif-h-demo.x gif-h-demo.cpp)
target_link_libraries(gif-h-demo.x PRIVATE gif-h)
