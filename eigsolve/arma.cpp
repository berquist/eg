#include <armadillo>
#include <iostream>

int main() {
    arma::mat33 m = {
        {-0.386087, 0.00813956,  0.0781361},
        {0.00813956,  -0.390147,  0.0986476},
        {0.0781361,  0.0986476,   0.776234}
    };
    arma::vec eigvals;
    arma::mat eigvecs;
    arma::eig_sym(eigvals, eigvecs, m);
    std::cout << m;
    std::cout << eigvals;
    std::cout << eigvecs;
    return 0;
}
