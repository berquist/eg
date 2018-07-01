#include <iostream>

int main() {

    int a = 0, b = 0;

#pragma omp parallel private(b)
{
    int c = 0;
#pragma omp critical
    std::cout << &a << " " << &b << " " << &c << std::endl;
}

    return 0;
}
