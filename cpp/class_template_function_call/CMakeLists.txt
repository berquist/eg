cmake_minimum_required(VERSION 3.8)
project(class_template_function_call CXX)

find_package(Armadillo REQUIRED)

set(SRC
    consumer.cpp
    )

add_library(example ${SRC})
set(EXE_NAME class_template_function_call.x)
add_executable(${EXE_NAME} main.cpp)
target_link_libraries(${EXE_NAME} example)
target_link_libraries(${EXE_NAME} ${ARMADILLO_LIBRARIES})
