#include <armadillo>

template<typename T>
void elem_exp(arma::Col<T> &out, const arma::Col<T> &in) {
    out.set_size(arma::size(in));
    out = arma::exp(in);
}

extern "C" void elem_exp(double * out, double * in, size_t len) {
    arma::Col<double> aout(out, len, false, true);
    arma::Col<double> ain(in, len, false, true);
    elem_exp(aout, ain);
}
