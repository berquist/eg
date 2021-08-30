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

#include <armadillo>
#include <h5cpp/hdf5.hpp>
#include <boost/filesystem.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

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
        // h5file = file::open(fp, file::AccessFlags::READWRITE);
        // for testing
        h5file = file::create(fp, file::AccessFlags::TRUNCATE);        
    } else {
        throw std::runtime_error("non-HDF5 file already exists!");
    }
    return h5file;
}

namespace hdf5 {
    namespace dataspace {
        template<> class TypeTrait<arma::Col<double> > {
        public:
            using DataspaceType = Simple;
            static DataspaceType create(const arma::Col<double> &v) {
                return Simple({v.n_elem});
            }
            static void *ptr(arma::Col<double> &v) {
                return reinterpret_cast<void*>(v.memptr());
            }
            static const void *cptr(const arma::Col<double> &v) {
                return reinterpret_cast<const void*>(v.memptr());
            }
        };
    }
    namespace datatype {
        template<> class TypeTrait<arma::Col<double> > {
        public:
            using Type = arma::Col<double>;
            using TypeClass = Float;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<double>::create();
            }
        };
    }
}

int main() {
    const std::string filename("arma.h5");
    file::File file = get_or_create_file(filename);
    node::Group root = file.root();

    // Demonstrate the "pure" Armadillo-based approach of saving to an HDF5
    // file.

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
    node::Dataset dset = root.create_dataset("rv1_2", dtype, dspace);
    dset.write(rv1);

    arma::Col<double> rv1_read(dim_big);
    dset.read(rv1_read);
    rv1_read.print("rv1 read");

    // You can't specify a full path like this, you need to use the full dataset constructor.
    // auto dset2 = root.create_dataset("/vecs/rv1_3", dtype, dspace);
    const Path p2("/vecs/rv1_3");
    node::Dataset dset2(root, p2, dtype, dspace);
    dset2.write(rv1);

    return 0;
}
