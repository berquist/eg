#include "interface.hpp"
#include "rscf_orbitals_mock.h"
#include <highfive/H5DataType.hpp>

using namespace HighFive;
using namespace libgscf;

namespace libarchive {
namespace impl {
namespace schema {
struct mecp_state {
    bool spin;
    size_t irrep;
    size_t state_within_irrep;
};
} // namespace schema
} // namespace impl
} // namespace libarchive

CompoundType create_compound_mecp_state() {
    return CompoundType(
        {
            {"spin", AtomicType<bool>{}},
            {"irrep", AtomicType<size_t>{}},
            {"state_within_irrep", AtomicType<size_t>{}}
        }
        );
}

HIGHFIVE_REGISTER_TYPE(libarchive::impl::schema::mecp_state, create_compound_mecp_state)

namespace libgscf {
template class rscf_orbitals<double, double>;
}

CompoundType create_compound_rscf_orbitals() {
    return CompoundType(
        {
            {"nbsf", AtomicType<size_t>{}},
            {"nmo", AtomicType<size_t>{}},
            {"nocc", AtomicType<size_t>{}},
            {"c", AtomicType<double>{}},
            {"eigval", AtomicType<double>{}},
            {"objv", AtomicType<double>{}}
        }
        );
}

// HIGHFIVE_REGISTER_TYPE(libgscf::rscf_orbitals<double, double>, create_compound_rscf_orbitals);
// HIGHFIVE_REGISTER_TYPE(double, create_compound_rscf_orbitals);

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

    // Interface iface(filename);

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

    const auto h5_mecp_state = create_compound_mecp_state();
    const auto type_name = std::string("mecp_state");
    std::cout << file.exist(type_name) << std::endl;
    h5_mecp_state.commit(file, type_name);
    std::cout << file.exist(type_name) << std::endl;
    // Have to write a vector, not a single instance...
    // const auto s1 = libarchive::impl::schema::mecp_state {true, 2, 1};
    const std::vector<libarchive::impl::schema::mecp_state> s1 = {{true, 2, 1}};
    auto dset_s1 = file.createDataSet("/s1", DataSpace(1), h5_mecp_state);
    dset_s1.write(s1);

    return 0;
}
