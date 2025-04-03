cmake_minimum_required(VERSION 3.10)
project(CEREAL_EXAMPLES LANGUAGES CXX)

find_package(cereal REQUIRED)

set(SRC cereal_main.cpp)
set(TGT cereal_main.x)

add_executable(${TGT} ${SRC})
