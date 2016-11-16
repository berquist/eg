#include <iostream>

bool compare_against_zero_implicit(size_t arg)
{

    return (arg <= 0);

}

bool compare_against_zero_implicit(int arg)
{

    return (arg <= 0);

}

bool compare_against_zero_explicit(int arg)
{

    int zero = 0;
    return (arg <= 0);

}

int main() {

    size_t NB2car_size_t = 28725;
    int NB2car_int = 28725;

    std::cout << "NB2car: " << NB2car_size_t << std::endl;
    std::cout << compare_against_zero_implicit(NB2car_size_t) << std::endl;
    std::cout << "NB2car_size_t*NB2car_size_t*3: " << NB2car_size_t*NB2car_size_t*3 << std::endl;
    std::cout << compare_against_zero_implicit(NB2car_size_t*NB2car_size_t*3) << std::endl;
    std::cout << compare_against_zero_implicit(NB2car_int) << std::endl;
    std::cout << "NB2car_int*NB2car_int*3: " << NB2car_int*NB2car_int*3 << std::endl;
    std::cout << compare_against_zero_implicit(NB2car_int*NB2car_int*3) << std::endl;
    std::cout << compare_against_zero_explicit(NB2car_size_t*NB2car_size_t*3) << std::endl;
    std::cout << compare_against_zero_explicit(NB2car_int*NB2car_int*3) << std::endl;

    return 0;

}
