// examples of how to use static assertions and is_base_of as part of control flow

#include "type_name.hpp"
#include <iostream>

template<typename container>
struct can_add {
    template<typename to_add>
    to_add add();
};

struct prop {};
struct deny {};
struct is_thing {};
struct A: can_add<A>, is_thing {};
struct B: can_add<B>, is_thing, prop {};
struct C: can_add<C>, deny {};
struct D: can_add<D> {};

template<typename container>
template<typename to_add>
to_add can_add<container>::add() {
    std::cout << \
        "[add] container: " << \
        type_name<container>() << \
        " to_add: " << \
        type_name<to_add>() << \
        std::endl;

    constexpr bool container_is_thing = std::is_base_of<is_thing, container>::value;
    constexpr bool to_add_is_thing = std::is_base_of<is_thing, to_add>::value;
    constexpr bool to_add_prop = std::is_base_of<prop, to_add>::value;

    // only allow adding something that's `prop` to something that's `is_thing`
    if (to_add_prop) {
        static_assert(container_is_thing,
                      "Can only add something derived from `prop` to something derived from `is_thing`");
    }

    // default (empty) constructor good enough for this example
    to_add inst;
    return inst;
}

int main() {
    // base type on the left, derived type on the right
    static_assert(std::is_base_of<prop, B>::value, "B not derived from prop");
    static_assert(!std::is_base_of<B, prop>::value, "prop not derived from B");

    A a;
    D d;
    // B is `prop`, A is `is_thing`
    B b = a.add<B>();
    // B is `prop`, D is *not* `is_thing`
    // B b2 = d.add<B>();
    D d2 = b.add<D>();
    
    return 0;
}
