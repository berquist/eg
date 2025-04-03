project(EG_DOXYGEN LANGUAGES CXX)
cmake_minimum_required(VERSION 3.10)

find_package(Doxygen 1.9 REQUIRED)

add_executable(alphanum_test.x alphanum_test.C)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
    "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
add_custom_target(alphanum_docs
    "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    COMMENT "Doxygen documentation" VERBATIM)
