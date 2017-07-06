#ifndef CLASS_TEMPLATE_HEADER_H_
#define CLASS_TEMPLATE_HEADER_H_

#include <armadillo>

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

template <class T>
class TestClass_Derived : public TestClass<T> {

private:

public:

    T add(T &t1, T &t2) const {
        return t1 + t2;
    }

};

class TestClass_Fixed : public TestClass_Derived< arma::mat > {

private:

public:

    arma::mat mul(arma::mat &m1, arma::mat &m2) const {
        return m1 * m2;
    }

};

#endif // CLASS_TEMPLATE_HEADER_H_
