#include <iostream>

int get_mult(int m) {
    if (m < 1000) {
        return m;
    }
    return m / 1000;
}

int main() {
    std::cout << get_mult(4) << std::endl;
    std::cout << get_mult(4000) << std::endl;
    return 0;
}
