cmake_minimum_required(VERSION 3.10)
project(TEST_UNIQUEPTR LANGUAGES CXX)

set(TGT smart_ptr_main.x)
add_executable(${TGT}
    main.cpp)
target_compile_features(${TGT} PRIVATE cxx_std_14)

set(SRC
    smart_ptr_destructors
    smart_ptr_push_pop
    smart_ptr_push_pop_2
    # smart_ptr_temporary
    )

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
    set_target_properties(${file}.x PROPERTIES CXX_STANDARD 11)
endforeach()
