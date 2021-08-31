#include <armadillo>
#include "h5cpp_arma.hpp"
#include "interface.hpp"

using namespace hdf5;

arma::SizeMat hdf5_dimensions_to_arma_size_mat(const Dimensions &dims) {
    switch (dims.size()) {
    case 2:
        return arma::size(dims[0], dims[1]);
    default:
        throw std::runtime_error("unknown number of dimensions");
    }
}

arma::SizeCube hdf5_dimensions_to_arma_size_cube(const Dimensions &dims) {
    switch (dims.size()) {
    case 3:
        return arma::size(dims[0], dims[1], dims[2]);
    default:
        throw std::runtime_error("unknown number of dimensions");
    }
}

// loose implementations

template <typename T>
void read(const file::File &h5cpp_file, const std::string &path, arma::Col<T> &value) {
    const Path h5cpp_path(path);
    const node::Dataset dset = h5cpp_file.root().get_dataset(h5cpp_path);
    const dataspace::Simple dspace = dset.dataspace();
    value.set_size(hdf5_dimensions_to_arma_size_mat(dspace.current_dimensions()));
    dset.read(value);
}

template <typename T>
void read(const file::File &h5cpp_file, const std::string &path, arma::Row<T> &value) {
    const Path h5cpp_path(path);
    const node::Dataset dset = h5cpp_file.root().get_dataset(h5cpp_path);
    const dataspace::Simple dspace = dset.dataspace();
    value.set_size(hdf5_dimensions_to_arma_size_mat(dspace.current_dimensions()));
    dset.read(value);
}

template <typename T>
void read(const file::File &h5cpp_file, const std::string &path, arma::Mat<T> &value) {
    const Path h5cpp_path(path);
    const node::Dataset dset = h5cpp_file.root().get_dataset(h5cpp_path);
    const dataspace::Simple dspace = dset.dataspace();
    value.set_size(hdf5_dimensions_to_arma_size_mat(dspace.current_dimensions()));
    dset.read(value);
}

template <typename T>
void read(const file::File &h5cpp_file, const std::string &path, arma::Cube<T> &value) {
    const Path h5cpp_path(path);
    const node::Dataset dset = h5cpp_file.root().get_dataset(h5cpp_path);
    const dataspace::Simple dspace = dset.dataspace();
    value.set_size(hdf5_dimensions_to_arma_size_cube(dspace.current_dimensions()));
    dset.read(value);
}

void read(const file::File &h5cpp_file, const std::string &path, std::string &value) {
    const Path h5cpp_path(path);
    const node::Dataset dset = h5cpp_file.root().get_dataset(h5cpp_path);
    dset.read(value);
}

template <typename T>
void write_scalar(const file::File &h5cpp_file, const std::string &path, const T &value) {
    const Path h5cpp_path(path);
    property::LinkCreationList lcpl;
    lcpl.enable_intermediate_group_creation();
    const node::Dataset dset(h5cpp_file.root(), h5cpp_path, datatype::create<T>(), dataspace::create(value), lcpl);
    dset.write(value);
}

// class implementations

template <>
void Interface::read(const std::string &path, arma::Col<double> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Row<double> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Mat<double> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Cube<double> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Col<arma::uword> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Row<arma::uword> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Mat<arma::uword> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Cube<arma::uword> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Col<arma::sword> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Row<arma::sword> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Mat<arma::sword> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::read(const std::string &path, arma::Cube<arma::sword> &value) const {
    ::read(m_file, path, value);
}

template <>
void Interface::write(const std::string &path, const std::string &value) const {
    ::write_scalar(m_file, path, value);
}

template <>
void Interface::write(const std::string &path, const double &value) const {
    ::write_scalar(m_file, path, value);
}
