#include <iostream>
#include <tuple>

typedef unsigned long long fib_t;

// personal solution

constexpr fib_t fib_stack(fib_t n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib_stack(n - 1) + fib_stack(n - 2);
    }
}

template<fib_t N>
constexpr fib_t fib_1();

template<>
constexpr fib_t fib_1<0>() { return 0; }
template<>
constexpr fib_t fib_1<1>() { return 1; }
template<fib_t N>
constexpr fib_t fib_1() { return fib_1<N - 1>() + fib_1<N - 2>(); }

// simplification of https://stackoverflow.com/a/908345

template<fib_t N>
struct Fibonacci {
    enum { value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value };
};

template<>
struct Fibonacci<0> {
    enum { value = 0 };
};

template<>
struct Fibonacci<1> {
    enum { value = 1 };
};

// https://stackoverflow.com/a/6398890: extend above idea to generating a
// table using variadic templates

template<fib_t N, typename Tuple, typename ... Types>
struct make_fibtuple_impl;

template<fib_t N, typename ... Types>
struct make_fibtuple_impl<N, std::tuple<Types...>> {
    typedef typename make_fibtuple_impl<N - 1, std::tuple<Fibonacci<N>, Types...>>::type type;
};

template<typename... Types>
struct make_fibtuple_impl<0, std::tuple<Types...>> {
    typedef std::tuple<Fibonacci<0>, Types...> type;
};

template<fib_t N>
struct make_fibtuple : make_fibtuple_impl<N, std::tuple<>>
{ };

int main() {
    constexpr fib_t n = 20;
    std::cout << "fib_stack: " << fib_stack(n) << std::endl;
    std::cout << "fib_1: " << fib_1<n>() << std::endl;
    std::cout << "struct: " << Fibonacci<n>::value << std::endl;
    constexpr auto tup = typename make_fibtuple<n>::type();
    std::cout << "tuple: " << std::get<n>(tup).value << std::endl;
    return 0;
}
