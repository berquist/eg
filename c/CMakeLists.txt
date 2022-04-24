cmake_minimum_required(VERSION 3.0)
project(c_examples C)

find_package(GSL)
find_package(HDF5)

if(HDF5_FOUND)
    add_subdirectory(hdf5)
endif(HDF5_FOUND)
if(GSL_FOUND)
    add_subdirectory(test_libgsl)
endif(GSL_FOUND)
