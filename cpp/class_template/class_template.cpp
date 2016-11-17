#include <string>

#include "class_template.h"

template <class T>
TestClass<T>::TestClass()
{ }

template <class T>
TestClass<T>::~TestClass()
{ }

// template TestClass<arma::vec>::TestClass();
// template TestClass<arma::vec>::~TestClass();

// This below doesn't work.
// template TestClass<arma::mat>::TestClass() { t.ones(dim, dim); }
// template TestClass<arma::mat>::~TestClass();

template <>
TestClass<arma::vec>::TestClass()
{
    t.ones(dim);
}

template <>
TestClass<arma::mat>::TestClass()
{
    t.ones(dim, dim);
}

template <class T>
void TestClass<T>::print(std::string st)
{

    t.print(st);

    return;

}

// Not necessary?
// template void TestClass<arma::vec>::print(std::string st);
// template void TestClass<arma::mat>::print(std::string st);

template <class T>
T TestClass_Derived<T>::add(T &t1, T &t2)
{

    return t1 + t2;

}

// Not necessary?
// template arma::vec TestClass_Derived<arma::vec>::add(arma::vec &t1, arma::vec &t2);
// template arma::mat TestClass_Derived<arma::mat>::add(arma::mat &t1, arma::mat &t2);

arma::mat TestClass_Fixed::mul(arma::mat &m1, arma::mat &m2)
{

    return m1 * m2;

}

int main()
{

    const size_t dim = 2;
    const double f = 0.56;

    arma::vec fv3(dim);
    fv3.fill(f);

    arma::mat fm2(dim, dim);
    fm2.fill(f);

    TestClass<arma::vec> tcv1 = TestClass<arma::vec>();
    // http://stackoverflow.com/questions/877523/error-request-for-member-in-which-is-of-non-class-type
    // request for member ‘print’ in ‘tcv2’, which is of non-class
    // type ‘TestClass<arma::Col<double> >()’
    /// TestClass<arma::vec> tcv2();
    // This is how the default no-argument constructor should be called:
    TestClass<arma::vec> tcv2;
    TestClass<arma::vec> tcv3 = TestClass<arma::vec>(fv3);
    TestClass<arma::mat> tcm = TestClass<arma::mat>();
    TestClass<arma::mat> tcm2(fm2);

    tcv1.print("tcv1");
    tcv2.print("tcv2");
    tcv3.print("tcv3");
    tcm.print("tcm");
    tcm2.print("tcm2");

    arma::cube c1 = arma::cube(dim, dim, dim, arma::fill::ones) * 2;
    arma::cube c2 = arma::cube(dim, dim, dim, arma::fill::ones) * 3;
    TestClass_Derived<arma::cube> tcc;
    arma::cube c3 = tcc.add(c1, c2);
    c3.print("c3");

    TestClass_Fixed m;
    m.print("m");
    m.mul(fm2, fm2).print("fm2 * fm2");
    m.add(fm2, fm2).print("fm2 + fm2");

    return 0;

}
