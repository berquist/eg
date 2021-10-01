cmake_minimum_required(VERSION 3.0)
project(highfive_examples C CXX)

add_library(get_dims get_dims.cpp)

find_package(HighFive)
find_package(Armadillo)

add_executable(arma.x arma.cpp)
target_link_libraries(arma.x get_dims HighFive ${ARMADILLO_LIBRARIES})

add_subdirectory(libaview)
add_executable(aview.x aview.cpp)
# target_include_directories(aview.x PRIVATE ${LIBAVIEW_SOURCE_DIR})
target_link_libraries(aview.x get_dims aview HighFive ${ARMADILLO_LIBRARIES})

# add_executable(eigen.x eigen.cpp)
# target_link_libraries(eigen.x HighFive)

add_executable(stl.x stl.cpp)
target_link_libraries(stl.x get_dims HighFive)
