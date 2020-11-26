cmake_minimum_required(VERSION 3.1)
project(TEST_UNIQUEPTR CXX)

set(TGT main.x)
add_executable(${TGT}
    main.cpp)
target_compile_features(${TGT} PRIVATE cxx_std_14)
