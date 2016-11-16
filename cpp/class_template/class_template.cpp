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
void TestClass<T>::print()
{

    t.print("t");

    return;

}

template void TestClass<arma::vec>::print();
template void TestClass<arma::mat>::print();

int main()
{

    TestClass<arma::vec> tcv1 = TestClass<arma::vec>();
    TestClass<arma::vec> tcv2();
    TestClass<arma::mat> tcm = TestClass<arma::mat>();

    tcv1.print();
    // tcv2.print();
    tcm.print();

    return 0;

}
