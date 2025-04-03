cmake_minimum_required(VERSION 3.10)
project(rtti_examples LANGUAGES CXX)

set(SRC
    rtti_example
    write_typeid
)

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
endforeach(file)
