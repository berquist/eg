#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <h5cpp/hdf5.hpp>

class Interface {
private:
    const hdf5::file::File &m_file;
public:
    Interface(const hdf5::file::File &file) : m_file(file) {};

    template <typename T>
    void read(const std::string &path, T &value) const {
        const hdf5::Path h5cpp_path(path);
        const hdf5::node::Dataset dset = m_file.root().get_dataset(h5cpp_path);
        dset.read(value);
    }

    template <typename T>
    void write(const std::string &path, const T &value) const {
        const hdf5::Path h5cpp_path(path);
        hdf5::property::LinkCreationList lcpl;
        lcpl.enable_intermediate_group_creation();
        const hdf5::dataspace::Simple dspace = hdf5::dataspace::create(value);
        const hdf5::node::Dataset dset(m_file.root(), h5cpp_path, hdf5::datatype::create<T>(), dspace, lcpl);
        dset.write(value);
    }
};

#endif // INTERFACE_HPP_
