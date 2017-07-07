#include "class_template.h"

namespace foo {

void consumer(TestClass<arma::vec> *tc_vec) {
    tc_vec->print();
    return;
}

} // namespace foo
