cmake_minimum_required(VERSION 3.0)
project(eg C CXX)

set(SRC
    # complex_example
    destructor_chain
    int_size_t_comparison
    return_const_reference
    stl
    string_conversion
    # test_function
    test_getenv
    test_openmp_2
    test_openmp_copyprivate
    test_openmp
    # test_template_inheritance
    )

message(STATUS "SRC: ${SRC}")

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
endforeach(file)

add_executable(alphanum.x alphanum.cpp)
set_target_properties(alphanum.x PROPERTIES CXX_STANDARD 11)

find_package(Armadillo)
find_package(cereal)
find_package(HDF5 COMPONENTS C CXX)
find_package(h5cpp)
find_package(HighFive)
# FIXME blergh
# include("/usr/lib/cmake/libint2/FindLibint2.cmake")
find_package(Libint2)

if(${ARMADILLO_FOUND})
    add_subdirectory(armadillo)
endif(${ARMADILLO_FOUND})
# TODO Doesn't have CMakeLists.txt yet
# add_subdirectory(arrayfire_playground)
# TODO Doesn't have CMakeLists.txt yet
# add_subdirectory(boost)
if(${ARMADILLO_FOUND})
    add_subdirectory(capi)
endif(${ARMADILLO_FOUND})
if(${cereal_FOUND})
    add_subdirectory(cereal)
endif(${cereal_FOUND})
# TODO ???
# add_subdirectory(eigen)
if(${ARMADILLO_FOUND})
    if(TARGET h5cpp)
        add_subdirectory(h5cpp)
    endif(TARGET h5cpp)
endif(${ARMADILLO_FOUND})
# TODO ???
# add_subdirectory(H5CPP)
if(TARGET hdf5::hdf5_cpp)
    add_subdirectory(hdf5)
endif(TARGET hdf5::hdf5_cpp)
if(${ARMADILLO_FOUND})
    if(TARGET HighFive)
        add_subdirectory(highfive)
    endif(TARGET HighFive)
endif(${ARMADILLO_FOUND})
if(${LIBINT2_FOUND})
    add_subdirectory(libint2)
endif(${LIBINT2_FOUND})
add_subdirectory(linking)
add_subdirectory(rtti)
add_subdirectory(seeandsay)
add_subdirectory(unique_ptr)
if(${ARMADILLO_FOUND})
    add_subdirectory(templates)
    # something is broken
    # add_subdirectory(transmute)
endif(${ARMADILLO_FOUND})
# TODO directory naming problem
# add_subdirectory(unique_ptr)
# TODO something is broken
# add_subdirectory(xtensor)
