cmake_minimum_required(VERSION 3.10)
project(INTERFACES LANGUAGES C CXX Fortran)

set(SRC
    src/impl.cpp
    src/fileman_interface.f90
    src/fileman_calls.f90
    )

add_executable(interface_example.x ${SRC})
