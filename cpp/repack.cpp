#include <cassert>
#include <armadillo>

void repack_matrix_to_vector_fast(arma::vec &v, const arma::mat &m)
{

    const size_t d1 = m.n_cols;
    const size_t d2 = m.n_rows;
    const size_t dv = d1 * d2;
    assert(v.n_elem == dv);

    size_t ia;
    for (size_t i = 0; i < d1; i++) {
        for (size_t a = 0; a < d2; a++) {
            ia = i*d2 + a;
            v(ia) = m(a, i);
        }
    }

    return;

}

void repack_matrix_to_vector(arma::vec &v, const arma::mat &m)
{

    const size_t d1 = m.n_rows;
    const size_t d2 = m.n_cols;
    const size_t dv = d1 * d2;
    assert(v.n_elem == dv);

    size_t ia;
    for (size_t i = 0; i < d1; i++) {
        for (size_t a = 0; a < d2; a++) {
            ia = i*d2 + a;
            v(ia) = m(i, a);
        }
    }

    return;

}

void repack_vector_to_matrix(arma::mat &m, const arma::vec &v)
{

    const size_t d1 = m.n_rows;
    const size_t d2 = m.n_cols;
    const size_t dv = d1 * d2;
    assert(v.n_elem == dv);

    size_t ia;
    for (size_t i = 0; i < d1; i++) {
        for (size_t a = 0; a < d2; a++) {
            ia = i*d2 + a;
            m(i, a) = v(ia);
        }
    }

    return;
}

int main() {

    const size_t d1 = 3;
    const size_t d2 = 4;

    arma::mat m(d1, d2);
    arma::vec v(d1 * d2);

    size_t ia;
    for (size_t i = 0; i < d1; i++) {
        for (size_t a = 0; a < d2; a++) {
            ia = i*d2 + a;
            m(i, a) = ia;
        }
    }

    m.print("m");
    repack_matrix_to_vector(v, m);
    v.print("v");

    arma::vec v2(d1 * d2);
    arma::mat m2 = m.t();
    repack_matrix_to_vector_fast(v2, m2);
    m2.print("m2");
    v2.print("v2");

    arma::vec mv = arma::vectorise(m);
    mv.print("vectorise(m)");
    // otherwise we get a rowvec!
    arma::vec mv1 = arma::vectorise(m, 1).t();
    mv1.print("vectorise(m, 1)");

    arma::vec mv2 = arma::vectorise(m2);
    mv2.print("vectorise(m2)");

    return 0;
}
