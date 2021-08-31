cmake_minimum_required(VERSION 3.0)
project(h5cpp_examples C CXX)

find_package(h5cpp)
find_package(Armadillo)

add_executable(attribute_creation.x attribute_creation.cpp)
target_link_libraries(attribute_creation.x h5cpp)

add_executable(arma.x
    interface.cpp arma.cpp)
target_link_libraries(arma.x h5cpp ${ARMADILLO_LIBRARIES})

add_executable(h5cpp_string.x h5cpp_string.cpp)
target_link_libraries(h5cpp_string.x h5cpp)
