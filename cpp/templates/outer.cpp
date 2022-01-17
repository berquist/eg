#include <iostream>
#include <typeinfo>
#include <utility>
#include "type_name.hpp"
#include <cassert>

// stolen from https://stackoverflow.com/a/24207963

template<class T>
struct inner_class_of { using outer_class = T; }; 

struct Message {
    struct Binding:inner_class_of<Message> {
    };
};

template<class T>
inner_class_of<T> get_outer_helper(inner_class_of<T>const&);

template<class T>
using outer_class_of_t = typename decltype(get_outer_helper(std::declval<T>()))::outer_class;

struct iterable {};

struct A {
    int A_int;
    template<typename T>
    struct B: inner_class_of<A>, iterable {
        int B_int;
        struct D: inner_class_of<B> {
            int D_int;
            struct E: inner_class_of<D>, iterable {
                int E_int;
            };
        };
    };
};

std::string print(const A &v) {
    return "a";
}

template<typename T>
std::string print(const typename A::B<T> &v) {
    return "foo";
}

template<typename T>
std::string print(const typename A::B<T>::D &v) {
    return "bar";
}

template<typename T>
std::string print(const typename A::B<T>::D::E &v) {
    return "baz";
}

int main() {

    A s0;
    A::B<int> s1;
    A::B<int>::D s2;
    A::B<A>::D s2_2;
    A::B<A>::D::E s3;

    std::cout << type_name<A::B<int>>() << std::endl;
    std::cout << type_name<outer_class_of_t<A::B<int>::D>>() << std::endl;
    std::cout << type_name<outer_class_of_t<A::B<int>::D::E>>() << std::endl;

    assert(print(s1) == std::string("foo"));
    assert(print<int>(s2) == std::string("bar"));
    assert(print<A>(s2_2) == std::string("bar"));
    assert(print<A>(s3) == std::string("baz"));

    const bool v0 = std::is_base_of<iterable, decltype(s0)>::value;
    const bool v1 = std::is_base_of<iterable, decltype(s1)>::value;
    const bool v2 = std::is_base_of<iterable, decltype(s2)>::value;
    const bool v2_2 = std::is_base_of<iterable, decltype(s2_2)>::value;
    const bool v3 = std::is_base_of<iterable, decltype(s3)>::value;
    assert(v0 == false);
    assert(v1 == true);
    assert(v2 == false);
    assert(v2_2 == false);
    assert(v3 == true);

    return 0;
}
