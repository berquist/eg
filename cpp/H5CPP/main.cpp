#include <string>
#include <vector>

#include <armadillo>

#include <h5cpp/core>
#include <h5cpp/io>
#include "utils.hpp"

/**
 * Examples of using H5CPP with Armadillo.
 *
 * Some of this adapted from
 * https://github.com/steven-varga/h5cpp/blob/9b9b90c55b4ae5fd2e7f21c075440e7c88c1545f/examples/attributes/attributes.cpp
 */
int main() {
    const size_t nrow = 2;
    const size_t ncol = 3;
    arma::mat m1 = arma::randu<arma::mat>(nrow, ncol);
    arma::mat m2 = arma::randu<arma::mat>(ncol, nrow);
    m1.print("m1");
    m2.print("m2");
    m1.save("m1.h5", arma::hdf5_binary);
    m2.save("m2.h5", arma::hdf5_binary);
    // Stop Armadillo from saving in column-major (Fortran) order
    m1.save(arma::hdf5_name("m.h5", "m1", arma::hdf5_opts::append + arma::hdf5_opts::trans));
    m2.save(arma::hdf5_name("m.h5", "m2", arma::hdf5_opts::append + arma::hdf5_opts::trans));

    h5::fd_t fd = h5::create("ml.h5", H5F_ACC_TRUNC, h5::default_fcpl, h5::libver_bounds({H5F_LIBVER_V18, H5F_LIBVER_V18}));
    h5::ds_t ds1 = h5::write(fd, "directory/dataset/m1", m1);
    h5::ds_t ds2 = h5::write(fd, "directory/dataset/m2", m2);

    arma::mat matrix = arma::zeros(3, 4);
    for (int i = 0; i < matrix.n_elem; i++) {
        matrix[i] = i;
    }
    // std::vector<sn::example::Record> vector = h5::utils::get_test_data<sn::example::Record>(40);
    // sn::example::Record& record = vector[3];

    // Let's write some attributes
    {
        ds1["att_01"] = 42;
        ds1["att_02"] = {1., 2., 3., 4.};
        ds1["att_03"] = {"1", "2", "3", "4"};
        ds1["att_04"] = {"alpha", "beta", "gamma", "..."};

        ds1["att_05"] = "const char[N]";
        ds1["att_06"] = u8"const char[N]áééé";
        ds1["att_07"] = std::string("std::string");

        // ds2["att_08"] = record; // pod/compound datatype
        // ds2["att_09"] = vector; // vector of pod/compound type
        ds2["att_10"] = matrix; // linear algebra object
    }
    return 0;
}
