#include "class_template_2.h"

template <class T>
TestClass<T>::TestClass()
{
    // This doesn't work properly?
    dim_copy = dim;
}

template <class T>
TestClass<T>::~TestClass()
{ }

// template TestClass<arma::vec>::TestClass();
template TestClass<arma::vec>::~TestClass();

// This below doesn't work.
// template TestClass<arma::mat>::TestClass() { t.ones(dim, dim); }
template TestClass<arma::mat>::~TestClass();

template TestClass<arma::cube>::TestClass();
template TestClass<arma::cube>::~TestClass();

// 'template <>' is needed for when the *implementation* is different.
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

template void TestClass<arma::vec>::print(std::string st);
template void TestClass<arma::mat>::print(std::string st);

template <class T>
T TestClass_Derived<T>::add(T &t1, T &t2)
{

    return t1 + t2;

}

template arma::vec TestClass_Derived<arma::vec>::add(arma::vec &t1, arma::vec &t2);
template arma::mat TestClass_Derived<arma::mat>::add(arma::mat &t1, arma::mat &t2);
template arma::cube TestClass_Derived<arma::cube>::add(arma::cube &t1, arma::cube &t2);

arma::mat TestClass_Fixed::mul(arma::mat &m1, arma::mat &m2)
{

    return m1 * m2;

}
