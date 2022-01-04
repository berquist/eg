#include "nested.hpp"
#include <armadillo>

int main() {
    arma::cube c(2, 2, 2, arma::fill::randn);
    myfunc(c);
    return 0;
}
