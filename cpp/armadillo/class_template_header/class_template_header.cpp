#include "class_template_header.h"

//// The template destructor is only needed if it isn't present in the header file.
// template <class T>
// TestClass<T>::~TestClass()
// { }

//// The destructors here are only needed if the template destructor is defined.
// template TestClass<arma::vec>::TestClass();
// template TestClass<arma::vec>::~TestClass();
// template TestClass<arma::mat>::TestClass();
// template TestClass<arma::mat>::~TestClass();
// template TestClass<arma::cube>::TestClass();
// template TestClass<arma::cube>::~TestClass();

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
