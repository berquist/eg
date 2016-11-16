#ifndef CLASS_TEMPLATE_H_
#define CLASS_TEMPLATE_H_

#include <armadillo>

template <class T>
class TestClass {

private:

    double dim = 5;

    T t;

public:

    TestClass();
    TestClass(T &t_) : t(t_) { }
    ~TestClass();

    void print();

};

#endif // CLASS_TEMPLATE_H_
