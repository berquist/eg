cmake_minimum_required(VERSION 3.8)
project(test_external_project CXX)

# strongly adapted from
# https://github.com/charlesnicholson/cmake-external-project-test/blob/e7bd116f027e8353ac78355450877619bdfbe0a4/CMakeLists.txt

include(ExternalProject)

# An example of a Makefile-based non-CMake project.

set(LIBBOYS_ROOT ${CMAKE_BINARY_DIR}/thirdparty/micb25_libboys)
ExternalProject_Add(micb25_libboys_external
    PREFIX ${LIBBOYS_ROOT}
    GIT_REPOSITORY https://github.com/micb25/libboys.git
    GIT_TAG master
    GIT_PROGRESS 1
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make
    INSTALL_COMMAND ""
    # The Makefile is hardcoded to produced a shared library, so this is ok.
    BUILD_BYPRODUCTS ${LIBBOYS_ROOT}/src/micb25_libboys_external/libboys.so
    )
add_library(boys SHARED IMPORTED)
set_target_properties(boys PROPERTIES
    IMPORTED_LOCATION ${LIBBOYS_ROOT}/src/micb25_libboys_external/libboys.so)

# The same project, but with a bare minimum CMake setup.

# set(LIBBOYS_FORK_ROOT ${CMAKE_BINARY_DIR}/thirdparty/micb25_libboys_fork)
# ExternalProject_Add(micb25_libboys_fork_external
#     PREFIX ${LIBBOYS_FORK_ROOT}
#     GIT_REPOSITORY https://github.com/berquist/libboys.git
#     GIT_TAG ce5eaaaa7ac49973523791b4487974af33e5244f
#     GIT_PROGRESS 1
#     CMAKE_ARGS -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
#                -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)

# find_library(BLAS REQUIRED)
set(LIBPT_ROOT ${CMAKE_BINARY_DIR}/thirdparty/libpt)
ExternalProject_Add(libpt_external
    PREFIX ${LIBPT_ROOT}
    GIT_REPOSITORY https://github.com/ilyak/libpt.git
    GIT_TAG master
    GIT_PROGRESS 1
    INSTALL_COMMAND ""
    CMAKE_ARGS -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
    # This is less ok
    BUILD_BYPRODUCTS ${LIBPT_ROOT}/src/libpt_external-build/src/libpt.so)
# add_library(pt SHARED IMPORTED)
# set_target_properties(pt PROPERTIES
#     IMPORTED_LOCATION ${LIBPT_ROOT}/src/libpt_external-build/src/libpt.so
#     INTERFACE_LINK_LIBRARIES ${BLAS_LIBRARIES})

# set(LIBEFP_ROOT ${CMAKE_BINARY_DIR}/thirdparty/libefp)
# ExternalProject_Add(libefp_external
#     PREFIX ${LIBEFP_ROOT}
#     GIT_REPOSITORY https://github.com/ilyak/libefp.git
#     GIT_TAG master
#     GIT_PROGRESS 1
#     CMAKE_ARGS -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
#                -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)
# find_library(libefp
#     HINTS ${LIBEFP_ROOT}
#     REQUIRED
#     NO_DEFAULT_PATH)

# set(LIBECPINT_ROOT ${CMAKE_BINARY_DIR}/thirdparty/libecpint)
# ExternalProject_Add(libecpint_external
#     PREFIX ${LIBECPINT_ROOT}
#     GIT_REPOSITORY https://github.com/robashaw/libecpint.git
#     GIT_TAG master
#     GIT_PROGRESS 1
#     CMAKE_ARGS -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
#                -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
#                -DLIBECPINT_USE_PUGIXML=OFF
#                -DLIBECPINT_BUILD_TESTS=OFF)

add_executable(example.x main.cpp)
add_dependencies(example.x micb25_libboys_external)
target_link_libraries(example.x boys)
