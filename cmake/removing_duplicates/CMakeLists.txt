cmake_minimum_required(VERSION 3.8)
project(removing_duplicates CXX)

# CMake versions < 3.14 error when an undefined variable is passed to
# REMOVE_DUPLICATES.
macro(_remove_duplicates mylist)
  # message(STATUS "removing duplicates: ${${mylist}}")
  if(${mylist})
    list(REMOVE_DUPLICATES ${mylist})
  endif(${mylist})
endmacro(_remove_duplicates)

set(l1 "a;b;c;a;a;b;d;e;c")
set(l1_ref "a;b;c;d;e")
# message(STATUS "l1: ${l1}")
list(REMOVE_DUPLICATES l1)
message(STATUS "l1: ${l1}")

set(l1 "a;b;c;a;a;b;d;e;c")
_remove_duplicates(l1)
message(STATUS "l1: ${l1}")

list(REMOVE_DUPLICATES l2)
message(STATUS "l2: ${l2}")

_remove_duplicates(l3)
message(STATUS "l3: ${l3}")
