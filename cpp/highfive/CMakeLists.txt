cmake_minimum_required(VERSION 3.0)
project(highfive_examples C CXX)

find_package(HighFive)
find_package(Armadillo)

add_executable(arma.x arma.cpp)
target_link_libraries(arma.x HighFive ${ARMADILLO_LIBRARIES})
