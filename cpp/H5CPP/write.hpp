#include <armadillo>

#include <hdf5.h>
#include <h5cpp/core>

herr_t write(h5::ds_t &ds, const arma::vec &v, hsize_t offset);

template <typename T>
herr_t write(h5::ds_t &ds, const T * ptr, size_t len, hsize_t offset);
