#include <iostream>

// personal solution #1

typedef unsigned long long fib_t;

constexpr fib_t fib_stack(fib_t n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib_stack(n - 1) + fib_stack(n - 2);
    }
}

template<fib_t n>
constexpr fib_t fib_1();

template<>
constexpr fib_t fib_1<0>() { return 0; }
template<>
constexpr fib_t fib_1<1>() { return 1; }
template<fib_t n>
constexpr fib_t fib_1() { return fib_1<n - 1>() + fib_1<n - 2>(); }

int main() {
    const fib_t n = 20;
    std::cout << "fib_stack: " << fib_stack(n) << std::endl;
    std::cout << "fib_1: " << fib_1<n>() << std::endl;
    return 0;
}
