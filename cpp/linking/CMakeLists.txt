cmake_minimum_required(VERSION 3.18)
project(linking_examples CXX)

include(CheckLinkerFlag)
check_linker_flag(CXX --no-undefined NO_UNDEFINED)
check_linker_flag(CXX -Wl,--no-undefined NO_UNDEFINED_PREFIX)
message(STATUS "NO_UNDEFINED: ${NO_UNDEFINED}")
message(STATUS "NO_UNDEFINED_PREFIX: ${NO_UNDEFINED_PREFIX}")

message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined" ${CMAKE_SHARED_LINKER_FLAGS})
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")

# [1/1] Linking CXX shared library linking/libms.so
# FAILED: linking/libms.so
# : && /usr/bin/c++ -fPIC   -Wl,--no-undefined -shared -Wl,-soname,libms.so -o linking/libms.so linking/CMakeFiles/ms.dir/missing_symbols.cpp.o   && :
# /usr/bin/ld: linking/CMakeFiles/ms.dir/missing_symbols.cpp.o: in function `baz()':
# missing_symbols.cpp:(.text+0x14): undefined reference to `foo()'
# collect2: error: ld returned 1 exit status
# ninja: build stopped: subcommand failed.
#
# add_library(ms SHARED missing_symbols.cpp)

add_executable(6116188.x 6116188_a.cpp 6116188_b.cpp)
set_target_properties(6116188.x PROPERTIES CXX_STANDARD 11)

# https://stackoverflow.com/q/2894957

add_library(static_data_1 STATIC static_data_1.cpp)
add_library(static_data_2 STATIC static_data_2.cpp)
# add_executable(static_data.x static_data_main.cpp)
# target_link_libraries(static_data.x static_data_1 static_data_2)
#add_executable(static_data.x static_data_main.cpp static_data_2.cpp)

# add_library(2894957_1 STATIC 2894957_1.cpp)
# add_executable(2894957.x 2894957_main.cpp)
# target_link_libraries(2894957.x 2894957_1)
