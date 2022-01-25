cmake_minimum_required(VERSION 3.1)
project(TEST_UNIQUEPTR CXX)

set(TGT unique_ptr.x)
add_executable(${TGT}
    main.cpp)
target_compile_features(${TGT} PRIVATE cxx_std_14)

set(SRC
    destructors
    )

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
    set_target_properties(${file}.x PROPERTIES CXX_STANDARD 11)
endforeach()
