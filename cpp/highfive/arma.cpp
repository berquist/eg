#include "common.hpp"
#include "highfive_arma.hpp"
#include "interface.hpp"

using namespace HighFive;

/** Write a STL vector of Armadillo matrices with the STL vector index as the first index.
 *
 */
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
        // Because the matrix has 2 dimensions and the dataspace still
        // technically has three, the matrix cannot be written directly using
        // HighFive machinery.  We can't call write_raw, because we want that
        // HighFive machinery to handle the memory layout conversions.

        // dset.select({i, 0, 0}, {1, dims[1], dims[2]}).write_raw(vec[i].memptr());
        dset.select({i, 0, 0}, {1, dims[1], dims[2]}).write(vec[i]);
    }
}

/** Write a STL vector of Armadillo cubes with the STL vector index as the first index.
 *
 */
template <typename T>
void write(File &file, const std::string &name, const std::vector<arma::Cube<T>> &vec) {
    const size_t vs = vec.size();
    std::vector<size_t> dims = DataSpace::From(vec[0]).getDimensions();
    dims.insert(dims.begin(), vs);
    DataSet dset = file.createDataSet<T>(name, DataSpace(dims));
    for (size_t i = 0; i < vs; i++) {
        vec[i].print("c");
        // Because the cube has 3 dimensions and the dataspace still technically has four
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

    iface.write("/vecs/rv4", arma::Row<double>(3, arma::fill::randn));
    arma::cube rc3(2, 3, 4, arma::fill::randn);
    rc3.print("rc3");
    iface.write("/cubes/rc3", rc3);

    arma::cube rc3_read;
    iface.read("/cubes/rc3", rc3_read);
    rc3_read.print("rc3 (read)");

    arma::imat rm2 = arma::randi<arma::imat>(6, 7, arma::distr_param(-10, +20));
    rm2.print("rm2");
    iface.write("/mats/rm2", rm2);
    iface.write("/nested/mats/rm2", rm2);

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

    // Example of writing an object to a DataSet that has the same number of
    // dimensions but the number of elements is distributed differently
    // between each dimension.
    DataSet dset_cube_different_shape = file.createDataSet<double>("/cubes/different_shape", DataSpace(new_dims));
    dset_cube_different_shape.write(rc3);

    // std::vector<arma::mat> vec_of_mats;
    // std::vector<arma::cube> vec_of_cubes;
    // for (size_t i = 0; i < 5; i++) {
    //     vec_of_mats.push_back(arma::mat(2, 3, arma::fill::randn));
    //     vec_of_cubes.push_back(arma::cube(2, 3, 4, arma::fill::randn));
    // }
    // write(file, "/x/y/z/vec_of_mats", vec_of_mats);
    // write(file, "/x/y/z/vec_of_cubes", vec_of_cubes);

    // Example of reading and writing an object with complex elements.
    arma::cx_mat cm(3, 4, arma::fill::randn);
    cm.print("cm");
    iface.write("cm", cm);
    arma::cx_mat cm_read;
    iface.read("cm", cm_read);
    cm_read.print("cm_read");
    assert((cm - cm_read).is_zero());

    const arma::span sp_0(0);
    const arma::span sp_12(1, 2);

    // Reading and writing slices of DataSets

    const std::string filename_windows("arma_windows.h5");
    File file_windows(filename_windows, File::ReadWrite | File::Create | File::Truncate);
    Interface iface_windows(filename_windows);

    arma::cx_cube cc(2, 3, 5, arma::fill::randn);
    arma::cx_cube cc2(cc);
    cc.print("cc");
    // This only sets the real part...?
    // cc2.tube(sp_0, sp_12).ones();
    arma::cx_cube tube(arma::cube(1, 2, 5, arma::fill::ones), arma::cube(1, 2, 5, arma::fill::ones));
    cc2.tube(sp_0, sp_12) = tube;
    cc2.print("cc2");
    DataSet dset_cc = file_windows.createDataSet("cc", cc);
    // rows: write 0 to 0 -> 0 offset, 1 element
    // cols: write 1 to 2 -> 1 offset, 2 elements
    // slices: tube, do all
    // The ordering follows HDF, not Armadillo: slices, rows, columns
    dset_cc.select({0, 0, 1}, {5, 1, 2}).write(tube);
    arma::cx_cube cc2_read;
    dset_cc.read(cc2_read);
    assert((cc2_read - cc2).is_zero());
    arma::cx_cube tube_read;
    dset_cc.select({0, 0, 1}, {5, 1, 2}).read(tube_read);
    tube_read.print("tube_read");

    const arma::cube ones_5 = arma::cube(5, 5, 5, arma::fill::ones);
    const arma::cube twos_5 = ones_5 * 2.0;
    const arma::cube threes_5 = ones_5 * 3.0;
    const arma::cube ones_1 = arma::cube(1, 1, 1, arma::fill::ones);
    const arma::cx_cube cx_threes_5(threes_5, threes_5);
    const arma::cx_cube cx_ones_1(ones_1, ones_1);

    // What happens when we try to write something too big of the same type?
    dset_cc.write(cx_threes_5);
    // -> writes matching space with no offset, drops extra elements!

    // What happens when we try to write something too small of the same type?
    dset_cc.write(cx_ones_1);
    // -> writes matching space with no offset, remaining elements become uninitialized!

    // What happens when we try to write something of the right size of a
    // different type?
    arma::cube cd = arma::randi<arma::cube>(2, 3, 5, arma::distr_param(-10, +20));
    arma::icube ci = arma::randi<arma::icube>(2, 3, 5, arma::distr_param(-10, +20));
    //     HighFive WARNING "/cc": data and hdf5 dataset have different types: Integer64 -> Compound128
    // HDF5-DIAG: Error detected in HDF5 (1.12.0) thread 0:
    //   #000: H5Dio.c line 314 in H5Dwrite(): can't write data
    //     major: Dataset
    //     minor: Write failed
    //   #001: H5VLcallback.c line 2186 in H5VL_dataset_write(): dataset write failed
    //     major: Virtual Object Layer
    //     minor: Write failed
    //   #002: H5VLcallback.c line 2152 in H5VL__dataset_write(): dataset write failed
    //     major: Virtual Object Layer
    //     minor: Write failed
    //   #003: H5VLnative_dataset.c line 207 in H5VL__native_dataset_write(): can't write data
    //     major: Dataset
    //     minor: Write failed
    //   #004: H5Dio.c line 648 in H5D__write(): unable to set up type info
    //     major: Dataset
    //     minor: Unable to initialize object
    //   #005: H5Dio.c line 946 in H5D__typeinfo_init(): unable to convert between src and dest datatype
    //     major: Dataset
    //     minor: Feature is unsupported
    //   #006: H5T.c line 4815 in H5T_path_find(): can't find datatype conversion path
    //     major: Datatype
    //     minor: Can't get value
    //   #007: H5T.c line 5028 in H5T__path_find_real(): no appropriate function for conversion path
    //     major: Datatype
    //     minor: Unable to initialize object
    // terminate called after throwing an instance of 'HighFive::DataSetException'
    //   what():  Error during HDF5 Write:
    //
    // dset_cc.write(ci);

    // What about writing integer to float?
    DataSet dset_float = file_windows.createDataSet<double>("float", DataSpace::From(cd));
    // HighFive WARNING "/float": data and hdf5 dataset have different types:
    // Integer64 -> Float64
    dset_float.write(ci);
    // ...but it does work.

    // Now try writing through the interface.
    // iface_windows.write("cc", cc);
    // iface_windows.write("cc", cx_threes_5);

    // Dimensions for vectors should be like (n, 1) or (1, n) for column and
    // row vectors, respectively.
    const DataSpace dspace_col = file.getDataSet("/vecs/rv2").getSpace();
    const DataSpace dspace_row = file.getDataSet("/vecs/rv4").getSpace();
    std::cout << "dspace_col.getDimensions: " << dspace_col.getDimensions() << std::endl;
    std::cout << "dspace_col.getMaxDimensions: " << dspace_col.getMaxDimensions() << std::endl;
    std::cout << "dspace_row.getDimensions: " << dspace_row.getDimensions() << std::endl;
    std::cout << "dspace_row.getMaxDimensions: " << dspace_row.getMaxDimensions() << std::endl;

    return 0;
}
