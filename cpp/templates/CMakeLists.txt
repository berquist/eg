cmake_minimum_required(VERSION 3.0)
project(template_examples C CXX)

set(SRC
    25200473_arma
    type_traits_examples
)

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
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