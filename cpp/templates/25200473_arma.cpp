#include <armadillo>
#include <type_traits>

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

static_assert(
    std::is_same<innermost<arma::Mat<X<arma::Mat<double>>>>, double>::value,
    ""
);

static_assert(
    std::is_same<innermost<arma::mat>, double>::value,
    ""
);

int main()
{
}
