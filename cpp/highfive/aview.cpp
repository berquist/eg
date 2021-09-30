#include <complex>

#include "common.hpp"

#include <armadillo>
#include "highfive_arma.hpp"
#include "highfive_aview.hpp"

using namespace HighFive;

int main() {
    const std::string filename("aview.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    const size_t d1 = 2, d2 = 3, d3 = 4, d4 = 5;
    const size_t dt = d1 * d2 * d3 * d4;
    arma::vec v1(dt, arma::fill::randn);
    v1.print("v1");
    libaview::array_view<double> av1(v1.memptr(), v1.n_elem);
    libaview::tens4d t1(av1, d1, d2, d3, d4);

    DataSpace dspace_t1 =  DataSpace::From(t1);
    std::cout << dspace_t1.getDimensions() << std::endl;
    std::cout << "dt: " << dt << std::endl;
    // std::cout << "1: " << t1.view(0).size() << std::endl;
    // std::cout << "2: " << t1.view(0, 0).size() << std::endl;
    // std::cout << "3: " << t1.view(0, 0, 0).size() << std::endl;
    std::cout << "d2: " << d2 << " " << t1.view(0).size() / t1.view(0, 0).size() << std::endl;
    std::cout << "d3: " << d3 << " " << t1.view(0, 0).size() / t1.view(0, 0, 0).size() << std::endl;
    std::cout << "d4: " << d4 << " " << t1.view(0, 0, 0).size() << std::endl;

    size_t d1c = 0;
    while (true) {
        try {
            t1.view(d1c);
            d1c++;
        } catch (const std::out_of_range &e) {
            break;
        }
    }
    std::cout << "d1: " << d1 << " " << d1c << std::endl;

    DataSet dset_t1 = file.createDataSet<double>("t1", dspace_t1);
    dset_t1.write(t1);

    arma::vec v2(dt);
    libaview::array_view<double> av2(v2.memptr(), v2.n_elem);
    libaview::tens4d t2(av2, d1, d2, d3, d4);
    DataSet dset_t2 = file.getDataSet("t1");
    dset_t2.read(t2);
    // v2.print("v2");

    std::vector<double> v3(dt);
    libaview::array_view<double> av3(v3.data(), v2.n_elem);
    // libaview::tens4d t3(av3, d1, d2, d3, d4);
    // need to allocate underlying memory first, otherwise runtime error (not segfault)
    // pass a pointer to get around dim restrictions
    dset_t2.read(v3.data());
    // v3.clear();
    // v3.resize(dt);

    auto dset_t3 = file.createDataSet<double>("t3", DataSpace::From(av3));
    dset_t3.write(av3);
    // std::cout << v3 << std::endl;

    const size_t dt2 = d1 * d2 * d3;
    arma::cx_cube cz1(d1, d2, d3, arma::fill::randu);
    libaview::array_view<std::complex<double>> vz1(cz1.memptr(), cz1.n_elem);
    libaview::tens3z tz1(vz1, d1, d2, d3);

    auto dset_z1_arma = file.createDataSet<std::complex<double>>("z1_arma", DataSpace::From(cz1));
    auto dset_z1_aview = file.createDataSet<std::complex<double>>("z1_aview", DataSpace::From(tz1));
    dset_z1_arma.write(cz1);
    dset_z1_aview.write(tz1);
    cz1.print("cz1");

    return 0;
}
