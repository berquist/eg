#include <complex>
#include <iostream>
#include <typeinfo>

int main() {
    double v1 = 4.2;
    std::complex<double> v2(3.4, 9.8);
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << typeid(v1).name() << std::endl;
    std::cout << typeid(v2).name() << std::endl;
    return 0;
}
