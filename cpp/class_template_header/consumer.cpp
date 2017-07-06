#include "consumer.h"

#include <iostream>

// template <>
// void consuming_function(
//     TestClass<arma::vec> *testclass
//     ) {

//     std::cout << "testclass->dim_copy: " << testclass->dim_copy << std::endl;

//     return;
// }

template <typename T>
void consuming_function(
    TestClass<T> *testclass
    ) {

    std::cout << "testclass->dim_copy: " << testclass->dim_copy << std::endl;

    return;
}

consuming_function(TestClass<arma::vec> *testclass);
