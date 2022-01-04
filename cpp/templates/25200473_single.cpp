#include <type_traits>
#include <vector>
#include <complex>

// Question: https://stackoverflow.com/questions/25187323/how-can-i-get-the-innermost-template-parameter-type
// adapted from https://stackoverflow.com/a/25200473

template<typename T>
struct innermost_impl
{
    using type = T;
};

template<template<typename...> class E, typename Head, typename... Tail>
struct innermost_impl<E<Head, Tail...>>
{
    // using type = typename innermost_impl<Head>::type;
    using type = Head;
};

template<typename T>
using innermost = typename innermost_impl<T>::type;

template<class>
struct X;

static_assert(std::is_same<innermost<X<X<X<int>>>>, X<X<int>>>::value, "");

static_assert(std::is_same<innermost<std::vector<double>>, double>::value, "");
static_assert(std::is_same<innermost<std::vector<std::complex<double>>>, std::complex<double>>::value, "");
static_assert(
    std::is_same<innermost<std::vector<X<std::vector<int>>>>, X<std::vector<int>>>::value,
    ""
);

int main()
{
}
