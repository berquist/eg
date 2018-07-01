#include "consumer.h"

#include <iostream>

template <>
void consuming_function(
    TestClass<arma::vec> *testclass
    ) {

    std::cout << "testclass->dim_copy: " << testclass->dim_copy << std::endl;

    return;
}
