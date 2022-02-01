#include <iostream>

struct interface {
    template<typename T>
    void myfunc() {
        std::cout << "hello from myfunc" << std::endl;
    }
};

struct B: interface {};

template<typename T>
void mynewfunc(T &t) {
    t.template myfunc<T>();
}

int main() {
    B b;
    mynewfunc(b);
    return 0;
}
