#include "h5cpp_arma.hpp"
#include <boost/filesystem.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

// arma::SizeMat hdf5_dimensions_to_arma_size_mat(const Dimensions &dims) {
//     switch (dims.size()) {
//     case 2:
//         return arma::size(dims[0], dims[1]);
//     default:
//         throw std::runtime_error("unknown number of dimensions");
//     }
// }

// arma::SizeCube hdf5_dimensions_to_arma_size_cube(const Dimensions &dims) {
//     switch (dims.size()) {
//     case 3:
//         return arma::size(dims[0], dims[1], dims[2]);
//     default:
//         throw std::runtime_error("unknown number of dimensions");
//     }
// }

// template <typename T>
// void read(const file::File &h5cpp_file, const std::string &path, arma::Col<T> &value) {
//     const Path h5cpp_path(path);
//     const node::Dataset dset = h5cpp_file.root().get_dataset(h5cpp_path);
//     const dataspace::Simple dspace = dset.dataspace();
//     value.set_size(hdf5_dimensions_to_arma_size_mat(dspace.current_dimensions()));
//     dset.read(value);
// }

// template <typename T>
// void read(const file::File &h5cpp_file, const std::string &path, arma::Row<T> &value) {
//     const Path h5cpp_path(path);
//     const node::Dataset dset = h5cpp_file.root().get_dataset(h5cpp_path);
//     const dataspace::Simple dspace = dset.dataspace();
//     value.set_size(hdf5_dimensions_to_arma_size_mat(dspace.current_dimensions()));
//     dset.read(value);
// }

// template <typename T>
// void read(const file::File &h5cpp_file, const std::string &path, arma::Mat<T> &value) {
//     const Path h5cpp_path(path);
//     const node::Dataset dset = h5cpp_file.root().get_dataset(h5cpp_path);
//     const dataspace::Simple dspace = dset.dataspace();
//     value.set_size(hdf5_dimensions_to_arma_size_mat(dspace.current_dimensions()));
//     dset.read(value);
// }

// template <typename T>
// void read(const file::File &h5cpp_file, const std::string &path, arma::Cube<T> &value) {
//     const Path h5cpp_path(path);
//     const node::Dataset dset = h5cpp_file.root().get_dataset(h5cpp_path);
//     const dataspace::Simple dspace = dset.dataspace();
//     value.set_size(hdf5_dimensions_to_arma_size_cube(dspace.current_dimensions()));
//     dset.read(value);
// }

class Interface {
private:
    const file::File &m_file;
public:
    Interface(const file::File &file) : m_file(file) {};

    template <typename T>
    void read(const std::string &path, T &value) const {
        const Path h5cpp_path(path);
        const node::Dataset dset = m_file.root().get_dataset(h5cpp_path);
        dset.read(value);
    }

    // the decision made to force explicit instantiation for POD rather than
    // Armadillo types due to the sheer number of combinations
    template <typename T>
    void write(const std::string &path, const T &value) const {
        const Path h5cpp_path(path);
        property::LinkCreationList lcpl;
        lcpl.enable_intermediate_group_creation();
        const dataspace::Simple dspace = dataspace::create(value);
        const node::Dataset dset(m_file.root(), h5cpp_path, datatype::create<T>(), dspace, lcpl);
        dset.write(value);
    }
};

file::File get_or_create_file(const std::string &filename) {
    file::File h5file;
    const fs::path fp(filename);
    if (!fs::exists(fp)) {
        h5file = file::create(fp);
    } else if (file::is_hdf5_file(fp)) {
        h5file = file::open(fp, file::AccessFlags::READWRITE);
    } else {
        std::ostringstream os;
        os << "non-HDF5 file already exists: " << filename;
        throw std::runtime_error(os.str());
    }
    return h5file;
}

void containment(const node::Group &grp, const std::string &p) {
    const Path h5p(p);
    std::cout << p << std::endl;
    std::cout << "has_group:" << std::endl;
    std::cout << grp.has_group(h5p) << std::endl;
    std::cout << "has_dataset:" << std::endl;
    std::cout << grp.has_dataset(h5p) << std::endl;
}

int main() {
    const std::string filename("arma_nointerface.h5");
    const file::File file = get_or_create_file(filename);

    const Interface iface(file);

    const node::Group root = file.root();

    const size_t dim_big = 20;
    const arma::Col<double> rv1(dim_big, arma::fill::randn);
    const arma::mat rm1(dim_big, dim_big, arma::fill::randn);
    const arma::Cube<double> rc1(2, 3, 4, arma::fill::randn);
    const arma::Cube<arma::sword> rc2(2, 3, 4, arma::fill::zeros);

    // write manually

    const datatype::Float dtype = datatype::create<arma::Col<double> >();
    const dataspace::Simple dspace = dataspace::create(rv1);
    const node::Dataset dset = root.create_dataset("rv1_2", dtype, dspace);
    dset.write(rv1);

    // read manually

    arma::Col<double> rv1_read(dim_big);
    dset.read(rv1_read);

    const Path p2("rv1_3");
    const node::Dataset dset2(root, p2, dtype, dspace);
    dset2.write(rv1);

    const arma::Col<double> rv2(dim_big, arma::fill::randn);
    dset2.write(rv2);

    // iface.write("/vecs/rv2", rv2);

    // arma::Col<double> rv3;
    // iface.read("/vecs/rv2", rv3);

    // iface.write("/vecs/rv4", arma::Col<double>(3, arma::fill::randn));
    // iface.write("/cubes/rc3", arma::cube(2, 3, 4, arma::fill::randn));

    // arma::cube rc3;
    // iface.read("/cubes/rc3", rc3);

    // arma::imat rm2 = arma::randi<arma::imat>(6, 7, arma::distr_param(-10, +20));
    // iface.write("/mats/rm2", rm2);
    // iface.write("/nested/mats/rm2", rm2);

    // std::string p = "/nested/mats/rm2";
    // containment(root, p);

    // p = "/nested/mats";
    // containment(root, p);

    return 0;
}
