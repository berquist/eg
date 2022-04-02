#include "common.hpp"

std::ostream& operator<<(std::ostream &os, const HighFive::ObjectType &ot) {
    switch (ot) {
    case HighFive::ObjectType::File:
        os << "HighFive::ObjectType::File";
        break;
    case HighFive::ObjectType::Group:
        os << "HighFive::ObjectType::Group";
        break;
    case HighFive::ObjectType::UserDataType:
        os << "HighFive::ObjectType::UserDataType";
        break;
    case HighFive::ObjectType::DataSpace:
        os << "HighFive::ObjectType::DataSpace";
        break;
    case HighFive::ObjectType::Dataset:
        os << "HighFive::ObjectType::Dataset";
        break;
    case HighFive::ObjectType::Attribute:
        os << "HighFive::ObjectType::Attribute";
        break;
    case HighFive::ObjectType::Other:
        os << "HighFive::ObjectType::Other";
        break;
    default:
        throw std::invalid_argument("invalid argument to operator<< for HighFive::ObjectType");
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const HighFive::DataTypeClass &dtc) {
    os << HighFive::type_class_string(dtc);
    return os;
}

std::ostream& operator<<(std::ostream &os, const HighFive::DataType &dt) {
    os << dt.string();
    return os;
}

std::ostream& operator<<(std::ostream &os, const perturbation_type &pt) {
    switch (pt) {
    case perturbation_type::electric:
        os << "perturbation_type::electric";
        break;
    case perturbation_type::magnetic:
        os << "perturbation_type::magnetic";
        break;
    case perturbation_type::geometric:
        os << "perturbation_type::geometric";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const mecp_algorithm &alg) {
    switch (alg) {
    case mecp_algorithm::branching_plane:
        os << "mecp_algorithm::branching_plane";
        break;
    case mecp_algorithm::direct:
        os << "mecp_algorithm::direct";
        break;
    case mecp_algorithm::penalty_function:
        os << "mecp_algorithm::penalty_function";
        break;
    }
    return os;
}

HighFive::EnumType<perturbation_type> create_enum_perturbation_type() {
    return {{"electric", perturbation_type::electric},
            {"magnetic", perturbation_type::magnetic},
            {"geometric", perturbation_type::geometric}};
}

HighFive::EnumType<mecp_algorithm> create_enum_mecp_algorithm() {
    return {{"branching_plane", mecp_algorithm::branching_plane},
            {"direct", mecp_algorithm::direct},
            {"penalty_function", mecp_algorithm::penalty_function}};
}

HighFive::CompoundType create_compound_mecp_state() {
    return HighFive::CompoundType(
        {
            {"spin", HighFive::AtomicType<bool>{}},
            {"irrep", HighFive::AtomicType<size_t>{}},
            {"state_within_irrep", HighFive::AtomicType<size_t>{}}
        }
        );
}

HighFive::CompoundType create_compound_rscf_orbitals_d_d() {
    return HighFive::CompoundType(
        {
            {"nbsf", HighFive::AtomicType<size_t>{}},
            {"nmo", HighFive::AtomicType<size_t>{}},
            {"nocc", HighFive::AtomicType<size_t>{}},
            {"c", HighFive::AtomicType<double>{}},
            {"eigval", HighFive::AtomicType<double>{}},
            {"objv", HighFive::AtomicType<double>{}}
        }
        );
}
