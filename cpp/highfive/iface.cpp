#include "interface.hpp"

#if 0
#define HIGHFIVE_REGISTER_TYPE(type, function) \
    namespace HighFive {                       \
    template<>                                 \
    DataType create_datatype<type>() {         \
        return function();                     \
    }                                          \
    }
#endif

void init_types(Interface &iface) {
    // iface.register_type(create_enum_perturbation_type, "perturbationp_type");
    // iface.register_type(create_enum_mecp_algorithm, "mecp_algorithm");
    // iface.register_type(create_compound_mecp_state, "mecp_state");
    // iface.register_type(create_compound_rscf_orbitals_d_d, "rscf_orbitals_d_d");
    // iface.register_type(std::function<EnumType<perturbation_type>()>(&create_enum_perturbation_type), "perturbation_type");
    // iface.register_type(std::function<EnumType<mecp_algorithm>()>(create_enum_mecp_algorithm), "mecp_algorithm");
    // iface.register_type(std::function<CompoundType()>(&create_compound_mecp_state), "mecp_state");
    // iface.register_type(std::function<CompoundType()>(&create_compound_rscf_orbitals_d_d), "rscf_orbitals_d_d");
}

#if 0
template<typename T>
std::function<HighFive::EnumType<T>()> get_highfive_type_generating_function_enum(const std::string &file_type_name) {
    if (file_type_name == "perturbation_type")
        return std::function<HighFive::EnumType<perturbation_type>()>(&create_enum_perturbation_type);
    if (file_type_name == "mecp_algorithm")
        return std::function<HighFive::EnumType<mecp_algorithm>()>(&create_enum_mecp_algorithm);
    throw std::runtime_error("unknown string representation of enum type name");
}
#endif

// HIGHFIVE_REGISTER_TYPE(perturbation_type, create_enum_perturbation_type)
// HIGHFIVE_REGISTER_TYPE(mecp_algorithm, create_enum_mecp_algorithm)
// HIGHFIVE_REGISTER_TYPE(libarchive::impl::schema::mecp_state, create_compound_mecp_state)
// HIGHFIVE_REGISTER_TYPE(libgscf::rscf_orbitals_d_d, create_compound_rscf_orbitals_d_d)

template<>
std::function<HighFive::EnumType<perturbation_type>()> get_highfive_type_generating_function_enum(const std::string &file_type_name) {
    return std::function<HighFive::EnumType<perturbation_type>()>(&create_enum_perturbation_type);
}

template<>
std::function<HighFive::EnumType<mecp_algorithm>()> get_highfive_type_generating_function_enum(const std::string &file_type_name) {
    return std::function<HighFive::EnumType<mecp_algorithm>()>(&create_enum_mecp_algorithm);
}
