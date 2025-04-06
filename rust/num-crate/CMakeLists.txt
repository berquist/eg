cmake_minimum_required(VERSION 3.10)
project(num-crate LANGUAGES C)

set(TARGET bind)
add_library(${TARGET} src/bind.c)
install(TARGETS ${TARGET} DESTINATION .)
unset(TARGET)
