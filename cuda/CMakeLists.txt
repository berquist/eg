# Adapted from
# https://developer.nvidia.com/blog/building-cuda-applications-cmake/

cmake_minimum_required(VERSION 3.0)
project(cuda_examples LANGUAGES CUDA)

add_executable(test_rand.x test_rand.cu)
set_property(TARGET test_rand.x PROPERTY CUDA_ARCHITECTURES OFF)
