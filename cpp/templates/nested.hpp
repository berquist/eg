#ifndef NESTED_HPP_
#define NESTED_HPP_

#include <iostream>

// template<typename DT, typename CT, template<typename, typename> class C>
// `void myinnerfunc<double, arma::Cube>(arma::Cube<double> const&)'
template<typename DT, template<typename> class CT>
void myinnerfunc(const CT<DT> &value) {
    std::cout << value << std::endl;
}

#endif // NESTED_HPP_
