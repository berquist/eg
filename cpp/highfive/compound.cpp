#include "interface.hpp"
#include <highfive/H5DataType.hpp>
#include <type_traits>

using namespace HighFive;

// TODO why can't these live in common.cpp?
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
    const auto type_name = std::string("mecp_state");
    std::cout << group_types.exist(type_name) << std::endl;
    h5_mecp_state.commit(group_types, type_name);
    std::cout << group_types.exist(type_name) << std::endl;
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

    std::cout << "std::is_enum<decltype(e1)> = " << std::is_enum<decltype(e1)>::value << std::endl;
    std::cout << "std::is_enum<decltype(e2)> = " << std::is_enum<decltype(e2)>::value << std::endl;
    std::cout << "std::is_compound<decltype(e1)> = " << std::is_compound<decltype(e1)>::value << std::endl;
    std::cout << "std::is_compound<decltype(e2)> = " << std::is_compound<decltype(e2)>::value << std::endl;
    std::cout << "std::is_object<decltype(e1)> = " << std::is_object<decltype(e1)>::value << std::endl;
    std::cout << "std::is_object<decltype(e2)> = " << std::is_object<decltype(e2)>::value << std::endl;

    std::cout << "std::is_enum<perturbation_type> = " << std::is_enum<perturbation_type>::value << std::endl;
    std::cout << "std::is_enum<mecp_algorithm> = " << std::is_enum<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_enum<libarchive::impl::schema::mecp_state> = " << std::is_enum<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_compound<perturbation_type> = " << std::is_compound<perturbation_type>::value << std::endl;
    std::cout << "std::is_compound<mecp_algorithm> = " << std::is_compound<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_compound<libarchive::impl::schema::mecp_state> = " << std::is_compound<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_function<perturbation_type> = " << std::is_function<perturbation_type>::value << std::endl;
    std::cout << "std::is_function<mecp_algorithm> = " << std::is_function<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_function<libarchive::impl::schema::mecp_state> = " << std::is_function<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_object<perturbation_type> = " << std::is_object<perturbation_type>::value << std::endl;
    std::cout << "std::is_object<mecp_algorithm> = " << std::is_object<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_object<libarchive::impl::schema::mecp_state> = " << std::is_object<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_class<perturbation_type> = " << std::is_class<perturbation_type>::value << std::endl;
    std::cout << "std::is_class<mecp_algorithm> = " << std::is_class<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_class<libarchive::impl::schema::mecp_state> = " << std::is_class<libarchive::impl::schema::mecp_state>::value << std::endl;
    std::cout << "std::is_union<perturbation_type> = " << std::is_union<perturbation_type>::value << std::endl;
    std::cout << "std::is_union<mecp_algorithm> = " << std::is_union<mecp_algorithm>::value << std::endl;
    std::cout << "std::is_union<libarchive::impl::schema::mecp_state> = " << std::is_union<libarchive::impl::schema::mecp_state>::value << std::endl;

    iface.write("s1_2", s1);
    iface.write("orbs_2", orbs);

    return 0;
}
