# message(STATUS "in eigen")
# message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")

find_package(Eigen3)

# https://stackoverflow.com/a/13703725/3249688
add_executable(simple_first_program.x simple_first_program/simple_first_program.cpp)
add_executable(tensor_declaration.x tensor_declaration/tensor_declaration.cpp)

target_include_directories(simple_first_program.x PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(tensor_declaration.x PRIVATE ${EIGEN3_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR}/unsupported)
