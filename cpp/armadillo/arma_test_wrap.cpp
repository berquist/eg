#include <armadillo>
#include <cassert>
#include <iostream>

void alter(arma::vec &vref) {
    vref *= -4.0;
}

int main() {
    // arma::arma_rng::set_seed_random();
    arma::arma_rng::set_seed(5489);

    const size_t lr = 4;
    const size_t lc = 3;
    const size_t ls = 2;

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

    arma::cube cr(lr, lc, ls, arma::fill::randn);
    cr.print("cr");
    arma::vec cr_wrap(cr.memptr(), cr.n_elem, false, true);
    cr_wrap.print("cr_wrap");

    return 0;
}
