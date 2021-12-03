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
    using type = typename innermost_impl<Head>::type;
};

template<typename T>
using innermost = typename innermost_impl<T>::type;

template<class>
struct X;

static_assert(std::is_same<innermost<X<X<X<int>>>>, int>::value, "");

static_assert(std::is_same<innermost<std::vector<double>>, double>::value, "");
static_assert(std::is_same<innermost<std::vector<std::complex<double>>>, double>::value, "");
static_assert(
    std::is_same<innermost<std::vector<X<std::vector<int>>>>, int>::value,
    ""
);

int main()
{
}
