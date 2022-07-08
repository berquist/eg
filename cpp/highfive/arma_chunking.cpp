#include "highfive_arma.hpp"

using namespace HighFive;

int main() {
    const std::string filename("arma_chunking.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    const arma::mat m1(3, 3, arma::fill::randn);
    const arma::mat m2(3, 6, arma::fill::randn);
    const arma::mat m3(4, 4, arma::fill::ones);

    const DataSet dset_default = file.createDataSet("m1", m1);

    // With extendable dimensions you *must* specify chunking, otherwise you
    // get this semi-cryptic error:
    //
    // extendible contiguous non-external dataset not allowed
    DataSetCreateProps props;
    // props.add(Chunking(std::vector<hsize_t>{1, 1}));
    // hunk size must be <= maximum dimension size for fixed-sized dimensions
    // props.add(Chunking(std::vector<hsize_t>{5, 5}));
    props.add(Chunking(std::vector<hsize_t>{3, 5}));

    // Writing to a dset with one unlimited/extendable dimension.
    const std::string name_dset_ulimit_1("m1_1");
    std::cout << name_dset_ulimit_1 << std::endl;
    DataSet dset_ulimit_1 = file.createDataSet<double>(
        name_dset_ulimit_1, DataSpace({3, 3}, {3, DataSpace::UNLIMITED}), props);
    dset_ulimit_1.write(m1);

    // Writing to a dset with all unlimited/extendable dimensions.
    const std::string name_dset_ulimit_all("m1_all");
    std::cout << name_dset_ulimit_all << std::endl;
    DataSet dset_ulimit_all = file.createDataSet<double>(
        name_dset_ulimit_all, DataSpace({3, 3}, {DataSpace::UNLIMITED, DataSpace::UNLIMITED}), props);
    dset_ulimit_all.write(m1);

    dset_ulimit_1.resize({m2.n_rows, m2.n_cols});
    dset_ulimit_1.write(m2);

    // dimension cannot exceed the existing maximal size (new: 4 max: 3)
    // dset_ulimit_1.resize({m3.n_rows, m3.n_cols});

    return 0;
}
