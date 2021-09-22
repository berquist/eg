#include <cassert>
#include <armadillo>

int main() {
    const std::string filename("transpose.h5");

    arma::mat m(3, 4, arma::fill::randn);
    arma::cx_mat cm(3, 4, arma::fill::randn);

    m.print("m");
    m.t().print("m.t");
    // this *does* work, just passes through to regular transpose
    m.st().print("m.st");

    cm.print("cm");
    cm.t().print("cm.t");
    cm.st().print("cm.st");

    std::cout << "m(1, 2): " << m(1, 2) << std::endl;
    std::cout << "cm(1, 2): " << cm(1, 2) << std::endl;

    // Armadillo saves things _transposed_ by default, appearing as row-major
    // rather than column major, probably as an attempt to make the conversion
    // easier.
    m.save(arma::hdf5_name(filename, "m", arma::hdf5_opts::append));
    // cm.save(arma::hdf5_name(filename, "cm", arma::hdf5_opts::append));
    m.save(arma::hdf5_name(filename, "mt", arma::hdf5_opts::append + arma::hdf5_opts::trans));
    // cm.save(arma::hdf5_name(filename, "cmt", arma::hdf5_opts::append + arma::hdf5_opts::trans));

    arma::mat m2;
    // arma::cx_mat cm2;
    arma::mat mt2;
    // arma::cx_mat cmt2;
    m2.load(arma::hdf5_name(filename, "m"));
    // cm2.load(arma::hdf5_name(filename, "cm"));
    mt2.load(arma::hdf5_name(filename, "mt"));
    // cmt2.load(arma::hdf5_name(filename, "cmt"));

    m2.print("m2");
    mt2.print("mt2");

    assert((m - m2).is_zero());
    assert((m.t() - mt2).is_zero());

    return 0;
}
