#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <iostream>
#include <vector>

#include <highfive/H5DataType.hpp>

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        os << "v[" << i << "] = " << v[i] << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const HighFive::ObjectType &ot);
std::ostream& operator<<(std::ostream &os, const HighFive::DataTypeClass &dtc);
std::ostream& operator<<(std::ostream &os, const HighFive::DataType &dt);

enum perturbation_type {
    electric,
    magnetic,
    geometric
};

enum class mecp_algorithm {
    branching_plane,
    direct,
    penalty_function
};

std::ostream& operator<<(std::ostream &os, const perturbation_type &pt);
std::ostream& operator<<(std::ostream &os, const mecp_algorithm &alg);

HighFive::EnumType<perturbation_type> create_enum_perturbation_type();
HighFive::EnumType<mecp_algorithm> create_enum_mecp_algorithm();

#endif // COMMON_HPP_
