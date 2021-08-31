//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Oct 07, 2017
//

#include "h5cpp_arma.hpp"
#include "arma.hpp"
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

void createFile() {
    file::File File = file::create("SomeFile.hdf5", file::AccessFlags::TRUNCATE);
    node::Group RootGroup = File.root();

    std::vector<int> Data{1, 2, 3, 4, 5, 6};
    Dimensions Shape{2, 3};
    Dimensions MaxShape{dataspace::Simple::UNLIMITED, 3};
    Dimensions ChunkSize{512, 3};
    dataspace::Simple Dataspace{Shape, MaxShape};
    datatype::Datatype Datatype = datatype::create<std::int32_t>();
    auto Dataset = node::ChunkedDataset(RootGroup, "test_data", Datatype,
                                        Dataspace, ChunkSize);
    Dataset.write(Data);
}

int example() {
    createFile();
    auto AnotherFile = file::open("SomeFile.hdf5");
    auto RootGroup = AnotherFile.root();
    auto Dataset = RootGroup.get_dataset("test_data");
    dataspace::Simple Dataspace(Dataset.dataspace());
    auto Dimensions = Dataspace.current_dimensions();
    auto MaxDimensions = Dataspace.maximum_dimensions();
    std::cout << "Dataset dimensions\n";
    std::cout << "   Current | Max\n";
    for (int i = 0; i < Dimensions.size(); i++) {
        std::cout << "i:" << i << "      " << Dimensions[i] << " | "
                  << MaxDimensions[i] << "\n";
    }

    auto CreationProperties = Dataset.creation_list();
    auto ChunkDims = CreationProperties.chunk();
    std::cout << "\nChunk size\n";
    for (int i = 0; i < ChunkDims.size(); i++) {
        std::cout << "i:" << i << "     " << ChunkDims[i] << "\n";
    }

    std::cout << "\nData type\n";
    auto Int32Type = datatype::create<std::int32_t>();
    auto UInt32Type = datatype::create<std::uint32_t>();
    auto FloatType = datatype::create<float>();
    auto DataTypeClass = Dataset.datatype().get_class();
    auto CurrentType = Dataset.datatype();
    std::cout << "Is:        " << DataTypeClass << std::endl;
    std::cout << "Is  int32: " << (Int32Type == CurrentType) << std::endl;
    std::cout << "Is uint32: " << (UInt32Type == CurrentType) << std::endl;
    std::cout << "Is  float: " << (FloatType == CurrentType) << std::endl;

    std::cout << "\nAll elements\n";
    std::vector<int> AllElements(Dataspace.size());
    Dataset.read(AllElements);
    for (auto Value : AllElements) {
        std::cout << Value << " ";
    }
    std::cout << "\n\nRow access\n";
    std::vector<int> RowData(static_cast<size_t>(Dimensions[1]));
    for (size_t i = 0; i < Dimensions[0]; i++) {
        dataspace::Hyperslab RowSelection{{i, 0}, {1, 3}};
        Dataset.read(RowData, RowSelection);
        std::cout << "i: " << i << " | ";
        for (auto Value : RowData) {
            std::cout << Value << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\nElement access\n     j:0  j:1 j:2\n";
    for (size_t i = 0; i < Dimensions[0]; i++) {
        std::cout << "i:" << i << "    ";
        for (size_t j = 0; j < Dimensions[1]; j++) {
            int Value;
            dataspace::Hyperslab ElementSelection{{i, j}, {1, 1}};
            Dataset.read(Value, ElementSelection);
            std::cout << Value << "    ";
        }
        std::cout << "\n";
    }
    return 0;
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

template <typename T>
void write(const file::File &h5cpp_file, const std::string &path, const T &value) {
    const Path h5cpp_path(path);
    const dataspace::Simple dspace = dataspace::create(value);
    const node::Dataset dset(h5cpp_file.root(), h5cpp_path, datatype::create<T>(), dspace);
    dset.write(value);
}

void write(const file::File &h5cpp_file, const std::string &path, const std::string &value) {
    const Path h5cpp_path(path);
    // const dataspace::Scalar dspace = dataspace::create(value);
    // const node::Dataset dset(h5cpp_file.root(), h5cpp_path, datatype::create<std::string>(), dspace);
    const node::Dataset dset(h5cpp_file.root(), h5cpp_path, datatype::create<std::string>());
    dset.write(value);
}

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

template <typename T>
void read(const file::File &h5cpp_file, const std::string &path, arma::Col<T> &value) {
    const Path h5cpp_path(path);
    const node::Group root = h5cpp_file.root();
    const node::Dataset dset = root.get_dataset(h5cpp_path);
    const dataspace::Simple dspace = dset.dataspace();
    value.set_size(hdf5_dimensions_to_arma_size_mat(dspace.current_dimensions()));
    dset.read(value);
}

template <typename T>
void read(const file::File &h5cpp_file, const std::string &path, arma::Row<T> &value) {
    const Path h5cpp_path(path);
    const node::Group root = h5cpp_file.root();
    const node::Dataset dset = root.get_dataset(h5cpp_path);
    const dataspace::Simple dspace = dset.dataspace();
    value.set_size(hdf5_dimensions_to_arma_size_mat(dspace.current_dimensions()));
    dset.read(value);
}

template <typename T>
void read(const file::File &h5cpp_file, const std::string &path, arma::Mat<T> &value) {
    const Path h5cpp_path(path);
    const node::Group root = h5cpp_file.root();
    const node::Dataset dset = root.get_dataset(h5cpp_path);
    const dataspace::Simple dspace = dset.dataspace();
    value.set_size(hdf5_dimensions_to_arma_size_mat(dspace.current_dimensions()));
    dset.read(value);
}

template <typename T>
void read(const file::File &h5cpp_file, const std::string &path, arma::Cube<T> &value) {
    const Path h5cpp_path(path);
    const node::Group root = h5cpp_file.root();
    const node::Dataset dset = root.get_dataset(h5cpp_path);
    const dataspace::Simple dspace = dset.dataspace();
    value.set_size(hdf5_dimensions_to_arma_size_cube(dspace.current_dimensions()));
    dset.read(value);
}

void read(const file::File &h5cpp_file, const std::string &path, std::string &value) {
    const Path h5cpp_path(path);
    const node::Group root = h5cpp_file.root();
    const node::Dataset dset = root.get_dataset(h5cpp_path);
    const dataspace::Scalar dspace = dset.dataspace();
    dset.read(value);
}

int main() {
    const std::string filename("arma.h5");
    const file::File file = get_or_create_file(filename);
    const node::Group root = file.root();

    // Demonstrate the "pure" Armadillo-based approach of saving to an HDF5
    // file.  Note that when looking at the underlying HDF5 file, the contents
    // will transposed from what's expected, since the storage mechanism
    // preserves Armadillo's use of column-major memory layout (Fortran)
    // rather than row-major (C).

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

    write(file, "/vecs/rv2", rv2);

    arma::Col<double> rv3;
    read(file, "/vecs/rv2", rv3);
    rv3.print("rv3 (that is rv2)");

    write(file, "/vecs/rv4", arma::Col<double>(3, arma::fill::randn));
    write(file, "/cubes/rc3", arma::cube(2, 3, 4, arma::fill::randn));

    arma::cube rc3;
    read(file, "/cubes/rc3", rc3);
    rc3.print("rc3 (read)");

    arma::imat rm2 = arma::randi<arma::imat>(6, 7, arma::distr_param(-10, +20));
    write(file, "/mats/rm2", rm2);

    const std::string mystring("I am just a string");
    write(file, "/s1", mystring);
    std::string mynewstring;
    read(file, "/s1", mynewstring);
    std::cout << mynewstring << std::endl;

    return 0;
}
