#include <armadillo>

// on laptop:
// size_t      <- long unsigned int
// arma::uword <- long long unsigned int
typedef arma::uword index_t;

int main() {

    const size_t n_rows = 10;
    const size_t n_cols = 4;
    const size_t n_slices = 2;
    const int imin = -3;
    const int imax = 10;

    const arma::Cube<int> R = arma::randi<arma::Cube<int>>(n_rows, n_cols, n_slices, arma::distr_param(imin, imax));

    R.print("R");

    index_t _indices[5] = {2, 3, 4, 8, 9};
    const arma::uvec indices = arma::uvec(&_indices[0], 5, true);
    indices.print("indices");

    return 0;
}
