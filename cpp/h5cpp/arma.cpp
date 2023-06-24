#include "h5cpp_arma.hpp"
#include "interface.hpp"
#include <boost/filesystem.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        os << "v[" << i << "] = " << v[i] << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const node::Dataset &ds) {
    return os;
}

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
    // Must be a single link name
    // std::cout << "exists:" << std::endl;
    // std::cout << grp.exists(p) << std::endl;
    std::cout << "has_group:" << std::endl;
    std::cout << grp.has_group(h5p) << std::endl;
    std::cout << "has_dataset:" << std::endl;
    std::cout << grp.has_dataset(h5p) << std::endl;
}

int main() {
    const std::string filename("arma.h5");
    const file::File file = get_or_create_file(filename);

    const Interface iface(file);

    const node::Group root = file.root();

    // Demonstrate the "pure" Armadillo-based approach of saving to an HDF5
    // file.  Note that when looking at the underlying HDF5 file, the contents
    // will transposed from what's expected, since the storage mechanism
    // preserves Armadillo's use of column-major memory layout (Fortran)
    // rather than row-major (C).
    //
    // Armadillo also seems to handle intermediate path creation properly...

    const size_t dim_big = 20;
    const arma::Col<double> rv1(dim_big, arma::fill::randn);
    rv1.print("rv1 create");
    rv1.save(arma::hdf5_name(filename, "/vecs/rv1", arma::hdf5_opts::append));

    const arma::mat rm1(dim_big, dim_big, arma::fill::randn);
    // rm1.print();
    rm1.save(arma::hdf5_name(filename, "/mats/rm1", arma::hdf5_opts::append));

    const arma::Cube<double> rc1(2, 3, 4, arma::fill::randn);
    const arma::Cube<arma::sword> rc2(2, 3, 4, arma::fill::zeros);
    // rc1.print();
    // rc2.print();
    rc1.save(arma::hdf5_name(filename, "/cubes/rc1", arma::hdf5_opts::append));
    rc2.save(arma::hdf5_name(filename, "/cubes/rc2", arma::hdf5_opts::append));

    // Demonstrate the proper h5cpp-based approach of saving to and reading
    // from an HDF5 file.

    const datatype::Float dtype = datatype::create<arma::Col<double> >();
    const dataspace::Simple dspace = dataspace::create(rv1);
    const node::Dataset dset = root.create_dataset("rv1_2", dtype, dspace);
    dset.write(rv1);

    arma::Col<double> rv1_read(dim_big);
    dset.read(rv1_read);
    rv1_read.print("rv1 read");

    // You can't specify a full path like this, you need to use the full dataset constructor.
    // auto dset2 = root.create_dataset("/vecs/rv1_3", dtype, dspace);
    const Path p2("/vecs/rv1_3");
    const node::Dataset dset2(root, p2, dtype, dspace);
    dset2.write(rv1);

    // Can we overwrite an existing dataset with data that has the same shape? Yes.
    const arma::Col<double> rv2(dim_big, arma::fill::randn);
    rv2.print("rv2");
    dset2.write(rv2);

    iface.write("/vecs/rv2", rv2);

    arma::Col<double> rv3;
    iface.read("/vecs/rv2", rv3);
    rv3.print("rv3 (that is rv2)");

    iface.write("/vecs/rv4", arma::Col<double>(3, arma::fill::randn));
    iface.write("/cubes/rc3", arma::cube(2, 3, 4, arma::fill::randn));

    arma::cube rc3;
    iface.read("/cubes/rc3", rc3);
    rc3.print("rc3 (read)");

    arma::imat rm2 = arma::randi<arma::imat>(6, 7, arma::distr_param(-10, +20));
    iface.write("/mats/rm2", rm2);
    iface.write("/nested/mats/rm2", rm2);

    const std::string mystring("I am just a string");
    iface.write("/strings/s1", mystring);
    std::string mynewstring;
    iface.read("/strings/s1", mynewstring);
    std::cout << mynewstring << std::endl;

    iface.write("/nums/n1", 1.23);
    iface.write("/nums/n2", 4);
    iface.write("/nums/n3", size_t(4));
    double n1;
    int n2;
    size_t n3;
    iface.read("/nums/n1", n1);
    iface.read("/nums/n2", n2);
    iface.read("/nums/n3", n3);

    // node::Group group = root;
    // std::vector<node::Dataset> datasets;

    // std::copy_if(node::RecursiveNodeIterator::begin(group),
    //              node::RecursiveNodeIterator::end(group),
    //              std::back_inserter(datasets),
    //              [](const node::Node &node) {
    //                  return node.type()==node::Type::DATASET;
    //              });

    // std::cout << "Datasets:" << std::endl;
    // std::cout << datasets << std::endl;


    // std::for_each(hdf5::node::RecursiveLinkIterator::begin(group),
    //               hdf5::node::RecursiveLinkIterator::end(group),
    //               [](const hdf5::node::Link &link)
    //                   { std::cout << link.path() << std::endl; });

    std::string p = "/nested/mats/rm2";
    containment(root, p);

    p = "/nested/mats";
    containment(root, p);

    return 0;
}
