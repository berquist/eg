#include <armadillo>

void pointer_fun(const double * charges, size_t natoms) {
    std::cout << "charges:" << std::endl;
    for (size_t i = 0; i < natoms; i++) {
        const double charge = charges[i];
        std::cout << " " << charge << std::endl;
    }
}

int main() {

    const size_t ncharges = 10;
    int * charges = new int[ncharges];
    for (size_t i = 0; i < ncharges; i++) {
        charges[i] = i;
    }
    arma::Col<int> icharges(charges, ncharges, false, true);
    icharges.print("icharges");
    arma::vec dcharges = arma::conv_to<arma::vec>::from(icharges);
    dcharges.print("dcharges");
    pointer_fun(dcharges.memptr(), dcharges.n_elem);
    for (size_t i = 0; i < dcharges.n_elem; i++) {
        // no bounds check
        dcharges[i] = i + (i / 10.0);
    }
    pointer_fun(dcharges.memptr(), dcharges.n_elem);
    delete[] charges;

    return 0;

}
