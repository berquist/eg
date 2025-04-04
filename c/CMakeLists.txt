cmake_minimum_required(VERSION 3.10)
project(c_examples LANGUAGES C)

find_package(GSL)
find_package(HDF5)

if(HDF5_FOUND)
    add_subdirectory(hdf5)
endif(HDF5_FOUND)
if(GSL_FOUND)
    add_subdirectory(test_libgsl)
endif(GSL_FOUND)

add_executable(complex_example_99.x complex_example_99.c)
set_target_properties(complex_example_99.x
    PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED TRUE)
target_link_libraries(complex_example_99.x m)

add_executable(numeric_casts.x numeric_casts.c)
