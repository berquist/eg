# cmake_minimum_required(VERSION 3.10)
# project(class_template_function_call LANGUAGES CXX)

# find_package(Armadillo REQUIRED)

# set(SRC
#     consumer.cpp
#     )

# add_library(example ${SRC})
# set(EXE_NAME class_template_function_call.x)
# add_executable(${EXE_NAME} main.cpp)
# target_link_libraries(${EXE_NAME} example)
# target_link_libraries(${EXE_NAME} ${ARMADILLO_LIBRARIES})

set(SRC
    consumer.cpp
    main.cpp
    )

add_executable(class_template_function_call.x ${SRC})
target_link_libraries(class_template_function_call.x ${ARMADILLO_LIBRARIES})
