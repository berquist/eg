#include <complex>
#include <tuple>
#include <type_traits>

// Question: https://stackoverflow.com/questions/25187323/how-can-i-get-the-innermost-template-parameter-type
// adapted from https://stackoverflow.com/a/25187583

template<typename T>
struct innermost_impl
{
    using type = T;
};

template<template<typename> class E, typename T>
struct innermost_impl<E<T>>
{
    using type = typename innermost_impl<T>::type;
};

template<template<typename...> class E, typename... Ts>
struct innermost_impl<E<Ts...>>
{
    using type = std::tuple<typename innermost_impl<Ts>::type...>;
};

template<typename T>
using innermost = typename innermost_impl<T>::type;

template<class>
struct X;

static_assert(std::is_same<innermost<X<X<X<int>>>>, int>::value, "");
static_assert(std::is_same<innermost<X<X<X<std::complex<double>>>>>, double>::value, "");

int main()
{
}
