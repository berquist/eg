cmake_minimum_required(VERSION 3.0)
project(INCLUDES Fortran)

set(SRC
    src/main.F
    )

set(TARGET_NAME include_example.x)
add_executable(${TARGET_NAME} ${SRC})
