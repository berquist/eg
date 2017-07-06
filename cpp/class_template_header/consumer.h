#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "class_template_header.h"

// template <typename T>
// void consuming_function(
//     TestClass<T> *testclass
//     );

template <typename T>
void consuming_function(
    TestClass<T> *testclass
    ) {

    std::cout << "testclass->dim_copy: " << testclass->dim_copy << std::endl;

    return;
}

#endif // CONSUMER_H_
