cmake_minimum_required(VERSION 3.10)
# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
project(mylib LANGUAGES C VERSION 0.1)

add_library(mylib SHARED mylib.c)
set_target_properties(mylib
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    )
set_target_properties(mylib PROPERTIES PUBLIC_HEADER mylib.h)
