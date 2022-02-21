cmake_minimum_required(VERSION 3.0)
project(template_examples C CXX)

find_package(Armadillo REQUIRED)

set(SRC
    6398890
    25200473_arma
    dependents
    fibonacci
    nested
    outer
    static_assert
    # string_join
    struct_traversal
    type_traits_examples
)

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
    set_target_properties(${file}.x PROPERTIES CXX_STANDARD 11)
    target_link_libraries(${file}.x ${ARMADILLO_LIBRARIES})
endforeach(file)

set(SRC_MULTI
    25187583
    25187583_single
    25200473
    25200473_single
    decltype_examples
)

foreach(file ${SRC_MULTI})
    add_executable(${file}_11.x ${file}.cpp)
    add_executable(${file}_17.x ${file}.cpp)
    set_target_properties(${file}_11.x PROPERTIES CXX_STANDARD 11)
    set_target_properties(${file}_17.x PROPERTIES CXX_STANDARD 17)
endforeach(file)

find_package(HighFive REQUIRED)
add_executable(highfive_dtype_11.x highfive_dtype.cpp)
add_executable(highfive_dtype_17.x highfive_dtype.cpp)
set_target_properties(highfive_dtype_11.x PROPERTIES CXX_STANDARD 11)
set_target_properties(highfive_dtype_17.x PROPERTIES CXX_STANDARD 17)
target_link_libraries(highfive_dtype_11.x HighFive)
target_link_libraries(highfive_dtype_17.x HighFive)
