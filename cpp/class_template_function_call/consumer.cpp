#include "class_template.h"

void consumer(TestClass<arma::vec> *tc_vec) {
    tc_vec->print();
    return;
}
