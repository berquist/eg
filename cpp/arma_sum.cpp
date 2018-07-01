#include <armadillo>

int main() {

    arma::cube c(3, 3, 5);
    for (size_t s = 0; s < c.n_slices; s++)
        c.slice(s).fill(s);

    c.print("c");

    arma::sum(c, 2).print("c sum 2");

    return 0;

}
