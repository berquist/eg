cmake_minimum_required(VERSION 3.0)
project(H5CPP_examples CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Armadillo REQUIRED)
find_package(HDF5 REQUIRED COMPONENTS CXX)

include_directories("/home/eric/data/opt/apps/H5CPP/1.10.5-6/include")
include_directories("/home/eric/data/opt/apps/H5CPP/1.10.5-6/share/h5cpp/attributes")
# include("/home/eric/data/opt/apps/H5CPP/1.10.5-6/lib/cmake/h5cpp/h5cpp-config.cmake")

add_executable(main.x main.cpp)
target_link_libraries(main.x ${HDF5_CXX_LIBRARIES} ${ARMADILLO_LIBRARIES})
# target_compile_features(main.x PRIVATE cxx_std_17)
