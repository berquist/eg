#ifndef CLASS_TEMPLATE_H_
#define CLASS_TEMPLATE_H_

#include <armadillo>

namespace foo {

template <class T>
class TestClass {

private:

    const double dim = 5;

    T t;

public:

    double dim_copy;

public:

    TestClass() {
        dim_copy = dim;
    }

    TestClass(T &t_) : t(t_) { }
    ~TestClass() { }

    void print(std::string st = "t") {
        t.print(st);
    }

};

} // namespace foo

#endif // CLASS_TEMPLATE_H_
