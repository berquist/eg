cmake_minimum_required(VERSION 3.0)
project(eg CXX)

set(SRC
    int_size_t_comparison
    string_conversion
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

add_subdirectory(armadillo)
# add_subdirectory(arrayfire_playground)
# add_subdirectory(boost)
add_subdirectory(eigen)
add_subdirectory(H5CPP)
add_subdirectory(hdf5)
add_subdirectory(unique_ptr)
add_subdirectory(templates)
# add_subdirectory(xtensor)
