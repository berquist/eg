cmake_minimum_required(VERSION 3.10)
project(EG_CPPCON LANGUAGES CXX)

add_executable(memory_safe_cpp.x memory_safe_cpp.cpp)
set_target_properties(memory_safe_cpp.x PROPERTIES CXX_STANDARD 14)
