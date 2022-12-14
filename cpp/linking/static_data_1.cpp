#include "static_data.hpp"
#include <iostream>

int myfunc1() {
    std::cout << static_data::fdiff::ideriv.key << std::endl;
    return 1;
}
