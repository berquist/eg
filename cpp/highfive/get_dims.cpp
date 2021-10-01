#include "get_dims.hpp"

#include <armadillo>

// template <typename T>
// std::vector<std::size_t> get_dims(const arma::Col<T> &value) {
//     return {value.n_elem, 1};
// }

template <>
std::vector<std::size_t> get_dims(const int &value) {
    return {};
}

template <>
std::vector<std::size_t> get_dims(const double &value) {
    return {};
}

template <>
std::vector<std::size_t> get_dims(const unsigned long &value) {
    return {};
}

template <>
std::vector<std::size_t> get_dims(const std::string &value) {
    return {};
}

template <>
std::vector<std::size_t> get_dims(const arma::Col<double> &value) {
    return {value.n_elem, 1};
}

template <>
std::vector<std::size_t> get_dims(const arma::Mat<std::complex<double>> &value) {
    return {value.n_rows, value.n_cols};
}

template <>
std::vector<std::size_t> get_dims(const arma::Mat<long long> &value) {
    return {value.n_rows, value.n_cols};
}

template <>
std::vector<std::size_t> get_dims(const arma::Cube<double> &value) {
    return {value.n_slices, value.n_rows, value.n_cols};
}

template <>
std::vector<std::size_t> get_dims(const arma::Cube<std::complex<double>> &value) {
    return {value.n_slices, value.n_rows, value.n_cols};
}
