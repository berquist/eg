#include <iostream>
#include <type_traits>
#include "enable_if.hpp"

// https://stackoverflow.com/a/9660190
template<typename T, typename Sfinae = void>
struct Foo {
    Foo() {
        std::cout << "default" << std::endl;
    }
};

template<typename T>
struct Foo<T, typename std::enable_if<std::is_same<T, int>::value>::type> {
    Foo() {
        std::cout << "int" << std::endl;
    }
};

template<typename T>
struct Foo<T, typename std::enable_if<std::is_same<T, float>::value>::type> {
    Foo() {
        std::cout << "float" << std::endl;
    }
};

int main() {
    Foo<int> f1;
    Foo<bool> f2;
    Foo<float> f3;

    myfunc<int>();
    myfunc<bool>();
    myfunc<float>();
    return 0;
}
