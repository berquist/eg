cmake_minimum_required(VERSION 3.10)
project(eg LANGUAGES C CXX)

set(SRC
    # complex_example
    destructor_chain
    int_size_t_comparison
    mod
    return_const_reference
    string_conversion
    # test_function
    test_getenv
    test_openmp_2
    test_openmp_copyprivate
    test_openmp
    # test_template_inheritance
    )

set(SRC_11
    alphanum
    stl
)

set(SRC_14
    test_lambda
)

message(STATUS "SRC: ${SRC}")
message(STATUS "SRC_11: ${SRC_11}")
message(STATUS "SRC_14: ${SRC_14}")

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
endforeach(file)

foreach(file ${SRC_11})
    add_executable(${file}.x ${file}.cpp)
    set_target_properties(${file}.x PROPERTIES CXX_STANDARD 11)
endforeach(file)

foreach(file ${SRC_14})
    add_executable(${file}.x ${file}.cpp)
    set_target_properties(${file}.x PROPERTIES CXX_STANDARD 14)
endforeach(file)

find_package(Armadillo)
find_package(cereal)
find_package(Doxygen 1.9)
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
add_subdirectory(cppcon)
if(${DOXYGEN_FOUND})
    add_subdirectory(doxygen)
endif(${DOXYGEN_FOUND})
# TODO ???
# add_subdirectory(eigen)
if(${ARMADILLO_FOUND})
    if(TARGET h5cpp)
        add_subdirectory(h5cpp_ess-dmsc)
    endif(TARGET h5cpp)
endif(${ARMADILLO_FOUND})
# TODO ???
# add_subdirectory(h5cpp_steven-vargas)
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
add_subdirectory(mat2d)
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
