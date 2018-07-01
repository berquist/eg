#include "consumer.h"

#include <iostream>

// template <>
// void consuming_function(
//     TestClass<arma::vec> *testclass
//     ) {

//     std::cout << "testclass->dim_copy: " << testclass->dim_copy << std::endl;

//     return;
// }

// template <typename T>
// void consuming_function(
//     TestClass<T> *testclass
//     ) {

//     std::cout << "testclass->dim_copy: " << testclass->dim_copy << std::endl;

//     return;
// }

// Explicit specialization.
// template void consuming_function<arma::vec>(TestClass<arma::vec> *testclass);

void consuming_function_2(
    TestClass<arma::vec> *testclass
    ) {

    std::cout << 17 << std::endl;

    return;
}
