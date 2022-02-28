cmake_minimum_required(VERSION 3.8)
project(CEREAL_EXAMPLES CXX)

find_package(cereal REQUIRED)

set(SRC cereal_main.cpp)
set(TGT cereal_main.x)

add_executable(${TGT} ${SRC})
