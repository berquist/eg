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

    arma::mat tensor(3, 3);
    tensor(0, 0) = 71.96979730;
    tensor(0, 1) = -7.19617988;
    tensor(0, 2) = 1.01470321;
    tensor(1, 0) = -7.19617833;
    tensor(1, 1) = 65.74361807;
    tensor(1, 2) = -5.62003645;
    tensor(2, 0) = 1.01469269;
    tensor(2, 1) = -5.62002592;
    tensor(2, 2) = 65.05385723;

    // arma::cx_vec principal_components_cx;
    // arma::cx_mat orientation_cx;

    // arma::eig_gen(principal_components_cx, orientation_cx, tensor);
    // principal_components_cx.print("principal components (complex)");
    // orientation_cx.print("orientation (complex)");

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
