#include <armadillo>

int main() {
    arma::mat m_orig(3, 6, arma::fill::randu);
    m_orig.print("m_orig");

    arma::mat m_row = m_orig.row(2);
    m_row.print("m_row");
    m_row.reshape(3, 2);
    m_row.print("m_row");

    return 0;
}
