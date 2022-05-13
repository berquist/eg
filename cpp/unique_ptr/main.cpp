#include <cstdio>
#include "dummy.hpp"

std::unique_ptr<Dummy> make_dummy() {
    return std::make_unique<Dummy>();
}

void print_dummy(const std::unique_ptr<Dummy> &ptr) {
    printf("%d %c\n", ptr->x, ptr->y);
    printf("%p\n", ptr.get());
}

int main() {
    std::unique_ptr<Dummy> dup(new Dummy);
    dup->x = 2;
    dup->y = 'c';
    print_dummy(dup);
    auto dup2 = make_dummy();
    dup2->x = 4;
    dup2->y = 'a';
    print_dummy(dup2);
    return 0;
}
