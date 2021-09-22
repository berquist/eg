#include "highfive_arma.hpp"
#include "interface.hpp"

using namespace HighFive;

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        os << "v[" << i << "] = " << v[i] << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const ObjectType &ot) {
    switch (ot) {
    case ObjectType::File:
        os << "ObjectType::File";
        break;
    case ObjectType::Group:
        os << "ObjectType::Group";
        break;
    case ObjectType::UserDataType:
        os << "ObjectType::UserDataType";
        break;
    case ObjectType::DataSpace:
        os << "ObjectType::DataSpace";
        break;
    case ObjectType::Dataset:
        os << "ObjectType::Dataset";
        break;
    case ObjectType::Attribute:
        os << "ObjectType::Attribute";
        break;
    case ObjectType::Other:
        os << "ObjectType::Other";
        break;
    default:
        throw std::invalid_argument("invalid argument to operator<< for HighFive::ObjectType");
    }
    return os;
}

template <typename T>
void write(File &file, const std::string &name, const std::vector<arma::Mat<T>> &vec) {
    const size_t vs = vec.size();
    // TODO check at least length 1
    // TODO check all items have same shape
    std::vector<size_t> dims = DataSpace::From(vec[0]).getDimensions();
    dims.insert(dims.begin(), vs);
    DataSet dset = file.createDataSet<T>(name, DataSpace(dims));
    for (size_t i = 0; i < vs; i++) {
        vec[i].print("m");
        // arma.x: /home/eric/development/eg/cpp/highfive/highfive_arma.hpp:124: HighFive::details::data_converter<arma::Mat<eT> >::data_converter(const HighFive::DataSpace&) [with T = double]: Assertion `dims.size() == 2' failed.
        // dset.select({i, 0, 0}, {1, dims[1], dims[2]}).write(vec[i]);
        // terminate called after throwing an instance of 'HighFive::DataSpaceException'
        //  what():  Impossible to write buffer of dimensions 1 into dataset of dimensions 3
        // dset.select({i, 0, 0}, {1, dims[1], dims[2]}).write(arma::conv_to<std::vector<T>>::from(arma::vectorise(vec[i])));
        dset.select({i, 0, 0}, {1, dims[1], dims[2]}).write_raw(vec[i].memptr());
    }
}

template <typename T>
void write(File &file, const std::string &name, const std::vector<arma::Cube<T>> &vec) {
    const size_t vs = vec.size();
    // TODO check at least length 1
    // TODO check all items have same shape
    std::vector<size_t> dims = DataSpace::From(vec[0]).getDimensions();
    dims.insert(dims.begin(), vs);
    DataSet dset = file.createDataSet<T>(name, DataSpace(dims));
    for (size_t i = 0; i < vs; i++) {
        vec[i].print("c");
        dset.select({i, 0, 0, 0}, {1, dims[1], dims[2], dims[3]}).write_raw(vec[i].memptr());
    }
}

int main() {
    const std::string filename("arma.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    Interface iface(filename);

    const size_t dim_big = 20;
    const std::vector<size_t> dim_big_to_cube{2, 5, 2};

    const arma::Col<double> rv1(dim_big, arma::fill::randn);
    const arma::mat rm1(dim_big, dim_big, arma::fill::randn);
    const arma::Cube<double> rc1(2, 3, 4, arma::fill::randn);
    const arma::Cube<arma::sword> rc2(2, 3, 4, arma::fill::zeros);

    rv1.print("rv1");
    auto dset_rv1 = file.createDataSet("rv1", rv1);
    arma::Col<double> rv1_read;
    rv1_read.print("rv1_read (before)");
    dset_rv1.read(rv1_read);
    rv1_read.print("rv1_read (after)");

    // Make a DataSet just from a DataSpace, *then* write.
    DataSpace dspace_rv1 = DataSpace::From(rv1);
    // std::cout << dspace_rv1 << std::endl;
    DataSet dset_rv1_clone = file.createDataSet<double>("rv1_clone", dspace_rv1);
    dset_rv1_clone.write(rv1);
    arma::Col<double> rv1_read_clone;
    dset_rv1_clone.read(rv1_read_clone);

    const arma::Col<double> rv2(dim_big, arma::fill::randn);
    rv2.print("rv2");
    dset_rv1_clone.write(rv2);

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
    rm2.print("rm2");
    iface.write("/mats/rm2", rm2);
    iface.write("/nested/mats/rm2", rm2);

    const std::string mystring("I am just a string");
    iface.write("/strings/s1", mystring);
    std::string mynewstring;
    iface.read("/strings/s1", mynewstring);
    std::cout << mynewstring << std::endl;

    const double n1_ = 1.23;
    const int n2_ = 4;
    const size_t n3_ = size_t(4);
    iface.write("/nums/n1", n1_);
    iface.write("/nums/n2", n2_);
    iface.write("/nums/n3", n3_);
    // DataSet dset_double = file.createDataSet("/nums/n1", 1.23);
    // DataSet dset_int = file.createDataSet("/nums/n2", 4);
    // DataSet dset_sizet = file.createDataSet("/nums/n3", size_t(4));
    double n1;
    int n2;
    size_t n3;
    iface.read("/nums/n1", n1);
    iface.read("/nums/n2", n2);
    iface.read("/nums/n3", n3);
    std::cout << "n1: " << n1 << std::endl;
    std::cout << "n2: " << n2 << std::endl;
    std::cout << "n3: " << n3 << std::endl;

    std::cout << file.listObjectNames() << std::endl;
    std::cout << "exist rv1: " << file.exist("rv1") << std::endl;
    std::cout << "exist /nums/n3: " << file.exist("/nums/n3") << std::endl;
    std::cout << "exist nums/n3: " << file.exist("nums/n3") << std::endl;

    const Group group_nums = file.getGroup("nums");
    std::cout << group_nums.getPath() << std::endl;
    const ObjectType type_nums = file.getObjectType("nums");
    std::cout << type_nums << std::endl;

    std::cout << iface.get_paths() << std::endl;

    // Write a vector into a DataSet that has a different shape but the same
    // total space.
    //
    // Can't resize...
    // DataSet dset_rv2_cube = file.createDataSet("/vecs/rv2_cube", rv2);
    // dset_rv2_cube.resize(dim_big_to_cube);
    // DataSet dset_rv2_cube = file.createDataSet<double>("/vecs/rv2_cube", DataSpace(dim_big_to_cube));
    // terminate called after throwing an instance of 'HighFive::DataSpaceException'
    //   what():  Impossible to write buffer of dimensions 2 into dataset of dimensions 3
    // [1]    67136 abort (core dumped)  ./arma.x
    // dset_rv2_cube.write(rv2);

    const std::vector<size_t> new_dims{1, 2, 12};
    // HDF5-DIAG: Error detected in HDF5 (1.12.0) thread 0:
    //   #000: H5D.c line 793 in H5Dset_extent(): unable to set dataset extent
    //     major: Dataset
    //     minor: Can't set value
    //   #001: H5VLcallback.c line 2406 in H5VL_dataset_specific(): unable to execute dataset specific callback
    //     major: Virtual Object Layer
    //     minor: Can't operate on object
    //   #002: H5VLcallback.c line 2369 in H5VL__dataset_specific(): unable to execute dataset specific callback
    //     major: Virtual Object Layer
    //     minor: Can't operate on object
    //   #003: H5VLnative_dataset.c line 334 in H5VL__native_dataset_specific(): unable to set extent of dataset
    //     major: Dataset
    //     minor: Unable to initialize object
    //   #004: H5Dint.c line 3021 in H5D__set_extent(): dataset has contiguous storage
    //     major: Invalid arguments to routine
    //     minor: Out of range
    // terminate called after throwing an instance of 'HighFive::DataSetException'
    //   what():  Could not resize dataset. (Invalid arguments to routine) Out of range
    // [1]    60265 abort (core dumped)  ./arma.x
    //
    // DataSet dset_cube_to_resize = file.createDataSet("/cubes/cube_to_resize", rc3);
    // dset_cube_to_resize.resize(new_dims);
    
    DataSet dset_cube_different_shape = file.createDataSet<double>("/cubes/different_shape", DataSpace(new_dims));
    dset_cube_different_shape.write(rc3);

    std::vector<arma::mat> vec_of_mats;
    std::vector<arma::cube> vec_of_cubes;
    for (size_t i = 0; i < 5; i++) {
        vec_of_mats.push_back(arma::mat(2, 3, arma::fill::randn));
        vec_of_cubes.push_back(arma::cube(2, 3, 4, arma::fill::randn));
    }
    write(file, "/x/y/z/vec_of_mats", vec_of_mats);
    write(file, "/x/y/z/vec_of_cubes", vec_of_cubes);

    arma::cx_mat cm(3, 4, arma::fill::randn);
    cm.print("cm");
    iface.write("cm", cm);
    arma::cx_mat cm_read;
    iface.read("cm", cm_read);
    cm_read.print("cm_read");
    assert((cm - cm_read).is_zero());

    return 0;
}
