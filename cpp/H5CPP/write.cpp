#include <cassert>

#include <armadillo>

#include <hdf5.h>
#include <h5cpp/core>
#include <h5cpp/io>

#include "write.hpp"

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

// TODO not template<> and I don't understand why, but it looks like
// `write<double>` isn't needed anymore.
template herr_t write(h5::ds_t &ds, const double * ptr, size_t len, hsize_t offset);
