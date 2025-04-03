cmake_minimum_required(VERSION 3.10)
# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
project(linking_against_c VERSION 0.1)

add_library(mylib SHARED src/mylib.c)
set_target_properties(mylib
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    )
set_target_properties(mylib PROPERTIES PUBLIC_HEADER include/mylib.h)
