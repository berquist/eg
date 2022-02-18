cmake_minimum_required(VERSION 3.0)
project(capi_examples C CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(Armadillo REQUIRED)

add_library(core core.cpp)

add_executable(capi_main.x main.c)
target_link_libraries(capi_main.x core)

# add_executable(capi_consumer_cpp.x capi_consumer_cpp.cpp)
# target_link_libraries(capi_consumer_cpp.x core)
