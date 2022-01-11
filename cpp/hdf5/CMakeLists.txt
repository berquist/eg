cmake_minimum_required(VERSION 3.0)
project(hdf5_examples CXX)

find_package(HDF5 REQUIRED COMPONENTS CXX)
add_executable(writedata.x writedata.cpp)
target_link_libraries(writedata.x ${HDF5_CXX_LIBRARIES})
