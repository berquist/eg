find_package(xtensor)

set(SRC_XTENSOR
    example_1
    fill_array_with_data
    time_rank4
    )

if(xtensor_FOUND)
    message(STATUS "xtensor_INCLUDE_DIRS: ${xtensor_INCLUDE_DIRS}")
    foreach(file ${SRC_XTENSOR})
        add_executable(${file}.x ${file}.cpp)
        target_include_directories(${file}.x PRIVATE ${xtensor_INCLUDE_DIRS})
    endforeach(file)
endif()
