#include <armadillo>

int main() {


    // To generate the (symmetric positive-definite) matrix:

    // const size_t dim = 5;
    // arma::mat S(dim, dim, arma::fill::randu);
    // S = 0.5 * (S + S.t());
    // S += dim * arma::eye(arma::size(S));
    // S.save("S.dat", arma::arma_ascii);

    // To load the pre-generated matrix:

    arma::mat S;
    S.load("S.dat");

    S.print("S");

    // arma::vec Lam_S_vec(dim);
    // arma::mat Lam_S_mat(dim, dim);
    // arma::mat L_S(dim, dim);
    arma::vec Lam_S_vec;
    arma::mat Lam_S_mat;
    arma::mat L_S;

    arma::eig_sym(Lam_S_vec, L_S, S);
    // What's wrong with this?
    // Lam_S_mat = Lam_S_vec * arma::eye<arma::mat>(Lam_S_vec.n_elem, Lam_S_vec.n_elem);
    Lam_S_mat = arma::diagmat(Lam_S_vec);
    arma::mat Lam_sqrt_inv = arma::sqrt(arma::inv(Lam_S_mat));
    arma::mat symm_orthog = L_S * Lam_sqrt_inv * L_S.t();

    L_S.print("L_S");
    Lam_S_vec.print("Lam_S_vec");
    Lam_S_mat.print("Lam_S_mat");
    Lam_sqrt_inv.print("Lam_sqrt_inv");
    symm_orthog.print("symm_orthog");

    // Demonstration that matrix operations require diagonalization,
    // operation on the eigenvalues, then back-transformation to the
    // original basis.
    arma::mat S_inv = arma::inv(S);
    arma::mat Lam_inv = arma::inv(Lam_S_mat);
    arma::mat S_inv_2 = L_S * Lam_inv * L_S.t();
    arma::mat S_pinv = arma::pinv(S);
    arma::mat S_inv_sympd = arma::inv_sympd(S);

    S_inv.print("S_inv");
    S_inv_2.print("S_inv_2");
    S_pinv.print("S_pinv");
    S_inv_sympd.print("S_inv_sympd");

    return 0;

}
