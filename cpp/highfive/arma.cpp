#include <highfive/H5Easy.hpp>
#include "highfive_arma.hpp"

using namespace HighFive;

int main() {
    const std::string filename("arma.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    const size_t dim_big = 20;
    const arma::Col<double> rv1(dim_big, arma::fill::randn);
    const arma::mat rm1(dim_big, dim_big, arma::fill::randn);
    const arma::Cube<double> rc1(2, 3, 4, arma::fill::randn);
    const arma::Cube<arma::sword> rc2(2, 3, 4, arma::fill::zeros);

    rv1.print("rv1");
    auto dset_rv1 = file.createDataSet("rv1", rv1);
    arma::Col<double> rv1_read;
    rv1_read.print("rv1_read (before)");
    dset_rv1.read(rv1_read);
    rv1_read.print("rv1_read (after)");

    return 0;
}
