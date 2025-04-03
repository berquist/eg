cmake_minimum_required(VERSION 3.10)
project(test_libgsl LANGUAGES C)

find_package(GSL REQUIRED)

add_executable(gsl_example.x main.c)
target_link_libraries(gsl_example.x GSL::gsl)
