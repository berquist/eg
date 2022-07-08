#ifndef TGF_HPP_
#define TGF_HPP_

#include <functional>
#include <highfive/H5DataType.hpp>

template<typename T>
std::function<HighFive::EnumType<T>()> get_highfive_type_generating_function_enum(const std::string &file_type_name);

std::function<HighFive::CompoundType()> get_highfive_type_generating_function_compound(const std::string &file_type_name);
#endif // TGF_HPP_
