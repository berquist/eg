#include <cassert>
#include <string>
#include <vector>

#include <armadillo>

#include <hdf5.h>
#include <h5cpp/core>
#include <h5cpp/io>
#include "utils.hpp"

herr_t write(h5::ds_t &ds, const arma::vec &v, hsize_t offset) {
    herr_t status;
    // Make sure that `v` will fit at the given offset. The new required
    // length is `offset + v.n_elem`. If this is larger than the current
    // number of elements, resize.
    const hid_t dspace = H5Dget_space(ds);
    const hssize_t current_size = H5Sget_simple_extent_npoints(dspace);
    assert(current_size >= 0);
    const hsize_t required_size = v.n_elem + offset;
    if (required_size > current_size) {
        hsize_t newdims[1] = {required_size};
        status = H5Dset_extent(ds, newdims);
    }
    h5::write(ds, v, h5::offset{offset}, h5::stride{1});
    return status;
}

template <typename T>
herr_t write(h5::ds_t &ds, const T * ptr, size_t len, hsize_t offset) {
    herr_t status;
    const hid_t dspace = H5Dget_space(ds);
    const hssize_t current_size = H5Sget_simple_extent_npoints(dspace);
    assert(current_size >= 0);
    const hsize_t required_size = len + offset;
    if (required_size > current_size) {
        hsize_t newdims[1] = {required_size};
        status = H5Dset_extent(ds, newdims);
    }
    h5::write(ds, ptr, h5::count{len}, h5::offset{offset}, h5::stride{1});
    return status;
}

hid_t get_or_create(h5::fd_t &fd, const std::string &ds_name) {
    hid_t ds;
    ds = H5Dopen2(fd, ds_name.c_str(), H5P_DEFAULT);
    // TODO how to silence HDF5-DIAG in this case?
    if (ds < 0) {
        ds = H5Dcreate2(fd, ds_name.c_str(), H5T_NATIVE_DOUBLE, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    }
    // TODO how to close `ds` automatically when done? Can we avoid using
    // `hid_t`?
    return ds;
}

/**
 * Examples of using H5CPP with Armadillo.
 *
 * Some of this adapted from
 * https://github.com/steven-varga/h5cpp/blob/9b9b90c55b4ae5fd2e7f21c075440e7c88c1545f/examples/attributes/attributes.cpp
 */
int main() {
    const size_t nrow = 2;
    const size_t ncol = 3;
    const arma::mat m1 = arma::randu<arma::mat>(nrow, ncol);
    const arma::mat m2 = arma::randu<arma::mat>(ncol, nrow);
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

    // This example tries to write to a dataset, then overwrite it with a
    // different
    // value. https://stackoverflow.com/questions/447854/delete-or-update-a-dataset-in-hdf5
    h5::fd_t fd2 = h5::create("ml2.h5", H5F_ACC_TRUNC);
    const std::string ds_name = "ds3";
    h5::write(fd2, ds_name, m1);
    // We need to drop down to the C API for this part. We can't overwrite
    // directly, rather we need to delete and then write. The terminology is
    // to "unlink", since unlinking the group does not necessarily free the
    // data, only the command-line tool `h5repack` guarantees that.
    herr_t status;

    status = H5Ldelete(fd2, ds_name.c_str(), H5P_DEFAULT);
    std::cout << "status: " << status << std::endl;

    h5::write(fd2, ds_name, m2);

    status = H5Ldelete(fd2, ds_name.c_str(), H5P_DEFAULT);
    std::cout << "status: " << status << std::endl;

    // This example tries writing a pointer.
    const arma::vec v1(23, arma::fill::randn);
    v1.print("v1");
    const double * v1p = v1.memptr();
    h5::write(fd2, ds_name, v1p, h5::count{v1.n_elem});

    status = H5Ldelete(fd2, ds_name.c_str(), H5P_DEFAULT);
    std::cout << "status: " << status << std::endl;

    // This example emulates appending to a dataset.
    arma::vec v2({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    v2.print("v2");
    // `current_dims` needs to be big enough to hold what you're going to
    // write!
    h5::ds_t ds3 = h5::create<double>(fd2, ds_name, h5::current_dims{v1.n_elem}, h5::max_dims{H5S_UNLIMITED});
    h5::write(ds3, v1, h5::offset{0}, h5::stride{1});
    // there is space, overwrite the first `v2.n_elem` elements
    h5::write(ds3, v2, h5::offset{0}, h5::stride{1});
    // This doesn't work, you need to set the extent first.
    // h5::write(ds3, v2, h5::offset{v1.n_elem}, h5::stride{1});
    const hsize_t ndims = 1;
    hsize_t newdims[ndims] = {40};
    // status = H5Sset_extent_simple(ds3, ndims, newdims, NULL);
    // This will automatically zero-fill the data memory
    status = H5Dset_extent(ds3, newdims);
    std::cout << "status: " << status << std::endl;
    // h5::write(ds3, v2, h5::offset{29}, h5::stride{1});
    status = write(ds3, v2, 29);
    std::cout << "status: " << status << std::endl;
    // HDF5 "ml2.h5" {
    // GROUP "/" {
    //    DATASET "ds3" {
    //       DATATYPE  H5T_IEEE_F64LE
    //       DATASPACE  SIMPLE { ( 40 ) / ( H5S_UNLIMITED ) }
    //       DATA {
    //       (0): 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -0.743551, -0.627185, -0.0953408,
    //       (13): 0.0612647, -1.66176, -0.27435, 0.428477, 1.41516, -0.0840964,
    //       (19): 0.611771, 0.362008, -1.98528, 1.93324, 0, 0, 0, 0, 0, 0, 1, 2, 3,
    //       (32): 4, 5, 6, 7, 8, 9, 10, 0
    //       }
    //    }
    // }
    // }
    status = write(ds3, v2, 100);
    std::cout << "status: " << status << std::endl;
    // HDF5 "ml2.h5" {
    // GROUP "/" {
    //    DATASET "ds3" {
    //       DATATYPE  H5T_IEEE_F64LE
    //       DATASPACE  SIMPLE { ( 110 ) / ( H5S_UNLIMITED ) }
    //       DATA {
    //       (0): 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -0.743551, -0.627185, -0.0953408,
    //       (13): 0.0612647, -1.66176, -0.27435, 0.428477, 1.41516, -0.0840964,
    //       (19): 0.611771, 0.362008, -1.98528, 1.93324, 0, 0, 0, 0, 0, 0, 1, 2, 3,
    //       (32): 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //       (53): 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //       (75): 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //       (97): 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    //       }
    //    }
    // }
    // }
    status = write<double>(ds3, v1p, 23, 120);
    std::cout << "status: " << status << std::endl;

    // Try getting two datasets: one that exists and one that doesn't.
    hid_t ds_exists_id = H5Dopen2(fd2, ds_name.c_str(), H5P_DEFAULT);
    std::cout << "ds_exists_id: " << ds_exists_id << std::endl;
    status = H5Dclose(ds_exists_id);
    std::cout << "status: " << status << std::endl;
    hid_t ds_doesnt_exist_id = H5Dopen2(fd2, "hello", H5P_DEFAULT);
    std::cout << "ds_doesnt_exist_id: " << ds_doesnt_exist_id << std::endl;
    hid_t ds_exists_id2 = get_or_create(fd2, ds_name);
    std::cout << "ds_exists_id2: " << ds_exists_id2 << std::endl;
    // The dataset id isn't necessarily the same, even though the dataset is?
    h5::write(ds_exists_id2, arma::vec({2.5}), h5::offset{70});
    status = H5Dclose(ds_exists_id2);
    std::cout << "status: " << status << std::endl;
    return 0;
}
