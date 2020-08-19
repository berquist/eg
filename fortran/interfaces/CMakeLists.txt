cmake_minimum_required(VERSION 3.0)
project(INTERFACES C CXX Fortran)

set(SRC
    src/fileman_interface.f90
    src/fileman_calls.f90
    )

# include(FortranCInterface)
# FortranCInterface_HEADER("rdm_focas.h" MACRO_NAMESPACE "LIBRDM_FORTRAN_" SYMBOLS focas_data)

add_executable(interface_example.x ${SRC})
# set_target_properties(rdm2 PROPERTIES Fortran_FORMAT FREE CXX_STANDARD 11)
