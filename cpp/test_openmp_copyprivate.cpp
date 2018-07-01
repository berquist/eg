#include <iostream>

// int main() {

//     int a = 0, b = 0;

// #pragma omp parallel copyprivate(b)
// {
//     int c = 0;
// #pragma omp critical
//     std::cout << &a << " " << &b << " " << &c << std::endl;
// }

//     return 0;
// }

int main() {

    int a = 0, b = 0;

#pragma omp parallel private(b) num_threads(4)
{
    int c = 0;
#pragma omp single copyprivate(c)
    {
        c = 1;
    }
#pragma omp critical
    std::cout << &a << " " << &b << " " << &c << std::endl;
}

    return 0;
}
