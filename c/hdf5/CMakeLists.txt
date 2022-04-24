cmake_minimum_required(VERSION 3.0)
project(hdf5_examples C)

find_package(HDF5 REQUIRED)

add_executable(hdf5_example.x main.c)
target_link_libraries(hdf5_example.x ${HDF5_LIBRARIES})
