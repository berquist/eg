cmake_minimum_required(VERSION 3.10)
project(autoconf_earthly
    VERSION 0.1
    LANGUAGES C)

set(_TARGET_NAME ${CMAKE_PROJECT_NAME}.x)
add_executable(${_TARGET_NAME} main.c)
unset(_TARGET_NAME)
