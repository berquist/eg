cmake_minimum_required(VERSION 3.11)
project(eg CXX)

set(SRC
    int_size_t_comparison
    string_conversion
    )

message(STATUS "SRC: ${SRC}")

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
endforeach(file)

add_subdirectory(armadillo)
add_subdirectory(eigen)
