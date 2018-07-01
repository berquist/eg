#include <armadillo>
#include <cassert>
#include <cstdio>
#include <iostream>

void alter(arma::vec &vref) {

    vref *= -4.0;

    return;
}

int main() {

    // arma::arma_rng::set_seed_random();
    arma::arma_rng::set_seed(5489);

    size_t lr = 4;
    size_t lc = 3;

    arma::mat Am(lr, lc, arma::fill::randn);

    Am.print("Am");

    arma::vec ones(lr, arma::fill::ones);
    Am.col(2) = ones;

    Am.print("Am");

    arma::vec wrapper(Am.colptr(2), lr, false, false);
    wrapper *= -4.0;

    Am.print("Am");

    alter(wrapper);

    Am.print("Am");

    return 0;

}
