#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <iostream>
#include <vector>

#include <highfive/H5File.hpp>

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

#endif // COMMON_HPP_
