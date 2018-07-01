#include <armadillo>

int main() {

    const size_t dim = 6;
    arma::mat A(dim, dim, arma::fill::ones);
    A(arma::span(0, (dim / 2) - 1), arma::span(0, (dim / 2) - 1)).fill(-1.032e-310);
    A.print("A");
    arma::vec eigval = arma::eig_sym(A);
    eigval.print("eigval");
    arma::vec eigvalsqrt = arma::sqrt(eigval);
    // This has junk tiny (negative) values that need to be removed.
    eigvalsqrt.print("eigvalsqrt");

    const double thresh = 1.0e-15;
    // arma::uvec mask = arma::abs(eigval) < thresh;
    // mask.print("mask");
    // eigval(mask).zeros();
    arma::uvec mask = arma::find(arma::abs(eigval) < thresh);
    mask.print("mask");
    eigval(mask).zeros();
    eigval.print("eigval");
    arma::sqrt(eigval).print("eigvalsqrt");

    return 0;
}
