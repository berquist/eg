#include <complex>
#include <tuple>
#include <type_traits>

// Question: https://stackoverflow.com/questions/25187323/how-can-i-get-the-innermost-template-parameter-type
// adapted from https://stackoverflow.com/a/25187583

template<typename T>
struct inner_impl
{
    using type = T;
};

template<template<typename> class E, typename T>
struct inner_impl<E<T>>
{
    // using type = typename inner_impl<T>::type;
    using type = T;
};

template<typename T>
using inner = typename inner_impl<T>::type;

template<class>
struct X;

static_assert(std::is_same<inner<X<X<X<int>>>>, X<X<int>>>::value, "");
static_assert(std::is_same<inner<std::complex<double>>, double>::value, "");
static_assert(std::is_same<inner<X<std::complex<double>>>, std::complex<double>>::value, "");

int main()
{
}
