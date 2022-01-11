cmake_minimum_required(VERSION 3.0)
project(eg CXX)

set(SRC
    int_size_t_comparison
    return_const_reference
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
# add_subdirectory(cereal)
# add_subdirectory(eigen)
# add_subdirectory(h5cpp)
# add_subdirectory(H5CPP)
add_subdirectory(hdf5)
# add_subdirectory(highfive)
add_subdirectory(libint2)
add_subdirectory(rtti)
add_subdirectory(seeandsay)
add_subdirectory(unique_ptr)
add_subdirectory(templates)
# add_subdirectory(transmute)
# add_subdirectory(unique_ptr)
# add_subdirectory(xtensor)
