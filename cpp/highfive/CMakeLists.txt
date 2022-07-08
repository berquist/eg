cmake_minimum_required(VERSION 3.0)
project(highfive_examples C CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(HighFive REQUIRED)
find_package(Armadillo REQUIRED)

# add_subdirectory(libaview)
# blergh...
# include_directories(libaview)

add_library(highfive_common common.cpp)
target_link_libraries(highfive_common HighFive)

add_library(highfive_iface iface.cpp)
target_link_libraries(highfive_iface highfive_common)

add_executable(highfive_enum.x enum.cpp)
target_link_libraries(highfive_enum.x highfive_iface)

add_executable(highfive_compound.x compound.cpp)
target_link_libraries(highfive_compound.x highfive_iface ${ARMADILLO_LIBRARIES})

add_executable(highfive_enum_compound_auto.x enum_compound_auto.cpp)
target_link_libraries(highfive_enum_compound_auto.x highfive_iface)

add_executable(highfive_arma.x arma.cpp)
target_link_libraries(highfive_arma.x ${ARMADILLO_LIBRARIES} highfive_common)

add_executable(highfive_arma_chunking.x arma_chunking.cpp)
target_link_libraries(highfive_arma_chunking.x ${ARMADILLO_LIBRARIES} highfive_common)

# add_executable(highfive_aview.x aview.cpp)
# target_link_libraries(highfive_aview.x aview HighFive ${ARMADILLO_LIBRARIES})

# add_executable(highfive_eigen.x eigen.cpp)
# target_link_libraries(highfive_eigen.x HighFive)

# add_executable(highfive_stl.x stl.cpp)
# target_link_libraries(highfive_stl.x HighFive Armadillo)

add_executable(highfive_pod.x pod.cpp)
target_link_libraries(highfive_pod.x highfive_common)

enable_testing()
find_package(GTest)

add_executable(highfive_test_span.x test_span.cpp)
target_link_libraries(highfive_test_span.x ${GTEST_BOTH_LIBRARIES})
add_test(highfive_test_span highfive_test_span.x)
