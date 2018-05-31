#include <armadillo>

int main() {

    const size_t dim = 3;

    arma::mat A(dim, dim, arma::fill::ones);
    A.print("A");
    arma::mat B = A;
    arma::vec b(dim);
    for (size_t i = 0; i < dim; i++)
        b(i) = (i + 2);
    b.print("b");

    // error: element-wise multiplication: incompatible matrix dimensions: 3x3 and 3x1
    // (A % b).print("A % b");

    // This seems silly but it's ok from a memory access standpoint.
    for (size_t j = 0; j < dim; j++)
        A.col(j) *= b(j);
    A.print("% (1)");

    // error: no match for ‘operator*=’ (operand types are ‘arma::subview_row<double>’ and ‘arma::vec {aka arma::Col<double>}’)
    // for (size_t i = 0; i < dim; i++)
    //     B.row(i) *= b;
    // error: element-wise multiplication: incompatible matrix dimensions: 1x3 and 3x1
    // for (size_t i = 0; i < dim; i++)
    //     B.row(i) = B.row(i) % b;
    // This is matrix multiplication!
    // B *= b;

    // order doesn't matter
    arma::mat C = B.each_row() % b.t();
    C.print("% (2)");

    return 0;
}
