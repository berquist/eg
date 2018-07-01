cmake_minimum_required(VERSION 3.11)
project(eg CXX)

set(SRC
    int_size_t_comparison
    pointer_cast
    repack
    string_conversion
    )

find_package(Armadillo)

set(SRC_ARMA
    arma_aniso
    arma_diag
    arma_fancy_indexing
    arma_sum
    )

message(STATUS "SRC: ${SRC}")

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
endforeach(file)

if(${ARMADILLO_FOUND})
    message(STATUS "SRC_ARMA: ${SRC_ARMA}")
    foreach(file ${SRC_ARMA})
        add_executable(${file}.x ${file}.cpp)
        target_link_libraries(${file}.x ${ARMADILLO_LIBRARIES})
    endforeach(file)
endif()
