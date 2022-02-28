cmake_minimum_required(VERSION 3.8)
project(LIBINT2 CXX)

# find_package(Libint2 REQUIRED)

set(SRC libint2.cpp)
set(TGT libint2.x)

add_executable(${TGT} ${SRC})
target_link_libraries(${TGT} Libint2::int2)
