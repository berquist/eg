cmake_minimum_required(VERSION 3.2)
project(test_external_project Fortran)

# strongly adapted from
# https://github.com/charlesnicholson/cmake-external-project-test/blob/e7bd116f027e8353ac78355450877619bdfbe0a4/CMakeLists.txt

include(ExternalProject)

set(LIBBOYS_ROOT ${CMAKE_BINARY_DIR}/thirdparty/micb25_libboys)

ExternalProject_Add(micb25_libboys
    PREFIX ${LIBBOYS_ROOT}
    GIT_REPOSITORY "https://github.com/berquist/libboys.git"
    GIT_TAG "ce5eaaaa7ac49973523791b4487974af33e5244f"
    # STAMP_DIR "${LIBBOYS_ROOT}"
    BINARY_DIR ${LIBBOYS_ROOT}
    SOURCE_DIR ${LIBBOYS_ROOT}
    # INSTALL_DIR "${LIBBOYS_ROOT}/lib"
    # CONFIGURE_COMMAND ""
    BUILD_COMMAND make
    # BUILD_BYPRODUCTS "${LIBBOYS_ROOT}/libboys.so"
    # BUILD_ALWAYS 1
    )

# set(GTEST_ROOT ${CMAKE_BINARY_DIR}/thirdparty/gtest)
# ExternalProject_Add(gtest
#     PREFIX ${GTEST_ROOT}
#     GIT_REPOSITORY "https://github.com/google/googletest.git"
#     TIMEOUT 20
#     GIT_BRANCH main)
