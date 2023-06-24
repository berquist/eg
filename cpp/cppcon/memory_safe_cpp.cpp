#include <memory>
#include <vector>

struct T {
    T(): v(100) {}
    std::vector<int> v;
};

struct Base {};

struct Derived : public Base {
    T t;
};

void Work_With_Delete(Base* b) {
    delete b;  // Boom!
}

int main() {
    Base* b = new Derived;
    Work_With_Delete(b);
    std::unique_ptr<Base> b1 = std::make_unique<Derived>();
    return 0;
}
