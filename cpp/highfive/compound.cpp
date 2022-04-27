#include "common.hpp"
#include "interface.hpp"
#include <highfive/H5DataType.hpp>
#include "highfive_arma.hpp"

using namespace HighFive;

namespace libstore {

template<typename T>
struct inner_type
{
    using type = T;
};

template<typename T>
struct inner_type<std::complex<T>>
{
    using type = std::complex<T>;
};

template<template<typename...> class E, typename Head, typename... Tail>
struct inner_type<E<Head, Tail...>>
{
    using type = Head;
};

template <typename T>
DataType get_dtype(const T &val) {
    return create_and_check_datatype<typename inner_type<T>::type>();
}

std::ostream &operator<<(std::ostream &os, const DataType &dt);

} // namespace libstore

// TODO why can't these live in common.cpp?
HIGHFIVE_REGISTER_TYPE(perturbation_type, create_enum_perturbation_type)
HIGHFIVE_REGISTER_TYPE(mecp_algorithm, create_enum_mecp_algorithm)
HIGHFIVE_REGISTER_TYPE(libarchive::impl::schema::mecp_state, create_compound_mecp_state)
HIGHFIVE_REGISTER_TYPE(libgscf::rscf_orbitals_d_d, create_compound_rscf_orbitals_d_d)

typedef struct {
    int m1;
    int m2;
    int m3;
} CSL1;

typedef struct {
    CSL1 csl1;
} CSL2;


CompoundType create_compound_csl1() {
    auto t2 = AtomicType<int>();
    CompoundType t1({{"m1", AtomicType<int>{}}, {"m2", AtomicType<int>{}}, {"m3", t2}});

    return t1;
}

CompoundType create_compound_csl2() {
    CompoundType t1 = create_compound_csl1();

    CompoundType t2({{"csl1", t1}});

    return t2;
}

HIGHFIVE_REGISTER_TYPE(CSL1, create_compound_csl1)
HIGHFIVE_REGISTER_TYPE(CSL2, create_compound_csl2)

template<typename T>
struct is_custom {
    using TI = typename libstore::inner_type<T>::type;
    static constexpr bool value = std::is_compound<TI>::value && !(std::is_enum<T>::value);
};

template<typename T>
struct is_custom<std::complex<T>> {
    static constexpr bool value = false;
};

int main() {
    const std::string filename("compound.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    Interface iface(filename);

    const std::string DATASET_NAME1("/a");
    const std::string DATASET_NAME2("/b");

    const auto t3 = AtomicType<int>();
    const auto t1 = create_compound_csl1();
    t1.commit(file, "my_type");

    const auto t2 = create_compound_csl2();
    t2.commit(file, "my_type2");

    {
        auto dataset = file.createDataSet(DATASET_NAME1, DataSpace(2), t1);

        const std::vector<CSL1> csl = {{1, 1, 1}, {2, 3, 4}};
        dataset.write(csl);
    }

    const std::string name_group_types(".types");
    // auto group_types = file.createGroup(name_group_types);
    auto group_types = file.getGroup(name_group_types);

    const auto h5_mecp_state = create_compound_mecp_state();
    const auto mecp_state_type_name = std::string("mecp_state");
    std::cout << group_types.exist(mecp_state_type_name) << std::endl;
    h5_mecp_state.commit(group_types, mecp_state_type_name);
    std::cout << group_types.exist(mecp_state_type_name) << std::endl;
    // Have to write a vector, not a single instance...
    // const auto s1 = libarchive::impl::schema::mecp_state {true, 2, 1};
    const std::vector<libarchive::impl::schema::mecp_state> s1 = {{true, 2, 1}};
    auto dset_s1 = file.createDataSet("/s1", DataSpace(s1.size()), h5_mecp_state);
    dset_s1.write(s1);

    const auto h5_rscf_orbitals_d_d = create_compound_rscf_orbitals_d_d();
    h5_rscf_orbitals_d_d.commit(group_types, "rscf_orbitals_d_d");
    const std::vector<libgscf::rscf_orbitals_d_d> orbs = {libgscf::rscf_orbitals_d_d(5, 4, 2)};
    // auto dset_orbs = file.createDataSet("orbs", orbs);
    auto dset_orbs = file.createDataSet("orbs", DataSpace(orbs.size()), h5_rscf_orbitals_d_d);
    dset_orbs.write(orbs);

    constexpr auto e1 = perturbation_type::magnetic;
    constexpr auto e2 = mecp_algorithm::penalty_function;
    const arma::vec v1(4, arma::fill::randn);
    const std::complex<double> c1(2.0, 3.2);
    const std::vector<int> v2 {4, 5, 6};

    std::cout << "std::is_floating_point<std::complex<double>> = " << std::is_floating_point<std::complex<double>>::value << std::endl;
    std::cout << "std::is_floating_point<arma::vec> = " << std::is_floating_point<arma::vec>::value << std::endl;
    std::cout << "std::is_floating_point<perturbation_type> = " << std::is_floating_point<perturbation_type>::value << std::endl;
    std::cout << "std::is_floating_point<mecp_algorithm> = " << std::is_floating_point<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_floating_point<libarchive::impl::schema::mecp_state> = " << std::is_floating_point<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_array<std::complex<double>> = " << std::is_array<std::complex<double>>::value << std::endl;
    std::cout << "std::is_array<arma::vec> = " << std::is_array<arma::vec>::value << std::endl;
    std::cout << "std::is_array<perturbation_type> = " << std::is_array<perturbation_type>::value << std::endl;
    std::cout << "std::is_array<mecp_algorithm> = " << std::is_array<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_array<libarchive::impl::schema::mecp_state> = " << std::is_array<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_enum<std::complex<double>> = " << std::is_enum<std::complex<double>>::value << std::endl;
    std::cout << "std::is_enum<arma::vec> = " << std::is_enum<arma::vec>::value << std::endl;
    std::cout << "std::is_enum<perturbation_type> = " << std::is_enum<perturbation_type>::value << std::endl;
    std::cout << "std::is_enum<mecp_algorithm> = " << std::is_enum<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_enum<libarchive::impl::schema::mecp_state> = " << std::is_enum<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_union<std::complex<double>> = " << std::is_union<std::complex<double>>::value << std::endl;
    std::cout << "std::is_union<arma::vec> = " << std::is_union<arma::vec>::value << std::endl;
    std::cout << "std::is_union<perturbation_type> = " << std::is_union<perturbation_type>::value << std::endl;
    std::cout << "std::is_union<mecp_algorithm> = " << std::is_union<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_union<libarchive::impl::schema::mecp_state> = " << std::is_union<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_class<std::complex<double>> = " << std::is_class<std::complex<double>>::value << std::endl;
    std::cout << "std::is_class<arma::vec> = " << std::is_class<arma::vec>::value << std::endl;
    std::cout << "std::is_class<perturbation_type> = " << std::is_class<perturbation_type>::value << std::endl;
    std::cout << "std::is_class<mecp_algorithm> = " << std::is_class<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_class<libarchive::impl::schema::mecp_state> = " << std::is_class<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_function<std::complex<double>> = " << std::is_function<std::complex<double>>::value << std::endl;
    std::cout << "std::is_function<arma::vec> = " << std::is_function<arma::vec>::value << std::endl;
    std::cout << "std::is_function<perturbation_type> = " << std::is_function<perturbation_type>::value << std::endl;
    std::cout << "std::is_function<mecp_algorithm> = " << std::is_function<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_function<libarchive::impl::schema::mecp_state> = " << std::is_function<libarchive::impl::schema::mecp_state>::value << std::endl;

    std::cout << "std::is_object<std::complex<double>> = " << std::is_object<std::complex<double>>::value << std::endl;
    std::cout << "std::is_object<arma::vec> = " << std::is_object<arma::vec>::value << std::endl;
    std::cout << "std::is_object<perturbation_type> = " << std::is_object<perturbation_type>::value << std::endl;
    std::cout << "std::is_object<mecp_algorithm> = " << std::is_object<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_object<libarchive::impl::schema::mecp_state> = " << std::is_object<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_compound<std::complex<double>> = " << std::is_compound<std::complex<double>>::value << std::endl;
    std::cout << "std::is_compound<arma::vec> = " << std::is_compound<arma::vec>::value << std::endl;
    std::cout << "std::is_compound<perturbation_type> = " << std::is_compound<perturbation_type>::value << std::endl;
    std::cout << "std::is_compound<mecp_algorithm> = " << std::is_compound<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_compound<libarchive::impl::schema::mecp_state> = " << std::is_compound<libarchive::impl::schema::mecp_state>::value << std::endl;

    std::cout << "get_dtype(std::complex<double>) = " << libstore::get_dtype(c1) << std::endl;
    std::cout << "get_dtype(arma::vec) = " << libstore::get_dtype(v1) << std::endl;
    std::cout << "get_dtype(perturbation_type) = " << libstore::get_dtype(e1) << std::endl;
    std::cout << "get_dtype(mecp_algorithm) = " << libstore::get_dtype(e2) << std::endl;
    std::cout << "get_dtype(libarchive::impl::schema::mecp_state) = " << libstore::get_dtype(s1[0]) << std::endl;

    // decltype not working?
    // std::cout << "[inner] type_name(std::complex<double>) = " << type_name<libstore::inner_type<decltype(c1)>::type>() << std::endl;
    // std::cout << "[inner] type_name(arma::vec) = " << type_name<libstore::inner_type<decltype(v1)>::type>() << std::endl;
    // std::cout << "[inner] type_name(std::vector<int>) = " << type_name<libstore::inner_type<decltype(v2)>::type>() << std::endl;
    // std::cout << "[inner] type_name(perturbation_type) = " << type_name<libstore::inner_type<decltype(e1)>::type>() << std::endl;
    // std::cout << "[inner] type_name(mecp_algorithm) = " << type_name<libstore::inner_type<decltype(e2)>::type>() << std::endl;
    // std::cout << "[inner] type_name(libarchive::impl::schema::mecp_state) = " << type_name<libstore::inner_type<decltype(s1[0])>::type>() << std::endl;
    // std::cout << "[inner] type_name(std::vector<libarchive::impl::schema::mecp_state>) = " << type_name<libstore::inner_type<decltype(s1)>::type>() << std::endl;

    std::cout << "[inner] type_name(std::complex<double>) = " << type_name<libstore::inner_type<std::complex<double>>::type>() << std::endl;
    std::cout << "[inner] type_name(arma::vec) = " << type_name<libstore::inner_type<arma::vec>::type>() << std::endl;
    std::cout << "[inner] type_name(std::vector<int>) = " << type_name<libstore::inner_type<std::vector<int>>::type>() << std::endl;
    std::cout << "[inner] type_name(perturbation_type) = " << type_name<libstore::inner_type<perturbation_type>::type>() << std::endl;
    std::cout << "[inner] type_name(mecp_algorithm) = " << type_name<libstore::inner_type<mecp_algorithm>::type>() << std::endl;
    std::cout << "[inner] type_name(libarchive::impl::schema::mecp_state) = " << type_name<libstore::inner_type<libarchive::impl::schema::mecp_state>::type>() << std::endl;
    std::cout << "[inner] type_name(std::vector<libarchive::impl::schema::mecp_state>) = " << type_name<libstore::inner_type<std::vector<libarchive::impl::schema::mecp_state>>::type>() << std::endl;

    std::cout << "is_custom(std::complex<double>) = " << is_custom<std::complex<double>>::value << std::endl;
    std::cout << "is_custom(arma::vec) = " << is_custom<arma::vec>::value << std::endl;
    std::cout << "is_custom(std::vector<int>) = " << is_custom<std::vector<int>>::value << std::endl;
    std::cout << "is_custom(perturbation_type) = " << is_custom<perturbation_type>::value << std::endl;
    std::cout << "is_custom(mecp_algorithm) = " << is_custom<mecp_algorithm>::value << std::endl;
    std::cout << "is_custom(libarchive::impl::schema::mecp_state) = " << is_custom<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "is_custom(std::vector<libarchive::impl::schema::mecp_state>) = " << is_custom<std::vector<libarchive::impl::schema::mecp_state>>::value << std::endl;

    iface.write("s1_2", s1);
    iface.write("orbs_2", orbs);

    return 0;
}
