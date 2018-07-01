#include <iostream>
#include <armadillo>
#include <cmath>

double calculate_anisotropy(const arma::mat &m) {

    const double iso = arma::mean(arma::eig_sym(m));
    double aniso = arma::accu(m % m);
    aniso = std::sqrt(std::abs(1.5*(aniso - (3.0*iso*iso))));

    return aniso;
}

int main() {

    arma::mat tensor(3, 3, arma::fill::zeros);

    tensor(0, 0) = 12;
    tensor(1, 1) = 12;
    tensor(2, 2) = -0;

    arma::vec principal_components;
    arma::mat orientation;

    arma::eig_sym(principal_components, orientation, tensor);

    principal_components.print("principal components (real)");
    orientation.print("orientation (real)");

    double isotropic = arma::mean(principal_components);
    std::cout << "isotropic  : " << isotropic << std::endl;
    double anisotropic = calculate_anisotropy(tensor);
    std::cout << "anisotropic: " << anisotropic << std::endl;

    return 0;
}
