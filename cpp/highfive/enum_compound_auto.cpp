#include "iface.hpp"

HIGHFIVE_REGISTER_TYPE(perturbation_type, create_enum_perturbation_type)
HIGHFIVE_REGISTER_TYPE(mecp_algorithm, create_enum_mecp_algorithm)
HIGHFIVE_REGISTER_TYPE(libarchive::impl::schema::mecp_state, create_compound_mecp_state)
HIGHFIVE_REGISTER_TYPE(libgscf::rscf_orbitals_d_d, create_compound_rscf_orbitals_d_d)

int main() {
    const std::string filename("enum_compound_auto.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    Interface iface(filename);

    constexpr auto e1 = perturbation_type::magnetic;
    constexpr auto e2 = mecp_algorithm::penalty_function;
    const std::vector<libarchive::impl::schema::mecp_state> s1 = {{true, 2, 1}};
    const std::vector<libgscf::rscf_orbitals_d_d> orbs = {libgscf::rscf_orbitals_d_d(5, 4, 2)};
    // const auto s1 = libarchive::impl::schema::mecp_state {true, 2, 1};
    // const auto orbs = libgscf::rscf_orbitals_d_d(5, 4, 2);

    iface.write("e1", e1);
    iface.write("e2", e2);
    // iface.write("s1", s1);
    // iface.write("orbs", orbs);

    return 0;
}
