cmake_minimum_required(VERSION 3.0)
project(highfive_examples C CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(HighFive REQUIRED)
find_package(Armadillo REQUIRED)

# add_subdirectory(libaview)
# blergh...
# include_directories(libaview)

add_library(common common.cpp)
target_link_libraries(common HighFive)

add_executable(highfive_enum.x enum.cpp)
target_link_libraries(highfive_enum.x common)

add_executable(highfive_compound.x compound.cpp)
target_link_libraries(highfive_compound.x common)

add_executable(arma_highfive.x arma.cpp)
target_link_libraries(arma_highfive.x ${ARMADILLO_LIBRARIES} common)

# add_executable(aview.x aview.cpp)
# target_link_libraries(aview.x aview HighFive ${ARMADILLO_LIBRARIES})

# add_executable(eigen.x eigen.cpp)
# target_link_libraries(eigen.x HighFive)

# add_executable(stl.x stl.cpp)
# target_link_libraries(stl.x HighFive Armadillo)

add_executable(pod.x pod.cpp)
target_link_libraries(pod.x common)

enable_testing()
find_package(GTest)

add_executable(test_span.x test_span.cpp)
target_link_libraries(test_span.x ${GTEST_BOTH_LIBRARIES})
add_test(test_span test_span.x)
