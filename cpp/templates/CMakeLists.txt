cmake_minimum_required(VERSION 3.0)
project(template_examples CXX)

set(SRC
    25187583
    25187583_single
    25200473
    25200473_arma
    decltype_examples
    type_traits_examples
)

foreach(file ${SRC})
    add_executable(${file}.x ${file}.cpp)
endforeach(file)
