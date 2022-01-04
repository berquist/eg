#include "nested.hpp"
#include <armadillo>

template<typename T>
void myouterfunc(const T &ovalue) {
    myinnerfunc(ovalue);
}

int main() {
    arma::cube c(2, 2, 2, arma::fill::randn);
    myouterfunc(c);
    return 0;
}
