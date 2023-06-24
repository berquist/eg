#include <armadillo>

int main()
{

    size_t dim = 5;
    double fl = 0.567;

    arma::mat em = arma::eye<arma::mat>(dim, dim);
    em.print("em");

    // type is arma::SizeMat?
    // auto s = arma::size(em);
    // s.print("s");

    arma::mat em2 = arma::eye<arma::mat>(arma::size(em));
    em2.print("em2");

    arma::mat em3 = fl * arma::eye<arma::mat>(arma::size(em));
    em3.print("em3");

    return 0;

}
