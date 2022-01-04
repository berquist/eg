#ifndef DTYPE_UTILS_H_
#define DTYPE_UTILS_H_

#include <ostream>
#include <highfive/H5DataType.hpp>

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
HighFive::DataType get_dtype(const T &val) {
    return HighFive::create_and_check_datatype<inner_type<decltype(static_cast<T>(const_cast<T&>(val)))>>();
}

std::ostream &operator<<(std::ostream &os, const HighFive::DataType &dt);

#endif // DTYPE_UTILS_H_
