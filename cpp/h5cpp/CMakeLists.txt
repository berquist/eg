cmake_minimum_required(VERSION 3.0)
project(h5cpp_examples C CXX)

find_package(h5cpp REQUIRED)
find_package(Armadillo REQUIRED)

add_executable(attribute_creation.x attribute_creation.cpp)
target_link_libraries(attribute_creation.x h5cpp)

add_executable(arma_h5cpp.x
    interface.cpp arma.cpp)
target_link_libraries(arma_h5cpp.x h5cpp ${ARMADILLO_LIBRARIES})

add_executable(arma_nointerface_h5cpp.x
    interface.cpp arma_nointerface.cpp)
target_link_libraries(arma_nointerface_h5cpp.x h5cpp ${ARMADILLO_LIBRARIES})

add_executable(h5cpp_string.x h5cpp_string.cpp)
target_link_libraries(h5cpp_string.x h5cpp)
