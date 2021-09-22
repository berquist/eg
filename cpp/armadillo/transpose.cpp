#include <armadillo>

int main() {
    arma::mat m(3, 4, arma::fill::randn);
    arma::cx_mat cm(3, 4, arma::fill::randn);

    m.print("m");
    m.t().print("m.t");
    // this *does* work, just passes through to regular transpose
    m.st().print("m.st");

    cm.print("cm");
    cm.t().print("cm.t");
    cm.st().print("cm.st");

    return 0;
}
