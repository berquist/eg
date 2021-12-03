#include <limits>
#include <random>

#include <complex>

#include <armadillo>
#include <highfive/H5File.hpp>

#include "common.hpp"
#include "interface.hpp"

using namespace HighFive;

// This contraption has been modified from
// https://stackoverflow.com/a/25200473 to only extract the first-level inner
// type.  This was done to cover the cases of Armadillo and libaview
// containers that may hold std::complex<T>, so that T is not mistakenly
// extracted.  We need this because both HDF5 and HighFive (understandably)
// treat std::complex<T> as a compound datatype.
//
// TODO to be bulletproof, it should go to the innermost type unless
// std::complex is found, in which case it should stop.  The current
// implementation will break with something like std::vector<std::vector<T>>.

template<typename T>
struct inner_type_impl
{
    using type = T;
};

template<template<typename> class E, typename T>
struct inner_type_impl<E<T>>
{
    // using type = typename inner_type_impl<T>::type;
    using type = T;
};

template<typename T>
using inner_type = typename inner_type_impl<T>::type;

template <typename T>
DataType get_dtype(const T &val) {
    return create_and_check_datatype<inner_type<decltype(static_cast<T>(const_cast<T&>(val)))>>();
}

// std::ostream &operator<<(std::ostream &os, const HighFive::DataType &dt);

std::ostream& operator<<(std::ostream &os, const DataTypeClass &dtc) {
    os << type_class_string(dtc);
    return os;
}

std::ostream& operator<<(std::ostream &os, const DataType &dt) {
    os << dt.string();
    return os;
}

static std::vector<int> generate_data(size_t size) {
    using value_type = int;
    // We use static in order to instantiate the random engine
    // and the distribution once only.
    // It may provoke some thread-safety issues.
    static std::uniform_int_distribution<value_type> distribution(
        std::numeric_limits<value_type>::min(),
        std::numeric_limits<value_type>::max());
    static std::default_random_engine generator;

    std::vector<value_type> data(size);
    std::generate(data.begin(), data.end(), []() { return distribution(generator); });
    return data;
}

int main() {
    const std::string filename("stl.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    std::vector<int> v10 = generate_data(10);
    std::vector<int> v20 = generate_data(20);
    std::vector<int> v30 = generate_data(30);
    std::cout << "v10" << std::endl;
    std::cout << v10 << std::endl;
    std::cout << "v20" << std::endl;
    std::cout << v20 << std::endl;
    std::cout << "v30" << std::endl;
    std::cout << v30 << std::endl;

    DataSet dset_0 = file.createDataSet("v0", v20);

    std::string attr_0_contents("v20");
    Attribute attr_0 = dset_0.createAttribute<std::string>("contents", DataSpace::From(attr_0_contents));
    attr_0.write(attr_0_contents);

    DataSet dset_1 = file.createDataSet("v1", v20);
    dset_1.write(v10);

    std::string attr_1_contents("v10");
    Attribute attr_1 = dset_1.createAttribute<std::string>("contents", DataSpace::From(attr_1_contents));
    attr_1.write(attr_1_contents);

    DataSet dset_2 = file.createDataSet("v2", v20);
    dset_2.write(v30);

    std::string attr_2_contents("v30");
    Attribute attr_2 = dset_2.createAttribute<std::string>("contents", DataSpace::From(attr_2_contents));
    attr_2.write(attr_2_contents);

    // DataSet dset_0_unlimited = file.createDataSet<int>("v0_unlimited", DataSpace(DataSpace::UNLIMITED));

    Interface iface(filename);

    iface.write("v0_iface", v20);

    const size_t dim = 5;
    arma::Col<double> a0(dim, arma::fill::randn);
    arma::Col<double> a1(dim, arma::fill::randn);
    arma::Col<std::complex<double>> ac01(a0, a1);
    std::vector<double> v0 = arma::conv_to<std::vector<double>>::from(a0);
    std::vector<std::complex<double>> vc01 = arma::conv_to<std::vector<std::complex<double>>>::from(ac01);
    a0.print("a0");
    a1.print("a1");
    ac01.print("ac01");

    const auto dt_int = get_dtype(v20);
    std::cout << "dt_int:  " << dt_int << std::endl;
    const auto dt_double = get_dtype(v0);
    std::cout << "dt_double:  " << dt_double << std::endl;
    const auto dt_cxdouble = get_dtype(vc01);
    std::cout << "dt_cxdouble:  " << dt_cxdouble << std::endl;

    return 0;
}
