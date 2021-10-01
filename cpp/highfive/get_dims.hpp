#ifndef GET_DIMS_HPP_
#define GET_DIMS_HPP_

#include <vector>

#include <armadillo>
// #include <libaview/tens.h>

template <typename T>
std::vector<std::size_t> get_dims(const T &value) {
    return {};
}

template <typename T>
std::vector<std::size_t> get_dims(const arma::Col<T> &value) {
    return {value.n_elem, 1};
}

template <typename T>
std::vector<std::size_t> get_dims(const arma::Row<T> &value) {
    return {1, value.n_elem};
}

template <typename T>
std::vector<std::size_t> get_dims(const arma::Mat<T> &value) {
    return {value.n_rows, value.n_cols};
}

template <typename T>
std::vector<std::size_t> get_dims(const arma::Cube<T> &value) {
    return {value.n_slices, value.n_rows, value.n_cols};
}

#endif // GET_DIMS_HPP_
