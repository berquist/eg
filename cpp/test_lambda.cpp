#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        os << "v[" << i << "] = " << v[i] << std::endl;
    }
    return os;
}

typedef std::vector<int> vec_t;

int main() {
    const vec_t v1 {0, 1, 3, 10};
    const vec_t v2 {1, 2, 2, 8};
    auto gt = [](int a, int b) { return a > b; };
    for (size_t i = 0; i < v1.size(); i++) {
        std::cout << gt(v1[i], v2[i]) << std::endl;
    }
    auto square = [](auto x) { return std::pow(x, 2); };
    auto square_ref = [](auto &x) { x = std::pow(x, 2); };
    // vec_t v3(v1.begin(), v1.end(), square);
    // this brings along the const?
    // decltype(v2) v3(v2);
    vec_t v3(v2);
    std::cout << v3 << std::endl;
    std::for_each(v3.begin(), v3.end(), square_ref);
    std::cout << v3 << std::endl;
    return 0;
}
