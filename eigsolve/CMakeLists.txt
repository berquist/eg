cmake_minimum_required(VERSION 3.10)
project(eigsolve LANGUAGES CXX)

find_package(Armadillo REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(arma.x arma.cpp)
target_include_directories(arma.x PRIVATE ${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(arma.x ${ARMADILLO_LIBRARIES})
add_executable(eigen.x eigen.cpp)
target_link_libraries(eigen.x Eigen3::Eigen)

install(TARGETS arma.x)
install(TARGETS eigen.x)
